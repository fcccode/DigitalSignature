/* LDAP lookup */

#include <stdio.h>
#include <errno.h>

#include <ldap.h>
#include <lber.h>

#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>

X509_LOOKUP_METHOD *X509_LOOKUP_ldap(void);
int get_by_subject(X509_LOOKUP *ctx, int type, X509_NAME *xn,
		   X509_OBJECT *ret);
int get_by_url(X509_LOOKUP *ctx, int type, char *url,
	       int length, X509_OBJECT *ret);
void add_vals(X509_LOOKUP *ctx, int type, struct berval **vals);

X509_LOOKUP_METHOD x509_ldap_lookup =
{
	"LDAP lookup using issuerAltName URI",
	NULL,		/* new */
	NULL,		/* free */
	NULL, 		/* init */
	NULL,		/* shutdown */
	NULL,		/* ctrl */
	get_by_subject,	/* get_by_subject */
	NULL,		/* get_by_issuer_serial */
	NULL,		/* get_by_fingerprint */
	get_by_url,	/* get_by_alias */
};

X509_LOOKUP_METHOD *X509_LOOKUP_ldap(void)
{
	return &x509_ldap_lookup;
}

int
get_by_subject(X509_LOOKUP *ctx, int type, X509_NAME *xn, X509_OBJECT *ret)
{
	X509_OBJECT *tmp;

	tmp = X509_OBJECT_retrieve_by_subject(ctx->store_ctx->objs, type, xn);
	if (tmp == NULL)
		return 0;
	ret->type = tmp->type;
	ret->data.ptr = tmp->data.ptr;
	return 1;
}

/*char *x509_attrs[2] = { "userCertificate", NULL };*/
char *x509_attrs[2] = { "cACertificate;binary", NULL };
char *crl_attrs[2] = { "certificateRevocationList;binary", NULL };

