/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIWebProgressListener.idl
 */

#ifndef __gen_nsIWebProgressListener_h__
#define __gen_nsIWebProgressListener_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
/**
 * The nsIWebProgressListener interface is implemented by clients wishing to 
 * listen in on the progress associated with the loading of documents.
 *
 * @status UNDER_REVIEW
 */
class nsIWebProgress; /* forward declaration */

class nsIRequest; /* forward declaration */

class nsIURI; /* forward declaration */


/* starting interface:    nsIWebProgressListener */
#define NS_IWEBPROGRESSLISTENER_IID_STR "570f39d1-efd0-11d3-b093-00a024ffc08c"

#define NS_IWEBPROGRESSLISTENER_IID \
  {0x570f39d1, 0xefd0, 0x11d3, \
    { 0xb0, 0x93, 0x00, 0xa0, 0x24, 0xff, 0xc0, 0x8c }}

class NS_NO_VTABLE nsIWebProgressListener : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IWEBPROGRESSLISTENER_IID)

  /**
  * Progress state transition bits.
  * These flags indicate the various states that documents and requests
  * may transition through as they are being loaded.
  */
  enum { STATE_START = 1U };

  enum { STATE_REDIRECTING = 2U };

  enum { STATE_TRANSFERRING = 4U };

  enum { STATE_NEGOTIATING = 8U };

  enum { STATE_STOP = 16U };

  /**
  * Progress State type bits.
  * These flags indicate whether the transition is occuring on a document
  * or an individual request within the document.
  */
  enum { STATE_IS_REQUEST = 65536U };

  enum { STATE_IS_DOCUMENT = 131072U };

  enum { STATE_IS_NETWORK = 262144U };

  enum { STATE_IS_WINDOW = 524288U };

  /**
  * Security state bits
  */
  enum { STATE_IS_INSECURE = 4U };

  enum { STATE_IS_BROKEN = 1U };

  enum { STATE_IS_SECURE = 2U };

  enum { STATE_SECURE_HIGH = 262144U };

  enum { STATE_SECURE_MED = 65536U };

  enum { STATE_SECURE_LOW = 131072U };

  /**
  * Notification indicating the state has changed for one of the requests
  * associated with the document loaded.
  *
  * @param aWebProgress    The nsIWebProgress instance that fired the
  *                        notification
  *
  * @param aRequest        The nsIRequest which has changed state.
  *
  * @param aStateFlags     Flags indicating the state change.
  *
  * @param aStatus         Error status code associated with the state change.
  * This parameter should be ignored unless the status flag includes the
  * STATE_STOP bit. The status code will indicate success / failure of the
  * request associated with the state change.
  *
  * @return                NS_OK should always be returned.
  */
  /* void onStateChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in unsigned long aStateFlags, in nsresult aStatus); */
  NS_IMETHOD OnStateChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 aStateFlags, nsresult aStatus) = 0;

  /**
  * Notification that the progress has changed for one of the requests being
  * monitored.
  *
  * @param aWebProgress        The nsIWebProgress instance that fired the
  *                            notification
  *
  * @param aRequest            The nsIRequest that has new progress.
  *
  * @param aCurSelfProgress    The current progress for aRequest.
  *
  * @param aMaxSelfProgress    The maximum progress for aRequest.  If this
  *                            value is not known then -1 is passed.
  *
  * @param aCurTotalProgress   The current progress for all the requests
  *                            being monitored.
  *
  * @param aMaxTotalProgress   The total progress for all the requests being
  *                            monitored.  If this value is not known then
  *                            -1 is passed.
  *
  * @return                    NS_OK should always be returned.
  */
  /* void onProgressChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in long aCurSelfProgress, in long aMaxSelfProgress, in long aCurTotalProgress, in long aMaxTotalProgress); */
  NS_IMETHOD OnProgressChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRInt32 aCurSelfProgress, PRInt32 aMaxSelfProgress, PRInt32 aCurTotalProgress, PRInt32 aMaxTotalProgress) = 0;

  /**
  * Called when the window being watched changes the location that is currently.
  * This is not when a load is requested, but rather once it is verified that 
  * the load is going to occur in the given window.  For instance, a load that
  * starts in a window might send progress and status messages, for the new site
  * but it will not send the onLocationChange until we are sure we are loading
  * this new page here.
  *
  * @param location   The URI of the location that is being loaded.
  *
  * @return           NS_OK should always be returned.
  */
  /* void onLocationChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in nsIURI location); */
  NS_IMETHOD OnLocationChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsIURI *location) = 0;

  /**
  * Notification that the status has changed. The status message is usually
  * printed in the status bar of the browser.
  *
  * @return           NS_OK should always be returned.
  */
  /* void onStatusChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in nsresult aStatus, in wstring aMessage); */
  NS_IMETHOD OnStatusChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage) = 0;

  /**
  * Notification called for security progress.  
  * This method will be called on security transitions (eg HTTP -> HTTPS, 
  * HTTPS -> HTTP, FOO -> https) and after document load completion.  
  * It might also be called if an error occurs during network loading.
  *
  * These notification will only occur if a security package is installed.
  *
  * @return           NS_OK should always be returned.
  */
  /* void onSecurityChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in unsigned long state); */
  NS_IMETHOD OnSecurityChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 state) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIWEBPROGRESSLISTENER \
  NS_IMETHOD OnStateChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 aStateFlags, nsresult aStatus); \
  NS_IMETHOD OnProgressChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRInt32 aCurSelfProgress, PRInt32 aMaxSelfProgress, PRInt32 aCurTotalProgress, PRInt32 aMaxTotalProgress); \
  NS_IMETHOD OnLocationChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsIURI *location); \
  NS_IMETHOD OnStatusChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage); \
  NS_IMETHOD OnSecurityChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 state); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIWEBPROGRESSLISTENER(_to) \
  NS_IMETHOD OnStateChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 aStateFlags, nsresult aStatus) { return _to OnStateChange(aWebProgress, aRequest, aStateFlags, aStatus); } \
  NS_IMETHOD OnProgressChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRInt32 aCurSelfProgress, PRInt32 aMaxSelfProgress, PRInt32 aCurTotalProgress, PRInt32 aMaxTotalProgress) { return _to OnProgressChange(aWebProgress, aRequest, aCurSelfProgress, aMaxSelfProgress, aCurTotalProgress, aMaxTotalProgress); } \
  NS_IMETHOD OnLocationChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsIURI *location) { return _to OnLocationChange(aWebProgress, aRequest, location); } \
  NS_IMETHOD OnStatusChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage) { return _to OnStatusChange(aWebProgress, aRequest, aStatus, aMessage); } \
  NS_IMETHOD OnSecurityChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 state) { return _to OnSecurityChange(aWebProgress, aRequest, state); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIWEBPROGRESSLISTENER(_to) \
  NS_IMETHOD OnStateChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 aStateFlags, nsresult aStatus) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnStateChange(aWebProgress, aRequest, aStateFlags, aStatus); } \
  NS_IMETHOD OnProgressChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRInt32 aCurSelfProgress, PRInt32 aMaxSelfProgress, PRInt32 aCurTotalProgress, PRInt32 aMaxTotalProgress) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnProgressChange(aWebProgress, aRequest, aCurSelfProgress, aMaxSelfProgress, aCurTotalProgress, aMaxTotalProgress); } \
  NS_IMETHOD OnLocationChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsIURI *location) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnLocationChange(aWebProgress, aRequest, location); } \
  NS_IMETHOD OnStatusChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnStatusChange(aWebProgress, aRequest, aStatus, aMessage); } \
  NS_IMETHOD OnSecurityChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 state) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnSecurityChange(aWebProgress, aRequest, state); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsWebProgressListener : public nsIWebProgressListener
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIWEBPROGRESSLISTENER

  nsWebProgressListener();
  virtual ~nsWebProgressListener();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsWebProgressListener, nsIWebProgressListener)

