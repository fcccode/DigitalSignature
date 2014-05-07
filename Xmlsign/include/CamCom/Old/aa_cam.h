/* $Id: aa_cam.h,v 1.21 2001/05/18 21:50:13 ken Exp $ */

/* Certificate Arbitration Module
   (c) 1999 Mitretek Systems
   
   COMMUNICATION STRUCTURES BETWEEN THE AA AND THE CAM (both directions)
*/

#ifndef _AA_CAM_H
#define _AA_CAM_H

// include referenced datatypes
#include "cam.h"
#include "icl.h"

#define AA_CAM_PORT 7777


/* ------------------------------------------------------------------ */
/* VALIDATION REQUEST */

typedef struct {
	CamMessageType	msg_type;		// __int32: must be AA_VALIDATE
	BinString		aa_id;			// who is to be billed
	BinString		cert;			// certificate to be validated
} AaCamValidate;

#define AaCamValidateBSC 2			// BinString count

/* ------------------------------------------------------------------ */
/* VALIDATION RESPONSE */

typedef struct {
	CamMessageType			msg_type;		//__int32: must be CAM_RESP_VALIDATE
	CertValidationStatus	status;			// __int32
	AcesProfileCheckCode	aces_check_code;// __int32
	BinString				cert_ascii;
	BinString				ca_signed_msg;
} CamAaValidate;

#define CamAaValidateBSC 2


/* ------------------------------------------------------------------ */
/* ADMINISTRATIVE REQUESTs */

typedef enum {	QUERY_LOG,
				GET_LOG,

				at_FORCE_INT32 = 0xffffffff		/* make sure enum uses 4-byte size */
			} AdminType;

typedef struct {
	CamMessageType	msg_type;		// __int32: must be AA_ADMIN
	AdminType		command;		// __int32: (above)
	BinString		param;			// contains serialized version of 
									// one of the param structs (below)
} AaCamAdmin;

#define AaCamAdminBSC 1


// -----------------------------------
// ADMIN REQUEST PARAMETER TYPES:

// -------------
// for QUERY_LOG:

// no param: send BinString as { 0, NULL }


// -------------
// for GET_LOG:

typedef struct {
	char			start_date[11];	// format: mm/dd/yyyy[NULL] of first entry to retieve.
									// send mm=00 to remove constraint
	char			end_date[11];	// as above for last entry to retrieve
	__int16			limit;			// number of lines to retieve max, 0 => no limit
	char			get_normal,		// retrieve non-error log messages? 
					get_error,		// retrieve recoverable error log messages?
					get_fatal;		// retrieve fatal error log messages?
} AaCamAdmin_GetLog;

#define AaCamAdmin_GetLogBSC 0

/* ------------------------------------------------------------------ */
/* ADMINISTRATIVE RESPONSES */

// --------------
// For QUERY_LOG

typedef struct {
	CamMessageType	msg_type;		//__int32: must be CAM_RESP_ADMIN_LOG_QUERY
	char			start_date[11];	// format: mm/dd/yyyy[NULL] of first entry available
	char			end_date[11];	// as above, for date of last entry available
	__int16			lines_normal,	// line counts for messages of various types
					lines_error,
					lines_fatal;
} CamAaAdmin_QueryLog;

#define CamAaAdmin_QueryLogBSC 0


// --------------
// For GET_LOG

typedef struct {
	CamMessageType			msg_type;		//__int32: must be CAM_RESP_ADMIN_LOG
} CamAaAdmin_GetLog;

#define CamAaAdmin_GetLogBSC 0

// The above header will be followed by a series of text lines 
// Each line is from the log, in the order recorded
// The series is ended with an empty line


/* ------------------------------------------------------------------ */
/* MAINTENANCE REQUESTs */

typedef enum { deprecated1_ADD_CA		=0x0,	// deprecated, see below
			   DEL_CA					=0x1,
			   deprecated1_SEARCH_CA_DB	=0x2,	// deprecated, see below
			   deprecated1_LIST_CA_DB	=0x3,	// deprecated, see below
			   CLEAR_CA_DB				=0x4,

			   ADD_ICL					=0x5,
			   DEL_ICL					=0x6,
			   SEARCH_ICL				=0x7,
			   LIST_ICL					=0x8,
			   CLEAR_ICL				=0x9,

			   // ----------------------------------------------------
			   // special debugging / internal-maintenance commands

			   INTERNAL_MEMORY_CHECK	=0xa,	// log memory consumed since startup
			   INTERNAL_MEMORY_REPORT	=0xb,	// log detailed memory usage report
												// (only works if compiled in _DEBUG mode)
			   CAM_RESET				=0xc,
			   CAM_SHUTDOWN				=0xd,

			   // -----------------------------------------------------
			   // replacement/updated commands

			   ADD_CA					=0xe,
			   SEARCH_CA_DB				=0xf,
			   LIST_CA_DB				=0x10,
			   

			   mt_FORCE_INT32 =0xffffffff	/* make sure enum uses 4-byte size */
			 } MaintType;

