/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu May 15 14:43:42 2003
 */
/* Compiler settings for C:\ActiveX\XMLSign\include\SecurePad\SecurePad.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __SecurePad_h__
#define __SecurePad_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IePad_FWD_DEFINED__
#define __IePad_FWD_DEFINED__
typedef interface IePad IePad;
#endif 	/* __IePad_FWD_DEFINED__ */


#ifndef __ePad_FWD_DEFINED__
#define __ePad_FWD_DEFINED__

#ifdef __cplusplus
typedef class ePad ePad;
#else
typedef struct ePad ePad;
#endif /* __cplusplus */

#endif 	/* __ePad_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IePad_INTERFACE_DEFINED__
#define __IePad_INTERFACE_DEFINED__

/* interface IePad */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IePad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F5734F4F-8013-496B-A7F6-10D2F1C048FD")
    IePad : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPhysicalSignature( 
            /* [in] */ BSTR bstrGuidStr,
            /* [retval][out] */ BSTR __RPC_FAR *sigFilePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEpadPropXML( 
            /* [retval][out] */ BSTR __RPC_FAR *ePadPropXML) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UpperX( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UpperX( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UpperY( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UpperY( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPenColor( 
            /* [in] */ long red,
            /* [in] */ long green,
            /* [in] */ long blue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IePadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IePad __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IePad __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IePad __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IePad __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IePad __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IePad __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IePad __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPhysicalSignature )( 
            IePad __RPC_FAR * This,
            /* [in] */ BSTR bstrGuidStr,
            /* [retval][out] */ BSTR __RPC_FAR *sigFilePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEpadPropXML )( 
            IePad __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ePadPropXML);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UpperX )( 
            IePad __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UpperX )( 
            IePad __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UpperY )( 
            IePad __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UpperY )( 
            IePad __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IePad __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            IePad __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IePad __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            IePad __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPenColor )( 
            IePad __RPC_FAR * This,
            /* [in] */ long red,
            /* [in] */ long green,
            /* [in] */ long blue);
        
        END_INTERFACE
    } IePadVtbl;

    interface IePad
    {
        CONST_VTBL struct IePadVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IePad_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IePad_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IePad_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IePad_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IePad_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IePad_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IePad_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IePad_GetPhysicalSignature(This,bstrGuidStr,sigFilePath)	\
    (This)->lpVtbl -> GetPhysicalSignature(This,bstrGuidStr,sigFilePath)

#define IePad_GetEpadPropXML(This,ePadPropXML)	\
    (This)->lpVtbl -> GetEpadPropXML(This,ePadPropXML)

#define IePad_get_UpperX(This,pVal)	\
    (This)->lpVtbl -> get_UpperX(This,pVal)

#define IePad_put_UpperX(This,newVal)	\
    (This)->lpVtbl -> put_UpperX(This,newVal)

#define IePad_get_UpperY(This,pVal)	\
    (This)->lpVtbl -> get_UpperY(This,pVal)

#define IePad_put_UpperY(This,newVal)	\
    (This)->lpVtbl -> put_UpperY(This,newVal)

#define IePad_get_Width(This,pVal)	\
    (This)->lpVtbl -> get_Width(This,pVal)

#define IePad_put_Width(This,newVal)	\
    (This)->lpVtbl -> put_Width(This,newVal)

#define IePad_get_Height(This,pVal)	\
    (This)->lpVtbl -> get_Height(This,pVal)

#define IePad_put_Height(This,newVal)	\
    (This)->lpVtbl -> put_Height(This,newVal)

#define IePad_SetPenColor(This,red,green,blue)	\
    (This)->lpVtbl -> SetPenColor(This,red,green,blue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IePad_GetPhysicalSignature_Proxy( 
    IePad __RPC_FAR * This,
    /* [in] */ BSTR bstrGuidStr,
    /* [retval][out] */ BSTR __RPC_FAR *sigFilePath);


void __RPC_STUB IePad_GetPhysicalSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IePad_GetEpadPropXML_Proxy( 
    IePad __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ePadPropXML);


void __RPC_STUB IePad_GetEpadPropXML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IePad_get_UpperX_Proxy( 
    IePad __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IePad_get_UpperX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IePad_put_UpperX_Proxy( 
    IePad __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IePad_put_UpperX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IePad_get_UpperY_Proxy( 
    IePad __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IePad_get_UpperY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IePad_put_UpperY_Proxy( 
    IePad __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IePad_put_UpperY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IePad_get_Width_Proxy( 
    IePad __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IePad_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IePad_put_Width_Proxy( 
    IePad __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IePad_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IePad_get_Height_Proxy( 
    IePad __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IePad_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IePad_put_Height_Proxy( 
    IePad __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IePad_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IePad_SetPenColor_Proxy( 
    IePad __RPC_FAR * This,
    /* [in] */ long red,
    /* [in] */ long green,
    /* [in] */ long blue);


void __RPC_STUB IePad_SetPenColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IePad_INTERFACE_DEFINED__ */



#ifndef __SECUREPADLib_LIBRARY_DEFINED__
#define __SECUREPADLib_LIBRARY_DEFINED__

/* library SECUREPADLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SECUREPADLib;

EXTERN_C const CLSID CLSID_ePad;

#ifdef __cplusplus

class DECLSPEC_UUID("ACC8C50C-31C8-4453-A535-84C5F8C9F99A")
ePad;
#endif
#endif /* __SECUREPADLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
