/* scvp.h */
/* Written by Yann Busnel <Yann.Busnel@enst-bretagne.fr> */
/* for the RSM group of projects */
/* ================================================================ */

/* TODO : 
 *   - Reasonable value for MAX (in SIZE (1..MAX)).
 *   - Add cplusplus export
 *   - Get an ASN.1 for AttributeCertificate (to replace SCVP_ATTRIBUTECERT).
 */

#ifndef HEADER_SCVP_H
#define HEADER_SCVP_H

#include <openssl/asn1t.h>
#include <openssl/ocsp.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/safestack.h>

/* ===================================================
 *                   SCVP REQUEST
 * ===================================================
 */

/*  RevocationInfos ::= SEQUENCE SIZE (1..MAX) OF RevocationInfo
 *  
 *  RevocationInfo ::= CHOICE {
 *    crl        [0] CertificateList,
 *    delta-crl  [1] CertificateList,
 *    ocsp       [2] OCSPResponse,
 *    other      [3] OtherRevInfo }
 *  
 *  OtherRevInfo ::= SEQUENCE {
 *    retype         OBJECT IDENTIFIER,
 *    revalue        ANY DEFINED BY retype }
 */

typedef struct scvp_other_rev_info_st {
	ASN1_OBJECT *retype;
	ASN1_TYPE *revalue;
} SCVP_OTHERREVINFO;

#define V_SCVP_REVOCATIONINFO_CRL       0
#define V_SCVP_REVOCATIONINFO_DELTA_CRL 1
#define V_SCVP_REVOCATIONINFO_OCSP      2
#define V_SCVP_REVOCATIONINFO_OTHER     3

typedef struct scvp_revocation_info_st {
	int type;
	union {
		X509_CRL *crl;
		X509_CRL *delta_crl;
		OCSP_RESPONSE *ocsp;
		SCVP_OTHERREVINFO *other;
	} value;
} SCVP_REVOCATIONINFO;

DECLARE_STACK_OF(SCVP_REVOCATIONINFO)

typedef struct scvp_revocation_infos_st {
	STACK_OF(SCVP_REVOCATIONINFO) *revinfo;
} SCVP_REVOCATIONINFOS;

/*  ValidationPolicy ::= SEQUENCE {
 *    valPolicyId           OBJECT IDENTIFIER,
 *    parameters            ANY DEFINED BY valPolicyId OPTIONAL }
 */

typedef struct scvp_validation_policy_st {
	ASN1_OBJECT *valPolicyId;
	ASN1_TYPE *parameters;     /* OPTIONAL */
} SCVP_VALIDPOLICY;

/*  ESSCertID ::=  SEQUENCE {
 *    certHash                 Hash,
 *    issuerSerial             IssuerSerial OPTIONAL }
 *  
 *  Hash ::= OCTET STRING -- SHA1 hash of entire certificate
 *  
 *  IssuerSerial ::= SEQUENCE {
 *    issuer                   GeneralNames,
 *    serialNumber             CertificateSerialNumber }
 *  
 *  
 */

typedef struct scvp_ess_issuer_serial_st {
	GENERAL_NAME *issuer;
	ASN1_INTEGER *serialNumber;
} ESS_ISSUERSERIAL;

typedef struct scvp_ess_certId_st {
	ASN1_OCTET_STRING *certHash;
	ESS_ISSUERSERIAL *issuerSerial;
} ESS_CERTID;

typedef struct scvp_attributecert_st {
} SCVP_ATTRIBUTECERT;

/*  CertReference ::= CHOICE {
 *    pkc                   PKCReference,
 *    ac                    ACReference }
 *
 *  PKCReference ::= CHOICE {
 *    cert              [1] Certificate,
 *    pkcRef            [2] ESSCertID }
 *
 *  ACReference ::= CHOICE {
 *    attrCert          [3] AttributeCertificate,
 *    acRef             [4] ESSCertID }
 */

#define V_SCVP_PKCREF_CERT    0
#define V_SCVP_PKCREF_PKCREF  1

typedef struct scvp_pkcRef_st {
	int type;
	union {
		X509 *cert;
		ESS_CERTID *pkcRef;
	} value;
} SCVP_PKCREF;

DECLARE_STACK_OF(SCVP_PKCREF)

