/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIDocumentLoader.idl
 */

#ifndef __gen_nsIDocumentLoader_h__
#define __gen_nsIDocumentLoader_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsILoadGroup; /* forward declaration */

class nsIContentViewerContainer; /* forward declaration */

class nsIChannel; /* forward declaration */

class nsIURI; /* forward declaration */

class nsIWebProgress; /* forward declaration */

class nsIRequest; /* forward declaration */


/* starting interface:    nsIDocumentLoader */
#define NS_IDOCUMENTLOADER_IID_STR "f43ba260-0737-11d2-beb9-00805f8a66dc"

#define NS_IDOCUMENTLOADER_IID \
  {0xf43ba260, 0x0737, 0x11d2, \
    { 0xbe, 0xb9, 0x00, 0x80, 0x5f, 0x8a, 0x66, 0xdc }}

class NS_NO_VTABLE nsIDocumentLoader : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDOCUMENTLOADER_IID)

  /* void stop (); */
  NS_IMETHOD Stop(void) = 0;

  /* boolean isBusy (); */
  NS_IMETHOD IsBusy(PRBool *_retval) = 0;

  /* void createDocumentLoader (out nsIDocumentLoader anInstance); */
  NS_IMETHOD CreateDocumentLoader(nsIDocumentLoader **anInstance) = 0;

  /* attribute nsISupports container; */
  NS_IMETHOD GetContainer(nsISupports * *aContainer) = 0;
  NS_IMETHOD SetContainer(nsISupports * aContainer) = 0;

  /* [noscript] void getContentViewerContainer (in nsISupports aDocumentID, out nsIContentViewerContainer aResult); */
  NS_IMETHOD GetContentViewerContainer(nsISupports *aDocumentID, nsIContentViewerContainer **aResult) = 0;

  /* nsILoadGroup getLoadGroup (); */
  NS_IMETHOD GetLoadGroup(nsILoadGroup **_retval) = 0;

  /* void destroy (); */
  NS_IMETHOD Destroy(void) = 0;

  /* void clearParentDocLoader (); */
  NS_IMETHOD ClearParentDocLoader(void) = 0;

  /* readonly attribute nsIChannel documentChannel; */
  NS_IMETHOD GetDocumentChannel(nsIChannel * *aDocumentChannel) = 0;

  /* void fireOnLocationChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in nsIURI aUri); */
  NS_IMETHOD FireOnLocationChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsIURI *aUri) = 0;

  /* void fireOnStatusChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in nsresult aStatus, in wstring aMessage); */
  NS_IMETHOD FireOnStatusChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOCUMENTLOADER \
  NS_IMETHOD Stop(void); \
  NS_IMETHOD IsBusy(PRBool *_retval); \
  NS_IMETHOD CreateDocumentLoader(nsIDocumentLoader **anInstance); \
  NS_IMETHOD GetContainer(nsISupports * *aContainer); \
  NS_IMETHOD SetContainer(nsISupports * aContainer); \
  NS_IMETHOD GetContentViewerContainer(nsISupports *aDocumentID, nsIContentViewerContainer **aResult); \
  NS_IMETHOD GetLoadGroup(nsILoadGroup **_retval); \
  NS_IMETHOD Destroy(void); \
  NS_IMETHOD ClearParentDocLoader(void); \
  NS_IMETHOD GetDocumentChannel(nsIChannel * *aDocumentChannel); \
  NS_IMETHOD FireOnLocationChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsIURI *aUri); \
  NS_IMETHOD FireOnStatusChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOCUMENTLOADER(_to) \
  NS_IMETHOD Stop(void) { return _to Stop(); } \
  NS_IMETHOD IsBusy(PRBool *_retval) { return _to IsBusy(_retval); } \
  NS_IMETHOD CreateDocumentLoader(nsIDocumentLoader **anInstance) { return _to CreateDocumentLoader(anInstance); } \
  NS_IMETHOD GetContainer(nsISupports * *aContainer) { return _to GetContainer(aContainer); } \
  NS_IMETHOD SetContainer(nsISupports * aContainer) { return _to SetContainer(aContainer); } \
  NS_IMETHOD GetContentViewerContainer(nsISupports *aDocumentID, nsIContentViewerContainer **aResult) { return _to GetContentViewerContainer(aDocumentID, aResult); } \
  NS_IMETHOD GetLoadGroup(nsILoadGroup **_retval) { return _to GetLoadGroup(_retval); } \
  NS_IMETHOD Destroy(void) { return _to Destroy(); } \
  NS_IMETHOD ClearParentDocLoader(void) { return _to ClearParentDocLoader(); } \
  NS_IMETHOD GetDocumentChannel(nsIChannel * *aDocumentChannel) { return _to GetDocumentChannel(aDocumentChannel); } \
  NS_IMETHOD FireOnLocationChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsIURI *aUri) { return _to FireOnLocationChange(aWebProgress, aRequest, aUri); } \
  NS_IMETHOD FireOnStatusChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage) { return _to FireOnStatusChange(aWebProgress, aRequest, aStatus, aMessage); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOCUMENTLOADER(_to) \
  NS_IMETHOD Stop(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Stop(); } \
  NS_IMETHOD IsBusy(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsBusy(_retval); } \
  NS_IMETHOD CreateDocumentLoader(nsIDocumentLoader **anInstance) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateDocumentLoader(anInstance); } \
  NS_IMETHOD GetContainer(nsISupports * *aContainer) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetContainer(aContainer); } \
  NS_IMETHOD SetContainer(nsISupports * aContainer) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetContainer(aContainer); } \
  NS_IMETHOD GetContentViewerContainer(nsISupports *aDocumentID, nsIContentViewerContainer **aResult) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetContentViewerContainer(aDocumentID, aResult); } \
  NS_IMETHOD GetLoadGroup(nsILoadGroup **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLoadGroup(_retval); } \
  NS_IMETHOD Destroy(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Destroy(); } \
  NS_IMETHOD ClearParentDocLoader(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ClearParentDocLoader(); } \
  NS_IMETHOD GetDocumentChannel(nsIChannel * *aDocumentChannel) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDocumentChannel(aDocumentChannel); } \
  NS_IMETHOD FireOnLocationChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsIURI *aUri) { return !_to ? NS_ERROR_NULL_POINTER : _to->FireOnLocationChange(aWebProgress, aRequest, aUri); } \
  NS_IMETHOD FireOnStatusChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage) { return !_to ? NS_ERROR_NULL_POINTER : _to->FireOnStatusChange(aWebProgress, aRequest, aStatus, aMessage); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDocumentLoader : public nsIDocumentLoader
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOCUMENTLOADER

  nsDocumentLoader();
  virtual ~nsDocumentLoader();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDocumentLoader, nsIDocumentLoader)

