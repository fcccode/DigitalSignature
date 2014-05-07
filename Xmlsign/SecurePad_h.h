

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Wed Jun 27 14:56:41 2007
 */
/* Compiler settings for .\include\SecurePad\SecurePad.idl:
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

#ifndef __SecurePad_h_h__
#define __SecurePad_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
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

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

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
            /* [retval][out] */ BSTR *sigFilePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEpadPropXML( 
            /* [retval][out] */ BSTR *ePadPropXML) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UpperX( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UpperX( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UpperY( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UpperY( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long *pVal) = 0;
        
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
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IePad * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IePad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IePad * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IePad * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IePad * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IePad * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IePad * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPhysicalSignature )( 
            IePad * This,
            /* [in] */ BSTR bstrGuidStr,
            /* [retval][out] */ BSTR *sigFilePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEpadPropXML )( 
            IePad * This,
            /* [retval][out] */ BSTR *ePadPropXML);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UpperX )( 
            IePad * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UpperX )( 
            IePad * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UpperY )( 
            IePad * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UpperY )( 
            IePad * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IePad * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            IePad * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IePad * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            IePad * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPenColor )( 
            IePad * This,
            /* [in] */ long red,
            /* [in] */ long green,
            /* [in] */ long blue);
        
        END_INTERFACE
    } IePadVtbl;

    interface IePad
    {
        CONST_VTBL struct IePadVtbl *lpVtbl;
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
    IePad * This,
    /* [in] */ BSTR bstrGuidStr,
    /* [retval][out] */ BSTR *sigFilePath);


void __RPC_STUB IePad_GetPhysicalSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IePad_GetEpadPropXML_Proxy( 
    IePad * This,
    /* [retval][out] */ BSTR *ePadPropXML);


void __RPC_STUB IePad_GetEpadPropXML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IePad_get_UpperX_Proxy( 
    IePad * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IePad_get_UpperX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IePad_put_UpperX_Proxy( 
    IePad * This,
    /* [in] */ long newVal);


void __RPC_STUB IePad_put_UpperX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IePad_get_UpperY_Proxy( 
    IePad * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IePad_get_UpperY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IePad_put_UpperY_Proxy( 
    IePad * This,
    /* [in] */ long newVal);


void __RPC_STUB IePad_put_UpperY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IePad_get_Width_Proxy( 
    IePad * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IePad_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IePad_put_Width_Proxy( 
    IePad * This,
    /* [in] */ long newVal);


void __RPC_STUB IePad_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IePad_get_Height_Proxy( 
    IePad * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IePad_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IePad_put_Height_Proxy( 
    IePad * This,
    /* [in] */ long newVal);


void __RPC_STUB IePad_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IePad_SetPenColor_Proxy( 
    IePad * This,
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

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


