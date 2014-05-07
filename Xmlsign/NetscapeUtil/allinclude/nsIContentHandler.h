/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIContentHandler.idl
 */

#ifndef __gen_nsIContentHandler_h__
#define __gen_nsIContentHandler_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIRequest; /* forward declaration */


/* starting interface:    nsIContentHandler */
#define NS_ICONTENTHANDLER_IID_STR "2f0f927a-8677-11d3-989d-001083010e9b"

#define NS_ICONTENTHANDLER_IID \
  {0x2f0f927a, 0x8677, 0x11d3, \
    { 0x98, 0x9d, 0x00, 0x10, 0x83, 0x01, 0x0e, 0x9b }}

class NS_NO_VTABLE nsIContentHandler : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ICONTENTHANDLER_IID)

  /* void handleContent (in string aContentType, in string aCommand, in nsISupports aWindowContext, in nsIRequest aRequest); */
  NS_IMETHOD HandleContent(const char *aContentType, const char *aCommand, nsISupports *aWindowContext, nsIRequest *aRequest) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICONTENTHANDLER \
  NS_IMETHOD HandleContent(const char *aContentType, const char *aCommand, nsISupports *aWindowContext, nsIRequest *aRequest); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICONTENTHANDLER(_to) \
  NS_IMETHOD HandleContent(const char *aContentType, const char *aCommand, nsISupports *aWindowContext, nsIRequest *aRequest) { return _to HandleContent(aContentType, aCommand, aWindowContext, aRequest); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICONTENTHANDLER(_to) \
  NS_IMETHOD HandleContent(const char *aContentType, const char *aCommand, nsISupports *aWindowContext, nsIRequest *aRequest) { return !_to ? NS_ERROR_NULL_POINTER : _to->HandleContent(aContentType, aCommand, aWindowContext, aRequest); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsContentHandler : public nsIContentHandler
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICONTENTHANDLER

  nsContentHandler();
  virtual ~nsContentHandler();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsContentHandler, nsIContentHandler)

nsContentHandler::nsContentHandler()
{
  /* member initializers and constructor code */
}

nsContentHandler::~nsContentHandler()
{
  /* destructor code */
}

/* void handleContent (in string aContentType, in string aCommand, in nsISupports aWindowContext, in nsIRequest aRequest); */
NS_IMETHODIMP nsContentHandler::HandleContent(const char *aContentType, const char *aCommand, nsISupports *aWindowContext, nsIRequest *aRequest)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

#define NS_ERROR_WONT_HANDLE_CONTENT   NS_ERROR_GENERATE_FAILURE(NS_ERROR_MODULE_URILOADER, 1)

#endif /* __gen_nsIContentHandler_h__ */
