/* scvp_srv.c */
/* Written by Yann Busnel <Yann.Busnel@enst-bretagne.fr> */
/* for the RSM group of projects - July 2003 */
/* ================================================================ */

#include <sys/param.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/scvp.h>
#include <openssl/x509_vfy.h>

#ifdef no_debug
#define log(x,y)
#else
#define log(x,y)	fprintf(stderr, x "\n", y)
#endif

#define NBRET	5
#define CHECK_STATUS_VALID		0
#define CHECK_STATUS_NOPATH		1
#define CHECK_STATUS_INVALID		0x10
#define CHECK_STATUS_REVOKED		0x100
#define CHECK_STATUS_UNKNOWN		0x200
#define CHECK_STATUS_UNAVAIL		0x400

typedef struct scvp_responder_ctx_st {
	SCVP_REQUEST *CVRequest;
	SCVP_RESPONSE *CVResponse;
	SCVP_CERTREF *certRef;
	X509 *cert;
	int checks[NBRET];
	int wantbacks[NBRET];
	long response_status;		/* defaults are SUCCESS */
	long reply_status;
	long check_status;
	long wb_status;			/* default is FALSE */
	unsigned char *rbuf, *sbuf;
	int rlen, slen;
} SCVP_RESPONDER_CTX;

typedef struct read_ctx_st {
	char *buf;
	int size, len, off;
} READ_CTX;

typedef struct global_context_st {
	X509_STORE_CTX csc;
	READ_CTX rc;
	SCVP_RESPONDER_CTX ctx;
} SCVP_CTX;

char *bpeek(READ_CTX *rc, int *cnt);
char *bread(READ_CTX *rc, int *cnt);
void bfill(READ_CTX *rc, int cnt);
int parse_http(READ_CTX *rc, int *lenp);
int send_http(SCVP_CTX *gcp, int status);
int scvp_srv(X509_STORE *store);
int cb(int ok, X509_STORE_CTX *csc);
int scvp_check_check(SCVP_CTX *gcp, ASN1_OBJECT *check);
int scvp_check_wantback(SCVP_CTX *gcp, ASN1_OBJECT *wantback);
void scvp_check_request(SCVP_CTX *gcp);
SCVP_REPLYCHECK *scvp_build_check(SCVP_RESPONDER_CTX *ctx, int nid);
SCVP_REPLYWANTBACK *scvp_build_wantback(SCVP_CTX *gcp, int nid);
SCVP_CERTBUNDLE *scvp_build_chain(SCVP_CTX *gcp);
SCVP_REVOCATIONINFOS *scvp_build_revinfo(SCVP_CTX *gcp);
int scvp_build_response(SCVP_CTX *gcp);
#ifdef dnssec_trust
int trust_dnssec(X509_TRUST *trust, X509 *x, int flags);
#endif
#ifdef ldap_lookup
int get_issuer(X509 **issuer, X509_STORE_CTX *ctx, X509 *x);
int get_crl(X509_STORE_CTX *ctx, X509_CRL **crl, X509 *x);
int get_by_subjects(X509_STORE_CTX *vs, int type, X509_NAME *name,
			   X509 *x, X509_OBJECT *ret);
char *get_uri(X509 *x, int type, int *len);

extern X509_LOOKUP_METHOD *X509_LOOKUP_ldap(void);
#endif

int
main(int argc, char *argv[])
{
	X509_STORE *store = NULL;
	X509_LOOKUP *lkpf, *lkpd;
#ifdef ldap_lookup
	X509_LOOKUP *lkpl;
#endif
	char *CAfile, *CApath;
	int cr;

#define ERR(o, msg, arg)	{ \
		log(msg, arg); \
		if (o) { \
			unsigned long l; \
			while((l = ERR_get_error()) != 0) \
				log("%s", ERR_error_string(l, NULL)); \
		} \
		cr = 1; \
		goto senderr; \
		} while(0)

	/* SIGPIPE handler? */

	/* decode arguments */

	CAfile = NULL;
	CApath = NULL;

	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();

	/* init store */

	store = X509_STORE_new();
	if (store == NULL)
		ERR(1, "can't allocate store", "");
	X509_STORE_set_verify_cb_func(store, &cb);
#ifdef ldap_lookup
	store->get_issuer = get_issuer;
	store->get_crl = get_crl;
#endif
	lkpf = X509_STORE_add_lookup(store, X509_LOOKUP_file());
	if (lkpf == NULL)
		ERR(1, "can't set file lookup", "");
	lkpd = X509_STORE_add_lookup(store, X509_LOOKUP_hash_dir());
	if (lkpd == NULL)
		ERR(1, "can't set directory lookup", "");
#ifdef ldap_lookup
	lkpl = X509_STORE_add_lookup(store, X509_LOOKUP_ldap());
	if (lkpl == NULL)
		ERR(1, "can't set ldap lookup", "");
#endif

	while (argc >= 2) {
		if (*(argv[1] + strlen(argv[1]) - 1) == '/') {
			CApath = argv[1];
			CApath[strlen(CApath) - 1] = '\0';
			if (!X509_LOOKUP_add_dir(lkpd,
						 CApath,
						 X509_FILETYPE_PEM))
				ERR(1, "can't load CApath = %s", CApath);
		} else {
			CAfile = argv[1];
			if (!X509_LOOKUP_load_file(lkpf,
						   CAfile,
						   X509_FILETYPE_PEM))
				ERR(1, "can't load CAfile = %s", CAfile);
		}
		argc--, argv++;
	}
	if (CAfile == NULL)
		X509_LOOKUP_load_file(lkpf, NULL, X509_FILETYPE_DEFAULT);
	if (CApath == NULL)
		X509_LOOKUP_add_dir(lkpd, NULL, X509_FILETYPE_DEFAULT);

	/* ADD LDAP method here ? */
	/* DNSsec trust */
#ifdef dnssec_trust
#ifndef X509_TRUST_DNSSEC
#define X509_TRUST_DNSSEC	X509_TRUST_MAX + 1
	if (!X509_TRUST_add(X509_TRUST_DNSSEC, 0, trust_dnssec,
			    "DNSsec", X509_TRUST_COMPAT, NULL))
		ERR(1, "can't add dnssec trust", "");
#endif
	if (!X509_STORE_set_trust(store, X509_TRUST_DNSSEC))
		ERR(1, "can't set DNSsec trust", "");
#else
	if (!X509_STORE_set_trust(store, X509_TRUST_COMPAT))
		ERR(1, "can't set compat trust", "");
