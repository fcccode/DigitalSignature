

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Thu Aug 21 15:25:40 2003
 */
/* Compiler settings for _FormLicense.idl:
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

#ifndef ___FormLicense_h__
#define ___FormLicense_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IValidation_FWD_DEFINED__
#define __IValidation_FWD_DEFINED__
typedef interface IValidation IValidation;
#endif 	/* __IValidation_FWD_DEFINED__ */


#ifndef __CValidation_FWD_DEFINED__
#define __CValidation_FWD_DEFINED__

#ifdef __cplusplus
typedef class CValidation CValidation;
#else
typedef struct CValidation CValidation;
#endif /* __cplusplus */

#endif 	/* __CValidation_FWD_DEFINED__ */


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

#ifndef __IValidation_INTERFACE_DEFINED__
#define __IValidation_INTERFACE_DEFINED__

/* interface IValidation */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IValidation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9C2C7A7E-E901-43F4-91F5-869B20DC6A1A")
    IValidation : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ValidateXmlWithSchema( 
            /* [in] */ BSTR instanceXMLStr,
            /* [in] */ BSTR schemaXmlStr,
            /* [retval][out] */ ULONG *validationStatus) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ValidateFormLicense( 
            /* [in] */ BSTR formXmlStr,
            /* [retval][out] */ ULONG *validationStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IValidationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IValidation * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IValidation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IValidation * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IValidation * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IValidation * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IValidation * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IValidation * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ValidateXmlWithSchema )( 
            IValidation * This,
            /* [in] */ BSTR instanceXMLStr,
            /* [in] */ BSTR schemaXmlStr,
            /* [retval][out] */ ULONG *validationStatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ValidateFormLicense )( 
            IValidation * This,
            /* [in] */ BSTR formXmlStr,
            /* [retval][out] */ ULONG *validationStatus);
        
        END_INTERFACE
    } IValidationVtbl;

    interface IValidation
    {
        CONST_VTBL struct IValidationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IValidation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IValidation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IValidation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IValidation_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IValidation_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IValidation_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IValidation_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IValidation_ValidateXmlWithSchema(This,instanceXMLStr,schemaXmlStr,validationStatus)	\
    (This)->lpVtbl -> ValidateXmlWithSchema(This,instanceXMLStr,schemaXmlStr,validationStatus)

#define IValidation_ValidateFormLicense(This,formXmlStr,validationStatus)	\
    (This)->lpVtbl -> ValidateFormLicense(This,formXmlStr,validationStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IValidation_ValidateXmlWithSchema_Proxy( 
    IValidation * This,
    /* [in] */ BSTR instanceXMLStr,
    /* [in] */ BSTR schemaXmlStr,
    /* [retval][out] */ ULONG *validationStatus);


void __RPC_STUB IValidation_ValidateXmlWithSchema_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IValidation_ValidateFormLicense_Proxy( 
    IValidation * This,
    /* [in] */ BSTR formXmlStr,
    /* [retval][out] */ ULONG *validationStatus);


void __RPC_STUB IValidation_ValidateFormLicense_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IValidation_INTERFACE_DEFINED__ */



#ifndef __FormLicense_LIBRARY_DEFINED__
#define __FormLicense_LIBRARY_DEFINED__

/* library FormLicense */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_FormLicense;

EXTERN_C const CLSID CLSID_CValidation;

#ifdef __cplusplus

class DECLSPEC_UUID("667A9827-D2EF-42D5-A9A7-4B6209ECBD04")
CValidation;
#endif
#endif /* __FormLicense_LIBRARY_DEFINED__ */

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


