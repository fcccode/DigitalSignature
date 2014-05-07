/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIDownload.idl
 */

#ifndef __gen_nsIDownload_h__
#define __gen_nsIDownload_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIURI; /* forward declaration */

class nsILocalFile; /* forward declaration */

class nsIObserver; /* forward declaration */

class nsIWebBrowserPersist; /* forward declaration */

class nsIWebProgressListener; /* forward declaration */

class nsIMIMEInfo; /* forward declaration */


/* starting interface:    nsIDownload */
#define NS_IDOWNLOAD_IID_STR "06cb92f2-1dd2-11b2-95f2-96dfdfb804a1"

#define NS_IDOWNLOAD_IID \
  {0x06cb92f2, 0x1dd2, 0x11b2, \
    { 0x95, 0xf2, 0x96, 0xdf, 0xdf, 0xb8, 0x04, 0xa1 }}

class NS_NO_VTABLE nsIDownload : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDOWNLOAD_IID)

  /**
     * Initializes the download with certain properties.  This function must
     * be called prior to accessing any properties on this interface.
     *
     * @param aSource The source (nsIURI) of the download.
     *
     * @param aTarget The local file to which the download is being saved.
     *
     * @param aDisplayName The user-readable description of the download.
     *
     * @param aMIMEInfo The MIME info associated with the download file,
     *                  including MIME type and helper app when appropriate.
     *                  This parameter is optional.
     *
     * @param aPersist The "persist" used to transfer the download.  If set,
     *                 the manager will set its listener to the download item
     *                 and use it for cancellation.  If not set, the client
     *                 is expected to set the download item as the listener on
     *                 whatever transfer component is being used, and to
     *                 set an observer on the download item that listens for
     *                 the "oncancel" topic and cancels the download.
     */
  /* void init (in nsIURI aSource, in nsILocalFile aTarget, in wstring aDisplayName, in nsIMIMEInfo aMIMEInfo, in long long startTime, in nsIWebBrowserPersist aPersist); */
  NS_IMETHOD Init(nsIURI *aSource, nsILocalFile *aTarget, const PRUnichar *aDisplayName, nsIMIMEInfo *aMIMEInfo, PRInt64 startTime, nsIWebBrowserPersist *aPersist) = 0;

  /**
     * The source of the download.
     */
  /* readonly attribute nsIURI source; */
  NS_IMETHOD GetSource(nsIURI * *aSource) = 0;

  /**
     * The local file to which the download is being saved.
     */
  /* readonly attribute nsILocalFile target; */
  NS_IMETHOD GetTarget(nsILocalFile * *aTarget) = 0;

  /**
     * Optional. If set, it will be used for cancellation, and the download
     * will be set as its listener.  If not, |observer| should be set to listen
     * and respond accordingly to topics like oncancel, and the client promises
     * to set the download item as the listener for whatever transfer component
     * being used.
     */
  /* readonly attribute nsIWebBrowserPersist persist; */
  NS_IMETHOD GetPersist(nsIWebBrowserPersist * *aPersist) = 0;

  /**
     * The percentage of completion of the download.
     */
  /* readonly attribute PRInt32 percentComplete; */
  NS_IMETHOD GetPercentComplete(PRInt32 *aPercentComplete) = 0;

  /**
     * The user-readable description of the download.
     */
  /* attribute wstring displayName; */
  NS_IMETHOD GetDisplayName(PRUnichar * *aDisplayName) = 0;
  NS_IMETHOD SetDisplayName(const PRUnichar * aDisplayName) = 0;

  /**
     * The time a download was started.
     */
  /* readonly attribute long long startTime; */
  NS_IMETHOD GetStartTime(PRInt64 *aStartTime) = 0;

  /**
     * Optional. If set, it will contain the download's relevant MIME information.
     * This includes it's MIME Type, helper app, and whether that helper should be
     * executed.
     */
  /* readonly attribute nsIMIMEInfo MIMEInfo; */
  NS_IMETHOD GetMIMEInfo(nsIMIMEInfo * *aMIMEInfo) = 0;

  /**
     * Optional; downloading information is passed to this listener and used to
     * update client UI.
     */
  /* attribute nsIWebProgressListener listener; */
  NS_IMETHOD GetListener(nsIWebProgressListener * *aListener) = 0;
  NS_IMETHOD SetListener(nsIWebProgressListener * aListener) = 0;

  /**
     * If set, receives notifications of events like cancel ("oncancel").
     * Must be set if no persist object is specified (see above).
     */
  /* attribute nsIObserver observer; */
  NS_IMETHOD GetObserver(nsIObserver * *aObserver) = 0;
  NS_IMETHOD SetObserver(nsIObserver * aObserver) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOWNLOAD \
  NS_IMETHOD Init(nsIURI *aSource, nsILocalFile *aTarget, const PRUnichar *aDisplayName, nsIMIMEInfo *aMIMEInfo, PRInt64 startTime, nsIWebBrowserPersist *aPersist); \
  NS_IMETHOD GetSource(nsIURI * *aSource); \
  NS_IMETHOD GetTarget(nsILocalFile * *aTarget); \
  NS_IMETHOD GetPersist(nsIWebBrowserPersist * *aPersist); \
  NS_IMETHOD GetPercentComplete(PRInt32 *aPercentComplete); \
  NS_IMETHOD GetDisplayName(PRUnichar * *aDisplayName); \
  NS_IMETHOD SetDisplayName(const PRUnichar * aDisplayName); \
  NS_IMETHOD GetStartTime(PRInt64 *aStartTime); \
  NS_IMETHOD GetMIMEInfo(nsIMIMEInfo * *aMIMEInfo); \
  NS_IMETHOD GetListener(nsIWebProgressListener * *aListener); \
  NS_IMETHOD SetListener(nsIWebProgressListener * aListener); \
  NS_IMETHOD GetObserver(nsIObserver * *aObserver); \
  NS_IMETHOD SetObserver(nsIObserver * aObserver); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOWNLOAD(_to) \
  NS_IMETHOD Init(nsIURI *aSource, nsILocalFile *aTarget, const PRUnichar *aDisplayName, nsIMIMEInfo *aMIMEInfo, PRInt64 startTime, nsIWebBrowserPersist *aPersist) { return _to Init(aSource, aTarget, aDisplayName, aMIMEInfo, startTime, aPersist); } \
  NS_IMETHOD GetSource(nsIURI * *aSource) { return _to GetSource(aSource); } \
  NS_IMETHOD GetTarget(nsILocalFile * *aTarget) { return _to GetTarget(aTarget); } \
  NS_IMETHOD GetPersist(nsIWebBrowserPersist * *aPersist) { return _to GetPersist(aPersist); } \
  NS_IMETHOD GetPercentComplete(PRInt32 *aPercentComplete) { return _to GetPercentComplete(aPercentComplete); } \
  NS_IMETHOD GetDisplayName(PRUnichar * *aDisplayName) { return _to GetDisplayName(aDisplayName); } \
  NS_IMETHOD SetDisplayName(const PRUnichar * aDisplayName) { return _to SetDisplayName(aDisplayName); } \
  NS_IMETHOD GetStartTime(PRInt64 *aStartTime) { return _to GetStartTime(aStartTime); } \
  NS_IMETHOD GetMIMEInfo(nsIMIMEInfo * *aMIMEInfo) { return _to GetMIMEInfo(aMIMEInfo); } \
  NS_IMETHOD GetListener(nsIWebProgressListener * *aListener) { return _to GetListener(aListener); } \
  NS_IMETHOD SetListener(nsIWebProgressListener * aListener) { return _to SetListener(aListener); } \
  NS_IMETHOD GetObserver(nsIObserver * *aObserver) { return _to GetObserver(aObserver); } \
  NS_IMETHOD SetObserver(nsIObserver * aObserver) { return _to SetObserver(aObserver); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOWNLOAD(_to) \
  NS_IMETHOD Init(nsIURI *aSource, nsILocalFile *aTarget, const PRUnichar *aDisplayName, nsIMIMEInfo *aMIMEInfo, PRInt64 startTime, nsIWebBrowserPersist *aPersist) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(aSource, aTarget, aDisplayName, aMIMEInfo, startTime, aPersist); } \
  NS_IMETHOD GetSource(nsIURI * *aSource) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSource(aSource); } \
  NS_IMETHOD GetTarget(nsILocalFile * *aTarget) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTarget(aTarget); } \
  NS_IMETHOD GetPersist(nsIWebBrowserPersist * *aPersist) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPersist(aPersist); } \
  NS_IMETHOD GetPercentComplete(PRInt32 *aPercentComplete) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPercentComplete(aPercentComplete); } \
  NS_IMETHOD GetDisplayName(PRUnichar * *aDisplayName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDisplayName(aDisplayName); } \
  NS_IMETHOD SetDisplayName(const PRUnichar * aDisplayName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDisplayName(aDisplayName); } \
  NS_IMETHOD GetStartTime(PRInt64 *aStartTime) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetStartTime(aStartTime); } \
  NS_IMETHOD GetMIMEInfo(nsIMIMEInfo * *aMIMEInfo) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMIMEInfo(aMIMEInfo); } \
  NS_IMETHOD GetListener(nsIWebProgressListener * *aListener) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetListener(aListener); } \
  NS_IMETHOD SetListener(nsIWebProgressListener * aListener) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetListener(aListener); } \
  NS_IMETHOD GetObserver(nsIObserver * *aObserver) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetObserver(aObserver); } \
  NS_IMETHOD SetObserver(nsIObserver * aObserver) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetObserver(aObserver); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDownload : public nsIDownload
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOWNLOAD

  nsDownload();
  virtual ~nsDownload();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDownload, nsIDownload)

