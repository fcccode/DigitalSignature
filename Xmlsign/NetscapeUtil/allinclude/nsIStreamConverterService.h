/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIStreamConverterService.idl
 */

#ifndef __gen_nsIStreamConverterService_h__
#define __gen_nsIStreamConverterService_h__


#ifndef __gen_nsIInputStream_h__
#include "nsIInputStream.h"
#endif

#ifndef __gen_nsIStreamListener_h__
#include "nsIStreamListener.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#define NS_STREAMCONVERTERSERVICE_CID                \
{ /* 892FFEB0-3F80-11d3-A16C-0050041CAF44 */         \
    0x892ffeb0,                                      \
    0x3f80,                                          \
    0x11d3,                                          \
    {0xa1, 0x6c, 0x00, 0x50, 0x04, 0x1c, 0xaf, 0x44} \
}
#define NS_ISTREAMCONVERTER_KEY         "@mozilla.org/streamconv;1"

/* starting interface:    nsIStreamConverterService */
#define NS_ISTREAMCONVERTERSERVICE_IID_STR "00362090-3b97-11d3-a16c-0050041caf44"

#define NS_ISTREAMCONVERTERSERVICE_IID \
  {0x00362090, 0x3b97, 0x11d3, \
    { 0xa1, 0x6c, 0x00, 0x50, 0x04, 0x1c, 0xaf, 0x44 }}

/**
 * The nsIStreamConverterService is a higher level stream converter factory
 * responsible for locating and creating stream converters (nsIStreamConverter).
 *
 * This service retrieves an interface that can convert data from a particular MIME
 * type, to a particular MIME type. It is responsible for any intermediary
 * conversion required in order to get from X to Z, assuming direct conversion is not
 * possible.
 *
 * @author Jud Valeski
 * @see nsIStreamConverter
 */
class NS_NO_VTABLE nsIStreamConverterService : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ISTREAMCONVERTERSERVICE_IID)

  /**
     * <b>SYNCRONOUS VERSION</b>
     * Converts a stream of one type, to a stream of another type.
     *
     * Use this method when you have a stream you want to convert.
     *
     * @param aFromStream   The stream representing the original/raw data.
     * @param aFromType     The MIME type of aFromStream.
     * @param aToType       The MIME type of the returned stream.
     * @param aContext      Either an opaque context, or a converter specific context
     *                      (implementation specific).
     * @return              The converted stream. NOTE: The returned stream may not
     *                      already be converted. An efficient stream converter
     *                      implementation will converter data on demand rather than
     *                      buffering the converted data until it is used.
     */
  /* nsIInputStream Convert (in nsIInputStream aFromStream, in wstring aFromType, in wstring aToType, in nsISupports aContext); */
  NS_IMETHOD Convert(nsIInputStream *aFromStream, const PRUnichar *aFromType, const PRUnichar *aToType, nsISupports *aContext, nsIInputStream **_retval) = 0;

  /**
     * <b>ASYNCRONOUS VERSION</b>
     * Retrieves a nsIStreamListener that receives the original/raw data via its
     * nsIStreamListener::OnDataAvailable() callback, then converts and pushes 
     * the data to aListener.
     *
     * Use this method when you want to proxy (and convert) nsIStreamListener callbacks
     * asynchronously.
     *
     * @param aFromType     The MIME type of the original/raw data.
     * @param aToType       The MIME type of the converted data.
     * @param aListener     The listener who receives the converted data.
     * @param aCtxt         Either an opaque context, or a converter specific context
     *                      (implementation specific).
     * @return              A nsIStreamListener that receives data via its OnDataAvailable() method.
     */
  /* nsIStreamListener AsyncConvertData (in wstring aFromType, in wstring aToType, in nsIStreamListener aListener, in nsISupports aContext); */
  NS_IMETHOD AsyncConvertData(const PRUnichar *aFromType, const PRUnichar *aToType, nsIStreamListener *aListener, nsISupports *aContext, nsIStreamListener **_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISTREAMCONVERTERSERVICE \
  NS_IMETHOD Convert(nsIInputStream *aFromStream, const PRUnichar *aFromType, const PRUnichar *aToType, nsISupports *aContext, nsIInputStream **_retval); \
  NS_IMETHOD AsyncConvertData(const PRUnichar *aFromType, const PRUnichar *aToType, nsIStreamListener *aListener, nsISupports *aContext, nsIStreamListener **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISTREAMCONVERTERSERVICE(_to) \
  NS_IMETHOD Convert(nsIInputStream *aFromStream, const PRUnichar *aFromType, const PRUnichar *aToType, nsISupports *aContext, nsIInputStream **_retval) { return _to Convert(aFromStream, aFromType, aToType, aContext, _retval); } \
  NS_IMETHOD AsyncConvertData(const PRUnichar *aFromType, const PRUnichar *aToType, nsIStreamListener *aListener, nsISupports *aContext, nsIStreamListener **_retval) { return _to AsyncConvertData(aFromType, aToType, aListener, aContext, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISTREAMCONVERTERSERVICE(_to) \
  NS_IMETHOD Convert(nsIInputStream *aFromStream, const PRUnichar *aFromType, const PRUnichar *aToType, nsISupports *aContext, nsIInputStream **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Convert(aFromStream, aFromType, aToType, aContext, _retval); } \
  NS_IMETHOD AsyncConvertData(const PRUnichar *aFromType, const PRUnichar *aToType, nsIStreamListener *aListener, nsISupports *aContext, nsIStreamListener **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->AsyncConvertData(aFromType, aToType, aListener, aContext, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsStreamConverterService : public nsIStreamConverterService
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISTREAMCONVERTERSERVICE

  nsStreamConverterService();
  virtual ~nsStreamConverterService();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsStreamConverterService, nsIStreamConverterService)

nsStreamConverterService::nsStreamConverterService()
{
  /* member initializers and constructor code */
}

nsStreamConverterService::~nsStreamConverterService()
{
  /* destructor code */
}

/* nsIInputStream Convert (in nsIInputStream aFromStream, in wstring aFromType, in wstring aToType, in nsISupports aContext); */
NS_IMETHODIMP nsStreamConverterService::Convert(nsIInputStream *aFromStream, const PRUnichar *aFromType, const PRUnichar *aToType, nsISupports *aContext, nsIInputStream **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIStreamListener AsyncConvertData (in wstring aFromType, in wstring aToType, in nsIStreamListener aListener, in nsISupports aContext); */
NS_IMETHODIMP nsStreamConverterService::AsyncConvertData(const PRUnichar *aFromType, const PRUnichar *aToType, nsIStreamListener *aListener, nsISupports *aContext, nsIStreamListener **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIStreamConverterService_h__ */