nsDocumentLoader::nsDocumentLoader()
{
  /* member initializers and constructor code */
}

nsDocumentLoader::~nsDocumentLoader()
{
  /* destructor code */
}

/* void stop (); */
NS_IMETHODIMP nsDocumentLoader::Stop()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isBusy (); */
NS_IMETHODIMP nsDocumentLoader::IsBusy(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void createDocumentLoader (out nsIDocumentLoader anInstance); */
NS_IMETHODIMP nsDocumentLoader::CreateDocumentLoader(nsIDocumentLoader **anInstance)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsISupports container; */
NS_IMETHODIMP nsDocumentLoader::GetContainer(nsISupports * *aContainer)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDocumentLoader::SetContainer(nsISupports * aContainer)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void getContentViewerContainer (in nsISupports aDocumentID, out nsIContentViewerContainer aResult); */
NS_IMETHODIMP nsDocumentLoader::GetContentViewerContainer(nsISupports *aDocumentID, nsIContentViewerContainer **aResult)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsILoadGroup getLoadGroup (); */
NS_IMETHODIMP nsDocumentLoader::GetLoadGroup(nsILoadGroup **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void destroy (); */
NS_IMETHODIMP nsDocumentLoader::Destroy()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void clearParentDocLoader (); */
NS_IMETHODIMP nsDocumentLoader::ClearParentDocLoader()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIChannel documentChannel; */
NS_IMETHODIMP nsDocumentLoader::GetDocumentChannel(nsIChannel * *aDocumentChannel)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void fireOnLocationChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in nsIURI aUri); */
NS_IMETHODIMP nsDocumentLoader::FireOnLocationChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsIURI *aUri)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void fireOnStatusChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in nsresult aStatus, in wstring aMessage); */
NS_IMETHODIMP nsDocumentLoader::FireOnStatusChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDocumentLoader_h__ */