#endif
	ERR_clear_error();

#undef ERR

	cr = scvp_srv(store);

   senderr:
	if (store)
		X509_STORE_free(store);
	EVP_cleanup();
	ERR_free_strings();
	exit(cr);
}

char *
bpeek(READ_CTX *rc, int *cnt)
{
	if ((cnt == NULL) || (*cnt < 0))
		return (char *)-1;
	if (*cnt > rc->len) {
		bfill(rc, *cnt);
		if (rc->buf == NULL)
			return (char *)-1;
		*cnt = rc->len;
	}
	if (rc->len == 0)
		return NULL;
	else
		return rc->buf + rc->off;
}

char *
bread(READ_CTX *rc, int *cnt)
{
	if ((cnt == NULL) || (*cnt < 0))
		return (char *)-1;
	if (rc->off > 0) {
		bcopy(rc->buf + rc->off, rc->buf, rc->len);
		rc->off = 0;
	}
	if (*cnt > rc->len) {
		bfill(rc, *cnt);
		if (rc->buf == NULL)
			return (char *)-1;
		*cnt = rc->len;
	}
	if (*cnt == 0)
		return NULL;
	else {
		rc->off += *cnt;
		rc->len -= *cnt;
		return rc->buf;
	}
}

void
bfill(READ_CTX *rc, int cnt)
{
	char *ptr;
	int cc;

	if (cnt <= rc->len)
		return;
	if (cnt >= BUFSIZ)
		cnt = BUFSIZ;
	if (rc->off > 0) {
		bcopy(rc->buf + rc->off, rc->buf, rc->len);
		rc->off = 0;
	}
	if (cnt > rc->size) {
		rc->buf = realloc(rc->buf, cnt);
		if (rc->buf == NULL)
			return;
		rc->size = cnt;
	}
	cnt -= rc->len;
	ptr = rc->buf + rc->len;
	for (; cnt > 0;) {
		cc = read(0, ptr, cnt);
		if (cc < 0) {
			free(rc->buf);
			rc->buf = NULL;
			return;
		}
		if (cc == 0)
			return;
		rc->len += cc;
		ptr += cc;
		cnt -= cc;
	}
}

int
parse_http(READ_CTX *rc, int *lenp)
{
	char *line, *p, *e;
	int cc, state;

#define ERR(code, msg, arg)	{ \
		log(msg, arg); \
		return code; \
		}

	/* parse headers */

	for (state = 0, *lenp = 0;;) {
		cc = 256;
		line = bpeek(rc, &cc);
		if ((line == (char *)-1) || (line == NULL) || (cc < 40))
			ERR(400, "can't read: %s", strerror(errno));
		e = line + cc;
		if ((line[0] == '\r') && (line[1] == '\n')) {
			/* end of headers */
			if (*lenp == 0)
				ERR(411, "no Content-Length", "");
			if (state == 3) {
				cc = 2;
				(void) bread(rc, &cc);
				break;
			}
			ERR(412, "bad headers", "");
		}
		if (state == 0) {
			/* init: get POST */
			if (strncmp(line, "POST ", 5) == 0) {
				state = 1;
				goto next;
			} else
				ERR(405, "can't get POST", "");
		}
		/* get Content-xxx: */
		if (strncmp(line, "Content-", 8) != 0)
			goto next;
		/* Content-Length: <len> */
		if ((*lenp == 0) &&
		    (strncmp(line, "Content-Length:", 15) == 0)) {
			*lenp = (int)strtol(line + 15, NULL, 10);
			if (*lenp <= 0)
				ERR(412, "bad length %d", *lenp);
			if (state == 2)
				state = 3;
			goto next;
		}
		/* Content-Type: <type> */
		if (strncmp(line, "Content-Type:", 13) == 0) {
			p = line + 13;
			while (p <= e - 26) {
				if ((*p == ' ') | (*p == '\t'))
					p++;
				else
					break;
			}
			if (strncmp(p, "application/scvp-request", 24) == 0) {
				state = 2;
				goto next;
			}
			ERR(415, "bad content type", "");
		}
	    next:
		/* get end of line */
		p = line + 1;
		while (p < e) {
			if ((*p != '\r') || (*(p + 1) != '\n'))
				p++;
			else
				break;
		}
		p++;
		if (p >= e)
			ERR(400, "line too long", "");
		cc = p - line + 1;
		(void) bread(rc, &cc);
	}
#undef ERR

	return 0;
}

int
send_http(SCVP_CTX *gcp, int status)
{
	SCVP_RESPONDER_CTX *ctx;
	int cc, len;
	char *p;

	if (gcp == NULL)
		status = 500;

	if (status != 0) {
		printf("HTTP/1.1 %03d fatal error\r\n", status);
		return 1;
	}

	ctx = &gcp->ctx;
	len = ctx->slen;
	p = (char *) ctx->sbuf;

	printf("HTTP/1.1 200 OK\r\n");
	printf("Content-Length: %d\r\n", len);
	printf("Content-Type: application/scvp-response\r\n");
	printf("\r\n");
	fflush(stdout);

	for (cc = 0; len > 0; p += cc, len -= cc) {
		cc = write(1, p, len);
		if (cc <= 0) {
			log("can't write: %s", strerror(errno));
			return 1;
		}
	}
	return 0;
}

