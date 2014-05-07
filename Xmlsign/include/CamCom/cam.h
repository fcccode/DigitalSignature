/* $Id: cam.h,v 1.19 2001/05/18 21:50:35 ken Exp $ */

/* Certificate Arbitration Module
   (c) 1999 Mitretek Systems
   
  This file contains data types used by both AA<->CAM and CAM<->CA communications 

*/

#ifndef _CAM_H
#define _CAM_H

/* include referenced types */
#include "generic.h"			/* for: BinString */
#include "crypto.h"				/* for: CryptoSigType */


/* ----------[ Message Types ]---------- */
/* message type determines structure type */

typedef unsigned char IdNum[8];			/* used as 64-bit identification number */

typedef enum {
	/* AA->CAM Request Messages */
	AA_VALIDATE				=0x0200, 
	AA_ADMIN				=0x0202,
	AA_MAINT				=0x0203,

	/* CAM->AA Response Messages */
	CAM_RESP_VALIDATE		=0x0300,
	CAM_RESP_ADMIN_LOG_QUERY=0x0320,
	CAM_RESP_ADMIN_GET_LOG	=0x0321,
	CAM_RESP_MAINT_STATUS	=0x0330,
	CAM_RESP_MAINT_CA_LIST	=0x0331,
	CAM_RESP_MAINT_ICL_LIST	=0x0332,

	/* CA Request Messages */
	CA_REQ_VALIDATE_CERT	=0x0001,	/* certificate validation request */
	CA_REQ_RETRY		=0x1000,		/* retry previous request */
	CA_REQ_CANCEL		=0x9000, 		/* cancel request (exceeded time allotment) */

	/* CA Response Messages */
	CA_RESP_VALIDATE_CERT	=0x0101, 	/* certificate validate response */

	cmt_FORCE_INT32         =0xffffffff	/* make sure enum uses 4-byte size */
} CamMessageType;

/* ----------[ Certificate Statuses ]---------- */

typedef enum { 
	CERT_VALID				=0x0000,
	CERT_REVOKED			=0x0001,
	CERT_EXPIRED			=0x0002,
	CERT_SUSPENDED			=0x0003,
	CERT_FAILED_VERIFICATION=0x0004,
	CERT_ISSUER_NOT_FOUND	=0x0005,	/* CA not registered in CAM~s routing table */
	CERT_NOT_PARSABLE		=0x0006,
	CA_SYSTEM_BUSY			=0x0007,
	CA_TIMEOUT				=0x0008,
	CA_CERT_UNKNOWN			=0x0009,	/* CA claims they did not issue this cert */
	CA_REQ_BAD				=0x000A,	/* comm or protocol problem between CAM and CA */
	CA_BAD_RESP_SIG			=0x000B,	/* invalid signature on CA response */

	CAM_ERROR				=0x00FF,	/* CAM INTERNAL ERROR */

	cvs_FORCE_INT32         =0xffffffff	/* make sure enum uses 4-byte size */
} CertValidationStatus;


/* ----------[ Certificate ACES-Profile check codes ]---------- */

#define CHK_WRONG_VERSION (1<<0)
#define CHK_NO_SERIAL (1<<1)
#define CHK_NO_SIG_ALG_ID (1<<2)
#define CHK_NO_ISSUER (1<<3)
#define CHK_NO_SUBJECT_CN (1<<4)
#define CHK_NO_SUBJECT_KEY_ALG (1<<5)
#define CHK_NO_PUBKEY (1<<6)
#define CHK_NO_KEYUSAGE (1<<8)
#define CHK_KEYUSAGE_NOT_CRITICAL (1<<9)
#define CHK_WRONG_KEYUSAGE (1<<10)
#define CHK_NO_BASIC_CONSTRAINTS (1<<11)
#define CHK_BASIC_CONSTRAINTS_NOT_CRITICAL (1<<12)
#define CHK_NO_POLICY_ID (1<<13)
#define CHK_WRONG_POLICY_ID (1<<14)

typedef __int32 AcesProfileCheckCode;


/* ----------[ Public Key Structure ]---------- */

typedef struct {
  CryptoSigType	public_key_type;		/* type of public key; see crypto.h */

  /* following fields are extracted from ca_cert to provide efficient access */
  BinString	part[4];					/* see below for usage */
} CamPublicKey;

#define CamPublicKeyBSC	4

/* use following "pkp_" shortcuts as indexes for part[] in CamPublicKey above */

/* 4 DSA parts: p=prime modulus; q=prime divisor; g=SS0-generated value; y=public key */
const int PKP_DSA_P 	= 0;
const int PKP_DSA_Q	= 1;
const int PKP_DSA_G	= 2;
const int PKP_DSA_Y	= 3;

/* 2 RSA parts: exponent, modulus */
const int PKP_RSA_EXPONENT	= 0;
const int PKP_RSA_MODULUS	= 1;

/* 3 DH parts: p=prime; g=base; y=public key*/
const int PKP_DH_P	= 0;
const int PKP_DH_G	= 1;
const int PKP_DH_Y	= 2;

/* note: unused parts should be set to empty BinStrings: {0, NULL} */


/* ----------[ CA Registration Data ]---------- */

/* This is the information transfered to and from the CAM during
   a CA registration process.
*/

typedef struct {
	BinString		val_method;		/* see below */

	BinString		ca_cert_cert;	/* cert that this CA's certs are signed with
										(presumably, but not necessarily, self-signed) */

	BinString		ca_comm_cert;	/* cert used to verify communication with the 
										CA validation mechanism.  len=0 => use ca_cert_cert */
} CaRegistration;

#define CaRegistrationBSC 3

/*
	currently understood forms for val_method:

	ocsp-noaia:http[s]://{responder name/IP}
		[ignore AIA field, always use OCSP validator at given URL]

    ocsp-aia:
		[always use OCSP with validator address given in AIA field]

	ocsp-tryaia:http[s]://{responder name/IP}
		[always use OCSP; use validator address in AIA field if available, otherwise given addr]

	cam:{responder name/IP}
		[always use CAM native-mode CA with responder at given hostname/IP #]
*/



// -------------------------------------------------
// DEPRECATED STRUCTURES
// -------------------------------------------------

// included here for use in automatic conversion/mappping routines
// (ca_db.hh, maint.cpp)

typedef struct {
	__int8			ca_ipnum[4];	/* IP number of the CA */
	BinString		ca_cert_cert;	/* root cert (self-signed) that CA uses for
										signing its certificates */
	BinString		ca_comm_cert;	/* root cert (self-signed) that CA uses for
										signing CA->CAM messages.  If sent with zero
										length, ca_cert_cert is used for both. */
} Old_CaRegistration;

#define Old_CaRegistrationBSC 2


#endif
