/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIDNSRequest.idl
 */

#ifndef __gen_nsIDNSRequest_h__
#define __gen_nsIDNSRequest_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDNSRequest */
#define NS_IDNSREQUEST_IID_STR "3e538aea-d84b-4bf4-bae1-55f9969fe50e"

#define NS_IDNSREQUEST_IID \
  {0x3e538aea, 0xd84b, 0x4bf4, \
    { 0xba, 0xe1, 0x55, 0xf9, 0x96, 0x9f, 0xe5, 0x0e }}

/**
 * nsIDNSRequest
 */
class NS_NO_VTABLE nsIDNSRequest : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDNSREQUEST_IID)

  /**
     * called to cancel a pending asynchronous DNS request.  the listener will
     * passed to asyncResolve will be notified immediately with a status code
     * of NS_ERROR_ABORT.
     */
  /* void cancel (); */
  NS_IMETHOD Cancel(void) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDNSREQUEST \
  NS_IMETHOD Cancel(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDNSREQUEST(_to) \
  NS_IMETHOD Cancel(void) { return _to Cancel(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDNSREQUEST(_to) \
  NS_IMETHOD Cancel(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Cancel(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDNSRequest : public nsIDNSRequest
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDNSREQUEST

  nsDNSRequest();
  virtual ~nsDNSRequest();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDNSRequest, nsIDNSRequest)

nsDNSRequest::nsDNSRequest()
{
  /* member initializers and constructor code */
}

nsDNSRequest::~nsDNSRequest()
{
  /* destructor code */
}

/* void cancel (); */
NS_IMETHODIMP nsDNSRequest::Cancel()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDNSRequest_h__ */
