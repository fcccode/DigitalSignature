/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsISocketTransport.idl
 */

#ifndef __gen_nsISocketTransport_h__
#define __gen_nsISocketTransport_h__


#ifndef __gen_nsITransport_h__
#include "nsITransport.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIInterfaceRequestor; /* forward declaration */

class nsISocketEventSink; /* forward declaration */


/* starting interface:    nsISocketTransport */
#define NS_ISOCKETTRANSPORT_IID_STR "1e372001-ca12-4507-8405-3267d4e0c1fd"

#define NS_ISOCKETTRANSPORT_IID \
  {0x1e372001, 0xca12, 0x4507, \
    { 0x84, 0x05, 0x32, 0x67, 0xd4, 0xe0, 0xc1, 0xfd }}

/**
 * nsISocketTransport
 *
 * NOTE: This is a free-threaded interface, meaning that the methods on
 * this interface may be called from any thread.
 */
class NS_NO_VTABLE nsISocketTransport : public nsITransport {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ISOCKETTRANSPORT_IID)

  /**
     * Get the host for the underlying socket connection.
     */
  /* readonly attribute AUTF8String host; */
  NS_IMETHOD GetHost(nsACString & aHost) = 0;

  /**
     * Get the port for the underlying socket connection.
     */
  /* readonly attribute long port; */
  NS_IMETHOD GetPort(PRInt32 *aPort) = 0;

  /** 
     * Returns the IP address for the underlying socket connection.  This
     * attribute is only defined once a connection has been established.
     */
  /* [noscript] PRNetAddr getAddress (); */
  NS_IMETHOD GetAddress(union PRNetAddr *_retval) = 0;

  /**
     * Security info object returned from the secure socket provider.  This
     * object supports nsISSLSocketControl, nsITransportSecurityInfo, and
     * possibly other interfaces.
     */
  /* readonly attribute nsISupports securityInfo; */
  NS_IMETHOD GetSecurityInfo(nsISupports * *aSecurityInfo) = 0;

  /**
     * Security notification callbacks passed to the secure socket provider
     * via nsISSLSocketControl at socket creation time.
     *
     * NOTE: this attribute cannot be changed once a stream has been opened.
     */
  /* attribute nsIInterfaceRequestor securityCallbacks; */
  NS_IMETHOD GetSecurityCallbacks(nsIInterfaceRequestor * *aSecurityCallbacks) = 0;
  NS_IMETHOD SetSecurityCallbacks(nsIInterfaceRequestor * aSecurityCallbacks) = 0;

  /**
     * Test if this socket transport is (still) connected.
     */
  /* boolean isAlive (); */
  NS_IMETHOD IsAlive(PRBool *_retval) = 0;

  /**
     * nsITransportEventSink status codes.
     *
     * Although these look like XPCOM error codes and are passed in an nsresult
     * variable, they are *not* error codes.  Note that while they *do* overlap
     * with existing error codes in Necko, these status codes are confined
     * within a very limited context where no error codes may appear, so there
     * is no ambiguity.
     *
     * The values of these status codes must never change.
     *
     * The status codes appear in near-chronological order (not in numeric
     * order).  STATUS_RESOLVING may be skipped if the host does not need to be
     * resolved.  STATUS_WAITING_FOR is an optional status code, which the impl
     * of this interface may choose not to generate.
     */
  enum { STATUS_RESOLVING = 2152398851U };

  enum { STATUS_CONNECTING_TO = 2152398855U };

  enum { STATUS_CONNECTED_TO = 2152398852U };

  enum { STATUS_SENDING_TO = 2152398853U };

  enum { STATUS_WAITING_FOR = 2152398858U };

  enum { STATUS_RECEIVING_FROM = 2152398854U };

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISOCKETTRANSPORT \
  NS_IMETHOD GetHost(nsACString & aHost); \
  NS_IMETHOD GetPort(PRInt32 *aPort); \
  NS_IMETHOD GetAddress(union PRNetAddr *_retval); \
  NS_IMETHOD GetSecurityInfo(nsISupports * *aSecurityInfo); \
  NS_IMETHOD GetSecurityCallbacks(nsIInterfaceRequestor * *aSecurityCallbacks); \
  NS_IMETHOD SetSecurityCallbacks(nsIInterfaceRequestor * aSecurityCallbacks); \
  NS_IMETHOD IsAlive(PRBool *_retval); \

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISOCKETTRANSPORT(_to) \
  NS_IMETHOD GetHost(nsACString & aHost) { return _to GetHost(aHost); } \
  NS_IMETHOD GetPort(PRInt32 *aPort) { return _to GetPort(aPort); } \
  NS_IMETHOD GetAddress(union PRNetAddr *_retval) { return _to GetAddress(_retval); } \
  NS_IMETHOD GetSecurityInfo(nsISupports * *aSecurityInfo) { return _to GetSecurityInfo(aSecurityInfo); } \
  NS_IMETHOD GetSecurityCallbacks(nsIInterfaceRequestor * *aSecurityCallbacks) { return _to GetSecurityCallbacks(aSecurityCallbacks); } \
  NS_IMETHOD SetSecurityCallbacks(nsIInterfaceRequestor * aSecurityCallbacks) { return _to SetSecurityCallbacks(aSecurityCallbacks); } \
  NS_IMETHOD IsAlive(PRBool *_retval) { return _to IsAlive(_retval); } \

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISOCKETTRANSPORT(_to) \
  NS_IMETHOD GetHost(nsACString & aHost) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetHost(aHost); } \
  NS_IMETHOD GetPort(PRInt32 *aPort) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPort(aPort); } \
  NS_IMETHOD GetAddress(union PRNetAddr *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAddress(_retval); } \
  NS_IMETHOD GetSecurityInfo(nsISupports * *aSecurityInfo) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSecurityInfo(aSecurityInfo); } \
  NS_IMETHOD GetSecurityCallbacks(nsIInterfaceRequestor * *aSecurityCallbacks) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSecurityCallbacks(aSecurityCallbacks); } \
  NS_IMETHOD SetSecurityCallbacks(nsIInterfaceRequestor * aSecurityCallbacks) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSecurityCallbacks(aSecurityCallbacks); } \
  NS_IMETHOD IsAlive(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsAlive(_retval); } \

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSocketTransport : public nsISocketTransport
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISOCKETTRANSPORT

  nsSocketTransport();
  virtual ~nsSocketTransport();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSocketTransport, nsISocketTransport)