#define V_SCVP_ACREF_ATTRCERT 0
#define V_SCVP_ACREF_ACREF    1

typedef struct scvp_acRef_st {
	int type;
	union {
		SCVP_ATTRIBUTECERT *attrCert;
		ESS_CERTID *acRef;
	} value;
} SCVP_ACREF;

#define V_SCVP_CERTREF_PKC    0
#define V_SCVP_CERTREF_AC     1

typedef struct scvp_certRef_st {
	int type;
	union {
		SCVP_PKCREF *pkc;
		SCVP_ACREF *ac;
	} value;
} SCVP_CERTREF;

DECLARE_STACK_OF(SCVP_CERTREF)

/* CertBundle ::= SEQUENCE SIZE (1..MAX) OF PKCReference
 */

typedef struct scvp_cert_bundle_st {
	STACK_OF(SCVP_PKCREF) *bundle;
} SCVP_CERTBUNDLE;

/*  TrustAnchors ::= SEQUENCE SIZE (1..MAX) OF TrustAnchor
 *  
 *  TrustAnchor ::= SEQUENCE {
 *    anchor                  PKCReference,
 *    certPolicies        [1] SEQUENCE SIZE (1..MAX) OF
 *    OBJECT IDENTIFIER OPTIONAL }
 *  -- if absent, use any-policy
 */

typedef struct scvp_trust_anchor_st {
	SCVP_PKCREF *anchor;
	STACK_OF(ASN1_OBJECT) *certPolicies;
} SCVP_TRUSTANCHOR;

DECLARE_STACK_OF(SCVP_TRUSTANCHOR)

/*  Query ::= SEQUENCE {
 *    queriedCerts          SEQUENCE SIZE (1..MAX) OF CertReference,
 *    checks                CertChecks,
 *    wantBack              WantBack,
 *    serverContextInfo  [0] OCTET STRING OPTIONAL,
 *    valPolicy          [1] ValidationPolicy,
 *    validityTime       [2] GeneralizedTime OPTIONAL,
 *    trustAnchors       [3] TrustAnchors OPTIONAL,
 *    intermediateCerts  [4] CertBundle OPTIONAL,
 *    revInfos           [5] RevocationInfos OPTIONAL,
 *    queryExtensions    [6] Extensions OPTIONAL }
 */

typedef struct scvp_query_st {
	STACK_OF(SCVP_CERTREF) *queriedCerts;
	STACK_OF(ASN1_OBJECT) *checks;
	STACK_OF(ASN1_OBJECT) *wantBack;
	ASN1_OCTET_STRING *serverContextInfo;      /* OPTIONAL */
	SCVP_VALIDPOLICY *valPolicy;
	ASN1_GENERALIZEDTIME *validityTime;        /* OPTIONAL */
	STACK_OF(SCVP_TRUSTANCHOR) *trustAnchors;  /* OPTIONAL */
	SCVP_CERTBUNDLE *intermediateCerts;        /* OPTIONAL */
	SCVP_REVOCATIONINFOS *revInfos;            /* OPTIONAL */
	STACK_OF(X509_EXTENSION) *queryExtensions; /* OPTIONAL */
} SCVP_QUERY;

/*  CVRequest ::= SEQUENCE {
 *    scvpVersion           INTEGER,
 *    query                 Query,
 *    requestor         [0] OCTET STRING OPTIONAL,
 *    requestNonce      [1] OCTET STRING OPTIONAL,
 *    reqExtensions     [2] Extensions OPTIONAL }
 */ 

typedef struct scvp_request_st {
	ASN1_INTEGER *scvpVersion;
	SCVP_QUERY *query;
	ASN1_OCTET_STRING *requestor;            /* OPTIONAL */
	ASN1_OCTET_STRING *requestNonce;         /* OPTIONAL */
	STACK_OF(X509_EXTENSION) *reqExtensions; /* OPTIONAL */
} SCVP_REQUEST;

/* ===================================================
 *                   SCVP RESPONSE
 * ===================================================
 */

/*  ReplyWantBacks ::= SEQUENCE OF ReplyWantBack 
 *    
 *  ReplyWantBack::= SEQUENCE { 
 *    wb                         OBJECT IDENTIFIER, 
 *    value                      OCTET STRING } 
 *    -- CertBundle
 *    -- RevocationInfo (RevocationInfos for us)
 *    -- BOOLEAN
 *    -- SubjectPublicKeyInfo
 */

