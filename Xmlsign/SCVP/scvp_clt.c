/* scvp_clt.c */
/* Written by Yann Busnel <Yann.Busnel@enst-bretagne.fr> */
/* for the RSM group of projects - July 2003 */
/* ================================================================ */

#include <sys/param.h>
#include <err.h>
#include <fcntl.h>
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

#define NONCE_SIZE	4

typedef struct MemoryStruct_st {
	char *memory;
	size_t size;
} MemoryStruct;

int scvp_cert_verify(X509 *cert, char *url);
int scvp_build_request(SCVP_REQUEST *req, X509 *cert);
int scvp_check_response(SCVP_RESPONSE *resp, SCVP_REQUEST *req, X509 *cert,
			unsigned char *sbuf, int len);
int scvp_cmp_request(SCVP_REQUEST *req, unsigned char *sbuf, int slen);
size_t WriteMemory_cb(void *ptr, size_t size, size_t nmemb, void *data);
char ebuf[CURL_ERROR_SIZE];

int
scvp_cert_verify(X509 *cert, char *url)
{
	SCVP_REQUEST *CVRequest = NULL;
	SCVP_RESPONSE *CVResponse = NULL;
	CURL *curl = NULL;
	MemoryStruct *chunk = NULL;
	unsigned char *p, *sbuf = NULL;
	struct curl_slist *hlist = NULL;
	long httpcode;
	char *ct;
	int len, cr;

	CVRequest = SCVP_REQUEST_new();
	if (CVRequest == NULL)
		errx(1, "can't allocate request: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	if (scvp_build_request(CVRequest, cert) != 0)
		errx(1, "can't build request");
	len = i2d_SCVP_REQUEST(CVRequest, NULL);
	if (len <= 0)
		errx(1, "request encoding failed (get length): %s",
		     ERR_error_string(ERR_get_error(), NULL));
	sbuf = (unsigned char *) malloc(len + 1);
	if (sbuf == NULL)
		errx(1, "send buffer allocation failed: %s", strerror(errno));
	bzero(sbuf, len + 1);
	p = sbuf;
	if (i2d_SCVP_REQUEST(CVRequest, &p) <= 0)
		errx(1, "request encoding failed (real encoding): %s",
		     ERR_error_string(ERR_get_error(), NULL));
	chunk = (MemoryStruct *) malloc(sizeof(MemoryStruct));
	if (chunk == NULL)
		errx(1, "can't allocate receive memory: %s", strerror(errno));
	bzero(chunk, sizeof(MemoryStruct));

	/* debug */
	{
		int fd = open("req", O_WRONLY|O_CREAT|O_TRUNC, 0644);

		(void) write(fd, (char *) sbuf, len);
		(void) close(fd);
	}

	curl = curl_easy_init();
	if (curl == NULL)
		errx(1, "curl init failed");
	if (curl_easy_setopt(curl, CURLOPT_URL, url) != CURLE_OK)
		errx(1, "curl setopt failed (URL)");
	if (curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
			     (char *) sbuf) != CURLE_OK)
		errx(1, "curl setopt failed (POST)");
	if (curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, len) != CURLE_OK)
		errx(1, "curl setopt failed (SIZE)");
	hlist = curl_slist_append(hlist,
				  "Content-Type: application/scvp-request");
	if (hlist == NULL)
		errx(1, "curl header append failed (CT)");
	hlist = curl_slist_append(hlist,
				  "Accept: application/scvp-response");
	if (hlist == NULL)
		errx(1, "curl header append failed (A)");
	if (curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hlist) != CURLE_OK)
		errx(1, "curl setopt failed (HEADER)");
	if (curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
			     &WriteMemory_cb) != CURLE_OK)
		errx(1, "curl setopt failed (WRITECB)");
	if (curl_easy_setopt(curl, CURLOPT_FILE, (void *) chunk) != CURLE_OK)
		errx(1, "curl setopt failed (WRITE)");
	if (curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, ebuf) != CURLE_OK)
		errx(1, "curl setopt failed (ERROR)");
	if (curl_easy_perform(curl) != CURLE_OK)
		errx(1, "curl perform failed: %s", ebuf);
	httpcode = 0;
	if (curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &httpcode) != CURLE_OK)
		errx(1, "curl getinfo failed (HTTPCODE)");
	if (httpcode != 200L)
		errx(1, "HTTP error (status = %ld)", httpcode);
	ct = NULL;
	if (curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct) != CURLE_OK)
		errx(1, "curl getinfo failed (CONTENTTYPE)");
	if (ct == NULL)
		warnx("can't get Content-Type");
	else if (strcmp(ct, "application/scvp-response") != 0)
		errx(1, "bad Content-Type %s", ct);

	ERR_clear_error();
	p = (unsigned char *) chunk->memory;
	CVResponse = d2i_SCVP_RESPONSE(NULL, &p, chunk->size);
	if (CVResponse == NULL)
		errx(1, "response decoding failed: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	cr = scvp_check_response(CVResponse, CVRequest, cert, sbuf, len);

	if (CVRequest)
		SCVP_REQUEST_free(CVRequest);
	if (CVResponse)
		SCVP_RESPONSE_free(CVResponse);
	if (sbuf)
		free(sbuf);
	if (curl)
		curl_global_cleanup();
	if (hlist)
		curl_slist_free_all(hlist);
	if (chunk && chunk->memory)
		free(chunk->memory);
	if (chunk)
		free(chunk);
	ERR_clear_error();

	return cr;
}

