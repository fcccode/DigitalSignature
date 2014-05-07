/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIDNSService.idl
 */

#ifndef __gen_nsIDNSService_h__
#define __gen_nsIDNSService_h__


#ifndef __gen_nsIDNSRecord_h__
#include "nsIDNSRecord.h"
#endif

#ifndef __gen_nsIDNSRequest_h__
#include "nsIDNSRequest.h"
#endif

#ifndef __gen_nsIDNSListener_h__
#include "nsIDNSListener.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIEventQueue; /* forward declaration */


/* starting interface:    nsIDNSService */
#define NS_IDNSSERVICE_IID_STR "98519315-f139-405e-9182-3339907c29fd"

#define NS_IDNSSERVICE_IID \
  {0x98519315, 0xf139, 0x405e, \
    { 0x91, 0x82, 0x33, 0x39, 0x90, 0x7c, 0x29, 0xfd }}

/**
 * nsIDNSService
 */
class NS_NO_VTABLE nsIDNSService : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDNSSERVICE_IID)

  /**
     * called to initialize the DNS service.
     */
  /* void init (); */
  NS_IMETHOD Init(void) = 0;

  /**
     * called to shutdown the DNS service.  any pending asynchronous
     * requests will be canceled, and the local cache of DNS records
     * will be cleared.  NOTE: the operating system may still have
     * its own cache of DNS records, which would be unaffected by
     * this method.
     */
  /* void shutdown (); */
  NS_IMETHOD Shutdown(void) = 0;

  /**
     * kicks off an asynchronous host lookup.
     *
     * @param aHostName
     *        the hostname or IP-address-literal to resolve.
     * @param aBypassCache
     *        if true, the internal DNS lookup cache will be bypassed.
     * @param aListener
     *        the listener to be notified when the result is available.
     * @param aListenerEventQ
     *        optional parameter (may be null).  if non-null, this parameter
     *        specifies the nsIEventQueue of the thread on which the listener's
     *        onLookupComplete should be called.  however, if this parameter is
     *        null, then onLookupComplete will be called on an unspecified
     *        thread (possibly recursively).
     *
     * @return DNS request instance that can be used to cancel the host lookup.
     */
  /* nsIDNSRequest asyncResolve (in AUTF8String aHostName, in boolean aBypassCache, in nsIDNSListener aListener, in nsIEventQueue aListenerEventQ); */
  NS_IMETHOD AsyncResolve(const nsACString & aHostName, PRBool aBypassCache, nsIDNSListener *aListener, nsIEventQueue *aListenerEventQ, nsIDNSRequest **_retval) = 0;

  /**
     * called to synchronously resolve a hostname.
     *
     * @param aHostName
     *        the hostname or IP-address-literal to resolve.
     * @param aBypassCache
     *        if true, the internal DNS lookup cache will be bypassed.
     *
     * @return DNS record corresponding to the given hostname.
     * @throws NS_ERROR_UNKNOWN_HOST if host could not be resolved.
     */
  /* nsIDNSRecord resolve (in AUTF8String aHostName, in boolean aBypassCache); */
  NS_IMETHOD Resolve(const nsACString & aHostName, PRBool aBypassCache, nsIDNSRecord **_retval) = 0;

  /**
     * @return the hostname of the operating system.
     */
  /* readonly attribute AUTF8String myHostName; */
  NS_IMETHOD GetMyHostName(nsACString & aMyHostName) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDNSSERVICE \
  NS_IMETHOD Init(void); \
  NS_IMETHOD Shutdown(void); \
  NS_IMETHOD AsyncResolve(const nsACString & aHostName, PRBool aBypassCache, nsIDNSListener *aListener, nsIEventQueue *aListenerEventQ, nsIDNSRequest **_retval); \
  NS_IMETHOD Resolve(const nsACString & aHostName, PRBool aBypassCache, nsIDNSRecord **_retval); \
  NS_IMETHOD GetMyHostName(nsACString & aMyHostName); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDNSSERVICE(_to) \
  NS_IMETHOD Init(void) { return _to Init(); } \
  NS_IMETHOD Shutdown(void) { return _to Shutdown(); } \
  NS_IMETHOD AsyncResolve(const nsACString & aHostName, PRBool aBypassCache, nsIDNSListener *aListener, nsIEventQueue *aListenerEventQ, nsIDNSRequest **_retval) { return _to AsyncResolve(aHostName, aBypassCache, aListener, aListenerEventQ, _retval); } \
  NS_IMETHOD Resolve(const nsACString & aHostName, PRBool aBypassCache, nsIDNSRecord **_retval) { return _to Resolve(aHostName, aBypassCache, _retval); } \
  NS_IMETHOD GetMyHostName(nsACString & aMyHostName) { return _to GetMyHostName(aMyHostName); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDNSSERVICE(_to) \
  NS_IMETHOD Init(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(); } \
  NS_IMETHOD Shutdown(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Shutdown(); } \
  NS_IMETHOD AsyncResolve(const nsACString & aHostName, PRBool aBypassCache, nsIDNSListener *aListener, nsIEventQueue *aListenerEventQ, nsIDNSRequest **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->AsyncResolve(aHostName, aBypassCache, aListener, aListenerEventQ, _retval); } \
  NS_IMETHOD Resolve(const nsACString & aHostName, PRBool aBypassCache, nsIDNSRecord **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Resolve(aHostName, aBypassCache, _retval); } \
  NS_IMETHOD GetMyHostName(nsACString & aMyHostName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMyHostName(aMyHostName); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDNSService : public nsIDNSService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDNSSERVICE

  nsDNSService();
  virtual ~nsDNSService();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDNSService, nsIDNSService)

nsDNSService::nsDNSService()
{
  /* member initializers and constructor code */
}

nsDNSService::~nsDNSService()
{
  /* destructor code */
}

/* void init (); */
NS_IMETHODIMP nsDNSService::Init()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void shutdown (); */
NS_IMETHODIMP nsDNSService::Shutdown()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDNSRequest asyncResolve (in AUTF8String aHostName, in boolean aBypassCache, in nsIDNSListener aListener, in nsIEventQueue aListenerEventQ); */
NS_IMETHODIMP nsDNSService::AsyncResolve(const nsACString & aHostName, PRBool aBypassCache, nsIDNSListener *aListener, nsIEventQueue *aListenerEventQ, nsIDNSRequest **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDNSRecord resolve (in AUTF8String aHostName, in boolean aBypassCache); */
NS_IMETHODIMP nsDNSService::Resolve(const nsACString & aHostName, PRBool aBypassCache, nsIDNSRecord **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AUTF8String myHostName; */
NS_IMETHODIMP nsDNSService::GetMyHostName(nsACString & aMyHostName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDNSService_h__ */