typedef struct scvp_reply_wantback_st {
	ASN1_OBJECT *wb;
	ASN1_OCTET_STRING *value;
	union {
		SCVP_CERTBUNDLE *certpath;
		SCVP_REVOCATIONINFOS *revstatus;
		ASN1_BOOLEAN status;
		X509_PUBKEY *pkinfo;
		ASN1_TYPE *other;
	} d;
} SCVP_REPLYWANTBACK;

DECLARE_STACK_OF(SCVP_REPLYWANTBACK)

/*  ReplyChecks ::= SEQUENCE OF ReplyCheck 
 *    
 *  ReplyCheck ::= SEQUENCE { 
 *    check                      OBJECT IDENTIFIER, 
 *    status                     INTEGER } 
 */

typedef struct scvp_reply_check_st {
	ASN1_OBJECT *check;
	ASN1_INTEGER *status;
} SCVP_REPLYCHECK;

DECLARE_STACK_OF(SCVP_REPLYCHECK)

/*     ReplyStatus ::= ENUMERATED { 
 *       success                  (0), 
 *       unrecognizedCheck        (1), 
 *       unrecognizedWantBack     (2), 
 *       malformedPKC             (3), 
 *       malformedAC              (4), 
 *       unrecognizedCertPolicy   (5), 
 *       unrecognizedValPolicy    (6), 
 *       unrecognizedExtension    (7), 
 *       unavailableValidityTime  (8), 
 *       referenceCertHashFail    (9), 
 *       certPathConstructFail   (10), 
 *       certPathNotValid        (11), 
 *       certPathNotValidNow     (12) } 
 */

#define SCVP_REPLY_STATUS_SUCCESS                  0L
#define SCVP_REPLY_STATUS_UNRECOGNIZEDCHECK        1L
#define SCVP_REPLY_STATUS_UNRECOGNIZEDWANTBACK     2L
#define SCVP_REPLY_STATUS_MALFORMEDPKC             3L
#define SCVP_REPLY_STATUS_MALFORMEDAC              4L
#define SCVP_REPLY_STATUS_UNRECOGNIZEDCERTPOLICY   5L
#define SCVP_REPLY_STATUS_UNRECOGNIZEDVALPOLICY    6L
#define SCVP_REPLY_STATUS_UNRECOGNIZEDEXTENSION    7L
#define SCVP_REPLY_STATUS_UNAVAILABLEVALIDITYTIME  8L
#define SCVP_REPLY_STATUS_REFERENCECERTHASHFAIL    9L
#define SCVP_REPLY_STATUS_CERTPATHCONSTRUCTFAIL    10L
#define SCVP_REPLY_STATUS_CERTPATHNOTVALID         11L
#define SCVP_REPLY_STATUS_CERTPATHNOTVALIDNOW      12L

/*  ReplyObjects ::= SEQUENCE SIZE (1..MAX) OF CertReply 
 *     
 *  CertReply ::= SEQUENCE { 
 *    cert                       CertReference, 
 *    replyStatus                ReplyStatus, 
 *    replyValTime               GeneralizedTime, 
 *    replyChecks                ReplyChecks, 
 *    replyWantBacks             ReplyWantBacks, 
 *    valPolicy                  ValidationPolicy, 
 *    nextUpdate             [1] GeneralizedTime OPTIONAL, 
 *    certReplyExtensions    [2] Extensions OPTIONAL } 
 */

typedef struct scvp_cert_reply_st {
	SCVP_CERTREF *cert;
	ASN1_ENUMERATED *replyStatus;
	ASN1_GENERALIZEDTIME *replyValTime;
	STACK_OF(SCVP_REPLYCHECK) *replyChecks;
	STACK_OF(SCVP_REPLYWANTBACK) *replyWantBacks;
	SCVP_VALIDPOLICY *valPolicy;
	ASN1_GENERALIZEDTIME *nextUpdate;
	STACK_OF(X509_EXTENSION) *certReplyExtensions;
} SCVP_CERTREPLY;

DECLARE_STACK_OF(SCVP_CERTREPLY)

