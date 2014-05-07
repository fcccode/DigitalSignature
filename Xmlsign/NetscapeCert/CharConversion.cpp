#include "StdAfx.h"

#include <securexml/CharConversion.h>
#include <securexml/DebugLog.h>

#ifndef WIN32
#include <time.h>
#endif

#ifdef __powerpc__
static int xmlLittleEndian = 0;
#else
static int xmlLittleEndian = 1;
#endif

void FileEncoding(unsigned char *ptr)
{
	if (xmlLittleEndian)
	{
		*ptr = 0xFF;
		*(ptr + 1) = 0xFE;
	}
	else
	{
		*ptr = 0xFE;
		*(ptr + 1) = 0xFF;
	}
}

void PrintBstr(BSTR bstr)
{
        int len = SysStringLen(bstr);
        printf("%d :", len);
        unsigned char *str = HeapW2A(bstr);
        printf("%s\n", str);
        zFree(str);
}


/**
 * UTF16LEToUTF8:
 * @out:  a pointer to an array of bytes to store the result
 * @outlen:  the length of @out
 * @inb:  a pointer to an array of UTF-16LE passed as a byte array
 * @inlenb:  the length of @in in UTF-16LE chars
 *
 * Take a block of UTF-16LE ushorts in and try to convert it to an UTF-8
 * block of chars out. This function assume the endian property
 * is the same between the native type of this machine and the
 * inputed one.
 *
 * Returns the number of byte written, or -1 by lack of space, or -2
 *     if the transcoding fails (for *in is not valid utf16 string)
 *     The value of *inlen after return is the number of octets consumed
 *     as the return value is positive, else unpredictable.
 */
int UTF16LEToUTF8(unsigned char* out, int *outlen,
            const unsigned char* inb, int *inlenb)
{
    unsigned char* outstart = out;
    const unsigned char* processed = inb;
    unsigned char* outend = out + *outlen;
    unsigned short* in = (unsigned short*) inb;
    unsigned short* inend;
    unsigned int c, d, inlen;
    unsigned char *tmp;
    int bits;

    if ((*inlenb % 2) == 1)
        (*inlenb)--;
    inlen = *inlenb / 2;
    inend = in + inlen;
    while ((in < inend) && (out - outstart + 5 < *outlen)) {
        if (xmlLittleEndian) {
	    c= *in++;
	} else {
	    tmp = (unsigned char *) in;
	    c = *tmp++;
	    c = c | (((unsigned int)*tmp) << 8);
	    in++;
	}
        if ((c & 0xFC00) == 0xD800) {    /* surrogates */
	    if (in >= inend) {           /* (in > inend) shouldn't happens */
		break;
	    }
	    if (xmlLittleEndian) {
		d = *in++;
	    } else {
		tmp = (unsigned char *) in;
		d = *tmp++;
		d = d | (((unsigned int)*tmp) << 8);
		in++;
	    }
            if ((d & 0xFC00) == 0xDC00) {
                c &= 0x03FF;
                c <<= 10;
                c |= d & 0x03FF;
                c += 0x10000;
            }
            else {
		*outlen = out - outstart;
		*inlenb = processed - inb;
	        return(-2);
	    }
        }

	/* assertion: c is a single UTF-4 value */
        if (out >= outend)
	    break;
        if      (c <    0x80) {  *out++=  c;                bits= -6; }
        else if (c <   0x800) {  *out++= ((c >>  6) & 0x1F) | 0xC0;  bits=  0; }
        else if (c < 0x10000) {  *out++= ((c >> 12) & 0x0F) | 0xE0;  bits=  6; }
        else                  {  *out++= ((c >> 18) & 0x07) | 0xF0;  bits= 12; }
 
        for ( ; bits >= 0; bits-= 6) {
            if (out >= outend)
	        break;
            *out++= ((c >> bits) & 0x3F) | 0x80;
        }
	processed = (const unsigned char*) in;
    }
    *outlen = out - outstart;
    *inlenb = processed - inb;
    return(0);
}

/**
 * UTF8ToUTF16LE:
 * @outb:  a pointer to an array of bytes to store the result
 * @outlen:  the length of @outb
 * @in:  a pointer to an array of UTF-8 chars
 * @inlen:  the length of @in
 *
 * Take a block of UTF-8 chars in and try to convert it to an UTF-16LE
 * block of chars out.
 *
 * Returns the number of byte written, or -1 by lack of space, or -2
 *     if the transcoding failed. 
 */