int
scvp_srv(X509_STORE *store)
{
	SCVP_CTX *gcp = NULL;
	X509_STORE_CTX *csc = NULL;
	READ_CTX *rc = NULL;
	SCVP_RESPONDER_CTX *ctx = NULL;
	unsigned char *p;
	int cnt, status;

#define ERR(o, code, msg, arg)	{ \
		log(msg, arg); \
		if (o) { \
			unsigned long l; \
			while((l = ERR_get_error()) != 0) \
				log("%s", ERR_error_string(l, NULL)); \
		} \
		status = code; \
		goto sendhttp; \
		}

	gcp = (SCVP_CTX *) malloc(sizeof(SCVP_CTX));
	if (gcp == NULL)
		ERR(0, 500, "can't allocate contexts: %s", strerror(errno));
	bzero(gcp, sizeof(SCVP_CTX));
	csc = &gcp->csc;
	rc = &gcp->rc;
	ctx = &gcp->ctx;
	ctx->CVResponse = SCVP_RESPONSE_new();
	if (ctx->CVResponse == NULL)
		ERR(1, 500, "can't create response", "");

	/* do it */

	status = parse_http(rc, &ctx->rlen);
	if (status != 0)
		goto sendhttp;

	ctx->rbuf = (unsigned char *) malloc(ctx->rlen);
	if (ctx->rbuf == NULL)
		ERR(0, 500,
		     "can't allocate receive buffer: %s",
		     strerror(errno));
	for (p = ctx->rbuf, cnt = ctx->rlen; cnt > 0;) {
		char *rb;
		int cc = cnt;

		rb = bread(rc, &cc);
		if (rb == (char *)-1)
			ERR(0, 500, "can't read: %s", strerror(errno));
		if (rb == NULL)
			ERR(0, 500, "short read: missing %d", cnt);
		bcopy(rb, p, cc);
		p += cc;
		cnt -= cc;
	}

	p = ctx->rbuf;
	ctx->CVRequest = d2i_SCVP_REQUEST(NULL, &p, ctx->rlen);
	if (ctx->CVRequest == NULL)
		ERR(1, 500, "request decoding failed", "");

	X509_STORE_CTX_init(csc, store, NULL, NULL);
	scvp_check_request(gcp);
	if ((ctx->response_status > 0) || (ctx->reply_status > 0))
		goto checked;

	X509_STORE_CTX_set_cert(csc, ctx->cert);
	if (!X509_verify_cert(csc))
		ctx->wb_status = 0;
	else
		ctx->wb_status = 1;

   checked:
	if (scvp_build_response(gcp) < 0)
		ERR(0, 500, "can't build response", "");
	ctx->slen = i2d_SCVP_RESPONSE(ctx->CVResponse, NULL);
	if (ctx->slen <= 0)
		ERR(1, 500, "response encoding failed (get length)", "");
	ctx->sbuf = (unsigned char *) malloc(ctx->slen + 1);
	bzero(ctx->sbuf, ctx->slen + 1);
	p = ctx->sbuf;
	if (i2d_SCVP_RESPONSE(ctx->CVResponse, &p) <= 0)
		ERR(1, 500, "response encoding failed (real encoding)", "");

#undef ERR

	/* debug */
	{
		int fd = open("resp", O_WRONLY|O_CREAT|O_TRUNC, 0644);

		(void) write(fd, (char *) ctx->sbuf, ctx->slen);
		(void) close(fd);
	}

    sendhttp:
	status |= send_http(gcp, status);

	if (gcp) {
		if (rc->buf)
			free(rc->buf);
		if (ctx->CVRequest)
			SCVP_REQUEST_free(ctx->CVRequest);
		if (ctx->CVResponse)
			SCVP_RESPONSE_free(ctx->CVResponse);
		if (ctx->rbuf)
			free(ctx->rbuf);
		if (ctx->sbuf)
			free(ctx->sbuf);
		X509_STORE_CTX_free(csc);
	}

	return status != 0;
}

int
cb(int ok, X509_STORE_CTX *csc)
{
	SCVP_RESPONDER_CTX *ctx = &((SCVP_CTX *)csc)->ctx;

	if (ok)
		return ok;

	switch (csc->error) {
	case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
	case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
	case X509_V_ERR_PATH_LENGTH_EXCEEDED:
	case X509_V_ERR_CERT_CHAIN_TOO_LONG:
	case X509_V_ERR_SUBJECT_ISSUER_MISMATCH:
	case X509_V_ERR_AKID_SKID_MISMATCH:
	case X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH:
	case X509_V_ERR_KEYUSAGE_NO_CERTSIGN:
		ctx->reply_status = SCVP_REPLY_STATUS_CERTPATHCONSTRUCTFAIL;
		ctx->check_status |= CHECK_STATUS_NOPATH;
		break;

	case X509_V_ERR_UNABLE_TO_GET_CRL:
	case X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER:
	case X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE:
	case X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD:
	case X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD:
	case X509_V_ERR_CRL_NOT_YET_VALID:
	case X509_V_ERR_CRL_HAS_EXPIRED:
	case X509_V_ERR_CERT_NOT_YET_VALID:
	case X509_V_ERR_CRL_SIGNATURE_FAILURE:
		ctx->reply_status = SCVP_REPLY_STATUS_CERTPATHNOTVALIDNOW;
		ctx->check_status |= CHECK_STATUS_UNAVAIL;
		break;

	case X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY:
	case X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE:
	case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
	case X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN:
	case X509_V_ERR_INVALID_CA:
	case X509_V_ERR_CERT_SIGNATURE_FAILURE:
	case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
	case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
	case X509_V_ERR_CERT_HAS_EXPIRED:
	case X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE:
		ctx->reply_status = SCVP_REPLY_STATUS_CERTPATHNOTVALID;
		ctx->check_status |= CHECK_STATUS_INVALID;
		break;

	case X509_V_ERR_CERT_REVOKED:
		ctx->check_status |= CHECK_STATUS_REVOKED;
		break;

	case X509_V_ERR_APPLICATION_VERIFICATION:
	case X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION:
	case X509_V_ERR_INVALID_PURPOSE:
	case X509_V_ERR_CERT_UNTRUSTED:
	case X509_V_ERR_CERT_REJECTED:
		break;

	case X509_V_ERR_OUT_OF_MEM:
	default:
		ctx->response_status = SCVP_STATUS_CODE_INTERNALERROR;
		break;
	}
	log("cb called for error: %s",
	    X509_verify_cert_error_string(csc->error));
	ERR_clear_error();

	return ok;
}

int
scvp_check_check(SCVP_CTX *gcp, ASN1_OBJECT *check)
{
	X509_STORE_CTX *csc = &gcp->csc;
	SCVP_RESPONDER_CTX *ctx = &gcp->ctx;
	int nid = OBJ_obj2nid(check);

	switch (nid) {
	case NID_id_stc_build_pkc_path:
	case NID_id_stc_build_valid_pkc_path:
		return nid;

	case NID_id_stc_build_status_checked_pkc_path:
		X509_STORE_CTX_set_flags(csc,
			X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);
		return nid;

	case NID_id_stc_build_aa_path:
	case NID_id_stc_build_valid_aa_path:
	case NID_id_stc_build_status_checked_aa_path:
	case NID_id_stc_status_check_ac_and_build_status_checked_aa_path:
		ctx->response_status = SCVP_STATUS_CODE_UNSUPPORTEDCHECKS;
		return 0;

	case NID_undef:
	default:
		ctx->reply_status = SCVP_REPLY_STATUS_UNRECOGNIZEDCHECK;
		return 0;
	}
}