nsWebProgressListener::nsWebProgressListener()
{
  /* member initializers and constructor code */
}

nsWebProgressListener::~nsWebProgressListener()
{
  /* destructor code */
}

/* void onStateChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in unsigned long aStateFlags, in nsresult aStatus); */
NS_IMETHODIMP nsWebProgressListener::OnStateChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 aStateFlags, nsresult aStatus)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onProgressChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in long aCurSelfProgress, in long aMaxSelfProgress, in long aCurTotalProgress, in long aMaxTotalProgress); */
NS_IMETHODIMP nsWebProgressListener::OnProgressChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRInt32 aCurSelfProgress, PRInt32 aMaxSelfProgress, PRInt32 aCurTotalProgress, PRInt32 aMaxTotalProgress)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onLocationChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in nsIURI location); */
NS_IMETHODIMP nsWebProgressListener::OnLocationChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsIURI *location)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onStatusChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in nsresult aStatus, in wstring aMessage); */
NS_IMETHODIMP nsWebProgressListener::OnStatusChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onSecurityChange (in nsIWebProgress aWebProgress, in nsIRequest aRequest, in unsigned long state); */
NS_IMETHODIMP nsWebProgressListener::OnSecurityChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 state)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIWebProgressListener_h__ */
