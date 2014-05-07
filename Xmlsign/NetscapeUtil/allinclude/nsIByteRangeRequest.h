/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIByteRangeRequest.idl
 */

#ifndef __gen_nsIByteRangeRequest_h__
#define __gen_nsIByteRangeRequest_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIByteRangeRequest */
#define NS_IBYTERANGEREQUEST_IID_STR "39befdb9-fa76-469b-85dc-a617b81f26eb"

#define NS_IBYTERANGEREQUEST_IID \
  {0x39befdb9, 0xfa76, 0x469b, \
    { 0x85, 0xdc, 0xa6, 0x17, 0xb8, 0x1f, 0x26, 0xeb }}

class NS_NO_VTABLE nsIByteRangeRequest : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IBYTERANGEREQUEST_IID)

  /** 
     * Returns true IFF this request is a byte range request, otherwise it
     * returns false (This is effectively the same as checking to see if 
     * |startRequest| is zero and |endRange| is the content length.)
     */
  /* readonly attribute boolean isByteRangeRequest; */
  NS_IMETHOD GetIsByteRangeRequest(PRBool *aIsByteRangeRequest) = 0;

  /** 
     * Absolute start position in remote file for this request.
     */
  /* readonly attribute long startRange; */
  NS_IMETHOD GetStartRange(PRInt32 *aStartRange) = 0;

  /**
     * Absolute end postion in remote file for this request
     */
  /* readonly attribute long endRange; */
  NS_IMETHOD GetEndRange(PRInt32 *aEndRange) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIBYTERANGEREQUEST \
  NS_IMETHOD GetIsByteRangeRequest(PRBool *aIsByteRangeRequest); \
  NS_IMETHOD GetStartRange(PRInt32 *aStartRange); \
  NS_IMETHOD GetEndRange(PRInt32 *aEndRange); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIBYTERANGEREQUEST(_to) \
  NS_IMETHOD GetIsByteRangeRequest(PRBool *aIsByteRangeRequest) { return _to GetIsByteRangeRequest(aIsByteRangeRequest); } \
  NS_IMETHOD GetStartRange(PRInt32 *aStartRange) { return _to GetStartRange(aStartRange); } \
  NS_IMETHOD GetEndRange(PRInt32 *aEndRange) { return _to GetEndRange(aEndRange); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIBYTERANGEREQUEST(_to) \
  NS_IMETHOD GetIsByteRangeRequest(PRBool *aIsByteRangeRequest) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIsByteRangeRequest(aIsByteRangeRequest); } \
  NS_IMETHOD GetStartRange(PRInt32 *aStartRange) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetStartRange(aStartRange); } \
  NS_IMETHOD GetEndRange(PRInt32 *aEndRange) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetEndRange(aEndRange); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsByteRangeRequest : public nsIByteRangeRequest
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIBYTERANGEREQUEST

  nsByteRangeRequest();
  virtual ~nsByteRangeRequest();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsByteRangeRequest, nsIByteRangeRequest)

nsByteRangeRequest::nsByteRangeRequest()
{
  /* member initializers and constructor code */
}

nsByteRangeRequest::~nsByteRangeRequest()
{
  /* destructor code */
}

/* readonly attribute boolean isByteRangeRequest; */
NS_IMETHODIMP nsByteRangeRequest::GetIsByteRangeRequest(PRBool *aIsByteRangeRequest)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long startRange; */
NS_IMETHODIMP nsByteRangeRequest::GetStartRange(PRInt32 *aStartRange)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long endRange; */
NS_IMETHODIMP nsByteRangeRequest::GetEndRange(PRInt32 *aEndRange)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIByteRangeRequest_h__ */
