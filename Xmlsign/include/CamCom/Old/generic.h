/* $Id: generic.h,v 1.6 2001/01/22 14:49:15 ken Exp $ */

/* Certificate Arbitration Module (CAM)
   (c) 1999 Mitretek Systems, Inc.

   GENERIC DATA-TYPE DEFINITIONS

*/

#ifndef _GENERIC_H
#define _GENERIC_H

/* ----------[ basic data types ]---------- */

typedef unsigned char uChar;

typedef unsigned int  uInt;

struct BinString {
  uInt  size;
  uChar *data;
};
/* ----------[ debugging aids ]---------- */
#define DIE	die(__LINE__);
void die(int line_number);

#endif