int
scvp_check_wantback(SCVP_CTX *gcp, ASN1_OBJECT *wantback)
{
	SCVP_RESPONDER_CTX *ctx = &gcp->ctx;
	int nid = OBJ_obj2nid(wantback);

	switch (nid) {
	case NID_id_swb_pkc_cert_path:
	case NID_id_swb_pkc_revocation_info:
	case NID_id_swb_pkc_cert_status:
	case NID_id_swb_pkc_public_key_info:
		return nid;

	case NID_id_swb_aa_cert_path:
	case NID_id_swb_aa_revocation_info:
	case NID_id_swb_ac_revocation_info:
	case NID_id_swb_ac_cert_status:
		ctx->response_status = SCVP_STATUS_CODE_UNSUPPORTEDWANTBACKS;
		return 0;

	case NID_undef:
	default:
		ctx->reply_status = SCVP_REPLY_STATUS_UNRECOGNIZEDWANTBACK;
		return 0;
	}
}

void
scvp_check_request(SCVP_CTX *gcp)
{
	SCVP_RESPONDER_CTX *ctx = &gcp->ctx;
	SCVP_REQUEST *req = ctx->CVRequest;
	SCVP_RESPONSE *resp = ctx->CVResponse;
	SCVP_QUERY *query;
	int i, nid;

#define getRerr(o, x)	{ \
	ctx->response_status = (x); \
	if (o) { \
		unsigned long l; \
		while((l = ERR_get_error()) != 0) \
			log("%s", ERR_error_string(l, NULL)); \
	} \
        return; \
	} while(0)

#define getQerr(o, x)	{ \
	ctx->reply_status = (x); \
	if (o) { \
		unsigned long l; \
		while((l = ERR_get_error()) != 0) \
			log("%s", ERR_error_string(l, NULL)); \
	} \
        return; \
	} while(0)

	/* scvpVersion */

	if (req->scvpVersion == NULL)
		getRerr(0, SCVP_STATUS_CODE_UNABLETODECODE);
	if (ASN1_INTEGER_get(req->scvpVersion) != 1L)
		getRerr(0, SCVP_STATUS_CODE_UNSUPPORTEDVERSION);

	/* requestor */

	if (req->requestor != NULL)
		resp->requestor = ASN1_OCTET_STRING_dup(req->requestor);
	
	/* requestNonce */

	if (req->requestNonce != NULL)
		resp->requestNonce = ASN1_OCTET_STRING_dup(req->requestNonce);

	/* reqExtensions */

	if ((req->reqExtensions != NULL) &&
	    (sk_X509_EXTENSION_num(req->reqExtensions) > 0) &&
	    (sk_X509_EXTENSION_value(req->reqExtensions, 0) != NULL))
		getRerr(0, SCVP_STATUS_CODE_SKIPUNRECOGNIZEDITEMS);

	/* query */

	query = req->query;
	if (query == NULL)
		getRerr(0, SCVP_STATUS_CODE_BADSTRUCTURE);

	/* query -> queriedCerts */
	/* TODO: more than one cert */

	if ((query->queriedCerts == NULL) ||
	    (sk_SCVP_CERTREF_num(query->queriedCerts) != 1) ||
	    (sk_SCVP_CERTREF_value(query->queriedCerts, 0) == NULL))
		getRerr(0, SCVP_STATUS_CODE_BADSTRUCTURE);
	ctx->certRef = sk_SCVP_CERTREF_value(query->queriedCerts, 0);
	if (ctx->certRef->type != V_SCVP_CERTREF_PKC)
		getRerr(0, SCVP_STATUS_CODE_ABORTUNRECOGNIZEDITEMS);
	if (ctx->certRef->value.pkc->type != V_SCVP_PKCREF_CERT)
		getRerr(0, SCVP_STATUS_CODE_ABORTUNRECOGNIZEDITEMS);
	ctx->cert = ctx->certRef->value.pkc->value.cert;
	if (ctx->cert == NULL)
		getQerr(0, SCVP_REPLY_STATUS_MALFORMEDPKC);
	ctx->cert = X509_dup(ctx->cert);
	if (ctx->cert == NULL)
		getRerr(1, SCVP_STATUS_CODE_INTERNALERROR);

	/* query -> checks */

	if ((query->checks == NULL) ||
	    (sk_ASN1_OBJECT_num(query->checks) < 1) ||
	    (sk_ASN1_OBJECT_num(query->checks) > NBRET))
		getRerr(0, SCVP_STATUS_CODE_UNSUPPORTEDCHECKS);
	for (i = 0; i < sk_ASN1_OBJECT_num(query->checks); i++) {
		ASN1_OBJECT *check;

		check = sk_ASN1_OBJECT_value(query->checks, i);
		if (check == NULL)
			getQerr(0, SCVP_REPLY_STATUS_UNRECOGNIZEDCHECK);
		nid = scvp_check_check(gcp, check);
		ctx->checks[i] = nid;
	}

	/* query -> wantBack */

	if ((query->wantBack == NULL) ||
	    (sk_ASN1_OBJECT_num(query->wantBack) < 1) ||
	    (sk_ASN1_OBJECT_num(query->wantBack) > NBRET))
		getRerr(0, SCVP_STATUS_CODE_UNSUPPORTEDWANTBACKS);
	for (i = 0; i < sk_ASN1_OBJECT_num(query->wantBack); i++) {
		ASN1_OBJECT *wantback;

		wantback = sk_ASN1_OBJECT_value(query->wantBack, i);
		if (wantback == NULL)
			getQerr(0, SCVP_REPLY_STATUS_UNRECOGNIZEDWANTBACK);
		nid = scvp_check_wantback(gcp, wantback);
		ctx->wantbacks[i] = nid;
	}

	/* query -> validityTime */

	if (query->validityTime != NULL)
		getQerr(0, SCVP_REPLY_STATUS_UNAVAILABLEVALIDITYTIME);

	/* query -> trustAnchors */

	if ((query->trustAnchors != NULL) &&
	    (sk_SCVP_TRUSTANCHOR_num(query->trustAnchors) > 0) &&
	    (sk_SCVP_TRUSTANCHOR_value(query->trustAnchors, 0) != NULL))
		getQerr(0, SCVP_REPLY_STATUS_UNRECOGNIZEDCERTPOLICY);

	/* query -> queryExtensions */

	if ((query->queryExtensions != NULL) &&
	    (sk_X509_EXTENSION_num(query->queryExtensions) > 0) &&
	    (sk_X509_EXTENSION_value(query->queryExtensions, 0) != NULL))
		getQerr(0, SCVP_REPLY_STATUS_UNRECOGNIZEDEXTENSION);

	/* query -> valPolicy */

	if ((query->valPolicy == NULL) ||
	    (query->valPolicy->valPolicyId == NULL))
		getQerr(0, SCVP_REPLY_STATUS_SUCCESS);
	nid = OBJ_obj2nid(query->valPolicy->valPolicyId);
	if (nid != NID_id_svp_defaultValPolicy)
		getQerr(0, SCVP_REPLY_STATUS_UNRECOGNIZEDCERTPOLICY);

