// $Id: cert.h,v 1.6 1999/06/28 18:31:00 stillson Exp $

/* Certificate Arbitration Module
   (c) 1999 Mitretek Systems

  CERTIFICATE OBJECT DATATYPES

*/
  
#ifndef _CERT_H
#define _CERT_H

// =====================================================================================
// CERT data types

#define CM_TIME_LEN 16						// borrowed from the CML: yyyymmddhhmmssZ[NULL]

typedef char CmTimeType[CM_TIME_LEN];		// borrowed from the CML: yyyymmddhhmmssZ[NULL]

typedef struct {
    char* oid;				/* pointer to extension type oid in dot notation */
    char critical;			/* Indicates whether the extension is critical */
    void *value;			/* Pointer to content-dependent type */
} CertExtension;
/* note: this type deliberately identical to the CML type: Extn_struct
   So that CAM can directly use CML parsed certs without including the 
   complicate CML type subsystem at the .h level */
	
// --------------------------------------------------
// VARIOUS STATUS AND STAGE INDICATORS:

typedef enum {
	CERT_PARSED,
	CERT_CHECKED,
	CERT_VERIFIED,
	CERT_VALIDATED,		// (not determined by cert object, must be set by caller)
	CERT_ERROR
} CertStage;

typedef enum {
	CHECK_OK,
	CHECK_EXPIRED
} CertCheckStatus;

typedef enum {
	VERIFY_CONFIRMED,
	VERIFY_FAILED,
	VERIFICATION_ERROR
} CertVerifyStatus;


#endif
