// $Id: icl.h,v 1.8 1999/06/28 18:31:00 stillson Exp $

/* Certificate Arbitration Module
   (c) 1999 Mitretek Systems

  INVALID VERTIFICATE LIST DATATYPES
*/
  
#ifndef _ICL_H
#define _ICL_H

// include used datatypes
#include "cam.h"
#include "cert.h"
#include "generic.h"

// -----------------------------------------
// ICL DATA TYPE

typedef struct {
	CertValidationStatus reason;
	CmTimeType			 entry_date;		// format: yyyymmddhhmmssZ[NULL]
	CmTimeType			 cert_expire_date;
	BinString			 serial_id;			// primary key part 1
	BinString			 issuer_id;			// primary key part 2
	BinString			 ca_signed_msg;
} IclData;

#define IclDataBSC 3


// -----------------------------------------
// PRIVATE INTERNAL ICL TYPES

#define IclKeyLen 512

typedef unsigned char IclKey[IclKeyLen];

typedef struct {
	IclKey key;
	IclData data;
} IclType;

#define IclTypeBSC IclDataBSC

#endif
