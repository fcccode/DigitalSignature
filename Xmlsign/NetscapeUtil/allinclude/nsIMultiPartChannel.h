/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIMultiPartChannel.idl
 */

#ifndef __gen_nsIMultiPartChannel_h__
#define __gen_nsIMultiPartChannel_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIChannel; /* forward declaration */


/* starting interface:    nsIMultiPartChannel */
#define NS_IMULTIPARTCHANNEL_IID_STR "62d77f66-8ad0-4a7f-91a1-bb048b136490"

#define NS_IMULTIPARTCHANNEL_IID \
  {0x62d77f66, 0x8ad0, 0x4a7f, \
    { 0x91, 0xa1, 0xbb, 0x04, 0x8b, 0x13, 0x64, 0x90 }}

/**
 * An interface to access the the base channel 
 * associated with a MultiPartChannel.
 */
class NS_NO_VTABLE nsIMultiPartChannel : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IMULTIPARTCHANNEL_IID)

  /**
     * readonly attribute to access the underlying channel
     */
  /* readonly attribute nsIChannel baseChannel; */
  NS_IMETHOD GetBaseChannel(nsIChannel * *aBaseChannel) = 0;

  /**
     * Access to the Content-Disposition header field of this part of
     * a multipart message.  This allows getting the preferred
     * handling method, preferred filename, etc.  See RFC 2183.
     */
  /* attribute ACString contentDisposition; */
  NS_IMETHOD GetContentDisposition(nsACString & aContentDisposition) = 0;
  NS_IMETHOD SetContentDisposition(const nsACString & aContentDisposition) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIMULTIPARTCHANNEL \
  NS_IMETHOD GetBaseChannel(nsIChannel * *aBaseChannel); \
  NS_IMETHOD GetContentDisposition(nsACString & aContentDisposition); \
  NS_IMETHOD SetContentDisposition(const nsACString & aContentDisposition); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIMULTIPARTCHANNEL(_to) \
  NS_IMETHOD GetBaseChannel(nsIChannel * *aBaseChannel) { return _to GetBaseChannel(aBaseChannel); } \
  NS_IMETHOD GetContentDisposition(nsACString & aContentDisposition) { return _to GetContentDisposition(aContentDisposition); } \
  NS_IMETHOD SetContentDisposition(const nsACString & aContentDisposition) { return _to SetContentDisposition(aContentDisposition); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIMULTIPARTCHANNEL(_to) \
  NS_IMETHOD GetBaseChannel(nsIChannel * *aBaseChannel) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBaseChannel(aBaseChannel); } \
  NS_IMETHOD GetContentDisposition(nsACString & aContentDisposition) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetContentDisposition(aContentDisposition); } \
  NS_IMETHOD SetContentDisposition(const nsACString & aContentDisposition) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetContentDisposition(aContentDisposition); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsMultiPartChannel : public nsIMultiPartChannel
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIMULTIPARTCHANNEL

  nsMultiPartChannel();
  virtual ~nsMultiPartChannel();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsMultiPartChannel, nsIMultiPartChannel)

nsMultiPartChannel::nsMultiPartChannel()
{
  /* member initializers and constructor code */
}

nsMultiPartChannel::~nsMultiPartChannel()
{
  /* destructor code */
}

/* readonly attribute nsIChannel baseChannel; */
NS_IMETHODIMP nsMultiPartChannel::GetBaseChannel(nsIChannel * *aBaseChannel)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute ACString contentDisposition; */
NS_IMETHODIMP nsMultiPartChannel::GetContentDisposition(nsACString & aContentDisposition)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsMultiPartChannel::SetContentDisposition(const nsACString & aContentDisposition)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIMultiPartChannel_h__ */
