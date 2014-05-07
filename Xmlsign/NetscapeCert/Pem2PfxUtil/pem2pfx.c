/* Written by Dr Stephen N Henson (shenson@bigfoot.com) for the OpenSSL
 * project 1999.
 */
/* ====================================================================
 * Copyright (c) 1999 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.OpenSSL.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    licensing@OpenSSL.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.OpenSSL.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apps.h"
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/pkcs12.h>

const EVP_CIPHER *enc;

#include "pem2pfx.h"

void GetBaseName(const char *fileName, char *baseName)
{
	char *pt1, *pt2;
	BOOL foundSlash = FALSE;
	unsigned long len = 0;

	// TODO: Need to ignore the caps here in extension
	char *ptr = strstr(fileName, ".pem");

	// If there is no .pem extension, then return the whole file name
	if (ptr == NULL)
	{
		sprintf(baseName, "%s", fileName);
		return;
	}

	pt1 = strstr(fileName, "\\");
	while (pt1 != NULL)
	{
		foundSlash = TRUE;
		pt2 = pt1;
		pt1 = strstr(pt1 + 1, "\\");
	}

	// TODO: Need to check for the last .pem extension here
	if (foundSlash)
	{
		len = ptr - (pt2 + 1);
		strncpy(baseName, pt2 + 1, len);
	}
	else
	{
		len = ptr - fileName;
		strncpy(baseName, fileName, len);
	}
	baseName[len] = '\0';
}

char *Pem2Pfx(char *pemFile, char *pemPass)
{
    BIO *in=NULL, *out = NULL;
	char tempDirPath[MAX_PATH];
	char baseFileName[MAX_PATH];
	char *retFileName = NULL;
	EVP_PKEY *key = NULL;
	STACK_OF(PKCS12_SAFEBAG) *bags = NULL;
	STACK_OF(PKCS7) *safes = NULL;
	PKCS12_SAFEBAG *bag = NULL;
	PKCS8_PRIV_KEY_INFO *p8 = NULL;
	PKCS7 *authsafe = NULL;
	X509 *ucert = NULL;
	STACK_OF(X509) *certs=NULL;
	char *catmp = NULL;
	int i;
	unsigned char keyid[EVP_MAX_MD_SIZE];
	unsigned int keyidlen = 0;
	char *name = NULL;
    STACK *canames = NULL;
    int cert_pbe = NID_pbe_WithSHA1And40BitRC2_CBC;
    int key_pbe = NID_pbe_WithSHA1And3_Key_TripleDES_CBC;
    int iter = PKCS12_DEFAULT_ITER;
    int maciter = PKCS12_DEFAULT_ITER;
    int keytype = 0;
    char *csp_name = NULL;
    HRESULT ret = S_FALSE;
    PKCS12 *p12 = NULL;
	FILE *test;

    apps_startup();

    enc = EVP_des_ede3_cbc();

	app_RAND_load_file(NULL, bio_err, FALSE);
    ERR_load_crypto_strings();

	in = BIO_new_file(pemFile, "rb");
    if (!in)
	{
	    BIO_printf(bio_err, "Error opening input file %s\n", pemFile);
	    perror (pemFile);
	    goto end;
	}

	// Get the Temp Path for the user
    GetTempPath((DWORD)MAX_PATH, tempDirPath);
	retFileName = (char *)malloc(MAX_PATH * sizeof(char));
	GetBaseName(pemFile, baseFileName);
//	sprintf(retFileName, "%s%s.pfx", "C:\\Temp\\Debug\\", baseFileName);
	sprintf(retFileName, "%s%s.pfx", tempDirPath, baseFileName);

	out = BIO_new_file(retFileName, "wb");
	if (!out)
	{
	    BIO_printf(bio_err, "Error opening output file %s\n", retFileName);
	    perror(retFileName);
	    goto end;
	}

	key = load_key(bio_err, pemFile, FORMAT_PEM, 1, pemPass, NULL, "private key");
	if (!key)
		goto end;

	/* Load in all certs in input file */
	if(!(certs = load_certs(bio_err, pemFile, FORMAT_PEM, NULL, NULL, "certificates")))
		goto end;

	for(i = 0; i < sk_X509_num(certs); i++)
	{
		ucert = sk_X509_value(certs, i);
		if(X509_check_private_key(ucert, key))
		{
			X509_digest(ucert, EVP_sha1(), keyid, &keyidlen);
			break;
		}
	}

	if(!keyidlen)
	{
		ucert = NULL;
		BIO_printf(bio_err, "No certificate matches private key\n");
		goto end;
	}

	bags = sk_PKCS12_SAFEBAG_new_null();

	/* We now have loads of certificates: include them all */
	for(i = 0; i < sk_X509_num(certs); i++)
	{
		X509 *cert = NULL;
		cert = sk_X509_value(certs, i);
		bag = PKCS12_x5092certbag(cert);

		/* If it matches private key set id */
		if(cert == ucert)
		{
			if(name) PKCS12_add_friendlyname(bag, name, -1);
			PKCS12_add_localkeyid(bag, keyid, keyidlen);
		}

		else if((catmp = sk_shift(canames))) 
			PKCS12_add_friendlyname(bag, catmp, -1);

		sk_PKCS12_SAFEBAG_push(bags, bag);
	}

	sk_X509_pop_free(certs, X509_free);
	certs = NULL;

	/* Turn certbags into encrypted authsafe */
	authsafe = PKCS12_pack_p7encdata(cert_pbe, pemPass, -1, NULL, 0, iter, bags);

	sk_PKCS12_SAFEBAG_pop_free(bags, PKCS12_SAFEBAG_free);
	bags = NULL;

	if (!authsafe)
	{
		ERR_print_errors(bio_err);
		goto end;
	}

	safes = sk_PKCS7_new_null();
	sk_PKCS7_push(safes, authsafe);

	/* Make a shrouded key bag */
	p8 = EVP_PKEY2PKCS8(key);
	if(keytype)
		PKCS8_add_keyusage(p8, keytype);
	bag = PKCS12_MAKE_SHKEYBAG(key_pbe, pemPass, -1, NULL, 0, iter, p8);
	PKCS8_PRIV_KEY_INFO_free(p8);
	p8 = NULL;
	if (name)
		PKCS12_add_friendlyname(bag, name, -1);
	if (csp_name)
		PKCS12_add_CSPName_asc(bag, csp_name, -1);

	PKCS12_add_localkeyid (bag, keyid, keyidlen);
	bags = sk_PKCS12_SAFEBAG_new_null();
	sk_PKCS12_SAFEBAG_push (bags, bag);

	/* Turn it into unencrypted safe bag */
	authsafe = PKCS12_pack_p7data(bags);
	sk_PKCS12_SAFEBAG_pop_free(bags, PKCS12_SAFEBAG_free);
	bags = NULL;
	sk_PKCS7_push(safes, authsafe);

	p12 = PKCS12_init(NID_pkcs7_data);

	PKCS12_pack_authsafes(p12, safes);

	sk_PKCS7_pop_free(safes, PKCS7_free);
	safes = NULL;

	PKCS12_set_mac(p12, pemPass, -1, NULL, 0, maciter, NULL);

	i2d_PKCS12_bio (out, p12);

	ret = S_OK;

end:

	if (key)
		EVP_PKEY_free(key);
	if (certs)
		sk_X509_pop_free(certs, X509_free);
	if (safes)
		sk_PKCS7_pop_free(safes, PKCS7_free);
	if (bags)
		sk_PKCS12_SAFEBAG_pop_free(bags, PKCS12_SAFEBAG_free);
    if (p12)
		PKCS12_free(p12);
    app_RAND_write_file(NULL, bio_err);
    BIO_free(in);
    BIO_free_all(out);
    if (canames)
		sk_free(canames);
    apps_shutdown();

	if (ret != S_OK)
		return NULL;

	return retFileName;
}