typedef struct {
	CamMessageType	msg_type;		// __int32: must be AA_MAINT
	MaintType		command;		// __int32: see above
	BinString		param;			// contains serialized version of 
									// one of the param structs (below)
} AaCamMaint;

#define AaCamMaintBSC 1


// -----------------------------------
// MAINT REQUEST PARAMETER TYPES:

// -------------
// For ADD_CA:

//
// deprecated COMAMND NOTE:
// In CAM version 3.4, maint command 0x0 was deprecated;
// it used a previous formumaltion of the stuct CaRegistration
// which hardcoded a four-byte IP number for the CA address
// (see ca_db.h for struct Old_CaRegistration)
//
// The new version (as defined in cam.h) passes an extended
// uri-like validation method binstring, and should be passed
// with maint command 0xe

typedef CaRegistration AaCamMaint_AddCa;

#define AaCamMaint_AddCaBSC CaRegistrationBSC


// -------------
// For DEL_CA
// and SEARCH_CA_DB
//
// param is a certificate containing the issuer_id string

//
// deprecated COMAMND NOTE:
// In CAM version 3.4, maint commands 0x2 and 0x3 were deprecated;
// The format of the request has not changed, but the format the
// client must be able to parse has.  See response section for details.


// -------------
// For LIST_CA_DB
// and CLEAR_CA_DB

// no param: send BinString as { 0, NULL }


// --------------
// for ADD_ICL:

typedef struct {
	CertValidationStatus	reason;
	BinString				certificate;
	BinString				aa_signed_authorization;
} AaCamMaint_AddIcl;

#define AaCamMaint_AddIclBSC 2


// -------------
// For DEL_ICL
// and SEARCH_ICL

// param is a certificate containing the certificate sought


// --------------
// For LIST_ICL
// and CLEAR_ICL

// no param: send BinString as { 0, NULL }


/* ------------------------------------------------------------------ */
/* MAINTENANCE RESPONSES */

// -------------
// For ADD_CA
// and DEL_CA
// and CLEAR_CA
// and ADD_ICL
// and DEL_ICL
// and CLEAR_ICL

typedef enum {
	MAINT_CMND_COMPLETED, 
	MAINT_CMND_ERROR,

	ms_FORCE_INT32 =0xffffffff			/* make sure enum uses 4-byte size */
} MaintStatus;

typedef struct {
	CamMessageType		msg_type;		//__int32: must be CAM_RESP_MAINT_STATUS
	MaintStatus			status;			// see above
} CamAaMaint_Status;

#define CamAaMaint_StatusBSC 0


// -------------
// For SEARCH_CA
// and LIST_CA

//
// deprecated COMAMND NOTE:
// Old requests 0x2 and 0x3 respponded with a single CamAaMaint_CaList, and
// then a dump of the appropriate number of CaRegistration~s.
// 
// This response format is now deprecated in-favor of the following, where
// a single CamAaMaint_CaList is followed by the appripriate number of
// CamAaMaint_CaEntry structures.  This exposes the DN of each CA~s
// subject field without requiring certificate parsing at the maint client
//
// When a client sends the new request codes (0xf and 0x10), it indicates
// they understand how to parse the new response formats


// CAM will reply with a single CAM_RESP_MAINT_CA_LIST message,
// followed by the number of serialized CamAaMaint_CaEntry~s indicated

typedef struct {
	CamMessageType	msg_type;	//__int32: must be CAM_RESP_MAINT_CA_LIST
	__int16			count;		// number of serialized CaRegistration structs to follow
} CamAaMaint_CaList;

#define CamAaMaint_CaListBSC 0

typedef struct {
	CaRegistration	ca;		// contains transition from non-binsting to binstring
	BinString		dn;		// DN of ca, parsed out for ease of use by client
} CamAaMaint_CaEntry;

#define CamAaMaint_CaEntryBSC (1+CaRegistrationBSC)



// --------------
// and SEARCH_ICL
// and LIST_CA

// CAM will reply with a single CAM_RESP_MAINT_ICL_LIST message,
// followed by the number of serialized IclData~s indicated by the _LIST message

typedef struct {
	CamMessageType	msg_type;	//__int32: must be CAM_RESP_MAINT_ICL_LIST
	__int16			count;		// number of serialized IclData structs to follow
} CamAaMaint_IclList;

#define CamAaMaint_IclListBSC 0

#endif