int UTF8ToUTF16LE(unsigned char* outb, int *outlen,
            const unsigned char* in, int *inlen)
{
    unsigned short* out = (unsigned short*) outb;
    const unsigned char* processed = in;
    const unsigned char *const instart = in;
    unsigned short* outstart= out;
    unsigned short* outend;
    const unsigned char* inend= in+*inlen;
    unsigned int c, d;
    int trailing;
    unsigned char *tmp;
    unsigned short tmp1, tmp2;

    if (in == NULL) {
        /*
	 * initialization, add the Byte Order Mark
	 */
        if (*outlen >= 2) {
	    outb[0] = 0xFF;
	    outb[1] = 0xFE;
	    *outlen = 2;
	    *inlen = 0;
	    return(2);
	}
	*outlen = 0;
	*inlen = 0;
	return(0);
    }
    outend = out + (*outlen / 2);
    while (in < inend) {
      d= *in++;
      if      (d < 0x80)  { c= d; trailing= 0; }
      else if (d < 0xC0) {
          /* trailing byte in leading position */
	  *outlen = (out - outstart) * 2;
	  *inlen = processed - instart;
	  return(-2);
      } else if (d < 0xE0)  { c= d & 0x1F; trailing= 1; }
      else if (d < 0xF0)  { c= d & 0x0F; trailing= 2; }
      else if (d < 0xF8)  { c= d & 0x07; trailing= 3; }
      else {
        /* no chance for this in UTF-16 */
	*outlen = (out - outstart) * 2;
	*inlen = processed - instart;
	return(-2);
      }

      if (inend - in < trailing) {
          break;
      } 

      for ( ; trailing; trailing--) {
          if ((in >= inend) || (((d= *in++) & 0xC0) != 0x80))
	      break;
          c <<= 6;
          c |= d & 0x3F;
      }

      /* assertion: c is a single UTF-4 value */
        if (c < 0x10000) {
            if (out >= outend)
	        break;
	    if (xmlLittleEndian) {
		*out++ = c;
	    } else {
		tmp = (unsigned char *) out;
		*tmp = c ;
		*(tmp + 1) = c >> 8 ;
		out++;
	    }
        }
        else if (c < 0x110000) {
            if (out+1 >= outend)
	        break;
            c -= 0x10000;
	    if (xmlLittleEndian) {
		*out++ = 0xD800 | (c >> 10);
		*out++ = 0xDC00 | (c & 0x03FF);
	    } else {
		tmp1 = 0xD800 | (c >> 10);
		tmp = (unsigned char *) out;
		*tmp = (unsigned char) tmp1;
		*(tmp + 1) = tmp1 >> 8;
		out++;

		tmp2 = 0xDC00 | (c & 0x03FF);
		tmp = (unsigned char *) out;
		*tmp  = (unsigned char) tmp2;
		*(tmp + 1) = tmp2 >> 8;
		out++;
	    }
        }
        else
	    break;
	processed = in;
    }
    *outlen = (out - outstart) * 2;
    *inlen = processed - instart;
    return(0);
}

/**
 * UTF16BEToUTF8:
 * @out:  a pointer to an array of bytes to store the result
 * @outlen:  the length of @out
 * @inb:  a pointer to an array of UTF-16 passwd as a byte array
 * @inlenb:  the length of @in in UTF-16 chars
 *
 * Take a block of UTF-16 ushorts in and try to convert it to an UTF-8
 * block of chars out. This function assume the endian property
 * is the same between the native type of this machine and the
 * inputed one.
 *
 * Returns the number of byte written, or -1 by lack of space, or -2
 *     if the transcoding fails (for *in is not valid utf16 string)
 * The value of *inlen after return is the number of octets consumed
 *     as the return value is positive, else unpredictable.
 */