#undef getRerr
#undef getQerr

	ctx->reply_status = SCVP_REPLY_STATUS_SUCCESS;
        return;
}

SCVP_REPLYCHECK *
scvp_build_check(SCVP_RESPONDER_CTX *ctx, int nid)
{
	SCVP_REPLYCHECK *check = SCVP_REPLYCHECK_new();
	ASN1_OBJECT *obj;
	long status = ctx->check_status;

	if ((check == NULL) ||
	    (check->check == NULL) ||
	    (check->status == NULL)) {
		log("build response: allocation failed (check)", "");
		return check;
	}
	obj = OBJ_nid2obj(nid);
	if (obj == NULL) {
		log("build response: can't get check OID", "");
		SCVP_REPLYCHECK_free(check);
		return NULL;
	}
	check->check = obj;
	if ((status & CHECK_STATUS_NOPATH) != 0)
		status |= CHECK_STATUS_INVALID;
	if ((status & (CHECK_STATUS_NOPATH | CHECK_STATUS_INVALID)) != 0)
		status |= CHECK_STATUS_UNKNOWN;
	switch (nid) {
	case NID_id_stc_build_pkc_path:
		if ((status & CHECK_STATUS_NOPATH) != 0)
			status = 1;
		else
			status = 0;
		break;

	case NID_id_stc_build_valid_pkc_path:
		if ((status & CHECK_STATUS_INVALID) != 0)
			status = 1;
		else
			status = 0;
		break;

	case NID_id_stc_build_status_checked_pkc_path:
		if ((status & CHECK_STATUS_REVOKED) != 0)
			status = 1;
		else if ((status & CHECK_STATUS_UNKNOWN) != 0)
			status = 2;
		else if ((status & CHECK_STATUS_UNAVAIL) != 0)
			status = 3;
		else
			status = 0;
		break;

	default:
		log("build response: unknown check??", "");
		SCVP_REPLYCHECK_free(check);
		return NULL;
	}
	if (!ASN1_INTEGER_set(check->status, status)) {
		log("build response: can't set check status", "");
		SCVP_REPLYCHECK_free(check);
		return NULL;
	}
	return check;
}

SCVP_REPLYWANTBACK *
scvp_build_wantback(SCVP_CTX *gcp, int nid)
{
	SCVP_RESPONDER_CTX *ctx = &gcp->ctx;
	SCVP_REPLYWANTBACK *wantback = SCVP_REPLYWANTBACK_new();
	ASN1_OBJECT *obj;
	unsigned char *p, *buf = NULL;
	int len;

	if ((wantback == NULL) ||
	    (wantback->wb == NULL) ||
	    (wantback->value == NULL)) {
		log("build response: allocation failed (wantback)", "");
		return wantback;
	}
	obj = OBJ_nid2obj(nid);
	if (obj == NULL) {
		log("build response: can't get wantback OID", "");
		SCVP_REPLYWANTBACK_free(wantback);
		return NULL;
	}
	wantback->wb = obj;

#define ERRL	{ \
	log("build response: can't get wantback value (length)", ""); \
	SCVP_REPLYWANTBACK_free(wantback); \
	return NULL; \
	}

#define ERRM	{ \
	log("build response: can't get wantback value (alloc)", ""); \
	SCVP_REPLYWANTBACK_free(wantback); \
	return NULL; \
	}

#define ERRE	{ \
	log("build response: can't set wantback value", ""); \
	free(buf); \
	SCVP_REPLYWANTBACK_free(wantback); \
	return NULL; \
	}

	switch (nid) {
 	case NID_id_swb_pkc_cert_path:
		wantback->d.certpath = scvp_build_chain(gcp);
		if (wantback->d.certpath == NULL) {
			log("build response: can't build cert path", "");
			SCVP_REPLYWANTBACK_free(wantback);
			return NULL;
		}
		len = i2d_SCVP_CERTBUNDLE(wantback->d.certpath, NULL);
		if (len <= 0)
			ERRL
		buf = (unsigned char *) malloc(len);
		if (buf == NULL)
			ERRM
		p = buf;
		if (i2d_SCVP_CERTBUNDLE(wantback->d.certpath, &p) <= 0)
			ERRE
		break;

	case NID_id_swb_pkc_revocation_info:
		wantback->d.revstatus = scvp_build_revinfo(gcp);
		if (wantback->d.revstatus == NULL) {
			log("build response: can't build revinfo", "");
			SCVP_REPLYWANTBACK_free(wantback);
			return NULL;
		}
		len = i2d_SCVP_REVOCATIONINFOS(wantback->d.revstatus, NULL);
		if (len <= 0)
			ERRL
		buf = (unsigned char *) malloc(len);
		if (buf == NULL)
			ERRM
		p = buf;
		if (i2d_SCVP_REVOCATIONINFOS(wantback->d.revstatus, &p) <= 0)
			ERRE
		break;

	case NID_id_swb_pkc_cert_status:
		wantback->d.status = ctx->wb_status ? 0xff : 0;
		len = i2d_ASN1_BOOLEAN(wantback->d.status, NULL);
		if (len <= 0)
			ERRL
		buf = (unsigned char *) malloc(len);
		if (buf == NULL)
			ERRM
		p = buf;
		if (i2d_ASN1_BOOLEAN(wantback->d.status, &p) <= 0)
			ERRE
		break;

	case NID_id_swb_pkc_public_key_info:
		wantback->d.pkinfo = X509_get_X509_PUBKEY(ctx->cert);
		if (wantback->d.pkinfo == NULL) {
			log("build response: can't build key", "");
			SCVP_REPLYWANTBACK_free(wantback);
			return NULL;
		}
		len = i2d_X509_PUBKEY(wantback->d.pkinfo, NULL);
		if (len <= 0)
			ERRL
		buf = (unsigned char *) malloc(len);
		if (buf == NULL)
			ERRM
		p = buf;
		if (i2d_X509_PUBKEY(wantback->d.pkinfo, &p) <= 0)
			ERRE
		break;

	default:
		log("build response: unknown wantback??", "");
		SCVP_REPLYWANTBACK_free(wantback);
		return NULL;
	}
