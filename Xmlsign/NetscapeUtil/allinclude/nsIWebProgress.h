/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIWebProgress.idl
 */

#ifndef __gen_nsIWebProgress_h__
#define __gen_nsIWebProgress_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMWindow; /* forward declaration */

class nsIWebProgressListener; /* forward declaration */


/* starting interface:    nsIWebProgress */
#define NS_IWEBPROGRESS_IID_STR "570f39d0-efd0-11d3-b093-00a024ffc08c"

#define NS_IWEBPROGRESS_IID \
  {0x570f39d0, 0xefd0, 0x11d3, \
    { 0xb0, 0x93, 0x00, 0xa0, 0x24, 0xff, 0xc0, 0x8c }}

/**
 * The nsIWebProgress interface is used to look at the progress of document
 * loading in a particular DOM Window.
 *
 * @status UNDER_REVIEW
 */
class NS_NO_VTABLE nsIWebProgress : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IWEBPROGRESS_IID)

  enum { NOTIFY_STATE_REQUEST = 1U };

  enum { NOTIFY_STATE_DOCUMENT = 2U };

  enum { NOTIFY_STATE_NETWORK = 4U };

  enum { NOTIFY_STATE_WINDOW = 8U };

  enum { NOTIFY_STATE_ALL = 15U };

  enum { NOTIFY_PROGRESS = 16U };

  enum { NOTIFY_STATUS = 32U };

  enum { NOTIFY_SECURITY = 64U };

  enum { NOTIFY_LOCATION = 128U };

  enum { NOTIFY_ALL = 255U };

  /**
   * Registers a listener to be notified of Progress Events
   *
   * @param listener - The listener interface to be called when a progress
   *                   event occurs.
   *
   * @param aNotifyMask - The types of notifications to receive.
   *
   * @return  NS_OK - Listener was registered successfully.
   *          NS_INVALID_ARG - The listener passed in was either nsnull, 
   *                            or was already registered with this progress
   *                            interface.
   */
  /* void addProgressListener (in nsIWebProgressListener listener, in unsigned long aNotifyMask); */
  NS_IMETHOD AddProgressListener(nsIWebProgressListener *listener, PRUint32 aNotifyMask) = 0;

  /**
   * Removes a previously registered listener of Progress Events
   *
   * @param listener - The listener interface previously registered with 
   *                   AddListener().
   *
   * @return  NS_OK - Listener was successfully unregistered.
   *          NS_ERROR_INVALID_ARG - The listener was not previously
   *                                 registered listener.
   */
  /* void removeProgressListener (in nsIWebProgressListener listener); */
  NS_IMETHOD RemoveProgressListener(nsIWebProgressListener *listener) = 0;

  /**
   * The DOM Window associated with the WebProgress instance.
   */
  /* readonly attribute nsIDOMWindow DOMWindow; */
  NS_IMETHOD GetDOMWindow(nsIDOMWindow * *aDOMWindow) = 0;

  /**
   * The IsLoadingDocument associated with the WebProgress instance
   */
  /* readonly attribute PRBool isLoadingDocument; */
  NS_IMETHOD GetIsLoadingDocument(PRBool *aIsLoadingDocument) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIWEBPROGRESS \
  NS_IMETHOD AddProgressListener(nsIWebProgressListener *listener, PRUint32 aNotifyMask); \
  NS_IMETHOD RemoveProgressListener(nsIWebProgressListener *listener); \
  NS_IMETHOD GetDOMWindow(nsIDOMWindow * *aDOMWindow); \
  NS_IMETHOD GetIsLoadingDocument(PRBool *aIsLoadingDocument); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIWEBPROGRESS(_to) \
  NS_IMETHOD AddProgressListener(nsIWebProgressListener *listener, PRUint32 aNotifyMask) { return _to AddProgressListener(listener, aNotifyMask); } \
  NS_IMETHOD RemoveProgressListener(nsIWebProgressListener *listener) { return _to RemoveProgressListener(listener); } \
  NS_IMETHOD GetDOMWindow(nsIDOMWindow * *aDOMWindow) { return _to GetDOMWindow(aDOMWindow); } \
  NS_IMETHOD GetIsLoadingDocument(PRBool *aIsLoadingDocument) { return _to GetIsLoadingDocument(aIsLoadingDocument); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIWEBPROGRESS(_to) \
  NS_IMETHOD AddProgressListener(nsIWebProgressListener *listener, PRUint32 aNotifyMask) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddProgressListener(listener, aNotifyMask); } \
  NS_IMETHOD RemoveProgressListener(nsIWebProgressListener *listener) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveProgressListener(listener); } \
  NS_IMETHOD GetDOMWindow(nsIDOMWindow * *aDOMWindow) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDOMWindow(aDOMWindow); } \
  NS_IMETHOD GetIsLoadingDocument(PRBool *aIsLoadingDocument) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIsLoadingDocument(aIsLoadingDocument); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsWebProgress : public nsIWebProgress
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIWEBPROGRESS

  nsWebProgress();
  virtual ~nsWebProgress();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsWebProgress, nsIWebProgress)

nsWebProgress::nsWebProgress()
{
  /* member initializers and constructor code */
}

nsWebProgress::~nsWebProgress()
{
  /* destructor code */
}

/* void addProgressListener (in nsIWebProgressListener listener, in unsigned long aNotifyMask); */
NS_IMETHODIMP nsWebProgress::AddProgressListener(nsIWebProgressListener *listener, PRUint32 aNotifyMask)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeProgressListener (in nsIWebProgressListener listener); */
NS_IMETHODIMP nsWebProgress::RemoveProgressListener(nsIWebProgressListener *listener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIDOMWindow DOMWindow; */
NS_IMETHODIMP nsWebProgress::GetDOMWindow(nsIDOMWindow * *aDOMWindow)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRBool isLoadingDocument; */
NS_IMETHODIMP nsWebProgress::GetIsLoadingDocument(PRBool *aIsLoadingDocument)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIWebProgress_h__ */
