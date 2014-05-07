/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIProxyAutoConfig.idl
 */

#ifndef __gen_nsIProxyAutoConfig_h__
#define __gen_nsIProxyAutoConfig_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
/** 
 * The nsIProxyAutoConfig interface is used for setting arbitrary proxy
 * configurations based on the specified URL. 
 *
 * Note this interface wraps (at least in a the implementation) the older
 * hacks of proxy auto config. 
 *
 *  - Gagan Saksena 04/23/00 
 */
class nsIURI; /* forward declaration */

class nsIIOService; /* forward declaration */


/* starting interface:    nsIProxyAutoConfig */
#define NS_IPROXYAUTOCONFIG_IID_STR "26fae72a-1dd2-11b2-9dd9-cb3e0c2c79ba"

#define NS_IPROXYAUTOCONFIG_IID \
  {0x26fae72a, 0x1dd2, 0x11b2, \
    { 0x9d, 0xd9, 0xcb, 0x3e, 0x0c, 0x2c, 0x79, 0xba }}

class NS_NO_VTABLE nsIProxyAutoConfig : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IPROXYAUTOCONFIG_IID)

  /**
     * Get the proxy string for the specified URI.  The proxy string is
     * given by the following BNF:
     *   
     * result      = proxy-spec *( proxy-sep proxy-spec )
     * proxy-spec  = direct-type | proxy-type LWS proxy-host [":" proxy-port]
     * direct-type = "DIRECT"
     * proxy-type  = "PROXY" | "SOCKS" | "SOCKS4" | "SOCKS5"
     * proxy-sep   = ";" LWS
     * proxy-host  = hostname | ipv4-address-literal
     * proxy-port  = <any 16-bit unsigned integer>
     * LWS         = *( SP | HT )
     * SP          = <US-ASCII SP, space (32)>
     * HT          = <US-ASCII HT, horizontal-tab (9)>
     *
     * NOTE: direct-type and proxy-type are case insensitive
     * NOTE: SOCKS implies SOCKS4
     *
     * Examples:
     *   "PROXY proxy1.foo.com:8080; PROXY proxy2.foo.com:8080; DIRECT"
     *   "SOCKS socksproxy"
     *   "DIRECT"
     *
     * XXX add support for IPv6 address literals.
     * XXX quote whatever the official standard is for PAC.
     */
  /* ACString getProxyForURI (in nsIURI aURI); */
  NS_IMETHOD GetProxyForURI(nsIURI *aURI, nsACString & _retval) = 0;

  /**
     * Load the PAC file from the specified URI
     */
  /* void loadPACFromURI (in nsIURI aURI, in nsIIOService ioService); */
  NS_IMETHOD LoadPACFromURI(nsIURI *aURI, nsIIOService *ioService) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIPROXYAUTOCONFIG \
  NS_IMETHOD GetProxyForURI(nsIURI *aURI, nsACString & _retval); \
  NS_IMETHOD LoadPACFromURI(nsIURI *aURI, nsIIOService *ioService); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIPROXYAUTOCONFIG(_to) \
  NS_IMETHOD GetProxyForURI(nsIURI *aURI, nsACString & _retval) { return _to GetProxyForURI(aURI, _retval); } \
  NS_IMETHOD LoadPACFromURI(nsIURI *aURI, nsIIOService *ioService) { return _to LoadPACFromURI(aURI, ioService); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIPROXYAUTOCONFIG(_to) \
  NS_IMETHOD GetProxyForURI(nsIURI *aURI, nsACString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetProxyForURI(aURI, _retval); } \
  NS_IMETHOD LoadPACFromURI(nsIURI *aURI, nsIIOService *ioService) { return !_to ? NS_ERROR_NULL_POINTER : _to->LoadPACFromURI(aURI, ioService); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsProxyAutoConfig : public nsIProxyAutoConfig
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIPROXYAUTOCONFIG

  nsProxyAutoConfig();
  virtual ~nsProxyAutoConfig();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsProxyAutoConfig, nsIProxyAutoConfig)

nsProxyAutoConfig::nsProxyAutoConfig()
{
  /* member initializers and constructor code */
}

nsProxyAutoConfig::~nsProxyAutoConfig()
{
  /* destructor code */
}

/* ACString getProxyForURI (in nsIURI aURI); */
NS_IMETHODIMP nsProxyAutoConfig::GetProxyForURI(nsIURI *aURI, nsACString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void loadPACFromURI (in nsIURI aURI, in nsIIOService ioService); */
NS_IMETHODIMP nsProxyAutoConfig::LoadPACFromURI(nsIURI *aURI, nsIIOService *ioService)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIProxyAutoConfig_h__ */