/*  HashValue ::= SEQUENCE { 
 *    algorithm             AlgorithmIdentifier DEFAULT { sha-1 }, 
 *    value                 OCTET STRING } 
 */

typedef struct scvp_hashvalue_st {
	X509_ALGOR *algorithm;
	ASN1_OCTET_STRING *value;
} SCVP_HASHVALUE;

/*  RequestReference ::= CHOICE { 
 *    requestHash       [1] HashValue, -- hash of CVRequest 
 *    fullRequest       [2] CVRequest } 
 */

#define V_SCVP_REQUEST_REFERENCE_REQUESTHASH  0
#define V_SCVP_REQUEST_REFERENCE_FULLREQUEST  1

typedef struct scvp_request_reference_st {
	int type;
	union {
		SCVP_HASHVALUE *requestHash;
		SCVP_REQUEST *fullRequest;
	} value;
} SCVP_REQUEST_REFERENCE;

/*  ResponseStatus ::= SEQUENCE {
 *    statusCode            SCVPStatusCode,
 *    errorMessage      [0] UTF8String OPTIONAL }
 * 
 *  SCVPStatusCode ::= ENUMERATED {
 *    okay                    (0),
 *    skipUnrecognizedItems   (1),
 *    tooBusy                (10),
 *    internalError          (12),
 *    badStructure           (20),
 *    unsupportedVersion     (21),
 *    abortUnrecognizedItems (22),
 *    unrecognizedSigKey     (23),
 *    badSignature           (24),
 *    unableToDecode         (25),
 *    notAuthorized          (26),
 *    unsupportedChecks      (27),
 *    unsupportedWantBacks   (28),
 *    unsupportedSignature   (29),
 *    invalidSignature       (30),
 *    relayingLoop           (40) }
 */

#define SCVP_STATUS_CODE_OKAY                    0L
#define SCVP_STATUS_CODE_SKIPUNRECOGNIZEDITEMS   1L
#define SCVP_STATUS_CODE_TOOBUSY                 10L
#define SCVP_STATUS_CODE_INTERNALERROR           12L
#define SCVP_STATUS_CODE_BADSTRUCTURE            20L
#define SCVP_STATUS_CODE_UNSUPPORTEDVERSION      21L
#define SCVP_STATUS_CODE_ABORTUNRECOGNIZEDITEMS  22L
#define SCVP_STATUS_CODE_UNRECOGNIZEDSIGKEY      23L
#define SCVP_STATUS_CODE_BADSIGNATURE            24L
#define SCVP_STATUS_CODE_UNABLETODECODE          25L
#define SCVP_STATUS_CODE_NOTAUTHORIZED           26L
#define SCVP_STATUS_CODE_UNSUPPORTEDCHECKS       27L
#define SCVP_STATUS_CODE_UNSUPPORTEDWANTBACKS    28L
#define SCVP_STATUS_CODE_UNSUPPORTEDSIGNATURE    29L
#define SCVP_STATUS_CODE_INVALIDSIGNATURE        30L
#define SCVP_STATUS_CODE_RELAYINGLOOP            40L

typedef struct scvp_response_status_st {
	ASN1_ENUMERATED *statusCode;
	ASN1_UTF8STRING *errorMessage;
} SCVP_RESPONSE_STATUS;

/*  CVResponse ::= SEQUENCE {
 *    scvpVersion           INTEGER,
 *    producedAt            GeneralizedTime,
 *    responseStatus        ResponseStatus,
 *    requestRef            RequestReference,
 *    requestor         [1] OCTET STRING OPTIONAL,
 *    responder         [2] OCTET STRING OPTIONAL,
 *    replyObjects      [3] ReplyObjects OPTIONAL,
 *    requestNonce      [4] OCTET STRING OPTIONAL,
 *    serverContextInfo [5] OCTET STRING OPTIONAL,
 *    respExtensions    [6] Extensions OPTIONAL }
 */

typedef struct scvp_response_st {
	ASN1_INTEGER *scvpVersion;
	ASN1_GENERALIZEDTIME *producedAt;
	SCVP_RESPONSE_STATUS *responseStatus;
	SCVP_REQUEST_REFERENCE *requestRef;
	ASN1_OCTET_STRING *requestor;
	ASN1_OCTET_STRING *responder;
	STACK_OF(SCVP_CERTREPLY) *replyObjects;
	ASN1_OCTET_STRING *requestNonce;
	ASN1_OCTET_STRING *serverContextInfo;
	STACK_OF(X509_EXTENSION) *respExtensions;
} SCVP_RESPONSE;
  