static int
UTF16BEToUTF8(unsigned char* out, int *outlen,
            const unsigned char* inb, int *inlenb)
{
    unsigned char* outstart = out;
    const unsigned char* processed = inb;
    unsigned char* outend = out + *outlen;
    unsigned short* in = (unsigned short*) inb;
    unsigned short* inend;
    unsigned int c, d, inlen;
    unsigned char *tmp;
    int bits;

    if ((*inlenb % 2) == 1)
        (*inlenb)--;
    inlen = *inlenb / 2;
    inend= in + inlen;
    while (in < inend) {
	if (xmlLittleEndian) {
	    tmp = (unsigned char *) in;
	    c = *tmp++;
	    c = c << 8;
	    c = c | (unsigned int) *tmp;
	    in++;
	} else {
	    c= *in++;
	} 
        if ((c & 0xFC00) == 0xD800) {    /* surrogates */
	    if (in >= inend) {           /* (in > inend) shouldn't happens */
		*outlen = out - outstart;
		*inlenb = processed - inb;
	        return(-2);
	    }
	    if (xmlLittleEndian) {
		tmp = (unsigned char *) in;
		d = *tmp++;
		d = d << 8;
		d = d | (unsigned int) *tmp;
		in++;
	    } else {
		d= *in++;
	    }
            if ((d & 0xFC00) == 0xDC00) {
                c &= 0x03FF;
                c <<= 10;
                c |= d & 0x03FF;
                c += 0x10000;
            }
            else {
		*outlen = out - outstart;
		*inlenb = processed - inb;
	        return(-2);
	    }
        }

	/* assertion: c is a single UTF-4 value */
        if (out >= outend) 
	    break;
        if      (c <    0x80) {  *out++=  c;                bits= -6; }
        else if (c <   0x800) {  *out++= ((c >>  6) & 0x1F) | 0xC0;  bits=  0; }
        else if (c < 0x10000) {  *out++= ((c >> 12) & 0x0F) | 0xE0;  bits=  6; }
        else                  {  *out++= ((c >> 18) & 0x07) | 0xF0;  bits= 12; }
 
        for ( ; bits >= 0; bits-= 6) {
            if (out >= outend) 
	        break;
            *out++= ((c >> bits) & 0x3F) | 0x80;
        }
	processed = (const unsigned char*) in;
    }
    *outlen = out - outstart;
    *inlenb = processed - inb;
    return(0);
}

/**
 * UTF8ToUTF16BE:
 * @outb:  a pointer to an array of bytes to store the result
 * @outlen:  the length of @outb
 * @in:  a pointer to an array of UTF-8 chars
 * @inlen:  the length of @in
 *
 * Take a block of UTF-8 chars in and try to convert it to an UTF-16BE
 * block of chars out.
 *
 * Returns the number of byte written, or -1 by lack of space, or -2
 *     if the transcoding failed. 
 */
static int
UTF8ToUTF16BE(unsigned char* outb, int *outlen,
            const unsigned char* in, int *inlen)
{
    unsigned short* out = (unsigned short*) outb;
    const unsigned char* processed = in;
    const unsigned char *const instart = in;
    unsigned short* outstart= out;
    unsigned short* outend;
    const unsigned char* inend= in+*inlen;
    unsigned int c, d;
    int trailing;
    unsigned char *tmp;
    unsigned short tmp1, tmp2;

    if (in == NULL) {
        /*
	 * initialization, add the Byte Order Mark
	 */
        if (*outlen >= 2) {
	    outb[0] = 0xFE;
	    outb[1] = 0xFF;
	    *outlen = 2;
	    *inlen = 0;
#ifdef DEBUG_ENCODING
            xmlGenericError(xmlGenericErrorContext,
		    "Added FEFF Byte Order Mark\n");
#endif
	    return(2);
	}
	*outlen = 0;
	*inlen = 0;
	return(0);
    }
    outend = out + (*outlen / 2);
    while (in < inend) {
      d= *in++;
      if      (d < 0x80)  { c= d; trailing= 0; }
      else if (d < 0xC0)  {
          /* trailing byte in leading position */
	  *outlen = out - outstart;
	  *inlen = processed - instart;
	  return(-2);
      } else if (d < 0xE0)  { c= d & 0x1F; trailing= 1; }
      else if (d < 0xF0)  { c= d & 0x0F; trailing= 2; }
      else if (d < 0xF8)  { c= d & 0x07; trailing= 3; }
      else {
          /* no chance for this in UTF-16 */
	  *outlen = out - outstart;
	  *inlen = processed - instart;
	  return(-2);
      }

      if (inend - in < trailing) {
          break;
      } 

      for ( ; trailing; trailing--) {
          if ((in >= inend) || (((d= *in++) & 0xC0) != 0x80))  break;
          c <<= 6;
          c |= d & 0x3F;
      }

      /* assertion: c is a single UTF-4 value */
        if (c < 0x10000) {
            if (out >= outend)  break;
	    if (xmlLittleEndian) {
		tmp = (unsigned char *) out;
		*tmp = c >> 8;
		*(tmp + 1) = c;
		out++;
	    } else {
		*out++ = c;
	    }
        }
        else if (c < 0x110000) {
            if (out+1 >= outend)  break;
            c -= 0x10000;
	    if (xmlLittleEndian) {
		tmp1 = 0xD800 | (c >> 10);
		tmp = (unsigned char *) out;
		*tmp = tmp1 >> 8;
		*(tmp + 1) = (unsigned char) tmp1;
		out++;

		tmp2 = 0xDC00 | (c & 0x03FF);
		tmp = (unsigned char *) out;
		*tmp = tmp2 >> 8;
		*(tmp + 1) = (unsigned char) tmp2;
		out++;
	    } else {
		*out++ = 0xD800 | (c >> 10);
		*out++ = 0xDC00 | (c & 0x03FF);
	    }
        }
        else
	    break;
	processed = in;
    }
    *outlen = (out - outstart) * 2;
    *inlen = processed - instart;
    return(0);
}

