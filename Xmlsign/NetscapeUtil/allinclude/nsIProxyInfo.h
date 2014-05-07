/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIProxyInfo.idl
 */

#ifndef __gen_nsIProxyInfo_h__
#define __gen_nsIProxyInfo_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIProxyInfo */
#define NS_IPROXYINFO_IID_STR "b65d22b0-1dd1-11b2-8f95-920e5b7b56f0"

#define NS_IPROXYINFO_IID \
  {0xb65d22b0, 0x1dd1, 0x11b2, \
    { 0x8f, 0x95, 0x92, 0x0e, 0x5b, 0x7b, 0x56, 0xf0 }}

class NS_NO_VTABLE nsIProxyInfo : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IPROXYINFO_IID)

  /* [noscript, notxpcom] constCharPtr Host (); */
  NS_IMETHOD_(const char*) Host(void) = 0;

  /* [noscript, notxpcom] PRInt32 Port (); */
  NS_IMETHOD_(PRInt32) Port(void) = 0;

  /* [noscript, notxpcom] constCharPtr Type (); */
  NS_IMETHOD_(const char*) Type(void) = 0;

  /**
     * proxy info objects may be chained if several proxies could be treated
     * equivalently.  this is used to support proxy failover.
     */
  /* readonly attribute nsIProxyInfo next; */
  NS_IMETHOD GetNext(nsIProxyInfo * *aNext) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIPROXYINFO \
  NS_IMETHOD_(const char*) Host(void); \
  NS_IMETHOD_(PRInt32) Port(void); \
  NS_IMETHOD_(const char*) Type(void); \
  NS_IMETHOD GetNext(nsIProxyInfo * *aNext); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIPROXYINFO(_to) \
  NS_IMETHOD_(const char*) Host(void) { return _to Host(); } \
  NS_IMETHOD_(PRInt32) Port(void) { return _to Port(); } \
  NS_IMETHOD_(const char*) Type(void) { return _to Type(); } \
  NS_IMETHOD GetNext(nsIProxyInfo * *aNext) { return _to GetNext(aNext); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIPROXYINFO(_to) \
  NS_IMETHOD_(const char*) Host(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Host(); } \
  NS_IMETHOD_(PRInt32) Port(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Port(); } \
  NS_IMETHOD_(const char*) Type(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Type(); } \
  NS_IMETHOD GetNext(nsIProxyInfo * *aNext) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNext(aNext); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsProxyInfo : public nsIProxyInfo
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIPROXYINFO

  nsProxyInfo();
  virtual ~nsProxyInfo();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsProxyInfo, nsIProxyInfo)

nsProxyInfo::nsProxyInfo()
{
  /* member initializers and constructor code */
}

nsProxyInfo::~nsProxyInfo()
{
  /* destructor code */
}

/* [noscript, notxpcom] constCharPtr Host (); */
NS_IMETHODIMP_(const char*) nsProxyInfo::Host()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript, notxpcom] PRInt32 Port (); */
NS_IMETHODIMP_(PRInt32) nsProxyInfo::Port()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript, notxpcom] constCharPtr Type (); */
NS_IMETHODIMP_(const char*) nsProxyInfo::Type()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIProxyInfo next; */
NS_IMETHODIMP nsProxyInfo::GetNext(nsIProxyInfo * *aNext)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIProxyInfo_h__ */
