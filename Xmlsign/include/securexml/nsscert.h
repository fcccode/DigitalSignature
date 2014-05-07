#ifndef _NSSCERT_H_
#define _NSSCERT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <plarena.h>
#include <plhash.h>
#include <prlong.h>
#include <prlog.h>

#include <seccomon.h>
#include <secdert.h>
#include <secoidt.h>
#include <keyt.h>

#ifdef OLD
typedef enum {
    CertificateExtensions,
    CrlExtensions,
    OCSPRequestExtensions,
    OCSPSingleRequestExtensions,
    OCSPResponseSingleExtensions
} ExtensionsType;
#endif

typedef struct {
   int requireExplicitPolicy;
   int inhibitPolicyMapping;    
}CERTPolicyConstraintInfo;

typedef struct {
    SECOidTag oid;
	SECItem qualifierID;
    SECItem qualifierValue;
} i_CERTPolicyQualifier;

typedef struct {
    SECOidTag oid;
	BYTE cID[256];
	SECItem policyID;
    i_CERTPolicyQualifier **policyQualifiers;
} i_CERTPolicyInfo;

typedef struct {
    PRArenaPool *arena;
    i_CERTPolicyInfo **policyInfos;
} i_CERTCertificatePolicies;

#define MY_CONST_OID static const unsigned char
MY_CONST_OID i_x509PolicyConstraints[]     		= { 0x55, 0x1d, 36 };
MY_CONST_OID oid_delta_crl_idicator[] = { 0x55, 0x1d, 27 };
MY_CONST_OID oid_issuing_disp_point[] = { 0x55, 0x1d, 28 };

SEC_BEGIN_PROTOS

extern CERTPolicyConstraintInfo *
i_CERT_DecodeCertificatePolicyConstraintsExtension(SECItem *extnValue);

   
extern CERTCrlDistributionPoints *FindCRLDistributionPoints (CERTCertificate *cert);
/*
** Decode a DER encoded certificate into an CERTCertificate structure
**	"derSignedCert" is the DER encoded signed certificate
**	"copyDER" is true if the DER should be copied, false if the
**		existing copy should be referenced
**	"nickname" is the nickname to use in the database.  If it is NULL
**		then a temporary nickname is generated.
*/
extern CERTCertificate *
DecodeDERCertificate (SECItem *derSignedCert);

extern SECStatus FindBasicConstraintExten(CERTCertificate *cert,CERTBasicConstraints *value);
/**************** certxutil.h ***********************/
extern CERTCertExtension *
i_GetExtension (CERTCertExtension **extensions, SECItem *oid);

extern PRBool
i_cert_HasCriticalExtension (CERTCertExtension **extensions);

extern SECStatus
i_cert_FindExtension (CERTCertExtension **extensions, int tag, SECItem *value);

extern SECStatus
i_cert_FindExtensionByOID (CERTCertExtension **extensions,
			 SECItem *oid, SECItem *value);

extern SECStatus
i_cert_GetExtenCriticality (CERTCertExtension **extensions,
			  int tag, PRBool *isCritical);

extern i_CERTCertificatePolicies *
i_CERT_DecodeCertificatePoliciesExtension(SECItem *extnValue);

extern void
i_CERT_DestroyCertificatePoliciesExtension(i_CERTCertificatePolicies *policies);

//extern PRBool
//i_cert_HasUnknownCriticalExten (CERTCertExtension **extensions);

SEC_END_PROTOS

#ifdef __cplusplus
}       // Balance extern "C" above
#endif

#endif /* _NSSCERT_H_ */
