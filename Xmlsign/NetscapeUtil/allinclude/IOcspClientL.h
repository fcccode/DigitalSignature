/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM IOcspClientL.idl
 */

#ifndef __gen_IOcspClientL_h__
#define __gen_IOcspClientL_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IOcspClientL */
#define IOCSPCLIENTL_IID_STR "6d9e394e-f132-47a1-a33b-c057bb3204fb"

#define IOCSPCLIENTL_IID \
  {0x6d9e394e, 0xf132, 0x47a1, \
    { 0xa3, 0x3b, 0xc0, 0x57, 0xbb, 0x32, 0x04, 0xfb }}

class NS_NO_VTABLE IOcspClientL : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(IOCSPCLIENTL_IID)

  /* unsigned short verify (in AString responderUrl); */
  NS_IMETHOD Verify(const nsAString & responderUrl, PRUint16 *_retval) = 0;

  /* readonly attribute AString TextResponse; */
  NS_IMETHOD GetTextResponse(nsAString & aTextResponse) = 0;

  /* readonly attribute AString errors; */
  NS_IMETHOD GetErrors(nsAString & aErrors) = 0;

  /* readonly attribute AString Base64Response; */
  NS_IMETHOD GetBase64Response(nsAString & aBase64Response) = 0;

  /* readonly attribute AString RevocationTime; */
  NS_IMETHOD GetRevocationTime(nsAString & aRevocationTime) = 0;

  /* readonly attribute AString RevocationReason; */
  NS_IMETHOD GetRevocationReason(nsAString & aRevocationReason) = 0;

  /* attribute AString OcspNonce; */
  NS_IMETHOD GetOcspNonce(nsAString & aOcspNonce) = 0;
  NS_IMETHOD SetOcspNonce(const nsAString & aOcspNonce) = 0;

  /* attribute AString ResponderCAFileName; */
  NS_IMETHOD GetResponderCAFileName(nsAString & aResponderCAFileName) = 0;
  NS_IMETHOD SetResponderCAFileName(const nsAString & aResponderCAFileName) = 0;

  /* attribute AString CheckCertificate; */
  NS_IMETHOD GetCheckCertificate(nsAString & aCheckCertificate) = 0;
  NS_IMETHOD SetCheckCertificate(const nsAString & aCheckCertificate) = 0;

  /* attribute AString IssuerCertificate; */
  NS_IMETHOD GetIssuerCertificate(nsAString & aIssuerCertificate) = 0;
  NS_IMETHOD SetIssuerCertificate(const nsAString & aIssuerCertificate) = 0;

  /* attribute AString CheckCertificateFileName; */
  NS_IMETHOD GetCheckCertificateFileName(nsAString & aCheckCertificateFileName) = 0;
  NS_IMETHOD SetCheckCertificateFileName(const nsAString & aCheckCertificateFileName) = 0;

  /* attribute AString IssuerCertificateFileName; */
  NS_IMETHOD GetIssuerCertificateFileName(nsAString & aIssuerCertificateFileName) = 0;
  NS_IMETHOD SetIssuerCertificateFileName(const nsAString & aIssuerCertificateFileName) = 0;

  /* attribute unsigned short CheckCertificateFileFormat; */
  NS_IMETHOD GetCheckCertificateFileFormat(PRUint16 *aCheckCertificateFileFormat) = 0;
  NS_IMETHOD SetCheckCertificateFileFormat(PRUint16 aCheckCertificateFileFormat) = 0;

  /* attribute unsigned short IssuerCertificateFileFormat; */
  NS_IMETHOD GetIssuerCertificateFileFormat(PRUint16 *aIssuerCertificateFileFormat) = 0;
  NS_IMETHOD SetIssuerCertificateFileFormat(PRUint16 aIssuerCertificateFileFormat) = 0;

  /* attribute AString SignerPFXCertificate; */
  NS_IMETHOD GetSignerPFXCertificate(nsAString & aSignerPFXCertificate) = 0;
  NS_IMETHOD SetSignerPFXCertificate(const nsAString & aSignerPFXCertificate) = 0;

  /* attribute AString SignerPFXPassword; */
  NS_IMETHOD GetSignerPFXPassword(nsAString & aSignerPFXPassword) = 0;
  NS_IMETHOD SetSignerPFXPassword(const nsAString & aSignerPFXPassword) = 0;

  /* attribute AString CheckPFXPassword; */
  NS_IMETHOD GetCheckPFXPassword(nsAString & aCheckPFXPassword) = 0;
  NS_IMETHOD SetCheckPFXPassword(const nsAString & aCheckPFXPassword) = 0;

  /* attribute AString ResponderURL; */
  NS_IMETHOD GetResponderURL(nsAString & aResponderURL) = 0;
  NS_IMETHOD SetResponderURL(const nsAString & aResponderURL) = 0;

  /* attribute AString proxyHost; */
  NS_IMETHOD GetProxyHost(nsAString & aProxyHost) = 0;
  NS_IMETHOD SetProxyHost(const nsAString & aProxyHost) = 0;

  /* attribute unsigned short proxyPort; */
  NS_IMETHOD GetProxyPort(PRUint16 *aProxyPort) = 0;
  NS_IMETHOD SetProxyPort(PRUint16 aProxyPort) = 0;

  /* attribute AString proxyUsername; */
  NS_IMETHOD GetProxyUsername(nsAString & aProxyUsername) = 0;
  NS_IMETHOD SetProxyUsername(const nsAString & aProxyUsername) = 0;

  /* attribute AString proxyPassword; */
  NS_IMETHOD GetProxyPassword(nsAString & aProxyPassword) = 0;
  NS_IMETHOD SetProxyPassword(const nsAString & aProxyPassword) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IOCSPCLIENTL \
  NS_IMETHOD Verify(const nsAString & responderUrl, PRUint16 *_retval); \
  NS_IMETHOD GetTextResponse(nsAString & aTextResponse); \
  NS_IMETHOD GetErrors(nsAString & aErrors); \
  NS_IMETHOD GetBase64Response(nsAString & aBase64Response); \
  NS_IMETHOD GetRevocationTime(nsAString & aRevocationTime); \
  NS_IMETHOD GetRevocationReason(nsAString & aRevocationReason); \
  NS_IMETHOD GetOcspNonce(nsAString & aOcspNonce); \
  NS_IMETHOD SetOcspNonce(const nsAString & aOcspNonce); \
  NS_IMETHOD GetResponderCAFileName(nsAString & aResponderCAFileName); \
  NS_IMETHOD SetResponderCAFileName(const nsAString & aResponderCAFileName); \
  NS_IMETHOD GetCheckCertificate(nsAString & aCheckCertificate); \
  NS_IMETHOD SetCheckCertificate(const nsAString & aCheckCertificate); \
  NS_IMETHOD GetIssuerCertificate(nsAString & aIssuerCertificate); \
  NS_IMETHOD SetIssuerCertificate(const nsAString & aIssuerCertificate); \
  NS_IMETHOD GetCheckCertificateFileName(nsAString & aCheckCertificateFileName); \
  NS_IMETHOD SetCheckCertificateFileName(const nsAString & aCheckCertificateFileName); \
  NS_IMETHOD GetIssuerCertificateFileName(nsAString & aIssuerCertificateFileName); \
  NS_IMETHOD SetIssuerCertificateFileName(const nsAString & aIssuerCertificateFileName); \
  NS_IMETHOD GetCheckCertificateFileFormat(PRUint16 *aCheckCertificateFileFormat); \
  NS_IMETHOD SetCheckCertificateFileFormat(PRUint16 aCheckCertificateFileFormat); \
  NS_IMETHOD GetIssuerCertificateFileFormat(PRUint16 *aIssuerCertificateFileFormat); \
  NS_IMETHOD SetIssuerCertificateFileFormat(PRUint16 aIssuerCertificateFileFormat); \
  NS_IMETHOD GetSignerPFXCertificate(nsAString & aSignerPFXCertificate); \
  NS_IMETHOD SetSignerPFXCertificate(const nsAString & aSignerPFXCertificate); \
  NS_IMETHOD GetSignerPFXPassword(nsAString & aSignerPFXPassword); \
  NS_IMETHOD SetSignerPFXPassword(const nsAString & aSignerPFXPassword); \
  NS_IMETHOD GetCheckPFXPassword(nsAString & aCheckPFXPassword); \
  NS_IMETHOD SetCheckPFXPassword(const nsAString & aCheckPFXPassword); \
  NS_IMETHOD GetResponderURL(nsAString & aResponderURL); \
  NS_IMETHOD SetResponderURL(const nsAString & aResponderURL); \
  NS_IMETHOD GetProxyHost(nsAString & aProxyHost); \
  NS_IMETHOD SetProxyHost(const nsAString & aProxyHost); \
  NS_IMETHOD GetProxyPort(PRUint16 *aProxyPort); \
  NS_IMETHOD SetProxyPort(PRUint16 aProxyPort); \
  NS_IMETHOD GetProxyUsername(nsAString & aProxyUsername); \
  NS_IMETHOD SetProxyUsername(const nsAString & aProxyUsername); \
  NS_IMETHOD GetProxyPassword(nsAString & aProxyPassword); \
  NS_IMETHOD SetProxyPassword(const nsAString & aProxyPassword); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IOCSPCLIENTL(_to) \
  NS_IMETHOD Verify(const nsAString & responderUrl, PRUint16 *_retval) { return _to Verify(responderUrl, _retval); } \
  NS_IMETHOD GetTextResponse(nsAString & aTextResponse) { return _to GetTextResponse(aTextResponse); } \
  NS_IMETHOD GetErrors(nsAString & aErrors) { return _to GetErrors(aErrors); } \
  NS_IMETHOD GetBase64Response(nsAString & aBase64Response) { return _to GetBase64Response(aBase64Response); } \
  NS_IMETHOD GetRevocationTime(nsAString & aRevocationTime) { return _to GetRevocationTime(aRevocationTime); } \
  NS_IMETHOD GetRevocationReason(nsAString & aRevocationReason) { return _to GetRevocationReason(aRevocationReason); } \
  NS_IMETHOD GetOcspNonce(nsAString & aOcspNonce) { return _to GetOcspNonce(aOcspNonce); } \
  NS_IMETHOD SetOcspNonce(const nsAString & aOcspNonce) { return _to SetOcspNonce(aOcspNonce); } \
  NS_IMETHOD GetResponderCAFileName(nsAString & aResponderCAFileName) { return _to GetResponderCAFileName(aResponderCAFileName); } \
  NS_IMETHOD SetResponderCAFileName(const nsAString & aResponderCAFileName) { return _to SetResponderCAFileName(aResponderCAFileName); } \
  NS_IMETHOD GetCheckCertificate(nsAString & aCheckCertificate) { return _to GetCheckCertificate(aCheckCertificate); } \
  NS_IMETHOD SetCheckCertificate(const nsAString & aCheckCertificate) { return _to SetCheckCertificate(aCheckCertificate); } \
  NS_IMETHOD GetIssuerCertificate(nsAString & aIssuerCertificate) { return _to GetIssuerCertificate(aIssuerCertificate); } \
  NS_IMETHOD SetIssuerCertificate(const nsAString & aIssuerCertificate) { return _to SetIssuerCertificate(aIssuerCertificate); } \
  NS_IMETHOD GetCheckCertificateFileName(nsAString & aCheckCertificateFileName) { return _to GetCheckCertificateFileName(aCheckCertificateFileName); } \
  NS_IMETHOD SetCheckCertificateFileName(const nsAString & aCheckCertificateFileName) { return _to SetCheckCertificateFileName(aCheckCertificateFileName); } \
  NS_IMETHOD GetIssuerCertificateFileName(nsAString & aIssuerCertificateFileName) { return _to GetIssuerCertificateFileName(aIssuerCertificateFileName); } \
  NS_IMETHOD SetIssuerCertificateFileName(const nsAString & aIssuerCertificateFileName) { return _to SetIssuerCertificateFileName(aIssuerCertificateFileName); } \
  NS_IMETHOD GetCheckCertificateFileFormat(PRUint16 *aCheckCertificateFileFormat) { return _to GetCheckCertificateFileFormat(aCheckCertificateFileFormat); } \
  NS_IMETHOD SetCheckCertificateFileFormat(PRUint16 aCheckCertificateFileFormat) { return _to SetCheckCertificateFileFormat(aCheckCertificateFileFormat); } \
  NS_IMETHOD GetIssuerCertificateFileFormat(PRUint16 *aIssuerCertificateFileFormat) { return _to GetIssuerCertificateFileFormat(aIssuerCertificateFileFormat); } \
  NS_IMETHOD SetIssuerCertificateFileFormat(PRUint16 aIssuerCertificateFileFormat) { return _to SetIssuerCertificateFileFormat(aIssuerCertificateFileFormat); } \
  NS_IMETHOD GetSignerPFXCertificate(nsAString & aSignerPFXCertificate) { return _to GetSignerPFXCertificate(aSignerPFXCertificate); } \
  NS_IMETHOD SetSignerPFXCertificate(const nsAString & aSignerPFXCertificate) { return _to SetSignerPFXCertificate(aSignerPFXCertificate); } \
  NS_IMETHOD GetSignerPFXPassword(nsAString & aSignerPFXPassword) { return _to GetSignerPFXPassword(aSignerPFXPassword); } \
  NS_IMETHOD SetSignerPFXPassword(const nsAString & aSignerPFXPassword) { return _to SetSignerPFXPassword(aSignerPFXPassword); } \
  NS_IMETHOD GetCheckPFXPassword(nsAString & aCheckPFXPassword) { return _to GetCheckPFXPassword(aCheckPFXPassword); } \
  NS_IMETHOD SetCheckPFXPassword(const nsAString & aCheckPFXPassword) { return _to SetCheckPFXPassword(aCheckPFXPassword); } \
  NS_IMETHOD GetResponderURL(nsAString & aResponderURL) { return _to GetResponderURL(aResponderURL); } \
  NS_IMETHOD SetResponderURL(const nsAString & aResponderURL) { return _to SetResponderURL(aResponderURL); } \
  NS_IMETHOD GetProxyHost(nsAString & aProxyHost) { return _to GetProxyHost(aProxyHost); } \
  NS_IMETHOD SetProxyHost(const nsAString & aProxyHost) { return _to SetProxyHost(aProxyHost); } \
  NS_IMETHOD GetProxyPort(PRUint16 *aProxyPort) { return _to GetProxyPort(aProxyPort); } \
  NS_IMETHOD SetProxyPort(PRUint16 aProxyPort) { return _to SetProxyPort(aProxyPort); } \
  NS_IMETHOD GetProxyUsername(nsAString & aProxyUsername) { return _to GetProxyUsername(aProxyUsername); } \
  NS_IMETHOD SetProxyUsername(const nsAString & aProxyUsername) { return _to SetProxyUsername(aProxyUsername); } \
  NS_IMETHOD GetProxyPassword(nsAString & aProxyPassword) { return _to GetProxyPassword(aProxyPassword); } \
  NS_IMETHOD SetProxyPassword(const nsAString & aProxyPassword) { return _to SetProxyPassword(aProxyPassword); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IOCSPCLIENTL(_to) \
  NS_IMETHOD Verify(const nsAString & responderUrl, PRUint16 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Verify(responderUrl, _retval); } \
  NS_IMETHOD GetTextResponse(nsAString & aTextResponse) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTextResponse(aTextResponse); } \
  NS_IMETHOD GetErrors(nsAString & aErrors) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetErrors(aErrors); } \
  NS_IMETHOD GetBase64Response(nsAString & aBase64Response) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBase64Response(aBase64Response); } \
  NS_IMETHOD GetRevocationTime(nsAString & aRevocationTime) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRevocationTime(aRevocationTime); } \
  NS_IMETHOD GetRevocationReason(nsAString & aRevocationReason) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRevocationReason(aRevocationReason); } \
  NS_IMETHOD GetOcspNonce(nsAString & aOcspNonce) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOcspNonce(aOcspNonce); } \
  NS_IMETHOD SetOcspNonce(const nsAString & aOcspNonce) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetOcspNonce(aOcspNonce); } \
  NS_IMETHOD GetResponderCAFileName(nsAString & aResponderCAFileName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetResponderCAFileName(aResponderCAFileName); } \
  NS_IMETHOD SetResponderCAFileName(const nsAString & aResponderCAFileName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetResponderCAFileName(aResponderCAFileName); } \
  NS_IMETHOD GetCheckCertificate(nsAString & aCheckCertificate) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCheckCertificate(aCheckCertificate); } \
  NS_IMETHOD SetCheckCertificate(const nsAString & aCheckCertificate) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCheckCertificate(aCheckCertificate); } \
  NS_IMETHOD GetIssuerCertificate(nsAString & aIssuerCertificate) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIssuerCertificate(aIssuerCertificate); } \
  NS_IMETHOD SetIssuerCertificate(const nsAString & aIssuerCertificate) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetIssuerCertificate(aIssuerCertificate); } \
  NS_IMETHOD GetCheckCertificateFileName(nsAString & aCheckCertificateFileName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCheckCertificateFileName(aCheckCertificateFileName); } \
  NS_IMETHOD SetCheckCertificateFileName(const nsAString & aCheckCertificateFileName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCheckCertificateFileName(aCheckCertificateFileName); } \
  NS_IMETHOD GetIssuerCertificateFileName(nsAString & aIssuerCertificateFileName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIssuerCertificateFileName(aIssuerCertificateFileName); } \
  NS_IMETHOD SetIssuerCertificateFileName(const nsAString & aIssuerCertificateFileName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetIssuerCertificateFileName(aIssuerCertificateFileName); } \
  NS_IMETHOD GetCheckCertificateFileFormat(PRUint16 *aCheckCertificateFileFormat) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCheckCertificateFileFormat(aCheckCertificateFileFormat); } \
  NS_IMETHOD SetCheckCertificateFileFormat(PRUint16 aCheckCertificateFileFormat) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCheckCertificateFileFormat(aCheckCertificateFileFormat); } \
  NS_IMETHOD GetIssuerCertificateFileFormat(PRUint16 *aIssuerCertificateFileFormat) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIssuerCertificateFileFormat(aIssuerCertificateFileFormat); } \
  NS_IMETHOD SetIssuerCertificateFileFormat(PRUint16 aIssuerCertificateFileFormat) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetIssuerCertificateFileFormat(aIssuerCertificateFileFormat); } \
  NS_IMETHOD GetSignerPFXCertificate(nsAString & aSignerPFXCertificate) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSignerPFXCertificate(aSignerPFXCertificate); } \
  NS_IMETHOD SetSignerPFXCertificate(const nsAString & aSignerPFXCertificate) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSignerPFXCertificate(aSignerPFXCertificate); } \
  NS_IMETHOD GetSignerPFXPassword(nsAString & aSignerPFXPassword) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSignerPFXPassword(aSignerPFXPassword); } \
  NS_IMETHOD SetSignerPFXPassword(const nsAString & aSignerPFXPassword) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSignerPFXPassword(aSignerPFXPassword); } \
  NS_IMETHOD GetCheckPFXPassword(nsAString & aCheckPFXPassword) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCheckPFXPassword(aCheckPFXPassword); } \
  NS_IMETHOD SetCheckPFXPassword(const nsAString & aCheckPFXPassword) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCheckPFXPassword(aCheckPFXPassword); } \
  NS_IMETHOD GetResponderURL(nsAString & aResponderURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetResponderURL(aResponderURL); } \
  NS_IMETHOD SetResponderURL(const nsAString & aResponderURL) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetResponderURL(aResponderURL); } \
  NS_IMETHOD GetProxyHost(nsAString & aProxyHost) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetProxyHost(aProxyHost); } \
  NS_IMETHOD SetProxyHost(const nsAString & aProxyHost) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetProxyHost(aProxyHost); } \
  NS_IMETHOD GetProxyPort(PRUint16 *aProxyPort) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetProxyPort(aProxyPort); } \
  NS_IMETHOD SetProxyPort(PRUint16 aProxyPort) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetProxyPort(aProxyPort); } \
  NS_IMETHOD GetProxyUsername(nsAString & aProxyUsername) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetProxyUsername(aProxyUsername); } \
  NS_IMETHOD SetProxyUsername(const nsAString & aProxyUsername) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetProxyUsername(aProxyUsername); } \
  NS_IMETHOD GetProxyPassword(nsAString & aProxyPassword) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetProxyPassword(aProxyPassword); } \
  NS_IMETHOD SetProxyPassword(const nsAString & aProxyPassword) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetProxyPassword(aProxyPassword); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IOcspClientL
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IOCSPCLIENTL

  _MYCLASS_();
  virtual ~_MYCLASS_();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IOcspClientL)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* unsigned short verify (in AString responderUrl); */
