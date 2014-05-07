/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIProtocolProxyService.idl
 */

#ifndef __gen_nsIProtocolProxyService_h__
#define __gen_nsIProtocolProxyService_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIURI_h__
#include "nsIURI.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIProxyInfo; /* forward declaration */


/* starting interface:    nsIProtocolProxyService */
#define NS_IPROTOCOLPROXYSERVICE_IID_STR "91c4fe40-76c2-433f-9324-ffdae12df4b4"

#define NS_IPROTOCOLPROXYSERVICE_IID \
  {0x91c4fe40, 0x76c2, 0x433f, \
    { 0x93, 0x24, 0xff, 0xda, 0xe1, 0x2d, 0xf4, 0xb4 }}

class NS_NO_VTABLE nsIProtocolProxyService : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IPROTOCOLPROXYSERVICE_IID)

  /* readonly attribute PRBool proxyEnabled; */
  NS_IMETHOD GetProxyEnabled(PRBool *aProxyEnabled) = 0;

  /** Given a uri, return a proxyInfo */
  /* nsIProxyInfo examineForProxy (in nsIURI aURI); */
  NS_IMETHOD ExamineForProxy(nsIURI *aURI, nsIProxyInfo **_retval) = 0;

  /** Return a proxyInfo with the given data */
  /* nsIProxyInfo newProxyInfo (in string type, in string host, in long port); */
  NS_IMETHOD NewProxyInfo(const char *type, const char *host, PRInt32 port, nsIProxyInfo **_retval) = 0;

  /* void configureFromPAC (in string url); */
  NS_IMETHOD ConfigureFromPAC(const char *url) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIPROTOCOLPROXYSERVICE \
  NS_IMETHOD GetProxyEnabled(PRBool *aProxyEnabled); \
  NS_IMETHOD ExamineForProxy(nsIURI *aURI, nsIProxyInfo **_retval); \
  NS_IMETHOD NewProxyInfo(const char *type, const char *host, PRInt32 port, nsIProxyInfo **_retval); \
  NS_IMETHOD ConfigureFromPAC(const char *url); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIPROTOCOLPROXYSERVICE(_to) \
  NS_IMETHOD GetProxyEnabled(PRBool *aProxyEnabled) { return _to GetProxyEnabled(aProxyEnabled); } \
  NS_IMETHOD ExamineForProxy(nsIURI *aURI, nsIProxyInfo **_retval) { return _to ExamineForProxy(aURI, _retval); } \
  NS_IMETHOD NewProxyInfo(const char *type, const char *host, PRInt32 port, nsIProxyInfo **_retval) { return _to NewProxyInfo(type, host, port, _retval); } \
  NS_IMETHOD ConfigureFromPAC(const char *url) { return _to ConfigureFromPAC(url); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIPROTOCOLPROXYSERVICE(_to) \
  NS_IMETHOD GetProxyEnabled(PRBool *aProxyEnabled) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetProxyEnabled(aProxyEnabled); } \
  NS_IMETHOD ExamineForProxy(nsIURI *aURI, nsIProxyInfo **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->ExamineForProxy(aURI, _retval); } \
  NS_IMETHOD NewProxyInfo(const char *type, const char *host, PRInt32 port, nsIProxyInfo **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->NewProxyInfo(type, host, port, _retval); } \
  NS_IMETHOD ConfigureFromPAC(const char *url) { return !_to ? NS_ERROR_NULL_POINTER : _to->ConfigureFromPAC(url); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsProtocolProxyService : public nsIProtocolProxyService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIPROTOCOLPROXYSERVICE

  nsProtocolProxyService();
  virtual ~nsProtocolProxyService();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsProtocolProxyService, nsIProtocolProxyService)

nsProtocolProxyService::nsProtocolProxyService()
{
  /* member initializers and constructor code */
}

nsProtocolProxyService::~nsProtocolProxyService()
{
  /* destructor code */
}

/* readonly attribute PRBool proxyEnabled; */
NS_IMETHODIMP nsProtocolProxyService::GetProxyEnabled(PRBool *aProxyEnabled)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIProxyInfo examineForProxy (in nsIURI aURI); */
NS_IMETHODIMP nsProtocolProxyService::ExamineForProxy(nsIURI *aURI, nsIProxyInfo **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIProxyInfo newProxyInfo (in string type, in string host, in long port); */
NS_IMETHODIMP nsProtocolProxyService::NewProxyInfo(const char *type, const char *host, PRInt32 port, nsIProxyInfo **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void configureFromPAC (in string url); */
NS_IMETHODIMP nsProtocolProxyService::ConfigureFromPAC(const char *url)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIProtocolProxyService_h__ */
