/*
 *BSI.h
 */

/******************************************************************
 
            Title  : BSI.h
            Package: BSI
            Author : Del Putnam (dputnam@sympagic.com)
            Date   : 08/09/2002
            License: Proprietary

			Copyright © 2002 The MITRE Corporation

            Purpose: Includes definitions, types, and function
					 protptypes for a BSI module based on the
					 GSC-IS through version 2.0

			Notes:	 Some type names, type definitions, and function
					 definitions have changec between the GSC-IS v2.0
					 and the GSC-IS v1.8.  These header files have
					 been designed to work with both versions.  Where
					 necessary, identifiers have been defined to
					 allow for compatibility.  
					 
					 To ensure that the correct types and function
					 definitions are included, application developers
					 should define the identifier GSC_2_0 when using
					 these headers with BSI libraries based on the
					 GSC-IS v2.0
 
********************************************************************/

#ifndef __BSI_H__
#define __BSI_H__

/*
 * BSI Definitions
 */
#include "BSId.h"

/*
 * BSI Types
 */
#include "BSIt.h"

/*
 * BSI Functions
 */
//#include "BSIf.h"

#endif /*__BSI_H__*/