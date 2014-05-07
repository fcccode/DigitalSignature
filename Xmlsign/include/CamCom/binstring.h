/* $Id: binstring.h,v 1.1.1.2 2003/03/28 21:38:07 ken Exp $ */

/* Certificate Arbitration Module (CAM)
   (c) 1999 Mitretek Systems, Inc.

   GENERIC DATA-TYPE DEFINITIONS

*/

#ifndef _BINSTRING_H
#define _BINSTRING_H

/* ----------[ basic data types ]---------- */

typedef unsigned char uChar;

typedef unsigned int  uInt;

struct BinString {
  uInt  size;
  uChar *data;
};

#endif
