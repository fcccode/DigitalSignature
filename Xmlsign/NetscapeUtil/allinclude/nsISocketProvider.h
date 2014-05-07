/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsISocketProvider.idl
 */

#ifndef __gen_nsISocketProvider_h__
#define __gen_nsISocketProvider_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsISocketProvider */
#define NS_ISOCKETPROVIDER_IID_STR "4c29772e-cf73-414a-98d9-661761a4511a"

#define NS_ISOCKETPROVIDER_IID \
  {0x4c29772e, 0xcf73, 0x414a, \
    { 0x98, 0xd9, 0x66, 0x17, 0x61, 0xa4, 0x51, 0x1a }}

/**
 * nsISocketProvider
 */
class NS_NO_VTABLE nsISocketProvider : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ISOCKETPROVIDER_IID)

  /**
     * newSocket
     *
     * @param aFamily
     *        The address family for this socket (PR_AF_INET or PR_AF_INET6).
     * @param aHost
     *        The hostname for this connection.
     * @param aPort
     *        The port for this connection.
     * @param aProxyHost
     *        If non-null, the proxy hostname for this connection.
     * @param aProxyPort
     *        The proxy port for this connection.
     * @param aFileDesc
     *        The resulting PRFileDesc.
     * @param aSecurityInfo
     *        Any security info that should be associated with aFileDesc.  This
     *        object typically implements nsITransportSecurityInfo.
     */
  /* void newSocket (in long aFamily, in string aHost, in long aPort, in string aProxyHost, in long aProxyPort, out nsFileDescStar aFileDesc, out nsISupports aSecurityInfo); */
  NS_IMETHOD NewSocket(PRInt32 aFamily, const char *aHost, PRInt32 aPort, const char *aProxyHost, PRInt32 aProxyPort, struct PRFileDesc * *aFileDesc, nsISupports **aSecurityInfo) = 0;

  /**
     * addToSocket
     *
     * This function is called to allow the socket provider to layer a PRFileDesc
     * on top of another PRFileDesc.  For example, SSL via a SOCKS proxy.
     *
     * Parameters are the same as newSocket with the exception of aFileDesc, which
     * is an in-param instead.
     */
  /* void addToSocket (in long aFamily, in string aHost, in long aPort, in string aProxyHost, in long aProxyPort, in nsFileDescStar aFileDesc, out nsISupports aSecurityInfo); */
  NS_IMETHOD AddToSocket(PRInt32 aFamily, const char *aHost, PRInt32 aPort, const char *aProxyHost, PRInt32 aProxyPort, struct PRFileDesc * aFileDesc, nsISupports **aSecurityInfo) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISOCKETPROVIDER \
  NS_IMETHOD NewSocket(PRInt32 aFamily, const char *aHost, PRInt32 aPort, const char *aProxyHost, PRInt32 aProxyPort, struct PRFileDesc * *aFileDesc, nsISupports **aSecurityInfo); \
  NS_IMETHOD AddToSocket(PRInt32 aFamily, const char *aHost, PRInt32 aPort, const char *aProxyHost, PRInt32 aProxyPort, struct PRFileDesc * aFileDesc, nsISupports **aSecurityInfo); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISOCKETPROVIDER(_to) \
  NS_IMETHOD NewSocket(PRInt32 aFamily, const char *aHost, PRInt32 aPort, const char *aProxyHost, PRInt32 aProxyPort, struct PRFileDesc * *aFileDesc, nsISupports **aSecurityInfo) { return _to NewSocket(aFamily, aHost, aPort, aProxyHost, aProxyPort, aFileDesc, aSecurityInfo); } \
  NS_IMETHOD AddToSocket(PRInt32 aFamily, const char *aHost, PRInt32 aPort, const char *aProxyHost, PRInt32 aProxyPort, struct PRFileDesc * aFileDesc, nsISupports **aSecurityInfo) { return _to AddToSocket(aFamily, aHost, aPort, aProxyHost, aProxyPort, aFileDesc, aSecurityInfo); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISOCKETPROVIDER(_to) \
  NS_IMETHOD NewSocket(PRInt32 aFamily, const char *aHost, PRInt32 aPort, const char *aProxyHost, PRInt32 aProxyPort, struct PRFileDesc * *aFileDesc, nsISupports **aSecurityInfo) { return !_to ? NS_ERROR_NULL_POINTER : _to->NewSocket(aFamily, aHost, aPort, aProxyHost, aProxyPort, aFileDesc, aSecurityInfo); } \
  NS_IMETHOD AddToSocket(PRInt32 aFamily, const char *aHost, PRInt32 aPort, const char *aProxyHost, PRInt32 aProxyPort, struct PRFileDesc * aFileDesc, nsISupports **aSecurityInfo) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddToSocket(aFamily, aHost, aPort, aProxyHost, aProxyPort, aFileDesc, aSecurityInfo); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSocketProvider : public nsISocketProvider
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISOCKETPROVIDER

  nsSocketProvider();
  virtual ~nsSocketProvider();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSocketProvider, nsISocketProvider)

nsSocketProvider::nsSocketProvider()
{
  /* member initializers and constructor code */
}

nsSocketProvider::~nsSocketProvider()
{
  /* destructor code */
}

/* void newSocket (in long aFamily, in string aHost, in long aPort, in string aProxyHost, in long aProxyPort, out nsFileDescStar aFileDesc, out nsISupports aSecurityInfo); */
NS_IMETHODIMP nsSocketProvider::NewSocket(PRInt32 aFamily, const char *aHost, PRInt32 aPort, const char *aProxyHost, PRInt32 aProxyPort, struct PRFileDesc * *aFileDesc, nsISupports **aSecurityInfo)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void addToSocket (in long aFamily, in string aHost, in long aPort, in string aProxyHost, in long aProxyPort, in nsFileDescStar aFileDesc, out nsISupports aSecurityInfo); */
NS_IMETHODIMP nsSocketProvider::AddToSocket(PRInt32 aFamily, const char *aHost, PRInt32 aPort, const char *aProxyHost, PRInt32 aProxyPort, struct PRFileDesc * aFileDesc, nsISupports **aSecurityInfo)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

/**
 * nsISocketProvider implementations should be registered with XPCOM under a
 * contract ID of the form: "@mozilla.org/network/socket;2?type=foo"
 */
#define NS_NETWORK_SOCKET_CONTRACTID_PREFIX \
    "@mozilla.org/network/socket;2?type="

#endif /* __gen_nsISocketProvider_h__ */
