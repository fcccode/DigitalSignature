

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sun Jun 05 10:30:15 2005
 */
/* Compiler settings for _NetscapeCert.idl:
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

#ifndef ___NetscapeCert_h__
#define ___NetscapeCert_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICertStore_FWD_DEFINED__
#define __ICertStore_FWD_DEFINED__
typedef interface ICertStore ICertStore;
#endif 	/* __ICertStore_FWD_DEFINED__ */


#ifndef __CCertStore_FWD_DEFINED__
#define __CCertStore_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertStore CCertStore;
#else
typedef struct CCertStore CCertStore;
#endif /* __cplusplus */

#endif 	/* __CCertStore_FWD_DEFINED__ */


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

#ifndef __ICertStore_INTERFACE_DEFINED__
#define __ICertStore_INTERFACE_DEFINED__

/* interface ICertStore */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICertStore;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0D61AA35-48D5-47F5-8249-F685F75250FD")
    ICertStore : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCertificateList( 
            /* [out] */ ULONG *certCount,
            /* [retval][out] */ BSTR *certArray) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NetscapeStorePassword( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportNetscapeCert( 
            /* [in] */ BSTR certSerialNumber,
            /* [retval][out] */ BSTR *pfxFilePath) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertStoreVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICertStore * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICertStore * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICertStore * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICertStore * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICertStore * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICertStore * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICertStore * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCertificateList )( 
            ICertStore * This,
            /* [out] */ ULONG *certCount,
            /* [retval][out] */ BSTR *certArray);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NetscapeStorePassword )( 
            ICertStore * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExportNetscapeCert )( 
            ICertStore * This,
            /* [in] */ BSTR certSerialNumber,
            /* [retval][out] */ BSTR *pfxFilePath);
        
        END_INTERFACE
    } ICertStoreVtbl;

    interface ICertStore
    {
        CONST_VTBL struct ICertStoreVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertStore_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertStore_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertStore_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertStore_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertStore_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertStore_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertStore_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertStore_GetCertificateList(This,certCount,certArray)	\
    (This)->lpVtbl -> GetCertificateList(This,certCount,certArray)

#define ICertStore_put_NetscapeStorePassword(This,newVal)	\
    (This)->lpVtbl -> put_NetscapeStorePassword(This,newVal)

#define ICertStore_ExportNetscapeCert(This,certSerialNumber,pfxFilePath)	\
    (This)->lpVtbl -> ExportNetscapeCert(This,certSerialNumber,pfxFilePath)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICertStore_GetCertificateList_Proxy( 
    ICertStore * This,
    /* [out] */ ULONG *certCount,
    /* [retval][out] */ BSTR *certArray);


void __RPC_STUB ICertStore_GetCertificateList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICertStore_put_NetscapeStorePassword_Proxy( 
    ICertStore * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ICertStore_put_NetscapeStorePassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICertStore_ExportNetscapeCert_Proxy( 
    ICertStore * This,
    /* [in] */ BSTR certSerialNumber,
    /* [retval][out] */ BSTR *pfxFilePath);


void __RPC_STUB ICertStore_ExportNetscapeCert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertStore_INTERFACE_DEFINED__ */



#ifndef __NetscapeCert_LIBRARY_DEFINED__
#define __NetscapeCert_LIBRARY_DEFINED__

/* library NetscapeCert */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_NetscapeCert;

EXTERN_C const CLSID CLSID_CCertStore;

#ifdef __cplusplus

class DECLSPEC_UUID("0A06154B-8FF9-48B2-A819-B68C327FC773")
CCertStore;
#endif
#endif /* __NetscapeCert_LIBRARY_DEFINED__ */

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