NS_IMETHODIMP _MYCLASS_::Verify(const nsAString & responderUrl, PRUint16 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString TextResponse; */
NS_IMETHODIMP _MYCLASS_::GetTextResponse(nsAString & aTextResponse)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString errors; */
NS_IMETHODIMP _MYCLASS_::GetErrors(nsAString & aErrors)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString Base64Response; */
NS_IMETHODIMP _MYCLASS_::GetBase64Response(nsAString & aBase64Response)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString RevocationTime; */
NS_IMETHODIMP _MYCLASS_::GetRevocationTime(nsAString & aRevocationTime)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString RevocationReason; */
NS_IMETHODIMP _MYCLASS_::GetRevocationReason(nsAString & aRevocationReason)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString OcspNonce; */
NS_IMETHODIMP _MYCLASS_::GetOcspNonce(nsAString & aOcspNonce)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetOcspNonce(const nsAString & aOcspNonce)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString ResponderCAFileName; */
NS_IMETHODIMP _MYCLASS_::GetResponderCAFileName(nsAString & aResponderCAFileName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetResponderCAFileName(const nsAString & aResponderCAFileName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString CheckCertificate; */
NS_IMETHODIMP _MYCLASS_::GetCheckCertificate(nsAString & aCheckCertificate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetCheckCertificate(const nsAString & aCheckCertificate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString IssuerCertificate; */
NS_IMETHODIMP _MYCLASS_::GetIssuerCertificate(nsAString & aIssuerCertificate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetIssuerCertificate(const nsAString & aIssuerCertificate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString CheckCertificateFileName; */
NS_IMETHODIMP _MYCLASS_::GetCheckCertificateFileName(nsAString & aCheckCertificateFileName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetCheckCertificateFileName(const nsAString & aCheckCertificateFileName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString IssuerCertificateFileName; */
NS_IMETHODIMP _MYCLASS_::GetIssuerCertificateFileName(nsAString & aIssuerCertificateFileName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetIssuerCertificateFileName(const nsAString & aIssuerCertificateFileName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute unsigned short CheckCertificateFileFormat; */
NS_IMETHODIMP _MYCLASS_::GetCheckCertificateFileFormat(PRUint16 *aCheckCertificateFileFormat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetCheckCertificateFileFormat(PRUint16 aCheckCertificateFileFormat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute unsigned short IssuerCertificateFileFormat; */
NS_IMETHODIMP _MYCLASS_::GetIssuerCertificateFileFormat(PRUint16 *aIssuerCertificateFileFormat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetIssuerCertificateFileFormat(PRUint16 aIssuerCertificateFileFormat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString SignerPFXCertificate; */
NS_IMETHODIMP _MYCLASS_::GetSignerPFXCertificate(nsAString & aSignerPFXCertificate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetSignerPFXCertificate(const nsAString & aSignerPFXCertificate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString SignerPFXPassword; */
NS_IMETHODIMP _MYCLASS_::GetSignerPFXPassword(nsAString & aSignerPFXPassword)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetSignerPFXPassword(const nsAString & aSignerPFXPassword)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString CheckPFXPassword; */
NS_IMETHODIMP _MYCLASS_::GetCheckPFXPassword(nsAString & aCheckPFXPassword)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetCheckPFXPassword(const nsAString & aCheckPFXPassword)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString ResponderURL; */
NS_IMETHODIMP _MYCLASS_::GetResponderURL(nsAString & aResponderURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetResponderURL(const nsAString & aResponderURL)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString proxyHost; */
NS_IMETHODIMP _MYCLASS_::GetProxyHost(nsAString & aProxyHost)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetProxyHost(const nsAString & aProxyHost)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute unsigned short proxyPort; */
NS_IMETHODIMP _MYCLASS_::GetProxyPort(PRUint16 *aProxyPort)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetProxyPort(PRUint16 aProxyPort)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString proxyUsername; */
NS_IMETHODIMP _MYCLASS_::GetProxyUsername(nsAString & aProxyUsername)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetProxyUsername(const nsAString & aProxyUsername)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString proxyPassword; */
NS_IMETHODIMP _MYCLASS_::GetProxyPassword(nsAString & aProxyPassword)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetProxyPassword(const nsAString & aProxyPassword)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IOcspClientL_h__ */
