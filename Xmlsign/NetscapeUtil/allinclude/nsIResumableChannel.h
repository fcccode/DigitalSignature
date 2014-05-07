/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIResumableChannel.idl
 */

#ifndef __gen_nsIResumableChannel_h__
#define __gen_nsIResumableChannel_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIStreamListener; /* forward declaration */

class nsIResumableEntityID; /* forward declaration */


/* starting interface:    nsIResumableChannel */
#define NS_IRESUMABLECHANNEL_IID_STR "87cccd68-1dd2-11b2-8b66-cbf10a1b6438"

#define NS_IRESUMABLECHANNEL_IID \
  {0x87cccd68, 0x1dd2, 0x11b2, \
    { 0x8b, 0x66, 0xcb, 0xf1, 0x0a, 0x1b, 0x64, 0x38 }}

class NS_NO_VTABLE nsIResumableChannel : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IRESUMABLECHANNEL_IID)

  /**
     * Open this channel, and read starting at the specified offset.
     * @param listener - As for asyncOpen
     * @param ctxt - As for asyncOpen
     * @param startPos - the starting offset, in bytes, to use to download
     * @param info - information about the file, to match before obtaining
     *  the file. Pass null to use anything.
     * OnStartRequest wil have a status of NS_ERROR_NOT_RESUMABLE if the file
     *  cannot be resumed, eg because the server doesn't support this, or the
     *  nsIFileInfo doesn't match. This error may be occur even if startPos
     *  is 0, so that the front end can warn the user.
     *
     * The request given to the nsIStreamListener will be QIable to
     * nsIResumableInfo
     */
  /* void asyncOpenAt (in nsIStreamListener listener, in nsISupports ctxt, in unsigned long startPos, in nsIResumableEntityID entityID); */
  NS_IMETHOD AsyncOpenAt(nsIStreamListener *listener, nsISupports *ctxt, PRUint32 startPos, nsIResumableEntityID *entityID) = 0;

  /**
     * The nsIResumableEntityID for this uri. Available after OnStartRequest
     * If this attribute is null, then this load is not resumable.
     */
  /* readonly attribute nsIResumableEntityID entityID; */
  NS_IMETHOD GetEntityID(nsIResumableEntityID * *aEntityID) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIRESUMABLECHANNEL \
  NS_IMETHOD AsyncOpenAt(nsIStreamListener *listener, nsISupports *ctxt, PRUint32 startPos, nsIResumableEntityID *entityID); \
  NS_IMETHOD GetEntityID(nsIResumableEntityID * *aEntityID); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIRESUMABLECHANNEL(_to) \
  NS_IMETHOD AsyncOpenAt(nsIStreamListener *listener, nsISupports *ctxt, PRUint32 startPos, nsIResumableEntityID *entityID) { return _to AsyncOpenAt(listener, ctxt, startPos, entityID); } \
  NS_IMETHOD GetEntityID(nsIResumableEntityID * *aEntityID) { return _to GetEntityID(aEntityID); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIRESUMABLECHANNEL(_to) \
  NS_IMETHOD AsyncOpenAt(nsIStreamListener *listener, nsISupports *ctxt, PRUint32 startPos, nsIResumableEntityID *entityID) { return !_to ? NS_ERROR_NULL_POINTER : _to->AsyncOpenAt(listener, ctxt, startPos, entityID); } \
  NS_IMETHOD GetEntityID(nsIResumableEntityID * *aEntityID) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetEntityID(aEntityID); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsResumableChannel : public nsIResumableChannel
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIRESUMABLECHANNEL

  nsResumableChannel();
  virtual ~nsResumableChannel();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsResumableChannel, nsIResumableChannel)

nsResumableChannel::nsResumableChannel()
{
  /* member initializers and constructor code */
}

nsResumableChannel::~nsResumableChannel()
{
  /* destructor code */
}

/* void asyncOpenAt (in nsIStreamListener listener, in nsISupports ctxt, in unsigned long startPos, in nsIResumableEntityID entityID); */
NS_IMETHODIMP nsResumableChannel::AsyncOpenAt(nsIStreamListener *listener, nsISupports *ctxt, PRUint32 startPos, nsIResumableEntityID *entityID)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIResumableEntityID entityID; */
NS_IMETHODIMP nsResumableChannel::GetEntityID(nsIResumableEntityID * *aEntityID)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIResumableChannel_h__ */