#undef ERRL
#undef ERRM
#undef ERRE

	if (!ASN1_OCTET_STRING_set(wantback->value, buf, len)) {
		log("build response: can't set wantback value", "");
		free(buf);
		SCVP_REPLYWANTBACK_free(wantback);
		return NULL;
	}
	if (buf)
		free(buf);
	return wantback;
}

SCVP_CERTBUNDLE *
scvp_build_chain(SCVP_CTX *gcp)
{
	SCVP_RESPONDER_CTX *ctx = &gcp->ctx;
	X509_STORE_CTX *csc = &gcp->csc;
	SCVP_CERTBUNDLE *cb = SCVP_CERTBUNDLE_new();
	SCVP_PKCREF *pkc = NULL;
	STACK_OF(X509) *chain = X509_STORE_CTX_get_chain(csc);
	X509 *cert = NULL;
	int i;

	if ((cb == NULL) || (cb->bundle == NULL)) {
		log("build response: can't allocate cert path", "");
		ctx->response_status = SCVP_STATUS_CODE_INTERNALERROR;
		return cb;
	}
	if (chain == NULL) {
		log("build response: empty cert path", "");
		return cb;
	}

	for (i = 0; i < sk_X509_num(chain); i++) {
		pkc = SCVP_PKCREF_new();
		if (pkc == NULL) {
			log("build response: can't allocate pkc %d", i);
			ctx->response_status = SCVP_STATUS_CODE_INTERNALERROR;
			return cb;
		}
		cert = sk_X509_value(chain, i);
		if (cert == NULL) {
			log("build response: empty cert %d", i);
			SCVP_PKCREF_free(pkc);
			continue;
		}
		cert = X509_dup(cert);
		if (cert == NULL) {
			log("build response: can't copy cert %d", i);
			ctx->response_status = SCVP_STATUS_CODE_INTERNALERROR;
			SCVP_PKCREF_free(pkc);
			return cb;
		}
		pkc->type = V_SCVP_PKCREF_CERT;
		pkc->value.cert = cert;
		if (sk_SCVP_PKCREF_push(cb->bundle, pkc) <= 0) {
			log("build response: can't push pkc %d", i);
			ctx->response_status = SCVP_STATUS_CODE_INTERNALERROR;
			SCVP_PKCREF_free(pkc);
			return cb;
		}
	}
	return cb;
}

SCVP_REVOCATIONINFOS *
scvp_build_revinfo(SCVP_CTX *gcp)
{
	SCVP_RESPONDER_CTX *ctx = &gcp->ctx;
	X509_STORE_CTX *csc = &gcp->csc;
	SCVP_REVOCATIONINFOS *rs = SCVP_REVOCATIONINFOS_new();
	SCVP_REVOCATIONINFO *ri;
	X509_OBJECT xobj;

	if ((rs == NULL) || (rs->revinfo == NULL)) {
		log("build response: can't allocate revinfo", "");
		ctx->response_status = SCVP_STATUS_CODE_INTERNALERROR;
		return rs;
	}
	if (!X509_STORE_get_by_subject(csc,
				       X509_LU_CRL,
				       X509_get_issuer_name(ctx->cert),
				       &xobj)) {
		log("build response: empty revinfo", "");
		return rs;
	}
	if (xobj.data.crl == NULL) {
		log("build response: can't get crl??", "");
		ctx->response_status = SCVP_STATUS_CODE_INTERNALERROR;
		return rs;
	}
	ri = SCVP_REVOCATIONINFO_new();
	if (ri == NULL) {
		log("build response: can't get revinfo", "");
		ctx->response_status = SCVP_STATUS_CODE_INTERNALERROR;
		return rs;
	}
	ri->type = V_SCVP_REVOCATIONINFO_CRL;
	ri->value.crl = X509_CRL_dup(xobj.data.crl);
	if (ri->value.crl == NULL) {
		log("build response: can't copy crl", "");
		ctx->response_status = SCVP_STATUS_CODE_INTERNALERROR;
		return rs;
	}
	if (sk_SCVP_REVOCATIONINFO_push(rs->revinfo, ri) <= 0) {
		log("build response: can't set revinfo", "");
		ctx->response_status = SCVP_STATUS_CODE_INTERNALERROR;
		return rs;
	}
	return rs;
}

