

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Thu May 15 22:03:00 2003
 */
/* Compiler settings for \ActiveX\XMLSign\XMLSign.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */
#pragma warning( disable: 4211 )  /* redefine extent to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "XMLSign_h.h"

#define TYPE_FORMAT_STRING_SIZE   1089                              
#define PROC_FORMAT_STRING_SIZE   5515                              
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISignature_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISignature_ProxyInfo;

/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_DecryptUsingPFXFileCert_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[4818],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_DecryptionPFXPassword_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[4854],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_XpathNamespace_Proxy( 
    ISignature * This,
    /* [in] */ VARIANT newVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[4890],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_CamServerHost_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[4926],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_CamServerHost_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[4962],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_CamServerPort_Proxy( 
    ISignature * This,
    /* [retval][out] */ USHORT *pVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[4998],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_CamServerPort_Proxy( 
    ISignature * This,
    /* [in] */ USHORT newVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[5034],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_UseCam_Proxy( 
    ISignature * This,
    /* [retval][out] */ BOOL *pVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[5070],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_UseCam_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[5106],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_AgencyId_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[5142],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_AgencyId_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[5178],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_CamValidationResponse_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[5214],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GetSigPropValueByName_Proxy( 
    ISignature * This,
    /* [in] */ LONG sigIndex,
    /* [in] */ BSTR propName,
    /* [retval][out] */ BSTR *propValue)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[5250],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_Base64DecodeBufferToFile_Proxy( 
    ISignature * This,
    /* [in] */ BSTR encodedBuffer,
    /* [in] */ BSTR outFilePath,
    /* [retval][out] */ BSTR *decodedFilePath)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[5298],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_Base64DecodeFileToFile_Proxy( 
    ISignature * This,
    /* [in] */ BSTR encodedFilePath,
    /* [in] */ BSTR outFilePath,
    /* [retval][out] */ BSTR *decodedFilePath)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[5346],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GunZipFile_Proxy( 
    ISignature * This,
    /* [in] */ BSTR gZippedFile,
    /* [in] */ BSTR gUnZippedFile,
    /* [retval][out] */ BSTR *gUnZippedFilePath)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[5394],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_CertSerialNumberFormat_Proxy( 
    ISignature * This,
    /* [retval][out] */ LONG *pValretval)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[5442],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}

/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_CertSerialNumberFormat_Proxy( 
    ISignature * This,
    /* [in] */ LONG newVal)
{
CLIENT_CALL_RETURN _RetVal;

_RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[5478],
                  ( unsigned char * )&This);
return ( HRESULT  )_RetVal.Simple;

}


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure get_EnvelopingFlag */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x22 ),	/* 34 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 24 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EnvelopingFlag */

/* 36 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
/* 44 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 46 */	NdrFcShort( 0x6 ),	/* 6 */
/* 48 */	NdrFcShort( 0x8 ),	/* 8 */
/* 50 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 52 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 60 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 66 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 68 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 70 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_RecipientCertificateStore */

/* 72 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 74 */	NdrFcLong( 0x0 ),	/* 0 */
/* 78 */	NdrFcShort( 0x9 ),	/* 9 */
/* 80 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 82 */	NdrFcShort( 0x0 ),	/* 0 */
/* 84 */	NdrFcShort( 0x8 ),	/* 8 */
/* 86 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 88 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 90 */	NdrFcShort( 0x1 ),	/* 1 */
/* 92 */	NdrFcShort( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 96 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 98 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 100 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 104 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_RecipientCertificateStore */

/* 108 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0xa ),	/* 10 */
/* 116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 122 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 124 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 128 */	NdrFcShort( 0x1 ),	/* 1 */
/* 130 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 132 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 134 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 136 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 138 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 140 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 142 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SignerCertificate */

/* 144 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 146 */	NdrFcLong( 0x0 ),	/* 0 */
/* 150 */	NdrFcShort( 0xb ),	/* 11 */
/* 152 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 154 */	NdrFcShort( 0x8 ),	/* 8 */
/* 156 */	NdrFcShort( 0x8 ),	/* 8 */
/* 158 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 160 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 162 */	NdrFcShort( 0x1 ),	/* 1 */
/* 164 */	NdrFcShort( 0x0 ),	/* 0 */
/* 166 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 168 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 170 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 174 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 176 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 178 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 180 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 182 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 184 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_SignerCertificate */

/* 186 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 188 */	NdrFcLong( 0x0 ),	/* 0 */
/* 192 */	NdrFcShort( 0xc ),	/* 12 */
/* 194 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 196 */	NdrFcShort( 0x8 ),	/* 8 */
/* 198 */	NdrFcShort( 0x8 ),	/* 8 */
/* 200 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 202 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 206 */	NdrFcShort( 0x1 ),	/* 1 */
/* 208 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 210 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 212 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 214 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter newVal */

/* 216 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 218 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 220 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 222 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 224 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 226 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SignatureID */

/* 228 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 230 */	NdrFcLong( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0xd ),	/* 13 */
/* 236 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 238 */	NdrFcShort( 0x8 ),	/* 8 */
/* 240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 242 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 244 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 246 */	NdrFcShort( 0x1 ),	/* 1 */
/* 248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 252 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 254 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 258 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 260 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 262 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 264 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 266 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 268 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_SignatureID */

/* 270 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 272 */	NdrFcLong( 0x0 ),	/* 0 */
/* 276 */	NdrFcShort( 0xe ),	/* 14 */
/* 278 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 280 */	NdrFcShort( 0x8 ),	/* 8 */
/* 282 */	NdrFcShort( 0x8 ),	/* 8 */
/* 284 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 286 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 290 */	NdrFcShort( 0x1 ),	/* 1 */
/* 292 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 294 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 296 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter newVal */

/* 300 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 302 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 304 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 306 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 308 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 310 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Properties */

/* 312 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 314 */	NdrFcLong( 0x0 ),	/* 0 */
/* 318 */	NdrFcShort( 0xf ),	/* 15 */
/* 320 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 322 */	NdrFcShort( 0x10 ),	/* 16 */
/* 324 */	NdrFcShort( 0x8 ),	/* 8 */
/* 326 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 328 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 330 */	NdrFcShort( 0x1 ),	/* 1 */
/* 332 */	NdrFcShort( 0x0 ),	/* 0 */
/* 334 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigIndex */

/* 336 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 338 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter propIndex */

/* 342 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 344 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 346 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 348 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 350 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 352 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 354 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 356 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 358 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Properties */

/* 360 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 362 */	NdrFcLong( 0x0 ),	/* 0 */
/* 366 */	NdrFcShort( 0x10 ),	/* 16 */
/* 368 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 370 */	NdrFcShort( 0x10 ),	/* 16 */
/* 372 */	NdrFcShort( 0x8 ),	/* 8 */
/* 374 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 376 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 380 */	NdrFcShort( 0x1 ),	/* 1 */
/* 382 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigIndex */

/* 384 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 386 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 388 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter propIndex */

/* 390 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 392 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 394 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter newVal */

/* 396 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 398 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 400 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 402 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 404 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 406 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Base64EncodeXML */

/* 408 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 410 */	NdrFcLong( 0x0 ),	/* 0 */
/* 414 */	NdrFcShort( 0x11 ),	/* 17 */
/* 416 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 418 */	NdrFcShort( 0x0 ),	/* 0 */
/* 420 */	NdrFcShort( 0x24 ),	/* 36 */
/* 422 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 424 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 426 */	NdrFcShort( 0x0 ),	/* 0 */
/* 428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 430 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 432 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 434 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 436 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 438 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 440 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 442 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Base64EncodeXML */

/* 444 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 446 */	NdrFcLong( 0x0 ),	/* 0 */
/* 450 */	NdrFcShort( 0x12 ),	/* 18 */
/* 452 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 454 */	NdrFcShort( 0x8 ),	/* 8 */
/* 456 */	NdrFcShort( 0x8 ),	/* 8 */
/* 458 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 460 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 466 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 468 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 470 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 472 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 474 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 476 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 478 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Base64DecodeXML */

/* 480 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 482 */	NdrFcLong( 0x0 ),	/* 0 */
/* 486 */	NdrFcShort( 0x13 ),	/* 19 */
/* 488 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 490 */	NdrFcShort( 0x0 ),	/* 0 */
/* 492 */	NdrFcShort( 0x24 ),	/* 36 */
/* 494 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 496 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 502 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 504 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 506 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 508 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 510 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 512 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 514 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Base64DecodeXML */

/* 516 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 518 */	NdrFcLong( 0x0 ),	/* 0 */
/* 522 */	NdrFcShort( 0x14 ),	/* 20 */
/* 524 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 526 */	NdrFcShort( 0x8 ),	/* 8 */
/* 528 */	NdrFcShort( 0x8 ),	/* 8 */
/* 530 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 532 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 540 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 542 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 544 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 546 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 548 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 550 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DocumentURI */

/* 552 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 554 */	NdrFcLong( 0x0 ),	/* 0 */
/* 558 */	NdrFcShort( 0x15 ),	/* 21 */
/* 560 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 562 */	NdrFcShort( 0x10 ),	/* 16 */
/* 564 */	NdrFcShort( 0x8 ),	/* 8 */
/* 566 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 568 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 570 */	NdrFcShort( 0x1 ),	/* 1 */
/* 572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 574 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigIndex */

/* 576 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 578 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter uriIndex */

/* 582 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 584 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 586 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 588 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 590 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 592 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 594 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 596 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 598 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DigestObjectStatus */

/* 600 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 602 */	NdrFcLong( 0x0 ),	/* 0 */
/* 606 */	NdrFcShort( 0x16 ),	/* 22 */
/* 608 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 610 */	NdrFcShort( 0x10 ),	/* 16 */
/* 612 */	NdrFcShort( 0x24 ),	/* 36 */
/* 614 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 616 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	NdrFcShort( 0x0 ),	/* 0 */
/* 622 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigIndex */

/* 624 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 626 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 628 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter uriIndex */

/* 630 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 632 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 634 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 636 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 638 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 640 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 642 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 644 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 646 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CaptureOnce */

/* 648 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 650 */	NdrFcLong( 0x0 ),	/* 0 */
/* 654 */	NdrFcShort( 0x17 ),	/* 23 */
/* 656 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 660 */	NdrFcShort( 0x24 ),	/* 36 */
/* 662 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 664 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 670 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 672 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 674 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 676 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 678 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 680 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 682 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CaptureOnce */

/* 684 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 686 */	NdrFcLong( 0x0 ),	/* 0 */
/* 690 */	NdrFcShort( 0x18 ),	/* 24 */
/* 692 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 694 */	NdrFcShort( 0x8 ),	/* 8 */
/* 696 */	NdrFcShort( 0x8 ),	/* 8 */
/* 698 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 700 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 708 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 710 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 712 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 714 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 716 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 718 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SignatureStatus */

/* 720 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 722 */	NdrFcLong( 0x0 ),	/* 0 */
/* 726 */	NdrFcShort( 0x19 ),	/* 25 */
/* 728 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 730 */	NdrFcShort( 0x8 ),	/* 8 */
/* 732 */	NdrFcShort( 0x24 ),	/* 36 */
/* 734 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 736 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigIndex */

/* 744 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 746 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 748 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 750 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 752 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 754 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 756 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 758 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 760 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PhysicalSignatureUsage */

/* 762 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 764 */	NdrFcLong( 0x0 ),	/* 0 */
/* 768 */	NdrFcShort( 0x1a ),	/* 26 */
/* 770 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 772 */	NdrFcShort( 0x0 ),	/* 0 */
/* 774 */	NdrFcShort( 0x24 ),	/* 36 */
/* 776 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 778 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 784 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 786 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 788 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 790 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 792 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 794 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PhysicalSignatureUsage */

/* 798 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 800 */	NdrFcLong( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0x1b ),	/* 27 */
/* 806 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 808 */	NdrFcShort( 0x8 ),	/* 8 */
/* 810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 812 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 814 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 820 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 822 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 824 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 826 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 828 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 830 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 832 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PhysicalSignatureFile */

/* 834 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 836 */	NdrFcLong( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x1c ),	/* 28 */
/* 842 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 844 */	NdrFcShort( 0x0 ),	/* 0 */
/* 846 */	NdrFcShort( 0x8 ),	/* 8 */
/* 848 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 850 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 852 */	NdrFcShort( 0x1 ),	/* 1 */
/* 854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 856 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 858 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 860 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 862 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 864 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 866 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 868 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PhysicalSignatureFile */

/* 870 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 872 */	NdrFcLong( 0x0 ),	/* 0 */
/* 876 */	NdrFcShort( 0x1d ),	/* 29 */
/* 878 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 882 */	NdrFcShort( 0x8 ),	/* 8 */
/* 884 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 886 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 888 */	NdrFcShort( 0x0 ),	/* 0 */
/* 890 */	NdrFcShort( 0x1 ),	/* 1 */
/* 892 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 894 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 896 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 898 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 900 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 902 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 904 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CapturedSignatureFile */

/* 906 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 908 */	NdrFcLong( 0x0 ),	/* 0 */
/* 912 */	NdrFcShort( 0x1e ),	/* 30 */
/* 914 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 916 */	NdrFcShort( 0x0 ),	/* 0 */
/* 918 */	NdrFcShort( 0x8 ),	/* 8 */
/* 920 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 922 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 924 */	NdrFcShort( 0x1 ),	/* 1 */
/* 926 */	NdrFcShort( 0x0 ),	/* 0 */
/* 928 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 930 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 932 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 934 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 936 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 938 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 940 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Sign */

/* 942 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 944 */	NdrFcLong( 0x0 ),	/* 0 */
/* 948 */	NdrFcShort( 0x1f ),	/* 31 */
/* 950 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 952 */	NdrFcShort( 0x0 ),	/* 0 */
/* 954 */	NdrFcShort( 0x8 ),	/* 8 */
/* 956 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 958 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 960 */	NdrFcShort( 0x1 ),	/* 1 */
/* 962 */	NdrFcShort( 0x1 ),	/* 1 */
/* 964 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter URI */

/* 966 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 968 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 970 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter tempFileName */

/* 972 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 974 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 976 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 978 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 980 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 982 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IncludeCamResponse */

/* 984 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 986 */	NdrFcLong( 0x0 ),	/* 0 */
/* 990 */	NdrFcShort( 0x20 ),	/* 32 */
/* 992 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 994 */	NdrFcShort( 0x0 ),	/* 0 */
/* 996 */	NdrFcShort( 0x24 ),	/* 36 */
/* 998 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1000 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1004 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1006 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1008 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1010 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1012 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1014 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1016 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1018 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_IncludeCamResponse */

/* 1020 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1022 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1026 */	NdrFcShort( 0x21 ),	/* 33 */
/* 1028 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1030 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1032 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1034 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1036 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1042 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 1044 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1046 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1048 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1050 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1052 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1054 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SaveXMLSignature */

/* 1056 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1058 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1062 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1064 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1066 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1068 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1070 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1072 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1076 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1078 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigFileName */

/* 1080 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1082 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1084 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 1086 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1088 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1090 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Verify */

/* 1092 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1094 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1098 */	NdrFcShort( 0x23 ),	/* 35 */
/* 1100 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1104 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1106 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1108 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1112 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1114 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter signatureFileName */

/* 1116 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1118 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1120 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter sigStatus */

/* 1122 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1124 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1126 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1128 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1130 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1132 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetError */

/* 1134 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1136 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1140 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1142 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1144 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1146 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1148 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1150 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1152 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1156 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter errorString */

/* 1158 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1160 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1162 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 1164 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1166 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1168 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_OverwriteFile */

/* 1170 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1172 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1176 */	NdrFcShort( 0x25 ),	/* 37 */
/* 1178 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1180 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1182 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1184 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1186 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1192 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 1194 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1196 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1198 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1200 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1202 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1204 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PFXExportCertificate */

/* 1206 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1208 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1212 */	NdrFcShort( 0x26 ),	/* 38 */
/* 1214 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1216 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1218 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1220 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 1222 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1224 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1226 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1228 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter certID */

/* 1230 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1232 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1234 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter password */

/* 1236 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1238 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1240 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter pfxFilePath */

/* 1242 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1244 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1246 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 1248 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1250 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1252 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VerifyDetached */

/* 1254 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1256 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1260 */	NdrFcShort( 0x27 ),	/* 39 */
/* 1262 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1264 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1266 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1268 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1270 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1272 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1274 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1276 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter signatureFileName */

/* 1278 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1280 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1282 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter sigStatus */

/* 1284 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1286 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1288 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1290 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1292 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1294 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetLastError */

/* 1296 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1298 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1302 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1304 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1306 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1308 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1310 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1312 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1316 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1318 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter errorNum */

/* 1320 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1322 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1324 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1326 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1328 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1330 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetX509Certificate */

/* 1332 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1334 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1338 */	NdrFcShort( 0x29 ),	/* 41 */
/* 1340 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1344 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1346 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1348 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1350 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1352 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1354 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter certID */

/* 1356 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1358 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1360 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter certData */

/* 1362 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1364 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1366 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 1368 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1370 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1372 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ViewCertificate */

/* 1374 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1376 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1380 */	NdrFcShort( 0x2a ),	/* 42 */
/* 1382 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1384 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1386 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1388 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1390 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1392 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1394 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1396 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter certID */

/* 1398 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1400 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1402 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 1404 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1406 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1408 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CertificateCount */

/* 1410 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1412 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1416 */	NdrFcShort( 0x2b ),	/* 43 */
/* 1418 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1422 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1424 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1426 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1432 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1434 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1436 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1438 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1440 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1442 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1444 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCertificateInfo */

/* 1446 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1448 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1452 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1454 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1456 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1458 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1460 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 1462 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1464 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1468 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1470 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1472 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1474 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter valIndex */

/* 1476 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1478 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1480 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter value */

/* 1482 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1484 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1486 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 1488 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1490 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1492 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetActiveCertificate */

/* 1494 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1496 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1500 */	NdrFcShort( 0x2d ),	/* 45 */
/* 1502 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1506 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1508 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1510 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1512 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1514 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1516 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter certID */

/* 1518 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1520 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1522 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter status */

/* 1524 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1526 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1528 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1530 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1532 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1534 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SignedDocumentPath */

/* 1536 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1538 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1542 */	NdrFcShort( 0x2e ),	/* 46 */
/* 1544 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1546 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1548 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1550 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 1552 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1554 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1558 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigIndex */

/* 1560 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1562 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1564 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter uriIndex */

/* 1566 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1568 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1570 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 1572 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1574 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1576 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 1578 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1580 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1582 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SignerSubject */

/* 1584 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1586 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1590 */	NdrFcShort( 0x2f ),	/* 47 */
/* 1592 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1596 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1598 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1600 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1602 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1604 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1606 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigId */

/* 1608 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1610 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1612 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter pVal */

/* 1614 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1616 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1618 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 1620 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1622 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1624 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CertIssuer */

/* 1626 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1628 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1632 */	NdrFcShort( 0x30 ),	/* 48 */
/* 1634 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1638 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1640 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1642 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1644 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1646 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1648 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigId */

/* 1650 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1652 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1654 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter pVal */

/* 1656 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1658 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1660 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 1662 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1664 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1666 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CertExpiry */

/* 1668 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1670 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1674 */	NdrFcShort( 0x31 ),	/* 49 */
/* 1676 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1680 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1682 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1684 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1686 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1688 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1690 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigId */

/* 1692 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1694 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1696 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter pVal */

/* 1698 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1700 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1702 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 1704 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1706 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1708 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CertSerialNumber */

/* 1710 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1712 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1716 */	NdrFcShort( 0x32 ),	/* 50 */
/* 1718 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1720 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1722 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1724 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1726 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1728 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1730 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1732 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigId */

/* 1734 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1736 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1738 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter pVal */

/* 1740 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1742 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1744 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 1746 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1748 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1750 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FileExists */

/* 1752 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1754 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1758 */	NdrFcShort( 0x33 ),	/* 51 */
/* 1760 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1764 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1766 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1768 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1772 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1774 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter fileName */

/* 1776 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1778 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1780 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter fileStatus */

/* 1782 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1784 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1786 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1788 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1790 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1792 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_FailedUriCount */

/* 1794 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1796 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1800 */	NdrFcShort( 0x34 ),	/* 52 */
/* 1802 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1804 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1806 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1808 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1810 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1816 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1818 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1820 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1822 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1824 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1826 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1828 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_TotalUriCount */

/* 1830 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1832 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1836 */	NdrFcShort( 0x35 ),	/* 53 */
/* 1838 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1840 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1842 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1844 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1846 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1850 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1852 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 1854 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1856 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1858 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1860 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1862 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1864 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_FailedUriFullPath */

/* 1866 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1868 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1872 */	NdrFcShort( 0x36 ),	/* 54 */
/* 1874 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1876 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1878 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1880 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1882 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1884 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1886 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1888 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1890 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1892 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1894 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 1896 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1898 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1900 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 1902 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1904 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1906 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_FailedUriFullPath */

/* 1908 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1910 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1914 */	NdrFcShort( 0x37 ),	/* 55 */
/* 1916 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1918 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1920 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1922 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1924 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1926 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1928 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1930 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1932 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1934 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1936 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter newVal */

/* 1938 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1940 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1942 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 1944 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1946 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1948 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_FailedUri */

/* 1950 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1952 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1956 */	NdrFcShort( 0x38 ),	/* 56 */
/* 1958 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1960 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1962 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1964 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1966 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1968 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1970 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1972 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1974 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1976 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1978 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 1980 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1982 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1984 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 1986 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1988 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1990 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SignatureCount */

/* 1992 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1994 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1998 */	NdrFcShort( 0x39 ),	/* 57 */
/* 2000 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2004 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2006 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2008 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2010 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2012 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2014 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2016 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2018 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2020 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2022 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2024 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2026 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SignXMLStr */

/* 2028 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2030 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2034 */	NdrFcShort( 0x3a ),	/* 58 */
/* 2036 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2040 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2042 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2044 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2046 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2048 */	NdrFcShort( 0x2 ),	/* 2 */
/* 2050 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter xmlStr */

/* 2052 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2054 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2056 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter signatureId */

/* 2058 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2060 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2062 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter signedXMLStr */

/* 2064 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2066 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2068 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2070 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2072 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2074 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReadAll */

/* 2076 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2078 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2082 */	NdrFcShort( 0x3b ),	/* 59 */
/* 2084 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2086 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2088 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2090 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2092 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2094 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2096 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2098 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter fileName */

/* 2100 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2102 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2104 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter fileDataStr */

/* 2106 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2108 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2110 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2112 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2114 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2116 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SaveXMLStr */

/* 2118 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2120 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2124 */	NdrFcShort( 0x3c ),	/* 60 */
/* 2126 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2128 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2130 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2132 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2134 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2136 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2138 */	NdrFcShort( 0x2 ),	/* 2 */
/* 2140 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inputXMLStr */

/* 2142 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2144 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2146 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter fileName */

/* 2148 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2150 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2152 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter path */

/* 2154 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2156 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2158 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2160 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2162 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2164 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SignHTML */

/* 2166 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2168 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2172 */	NdrFcShort( 0x3d ),	/* 61 */
/* 2174 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2178 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2180 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2182 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2184 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2188 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter document */

/* 2190 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2192 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2194 */	NdrFcShort( 0x40 ),	/* Type Offset=64 */

	/* Parameter signedHTML */

/* 2196 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2198 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2200 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2202 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2204 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2206 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SecureXMLVerify */

/* 2208 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2210 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2214 */	NdrFcShort( 0x3e ),	/* 62 */
/* 2216 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2218 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2220 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2222 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2224 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2226 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2228 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2230 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter signedXML */

/* 2232 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2234 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2236 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter verificationResponse */

/* 2238 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2240 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2242 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2244 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2246 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2248 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetCSP */

/* 2250 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2252 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2256 */	NdrFcShort( 0x3f ),	/* 63 */
/* 2258 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2260 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2262 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2264 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2266 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2270 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2272 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter CSPName */

/* 2274 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2276 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2278 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 2280 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2282 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2284 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSignedHTML */

/* 2286 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2288 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2292 */	NdrFcShort( 0x40 ),	/* 64 */
/* 2294 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2296 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2298 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2300 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2302 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2304 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2306 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2308 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter signedHtmlXML */

/* 2310 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2312 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2314 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter originalHTML */

/* 2316 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2318 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2320 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2322 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2324 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2326 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SignFile */

/* 2328 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2330 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2334 */	NdrFcShort( 0x41 ),	/* 65 */
/* 2336 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2338 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2340 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2342 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2344 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2348 */	NdrFcShort( 0x2 ),	/* 2 */
/* 2350 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inputFile */

/* 2352 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2354 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2356 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter outputFile */

/* 2358 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2360 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2362 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 2364 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2366 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2368 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSignedFileObject */

/* 2370 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2372 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2376 */	NdrFcShort( 0x42 ),	/* 66 */
/* 2378 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2380 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2382 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2384 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2386 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2388 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2390 */	NdrFcShort( 0x2 ),	/* 2 */
/* 2392 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter signedXML */

/* 2394 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2396 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2398 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter saveDir */

/* 2400 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2402 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2404 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter signedFilePath */

/* 2406 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2408 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2410 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2412 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2414 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2416 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetStoreName */

/* 2418 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2420 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2424 */	NdrFcShort( 0x43 ),	/* 67 */
/* 2426 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2430 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2432 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2434 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2438 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2440 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter storeName */

/* 2442 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2444 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2446 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 2448 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2450 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2452 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetStoreName */

/* 2454 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2456 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2460 */	NdrFcShort( 0x44 ),	/* 68 */
/* 2462 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2466 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2468 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2470 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2472 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2476 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter storeName */

/* 2478 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2480 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2482 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2484 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2486 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2488 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SignXMLEnveloped */

/* 2490 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2492 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2496 */	NdrFcShort( 0x45 ),	/* 69 */
/* 2498 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2502 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2504 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2506 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2508 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2510 */	NdrFcShort( 0x2 ),	/* 2 */
/* 2512 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inputXML */

/* 2514 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2516 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2518 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter sigId */

/* 2520 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2522 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2524 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter signedXML */

/* 2526 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2528 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2530 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2532 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2534 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2536 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetVersion */

/* 2538 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2540 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2544 */	NdrFcShort( 0x46 ),	/* 70 */
/* 2546 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2550 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2552 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2554 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2556 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2560 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter version */

/* 2562 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2564 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2566 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2568 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2570 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2572 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetLicenseStatus */

/* 2574 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2576 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2580 */	NdrFcShort( 0x47 ),	/* 71 */
/* 2582 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2584 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2586 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2588 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2590 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2596 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter licStatus */

/* 2598 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2600 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2602 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2604 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2606 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2608 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPropertyCount */

/* 2610 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2612 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2616 */	NdrFcShort( 0x48 ),	/* 72 */
/* 2618 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2620 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2622 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2624 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 2626 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2632 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigIndex */

/* 2634 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2636 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2638 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter propCount */

/* 2640 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2642 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2644 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2646 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2648 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2650 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ViewAnyCertificate */

/* 2652 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2654 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2658 */	NdrFcShort( 0x49 ),	/* 73 */
/* 2660 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2664 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2666 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2668 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2670 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2672 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2674 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inputX509Data */

/* 2676 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2678 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2680 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 2682 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2684 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2686 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SelectActiveCertificate */

/* 2688 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2690 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2694 */	NdrFcShort( 0x4a ),	/* 74 */
/* 2696 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2700 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2702 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2704 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2706 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2710 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter certID */

/* 2712 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2714 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2716 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2718 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2720 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2722 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VerifyXMLStr */

/* 2724 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2726 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2730 */	NdrFcShort( 0x4b ),	/* 75 */
/* 2732 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2734 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2736 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2738 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2740 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2744 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2746 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter signedXML */

/* 2748 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2750 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2752 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter sigStatus */

/* 2754 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2756 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2758 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2760 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2762 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2764 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetActivePFXFileCert */

/* 2766 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2768 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2772 */	NdrFcShort( 0x4c ),	/* 76 */
/* 2774 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2778 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2780 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2782 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2784 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2786 */	NdrFcShort( 0x2 ),	/* 2 */
/* 2788 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pfxFileName */

/* 2790 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2792 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2794 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter pfxPassword */

/* 2796 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2798 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2800 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter x509Cert */

/* 2802 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2804 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2806 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2808 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2810 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2812 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PFXExportActiveCertificate */

/* 2814 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2816 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2820 */	NdrFcShort( 0x4d ),	/* 77 */
/* 2822 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2824 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2826 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2828 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2830 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2832 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2834 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2836 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter password */

/* 2838 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2840 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2842 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter pfxFilePath */

/* 2844 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2846 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2848 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2850 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2852 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2854 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_HostName */

/* 2856 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2858 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2862 */	NdrFcShort( 0x4e ),	/* 78 */
/* 2864 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2868 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2870 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2872 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2874 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2876 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2878 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2880 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2882 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2884 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2886 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2888 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2890 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_TimeStampURL */

/* 2892 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2894 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2898 */	NdrFcShort( 0x4f ),	/* 79 */
/* 2900 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2902 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2904 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2906 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2908 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2910 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2912 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2914 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2916 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2918 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2920 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 2922 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2924 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2926 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_TimeStampURL */

/* 2928 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2930 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2934 */	NdrFcShort( 0x50 ),	/* 80 */
/* 2936 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2938 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2940 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2942 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2944 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2946 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2948 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2950 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2952 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2954 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2956 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 2958 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2960 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2962 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_TimeStamping */

/* 2964 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2966 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2970 */	NdrFcShort( 0x51 ),	/* 81 */
/* 2972 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2974 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2976 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2978 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2980 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2982 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2984 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2986 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2988 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2990 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2992 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2994 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2996 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2998 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_TimeStamping */

/* 3000 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3002 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3006 */	NdrFcShort( 0x52 ),	/* 82 */
/* 3008 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3010 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3012 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3014 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3016 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3020 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3022 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3024 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3026 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3028 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3030 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3032 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3034 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_HostOsType */

/* 3036 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3038 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3042 */	NdrFcShort( 0x53 ),	/* 83 */
/* 3044 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3046 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3048 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3050 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3052 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3054 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3056 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3058 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3060 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3062 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3064 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3066 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3068 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3070 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CrlChecking */

/* 3072 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3074 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3078 */	NdrFcShort( 0x54 ),	/* 84 */
/* 3080 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3082 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3084 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3086 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3088 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3090 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3092 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3094 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3096 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3098 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3100 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3104 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CrlChecking */

/* 3108 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3114 */	NdrFcShort( 0x55 ),	/* 85 */
/* 3116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3118 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3122 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3124 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3128 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3130 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3132 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3134 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3136 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3138 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3140 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3142 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SigCertStatus */

/* 3144 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3146 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3150 */	NdrFcShort( 0x56 ),	/* 86 */
/* 3152 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3154 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3156 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3158 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 3160 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3164 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3166 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigIndex */

/* 3168 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3170 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter atTime */

/* 3174 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3176 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3178 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter timeFormat */

/* 3180 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3182 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3184 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 3186 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3188 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3190 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3192 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3194 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3196 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VerifyX509CertCRL */

/* 3198 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3200 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3204 */	NdrFcShort( 0x57 ),	/* 87 */
/* 3206 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3208 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3210 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3212 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 3214 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3216 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3218 */	NdrFcShort( 0x2 ),	/* 2 */
/* 3220 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter certData */

/* 3222 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3224 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3226 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter atTime */

/* 3228 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3230 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3232 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter timeFormat */

/* 3234 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3236 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3238 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 3240 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3242 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3244 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3246 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3248 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VerifyPFXCertCRL */

/* 3252 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3254 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3258 */	NdrFcShort( 0x58 ),	/* 88 */
/* 3260 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3262 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3264 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3266 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 3268 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3272 */	NdrFcShort( 0x3 ),	/* 3 */
/* 3274 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pfxFileName */

/* 3276 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3278 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3280 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter pfxPassword */

/* 3282 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3284 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3286 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter atTime */

/* 3288 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3290 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3292 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter timeFormat */

/* 3294 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3296 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 3300 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3302 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3306 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3308 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3310 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AddWindowImage */

/* 3312 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3314 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3318 */	NdrFcShort( 0x59 ),	/* 89 */
/* 3320 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3324 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3326 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3328 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3330 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3332 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3334 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3336 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3338 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3342 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3344 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3346 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AddWindowImage */

/* 3348 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3350 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3354 */	NdrFcShort( 0x5a ),	/* 90 */
/* 3356 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3358 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3360 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3362 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3364 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3370 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3372 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3374 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3376 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3378 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3380 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3382 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CRLLocation */

/* 3384 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3386 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3390 */	NdrFcShort( 0x5b ),	/* 91 */
/* 3392 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3396 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3398 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3400 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3404 */	NdrFcShort( 0x20 ),	/* 32 */
/* 3406 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3408 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3410 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3412 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 3414 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3416 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VerifyActiveCertificate */

/* 3420 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3426 */	NdrFcShort( 0x5c ),	/* 92 */
/* 3428 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3432 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3434 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3436 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3442 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter result */

/* 3444 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3446 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3448 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3450 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3452 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3454 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CertificatePolicy */

/* 3456 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3458 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3462 */	NdrFcShort( 0x5d ),	/* 93 */
/* 3464 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3468 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3470 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3472 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3476 */	NdrFcShort( 0x20 ),	/* 32 */
/* 3478 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3480 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3482 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3484 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 3486 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3488 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3490 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AuthorityConstrainedPolicy */

/* 3492 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3494 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3498 */	NdrFcShort( 0x5e ),	/* 94 */
/* 3500 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3502 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3504 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3506 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3508 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3510 */	NdrFcShort( 0x20 ),	/* 32 */
/* 3512 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3514 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3516 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 3518 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3520 */	NdrFcShort( 0x436 ),	/* Type Offset=1078 */

	/* Return value */

/* 3522 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3524 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3526 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_UserConstrainedPolicy */

/* 3528 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3530 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3534 */	NdrFcShort( 0x5f ),	/* 95 */
/* 3536 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3540 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3542 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3544 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3546 */	NdrFcShort( 0x20 ),	/* 32 */
/* 3548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3550 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3552 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 3554 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3556 */	NdrFcShort( 0x436 ),	/* Type Offset=1078 */

	/* Return value */

/* 3558 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3560 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3562 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CertificatePolicyChecking */

/* 3564 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3566 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3570 */	NdrFcShort( 0x60 ),	/* 96 */
/* 3572 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3574 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3576 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3578 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3580 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3584 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3586 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3588 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3590 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3592 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3594 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3596 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3598 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CertificateChainValidation */

/* 3600 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3602 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3606 */	NdrFcShort( 0x61 ),	/* 97 */
/* 3608 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3610 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3612 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3614 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3616 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3620 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3622 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3624 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3626 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3628 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3630 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3632 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3634 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CertificatePathLengthChecking */

/* 3636 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3638 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3642 */	NdrFcShort( 0x62 ),	/* 98 */
/* 3644 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3646 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3648 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3650 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3652 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3654 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3658 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3660 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3662 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3664 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3666 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3668 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3670 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ConfigFileName */

/* 3672 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3674 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3678 */	NdrFcShort( 0x63 ),	/* 99 */
/* 3680 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3682 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3684 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3686 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3688 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3690 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3692 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3694 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3696 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3698 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3700 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 3702 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3704 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3706 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DoDCompliance */

/* 3708 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3710 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3714 */	NdrFcShort( 0x64 ),	/* 100 */
/* 3716 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3718 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3720 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3722 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3724 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3726 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3728 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3730 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3732 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3734 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3736 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3738 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3740 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3742 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CertificatePolicyExplicit */

/* 3744 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3746 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3750 */	NdrFcShort( 0x65 ),	/* 101 */
/* 3752 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3756 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3758 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3760 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3764 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3766 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3768 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3770 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3772 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3774 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3776 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3778 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CertificatePolicyExplicit */

/* 3780 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3782 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3786 */	NdrFcShort( 0x66 ),	/* 102 */
/* 3788 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3790 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3792 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3794 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3796 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3798 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3802 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3804 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3806 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3808 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3810 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3812 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3814 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CertificateTrustExplicit */

/* 3816 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3818 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3822 */	NdrFcShort( 0x67 ),	/* 103 */
/* 3824 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3826 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3828 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3830 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3832 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3834 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3836 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3838 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3840 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3842 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3844 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3846 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3848 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3850 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SignXMLXpathStr */

/* 3852 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3854 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3858 */	NdrFcShort( 0x68 ),	/* 104 */
/* 3860 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3862 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3864 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3866 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 3868 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 3870 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3872 */	NdrFcShort( 0x3 ),	/* 3 */
/* 3874 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter xmlStr */

/* 3876 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3878 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3880 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter xpathExp */

/* 3882 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3884 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3886 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter signatureId */

/* 3888 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3890 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3892 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter signedXMLStr */

/* 3894 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3896 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3898 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 3900 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3902 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3904 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_UseHMAC */

/* 3906 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3908 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3912 */	NdrFcShort( 0x69 ),	/* 105 */
/* 3914 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3916 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3918 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3920 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3922 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3924 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3926 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3928 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3930 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3932 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3934 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3936 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3938 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3940 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_UseHMAC */

/* 3942 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3944 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3948 */	NdrFcShort( 0x6a ),	/* 106 */
/* 3950 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3952 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3954 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3956 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3958 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3964 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3966 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3968 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3970 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3972 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3974 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3976 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_HMACPassword */

/* 3978 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3980 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3984 */	NdrFcShort( 0x6b ),	/* 107 */
/* 3986 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3988 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3990 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3992 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3994 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3996 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3998 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4000 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 4002 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4004 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4006 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 4008 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4010 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4012 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_HMACPassword */

/* 4014 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4016 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4020 */	NdrFcShort( 0x6c ),	/* 108 */
/* 4022 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4024 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4026 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4028 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4030 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4032 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4034 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4036 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4038 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4040 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4042 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 4044 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4046 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4048 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ChangeOrAddProperty */

/* 4050 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4052 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4056 */	NdrFcShort( 0x6d ),	/* 109 */
/* 4058 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4060 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4062 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4064 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 4066 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4068 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4070 */	NdrFcShort( 0x2 ),	/* 2 */
/* 4072 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter propertyName */

/* 4074 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4076 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4078 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter propertyValue */

/* 4080 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4082 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4084 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 4086 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4088 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4090 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DetailedVerificationFlag */

/* 4092 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4094 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4098 */	NdrFcShort( 0x6e ),	/* 110 */
/* 4100 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4102 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4104 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4106 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4108 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4114 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4116 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4118 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4120 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4122 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4124 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4126 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CaptureLiveSignature */

/* 4128 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4130 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4134 */	NdrFcShort( 0x6f ),	/* 111 */
/* 4136 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4140 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4142 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4144 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4146 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4150 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter signatureFilePath */

/* 4152 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4154 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4156 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 4158 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4160 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4162 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SignDataStr */

/* 4164 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4166 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4170 */	NdrFcShort( 0x70 ),	/* 112 */
/* 4172 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4176 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4178 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 4180 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 4182 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4184 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4186 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter dataStrPtr */

/* 4188 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4190 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4192 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter signedXMLStr */

/* 4194 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4196 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4198 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 4200 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4202 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4204 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ExcludeSignerCertificate */

/* 4206 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4208 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4212 */	NdrFcShort( 0x71 ),	/* 113 */
/* 4214 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4216 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4218 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4220 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4222 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4224 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4226 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4228 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4230 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4232 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4234 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4236 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4238 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4240 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CoSignXMLStr */

/* 4242 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4244 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4248 */	NdrFcShort( 0x72 ),	/* 114 */
/* 4250 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4254 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4256 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 4258 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 4260 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4262 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4264 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter signedDataXMLStr */

/* 4266 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4268 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4270 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter coSignedXMLStr */

/* 4272 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4274 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4276 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 4278 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4280 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4282 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CoSignFile */

/* 4284 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4286 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4290 */	NdrFcShort( 0x73 ),	/* 115 */
/* 4292 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4294 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4296 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4298 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 4300 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 4302 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4304 */	NdrFcShort( 0x2 ),	/* 2 */
/* 4306 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inputSignedXMLFile */

/* 4308 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4310 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4312 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter outFileName */

/* 4314 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4316 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4318 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter outFilePath */

/* 4320 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4322 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4324 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 4326 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4328 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4330 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SignFiles */

/* 4332 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4334 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4338 */	NdrFcShort( 0x74 ),	/* 116 */
/* 4340 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 4342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4344 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4346 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 4348 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 4350 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4352 */	NdrFcShort( 0x21 ),	/* 33 */
/* 4354 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter fileList */

/* 4356 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4358 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4360 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter outFileName */

/* 4362 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4364 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4366 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter outFilePath */

/* 4368 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4370 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4372 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 4374 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4376 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 4378 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_RecipientCertificates */

/* 4380 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4382 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4386 */	NdrFcShort( 0x75 ),	/* 117 */
/* 4388 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4390 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4394 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4396 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4400 */	NdrFcShort( 0x20 ),	/* 32 */
/* 4402 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4404 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4406 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4408 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 4410 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4412 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4414 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EncryptStr */

/* 4416 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4418 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4422 */	NdrFcShort( 0x76 ),	/* 118 */
/* 4424 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4426 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4428 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4430 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 4432 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 4434 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4436 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4438 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inputStr */

/* 4440 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4442 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4444 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter cipherStr */

/* 4446 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4448 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4450 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 4452 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4454 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4456 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DecryptStr */

/* 4458 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4460 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4464 */	NdrFcShort( 0x77 ),	/* 119 */
/* 4466 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4468 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4470 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4472 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 4474 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 4476 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4478 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4480 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter cipherText */

/* 4482 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4484 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4486 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter plainText */

/* 4488 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4490 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4492 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 4494 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4496 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4498 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EncryptFile */

/* 4500 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4502 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4506 */	NdrFcShort( 0x78 ),	/* 120 */
/* 4508 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4510 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4512 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4514 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 4516 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 4518 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4520 */	NdrFcShort( 0x2 ),	/* 2 */
/* 4522 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inputFile */

/* 4524 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4526 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4528 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter outputFile */

/* 4530 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4532 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4534 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter encryptedFile */

/* 4536 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4538 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4540 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 4542 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4544 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4546 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DecryptFile */

/* 4548 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4550 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4554 */	NdrFcShort( 0x79 ),	/* 121 */
/* 4556 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4560 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4562 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 4564 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 4566 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4568 */	NdrFcShort( 0x2 ),	/* 2 */
/* 4570 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inputFile */

/* 4572 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4574 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4576 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter outputFile */

/* 4578 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4580 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4582 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter decryptedFile */

/* 4584 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4586 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4588 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 4590 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4592 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4594 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_TrustedRoots */

/* 4596 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4598 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4602 */	NdrFcShort( 0x7a ),	/* 122 */
/* 4604 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4608 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4610 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4612 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4616 */	NdrFcShort( 0x20 ),	/* 32 */
/* 4618 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4620 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4622 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4624 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 4626 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4628 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4630 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_RecipientCertificateFiles */

/* 4632 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4634 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4638 */	NdrFcShort( 0x7b ),	/* 123 */
/* 4640 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4644 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4646 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4648 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4652 */	NdrFcShort( 0x20 ),	/* 32 */
/* 4654 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4656 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4658 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4660 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 4662 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4664 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4666 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DetachedObjects */

/* 4668 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4670 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4674 */	NdrFcShort( 0x7c ),	/* 124 */
/* 4676 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4680 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4682 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4684 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4686 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4688 */	NdrFcShort( 0x20 ),	/* 32 */
/* 4690 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4692 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4694 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4696 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 4698 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4700 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4702 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AttachedObjects */

/* 4704 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4706 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4710 */	NdrFcShort( 0x7d ),	/* 125 */
/* 4712 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4716 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4718 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4720 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4722 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4724 */	NdrFcShort( 0x20 ),	/* 32 */
/* 4726 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4728 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4730 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4732 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 4734 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4736 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4738 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReadAllBase64 */

/* 4740 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4742 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4746 */	NdrFcShort( 0x7e ),	/* 126 */
/* 4748 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4752 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4754 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 4756 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 4758 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4760 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4762 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter uri */

/* 4764 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4766 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4768 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter base64EncodedData */

/* 4770 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4772 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4774 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 4776 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4778 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4780 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DecryptionPFXCertFile */

/* 4782 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4784 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4788 */	NdrFcShort( 0x7f ),	/* 127 */
/* 4790 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4794 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4796 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4798 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4802 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4804 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4806 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4808 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4810 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 4812 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4814 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4816 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DecryptUsingPFXFileCert */

/* 4818 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4820 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4824 */	NdrFcShort( 0x80 ),	/* 128 */
/* 4826 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4828 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4830 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4832 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4834 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4836 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4840 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4842 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4844 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4846 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4848 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4850 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4852 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DecryptionPFXPassword */

/* 4854 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4856 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4860 */	NdrFcShort( 0x81 ),	/* 129 */
/* 4862 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4866 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4868 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4870 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4872 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4874 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4876 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4878 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4880 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4882 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 4884 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4886 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4888 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_XpathNamespace */

/* 4890 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4892 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4896 */	NdrFcShort( 0x82 ),	/* 130 */
/* 4898 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4900 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4902 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4904 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4906 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4908 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4910 */	NdrFcShort( 0x20 ),	/* 32 */
/* 4912 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4914 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4916 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4918 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 4920 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4922 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4924 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CamServerHost */

/* 4926 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4928 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4932 */	NdrFcShort( 0x83 ),	/* 131 */
/* 4934 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4936 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4938 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4940 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4942 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4944 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4946 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4948 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 4950 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4952 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4954 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 4956 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4958 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4960 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CamServerHost */

/* 4962 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4964 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4968 */	NdrFcShort( 0x84 ),	/* 132 */
/* 4970 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4972 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4974 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4976 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4978 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4980 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4982 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4984 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 4986 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4988 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4990 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 4992 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4994 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4996 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CamServerPort */

/* 4998 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5000 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5004 */	NdrFcShort( 0x85 ),	/* 133 */
/* 5006 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5008 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5010 */	NdrFcShort( 0x22 ),	/* 34 */
/* 5012 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5014 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5016 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5020 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 5022 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5024 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5026 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 5028 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5030 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5032 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CamServerPort */

/* 5034 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5036 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5040 */	NdrFcShort( 0x86 ),	/* 134 */
/* 5042 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5044 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5046 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5048 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5050 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5052 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5054 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5056 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 5058 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5060 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5062 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 5064 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5066 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5068 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_UseCam */

/* 5070 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5072 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5076 */	NdrFcShort( 0x87 ),	/* 135 */
/* 5078 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5080 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5082 */	NdrFcShort( 0x24 ),	/* 36 */
/* 5084 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5086 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5088 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5090 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5092 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 5094 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5096 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5098 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5100 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5102 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5104 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_UseCam */

/* 5106 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5108 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5112 */	NdrFcShort( 0x88 ),	/* 136 */
/* 5114 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5116 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5118 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5120 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5122 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5128 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 5130 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5132 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5134 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5136 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5138 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5140 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AgencyId */

/* 5142 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5144 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5148 */	NdrFcShort( 0x89 ),	/* 137 */
/* 5150 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5154 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5156 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 5158 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 5160 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5164 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 5166 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 5168 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5170 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 5172 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5174 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5176 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AgencyId */

/* 5178 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5180 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5184 */	NdrFcShort( 0x8a ),	/* 138 */
/* 5186 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5190 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5192 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 5194 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 5196 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5198 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5200 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 5202 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5204 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5206 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 5208 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5210 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5212 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CamValidationResponse */

/* 5214 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5216 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5220 */	NdrFcShort( 0x8b ),	/* 139 */
/* 5222 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5224 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5226 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5228 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 5230 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 5232 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5236 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 5238 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 5240 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5242 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 5244 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5246 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5248 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSigPropValueByName */

/* 5250 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5252 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5256 */	NdrFcShort( 0x8c ),	/* 140 */
/* 5258 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5260 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5262 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5264 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 5266 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 5268 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5270 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5272 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter sigIndex */

/* 5274 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5276 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5278 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter propName */

/* 5280 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5282 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5284 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter propValue */

/* 5286 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 5288 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5290 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 5292 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5294 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5296 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Base64DecodeBufferToFile */

/* 5298 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5300 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5304 */	NdrFcShort( 0x8d ),	/* 141 */
/* 5306 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5308 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5310 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5312 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 5314 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 5316 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5318 */	NdrFcShort( 0x2 ),	/* 2 */
/* 5320 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter encodedBuffer */

/* 5322 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5324 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5326 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter outFilePath */

/* 5328 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5330 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5332 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter decodedFilePath */

/* 5334 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 5336 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5338 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 5340 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5342 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5344 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Base64DecodeFileToFile */

/* 5346 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5348 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5352 */	NdrFcShort( 0x8e ),	/* 142 */
/* 5354 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5358 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5360 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 5362 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 5364 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5366 */	NdrFcShort( 0x2 ),	/* 2 */
/* 5368 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter encodedFilePath */

/* 5370 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5372 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5374 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter outFilePath */

/* 5376 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5378 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5380 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter decodedFilePath */

/* 5382 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 5384 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5386 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 5388 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5390 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5392 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GunZipFile */

/* 5394 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5396 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5400 */	NdrFcShort( 0x8f ),	/* 143 */
/* 5402 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5404 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5406 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5408 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 5410 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 5412 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5414 */	NdrFcShort( 0x2 ),	/* 2 */
/* 5416 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter gZippedFile */

/* 5418 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5420 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5422 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter gUnZippedFile */

/* 5424 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5426 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5428 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Parameter gUnZippedFilePath */

/* 5430 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 5432 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5434 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Return value */

/* 5436 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5438 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5440 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CertSerialNumberFormat */

/* 5442 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5444 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5448 */	NdrFcShort( 0x90 ),	/* 144 */
/* 5450 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5452 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5454 */	NdrFcShort( 0x24 ),	/* 36 */
/* 5456 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5458 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5460 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5464 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pValretval */

/* 5466 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5468 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5470 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5472 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5474 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5476 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_CertSerialNumberFormat */

/* 5478 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5480 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5484 */	NdrFcShort( 0x91 ),	/* 145 */
/* 5486 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5488 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5490 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5492 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5494 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5496 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5500 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 5502 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5504 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5506 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5508 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5510 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5512 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  8 */	NdrFcShort( 0x1c ),	/* Offset= 28 (36) */
/* 10 */	
			0x13, 0x0,	/* FC_OP */
/* 12 */	NdrFcShort( 0xe ),	/* Offset= 14 (26) */
/* 14 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 16 */	NdrFcShort( 0x2 ),	/* 2 */
/* 18 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 20 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 22 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 24 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 26 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 28 */	NdrFcShort( 0x8 ),	/* 8 */
/* 30 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (14) */
/* 32 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 34 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 36 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x4 ),	/* 4 */
/* 42 */	NdrFcShort( 0x0 ),	/* 0 */
/* 44 */	NdrFcShort( 0xffde ),	/* Offset= -34 (10) */
/* 46 */	
			0x12, 0x0,	/* FC_UP */
/* 48 */	NdrFcShort( 0xffea ),	/* Offset= -22 (26) */
/* 50 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0x4 ),	/* 4 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (46) */
/* 60 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 62 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 64 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 66 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 70 */	NdrFcShort( 0x0 ),	/* 0 */
/* 72 */	NdrFcShort( 0x0 ),	/* 0 */
/* 74 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 76 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 78 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 80 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 82 */	
			0x12, 0x0,	/* FC_UP */
/* 84 */	NdrFcShort( 0x3bc ),	/* Offset= 956 (1040) */
/* 86 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 88 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 90 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 92 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 94 */	NdrFcShort( 0x2 ),	/* Offset= 2 (96) */
/* 96 */	NdrFcShort( 0x10 ),	/* 16 */
/* 98 */	NdrFcShort( 0x2f ),	/* 47 */
/* 100 */	NdrFcLong( 0x14 ),	/* 20 */
/* 104 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 106 */	NdrFcLong( 0x3 ),	/* 3 */
/* 110 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 112 */	NdrFcLong( 0x11 ),	/* 17 */
/* 116 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 118 */	NdrFcLong( 0x2 ),	/* 2 */
/* 122 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 124 */	NdrFcLong( 0x4 ),	/* 4 */
/* 128 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 130 */	NdrFcLong( 0x5 ),	/* 5 */
/* 134 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 136 */	NdrFcLong( 0xb ),	/* 11 */
/* 140 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 142 */	NdrFcLong( 0xa ),	/* 10 */
/* 146 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 148 */	NdrFcLong( 0x6 ),	/* 6 */
/* 152 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (384) */
/* 154 */	NdrFcLong( 0x7 ),	/* 7 */
/* 158 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 160 */	NdrFcLong( 0x8 ),	/* 8 */
/* 164 */	NdrFcShort( 0xff8a ),	/* Offset= -118 (46) */
/* 166 */	NdrFcLong( 0xd ),	/* 13 */
/* 170 */	NdrFcShort( 0xdc ),	/* Offset= 220 (390) */
/* 172 */	NdrFcLong( 0x9 ),	/* 9 */
/* 176 */	NdrFcShort( 0xff90 ),	/* Offset= -112 (64) */
/* 178 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 182 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (408) */
/* 184 */	NdrFcLong( 0x24 ),	/* 36 */
/* 188 */	NdrFcShort( 0x30a ),	/* Offset= 778 (966) */
/* 190 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 194 */	NdrFcShort( 0x304 ),	/* Offset= 772 (966) */
/* 196 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 200 */	NdrFcShort( 0x302 ),	/* Offset= 770 (970) */
/* 202 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 206 */	NdrFcShort( 0x300 ),	/* Offset= 768 (974) */
/* 208 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 212 */	NdrFcShort( 0x2fe ),	/* Offset= 766 (978) */
/* 214 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 218 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (982) */
/* 220 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 224 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (986) */
/* 226 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 230 */	NdrFcShort( 0x2f8 ),	/* Offset= 760 (990) */
/* 232 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 236 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (974) */
/* 238 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 242 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (978) */
/* 244 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 248 */	NdrFcShort( 0x2ea ),	/* Offset= 746 (994) */
/* 250 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 254 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (990) */
/* 256 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 260 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (998) */
/* 262 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 266 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (1002) */
/* 268 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 272 */	NdrFcShort( 0x2de ),	/* Offset= 734 (1006) */
/* 274 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 278 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (1010) */
/* 280 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 284 */	NdrFcShort( 0x2da ),	/* Offset= 730 (1014) */
/* 286 */	NdrFcLong( 0x10 ),	/* 16 */
/* 290 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 292 */	NdrFcLong( 0x12 ),	/* 18 */
/* 296 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 298 */	NdrFcLong( 0x13 ),	/* 19 */
/* 302 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 304 */	NdrFcLong( 0x15 ),	/* 21 */
/* 308 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 310 */	NdrFcLong( 0x16 ),	/* 22 */
/* 314 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 316 */	NdrFcLong( 0x17 ),	/* 23 */
/* 320 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 322 */	NdrFcLong( 0xe ),	/* 14 */
/* 326 */	NdrFcShort( 0x2b8 ),	/* Offset= 696 (1022) */
/* 328 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 332 */	NdrFcShort( 0x2bc ),	/* Offset= 700 (1032) */
/* 334 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 338 */	NdrFcShort( 0x2ba ),	/* Offset= 698 (1036) */
/* 340 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 344 */	NdrFcShort( 0x276 ),	/* Offset= 630 (974) */
/* 346 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 350 */	NdrFcShort( 0x274 ),	/* Offset= 628 (978) */
/* 352 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 356 */	NdrFcShort( 0x272 ),	/* Offset= 626 (982) */
/* 358 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 362 */	NdrFcShort( 0x268 ),	/* Offset= 616 (978) */
/* 364 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 368 */	NdrFcShort( 0x262 ),	/* Offset= 610 (978) */
/* 370 */	NdrFcLong( 0x0 ),	/* 0 */
/* 374 */	NdrFcShort( 0x0 ),	/* Offset= 0 (374) */
/* 376 */	NdrFcLong( 0x1 ),	/* 1 */
/* 380 */	NdrFcShort( 0x0 ),	/* Offset= 0 (380) */
/* 382 */	NdrFcShort( 0xffff ),	/* Offset= -1 (381) */
/* 384 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 386 */	NdrFcShort( 0x8 ),	/* 8 */
/* 388 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 390 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 392 */	NdrFcLong( 0x0 ),	/* 0 */
/* 396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 400 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 402 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 404 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 406 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 408 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 410 */	NdrFcShort( 0x2 ),	/* Offset= 2 (412) */
/* 412 */	
			0x12, 0x0,	/* FC_UP */
/* 414 */	NdrFcShort( 0x216 ),	/* Offset= 534 (948) */
/* 416 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 418 */	NdrFcShort( 0x18 ),	/* 24 */
/* 420 */	NdrFcShort( 0xa ),	/* 10 */
/* 422 */	NdrFcLong( 0x8 ),	/* 8 */
/* 426 */	NdrFcShort( 0x5a ),	/* Offset= 90 (516) */
/* 428 */	NdrFcLong( 0xd ),	/* 13 */
/* 432 */	NdrFcShort( 0x7e ),	/* Offset= 126 (558) */
/* 434 */	NdrFcLong( 0x9 ),	/* 9 */
/* 438 */	NdrFcShort( 0x9e ),	/* Offset= 158 (596) */
/* 440 */	NdrFcLong( 0xc ),	/* 12 */
/* 444 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (644) */
/* 446 */	NdrFcLong( 0x24 ),	/* 36 */
/* 450 */	NdrFcShort( 0x124 ),	/* Offset= 292 (742) */
/* 452 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 456 */	NdrFcShort( 0x140 ),	/* Offset= 320 (776) */
/* 458 */	NdrFcLong( 0x10 ),	/* 16 */
/* 462 */	NdrFcShort( 0x15a ),	/* Offset= 346 (808) */
/* 464 */	NdrFcLong( 0x2 ),	/* 2 */
/* 468 */	NdrFcShort( 0x174 ),	/* Offset= 372 (840) */
/* 470 */	NdrFcLong( 0x3 ),	/* 3 */
/* 474 */	NdrFcShort( 0x18e ),	/* Offset= 398 (872) */
/* 476 */	NdrFcLong( 0x14 ),	/* 20 */
/* 480 */	NdrFcShort( 0x1a8 ),	/* Offset= 424 (904) */
/* 482 */	NdrFcShort( 0xffff ),	/* Offset= -1 (481) */
/* 484 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 486 */	NdrFcShort( 0x4 ),	/* 4 */
/* 488 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 490 */	NdrFcShort( 0x0 ),	/* 0 */
/* 492 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 494 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 496 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 498 */	NdrFcShort( 0x4 ),	/* 4 */
/* 500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 502 */	NdrFcShort( 0x1 ),	/* 1 */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 508 */	0x12, 0x0,	/* FC_UP */
/* 510 */	NdrFcShort( 0xfe1c ),	/* Offset= -484 (26) */
/* 512 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 514 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 516 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 518 */	NdrFcShort( 0x8 ),	/* 8 */
/* 520 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 522 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 524 */	NdrFcShort( 0x4 ),	/* 4 */
/* 526 */	NdrFcShort( 0x4 ),	/* 4 */
/* 528 */	0x11, 0x0,	/* FC_RP */
/* 530 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (484) */
/* 532 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 534 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 536 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 540 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 544 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 546 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 550 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 552 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 554 */	NdrFcShort( 0xff5c ),	/* Offset= -164 (390) */
/* 556 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 558 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 560 */	NdrFcShort( 0x8 ),	/* 8 */
/* 562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 564 */	NdrFcShort( 0x6 ),	/* Offset= 6 (570) */
/* 566 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 568 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 570 */	
			0x11, 0x0,	/* FC_RP */
/* 572 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (536) */
/* 574 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 576 */	NdrFcShort( 0x0 ),	/* 0 */
/* 578 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 584 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 588 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 590 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 592 */	NdrFcShort( 0xfdf0 ),	/* Offset= -528 (64) */
/* 594 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 596 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 598 */	NdrFcShort( 0x8 ),	/* 8 */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	NdrFcShort( 0x6 ),	/* Offset= 6 (608) */
/* 604 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 606 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 608 */	
			0x11, 0x0,	/* FC_RP */
/* 610 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (574) */
/* 612 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 614 */	NdrFcShort( 0x4 ),	/* 4 */
/* 616 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 622 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 624 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 626 */	NdrFcShort( 0x4 ),	/* 4 */
/* 628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 630 */	NdrFcShort( 0x1 ),	/* 1 */
/* 632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 636 */	0x12, 0x0,	/* FC_UP */
/* 638 */	NdrFcShort( 0x192 ),	/* Offset= 402 (1040) */
/* 640 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 642 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 644 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 646 */	NdrFcShort( 0x8 ),	/* 8 */
/* 648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 650 */	NdrFcShort( 0x6 ),	/* Offset= 6 (656) */
/* 652 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 654 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 656 */	
			0x11, 0x0,	/* FC_RP */
/* 658 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (612) */
/* 660 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 662 */	NdrFcLong( 0x2f ),	/* 47 */
/* 666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 670 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 672 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 674 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 676 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 678 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 680 */	NdrFcShort( 0x1 ),	/* 1 */
/* 682 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 684 */	NdrFcShort( 0x4 ),	/* 4 */
/* 686 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 688 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 690 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 692 */	NdrFcShort( 0x10 ),	/* 16 */
/* 694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 696 */	NdrFcShort( 0xa ),	/* Offset= 10 (706) */
/* 698 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 700 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 702 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (660) */
/* 704 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 706 */	
			0x12, 0x0,	/* FC_UP */
/* 708 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (678) */
/* 710 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 712 */	NdrFcShort( 0x4 ),	/* 4 */
/* 714 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 716 */	NdrFcShort( 0x0 ),	/* 0 */
/* 718 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 720 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 722 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 724 */	NdrFcShort( 0x4 ),	/* 4 */
/* 726 */	NdrFcShort( 0x0 ),	/* 0 */
/* 728 */	NdrFcShort( 0x1 ),	/* 1 */
/* 730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 734 */	0x12, 0x0,	/* FC_UP */
/* 736 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (690) */
/* 738 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 740 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 742 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 744 */	NdrFcShort( 0x8 ),	/* 8 */
/* 746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 748 */	NdrFcShort( 0x6 ),	/* Offset= 6 (754) */
/* 750 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 752 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 754 */	
			0x11, 0x0,	/* FC_RP */
/* 756 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (710) */
/* 758 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 760 */	NdrFcShort( 0x8 ),	/* 8 */
/* 762 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 764 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 766 */	NdrFcShort( 0x10 ),	/* 16 */
/* 768 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 770 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 772 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (758) */
			0x5b,		/* FC_END */
/* 776 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 778 */	NdrFcShort( 0x18 ),	/* 24 */
/* 780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 782 */	NdrFcShort( 0xa ),	/* Offset= 10 (792) */
/* 784 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 786 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 788 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (764) */
/* 790 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 792 */	
			0x11, 0x0,	/* FC_RP */
/* 794 */	NdrFcShort( 0xfefe ),	/* Offset= -258 (536) */
/* 796 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 798 */	NdrFcShort( 0x1 ),	/* 1 */
/* 800 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 806 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 808 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 812 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 814 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 816 */	NdrFcShort( 0x4 ),	/* 4 */
/* 818 */	NdrFcShort( 0x4 ),	/* 4 */
/* 820 */	0x12, 0x0,	/* FC_UP */
/* 822 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (796) */
/* 824 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 826 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 828 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 830 */	NdrFcShort( 0x2 ),	/* 2 */
/* 832 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 834 */	NdrFcShort( 0x0 ),	/* 0 */
/* 836 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 838 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 840 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 842 */	NdrFcShort( 0x8 ),	/* 8 */
/* 844 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 846 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 848 */	NdrFcShort( 0x4 ),	/* 4 */
/* 850 */	NdrFcShort( 0x4 ),	/* 4 */
/* 852 */	0x12, 0x0,	/* FC_UP */
/* 854 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (828) */
/* 856 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 858 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 860 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 862 */	NdrFcShort( 0x4 ),	/* 4 */
/* 864 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 868 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 870 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 872 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 874 */	NdrFcShort( 0x8 ),	/* 8 */
/* 876 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 878 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 880 */	NdrFcShort( 0x4 ),	/* 4 */
/* 882 */	NdrFcShort( 0x4 ),	/* 4 */
/* 884 */	0x12, 0x0,	/* FC_UP */
/* 886 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (860) */
/* 888 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 890 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 892 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 894 */	NdrFcShort( 0x8 ),	/* 8 */
/* 896 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 898 */	NdrFcShort( 0x0 ),	/* 0 */
/* 900 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 902 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 904 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 906 */	NdrFcShort( 0x8 ),	/* 8 */
/* 908 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 910 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 912 */	NdrFcShort( 0x4 ),	/* 4 */
/* 914 */	NdrFcShort( 0x4 ),	/* 4 */
/* 916 */	0x12, 0x0,	/* FC_UP */
/* 918 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (892) */
/* 920 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 922 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 924 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 926 */	NdrFcShort( 0x8 ),	/* 8 */
/* 928 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 930 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 932 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 934 */	NdrFcShort( 0x8 ),	/* 8 */
/* 936 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 938 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 940 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 942 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 944 */	NdrFcShort( 0xffec ),	/* Offset= -20 (924) */
/* 946 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 948 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 950 */	NdrFcShort( 0x28 ),	/* 40 */
/* 952 */	NdrFcShort( 0xffec ),	/* Offset= -20 (932) */
/* 954 */	NdrFcShort( 0x0 ),	/* Offset= 0 (954) */
/* 956 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 958 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 960 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 962 */	NdrFcShort( 0xfdde ),	/* Offset= -546 (416) */
/* 964 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 966 */	
			0x12, 0x0,	/* FC_UP */
/* 968 */	NdrFcShort( 0xfeea ),	/* Offset= -278 (690) */
/* 970 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 972 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 974 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 976 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 978 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 980 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 982 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 984 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 986 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 988 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 990 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 992 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 994 */	
			0x12, 0x0,	/* FC_UP */
/* 996 */	NdrFcShort( 0xfd9c ),	/* Offset= -612 (384) */
/* 998 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1000 */	NdrFcShort( 0xfc46 ),	/* Offset= -954 (46) */
/* 1002 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1004 */	NdrFcShort( 0xfd9a ),	/* Offset= -614 (390) */
/* 1006 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1008 */	NdrFcShort( 0xfc50 ),	/* Offset= -944 (64) */
/* 1010 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1012 */	NdrFcShort( 0xfda4 ),	/* Offset= -604 (408) */
/* 1014 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1016 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1018) */
/* 1018 */	
			0x12, 0x0,	/* FC_UP */
/* 1020 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1040) */
/* 1022 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1024 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1026 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 1028 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 1030 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1032 */	
			0x12, 0x0,	/* FC_UP */
/* 1034 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1022) */
/* 1036 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1038 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1040 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1042 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1046 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1046) */
/* 1048 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1050 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1052 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1054 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1056 */	NdrFcShort( 0xfc36 ),	/* Offset= -970 (86) */
/* 1058 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1060 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1062 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1064 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1066 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1068 */	NdrFcShort( 0xfc26 ),	/* Offset= -986 (82) */
/* 1070 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1072 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1078) */
/* 1074 */	
			0x13, 0x0,	/* FC_OP */
/* 1076 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1040) */
/* 1078 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1080 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1082 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1086 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1074) */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ISignature, ver. 0.0,
   GUID={0x62EC64DC,0xB26D,0x46CE,{0x9E,0x33,0x24,0x28,0x9B,0xCF,0x5F,0x63}} */

#pragma code_seg(".orpc")
static const unsigned short ISignature_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    36,
    72,
    108,
    144,
    186,
    228,
    270,
    312,
    360,
    408,
    444,
    480,
    516,
    552,
    600,
    648,
    684,
    720,
    762,
    798,
    834,
    870,
    906,
    942,
    984,
    1020,
    1056,
    1092,
    1134,
    1170,
    1206,
    1254,
    1296,
    1332,
    1374,
    1410,
    1446,
    1494,
    1536,
    1584,
    1626,
    1668,
    1710,
    1752,
    1794,
    1830,
    1866,
    1908,
    1950,
    1992,
    2028,
    2076,
    2118,
    2166,
    2208,
    2250,
    2286,
    2328,
    2370,
    2418,
    2454,
    2490,
    2538,
    2574,
    2610,
    2652,
    2688,
    2724,
    2766,
    2814,
    2856,
    2892,
    2928,
    2964,
    3000,
    3036,
    3072,
    3108,
    3144,
    3198,
    3252,
    3312,
    3348,
    3384,
    3420,
    3456,
    3492,
    3528,
    3564,
    3600,
    3636,
    3672,
    3708,
    3744,
    3780,
    3816,
    3852,
    3906,
    3942,
    3978,
    4014,
    4050,
    4092,
    4128,
    4164,
    4206,
    4242,
    4284,
    4332,
    4380,
    4416,
    4458,
    4500,
    4548,
    4596,
    4632,
    4668,
    4704,
    4740,
    4782,
    4818,
    4854,
    4890,
    4926,
    4962,
    4998,
    5034,
    5070,
    5106,
    5142,
    5178,
    5214,
    5250,
    5298,
    5346,
    5394,
    5442,
    5478
    };

static const MIDL_STUBLESS_PROXY_INFO ISignature_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISignature_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISignature_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISignature_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(146) _ISignatureProxyVtbl = 
{
    &ISignature_ProxyInfo,
    &IID_ISignature,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_EnvelopingFlag */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_EnvelopingFlag */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_RecipientCertificateStore */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_RecipientCertificateStore */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_SignerCertificate */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_SignerCertificate */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_SignatureID */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_SignatureID */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_Properties */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_Properties */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_Base64EncodeXML */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_Base64EncodeXML */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_Base64DecodeXML */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_Base64DecodeXML */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_DocumentURI */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_DigestObjectStatus */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_CaptureOnce */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_CaptureOnce */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_SignatureStatus */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_PhysicalSignatureUsage */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_PhysicalSignatureUsage */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_PhysicalSignatureFile */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_PhysicalSignatureFile */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_CapturedSignatureFile */ ,
    (void *) (INT_PTR) -1 /* ISignature::Sign */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_IncludeCamResponse */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_IncludeCamResponse */ ,
    (void *) (INT_PTR) -1 /* ISignature::SaveXMLSignature */ ,
    (void *) (INT_PTR) -1 /* ISignature::Verify */ ,
    (void *) (INT_PTR) -1 /* ISignature::GetError */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_OverwriteFile */ ,
    (void *) (INT_PTR) -1 /* ISignature::PFXExportCertificate */ ,
    (void *) (INT_PTR) -1 /* ISignature::VerifyDetached */ ,
    (void *) (INT_PTR) -1 /* ISignature::GetLastError */ ,
    (void *) (INT_PTR) -1 /* ISignature::GetX509Certificate */ ,
    (void *) (INT_PTR) -1 /* ISignature::ViewCertificate */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_CertificateCount */ ,
    (void *) (INT_PTR) -1 /* ISignature::GetCertificateInfo */ ,
    (void *) (INT_PTR) -1 /* ISignature::SetActiveCertificate */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_SignedDocumentPath */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_SignerSubject */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_CertIssuer */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_CertExpiry */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_CertSerialNumber */ ,
    (void *) (INT_PTR) -1 /* ISignature::FileExists */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_FailedUriCount */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_TotalUriCount */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_FailedUriFullPath */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_FailedUriFullPath */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_FailedUri */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_SignatureCount */ ,
    (void *) (INT_PTR) -1 /* ISignature::SignXMLStr */ ,
    (void *) (INT_PTR) -1 /* ISignature::ReadAll */ ,
    (void *) (INT_PTR) -1 /* ISignature::SaveXMLStr */ ,
    (void *) (INT_PTR) -1 /* ISignature::SignHTML */ ,
    (void *) (INT_PTR) -1 /* ISignature::SecureXMLVerify */ ,
    (void *) (INT_PTR) -1 /* ISignature::SetCSP */ ,
    (void *) (INT_PTR) -1 /* ISignature::GetSignedHTML */ ,
    (void *) (INT_PTR) -1 /* ISignature::SignFile */ ,
    (void *) (INT_PTR) -1 /* ISignature::GetSignedFileObject */ ,
    (void *) (INT_PTR) -1 /* ISignature::SetStoreName */ ,
    (void *) (INT_PTR) -1 /* ISignature::GetStoreName */ ,
    (void *) (INT_PTR) -1 /* ISignature::SignXMLEnveloped */ ,
    (void *) (INT_PTR) -1 /* ISignature::GetVersion */ ,
    (void *) (INT_PTR) -1 /* ISignature::GetLicenseStatus */ ,
    (void *) (INT_PTR) -1 /* ISignature::GetPropertyCount */ ,
    (void *) (INT_PTR) -1 /* ISignature::ViewAnyCertificate */ ,
    (void *) (INT_PTR) -1 /* ISignature::SelectActiveCertificate */ ,
    (void *) (INT_PTR) -1 /* ISignature::VerifyXMLStr */ ,
    (void *) (INT_PTR) -1 /* ISignature::SetActivePFXFileCert */ ,
    (void *) (INT_PTR) -1 /* ISignature::PFXExportActiveCertificate */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_HostName */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_TimeStampURL */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_TimeStampURL */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_TimeStamping */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_TimeStamping */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_HostOsType */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_CrlChecking */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_CrlChecking */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_SigCertStatus */ ,
    (void *) (INT_PTR) -1 /* ISignature::VerifyX509CertCRL */ ,
    (void *) (INT_PTR) -1 /* ISignature::VerifyPFXCertCRL */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_AddWindowImage */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_AddWindowImage */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_CRLLocation */ ,
    (void *) (INT_PTR) -1 /* ISignature::VerifyActiveCertificate */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_CertificatePolicy */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_AuthorityConstrainedPolicy */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_UserConstrainedPolicy */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_CertificatePolicyChecking */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_CertificateChainValidation */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_CertificatePathLengthChecking */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_ConfigFileName */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_DoDCompliance */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_CertificatePolicyExplicit */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_CertificatePolicyExplicit */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_CertificateTrustExplicit */ ,
    (void *) (INT_PTR) -1 /* ISignature::SignXMLXpathStr */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_UseHMAC */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_UseHMAC */ ,
    (void *) (INT_PTR) -1 /* ISignature::get_HMACPassword */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_HMACPassword */ ,
    (void *) (INT_PTR) -1 /* ISignature::ChangeOrAddProperty */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_DetailedVerificationFlag */ ,
    (void *) (INT_PTR) -1 /* ISignature::CaptureLiveSignature */ ,
    (void *) (INT_PTR) -1 /* ISignature::SignDataStr */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_ExcludeSignerCertificate */ ,
    (void *) (INT_PTR) -1 /* ISignature::CoSignXMLStr */ ,
    (void *) (INT_PTR) -1 /* ISignature::CoSignFile */ ,
    (void *) (INT_PTR) -1 /* ISignature::SignFiles */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_RecipientCertificates */ ,
    (void *) (INT_PTR) -1 /* ISignature::EncryptStr */ ,
    (void *) (INT_PTR) -1 /* ISignature::DecryptStr */ ,
    (void *) (INT_PTR) -1 /* ISignature::EncryptFile */ ,
    (void *) (INT_PTR) -1 /* ISignature::DecryptFile */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_TrustedRoots */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_RecipientCertificateFiles */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_DetachedObjects */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_AttachedObjects */ ,
    (void *) (INT_PTR) -1 /* ISignature::ReadAllBase64 */ ,
    (void *) (INT_PTR) -1 /* ISignature::put_DecryptionPFXCertFile */ ,
    ISignature_put_DecryptUsingPFXFileCert_Proxy ,
    ISignature_put_DecryptionPFXPassword_Proxy ,
    ISignature_put_XpathNamespace_Proxy ,
    ISignature_get_CamServerHost_Proxy ,
    ISignature_put_CamServerHost_Proxy ,
    ISignature_get_CamServerPort_Proxy ,
    ISignature_put_CamServerPort_Proxy ,
    ISignature_get_UseCam_Proxy ,
    ISignature_put_UseCam_Proxy ,
    ISignature_get_AgencyId_Proxy ,
    ISignature_put_AgencyId_Proxy ,
    ISignature_get_CamValidationResponse_Proxy ,
    ISignature_GetSigPropValueByName_Proxy ,
    ISignature_Base64DecodeBufferToFile_Proxy ,
    ISignature_Base64DecodeFileToFile_Proxy ,
    ISignature_GunZipFile_Proxy ,
    ISignature_get_CertSerialNumberFormat_Proxy ,
    ISignature_put_CertSerialNumberFormat_Proxy
};


static const PRPC_STUB_FUNCTION ISignature_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _ISignatureStubVtbl =
{
    &IID_ISignature,
    &ISignature_ServerInfo,
    146,
    &ISignature_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x6000169, /* MIDL Version 6.0.361 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _XMLSign_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ISignatureProxyVtbl,
    0
};

const CInterfaceStubVtbl * _XMLSign_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ISignatureStubVtbl,
    0
};

PCInterfaceName const _XMLSign_InterfaceNamesList[] = 
{
    "ISignature",
    0
};

const IID *  _XMLSign_BaseIIDList[] = 
{
    &IID_IDispatch,
    0
};


#define _XMLSign_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _XMLSign, pIID, n)

int __stdcall _XMLSign_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_XMLSign_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo XMLSign_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _XMLSign_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _XMLSign_StubVtblList,
    (const PCInterfaceName * ) & _XMLSign_InterfaceNamesList,
    (const IID ** ) & _XMLSign_BaseIIDList,
    & _XMLSign_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/
