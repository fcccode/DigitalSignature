

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sat Jun 21 19:31:49 2003
 */
/* Compiler settings for .\XMLSign.idl:
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

#ifndef __XMLSign_h__
#define __XMLSign_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISignature_FWD_DEFINED__
#define __ISignature_FWD_DEFINED__
typedef interface ISignature ISignature;
#endif 	/* __ISignature_FWD_DEFINED__ */


#ifndef __Signature_FWD_DEFINED__
#define __Signature_FWD_DEFINED__

#ifdef __cplusplus
typedef class Signature Signature;
#else
typedef struct Signature Signature;
#endif /* __cplusplus */

#endif 	/* __Signature_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ISignature_INTERFACE_DEFINED__
#define __ISignature_INTERFACE_DEFINED__

/* interface ISignature */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISignature;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62EC64DC-B26D-46CE-9E33-24289BCF5F63")
    ISignature : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EnvelopingFlag( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnvelopingFlag( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ZeroSpaceFlag( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ZeroSpaceFlag( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignerCertificate( 
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SignerCertificate( 
            /* [in] */ long index,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignatureID( 
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SignatureID( 
            /* [in] */ long index,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Properties( 
            /* [in] */ long sigIndex,
            /* [in] */ long propIndex,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Properties( 
            /* [in] */ long sigIndex,
            /* [in] */ long propIndex,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignatureAlgorithm( 
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DigestAlgorithm( 
            /* [in] */ long sigIndex,
            /* [in] */ long uriIndex,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DocumentURI( 
            /* [in] */ long sigIndex,
            /* [in] */ long uriIndex,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DigestObjectStatus( 
            /* [in] */ long sigIndex,
            /* [in] */ long uriIndex,
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CaptureOnce( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CaptureOnce( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignatureStatus( 
            /* [in] */ long sigIndex,
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PhysicalSignatureUsage( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PhysicalSignatureUsage( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PhysicalSignatureFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PhysicalSignatureFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CapturedSignatureFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sign( 
            /* [in] */ BSTR URI,
            /* [retval][out] */ BSTR *tempFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetXMLSignature( 
            /* [retval][out] */ BSTR *xmlSignature) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveXMLSignature( 
            /* [in] */ BSTR sigFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Verify( 
            /* [in] */ BSTR signatureFileName,
            /* [retval][out] */ BOOL *sigStatus) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetError( 
            /* [retval][out] */ BSTR *errorString) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OverwriteFile( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PFXExportCertificate( 
            /* [in] */ BSTR certID,
            /* [in] */ BSTR password,
            /* [retval][out] */ BSTR *pfxFilePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyDetached( 
            /* [in] */ BSTR signatureFileName,
            /* [retval][out] */ BOOL *sigStatus) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLastError( 
            /* [retval][out] */ long *errorNum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetX509Certificate( 
            /* [in] */ BSTR certID,
            /* [retval][out] */ BSTR *certData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ViewCertificate( 
            /* [in] */ BSTR certID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertificateCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCertificateInfo( 
            /* [in] */ long index,
            /* [in] */ long valIndex,
            /* [retval][out] */ BSTR *value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetActiveCertificate( 
            /* [in] */ BSTR certID,
            /* [retval][out] */ BOOL *status) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignedDocumentPath( 
            /* [in] */ long sigIndex,
            /* [in] */ long uriIndex,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignerSubject( 
            /* [in] */ BSTR sigId,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertIssuer( 
            /* [in] */ BSTR sigId,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertExpiry( 
            /* [in] */ BSTR sigId,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertSerialNumber( 
            /* [in] */ BSTR sigId,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FileExists( 
            /* [in] */ BSTR fileName,
            /* [retval][out] */ BOOL *fileStatus) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FailedUriCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TotalUriCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FailedUriFullPath( 
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FailedUriFullPath( 
            /* [in] */ long index,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FailedUri( 
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignatureCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignXMLStr( 
            /* [in] */ BSTR xmlStr,
            /* [in] */ BSTR signatureId,
            /* [retval][out] */ BSTR *signedXMLStr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadAll( 
            /* [in] */ BSTR fileName,
            /* [retval][out] */ BSTR *fileDataStr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveXMLStr( 
            /* [in] */ BSTR inputXMLStr,
            /* [in] */ BSTR fileName,
            /* [retval][out] */ BSTR *path) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignHTML( 
            /* [in] */ IDispatch *document,
            /* [retval][out] */ BSTR *signedHTML) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SecureXMLVerify( 
            /* [in] */ BSTR signedXML,
            /* [retval][out] */ BSTR *verificationResponse) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCSP( 
            /* [in] */ BSTR CSPName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSignedHTML( 
            /* [in] */ BSTR signedHtmlXML,
            /* [retval][out] */ BSTR *originalHTML) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignFile( 
            /* [in] */ BSTR inputFile,
            /* [in] */ BSTR outputFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSignedFileObject( 
            /* [in] */ BSTR signedXML,
            /* [in] */ BSTR saveDir,
            /* [retval][out] */ BSTR *signedFilePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStoreName( 
            /* [in] */ BSTR storeName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStoreName( 
            /* [retval][out] */ BSTR *storeName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignXMLEnveloped( 
            /* [in] */ BSTR inputXML,
            /* [in] */ BSTR sigId,
            /* [retval][out] */ BSTR *signedXML) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVersion( 
            /* [retval][out] */ BSTR *version) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLicenseStatus( 
            /* [retval][out] */ long *licStatus) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPropertyCount( 
            /* [in] */ long sigIndex,
            /* [retval][out] */ long *propCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ViewAnyCertificate( 
            /* [in] */ BSTR inputX509Data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectActiveCertificate( 
            /* [retval][out] */ BSTR *certID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyXMLStr( 
            /* [in] */ BSTR signedXML,
            /* [retval][out] */ BOOL *sigStatus) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetActivePFXFileCert( 
            /* [in] */ BSTR pfxFileName,
            /* [in] */ BSTR pfxPassword,
            /* [retval][out] */ BSTR *x509Cert) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PFXExportActiveCertificate( 
            /* [in] */ BSTR password,
            /* [retval][out] */ BSTR *pfxFilePath) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HostName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeStampURL( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TimeStampURL( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeStamping( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TimeStamping( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HostOsType( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CrlChecking( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CrlChecking( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SigCertStatus( 
            /* [in] */ long sigIndex,
            /* [in] */ BSTR atTime,
            /* [in] */ long timeFormat,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyX509CertCRL( 
            /* [in] */ BSTR certData,
            /* [in] */ BSTR atTime,
            /* [in] */ long timeFormat,
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyPFXCertCRL( 
            /* [in] */ BSTR pfxFileName,
            /* [in] */ BSTR pfxPassword,
            /* [in] */ BSTR atTime,
            /* [in] */ long timeFormat,
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AddWindowImage( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AddWindowImage( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EmailSupport( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EmailSupport( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EmailFrom( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EmailFrom( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EmailTo( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EmailTo( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EmailCc( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EmailCc( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EmailBcc( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EmailBcc( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EmailUserName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EmailUserName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EmailUserPassword( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EmailUserPassword( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultEmailRecipient( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultEmailRecipient( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SendAutomaticEmail( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SendAutomaticEmail( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EmailServerType( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EmailServerType( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExchangeServer( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExchangeServer( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SmtpServer( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SmtpServer( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignXMLXpathStr( 
            /* [in] */ BSTR xmlStr,
            /* [in] */ BSTR xpathExp,
            /* [in] */ BSTR signatureId,
            /* [retval][out] */ BSTR *signedXMLStr) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UseHMAC( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseHMAC( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HMACPassword( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HMACPassword( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeOrAddProperty( 
            /* [in] */ BSTR propertyName,
            /* [in] */ BSTR propertyValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DetailedVerificationFlag( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CaptureLiveSignature( 
            /* [retval][out] */ BSTR *signatureFilePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignDataStr( 
            /* [in] */ BSTR dataStrPtr,
            /* [retval][out] */ BSTR *signedXMLStr) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ExcludeSignerCertificate( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CoSignDataXMLStr( 
            /* [in] */ BSTR signedDataXMLStr,
            /* [retval][out] */ BSTR *coSignedXMLStr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CoSignFileXMLStr( 
            /* [in] */ BSTR signedDataXMLStr,
            /* [retval][out] */ BSTR *coSignedXMLStr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISignatureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISignature * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISignature * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISignature * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISignature * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISignature * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISignature * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISignature * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnvelopingFlag )( 
            ISignature * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EnvelopingFlag )( 
            ISignature * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZeroSpaceFlag )( 
            ISignature * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ZeroSpaceFlag )( 
            ISignature * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SignerCertificate )( 
            ISignature * This,
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SignerCertificate )( 
            ISignature * This,
            /* [in] */ long index,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureID )( 
            ISignature * This,
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SignatureID )( 
            ISignature * This,
            /* [in] */ long index,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Properties )( 
            ISignature * This,
            /* [in] */ long sigIndex,
            /* [in] */ long propIndex,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Properties )( 
            ISignature * This,
            /* [in] */ long sigIndex,
            /* [in] */ long propIndex,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureAlgorithm )( 
            ISignature * This,
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DigestAlgorithm )( 
            ISignature * This,
            /* [in] */ long sigIndex,
            /* [in] */ long uriIndex,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DocumentURI )( 
            ISignature * This,
            /* [in] */ long sigIndex,
            /* [in] */ long uriIndex,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DigestObjectStatus )( 
            ISignature * This,
            /* [in] */ long sigIndex,
            /* [in] */ long uriIndex,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CaptureOnce )( 
            ISignature * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CaptureOnce )( 
            ISignature * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureStatus )( 
            ISignature * This,
            /* [in] */ long sigIndex,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PhysicalSignatureUsage )( 
            ISignature * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PhysicalSignatureUsage )( 
            ISignature * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PhysicalSignatureFile )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PhysicalSignatureFile )( 
            ISignature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CapturedSignatureFile )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Sign )( 
            ISignature * This,
            /* [in] */ BSTR URI,
            /* [retval][out] */ BSTR *tempFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetXMLSignature )( 
            ISignature * This,
            /* [retval][out] */ BSTR *xmlSignature);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveXMLSignature )( 
            ISignature * This,
            /* [in] */ BSTR sigFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Verify )( 
            ISignature * This,
            /* [in] */ BSTR signatureFileName,
            /* [retval][out] */ BOOL *sigStatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetError )( 
            ISignature * This,
            /* [retval][out] */ BSTR *errorString);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OverwriteFile )( 
            ISignature * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PFXExportCertificate )( 
            ISignature * This,
            /* [in] */ BSTR certID,
            /* [in] */ BSTR password,
            /* [retval][out] */ BSTR *pfxFilePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyDetached )( 
            ISignature * This,
            /* [in] */ BSTR signatureFileName,
            /* [retval][out] */ BOOL *sigStatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLastError )( 
            ISignature * This,
            /* [retval][out] */ long *errorNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetX509Certificate )( 
            ISignature * This,
            /* [in] */ BSTR certID,
            /* [retval][out] */ BSTR *certData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ViewCertificate )( 
            ISignature * This,
            /* [in] */ BSTR certID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CertificateCount )( 
            ISignature * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCertificateInfo )( 
            ISignature * This,
            /* [in] */ long index,
            /* [in] */ long valIndex,
            /* [retval][out] */ BSTR *value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetActiveCertificate )( 
            ISignature * This,
            /* [in] */ BSTR certID,
            /* [retval][out] */ BOOL *status);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SignedDocumentPath )( 
            ISignature * This,
            /* [in] */ long sigIndex,
            /* [in] */ long uriIndex,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SignerSubject )( 
            ISignature * This,
            /* [in] */ BSTR sigId,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CertIssuer )( 
            ISignature * This,
            /* [in] */ BSTR sigId,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CertExpiry )( 
            ISignature * This,
            /* [in] */ BSTR sigId,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CertSerialNumber )( 
            ISignature * This,
            /* [in] */ BSTR sigId,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FileExists )( 
            ISignature * This,
            /* [in] */ BSTR fileName,
            /* [retval][out] */ BOOL *fileStatus);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FailedUriCount )( 
            ISignature * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TotalUriCount )( 
            ISignature * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FailedUriFullPath )( 
            ISignature * This,
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FailedUriFullPath )( 
            ISignature * This,
            /* [in] */ long index,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FailedUri )( 
            ISignature * This,
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureCount )( 
            ISignature * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignXMLStr )( 
            ISignature * This,
            /* [in] */ BSTR xmlStr,
            /* [in] */ BSTR signatureId,
            /* [retval][out] */ BSTR *signedXMLStr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadAll )( 
            ISignature * This,
            /* [in] */ BSTR fileName,
            /* [retval][out] */ BSTR *fileDataStr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveXMLStr )( 
            ISignature * This,
            /* [in] */ BSTR inputXMLStr,
            /* [in] */ BSTR fileName,
            /* [retval][out] */ BSTR *path);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignHTML )( 
            ISignature * This,
            /* [in] */ IDispatch *document,
            /* [retval][out] */ BSTR *signedHTML);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SecureXMLVerify )( 
            ISignature * This,
            /* [in] */ BSTR signedXML,
            /* [retval][out] */ BSTR *verificationResponse);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCSP )( 
            ISignature * This,
            /* [in] */ BSTR CSPName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSignedHTML )( 
            ISignature * This,
            /* [in] */ BSTR signedHtmlXML,
            /* [retval][out] */ BSTR *originalHTML);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignFile )( 
            ISignature * This,
            /* [in] */ BSTR inputFile,
            /* [in] */ BSTR outputFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSignedFileObject )( 
            ISignature * This,
            /* [in] */ BSTR signedXML,
            /* [in] */ BSTR saveDir,
            /* [retval][out] */ BSTR *signedFilePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetStoreName )( 
            ISignature * This,
            /* [in] */ BSTR storeName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetStoreName )( 
            ISignature * This,
            /* [retval][out] */ BSTR *storeName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignXMLEnveloped )( 
            ISignature * This,
            /* [in] */ BSTR inputXML,
            /* [in] */ BSTR sigId,
            /* [retval][out] */ BSTR *signedXML);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVersion )( 
            ISignature * This,
            /* [retval][out] */ BSTR *version);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLicenseStatus )( 
            ISignature * This,
            /* [retval][out] */ long *licStatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPropertyCount )( 
            ISignature * This,
            /* [in] */ long sigIndex,
            /* [retval][out] */ long *propCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ViewAnyCertificate )( 
            ISignature * This,
            /* [in] */ BSTR inputX509Data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectActiveCertificate )( 
            ISignature * This,
            /* [retval][out] */ BSTR *certID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyXMLStr )( 
            ISignature * This,
            /* [in] */ BSTR signedXML,
            /* [retval][out] */ BOOL *sigStatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetActivePFXFileCert )( 
            ISignature * This,
            /* [in] */ BSTR pfxFileName,
            /* [in] */ BSTR pfxPassword,
            /* [retval][out] */ BSTR *x509Cert);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PFXExportActiveCertificate )( 
            ISignature * This,
            /* [in] */ BSTR password,
            /* [retval][out] */ BSTR *pfxFilePath);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HostName )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimeStampURL )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TimeStampURL )( 
            ISignature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimeStamping )( 
            ISignature * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TimeStamping )( 
            ISignature * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HostOsType )( 
            ISignature * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CrlChecking )( 
            ISignature * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CrlChecking )( 
            ISignature * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SigCertStatus )( 
            ISignature * This,
            /* [in] */ long sigIndex,
            /* [in] */ BSTR atTime,
            /* [in] */ long timeFormat,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyX509CertCRL )( 
            ISignature * This,
            /* [in] */ BSTR certData,
            /* [in] */ BSTR atTime,
            /* [in] */ long timeFormat,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyPFXCertCRL )( 
            ISignature * This,
            /* [in] */ BSTR pfxFileName,
            /* [in] */ BSTR pfxPassword,
            /* [in] */ BSTR atTime,
            /* [in] */ long timeFormat,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AddWindowImage )( 
            ISignature * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AddWindowImage )( 
            ISignature * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmailSupport )( 
            ISignature * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EmailSupport )( 
            ISignature * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmailFrom )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EmailFrom )( 
            ISignature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmailTo )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EmailTo )( 
            ISignature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmailCc )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EmailCc )( 
            ISignature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmailBcc )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EmailBcc )( 
            ISignature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmailUserName )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EmailUserName )( 
            ISignature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmailUserPassword )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EmailUserPassword )( 
            ISignature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultEmailRecipient )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultEmailRecipient )( 
            ISignature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SendAutomaticEmail )( 
            ISignature * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SendAutomaticEmail )( 
            ISignature * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmailServerType )( 
            ISignature * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EmailServerType )( 
            ISignature * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExchangeServer )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExchangeServer )( 
            ISignature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SmtpServer )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SmtpServer )( 
            ISignature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignXMLXpathStr )( 
            ISignature * This,
            /* [in] */ BSTR xmlStr,
            /* [in] */ BSTR xpathExp,
            /* [in] */ BSTR signatureId,
            /* [retval][out] */ BSTR *signedXMLStr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseHMAC )( 
            ISignature * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseHMAC )( 
            ISignature * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HMACPassword )( 
            ISignature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HMACPassword )( 
            ISignature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangeOrAddProperty )( 
            ISignature * This,
            /* [in] */ BSTR propertyName,
            /* [in] */ BSTR propertyValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DetailedVerificationFlag )( 
            ISignature * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CaptureLiveSignature )( 
            ISignature * This,
            /* [retval][out] */ BSTR *signatureFilePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignDataStr )( 
            ISignature * This,
            /* [in] */ BSTR dataStrPtr,
            /* [retval][out] */ BSTR *signedXMLStr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExcludeSignerCertificate )( 
            ISignature * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CoSignDataXMLStr )( 
            ISignature * This,
            /* [in] */ BSTR signedDataXMLStr,
            /* [retval][out] */ BSTR *coSignedXMLStr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CoSignFileXMLStr )( 
            ISignature * This,
            /* [in] */ BSTR signedDataXMLStr,
            /* [retval][out] */ BSTR *coSignedXMLStr);
        
        END_INTERFACE
    } ISignatureVtbl;

    interface ISignature
    {
        CONST_VTBL struct ISignatureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISignature_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISignature_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISignature_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISignature_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISignature_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISignature_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISignature_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISignature_get_EnvelopingFlag(This,pVal)	\
    (This)->lpVtbl -> get_EnvelopingFlag(This,pVal)

#define ISignature_put_EnvelopingFlag(This,newVal)	\
    (This)->lpVtbl -> put_EnvelopingFlag(This,newVal)

#define ISignature_get_ZeroSpaceFlag(This,pVal)	\
    (This)->lpVtbl -> get_ZeroSpaceFlag(This,pVal)

#define ISignature_put_ZeroSpaceFlag(This,newVal)	\
    (This)->lpVtbl -> put_ZeroSpaceFlag(This,newVal)

#define ISignature_get_SignerCertificate(This,index,pVal)	\
    (This)->lpVtbl -> get_SignerCertificate(This,index,pVal)

#define ISignature_put_SignerCertificate(This,index,newVal)	\
    (This)->lpVtbl -> put_SignerCertificate(This,index,newVal)

#define ISignature_get_SignatureID(This,index,pVal)	\
    (This)->lpVtbl -> get_SignatureID(This,index,pVal)

#define ISignature_put_SignatureID(This,index,newVal)	\
    (This)->lpVtbl -> put_SignatureID(This,index,newVal)

#define ISignature_get_Properties(This,sigIndex,propIndex,pVal)	\
    (This)->lpVtbl -> get_Properties(This,sigIndex,propIndex,pVal)

#define ISignature_put_Properties(This,sigIndex,propIndex,newVal)	\
    (This)->lpVtbl -> put_Properties(This,sigIndex,propIndex,newVal)

#define ISignature_get_SignatureAlgorithm(This,index,pVal)	\
    (This)->lpVtbl -> get_SignatureAlgorithm(This,index,pVal)

#define ISignature_get_DigestAlgorithm(This,sigIndex,uriIndex,pVal)	\
    (This)->lpVtbl -> get_DigestAlgorithm(This,sigIndex,uriIndex,pVal)

#define ISignature_get_DocumentURI(This,sigIndex,uriIndex,pVal)	\
    (This)->lpVtbl -> get_DocumentURI(This,sigIndex,uriIndex,pVal)

#define ISignature_get_DigestObjectStatus(This,sigIndex,uriIndex,pVal)	\
    (This)->lpVtbl -> get_DigestObjectStatus(This,sigIndex,uriIndex,pVal)

#define ISignature_get_CaptureOnce(This,pVal)	\
    (This)->lpVtbl -> get_CaptureOnce(This,pVal)

#define ISignature_put_CaptureOnce(This,newVal)	\
    (This)->lpVtbl -> put_CaptureOnce(This,newVal)

#define ISignature_get_SignatureStatus(This,sigIndex,pVal)	\
    (This)->lpVtbl -> get_SignatureStatus(This,sigIndex,pVal)

#define ISignature_get_PhysicalSignatureUsage(This,pVal)	\
    (This)->lpVtbl -> get_PhysicalSignatureUsage(This,pVal)

#define ISignature_put_PhysicalSignatureUsage(This,newVal)	\
    (This)->lpVtbl -> put_PhysicalSignatureUsage(This,newVal)

#define ISignature_get_PhysicalSignatureFile(This,pVal)	\
    (This)->lpVtbl -> get_PhysicalSignatureFile(This,pVal)

#define ISignature_put_PhysicalSignatureFile(This,newVal)	\
    (This)->lpVtbl -> put_PhysicalSignatureFile(This,newVal)

#define ISignature_get_CapturedSignatureFile(This,pVal)	\
    (This)->lpVtbl -> get_CapturedSignatureFile(This,pVal)

#define ISignature_Sign(This,URI,tempFileName)	\
    (This)->lpVtbl -> Sign(This,URI,tempFileName)

#define ISignature_GetXMLSignature(This,xmlSignature)	\
    (This)->lpVtbl -> GetXMLSignature(This,xmlSignature)

#define ISignature_SaveXMLSignature(This,sigFileName)	\
    (This)->lpVtbl -> SaveXMLSignature(This,sigFileName)

#define ISignature_Verify(This,signatureFileName,sigStatus)	\
    (This)->lpVtbl -> Verify(This,signatureFileName,sigStatus)

#define ISignature_GetError(This,errorString)	\
    (This)->lpVtbl -> GetError(This,errorString)

#define ISignature_put_OverwriteFile(This,newVal)	\
    (This)->lpVtbl -> put_OverwriteFile(This,newVal)

#define ISignature_PFXExportCertificate(This,certID,password,pfxFilePath)	\
    (This)->lpVtbl -> PFXExportCertificate(This,certID,password,pfxFilePath)

#define ISignature_VerifyDetached(This,signatureFileName,sigStatus)	\
    (This)->lpVtbl -> VerifyDetached(This,signatureFileName,sigStatus)

#define ISignature_GetLastError(This,errorNum)	\
    (This)->lpVtbl -> GetLastError(This,errorNum)

#define ISignature_GetX509Certificate(This,certID,certData)	\
    (This)->lpVtbl -> GetX509Certificate(This,certID,certData)

#define ISignature_ViewCertificate(This,certID)	\
    (This)->lpVtbl -> ViewCertificate(This,certID)

#define ISignature_get_CertificateCount(This,pVal)	\
    (This)->lpVtbl -> get_CertificateCount(This,pVal)

#define ISignature_GetCertificateInfo(This,index,valIndex,value)	\
    (This)->lpVtbl -> GetCertificateInfo(This,index,valIndex,value)

#define ISignature_SetActiveCertificate(This,certID,status)	\
    (This)->lpVtbl -> SetActiveCertificate(This,certID,status)

#define ISignature_get_SignedDocumentPath(This,sigIndex,uriIndex,pVal)	\
    (This)->lpVtbl -> get_SignedDocumentPath(This,sigIndex,uriIndex,pVal)

#define ISignature_get_SignerSubject(This,sigId,pVal)	\
    (This)->lpVtbl -> get_SignerSubject(This,sigId,pVal)

#define ISignature_get_CertIssuer(This,sigId,pVal)	\
    (This)->lpVtbl -> get_CertIssuer(This,sigId,pVal)

#define ISignature_get_CertExpiry(This,sigId,pVal)	\
    (This)->lpVtbl -> get_CertExpiry(This,sigId,pVal)

#define ISignature_get_CertSerialNumber(This,sigId,pVal)	\
    (This)->lpVtbl -> get_CertSerialNumber(This,sigId,pVal)

#define ISignature_FileExists(This,fileName,fileStatus)	\
    (This)->lpVtbl -> FileExists(This,fileName,fileStatus)

#define ISignature_get_FailedUriCount(This,pVal)	\
    (This)->lpVtbl -> get_FailedUriCount(This,pVal)

#define ISignature_get_TotalUriCount(This,pVal)	\
    (This)->lpVtbl -> get_TotalUriCount(This,pVal)

#define ISignature_get_FailedUriFullPath(This,index,pVal)	\
    (This)->lpVtbl -> get_FailedUriFullPath(This,index,pVal)

#define ISignature_put_FailedUriFullPath(This,index,newVal)	\
    (This)->lpVtbl -> put_FailedUriFullPath(This,index,newVal)

#define ISignature_get_FailedUri(This,index,pVal)	\
    (This)->lpVtbl -> get_FailedUri(This,index,pVal)

#define ISignature_get_SignatureCount(This,pVal)	\
    (This)->lpVtbl -> get_SignatureCount(This,pVal)

#define ISignature_SignXMLStr(This,xmlStr,signatureId,signedXMLStr)	\
    (This)->lpVtbl -> SignXMLStr(This,xmlStr,signatureId,signedXMLStr)

#define ISignature_ReadAll(This,fileName,fileDataStr)	\
    (This)->lpVtbl -> ReadAll(This,fileName,fileDataStr)

#define ISignature_SaveXMLStr(This,inputXMLStr,fileName,path)	\
    (This)->lpVtbl -> SaveXMLStr(This,inputXMLStr,fileName,path)

#define ISignature_SignHTML(This,document,signedHTML)	\
    (This)->lpVtbl -> SignHTML(This,document,signedHTML)

#define ISignature_SecureXMLVerify(This,signedXML,verificationResponse)	\
    (This)->lpVtbl -> SecureXMLVerify(This,signedXML,verificationResponse)

#define ISignature_SetCSP(This,CSPName)	\
    (This)->lpVtbl -> SetCSP(This,CSPName)

#define ISignature_GetSignedHTML(This,signedHtmlXML,originalHTML)	\
    (This)->lpVtbl -> GetSignedHTML(This,signedHtmlXML,originalHTML)

#define ISignature_SignFile(This,inputFile,outputFile)	\
    (This)->lpVtbl -> SignFile(This,inputFile,outputFile)

#define ISignature_GetSignedFileObject(This,signedXML,saveDir,signedFilePath)	\
    (This)->lpVtbl -> GetSignedFileObject(This,signedXML,saveDir,signedFilePath)

#define ISignature_SetStoreName(This,storeName)	\
    (This)->lpVtbl -> SetStoreName(This,storeName)

#define ISignature_GetStoreName(This,storeName)	\
    (This)->lpVtbl -> GetStoreName(This,storeName)

#define ISignature_SignXMLEnveloped(This,inputXML,sigId,signedXML)	\
    (This)->lpVtbl -> SignXMLEnveloped(This,inputXML,sigId,signedXML)

#define ISignature_GetVersion(This,version)	\
    (This)->lpVtbl -> GetVersion(This,version)

#define ISignature_GetLicenseStatus(This,licStatus)	\
    (This)->lpVtbl -> GetLicenseStatus(This,licStatus)

#define ISignature_GetPropertyCount(This,sigIndex,propCount)	\
    (This)->lpVtbl -> GetPropertyCount(This,sigIndex,propCount)

#define ISignature_ViewAnyCertificate(This,inputX509Data)	\
    (This)->lpVtbl -> ViewAnyCertificate(This,inputX509Data)

#define ISignature_SelectActiveCertificate(This,certID)	\
    (This)->lpVtbl -> SelectActiveCertificate(This,certID)

#define ISignature_VerifyXMLStr(This,signedXML,sigStatus)	\
    (This)->lpVtbl -> VerifyXMLStr(This,signedXML,sigStatus)

#define ISignature_SetActivePFXFileCert(This,pfxFileName,pfxPassword,x509Cert)	\
    (This)->lpVtbl -> SetActivePFXFileCert(This,pfxFileName,pfxPassword,x509Cert)

#define ISignature_PFXExportActiveCertificate(This,password,pfxFilePath)	\
    (This)->lpVtbl -> PFXExportActiveCertificate(This,password,pfxFilePath)

#define ISignature_get_HostName(This,pVal)	\
    (This)->lpVtbl -> get_HostName(This,pVal)

#define ISignature_get_TimeStampURL(This,pVal)	\
    (This)->lpVtbl -> get_TimeStampURL(This,pVal)

#define ISignature_put_TimeStampURL(This,newVal)	\
    (This)->lpVtbl -> put_TimeStampURL(This,newVal)

#define ISignature_get_TimeStamping(This,pVal)	\
    (This)->lpVtbl -> get_TimeStamping(This,pVal)

#define ISignature_put_TimeStamping(This,newVal)	\
    (This)->lpVtbl -> put_TimeStamping(This,newVal)

#define ISignature_get_HostOsType(This,pVal)	\
    (This)->lpVtbl -> get_HostOsType(This,pVal)

#define ISignature_get_CrlChecking(This,pVal)	\
    (This)->lpVtbl -> get_CrlChecking(This,pVal)

#define ISignature_put_CrlChecking(This,newVal)	\
    (This)->lpVtbl -> put_CrlChecking(This,newVal)

#define ISignature_get_SigCertStatus(This,sigIndex,atTime,timeFormat,pVal)	\
    (This)->lpVtbl -> get_SigCertStatus(This,sigIndex,atTime,timeFormat,pVal)

#define ISignature_VerifyX509CertCRL(This,certData,atTime,timeFormat,pVal)	\
    (This)->lpVtbl -> VerifyX509CertCRL(This,certData,atTime,timeFormat,pVal)

#define ISignature_VerifyPFXCertCRL(This,pfxFileName,pfxPassword,atTime,timeFormat,pVal)	\
    (This)->lpVtbl -> VerifyPFXCertCRL(This,pfxFileName,pfxPassword,atTime,timeFormat,pVal)

#define ISignature_get_AddWindowImage(This,pVal)	\
    (This)->lpVtbl -> get_AddWindowImage(This,pVal)

#define ISignature_put_AddWindowImage(This,newVal)	\
    (This)->lpVtbl -> put_AddWindowImage(This,newVal)

#define ISignature_get_EmailSupport(This,pVal)	\
    (This)->lpVtbl -> get_EmailSupport(This,pVal)

#define ISignature_put_EmailSupport(This,newVal)	\
    (This)->lpVtbl -> put_EmailSupport(This,newVal)

#define ISignature_get_EmailFrom(This,pVal)	\
    (This)->lpVtbl -> get_EmailFrom(This,pVal)

#define ISignature_put_EmailFrom(This,newVal)	\
    (This)->lpVtbl -> put_EmailFrom(This,newVal)

#define ISignature_get_EmailTo(This,pVal)	\
    (This)->lpVtbl -> get_EmailTo(This,pVal)

#define ISignature_put_EmailTo(This,newVal)	\
    (This)->lpVtbl -> put_EmailTo(This,newVal)

#define ISignature_get_EmailCc(This,pVal)	\
    (This)->lpVtbl -> get_EmailCc(This,pVal)

#define ISignature_put_EmailCc(This,newVal)	\
    (This)->lpVtbl -> put_EmailCc(This,newVal)

#define ISignature_get_EmailBcc(This,pVal)	\
    (This)->lpVtbl -> get_EmailBcc(This,pVal)

#define ISignature_put_EmailBcc(This,newVal)	\
    (This)->lpVtbl -> put_EmailBcc(This,newVal)

#define ISignature_get_EmailUserName(This,pVal)	\
    (This)->lpVtbl -> get_EmailUserName(This,pVal)

#define ISignature_put_EmailUserName(This,newVal)	\
    (This)->lpVtbl -> put_EmailUserName(This,newVal)

#define ISignature_get_EmailUserPassword(This,pVal)	\
    (This)->lpVtbl -> get_EmailUserPassword(This,pVal)

#define ISignature_put_EmailUserPassword(This,newVal)	\
    (This)->lpVtbl -> put_EmailUserPassword(This,newVal)

#define ISignature_get_DefaultEmailRecipient(This,pVal)	\
    (This)->lpVtbl -> get_DefaultEmailRecipient(This,pVal)

#define ISignature_put_DefaultEmailRecipient(This,newVal)	\
    (This)->lpVtbl -> put_DefaultEmailRecipient(This,newVal)

#define ISignature_get_SendAutomaticEmail(This,pVal)	\
    (This)->lpVtbl -> get_SendAutomaticEmail(This,pVal)

#define ISignature_put_SendAutomaticEmail(This,newVal)	\
    (This)->lpVtbl -> put_SendAutomaticEmail(This,newVal)

#define ISignature_get_EmailServerType(This,pVal)	\
    (This)->lpVtbl -> get_EmailServerType(This,pVal)

#define ISignature_put_EmailServerType(This,newVal)	\
    (This)->lpVtbl -> put_EmailServerType(This,newVal)

#define ISignature_get_ExchangeServer(This,pVal)	\
    (This)->lpVtbl -> get_ExchangeServer(This,pVal)

#define ISignature_put_ExchangeServer(This,newVal)	\
    (This)->lpVtbl -> put_ExchangeServer(This,newVal)

#define ISignature_get_SmtpServer(This,pVal)	\
    (This)->lpVtbl -> get_SmtpServer(This,pVal)

#define ISignature_put_SmtpServer(This,newVal)	\
    (This)->lpVtbl -> put_SmtpServer(This,newVal)

#define ISignature_SignXMLXpathStr(This,xmlStr,xpathExp,signatureId,signedXMLStr)	\
    (This)->lpVtbl -> SignXMLXpathStr(This,xmlStr,xpathExp,signatureId,signedXMLStr)

#define ISignature_get_UseHMAC(This,pVal)	\
    (This)->lpVtbl -> get_UseHMAC(This,pVal)

#define ISignature_put_UseHMAC(This,newVal)	\
    (This)->lpVtbl -> put_UseHMAC(This,newVal)

#define ISignature_get_HMACPassword(This,pVal)	\
    (This)->lpVtbl -> get_HMACPassword(This,pVal)

#define ISignature_put_HMACPassword(This,newVal)	\
    (This)->lpVtbl -> put_HMACPassword(This,newVal)

#define ISignature_ChangeOrAddProperty(This,propertyName,propertyValue)	\
    (This)->lpVtbl -> ChangeOrAddProperty(This,propertyName,propertyValue)

#define ISignature_put_DetailedVerificationFlag(This,newVal)	\
    (This)->lpVtbl -> put_DetailedVerificationFlag(This,newVal)

#define ISignature_CaptureLiveSignature(This,signatureFilePath)	\
    (This)->lpVtbl -> CaptureLiveSignature(This,signatureFilePath)

#define ISignature_SignDataStr(This,dataStrPtr,signedXMLStr)	\
    (This)->lpVtbl -> SignDataStr(This,dataStrPtr,signedXMLStr)

#define ISignature_put_ExcludeSignerCertificate(This,newVal)	\
    (This)->lpVtbl -> put_ExcludeSignerCertificate(This,newVal)

#define ISignature_CoSignDataXMLStr(This,signedDataXMLStr,coSignedXMLStr)	\
    (This)->lpVtbl -> CoSignDataXMLStr(This,signedDataXMLStr,coSignedXMLStr)

#define ISignature_CoSignFileXMLStr(This,signedDataXMLStr,coSignedXMLStr)	\
    (This)->lpVtbl -> CoSignFileXMLStr(This,signedDataXMLStr,coSignedXMLStr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_EnvelopingFlag_Proxy( 
    ISignature * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB ISignature_get_EnvelopingFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_EnvelopingFlag_Proxy( 
    ISignature * This,
    /* [in] */ short newVal);


void __RPC_STUB ISignature_put_EnvelopingFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_ZeroSpaceFlag_Proxy( 
    ISignature * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB ISignature_get_ZeroSpaceFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_ZeroSpaceFlag_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB ISignature_put_ZeroSpaceFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_SignerCertificate_Proxy( 
    ISignature * This,
    /* [in] */ long index,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_SignerCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_SignerCertificate_Proxy( 
    ISignature * This,
    /* [in] */ long index,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_SignerCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_SignatureID_Proxy( 
    ISignature * This,
    /* [in] */ long index,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_SignatureID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_SignatureID_Proxy( 
    ISignature * This,
    /* [in] */ long index,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_SignatureID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_Properties_Proxy( 
    ISignature * This,
    /* [in] */ long sigIndex,
    /* [in] */ long propIndex,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_Properties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_Properties_Proxy( 
    ISignature * This,
    /* [in] */ long sigIndex,
    /* [in] */ long propIndex,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_Properties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_SignatureAlgorithm_Proxy( 
    ISignature * This,
    /* [in] */ long index,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_SignatureAlgorithm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_DigestAlgorithm_Proxy( 
    ISignature * This,
    /* [in] */ long sigIndex,
    /* [in] */ long uriIndex,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_DigestAlgorithm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_DocumentURI_Proxy( 
    ISignature * This,
    /* [in] */ long sigIndex,
    /* [in] */ long uriIndex,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_DocumentURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_DigestObjectStatus_Proxy( 
    ISignature * This,
    /* [in] */ long sigIndex,
    /* [in] */ long uriIndex,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB ISignature_get_DigestObjectStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_CaptureOnce_Proxy( 
    ISignature * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB ISignature_get_CaptureOnce_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_CaptureOnce_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB ISignature_put_CaptureOnce_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_SignatureStatus_Proxy( 
    ISignature * This,
    /* [in] */ long sigIndex,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB ISignature_get_SignatureStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_PhysicalSignatureUsage_Proxy( 
    ISignature * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ISignature_get_PhysicalSignatureUsage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_PhysicalSignatureUsage_Proxy( 
    ISignature * This,
    /* [in] */ long newVal);


void __RPC_STUB ISignature_put_PhysicalSignatureUsage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_PhysicalSignatureFile_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_PhysicalSignatureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_PhysicalSignatureFile_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_PhysicalSignatureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_CapturedSignatureFile_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_CapturedSignatureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_Sign_Proxy( 
    ISignature * This,
    /* [in] */ BSTR URI,
    /* [retval][out] */ BSTR *tempFileName);


void __RPC_STUB ISignature_Sign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GetXMLSignature_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *xmlSignature);


void __RPC_STUB ISignature_GetXMLSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SaveXMLSignature_Proxy( 
    ISignature * This,
    /* [in] */ BSTR sigFileName);


void __RPC_STUB ISignature_SaveXMLSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_Verify_Proxy( 
    ISignature * This,
    /* [in] */ BSTR signatureFileName,
    /* [retval][out] */ BOOL *sigStatus);


void __RPC_STUB ISignature_Verify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GetError_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *errorString);


void __RPC_STUB ISignature_GetError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_OverwriteFile_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB ISignature_put_OverwriteFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_PFXExportCertificate_Proxy( 
    ISignature * This,
    /* [in] */ BSTR certID,
    /* [in] */ BSTR password,
    /* [retval][out] */ BSTR *pfxFilePath);


void __RPC_STUB ISignature_PFXExportCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_VerifyDetached_Proxy( 
    ISignature * This,
    /* [in] */ BSTR signatureFileName,
    /* [retval][out] */ BOOL *sigStatus);


void __RPC_STUB ISignature_VerifyDetached_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GetLastError_Proxy( 
    ISignature * This,
    /* [retval][out] */ long *errorNum);


void __RPC_STUB ISignature_GetLastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GetX509Certificate_Proxy( 
    ISignature * This,
    /* [in] */ BSTR certID,
    /* [retval][out] */ BSTR *certData);


void __RPC_STUB ISignature_GetX509Certificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_ViewCertificate_Proxy( 
    ISignature * This,
    /* [in] */ BSTR certID);


void __RPC_STUB ISignature_ViewCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_CertificateCount_Proxy( 
    ISignature * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ISignature_get_CertificateCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GetCertificateInfo_Proxy( 
    ISignature * This,
    /* [in] */ long index,
    /* [in] */ long valIndex,
    /* [retval][out] */ BSTR *value);


void __RPC_STUB ISignature_GetCertificateInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SetActiveCertificate_Proxy( 
    ISignature * This,
    /* [in] */ BSTR certID,
    /* [retval][out] */ BOOL *status);


void __RPC_STUB ISignature_SetActiveCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_SignedDocumentPath_Proxy( 
    ISignature * This,
    /* [in] */ long sigIndex,
    /* [in] */ long uriIndex,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_SignedDocumentPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_SignerSubject_Proxy( 
    ISignature * This,
    /* [in] */ BSTR sigId,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_SignerSubject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_CertIssuer_Proxy( 
    ISignature * This,
    /* [in] */ BSTR sigId,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_CertIssuer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_CertExpiry_Proxy( 
    ISignature * This,
    /* [in] */ BSTR sigId,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_CertExpiry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_CertSerialNumber_Proxy( 
    ISignature * This,
    /* [in] */ BSTR sigId,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_CertSerialNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_FileExists_Proxy( 
    ISignature * This,
    /* [in] */ BSTR fileName,
    /* [retval][out] */ BOOL *fileStatus);


void __RPC_STUB ISignature_FileExists_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_FailedUriCount_Proxy( 
    ISignature * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ISignature_get_FailedUriCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_TotalUriCount_Proxy( 
    ISignature * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ISignature_get_TotalUriCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_FailedUriFullPath_Proxy( 
    ISignature * This,
    /* [in] */ long index,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_FailedUriFullPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_FailedUriFullPath_Proxy( 
    ISignature * This,
    /* [in] */ long index,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_FailedUriFullPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_FailedUri_Proxy( 
    ISignature * This,
    /* [in] */ long index,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_FailedUri_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_SignatureCount_Proxy( 
    ISignature * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ISignature_get_SignatureCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SignXMLStr_Proxy( 
    ISignature * This,
    /* [in] */ BSTR xmlStr,
    /* [in] */ BSTR signatureId,
    /* [retval][out] */ BSTR *signedXMLStr);


void __RPC_STUB ISignature_SignXMLStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_ReadAll_Proxy( 
    ISignature * This,
    /* [in] */ BSTR fileName,
    /* [retval][out] */ BSTR *fileDataStr);


void __RPC_STUB ISignature_ReadAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SaveXMLStr_Proxy( 
    ISignature * This,
    /* [in] */ BSTR inputXMLStr,
    /* [in] */ BSTR fileName,
    /* [retval][out] */ BSTR *path);


void __RPC_STUB ISignature_SaveXMLStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SignHTML_Proxy( 
    ISignature * This,
    /* [in] */ IDispatch *document,
    /* [retval][out] */ BSTR *signedHTML);


void __RPC_STUB ISignature_SignHTML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SecureXMLVerify_Proxy( 
    ISignature * This,
    /* [in] */ BSTR signedXML,
    /* [retval][out] */ BSTR *verificationResponse);


void __RPC_STUB ISignature_SecureXMLVerify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SetCSP_Proxy( 
    ISignature * This,
    /* [in] */ BSTR CSPName);


void __RPC_STUB ISignature_SetCSP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GetSignedHTML_Proxy( 
    ISignature * This,
    /* [in] */ BSTR signedHtmlXML,
    /* [retval][out] */ BSTR *originalHTML);


void __RPC_STUB ISignature_GetSignedHTML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SignFile_Proxy( 
    ISignature * This,
    /* [in] */ BSTR inputFile,
    /* [in] */ BSTR outputFile);


void __RPC_STUB ISignature_SignFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GetSignedFileObject_Proxy( 
    ISignature * This,
    /* [in] */ BSTR signedXML,
    /* [in] */ BSTR saveDir,
    /* [retval][out] */ BSTR *signedFilePath);


void __RPC_STUB ISignature_GetSignedFileObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SetStoreName_Proxy( 
    ISignature * This,
    /* [in] */ BSTR storeName);


void __RPC_STUB ISignature_SetStoreName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GetStoreName_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *storeName);


void __RPC_STUB ISignature_GetStoreName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SignXMLEnveloped_Proxy( 
    ISignature * This,
    /* [in] */ BSTR inputXML,
    /* [in] */ BSTR sigId,
    /* [retval][out] */ BSTR *signedXML);


void __RPC_STUB ISignature_SignXMLEnveloped_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GetVersion_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *version);


void __RPC_STUB ISignature_GetVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GetLicenseStatus_Proxy( 
    ISignature * This,
    /* [retval][out] */ long *licStatus);


void __RPC_STUB ISignature_GetLicenseStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_GetPropertyCount_Proxy( 
    ISignature * This,
    /* [in] */ long sigIndex,
    /* [retval][out] */ long *propCount);


void __RPC_STUB ISignature_GetPropertyCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_ViewAnyCertificate_Proxy( 
    ISignature * This,
    /* [in] */ BSTR inputX509Data);


void __RPC_STUB ISignature_ViewAnyCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SelectActiveCertificate_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *certID);


void __RPC_STUB ISignature_SelectActiveCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_VerifyXMLStr_Proxy( 
    ISignature * This,
    /* [in] */ BSTR signedXML,
    /* [retval][out] */ BOOL *sigStatus);


void __RPC_STUB ISignature_VerifyXMLStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SetActivePFXFileCert_Proxy( 
    ISignature * This,
    /* [in] */ BSTR pfxFileName,
    /* [in] */ BSTR pfxPassword,
    /* [retval][out] */ BSTR *x509Cert);


void __RPC_STUB ISignature_SetActivePFXFileCert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_PFXExportActiveCertificate_Proxy( 
    ISignature * This,
    /* [in] */ BSTR password,
    /* [retval][out] */ BSTR *pfxFilePath);


void __RPC_STUB ISignature_PFXExportActiveCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_HostName_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_HostName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_TimeStampURL_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_TimeStampURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_TimeStampURL_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_TimeStampURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_TimeStamping_Proxy( 
    ISignature * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB ISignature_get_TimeStamping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_TimeStamping_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB ISignature_put_TimeStamping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_HostOsType_Proxy( 
    ISignature * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ISignature_get_HostOsType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_CrlChecking_Proxy( 
    ISignature * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB ISignature_get_CrlChecking_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_CrlChecking_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB ISignature_put_CrlChecking_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_SigCertStatus_Proxy( 
    ISignature * This,
    /* [in] */ long sigIndex,
    /* [in] */ BSTR atTime,
    /* [in] */ long timeFormat,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ISignature_get_SigCertStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_VerifyX509CertCRL_Proxy( 
    ISignature * This,
    /* [in] */ BSTR certData,
    /* [in] */ BSTR atTime,
    /* [in] */ long timeFormat,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB ISignature_VerifyX509CertCRL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_VerifyPFXCertCRL_Proxy( 
    ISignature * This,
    /* [in] */ BSTR pfxFileName,
    /* [in] */ BSTR pfxPassword,
    /* [in] */ BSTR atTime,
    /* [in] */ long timeFormat,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB ISignature_VerifyPFXCertCRL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_AddWindowImage_Proxy( 
    ISignature * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB ISignature_get_AddWindowImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_AddWindowImage_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB ISignature_put_AddWindowImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_EmailSupport_Proxy( 
    ISignature * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB ISignature_get_EmailSupport_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_EmailSupport_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB ISignature_put_EmailSupport_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_EmailFrom_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_EmailFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_EmailFrom_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_EmailFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_EmailTo_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_EmailTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_EmailTo_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_EmailTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_EmailCc_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_EmailCc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_EmailCc_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_EmailCc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_EmailBcc_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_EmailBcc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_EmailBcc_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_EmailBcc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_EmailUserName_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_EmailUserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_EmailUserName_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_EmailUserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_EmailUserPassword_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_EmailUserPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_EmailUserPassword_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_EmailUserPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_DefaultEmailRecipient_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_DefaultEmailRecipient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_DefaultEmailRecipient_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_DefaultEmailRecipient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_SendAutomaticEmail_Proxy( 
    ISignature * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB ISignature_get_SendAutomaticEmail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_SendAutomaticEmail_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB ISignature_put_SendAutomaticEmail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_EmailServerType_Proxy( 
    ISignature * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ISignature_get_EmailServerType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_EmailServerType_Proxy( 
    ISignature * This,
    /* [in] */ long newVal);


void __RPC_STUB ISignature_put_EmailServerType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_ExchangeServer_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_ExchangeServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_ExchangeServer_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_ExchangeServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_SmtpServer_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_SmtpServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_SmtpServer_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_SmtpServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SignXMLXpathStr_Proxy( 
    ISignature * This,
    /* [in] */ BSTR xmlStr,
    /* [in] */ BSTR xpathExp,
    /* [in] */ BSTR signatureId,
    /* [retval][out] */ BSTR *signedXMLStr);


void __RPC_STUB ISignature_SignXMLXpathStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_UseHMAC_Proxy( 
    ISignature * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB ISignature_get_UseHMAC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_UseHMAC_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB ISignature_put_UseHMAC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignature_get_HMACPassword_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISignature_get_HMACPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_HMACPassword_Proxy( 
    ISignature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignature_put_HMACPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_ChangeOrAddProperty_Proxy( 
    ISignature * This,
    /* [in] */ BSTR propertyName,
    /* [in] */ BSTR propertyValue);


void __RPC_STUB ISignature_ChangeOrAddProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_DetailedVerificationFlag_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB ISignature_put_DetailedVerificationFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_CaptureLiveSignature_Proxy( 
    ISignature * This,
    /* [retval][out] */ BSTR *signatureFilePath);


void __RPC_STUB ISignature_CaptureLiveSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_SignDataStr_Proxy( 
    ISignature * This,
    /* [in] */ BSTR dataStrPtr,
    /* [retval][out] */ BSTR *signedXMLStr);


void __RPC_STUB ISignature_SignDataStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignature_put_ExcludeSignerCertificate_Proxy( 
    ISignature * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB ISignature_put_ExcludeSignerCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_CoSignDataXMLStr_Proxy( 
    ISignature * This,
    /* [in] */ BSTR signedDataXMLStr,
    /* [retval][out] */ BSTR *coSignedXMLStr);


void __RPC_STUB ISignature_CoSignDataXMLStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISignature_CoSignFileXMLStr_Proxy( 
    ISignature * This,
    /* [in] */ BSTR signedDataXMLStr,
    /* [retval][out] */ BSTR *coSignedXMLStr);


void __RPC_STUB ISignature_CoSignFileXMLStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISignature_INTERFACE_DEFINED__ */



#ifndef __XMLSIGNLib_LIBRARY_DEFINED__
#define __XMLSIGNLib_LIBRARY_DEFINED__

/* library XMLSIGNLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_XMLSIGNLib;

EXTERN_C const CLSID CLSID_Signature;

#ifdef __cplusplus

class DECLSPEC_UUID("D300C133-A6F6-4FB4-A734-4865FBF5A3B1")
Signature;
#endif
#endif /* __XMLSIGNLib_LIBRARY_DEFINED__ */

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