int
scvp_build_response(SCVP_CTX *gcp)
{
	SCVP_RESPONDER_CTX *ctx = &gcp->ctx;
	SCVP_RESPONSE *resp = ctx->CVResponse;
	SCVP_HASHVALUE *hv;
	SCVP_CERTREPLY *reply;
	ASN1_OBJECT *obj;
	EVP_MD_CTX mdctx;
	unsigned char md_value[EVP_MAX_MD_SIZE];
	char *hostname;
	int i, md_len;

#define ERR(o, fatal, msg, arg)		{ \
		ctx->response_status = SCVP_STATUS_CODE_INTERNALERROR; \
		log(msg, arg); \
		if (o) { \
			unsigned long l; \
			while((l = ERR_get_error()) != 0) \
				log("%s", ERR_error_string(l, NULL)); \
		} \
		if (fatal) return -1; \
		goto finish; \
		}

	ERR_clear_error();

	if ((resp->scvpVersion == NULL) ||
	    (resp->producedAt == NULL) ||
	    (resp->requestRef == NULL))
		ERR(0, 1, "build response: allocation failed (global)", "");

	/* scvpVersion */

	if (!ASN1_INTEGER_set(resp->scvpVersion, 1L))
		ERR(1, 1, "build response: can't set version", "");

	/* produceAt */

	if (!ASN1_GENERALIZEDTIME_set(resp->producedAt, time(NULL)))
		ERR(1, 1, "build response: can't set produce time", "");

	/* requestRef */

	resp->requestRef->type = V_SCVP_REQUEST_REFERENCE_REQUESTHASH;
	hv = SCVP_HASHVALUE_new();
	if ((hv == NULL) ||
	    (hv->algorithm == NULL) ||
	    (hv->value == NULL))
		ERR(1, 0,
		    "build response: allocation failed (requestRef)", "");
	obj = OBJ_nid2obj(NID_sha1);
	if (obj == NULL)
		ERR(1, 0, "build response: can't get %s OID", "sha-1");
	hv->algorithm->algorithm = obj;
	EVP_MD_CTX_init(&mdctx);
	EVP_DigestInit_ex(&mdctx, EVP_sha1(), NULL);
	EVP_DigestUpdate(&mdctx, ctx->rbuf, ctx->rlen);
	EVP_DigestFinal_ex(&mdctx, md_value, &md_len);
	EVP_MD_CTX_cleanup(&mdctx);
	if (!ASN1_OCTET_STRING_set(hv->value, md_value, md_len))
		ERR(1, 0, "build response: can't set hash", "");
	resp->requestRef->value.requestHash = hv;

	/* responder */

	resp->responder = ASN1_OCTET_STRING_new();
	if (resp->responder == NULL)
		ERR(1, 0, "build response: allocation failed (responder)", "");
	hostname = malloc(MAXHOSTNAMELEN + 1);
	if (hostname == NULL)
		ERR(0, 0, "build response: allocation failed (hostname)", "");
	if (gethostname(hostname, MAXHOSTNAMELEN) < 0)
		ERR(0, 0, "build response: gethostname: %s", strerror(errno));
	if (!ASN1_OCTET_STRING_set(resp->responder,
				   hostname,
				   strlen(hostname)))
		ERR(1, 0, "build response: can't set responder","");

	/* replyObjects */

	if (ctx->response_status > 0)
		goto finish;
	resp->replyObjects = sk_SCVP_CERTREPLY_new_null();
	reply = SCVP_CERTREPLY_new();
	if ((resp->replyObjects == NULL) ||
	    (reply == NULL) ||
	    (reply->cert == NULL) ||
	    (reply->replyStatus == NULL) ||
	    (reply->replyValTime == NULL) ||
	    (reply->replyChecks == NULL) ||
	    (reply->replyWantBacks == NULL) ||
	    (reply->valPolicy == NULL) ||
	    (sk_SCVP_CERTREPLY_push(resp->replyObjects, reply) <= 0))
		ERR(1, 0, "build response: allocation failed (reply)", "");

	/* reply -> cert */
	/* TODO: deal with pointers too */

	SCVP_CERTREF_free(reply->cert);
	reply->cert = SCVP_CERTREF_dup(ctx->certRef);
	if (reply->cert == NULL)
		ERR(1, 0, "build response: can't set certRef", "");

	/* reply -> replyStatus */

	if (!ASN1_ENUMERATED_set(reply->replyStatus, ctx->reply_status))
		ERR(1, 0, "build response: can't set reply status", "");

	/* reply -> replyValTime */

	if (!ASN1_GENERALIZEDTIME_set(reply->replyValTime, time(NULL)))
		ERR(1, 0, "build response: can't set reply time", "");

	/* reply -> replyChecks */

	for (i = 0; i < NBRET; i++) {
		SCVP_REPLYCHECK *check;
		int nid;

		nid = ctx->checks[i];
		if (nid == 0)
			continue;
		check = scvp_build_check(ctx, nid);
		if (check == NULL)
			ERR(1, 0, "build reponse: build check %d", i);
		if (sk_SCVP_REPLYCHECK_push(reply->replyChecks, check) <= 0)
			ERR(1, 0,
			    "build response: push failed (check %d)", i);
	}

	/* reply -> replyWantBacks */

	for (i = 0; i < NBRET; i++) {
		SCVP_REPLYWANTBACK *wantback;
		int nid;

		nid = ctx->wantbacks[i];
		if (nid == 0)
			continue;
		wantback = scvp_build_wantback(gcp, nid);
		if (wantback == NULL)
			ERR(1, 0, "build reponse: build wantback %d", i);
		if (sk_SCVP_REPLYWANTBACK_push(reply->replyWantBacks,
					       wantback) <= 0)
			ERR(1, 0,
			    "build response: push failed (wantback %d)", i);
	}

	/* reply -> valPolicy */

	obj = OBJ_nid2obj(NID_id_svp_defaultValPolicy);
	if (obj == NULL)
		ERR(1, 0, "build response: can't get policy OID", "");
	reply->valPolicy->valPolicyId = obj;

	/* responseStatus (must be last) */

   finish:
	if ((resp->responseStatus == NULL) ||
	    (resp->responseStatus->statusCode == NULL))
		ERR(0, 1, "build response: allocation failed (global)", "");
	(void) ASN1_ENUMERATED_set(resp->responseStatus->statusCode,
				   ctx->response_status);
#undef ERR

	return 0;
}

#ifdef dnssec_trust
#include "getrrcertbyname.h"

int
trust_dnssec(X509_TRUST *trust, X509 *x, int flags)
{
	GENERAL_NAMES *gens;
	GENERAL_NAME *gen = NULL;
	struct certlist *curr, *certlist = NULL;
	unsigned char *p, *buf = NULL;
	char *fqdn = NULL;
	int i, ret, len = 0;

	ret = X509_check_trust(x, trust->arg1, flags);
	if (ret != X509_TRUST_TRUSTED) {
		log("trust_dnssec: previous trust %d failed", trust->arg1);
		return ret;
	}
	ret = X509_TRUST_UNTRUSTED;
	
	gens = X509_get_ext_d2i(x, NID_subject_alt_name, NULL, NULL);
	if (gens == NULL) {
		log("trust_dnssec: no extension: %s",
		    ERR_error_string(ERR_get_error(), NULL));
		goto end;
	}
	for (i = 0; i < sk_GENERAL_NAME_num(gens); i++) {
		gen = sk_GENERAL_NAME_value(gens, i);
		if (gen == NULL)
			continue;
		if (gen->type == GEN_DNS)
			break;
	}
	if ((gen == NULL) || (gen->type != GEN_DNS)) {
		log("trust_dnssec: no DNS Subject Alternate Name", "");
		goto end;
	}
	i = gen->d.dNSName->length + 1;
	fqdn = (char *) malloc(i);
	if (fqdn == NULL) {
		log("trust_dnssec: can't allocate FQDN", "");
		goto end;
	}
	bzero(fqdn, i);
#ifndef linux
	strlcpy(fqdn, gen->d.dNSName->data, i);
#else
	(void)strncpy(fqdn, gen->d.dNSName->data, gen->d.dNSName->length);
#endif
	/* debug */
	log("trust_dnssec: FQDN=%s", fqdn);

	if (getrrcertbyname(fqdn, &certlist) != 1) {
		log("trust_dnssec: getrrcertbyname failed: %s",
		    hstrerror(h_errno));
		goto end;
	}

	for (curr = certlist; curr != NULL; curr = curr->next) {
		if (curr->type != DNSSEC_TYPE_PKIX)
			continue;
#ifdef notdef
		if ((curr->keytag != 0) || (curr->algorithm != 0))
			continue;
#endif
		if (len == 0)
			len = i2d_X509(x, NULL);
		if (len <= 0) {
			log("trust_dnssec: encoding failed (get length): %s",
			    ERR_error_string(ERR_get_error(), NULL));
			goto end;
		}
		if (len != curr->certlen)
			continue;
		if (buf == NULL)
			buf = (unsigned char *) malloc(len);
		if (buf == NULL) {
			log("trust_dnssec: can't allocate DER buffer", "");
			goto end;
		}
		p = buf;
		if (i2d_X509(x, &p) <= 0) {
			log("trust_dnssec: encoding failed (real)", "");
			goto end;
		}
		/* brute force: binary comparison */
		if (bcmp(buf, curr->cert, len) == 0) {
			if (curr->status)
				ret = X509_TRUST_TRUSTED;
			break;
		}
	}

    end:
	if (buf != NULL)
		free(buf);
	if (certlist != NULL)
		free_certlist(certlist);
	if (fqdn != NULL)
		free(fqdn);
	return ret;
}
#endif