int
scvp_build_request(SCVP_REQUEST *req, X509 *cert)
{
	SCVP_CERTREF *certRef;
	ASN1_OBJECT *obj;
	SCVP_PKCREF *pkc;
	char *hostname;
	unsigned char nonce[NONCE_SIZE];

	if ((req->scvpVersion == NULL) ||
	    (req->query == NULL))
		errx(1, "build request: allocation failed (global)");
	if (!ASN1_INTEGER_set(req->scvpVersion, 1L))
		errx(1, "build request: can't set version: %s",
		     ERR_error_string(ERR_get_error(), NULL));

	/* Query */

	/* Query -> queryCerts */
	pkc = SCVP_PKCREF_new();
	certRef = SCVP_CERTREF_new();
	if ((req->query->queriedCerts == NULL) ||
	    (req->query->checks == NULL) ||
	    (req->query->wantBack == NULL) ||
	    (req->query->valPolicy == NULL) ||
	    (pkc == NULL) ||
	    (certRef == NULL))
		errx(1, "build request: allocation failed (query): %s",
		     ERR_error_string(ERR_get_error(), NULL));
	pkc->type = V_SCVP_PKCREF_CERT;
	pkc->value.cert = X509_dup(cert);
	if (pkc->value.cert == NULL)
		errx(1, "build request: allocation failed (cert): %s",
		     ERR_error_string(ERR_get_error(), NULL));
	certRef->type = V_SCVP_CERTREF_PKC;
	certRef->value.pkc = pkc;
	if (sk_SCVP_CERTREF_push(req->query->queriedCerts, certRef) <= 0)
		errx(1, "build request: allocation failed (certRef): %s",
		     ERR_error_string(ERR_get_error(), NULL));

	/* Query -> Checks */
	obj = OBJ_nid2obj(NID_id_stc_build_status_checked_pkc_path);
	if (obj == NULL)
		errx(1, "build request: can't get check OID: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	if (sk_ASN1_OBJECT_push(req->query->checks, obj) <= 0)
		errx(1, "build request: allocation failed (check): %s",
		     ERR_error_string(ERR_get_error(), NULL));

        /* Query -> WantBacks */
	obj = OBJ_nid2obj(NID_id_swb_pkc_cert_status);
	if (obj == NULL)
		errx(1, "build request: can't get wantback OID: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	if (sk_ASN1_OBJECT_push(req->query->wantBack, obj) <= 0)
		errx(1, "build request: allocation failed (wantback): %s",
		     ERR_error_string(ERR_get_error(), NULL));

	/* Query -> ValPolicy */
	obj = OBJ_nid2obj(NID_id_svp_defaultValPolicy);
	if (obj == NULL)
		errx(1, "build request: can't get policy OID: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	req->query->valPolicy->valPolicyId = obj;

	/* Requestor */
	req->requestor = ASN1_OCTET_STRING_new();
	if (req->requestor == NULL)
		errx(1, "build request: allocation failed (requestor): %s",
		     ERR_error_string(ERR_get_error(), NULL));
	hostname = malloc(MAXHOSTNAMELEN + 1);
	if (hostname == NULL)
		errx(1, "build request: allocation failed (hostname)");
	bzero(hostname, MAXHOSTNAMELEN + 1);
	if (gethostname(hostname, MAXHOSTNAMELEN) < 0)
		errx(1, "build request: gethostname: %s", strerror(errno));
	if (!ASN1_OCTET_STRING_set(req->requestor,
				   hostname,
				   strlen(hostname)))
		errx(1, "build request: can't set requestor: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	
	/* RequestNonce */
	req->requestNonce = ASN1_OCTET_STRING_new();
	if (req->requestNonce == NULL)
		errx(1, "build request: allocation failed (requestNonce): %s",
		     ERR_error_string(ERR_get_error(), NULL));
	if (RAND_pseudo_bytes(nonce, NONCE_SIZE) <= 0)
		errx(1, "build request: can't get nonce: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	if (!ASN1_OCTET_STRING_set(req->requestNonce, nonce, NONCE_SIZE))
		errx(1, "build request: can't set nonce: %s",
		     ERR_error_string(ERR_get_error(), NULL));

	/* ReqExtensions */

	return 0;
}

int
scvp_check_response(SCVP_RESPONSE *resp, SCVP_REQUEST *req, X509 *cert,
		    unsigned char *sbuf, int slen)
{
	SCVP_CERTREPLY *crep;
	SCVP_HASHVALUE *hv;
	ASN1_OCTET_STRING *ostr;
	EVP_MD_CTX mdctx;
	unsigned char md_value[EVP_MAX_MD_SIZE];
	long nid, status;
	int md_len, i;

	/* scvpVersion */
	if ((resp->scvpVersion == NULL) ||
	    ASN1_INTEGER_cmp(resp->scvpVersion, req->scvpVersion))
		errx(1, "check response: bad version");

	/* producedAt */

	/* responseStatus */
	if ((resp->responseStatus == NULL) ||
	    (resp->responseStatus->statusCode == NULL))
		errx(1, "check response: bad status");
	status = ASN1_ENUMERATED_get(resp->responseStatus->statusCode);
	if (status != SCVP_STATUS_CODE_OKAY) {
		warnx("check response: status = %ld", status);
		return (int) -status * 1000000;
	}

	/* requestRef */
	if (resp->requestRef == NULL)
		errx(1, "check response: bad requestRef");
	switch (resp->requestRef->type) {
	case V_SCVP_REQUEST_REFERENCE_REQUESTHASH:
		hv = resp->requestRef->value.requestHash;
		if ((hv == NULL) ||
		    (hv->algorithm == NULL) ||
		    (hv->algorithm->algorithm == NULL) ||
		    (hv->value == NULL))
			errx(1, "check response: no hash in requestRef");
		nid = OBJ_obj2nid(hv->algorithm->algorithm);
		if (nid != NID_sha1)
			errx(1, "check response: not a sha-1 hash");
		ostr = hv->value;
		EVP_MD_CTX_init(&mdctx);
		EVP_DigestInit_ex(&mdctx, EVP_sha1(), NULL);
		EVP_DigestUpdate(&mdctx, sbuf, slen);
		EVP_DigestFinal_ex(&mdctx, md_value, &md_len);
		EVP_MD_CTX_cleanup(&mdctx);
		if ((md_len != ostr->length) ||
		    bcmp(md_value, ostr->data, md_len)) {
			warnx("check response: hash mismatch");
			return -1;
		}
		break;

	case V_SCVP_REQUEST_REFERENCE_FULLREQUEST:
		if (resp->requestRef->value.fullRequest == NULL)
			errx(1, "check response: void requestRef");
		if (scvp_cmp_request(resp->requestRef->value.fullRequest,
				     sbuf, slen)) {
			warnx("check response: requestRef mismatch");
			return -1;
		}
		break;

	default:
		errx(1, "check response: unknown requestRef");
	}

	/* requestor */
	if (resp->requestor == NULL)
		errx(1, "check response: no requestor");
	if (ASN1_OCTET_STRING_cmp(resp->requestor, req->requestor))
		errx(1, "check response: requestor mismatch");

	/* responder */

	/* requestNonce */
	if (resp->requestNonce == NULL)
		errx(1, "check response: no requestNonce");
	if (ASN1_OCTET_STRING_cmp(resp->requestNonce, req->requestNonce))
		errx(1, "check response: requestNonce mismatch");

	/* replyObjects */
	if ((resp->replyObjects == NULL) ||
	    (sk_SCVP_CERTREPLY_num(resp->replyObjects) != 1))
		errx(1, "check response: bad replyObjects");
	crep = sk_SCVP_CERTREPLY_value(resp->replyObjects, 0);
	if (crep == NULL)
		errx(1, "check response: bad CertReply");

	/* CertReply -> cert */
	if ((crep->cert == NULL) ||
	    (crep->cert->type != V_SCVP_CERTREF_PKC) ||
	    (crep->cert->value.pkc == NULL) ||
	    (crep->cert->value.pkc->type != V_SCVP_PKCREF_CERT) ||
	    (crep->cert->value.pkc->value.cert == NULL) ||
	    X509_cmp(crep->cert->value.pkc->value.cert, cert))
		errx(1, "check reply: bad cert");

	/* CertReply -> replyStatus */
	if (crep->replyStatus == NULL)
		errx(1, "check reply: bad status");
	status = ASN1_ENUMERATED_get(crep->replyStatus);
	if (status != SCVP_REPLY_STATUS_SUCCESS) {
		warnx("check reply: status = %ld", status);
		return (int) -status * 1000;
	}

	/* CertReply -> replyValTime */
	if (crep->replyValTime == NULL)
		errx(1, "check reply: bad valtime");
	/* should do more checks */

	/* CertReply -> replyChecks */
	if (crep->replyChecks == NULL)
		errx(1, "check reply: no checks");
	for (i = 0; i < sk_SCVP_REPLYCHECK_num(crep->replyChecks); i++) {
		SCVP_REPLYCHECK *rcheck;

		rcheck = sk_SCVP_REPLYCHECK_value(crep->replyChecks, i);
		if ((rcheck == NULL) ||
		    (rcheck->check == NULL) ||
		    (rcheck->status == NULL)) {
			warnx("check reply: empty check %d", i);
			continue;
		}
		nid = OBJ_obj2nid(rcheck->check);
		if (nid != NID_id_stc_build_status_checked_pkc_path)
			warnx("check reply: bad check OID");
		status = ASN1_INTEGER_get(rcheck->status);
		if (status != 0L) {
			warnx("check reply: bad status %ld in check %d",
			      status, i);
			return (int) -status * 10;
		}
	}

	/* CertReply -> replyWantBacks */
	if (crep->replyWantBacks == NULL)
		errx(1, "check reply: bad wantbacks");
	for (i = 0; i < sk_SCVP_REPLYWANTBACK_num(crep->replyWantBacks); i++) {
		SCVP_REPLYWANTBACK *rwback;
		unsigned char *p;

		rwback = sk_SCVP_REPLYWANTBACK_value(crep->replyWantBacks, i);
		if ((rwback == NULL) ||
		    (rwback->wb == NULL) ||
		    (rwback->value == NULL)) {
			warnx("check reply: empty wantback %d", i);
			continue;
		}
		nid = OBJ_obj2nid(rwback->wb);
		if (nid != NID_id_swb_pkc_cert_status) {
			warnx("check reply: bad wantback OID");
			continue;
		}
		p = rwback->value->data;
		rwback->d.status =
			d2i_ASN1_BOOLEAN(NULL, &p, rwback->value->length);
		if (rwback->d.status < 0)
			errx(1, "check reply: can't get wantback value");
		if (rwback->d.status == 0) {
			warnx("check reply: wantback said cert is not valid");
			return -1;
		}
	}

	/* CertReply -> valPolicy */
	if ((crep->valPolicy == NULL) ||
	    (crep->valPolicy->valPolicyId == NULL))
		errx(1, "check reply: bad valPolicy");
	nid = OBJ_obj2nid(crep->valPolicy->valPolicyId);
	if (nid != NID_id_svp_defaultValPolicy)
		warnx("check response: bad policy OID");

	/* serverContextInfo */

	/* respExtensions */

	return 0;
}

int
scvp_cmp_request(SCVP_REQUEST *req, unsigned char *sbuf, int slen)
{
	unsigned char *buf, *p;
	int len, ret;

	len = i2d_SCVP_REQUEST(req, NULL);
	if (len <= 0) {
		warnx("cmp request: %s",
		      ERR_error_string(ERR_get_error(), NULL));
		return -1;
	}
	if (len != slen)
		return len - slen;
	buf = (unsigned char *) malloc(len + 1);
	if (buf == NULL)
		return -1;
	p = buf;
	if (i2d_SCVP_REQUEST(req, &p) <= 0) {
		warnx("cmp request: %s",
		      ERR_error_string(ERR_get_error(), NULL));
		free(buf);
		return -1;
	}
	ret = bcmp(buf, sbuf, len);
	free(buf);
	return ret;
}

size_t
WriteMemory_cb(void *ptr, size_t size, size_t nmemb, void *data)
{
	register int realsize = size * nmemb;
	MemoryStruct *mem = (MemoryStruct *) data;
	
	mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		bcopy(ptr, &(mem->memory[mem->size]), realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	} else
		errx(1, "realloc failed: %s", strerror(errno));
	return realsize;
}

int
main(int argc, char *argv[])
{
	BIO *in = NULL;
	X509 *cert = NULL;
	int cr;

	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();

	if (argc != 3)
		errx(1, "usage: %s certfile URL", argv[0]);
	in = BIO_new_file(argv[1], "r");
	if (in == NULL)
		errx(1, "can't open %s: %s", argv[1], strerror(errno));
	cert = d2i_X509_bio(in, NULL);
	if (cert == NULL)
		errx(1, "can't decode cert: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	cr = scvp_cert_verify(cert, argv[2]);
	printf("cr = %d\n", cr);

	if (in)
		BIO_free_all(in);
	if (cert)
		X509_free(cert);
	EVP_cleanup();
	ERR_free_strings();
	exit(0);
}
