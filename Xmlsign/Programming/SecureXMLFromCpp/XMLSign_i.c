/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Dec 25 21:25:34 2002
 */
/* Compiler settings for .\XMLSign.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ISignature = {0x62EC64DC,0xB26D,0x46CE,{0x9E,0x33,0x24,0x28,0x9B,0xCF,0x5F,0x63}};


const IID LIBID_XMLSIGNLib = {0x7CAD46B3,0x47CB,0x45B6,{0xBB,0x83,0x1B,0x22,0xAE,0x0C,0xB3,0xBC}};


const CLSID CLSID_Signature = {0xD300C133,0xA6F6,0x4FB4,{0xA7,0x34,0x48,0x65,0xFB,0xF5,0xA3,0xB1}};


#ifdef __cplusplus
}
#endif

