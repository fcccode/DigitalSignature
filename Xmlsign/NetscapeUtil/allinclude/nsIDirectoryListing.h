/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIDirectoryListing.idl
 */

#ifndef __gen_nsIDirectoryListing_h__
#define __gen_nsIDirectoryListing_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDirectoryListing */
#define NS_IDIRECTORYLISTING_IID_STR "a465d8ed-3661-483d-a6f1-a82a6bd617b3"

#define NS_IDIRECTORYLISTING_IID \
  {0xa465d8ed, 0x3661, 0x483d, \
    { 0xa6, 0xf1, 0xa8, 0x2a, 0x6b, 0xd6, 0x17, 0xb3 }}

/** This interface allows setting the output format for a directory listing
 * Implementations of this interface should default to html, since that is the
 * lowest common denominator which all places can deal with.
 */
class NS_NO_VTABLE nsIDirectoryListing : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDIRECTORYLISTING_IID)

  /** Use the pref */
  enum { FORMAT_PREF = 0U };

  /** Raw format - exactly what comes off the network. It is very
     * unlikely that you want this
     */
  enum { FORMAT_RAW = 1U };

  /** HTML */
  enum { FORMAT_HTML = 2U };

  /** application/http-index-format
     * This will end up at the code in xpfe/components/directory so if
     * you explicitly set this, be sure that this dependancy is OK
     */
  enum { FORMAT_HTTP_INDEX = 3U };

  /** The actual format
     * If the given format is not supported, NS_ERROR_FAILURE is returned.
     * The getter for this returns the actual value, having translated
     * FORMAT_PREF into the current pref format
     */
  /* attribute unsigned long listFormat; */
  NS_IMETHOD GetListFormat(PRUint32 *aListFormat) = 0;
  NS_IMETHOD SetListFormat(PRUint32 aListFormat) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDIRECTORYLISTING \
  NS_IMETHOD GetListFormat(PRUint32 *aListFormat); \
  NS_IMETHOD SetListFormat(PRUint32 aListFormat); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDIRECTORYLISTING(_to) \
  NS_IMETHOD GetListFormat(PRUint32 *aListFormat) { return _to GetListFormat(aListFormat); } \
  NS_IMETHOD SetListFormat(PRUint32 aListFormat) { return _to SetListFormat(aListFormat); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDIRECTORYLISTING(_to) \
  NS_IMETHOD GetListFormat(PRUint32 *aListFormat) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetListFormat(aListFormat); } \
  NS_IMETHOD SetListFormat(PRUint32 aListFormat) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetListFormat(aListFormat); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDirectoryListing : public nsIDirectoryListing
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDIRECTORYLISTING

  nsDirectoryListing();
  virtual ~nsDirectoryListing();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDirectoryListing, nsIDirectoryListing)

nsDirectoryListing::nsDirectoryListing()
{
  /* member initializers and constructor code */
}

nsDirectoryListing::~nsDirectoryListing()
{
  /* destructor code */
}

/* attribute unsigned long listFormat; */
NS_IMETHODIMP nsDirectoryListing::GetListFormat(PRUint32 *aListFormat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDirectoryListing::SetListFormat(PRUint32 aListFormat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDirectoryListing_h__ */
