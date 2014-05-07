/*****************************************************************************************
 * Copyright: (c) 2001 Infomosaic Corporation.
 * All rights reserved.
 * It is violation of international law to use this code without proper written authorization
 * and license agreement from Infomosaic Corporation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL INFOMOSAIC CORPORATION  OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * Author: 
 * Date:   
 * Change history:
 *
 * Date		|	Modified By		|	Brief description of the modification
 *
 *
 *****************************************************************************************
 */

#ifndef __CR_H__
#define __CR_H__
#if __cplusplus
extern "C" {
#endif

#include <securexml/coresig.h>
#include <securexml/ax.h>

#ifdef NSS
typedef unsigned int ALG_ID;
#endif

#ifdef NSS
#include <securexml/nsscert.h>

// crypto constants
#ifndef CALG_SHA1
#define CALG_SHA1	1
#endif
#ifndef CALG_DSS_SIGN
#define	CALG_DSS_SIGN 2
#endif
#ifndef CALG_RSA_SIGN
#define	CALG_RSA_SIGN 3
#endif
#ifndef CALG_HMAC
#define CALG_HMAC 4
#endif
#ifndef CALG_RSA_KEYX
#define CALG_RSA_KEYX 5
#endif
#ifndef CALG_SHA
#define CALG_SHA	1
#endif
#ifndef szOID_ANY_CERT_POLICY
#define szOID_ANY_CERT_POLICY           "2.5.29.32.0"
#endif

#define LDAP_PORT 389
#define LDAP_SCOPE_BASE 0x00
#define LDAP_SCOPE_SUBTREE 0x02
#define LDAP_SCOPE_ONELEVEL 0x01

#endif
/*
 * Wrappers for CryptAPI
 *
 */

#define MY_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
#define CERT_STORE_NAME  L"MY"
#define MAX_MODULUS_SIZE 1024

/**
 * RSAPUBKEYDETAILS:
 *
 * RSA Public key BLOB
 */

typedef struct _RSAPUBKEYDETAILS RSAPUBKEYDETAILS;
#ifdef NSS
struct _RSAPUBKEYDETAILS {
	//SECKEYPublicKey *pubKey;
	BYTE Modulus[MAX_MODULUS_SIZE];
	DWORD ModLen;
	BYTE Exponent[MAX_MODULUS_SIZE];
	DWORD ExpLen;
};
#else
struct _RSAPUBKEYDETAILS {
   PUBLICKEYSTRUC PublicKey;
   RSAPUBKEY RSAPublicKey;
   BYTE Modulus[MAX_MODULUS_SIZE];
};
#endif

/**
 * DSAPUBKEYDETAILS:
 *
 * DSA Public key BLOB
 */

typedef struct _DSAPUBKEYDETAILS DSAPUBKEYDETAILS;
#ifdef NSS
struct _DSAPUBKEYDETAILS {
	//SECKEYPublicKey *pubKey;
	BYTE              p[MAX_MODULUS_SIZE];
	BYTE              q[MAX_MODULUS_SIZE];
	BYTE              g[MAX_MODULUS_SIZE];
	BYTE              y[MAX_MODULUS_SIZE];
	DWORD pLen;
	DWORD qLen;
	DWORD gLen;
	DWORD yLen;
};
#else
struct _DSAPUBKEYDETAILS {
	PUBLICKEYSTRUC    publickeystruc ;
	DSSPUBKEY         dsspubkey;
	BYTE              p[MAX_MODULUS_SIZE];
	BYTE              q[20];
	BYTE              g[MAX_MODULUS_SIZE];
	BYTE              y[MAX_MODULUS_SIZE];
	DSSSEED           seedstruct;
};
#endif

#ifdef NSS
	typedef struct _MOZPUBLICKEY MOZPUBLICKEY;
	struct _MOZPUBLICKEY {
		int type; // 1- rsaKey, 2- dsaKey (keythi.h)
		RSAPUBKEYDETAILS rsaKey;
		DSAPUBKEYDETAILS dsaKey;
	};
#endif

// calculate digest 
extern int crComputeHash(ALG_ID algId,
				  PDS_DATA_BLOB pKey,
				  PDS_DATA_BLOB pdHash,
				  BYTE *pbDigest,
				  DWORD *cbDigest,
				  PGLOBAL_SIG pg_sig);

// verify digest
extern int crVerifyDigest(
		unsigned char *pbHashValue,
		unsigned int HashAlg,
		PDS_DATA_BLOB pObjectToHash,
		PDS_DATA_BLOB hKey,
		PGLOBAL_SIG pg_sig);

// verify signature
extern int crVerifySignature(
		PDS_DATA_BLOB cbDataToSign,
		ALG_ID SignatureAlg,
		PDS_DATA_BLOB cbSignatureValue,
		RSAPUBKEYDETAILS *RsaPubKey,
		DSAPUBKEYDETAILS *DsaPubKey, 
		PDS_DATA_BLOB pKey, 
		PGLOBAL_SIG pg_sig);

// cast PUBLICKEYBLOB to structure
extern int crGetPubKey(RSAPUBKEYDETAILS *rsaPubKey, DSAPUBKEYDETAILS *dsaPubKey, BYTE *keyBlobData);

// big integer to octets: big endian format
extern int crI2O(
	unsigned long lint,
	BYTE *newExp,
	DWORD *expLen);

extern int crO2I(
	BYTE *newExp,
	DWORD expLen,
	unsigned long *lint);

extern int crGetCertDetails(PCERT_DESCR certDetails, BYTE *pbData);

// get public key from certificate
extern int crGetCertPubKey(RSAPUBKEYDETAILS *rsaPubKey, DSAPUBKEYDETAILS *dsaPubKey, BYTE *pbData, PGLOBAL_SIG pg_sig);

// detect signature method from certificate: RSA or DSA
extern int crGetProviderType(
	const char *certData, PGLOBAL_SIG pg_sig);

// get CALG from XML Signature URI algorithm specification
extern int crGetCALG(char *alg);

// sign data with certificate
extern int crSign(PDS_DATA_BLOB srcObject,
		   BYTE *certData,
		   PDS_DATA_BLOB hHMACKey,
		   BYTE *pbSignature,
		   DWORD *dwSigLen,
		   DWORD *pkalgtype,
		   BYTE *keyBlobData,
		   DWORD *keySize,
		   BYTE *pbHash,
		   PGLOBAL_SIG pg_sig);

extern unsigned char *crConvertXmlDSASigToApi(unsigned char *xmlsig, int *len);
extern unsigned char *crConvertXmlRSASigToApi(unsigned char *xmlsig, int *xmlsiglen);
extern unsigned char *crConvertApiDSASigToXml(unsigned char *sig, int len);
extern unsigned char *crConvertApiRSASigToXml(unsigned char *sig, int siglen);
#ifdef NSS
extern unsigned char *crPFX2X509(
	PDS_DATA_BLOB certData,
	SECItem *password,
	PCERT_DESCR *pfxCertInfo,
	PGLOBAL_SIG pg_sig);
#else
extern unsigned char *crPFX2X509(
	PDS_DATA_BLOB certData,
	LPCWSTR password,
	PCERT_DESCR *pfxCertInfo,
	PGLOBAL_SIG pg_sig);
#endif
// cryptui.c
#if defined(NSS)
extern BOOL crFilterCerts(
        CERTCertificate *pCertContext,
		PGLOBAL_SIG		pg_sig);
#else
extern BOOL crFilterCerts(
        PCCERT_CONTEXT  pCertContext,
        BOOL            *pfInitialSelectedCert,
        void            *pvCallbackData,
		PGLOBAL_SIG		pg_sig);
#endif

extern int crIsPFX(unsigned char *certData, PDS_DATA_BLOB pwd, PGLOBAL_SIG pg_sig);
extern DS_DATA_BLOB **fetchLDAP_URL(BYTE *url);
extern DS_DATA_BLOB *fetch_URL(BYTE *url);
#ifdef NSS
extern BYTE **crGetSignerCertChain(BYTE *pEndCert, SECItem *password,  UINT *iCount, PGLOBAL_SIG pg_sig);
extern unsigned char *getCRLDist(CERTCertificate *pCertContext);
#else
extern BYTE **crGetSignerCertChain(BYTE *pEndCert, LPWSTR password,  UINT *iCount, PGLOBAL_SIG pg_sig);
extern unsigned char *getCRLDist(PCCERT_CONTEXT pCertContext);
#endif

#ifdef NSS
extern BOOL certIsNameEqual(BYTE *a, 
						    BYTE *b);

//extern SECItem *normalizeCertName(SECItem *pCertName);
extern BOOL certIsNameChainOK(CERTCertificateList *pChainContext, CERTCertDBHandle *handle);
extern BOOL certIsBasicExtensionConstraintOK(CERTCertificateList *pChainContext,CERTCertDBHandle *handle,PGLOBAL_SIG pg_sig);
extern BOOL certIsPathLengthConstraintOK(CERTCertificateList *pChainContext, CERTCertDBHandle *handle, PGLOBAL_SIG pg_sig);
extern BOOL certIsKeyUsageOK(CERTCertificateList *pChainContext, CERTCertDBHandle *handle, PGLOBAL_SIG pg_sig);
extern LPSTR *getAuthConstrainedPolicySet(CERTCertificateList *pChainContext,
										  CERTCertDBHandle *handle,
										  UINT explicitPolicyCount,
										  BOOL *explicitPolicyInd,		// out
										  UINT *authConstPolCount);
extern LPSTR *getUserConstrainedPolicySet(CERTCertificateList *pChainContext,
												CERTCertDBHandle *handle,
												LPSTR *userPolicySet,
												UINT userPolicyCount,
												UINT explicitPolicyCount,
												BOOL *explicitPolicyInd,		// out
												UINT *userConstPolCount);
extern BOOL crNSS_PFXIsPFXBlob(SECItem *blob, SECItem *pwd, PGLOBAL_SIG pg_sig);
//extern SECItem *normalizeCertName(SECItem *pCertName);
#else
extern BOOL certIsNameEqual(PCERT_NAME_BLOB pCertName1, 
						    PCERT_NAME_BLOB pCertName2);
extern PCERT_NAME_BLOB normalizeCertName(PCERT_NAME_BLOB pCertName);

extern BOOL certIsNameChainOK(PCCERT_CHAIN_CONTEXT pChainContext);
extern BOOL certIsBasicExtensionConstraintOK(PCCERT_CHAIN_CONTEXT pChainContext, PGLOBAL_SIG pg_sig);
extern BOOL certIsPathLengthConstraintOK(PCCERT_CHAIN_CONTEXT pChainContext, PGLOBAL_SIG pg_sig);
extern BOOL certIsKeyUsageOK(PCCERT_CHAIN_CONTEXT pChainContext, PGLOBAL_SIG pg_sig);
extern LPSTR *getAuthConstrainedPolicySet(PCCERT_CHAIN_CONTEXT pChainContext,
										  UINT explicitPolicyCount,
										  BOOL *explicitPolicyInd,		// out
										  UINT *authConstPolCount);
extern LPSTR *getUserConstrainedPolicySet(PCCERT_CHAIN_CONTEXT pChainContext,
												LPSTR *userPolicySet,
												UINT userPolicyCount,
												UINT explicitPolicyCount,
												BOOL *explicitPolicyInd,		// out
												UINT *userConstPolCount);
#endif

extern void cleanupError(PGLOBAL_SIG pg_sig);

#ifdef NSS
BOOL crDecodeCertificate(CERTCertificate *cert,PCERT_DESCR *cdes);
#else
BOOL crDecodeCertificate(PCCERT_CONTEXT cert,PCERT_DESCR *cdes);
#endif


#ifdef NSS
// special cases with certificates
extern CERTCertificate *NSS_ImportPKCS12Object(SECItem *, SECItem *, PGLOBAL_SIG pg_sig);
extern CERTCertList *P12U_ImportPKCS12Object(SECItem *pfx, PK11SlotInfo *slot, SECItem *pwitem, PRBool doImport, PGLOBAL_SIG pg_sig);
extern void P12U_Init();
extern SECStatus iP12U_InitSlot(PK11SlotInfo *slot, PGLOBAL_SIG pg_sig);
extern PRBool PKCS12ValidData(SECItem *p12file, SECItem *pwitem, PGLOBAL_SIG pg_sig);
extern CERTCrlEntry *FindCertInCRL(CERTCertificate *cert, CERTCrl *crl);
extern SECStatus P12U_UnicodeConversion(PRArenaPool *arena, SECItem *dest, SECItem *src,
		       PRBool toUnicode, PRBool swapBytes);
#endif

#if __cplusplus
}
#endif

#endif