#ifdef ldap_lookup
/* From x509_vfy.c */

int get_issuer(X509 **issuer, X509_STORE_CTX *ctx, X509 *x)
{
	X509_NAME *xn;
	X509_OBJECT obj, *pobj;
	int i, ok, idx;
	xn=X509_get_issuer_name(x);
	ok=get_by_subjects(ctx,X509_LU_X509,xn,x,&obj);
	if (ok != X509_LU_X509)
		{
		if (ok == X509_LU_RETRY)
			{
			X509_OBJECT_free_contents(&obj);
			X509err(X509_F_X509_VERIFY_CERT,X509_R_SHOULD_RETRY);
			return -1;
			}
		else if (ok != X509_LU_FAIL)
			{
			X509_OBJECT_free_contents(&obj);
			/* not good :-(, break anyway */
			return -1;
			}
		return 0;
		}
	/* If certificate matches all OK */
	if (ctx->check_issued(ctx, x, obj.data.x509))
		{
		*issuer = obj.data.x509;
		return 1;
		}
	X509_OBJECT_free_contents(&obj);
	/* Else find index of first matching cert */
	idx = X509_OBJECT_idx_by_subject(ctx->ctx->objs, X509_LU_X509, xn);
	/* This shouldn't normally happen since we already have one match */
	if (idx == -1) return 0;

	/* Look through all matching certificates for a suitable issuer */
	for (i = idx; i < sk_X509_OBJECT_num(ctx->ctx->objs); i++)
		{
		pobj = sk_X509_OBJECT_value(ctx->ctx->objs, i);
		/* See if we've ran out of matches */
		if (pobj->type != X509_LU_X509) return 0;
		if (X509_NAME_cmp(xn, X509_get_subject_name(pobj->data.x509))) return 0;
		if (ctx->check_issued(ctx, x, pobj->data.x509))
			{
			*issuer = pobj->data.x509;
			X509_OBJECT_up_ref_count(pobj);
			return 1;
			}
		}
	return 0;
}

int
get_crl(X509_STORE_CTX *ctx, X509_CRL **crl, X509 *x)
{
	int ok;
	X509_OBJECT xobj;
	ok = get_by_subjects(ctx, X509_LU_CRL, NULL, x, &xobj);
	if (!ok) return 0;
	*crl = xobj.data.crl;
	return 1;
}

/* From x509_lu.c */

int
get_by_subjects(X509_STORE_CTX *vs, int type, X509_NAME *name,
	X509 *x, X509_OBJECT *ret)
{
	X509_STORE *ctx=vs->ctx;
	X509_LOOKUP *lu;
	X509_NAME *nm = name != NULL ? name : X509_get_issuer_name(x);
	X509_OBJECT stmp,*tmp;
	int i,j,len;

	tmp=X509_OBJECT_retrieve_by_subject(ctx->objs,type,nm);

	if (tmp == NULL)
		{
		char *uri = get_uri(x, type, &len);

		for (i=vs->current_method; i<sk_X509_LOOKUP_num(ctx->get_cert_methods); i++)
			{
			lu=sk_X509_LOOKUP_value(ctx->get_cert_methods,i);
			if (uri != NULL)
				X509_LOOKUP_by_alias(lu,type,uri,len,&stmp);
			j=X509_LOOKUP_by_subject(lu,type,nm,&stmp);
			if (j < 0)
				{
				vs->current_method=j;
				return j;
				}
			else if (j)
				{
				tmp= &stmp;
				break;
				}
			}
		vs->current_method=0;
		if (tmp == NULL)
			return 0;
		}

	ret->type=tmp->type;
	ret->data.ptr=tmp->data.ptr;

	X509_OBJECT_up_ref_count(ret);

	return 1;
}

/* Get URI from the issuerAltName or the crlDistributionPoints */

char *
get_uri(X509 *x, int type, int *len)
{
	CRL_DIST_POINTS *crld;
	DIST_POINT *point;
	GENERAL_NAMES *gens;
	GENERAL_NAME *gen = NULL;
	int i;

	switch (type) {
	case X509_LU_X509:
		gens = X509_get_ext_d2i(x, NID_issuer_alt_name, NULL, NULL);
		break;

	case X509_LU_CRL:
		crld = X509_get_ext_d2i(x, NID_crl_distribution_points,
					NULL, NULL);
		if ((crld == NULL) || (sk_DIST_POINT_num(crld) <= 0))
			return NULL;
		/* Only support one distribution point */
		point = sk_DIST_POINT_value(crld, 0);
		if (point->distpoint->type != 0)
			return NULL;
		gens = point->distpoint->name.fullname;
		break;

	default:
		return NULL;
	}

	if (gens == NULL) {
		log("get_uri: no extension: %s",
		    ERR_error_string(ERR_get_error(), NULL));
		return NULL;
	}
		
	for (i = 0; i < sk_GENERAL_NAME_num(gens); i++) {
		gen = sk_GENERAL_NAME_value(gens, i);
		if (gen == NULL)
			continue;
		if (gen->type == GEN_URI)
			break;
	}
	if ((gen == NULL) || (gen->type != GEN_URI)) {
		log("get_uri: no URI Issuer Alternate Name", "");
		return NULL;
	}
	*len = gen->d.uniformResourceIdentifier->length;
	return gen->d.uniformResourceIdentifier->data;
}
#endif