/* ===============================================
 */

#define PEM_STRING_SCVP_REQUEST "SCVP REQUEST"
#define PEM_STRING_SCVP_RESPONSE "SCVP RESPONSE"

DECLARE_ASN1_FUNCTIONS(SCVP_OTHERREVINFO)
DECLARE_ASN1_FUNCTIONS(SCVP_REVOCATIONINFO)
DECLARE_ASN1_FUNCTIONS(SCVP_REVOCATIONINFOS)
DECLARE_ASN1_FUNCTIONS(SCVP_VALIDPOLICY)
DECLARE_ASN1_FUNCTIONS(ESS_ISSUERSERIAL)
DECLARE_ASN1_FUNCTIONS(ESS_CERTID)
DECLARE_ASN1_FUNCTIONS(SCVP_ATTRIBUTECERT)
DECLARE_ASN1_FUNCTIONS(SCVP_PKCREF)
DECLARE_ASN1_FUNCTIONS(SCVP_ACREF)
DECLARE_ASN1_FUNCTIONS(SCVP_CERTREF)
DECLARE_ASN1_FUNCTIONS(SCVP_CERTBUNDLE)
DECLARE_ASN1_FUNCTIONS(SCVP_TRUSTANCHOR)
DECLARE_ASN1_FUNCTIONS(SCVP_QUERY)
DECLARE_ASN1_FUNCTIONS(SCVP_REQUEST)
DECLARE_ASN1_FUNCTIONS(SCVP_REPLYWANTBACK)
DECLARE_ASN1_FUNCTIONS(SCVP_REPLYCHECK)
DECLARE_ASN1_FUNCTIONS(SCVP_CERTREPLY)
DECLARE_ASN1_FUNCTIONS(SCVP_HASHVALUE)
DECLARE_ASN1_FUNCTIONS(SCVP_REQUEST_REFERENCE)
DECLARE_ASN1_FUNCTIONS(SCVP_RESPONSE_STATUS)
DECLARE_ASN1_FUNCTIONS(SCVP_RESPONSE)

#define d2i_SCVP_REQUEST_bio(bp,p) (SCVP_REQUEST *)ASN1_d2i_bio( \
		(char *(*)())SCVP_REQUEST_new, \
		(char *(*)())d2i_SCVP_REQUEST, (bp), \
		(unsigned char **)(p))

#define d2i_SCVP_RESPONSE_bio(bp,p) (SCVP_RESPONSE *)ASN1_d2i_bio( \
		(char *(*)())SCVP_RESPONSE_new, \
		(char *(*)())d2i_SCVP_RESPONSE, (bp), \
		(unsigned char **)(p))

#define i2d_SCVP_REQUEST_bio(bp,o) ASN1_i2d_bio(i2d_SCVP_REQUEST,bp, \
		(unsigned char *)o)

#define i2d_SCVP_RESPONSE_bio(bp,o) ASN1_i2d_bio(i2d_SCVP_RESPONSE,bp, \
		(unsigned char *)o)

#define SCVP_REQUEST_dup(sr)	(SCVP_REQUEST *)ASN1_dup( \
		(int (*)())i2d_SCVP_REQUEST, \
		(char *(*)())d2i_SCVP_REQUEST, (char *)sr)

#define SCVP_CERTREF_dup(cr)	(SCVP_CERTREF *)ASN1_dup( \
		(int (*)())i2d_SCVP_CERTREF, \
		(char *(*)())d2i_SCVP_CERTREF, (char *)cr)

#ifdef notyet

char *SCVP_response_status_str(long s);
char *SCVP_cert_status_str(long s);
char *SCVP_crl_reason_str(long s);

int SCVP_REQUEST_print(BIO *bp, SCVP_REQUEST* a, unsigned long flags);
int SCVP_RESPONSE_print(BIO *bp, SCVP_RESPONSE* o, unsigned long flags);

int SCVP_basic_verify(SCVP_RESPONSE *bs, STACK_OF(X509) *certs, 
		      X509_STORE *st, unsigned long flags);

#endif

#endif
