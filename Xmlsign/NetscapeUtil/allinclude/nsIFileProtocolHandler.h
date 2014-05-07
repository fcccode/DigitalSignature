/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIFileProtocolHandler.idl
 */

#ifndef __gen_nsIFileProtocolHandler_h__
#define __gen_nsIFileProtocolHandler_h__


#ifndef __gen_nsIProtocolHandler_h__
#include "nsIProtocolHandler.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIFile; /* forward declaration */


/* starting interface:    nsIFileProtocolHandler */
#define NS_IFILEPROTOCOLHANDLER_IID_STR "987fb083-d7ff-46dc-9ee3-ab6e52501d53"

#define NS_IFILEPROTOCOLHANDLER_IID \
  {0x987fb083, 0xd7ff, 0x46dc, \
    { 0x9e, 0xe3, 0xab, 0x6e, 0x52, 0x50, 0x1d, 0x53 }}

class NS_NO_VTABLE nsIFileProtocolHandler : public nsIProtocolHandler {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IFILEPROTOCOLHANDLER_IID)

  /**
     * This method constructs a new file URI 
     *
     * @param aFile nsIFile
     * @return reference to a new nsIURI object
     */
  /* nsIURI newFileURI (in nsIFile aFile); */
  NS_IMETHOD NewFileURI(nsIFile *aFile, nsIURI **_retval) = 0;

  /**
     * Converts the nsIFile to the corresponding URL string.  NOTE: under
     * some platforms this is a lossy conversion (e.g., Mac Carbon build).
     * If the nsIFile is a local file, then the result will be a file://
     * URL string.
     *
     * The resulting string may contain URL-escaped characters.
     */
  /* AUTF8String getURLSpecFromFile (in nsIFile file); */
  NS_IMETHOD GetURLSpecFromFile(nsIFile *file, nsACString & _retval) = 0;

  /**
     * Converts the URL string into the corresponding nsIFile if possible.
     * A local file will be created if the URL string begins with file://.
     */
  /* nsIFile getFileFromURLSpec (in AUTF8String url); */
  NS_IMETHOD GetFileFromURLSpec(const nsACString & url, nsIFile **_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIFILEPROTOCOLHANDLER \
  NS_IMETHOD NewFileURI(nsIFile *aFile, nsIURI **_retval); \
  NS_IMETHOD GetURLSpecFromFile(nsIFile *file, nsACString & _retval); \
  NS_IMETHOD GetFileFromURLSpec(const nsACString & url, nsIFile **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIFILEPROTOCOLHANDLER(_to) \
  NS_IMETHOD NewFileURI(nsIFile *aFile, nsIURI **_retval) { return _to NewFileURI(aFile, _retval); } \
  NS_IMETHOD GetURLSpecFromFile(nsIFile *file, nsACString & _retval) { return _to GetURLSpecFromFile(file, _retval); } \
  NS_IMETHOD GetFileFromURLSpec(const nsACString & url, nsIFile **_retval) { return _to GetFileFromURLSpec(url, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIFILEPROTOCOLHANDLER(_to) \
  NS_IMETHOD NewFileURI(nsIFile *aFile, nsIURI **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->NewFileURI(aFile, _retval); } \
  NS_IMETHOD GetURLSpecFromFile(nsIFile *file, nsACString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetURLSpecFromFile(file, _retval); } \
  NS_IMETHOD GetFileFromURLSpec(const nsACString & url, nsIFile **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFileFromURLSpec(url, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsFileProtocolHandler : public nsIFileProtocolHandler
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIFILEPROTOCOLHANDLER

  nsFileProtocolHandler();
  virtual ~nsFileProtocolHandler();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsFileProtocolHandler, nsIFileProtocolHandler)

nsFileProtocolHandler::nsFileProtocolHandler()
{
  /* member initializers and constructor code */
}

nsFileProtocolHandler::~nsFileProtocolHandler()
{
  /* destructor code */
}

/* nsIURI newFileURI (in nsIFile aFile); */
NS_IMETHODIMP nsFileProtocolHandler::NewFileURI(nsIFile *aFile, nsIURI **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String getURLSpecFromFile (in nsIFile file); */
NS_IMETHODIMP nsFileProtocolHandler::GetURLSpecFromFile(nsIFile *file, nsACString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIFile getFileFromURLSpec (in AUTF8String url); */
NS_IMETHODIMP nsFileProtocolHandler::GetFileFromURLSpec(const nsACString & url, nsIFile **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIFileProtocolHandler_h__ */
