/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIProxy.idl
 */

#ifndef __gen_nsIProxy_h__
#define __gen_nsIProxy_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIProxy */
#define NS_IPROXY_IID_STR "0492d011-cd2f-11d2-b013-006097bfc036"

#define NS_IPROXY_IID \
  {0x0492d011, 0xcd2f, 0x11d2, \
    { 0xb0, 0x13, 0x00, 0x60, 0x97, 0xbf, 0xc0, 0x36 }}

class NS_NO_VTABLE nsIProxy : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IPROXY_IID)

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIPROXY \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIPROXY(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIPROXY(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsProxy : public nsIProxy
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIPROXY

  nsProxy();
  virtual ~nsProxy();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsProxy, nsIProxy)

nsProxy::nsProxy()
{
  /* member initializers and constructor code */
}

nsProxy::~nsProxy()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIProxy_h__ */
