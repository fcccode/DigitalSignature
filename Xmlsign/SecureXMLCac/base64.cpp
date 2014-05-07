/****************************************************************************
 * File         base64.h
 * Author       Patrick Meier, patrick.meier@gmx.net
 * Date         10-11-2000
 * Last change  12-05-2000 / Patrick Meier
 * Description  moule to en- and decode a base64 coded string
 *
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
 * $Id: base64.c,v 1.1.1.1 2001/11/22 15:37:30 cvs Exp $ 
 ****************************************************************************
*/ 


/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <securexml/base64.h>

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/
#define conv_bin2ascii(a)	(data_bin2ascii[(a)&0x3f])
#define conv_ascii2bin(a)	(data_ascii2bin[(a)&0x7f])


/* 0xF0 is a EOLN
 * 0xF1 is ignore but next needs to be 0xF0 (for \r\n processing).
 * 0xF2 is EOF
 * 0xE0 is ignore at start of line.
 * 0xFF is error
 */
#define B64_EOLN		0xF0
#define B64_CR			0xF1
#define B64_EOF			0xF2
#define B64_WS			0xE0
#define B64_ERROR       	0xFF
#define B64_NOT_BASE64(a)	(((a)|0x13) == 0xF3)

	
/******************************************************************************/
/* STATIC STUFF                                                               */
/******************************************************************************/
static unsigned char data_bin2ascii[] ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static unsigned char data_ascii2bin[128]={
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xE0,0xF0,0xFF,0xFF,0xF1,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x3E,0xFF,0xF2,0xFF,0x3F,
	0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,
	0x3C,0x3D,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,
	0xFF,0x00,0x01,0x02,0x03,0x04,0x05,0x06,
	0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,
	0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,
	0x17,0x18,0x19,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
	0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,
	0x31,0x32,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,
	};


/**
 * base64encodeSize
 * @len: length of the decoded string
 *
 * Callculate the encode buffersize of a given length
 * Copyright (C) 2000 Patrick Meier
 *
 * Returns: length of the encoded string
 */
int base64encodeSize( unsigned int len )
{    
    /* callculate new string size */    
    if( len%3 ) 
        return (len/3+1)*4;
    else 
    	return (len/3)*4;
}


/**
 * base64encode
 * @src: string to encode
 * @dlen: length of the string
 * @target: encoded string 
 * @targsize: length of the buffer
 *
 * Encode a given string with base64
 * Copyright (C) 2000 Patrick Meier
 *
 * Returns: number of written characters (-1 on error)
 */

/*******************************************************************************
 
   (From RFC1521 and draft-ietf-dnssec-secext-03.txt)
   The following encoding technique is taken from RFC 1521 by Borenstein
   and Freed.  It is reproduced here in a slightly edited form for
   convenience.

   A 65-character subset of US-ASCII is used, enabling 6 bits to be
   represented per printable character. (The extra 65th character, "=",
   is used to signify a special processing function.)

   The encoding process represents 24-bit groups of input bits as output
   strings of 4 encoded characters. Proceeding from left to right, a
   24-bit input group is formed by concatenating 3 8-bit input groups.
   These 24 bits are then treated as 4 concatenated 6-bit groups, each
   of which is translated into a single digit in the base64 alphabet.

   Each 6-bit group is used as an index into an array of 64 printable
   characters. The character referenced by the index is placed in the
   output string.

                         Table 1: The Base64 Alphabet

      Value Encoding  Value Encoding  Value Encoding  Value Encoding
          0 A            17 R            34 i            51 z
          1 B            18 S            35 j            52 0
          2 C            19 T            36 k            53 1
          3 D            20 U            37 l            54 2
          4 E            21 V            38 m            55 3
          5 F            22 W            39 n            56 4
          6 G            23 X            40 o            57 5
          7 H            24 Y            41 p            58 6
          8 I            25 Z            42 q            59 7
          9 J            26 a            43 r            60 8
         10 K            27 b            44 s            61 9
         11 L            28 c            45 t            62 +
         12 M            29 d            46 u            63 /
         13 N            30 e            47 v
         14 O            31 f            48 w         (pad) =
         15 P            32 g            49 x
         16 Q            33 h            50 y

   Special processing is performed if fewer than 24 bits are available
   at the end of the data being encoded.  A full encoding quantum is
   always completed at the end of a quantity.  When fewer than 24 input
   bits are available in an input group, zero bits are added (on the
   right) to form an integral number of 6-bit groups.  Padding at the
   end of the data is performed using the '=' character.

 ******************************************************************************/
int base64encode( unsigned char *src, int dlen, unsigned char *target, int targsize )
{
    int i, ret=0;
    unsigned long l;

    if(!target || !src || dlen<=0)
        return -1;

    for(i=dlen; i > 0; i-=3)
    {
        if(i>=3)
        {
            l=(((unsigned long)src[0])<<16L)|
               (((unsigned long)src[1])<< 8L)|src[2];
               
            *(target++)=conv_bin2ascii(l>>18L);
            *(target++)=conv_bin2ascii(l>>12L);
            *(target++)=conv_bin2ascii(l>> 6L);
            *(target++)=conv_bin2ascii(l     );
        }
        else
        {
            l=((unsigned long)src[0])<<16L;
            
            if(i==2) l|=((unsigned long)src[1]<<8L);

            *(target++)=conv_bin2ascii(l>>18L);
            *(target++)=conv_bin2ascii(l>>12L);
            *(target++)=(i == 1)?'=':conv_bin2ascii(l>> 6L);
            *(target++)='=';
        }
        
        ret+=4;
        src+=3;
        
        if(ret>targsize)
            return -1;
    }

    *target='\0';
    return ret;
}


