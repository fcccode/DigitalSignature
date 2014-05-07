/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /home/manoj/mozilla/security/manager/ssl/public/nsIKeygenThread.idl
 */

#ifndef __gen_nsIKeygenThread_h__
#define __gen_nsIKeygenThread_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMWindowInternal; /* forward declaration */


/* starting interface:    nsIKeygenThread */
#define NS_IKEYGENTHREAD_IID_STR "195763b8-1dd2-11b2-a843-eb44e44aaa37"

#define NS_IKEYGENTHREAD_IID \
  {0x195763b8, 0x1dd2, 0x11b2, \
    { 0xa8, 0x43, 0xeb, 0x44, 0xe4, 0x4a, 0xaa, 0x37 }}

/**
 * nsIKeygenThread
 *  This is used to communicate with the thread generating a key pair,
 *  to be used by the dialog displaying status information.
 */
class NS_NO_VTABLE nsIKeygenThread : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IKEYGENTHREAD_IID)

  /**
   * startKeyGeneration - run the thread
   *   A user interface implementing this interface needs to
   *   call this method as soon as the status information
   *   is displaying. This will trigger key generation.
   *   To allow the closure of the status information,
   *   the thread needs a handle to the displayed window.
   */
  /* void startKeyGeneration (in nsIDOMWindowInternal statusDialog); */
  NS_IMETHOD StartKeyGeneration(nsIDOMWindowInternal *statusDialog) = 0;

  /**
   * userCanceled - notify the thread
   *   If the user canceled, the thread is no longer allowed to
   *   close the dialog. However, if the thread already closed
   *   it, we are not allowed to close it.
   */
  /* void userCanceled (out boolean threadAlreadyClosedDialog); */
  NS_IMETHOD UserCanceled(PRBool *threadAlreadyClosedDialog) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIKEYGENTHREAD \
  NS_IMETHOD StartKeyGeneration(nsIDOMWindowInternal *statusDialog); \
  NS_IMETHOD UserCanceled(PRBool *threadAlreadyClosedDialog); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIKEYGENTHREAD(_to) \
  NS_IMETHOD StartKeyGeneration(nsIDOMWindowInternal *statusDialog) { return _to StartKeyGeneration(statusDialog); } \
  NS_IMETHOD UserCanceled(PRBool *threadAlreadyClosedDialog) { return _to UserCanceled(threadAlreadyClosedDialog); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIKEYGENTHREAD(_to) \
  NS_IMETHOD StartKeyGeneration(nsIDOMWindowInternal *statusDialog) { return !_to ? NS_ERROR_NULL_POINTER : _to->StartKeyGeneration(statusDialog); } \
  NS_IMETHOD UserCanceled(PRBool *threadAlreadyClosedDialog) { return !_to ? NS_ERROR_NULL_POINTER : _to->UserCanceled(threadAlreadyClosedDialog); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsKeygenThread : public nsIKeygenThread
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIKEYGENTHREAD

  nsKeygenThread();

private:
  ~nsKeygenThread();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsKeygenThread, nsIKeygenThread)

nsKeygenThread::nsKeygenThread()
{
  /* member initializers and constructor code */
}

nsKeygenThread::~nsKeygenThread()
{
  /* destructor code */
}

/* void startKeyGeneration (in nsIDOMWindowInternal statusDialog); */
NS_IMETHODIMP nsKeygenThread::StartKeyGeneration(nsIDOMWindowInternal *statusDialog)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void userCanceled (out boolean threadAlreadyClosedDialog); */
NS_IMETHODIMP nsKeygenThread::UserCanceled(PRBool *threadAlreadyClosedDialog)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

// {195763b8-1dd2-11b2-a843-eb44e44aaa37}
#define NS_KEYGENTHREAD_CID \
{ 0x195763b8, 0x1dd2, 0x11b2, { 0xa8, 0x43, 0xeb, 0x44, 0xe4, 0x4a, 0xaa, 0x37 } }
#define NS_KEYGENTHREAD_CONTRACTID "@mozilla.org/security/keygenthread;1"

#endif /* __gen_nsIKeygenThread_h__ */
