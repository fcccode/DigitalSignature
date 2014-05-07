
#ifdef LINUX
#include <securexml/SysBufferLinux.h>
#endif

int UTF16LEToUTF8(unsigned char* out, int *outlen,
            const unsigned char* inb, int *inlenb);

int UTF8ToUTF16LE(unsigned char* outb, int *outlen,
            const unsigned char* in, int *inlen);

int UTF16BEToUTF8(unsigned char* out, int *outlen,
            const unsigned char* inb, int *inlenb);

int UTF8ToUTF16BE(unsigned char* outb, int *outlen,
            const unsigned char* in, int *inlen);

unsigned char * HeapW2A(BSTR bstrStr);

BSTR A2WBSTR(LPCSTR lp, int nLen);

BSTR A2WBSTR(LPCSTR lp);

/* dump a line (16 bytes) of memory, starting at pointer ptr for len
   bytes */
void ldump(char *ptr, unsigned int len);
/* Print out a header for a hex dump starting at address st. Each
   entry shows the least significant nybble of the address for that
   column. */
void head(long st);
/* Dump a region of memory, starting at ptr for ct bytes */
void dump(char *ptr, unsigned int ct);