nsDownload::nsDownload()
{
  /* member initializers and constructor code */
}

nsDownload::~nsDownload()
{
  /* destructor code */
}

/* void init (in nsIURI aSource, in nsILocalFile aTarget, in wstring aDisplayName, in nsIMIMEInfo aMIMEInfo, in long long startTime, in nsIWebBrowserPersist aPersist); */
NS_IMETHODIMP nsDownload::Init(nsIURI *aSource, nsILocalFile *aTarget, const PRUnichar *aDisplayName, nsIMIMEInfo *aMIMEInfo, PRInt64 startTime, nsIWebBrowserPersist *aPersist)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIURI source; */
NS_IMETHODIMP nsDownload::GetSource(nsIURI * *aSource)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsILocalFile target; */
NS_IMETHODIMP nsDownload::GetTarget(nsILocalFile * *aTarget)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIWebBrowserPersist persist; */
NS_IMETHODIMP nsDownload::GetPersist(nsIWebBrowserPersist * *aPersist)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRInt32 percentComplete; */
NS_IMETHODIMP nsDownload::GetPercentComplete(PRInt32 *aPercentComplete)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute wstring displayName; */
NS_IMETHODIMP nsDownload::GetDisplayName(PRUnichar * *aDisplayName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDownload::SetDisplayName(const PRUnichar * aDisplayName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long long startTime; */
NS_IMETHODIMP nsDownload::GetStartTime(PRInt64 *aStartTime)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIMIMEInfo MIMEInfo; */
NS_IMETHODIMP nsDownload::GetMIMEInfo(nsIMIMEInfo * *aMIMEInfo)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIWebProgressListener listener; */
NS_IMETHODIMP nsDownload::GetListener(nsIWebProgressListener * *aListener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDownload::SetListener(nsIWebProgressListener * aListener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIObserver observer; */
NS_IMETHODIMP nsDownload::GetObserver(nsIObserver * *aObserver)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDownload::SetObserver(nsIObserver * aObserver)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

#define NS_DOWNLOAD_CONTRACTID "@mozilla.org/download;1"
// {E3FA9D0A-1DD1-11B2-BDEF-8C720B597445}
#define NS_DOWNLOAD_CID \
    { 0xe3fa9d0a, 0x1dd1, 0x11b2, { 0xbd, 0xef, 0x8c, 0x72, 0x0b, 0x59, 0x74, 0x45 } }

#endif /* __gen_nsIDownload_h__ */