/**
 * base64decodeSize
 * @len: length of the encoded string
 *
 * Callculate the decode buffersize of a given length
 * Copyright (C) 2000 Patrick Meier
 *
 * Returns: length of the decoded string
 */
int base64decodeSize( unsigned int len )
{    
    /* callculate new string size */    
    if( len%4 ) 
        return (len/4+1)*3;
    else 
    	return (len/4)*3;
}


/**
 * base64decode
 * @src: base64 coded string to decode
 * @target: decoded string 
 * @targsize: length of the buffer
 *
 * Decode a given string with base64
 * Copyright (C) 2000 Patrick Meier
 *
 * Returns: number of written characters (-1 on error)
 */

#if 0
int base64decode( unsigned char *src, unsigned char *target, int targsize )
{
    int i,ret=0,a,b,c,d;
    int dlen=0;
    unsigned long l;

	if (!src) return -1;
    dlen=strlen((char*)src);
    if(!target || !src || dlen<=0 || targsize<=0)
        return -1;

    /* trim white space from the start of the line. */
    while((conv_ascii2bin(*src)==B64_WS) && (dlen > 0))
    {
        src++;
        dlen--;
    }

    /* strip off stuff at the end of the line
     * ascii2bin values B64_WS, B64_EOLN, B64_EOLN and B64_EOF */
    while((dlen > 3) && (B64_NOT_BASE64(conv_ascii2bin(src[dlen-1]))))
        dlen--;

    if(dlen%4!=0) 
        return(-1);

    for(i=0; i<dlen; i+=4)
    {
        a=conv_ascii2bin(*(src++));
        b=conv_ascii2bin(*(src++));
        c=conv_ascii2bin(*(src++));
        d=conv_ascii2bin(*(src++));
	
        if (    (a & 0x80) || (b & 0x80) ||
                (c & 0x80) || (d & 0x80))
            return(-1);
            
        l=(    (((unsigned long)a)<<18L)|
               (((unsigned long)b)<<12L)|
               (((unsigned long)c)<< 6L)|
               (((unsigned long)d)     ));
               
        *(target++)=(unsigned char)(l>>16L)&0xff;
        *(target++)=(unsigned char)(l>> 8L)&0xff;
        *(target++)=(unsigned char)(l     )&0xff;
        ret+=3;
        
        if(ret>targsize)
            return -1;        
    }
    return --ret;
}
#endif

int base64decode(unsigned char *intext, unsigned char *out, int targsize)
{
    unsigned char ibuf[4];
    unsigned char obuf[3];
    char ignore;
    char endtext = FALSE;
    char ch;
    int lindex = 0;
    int length = 0;
	int dlen;

	if (!intext) return -1;
    dlen=strlen((char*)intext);
    if(!out || !intext || dlen<=0 || targsize<=0)
        return -1;

    
	memset(ibuf, 0, sizeof(ibuf));

    while (*intext) {
	ch = *intext;

	if (endtext)
		break;

	ignore = FALSE;
	if ((ch >= 'A') && (ch <= 'Z'))
	    ch = ch - 'A';
	else if ((ch >= 'a') && (ch <= 'z'))
	    ch = ch - 'a' + 26;
	else if ((ch >= '0') && (ch <= '9'))
	    ch = ch - '0' + 52;
	else if (ch == '+')
	    ch = 62;
	else if (ch == '=') {	/* end of text */
	    if (endtext)
		break;
	    endtext = TRUE;
	    lindex--;
	    if (lindex < 0)
		lindex = 3;
	}
	else if (ch == '/')
	    ch = 63;
	else if (endtext)
	    break;
	else
	    ignore = TRUE;

	if (!ignore) {
	    if (!endtext) {
		ibuf[lindex] = ch;

		lindex++;
		lindex &= 3;	/* use bit arithmetic instead of remainder */
	    }
	    if ((0 == lindex) || endtext) {

		obuf[0] = (ibuf[0] << 2) | ((ibuf[1] & 0x30) >> 4);
		obuf[1] =
		    ((ibuf[1] & 0x0F) << 4) | ((ibuf[2] & 0x3C) >> 2);
		obuf[2] = ((ibuf[2] & 0x03) << 6) | (ibuf[3] & 0x3F);

		switch (lindex) {
		case 1:
		    sprintf((char *)out, "%c", obuf[0]);
		    out++;
		    length++;
		    break;
		case 2:
		    sprintf((char *)out, "%c%c", obuf[0], obuf[1]);
		    out += 2;
		    length += 2;
		    break;
		default:
		    sprintf((char *)out, "%c%c%c", obuf[0], obuf[1], obuf[2]);
		    out += 3;
		    length += 3;
		    break;
		}
		memset(ibuf, 0, sizeof(ibuf));
	    }
	}
	intext++;
    }
	return length;
}


/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

