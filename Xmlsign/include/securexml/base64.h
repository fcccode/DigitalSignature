/****************************************************************************
 * Copyright (C) 2000 Patrick Meier
 *
 ****************************************************************************
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 *
 ****************************************************************************
 * $Id: base64.h,v 1.1.1.1 2001/11/22 15:37:30 cvs Exp $ 
 ****************************************************************************
*/ 


/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/
#ifndef __BASE64_H__
#define __BASE64_H__

#if defined WIN32 || defined __powerpc__
#if __cplusplus
extern "C" {
#endif
#endif

int base64encodeSize( unsigned int len );
int base64encode( unsigned char *src, int dlen, unsigned char *target, int targsize );
int base64decodeSize( unsigned int len );
int base64decode( unsigned char *src, unsigned char *target, int targsize );

#if defined WIN32 || defined __powerpc__
#if __cplusplus
}
#endif
#endif

#endif
/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