int
get_by_url(X509_LOOKUP *ctx, int type, char *url,
	       int length, X509_OBJECT *ret)
{
	LDAPURLDesc *lud = NULL;
	LDAP *ld = NULL;
	LDAPMessage *entry, *result = NULL;
	BerElement *ber = NULL;
	struct berval **vals = NULL;
	char *attr, **attrs;
	int rc, i;

	url[length] = '\0';
	/**/fprintf(stderr, "LDAP search on [%d]%s\n", length, url);

	rc = ldap_url_parse(url, &lud);
	if (rc != LDAP_SUCCESS) {
		fprintf(stderr, "ldap_url_parse: %d[%s]\n",
			rc, ldap_err2string(rc));
		goto end;
	}
	/**/
	fprintf(stderr, "URL Parse:\n");
	fprintf(stderr, "\tscheme = %s\n", lud->lud_scheme);
	fprintf(stderr, "\thost = %s, port=%d\n",
		lud->lud_host, lud->lud_port);
	fprintf(stderr, "\tdn/base = %s\n", lud->lud_dn);
	if (lud->lud_attrs != NULL)
		for (i = 0; lud->lud_attrs[i] != NULL; i++)
			fprintf(stderr, "\tattr[%d] = %s\n",
				i, lud->lud_attrs[i]);
	fprintf(stderr, "\tscope = %d\n", lud->lud_scope);
	if (lud->lud_filter != NULL)
		fprintf(stderr, "\tfilter = %s\n", lud->lud_filter);
	if (lud->lud_exts != NULL)
		for (i = 0; lud->lud_exts[i] != NULL; i++)
			fprintf(stderr, "\textension[%d] = %s\n",
				i, lud->lud_exts[i]);
	fprintf(stderr, "\tcritical = %d\n", lud->lud_crit_exts);

	ld = ldap_init(lud->lud_host, lud->lud_port);
	if (ld == NULL) {
		perror("ldap_init");
		goto end;
	}

	rc = ldap_simple_bind_s(ld, NULL, NULL);
	if (rc != LDAP_SUCCESS) {
		fprintf(stderr, "ldap_simple_bind_s: %d[%s]\n",
			rc, ldap_err2string(rc));
		goto end;
	}

	switch (type) {
	case X509_LU_X509:
		attrs = x509_attrs;
		break;

	case X509_LU_CRL:
		attrs = crl_attrs;
		break;

	default:
		attrs = lud->lud_attrs;
		break;
	}

	rc = ldap_search_ext_s(ld,
			       lud->lud_dn,
			       LDAP_SCOPE_SUBTREE,
			       lud->lud_filter,
			       attrs,
			       0,
			       NULL,
			       NULL,
			       NULL,
			       LDAP_NO_LIMIT,
			       &result);
	if (rc != LDAP_SUCCESS) {
		fprintf(stderr, "ldap_search: %d[%s]\n",
			rc, ldap_err2string(rc));
		goto end;
	}

	rc = ldap_count_entries(ld, result);
	/**/fprintf(stderr, "%d entries\n", rc);
	if (rc < 0) {
		fprintf(stderr, "ldap_count_entries: %d[%s]\n",
			rc, ldap_err2string(rc));
		goto end;
	} else if (rc == 0)
		goto end;

	for (entry = ldap_first_entry(ld, result);
	     entry != NULL;
	     entry = ldap_next_entry(ld, entry)) {
		/**/fprintf(stderr, "DN = %s\n", ldap_get_dn(ld, entry));

		for (attr = ldap_first_attribute(ld, entry, &ber);
		     attr != NULL;
		     attr = ldap_next_attribute(ld, entry, ber)) {
			/**/fprintf(stderr, "Attr = %s\n", attr);

			if (strcmp(attrs[0], attr) != 0)
				continue;
			vals = ldap_get_values_len(ld, entry, attr);
			if (vals == NULL) {
				fprintf(stderr,
					"ldap_get_values_len: %d[%s]\n",
					rc, ldap_err2string(rc));
				goto end;
			}
			add_vals(ctx, type, vals);
			ldap_value_free_len(vals);
			vals = NULL;
		}
/*		ber_free(ber, 0);*/
		ber = NULL;
	}
	ldap_msgfree(result);
	ldap_unbind_s(ld);
	ldap_free_urldesc(lud);
	return type;

   end:
	if (vals)
		ldap_value_free_len(vals);
	if (ber)
		ber_free(ber, 0);
	if (result)
		ldap_msgfree(result);
	if (ld)
		ldap_unbind_s(ld);
	if (lud)
		ldap_free_urldesc(lud);
	return X509_LU_FAIL;
}

void
add_vals(X509_LOOKUP *ctx, int type, struct berval **vals)
{
	X509 *x;
	X509_CRL *c;
	unsigned char *p;
	int i;

	for (i = 0; vals[i] != NULL; i++) {
		p = (unsigned char *) vals[i]->bv_val;
		if (type == X509_LU_X509) {
			x = d2i_X509(NULL, &p, vals[i]->bv_len);
			if (x == NULL) {
				unsigned long l;

				/**/
				fprintf(stderr, "d2i_X509 failed\n");
				while ((l = ERR_get_error()) != 0)
					fprintf(stderr, "%s",
						ERR_error_string(l, NULL));
				continue;
			}
			if (X509_STORE_add_cert(ctx->store_ctx, x) <= 0) {
				/**/
				fprintf(stderr, "X509_STORE_add_cert?\n");
				continue;
			}
			/**/fprintf(stderr, "Added CERT\n");
			X509_free(x);
		} else if (type == X509_LU_CRL) {
			c = d2i_X509_CRL(NULL, &p, vals[i]->bv_len);
			if (c == NULL) {
				unsigned long l;

				/**/
				fprintf(stderr, "d2i_X509_CRL failed\n");
				while ((l = ERR_get_error()) != 0)
					fprintf(stderr, "%s",
						ERR_error_string(l, NULL));
				continue;
			}
			if (X509_STORE_add_crl(ctx->store_ctx, c) <= 0) {
				/**/
				fprintf(stderr, "X509_STORE_add_crl?\n");
				continue;
			}
			/**/fprintf(stderr, "Added CRL\n");
			X509_CRL_free(c);
		}
	}
}
