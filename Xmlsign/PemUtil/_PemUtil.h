

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sun Jun 05 00:40:13 2005
 */
/* Compiler settings for _PemUtil.idl:
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

#ifndef ___PemUtil_h__
#define ___PemUtil_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPemObject_FWD_DEFINED__
#define __IPemObject_FWD_DEFINED__
typedef interface IPemObject IPemObject;
#endif 	/* __IPemObject_FWD_DEFINED__ */


#ifndef __CPemObject_FWD_DEFINED__
#define __CPemObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPemObject CPemObject;
#else
typedef struct CPemObject CPemObject;
#endif /* __cplusplus */

#endif 	/* __CPemObject_FWD_DEFINED__ */


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

#ifndef __IPemObject_INTERFACE_DEFINED__
#define __IPemObject_INTERFACE_DEFINED__

/* interface IPemObject */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPemObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12F2BF07-DC45-4684-A4BC-8A5F44984777")
    IPemObject : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CovertToPFX( 
            /* [in] */ BSTR pemFileName,
            /* [in] */ BSTR pemPassword,
            /* [retval][out] */ BSTR *pfxFilePath) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPemObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPemObject * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPemObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPemObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPemObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPemObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPemObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPemObject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CovertToPFX )( 
            IPemObject * This,
            /* [in] */ BSTR pemFileName,
            /* [in] */ BSTR pemPassword,
            /* [retval][out] */ BSTR *pfxFilePath);
        
        END_INTERFACE
    } IPemObjectVtbl;

    interface IPemObject
    {
        CONST_VTBL struct IPemObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPemObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPemObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPemObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPemObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPemObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPemObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPemObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPemObject_CovertToPFX(This,pemFileName,pemPassword,pfxFilePath)	\
    (This)->lpVtbl -> CovertToPFX(This,pemFileName,pemPassword,pfxFilePath)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPemObject_CovertToPFX_Proxy( 
    IPemObject * This,
    /* [in] */ BSTR pemFileName,
    /* [in] */ BSTR pemPassword,
    /* [retval][out] */ BSTR *pfxFilePath);


void __RPC_STUB IPemObject_CovertToPFX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPemObject_INTERFACE_DEFINED__ */



#ifndef __PemUtil_LIBRARY_DEFINED__
#define __PemUtil_LIBRARY_DEFINED__

/* library PemUtil */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_PemUtil;

EXTERN_C const CLSID CLSID_CPemObject;

#ifdef __cplusplus

class DECLSPEC_UUID("D8F3211F-302F-45DB-8187-CDF6B7677D90")
CPemObject;
#endif
#endif /* __PemUtil_LIBRARY_DEFINED__ */

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