unsigned char * HeapW2A(BSTR bstrStr)
{
#ifdef LOGGING
	char buffer[BUFSIZ];
	memset(buffer, 0, BUFSIZ);
#endif
	EnterLog;
	int bstrByteSize = (int)SysStringByteLen(bstrStr);
#ifdef LOGGING
	sprintf((char *)buffer, "bstrByteSize = %d", bstrByteSize);
	DebugLog((const char *)buffer);
#endif
	if (bstrByteSize==0) {
		return NULL;
	}
	int utf8CharStrLen = bstrByteSize * 2;
	if (utf8CharStrLen < 6)
		utf8CharStrLen = 6;
	unsigned char *utf8CharStr = (unsigned char *)zMalloc(utf8CharStrLen);
	memset(utf8CharStr, 0, utf8CharStrLen);
	if (xmlLittleEndian)
		UTF16LEToUTF8(utf8CharStr, &utf8CharStrLen, (const unsigned char *)bstrStr, &bstrByteSize);
	else
		UTF16BEToUTF8(utf8CharStr, &utf8CharStrLen, (const unsigned char *)bstrStr, &bstrByteSize);
	ExitLog;
	return utf8CharStr;
}

#ifdef DEBUG

#define MIN(x , y)  (((x) < (y)) ? (x) : (y))

/* dump a line (16 bytes) of memory, starting at pointer ptr for len
   bytes */

void
ldump(char *ptr, unsigned int len) {
  if ( len ) {
    int  i;
    char c;
    len=MIN(16,len);
    /*    printf("\nStart is %10x, Count is %5x, End is %10x",ptr,len,ptr+len); */
    printf("\n%10p ",ptr);

    for( i = 0 ; i < len ; i++ )  /* Print the hex dump for len
                                     chars. */
      printf("%3x",(*(ptr+i)&0xff));

    for( i = len ; i < 16 ; i++ ) /* Pad out the dump field to the
                                     ASCII field. */
      printf("   ");

    printf(" ");
    for( i = 0 ; i < len ; i++ ) { /* Now print the ASCII field. */
      c=0x7f&(*(ptr+i));      /* Mask out bit 7 */

      if (!(isprint(c))) {    /* If not printable */
        printf(".");          /* print a dot */
      } else {
        printf("%c",c);  }    /* else display it */
    }
  }
}

/* Print out a header for a hex dump starting at address st. Each
   entry shows the least significant nybble of the address for that
   column. */

void
head(long st) {
  int i;
  printf("\n   addr    ");
  for ( i = st&0xf ; i < (st&0xf)+0x10 ; i++ )
    printf("%3x",(i&0x0f));
  printf(" | 7 bit ascii. |");
}


/* Dump a region of memory, starting at ptr for ct bytes */

void
dump(char *ptr, unsigned int ct) {
  if ( ct ) {
    int i;

    /*  preliminary info for user's benefit. */
    printf("\nStart is %10p, Count is %5x, End is %10p",
           ptr, ct, ptr + ct);
    head((long)ptr);
    for ( i = 0 ; i <= ct ; i = i+16 , ptr = ptr+16 )
      ldump(ptr,(MIN(16,(ct-i))));

    printf("\n\"Enter\" to continue.\n"); /* Give him/her/it a chance
                                             to examine it. */
    getchar ();
  }
}
#else
void ldump(char *ptr, unsigned int len) {}
void head(long st) {}
void dump(char *ptr, unsigned int ct) {}
#endif

