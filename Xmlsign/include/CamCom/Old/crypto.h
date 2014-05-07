/* $Id: crypto.h,v 1.8 2001/09/04 20:56:24 ken Exp $ */

/* Certificate Arbitration Module (CAM)
   (c) 1999 Mitretek Systems, Inc.

   THE CRYPTOGRAPHIC OBJECT
   (see "crypto.hpp" for overview documentation)
   */

#ifndef _CRYPTO_H
#define _CRYPTO_H

/* -----[ switches ]----- */

/* CAM release version 3.0: RSABSAFE is now the default crypto module */

/*#define CERTICOM_IS_AVAILABLE*/
// #define RSABSAFE_IS_AVAILABLE
/*#define RSAREF20_IS_AVAILABLE*/
#define MSCAPI_IS_AVAILABLE

/*----------[ crypto data types ]----------*/

/* what caller needs to know about signature */
typedef enum {
  SIG_OK	= 0x00,		/* signature generated ok */
  SIG_BAD_SIG,			/* signature did not verify */
  SIG_UNKNOWN_OID,		/* unable to translate OID string to hash/sig algorithms */
  SIG_NO_HASH_ALGO,		/* hash algorithm not available */
  SIG_NO_SIG_ALGO,		/* signature algorithm not available */
  SIG_UNKNOWN_SIG_SIZE		/* can~t determine signature size by context */
} SigStatus;

/* hashing algorithms types (only last octet is non-zero) */
const static int CAM_HA_MASK	= 0x00FF;
typedef enum {
  CAM_HA_UNKNOWN= 0x0000,	/* couldn~t understand cert~s signature OID string */
  CAM_HA_MD2	= 0x0002,
  CAM_HA_MD4	= 0x0004,
  CAM_HA_MD5	= 0x0005,
  CAM_HA_SHA1	= 0x0001,
  CAM_HA_SIG_ONLY	= 0x0040,	/* OID specifies only signature algorithm, not hash algorithm */
  CAM_HA_UNSUPPORTED	= 0x0041	/* OID is known, but unsupported */
} CryptoHashType;

/* signature algorithm types (last octet must be zero */
const static int CAM_SA_MASK	= 0xFF00;
typedef enum {
  CAM_SA_UNKNOWN= 0x0000,	/* couldn~t understand cert~s signature OID string */
  CAM_SA_DSA	= 0x0100,
  CAM_SA_RSA	= 0x0200,
  CAM_SA_DES_CBC	= 0x0300,
  CAM_SA_ECDSA_cx= 0x1000,	/* curve x */
  CAM_SA_ECDSA_cy= 0x1100,	/* curve y */
  CAM_SA_ECDSA_cz= 0x1200,	/* curve z (these will be corrected later) */
  CAM_SA_HASH_ONLY	= 0x4000,	/* OID specifies only hasing algorithm, not signature algorithm */
  CAM_SA_UNSUPPORTED	= 0x4100	/* OID is known, but unsupported */
} CryptoSigType;

typedef struct {
  CryptoHashType hash;
  CryptoSigType  sig;
} CryptoSigSpec;

#endif
