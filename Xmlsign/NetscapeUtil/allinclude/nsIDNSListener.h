/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIDNSListener.idl
 */

#ifndef __gen_nsIDNSListener_h__
#define __gen_nsIDNSListener_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDNSRequest; /* forward declaration */

class nsIDNSRecord; /* forward declaration */


/* starting interface:    nsIDNSListener */
#define NS_IDNSLISTENER_IID_STR "36413eba-3a2a-444d-b88e-df9b6d306b73"

#define NS_IDNSLISTENER_IID \
  {0x36413eba, 0x3a2a, 0x444d, \
    { 0xb8, 0x8e, 0xdf, 0x9b, 0x6d, 0x30, 0x6b, 0x73 }}

/**
 * nsIDNSListener
 */
class NS_NO_VTABLE nsIDNSListener : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDNSLISTENER_IID)

  /**
     * called when an asynchronous host lookup completes.
     *
     * @param aRequest
     *        the value returned from asyncResolve.
     * @param aRecord
     *        the DNS record corresponding to the hostname that was resolved.
     *        this parameter is null if there was an error.
     * @param aStatus
     *        if the lookup failed, this parameter gives the reason.
     */
  /* void onLookupComplete (in nsIDNSRequest aRequest, in nsIDNSRecord aRecord, in nsresult aStatus); */
  NS_IMETHOD OnLookupComplete(nsIDNSRequest *aRequest, nsIDNSRecord *aRecord, nsresult aStatus) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDNSLISTENER \
  NS_IMETHOD OnLookupComplete(nsIDNSRequest *aRequest, nsIDNSRecord *aRecord, nsresult aStatus); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDNSLISTENER(_to) \
  NS_IMETHOD OnLookupComplete(nsIDNSRequest *aRequest, nsIDNSRecord *aRecord, nsresult aStatus) { return _to OnLookupComplete(aRequest, aRecord, aStatus); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDNSLISTENER(_to) \
  NS_IMETHOD OnLookupComplete(nsIDNSRequest *aRequest, nsIDNSRecord *aRecord, nsresult aStatus) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnLookupComplete(aRequest, aRecord, aStatus); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDNSListener : public nsIDNSListener
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDNSLISTENER

  nsDNSListener();
  virtual ~nsDNSListener();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDNSListener, nsIDNSListener)

nsDNSListener::nsDNSListener()
{
  /* member initializers and constructor code */
}

nsDNSListener::~nsDNSListener()
{
  /* destructor code */
}

/* void onLookupComplete (in nsIDNSRequest aRequest, in nsIDNSRecord aRecord, in nsresult aStatus); */
NS_IMETHODIMP nsDNSListener::OnLookupComplete(nsIDNSRequest *aRequest, nsIDNSRecord *aRecord, nsresult aStatus)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDNSListener_h__ */
