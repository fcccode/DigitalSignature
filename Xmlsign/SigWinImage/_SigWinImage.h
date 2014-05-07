

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue Jun 26 10:02:02 2007
 */
/* Compiler settings for _SigWinImage.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef ___SigWinImage_h__
#define ___SigWinImage_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICaptureImage_FWD_DEFINED__
#define __ICaptureImage_FWD_DEFINED__
typedef interface ICaptureImage ICaptureImage;
#endif 	/* __ICaptureImage_FWD_DEFINED__ */


#ifndef __CCaptureImage_FWD_DEFINED__
#define __CCaptureImage_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCaptureImage CCaptureImage;
#else
typedef struct CCaptureImage CCaptureImage;
#endif /* __cplusplus */

#endif 	/* __CCaptureImage_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ICaptureImage_INTERFACE_DEFINED__
#define __ICaptureImage_INTERFACE_DEFINED__

/* interface ICaptureImage */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICaptureImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0674A7D1-0A9C-4FE4-B914-96BCC6EDC4CF")
    ICaptureImage : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CaptureCurrentWindowImage( 
            /* [retval][out] */ BSTR *WindowImageFileName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PhysicalSignatureFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UpperX( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UpperY( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowFileSignature( 
            /* [in] */ BSTR guidStr,
            /* [retval][out] */ BSTR *outPngFilePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CaptureMouseSignature( 
            /* [in] */ BSTR guidStr,
            /* [retval][out] */ BSTR *outPngFilePath) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICaptureImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICaptureImage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICaptureImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICaptureImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICaptureImage * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICaptureImage * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICaptureImage * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICaptureImage * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CaptureCurrentWindowImage )( 
            ICaptureImage * This,
            /* [retval][out] */ BSTR *WindowImageFileName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PhysicalSignatureFile )( 
            ICaptureImage * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UpperX )( 
            ICaptureImage * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UpperY )( 
            ICaptureImage * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            ICaptureImage * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            ICaptureImage * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowFileSignature )( 
            ICaptureImage * This,
            /* [in] */ BSTR guidStr,
            /* [retval][out] */ BSTR *outPngFilePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CaptureMouseSignature )( 
            ICaptureImage * This,
            /* [in] */ BSTR guidStr,
            /* [retval][out] */ BSTR *outPngFilePath);
        
        END_INTERFACE
    } ICaptureImageVtbl;

    interface ICaptureImage
    {
        CONST_VTBL struct ICaptureImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICaptureImage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICaptureImage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICaptureImage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICaptureImage_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICaptureImage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICaptureImage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICaptureImage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICaptureImage_CaptureCurrentWindowImage(This,WindowImageFileName)	\
    (This)->lpVtbl -> CaptureCurrentWindowImage(This,WindowImageFileName)

#define ICaptureImage_put_PhysicalSignatureFile(This,newVal)	\
    (This)->lpVtbl -> put_PhysicalSignatureFile(This,newVal)

#define ICaptureImage_put_UpperX(This,newVal)	\
    (This)->lpVtbl -> put_UpperX(This,newVal)

#define ICaptureImage_put_UpperY(This,newVal)	\
    (This)->lpVtbl -> put_UpperY(This,newVal)

#define ICaptureImage_put_Width(This,newVal)	\
    (This)->lpVtbl -> put_Width(This,newVal)

#define ICaptureImage_put_Height(This,newVal)	\
    (This)->lpVtbl -> put_Height(This,newVal)

#define ICaptureImage_ShowFileSignature(This,guidStr,outPngFilePath)	\
    (This)->lpVtbl -> ShowFileSignature(This,guidStr,outPngFilePath)

#define ICaptureImage_CaptureMouseSignature(This,guidStr,outPngFilePath)	\
    (This)->lpVtbl -> CaptureMouseSignature(This,guidStr,outPngFilePath)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICaptureImage_CaptureCurrentWindowImage_Proxy( 
    ICaptureImage * This,
    /* [retval][out] */ BSTR *WindowImageFileName);


void __RPC_STUB ICaptureImage_CaptureCurrentWindowImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICaptureImage_put_PhysicalSignatureFile_Proxy( 
    ICaptureImage * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ICaptureImage_put_PhysicalSignatureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICaptureImage_put_UpperX_Proxy( 
    ICaptureImage * This,
    /* [in] */ LONG newVal);


void __RPC_STUB ICaptureImage_put_UpperX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICaptureImage_put_UpperY_Proxy( 
    ICaptureImage * This,
    /* [in] */ LONG newVal);


void __RPC_STUB ICaptureImage_put_UpperY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICaptureImage_put_Width_Proxy( 
    ICaptureImage * This,
    /* [in] */ LONG newVal);


void __RPC_STUB ICaptureImage_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICaptureImage_put_Height_Proxy( 
    ICaptureImage * This,
    /* [in] */ LONG newVal);


void __RPC_STUB ICaptureImage_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICaptureImage_ShowFileSignature_Proxy( 
    ICaptureImage * This,
    /* [in] */ BSTR guidStr,
    /* [retval][out] */ BSTR *outPngFilePath);


void __RPC_STUB ICaptureImage_ShowFileSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICaptureImage_CaptureMouseSignature_Proxy( 
    ICaptureImage * This,
    /* [in] */ BSTR guidStr,
    /* [retval][out] */ BSTR *outPngFilePath);


void __RPC_STUB ICaptureImage_CaptureMouseSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICaptureImage_INTERFACE_DEFINED__ */



#ifndef __SigWinImage_LIBRARY_DEFINED__
#define __SigWinImage_LIBRARY_DEFINED__

/* library SigWinImage */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_SigWinImage;

EXTERN_C const CLSID CLSID_CCaptureImage;

#ifdef __cplusplus

class DECLSPEC_UUID("F18805CC-5075-4D36-BB01-76A4CAF6EE31")
CCaptureImage;
#endif
#endif /* __SigWinImage_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


