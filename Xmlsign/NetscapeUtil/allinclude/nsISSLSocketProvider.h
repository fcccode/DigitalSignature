/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsISSLSocketProvider.idl
 */

#ifndef __gen_nsISSLSocketProvider_h__
#define __gen_nsISSLSocketProvider_h__


#ifndef __gen_nsISocketProvider_h__
#include "nsISocketProvider.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsISSLSocketProvider */
#define NS_ISSLSOCKETPROVIDER_IID_STR "856a93d0-5415-11d3-bbc8-0000861d1237"

#define NS_ISSLSOCKETPROVIDER_IID \
  {0x856a93d0, 0x5415, 0x11d3, \
    { 0xbb, 0xc8, 0x00, 0x00, 0x86, 0x1d, 0x12, 0x37 }}

class NS_NO_VTABLE nsISSLSocketProvider : public nsISocketProvider {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ISSLSOCKETPROVIDER_IID)

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISSLSOCKETPROVIDER \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISSLSOCKETPROVIDER(_to) \
  /* no methods! */

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISSLSOCKETPROVIDER(_to) \
  /* no methods! */

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSSLSocketProvider : public nsISSLSocketProvider
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISSLSOCKETPROVIDER

  nsSSLSocketProvider();
  virtual ~nsSSLSocketProvider();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSSLSocketProvider, nsISSLSocketProvider)

nsSSLSocketProvider::nsSSLSocketProvider()
{
  /* member initializers and constructor code */
}

nsSSLSocketProvider::~nsSSLSocketProvider()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif

#define NS_ISSLSOCKETPROVIDER_CONTRACTID     NS_NETWORK_SOCKET_CONTRACTID_PREFIX "ssl"
#define NS_ISSLSOCKETPROVIDER_CLASSNAME  "Mozilla SSL Socket Provider Component"
/* This code produces a normal socket which can be used to initiate the STARTTLS protocol
 * by calling its nsISSLSocketControl->StartTLS()
 */
#define NS_STARTTLSSOCKETPROVIDER_CONTRACTID     NS_NETWORK_SOCKET_CONTRACTID_PREFIX "starttls"
#define NS_STARTTLSSOCKETPROVIDER_CLASSNAME  "Mozilla STARTTLS Capable Socket Provider Component"

#endif /* __gen_nsISSLSocketProvider_h__ */