nsSocketTransport::nsSocketTransport()
{
  /* member initializers and constructor code */
}

nsSocketTransport::~nsSocketTransport()
{
  /* destructor code */
}

/* readonly attribute AUTF8String host; */
NS_IMETHODIMP nsSocketTransport::GetHost(nsACString & aHost)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long port; */
NS_IMETHODIMP nsSocketTransport::GetPort(PRInt32 *aPort)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] PRNetAddr getAddress (); */
NS_IMETHODIMP nsSocketTransport::GetAddress(union PRNetAddr *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsISupports securityInfo; */
NS_IMETHODIMP nsSocketTransport::GetSecurityInfo(nsISupports * *aSecurityInfo)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIInterfaceRequestor securityCallbacks; */
NS_IMETHODIMP nsSocketTransport::GetSecurityCallbacks(nsIInterfaceRequestor * *aSecurityCallbacks)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSocketTransport::SetSecurityCallbacks(nsIInterfaceRequestor * aSecurityCallbacks)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isAlive (); */
NS_IMETHODIMP nsSocketTransport::IsAlive(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

/**
 * #define's for compatibility
 */
#define NS_NET_STATUS_RESOLVING_HOST nsISocketTransport::STATUS_RESOLVING
#define NS_NET_STATUS_CONNECTED_TO   nsISocketTransport::STATUS_CONNECTED_TO
#define NS_NET_STATUS_SENDING_TO     nsISocketTransport::STATUS_SENDING_TO
#define NS_NET_STATUS_RECEIVING_FROM nsISocketTransport::STATUS_RECEIVING_FROM
#define NS_NET_STATUS_CONNECTING_TO  nsISocketTransport::STATUS_CONNECTING_TO
#define NS_NET_STATUS_WAITING_FOR    nsISocketTransport::STATUS_WAITING_FOR

#endif /* __gen_nsISocketTransport_h__ */