#ifdef LINUX
// FIXME: Check this function properly.
// TODO: This doesn't work.
unsigned char * HeapWCHAR2A(WCHAR *wcharStr)
{
    EnterLog;
    // wcharByteSize should be twice the number of wchars
    // Each wide char might become 1, 2 or 3 bytes in UTF8
    // Allocate 4 times the size just to be on the safe side
    int wcharByteSize = strlenW(wcharStr) * 2;
    int utf8StrLen = wcharByteSize * 2;
	if (utf8StrLen < 6)
		utf8StrLen = 6;
    unsigned char *utf8Str = (unsigned char *)zMalloc(utf8StrLen);
    memset(utf8Str, 0, utf8StrLen);
	if (xmlLittleEndian)
	    UTF16LEToUTF8(utf8Str, &utf8StrLen, (const unsigned char *)wcharStr, &wcharByteSize);
	else
		UTF16BEToUTF8(utf8Str, &utf8StrLen, (const unsigned char *)wcharStr, &wcharByteSize);
    ExitLog;
    return utf8Str;
}

#if 0
BSTR A2WBSTR(LPCSTR lp, int nLen)
{
	if (lp == NULL || nLen == 0)
		return NULL;
	BSTR str = NULL;
	unsigned char *utf16CharStr = NULL;
	int utf16ByteLen = 0, utf8ByteLen = 0;
	if (nLen > 0)
		utf8ByteLen = nLen;
	else
		utf8ByteLen = strlen(lp);
	utf16ByteLen = utf8ByteLen * 2;
	utf16CharStr = (unsigned char *)zMalloc(utf16ByteLen);
	if (xmlLittleEndian)
		UTF8ToUTF16LE(utf16CharStr, &utf16ByteLen, (const unsigned char*)lp, &utf8ByteLen);
	else
		UTF8ToUTF16BE(utf16CharStr, &utf16ByteLen, (const unsigned char*)lp, &utf8ByteLen);

	str = SysAllocStringByteLen((LPCSTR)utf16CharStr, utf16ByteLen);
	zFree(utf16CharStr);

	return str;
}
#endif

#if 1
WCHAR *A2WCHAR(LPCSTR lp, int nLen, int *utf16ByteLen)
{
	if (lp == NULL || nLen == 0)
		return NULL;
	unsigned char *utf16CharStr = NULL;
	*utf16ByteLen = 0;
	int utf8ByteLen = 0;
	if (nLen > 0)
		utf8ByteLen = nLen;
	else
		utf8ByteLen = strlen(lp);
	// strlen gives the number of bytes. Not the number of UTF8 chars
	// Hence it is safe to multiply the no. of bytes by 2 to get the bytes in UTF16 string
	*utf16ByteLen = utf8ByteLen * 2;
	utf16CharStr = (unsigned char *)zMalloc(*utf16ByteLen);
	if (xmlLittleEndian)
		UTF8ToUTF16LE(utf16CharStr, utf16ByteLen, (const unsigned char*)lp, &utf8ByteLen);
	else
		UTF8ToUTF16BE(utf16CharStr, utf16ByteLen, (const unsigned char*)lp, &utf8ByteLen);

	return (WCHAR *)utf16CharStr;
}

BSTR A2WBSTR(LPCSTR lp, int nLen)
{
	if (lp == NULL || nLen == 0)
		return NULL;
	BSTR bstr = NULL;
	int utf16ByteLen = 0;
	WCHAR *wStr = A2WCHAR(lp, nLen, &utf16ByteLen);
	if (wStr != NULL)
	{
		bstr = SysAllocStringByteLen((LPCSTR)wStr, utf16ByteLen);
		zFree(wStr);
	}
	return bstr;
}
#endif

BSTR A2WBSTR(LPCSTR lp)
{
	return A2WBSTR(lp, -1);
}

void GetSystemTimeLinux(SYSTEMTIME *ts)
{
	time_t t;
	struct tm *ptm;
	time(&t);
	ptm = gmtime(&t);

	ts->wYear = ptm->tm_year + 1900;
	ts->wMonth = ptm->tm_mon + 1;
	ts->wDay = ptm->tm_mday;
	ts->wHour = ptm->tm_hour;
	ts->wMinute = ptm->tm_min;
	ts->wSecond = ptm->tm_sec;
}

#endif

