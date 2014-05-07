/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIResumableEntityID.idl
 */

#ifndef __gen_nsIResumableEntityID_h__
#define __gen_nsIResumableEntityID_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIResumableEntityID */
#define NS_IRESUMABLEENTITYID_IID_STR "c9df38d4-1dd1-11b2-81ae-c9e767256d1b"

#define NS_IRESUMABLEENTITYID_IID \
  {0xc9df38d4, 0x1dd1, 0x11b2, \
    { 0x81, 0xae, 0xc9, 0xe7, 0x67, 0x25, 0x6d, 0x1b }}

/** This is an interface for resumable entities
 * @see nsIResumableChannel
 */
class NS_NO_VTABLE nsIResumableEntityID : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IRESUMABLEENTITYID_IID)

  /** Size of the entity, -1 if unknown */
  /* attribute unsigned long size; */
  NS_IMETHOD GetSize(PRUint32 *aSize) = 0;
  NS_IMETHOD SetSize(PRUint32 aSize) = 0;

  /** Last modified time, in seconds since epoch. Note that the timezone
     * these are in may not be known
     */
  /* attribute PRTime lastModified; */
  NS_IMETHOD GetLastModified(PRTime *aLastModified) = 0;
  NS_IMETHOD SetLastModified(PRTime aLastModified) = 0;

  /** Entity, may be empty. This is meant to hold the E-Tag for http */
/** Compare to another nsIResumableEntityID */
  /* boolean equals (in nsIResumableEntityID other); */
  NS_IMETHOD Equals(nsIResumableEntityID *other, PRBool *_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIRESUMABLEENTITYID \
  NS_IMETHOD GetSize(PRUint32 *aSize); \
  NS_IMETHOD SetSize(PRUint32 aSize); \
  NS_IMETHOD GetLastModified(PRTime *aLastModified); \
  NS_IMETHOD SetLastModified(PRTime aLastModified); \
  NS_IMETHOD Equals(nsIResumableEntityID *other, PRBool *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIRESUMABLEENTITYID(_to) \
  NS_IMETHOD GetSize(PRUint32 *aSize) { return _to GetSize(aSize); } \
  NS_IMETHOD SetSize(PRUint32 aSize) { return _to SetSize(aSize); } \
  NS_IMETHOD GetLastModified(PRTime *aLastModified) { return _to GetLastModified(aLastModified); } \
  NS_IMETHOD SetLastModified(PRTime aLastModified) { return _to SetLastModified(aLastModified); } \
  NS_IMETHOD Equals(nsIResumableEntityID *other, PRBool *_retval) { return _to Equals(other, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIRESUMABLEENTITYID(_to) \
  NS_IMETHOD GetSize(PRUint32 *aSize) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSize(aSize); } \
  NS_IMETHOD SetSize(PRUint32 aSize) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSize(aSize); } \
  NS_IMETHOD GetLastModified(PRTime *aLastModified) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastModified(aLastModified); } \
  NS_IMETHOD SetLastModified(PRTime aLastModified) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLastModified(aLastModified); } \
  NS_IMETHOD Equals(nsIResumableEntityID *other, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Equals(other, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsResumableEntityID : public nsIResumableEntityID
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIRESUMABLEENTITYID

  nsResumableEntityID();
  virtual ~nsResumableEntityID();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsResumableEntityID, nsIResumableEntityID)

nsResumableEntityID::nsResumableEntityID()
{
  /* member initializers and constructor code */
}

nsResumableEntityID::~nsResumableEntityID()
{
  /* destructor code */
}

/* attribute unsigned long size; */
NS_IMETHODIMP nsResumableEntityID::GetSize(PRUint32 *aSize)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsResumableEntityID::SetSize(PRUint32 aSize)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute PRTime lastModified; */
NS_IMETHODIMP nsResumableEntityID::GetLastModified(PRTime *aLastModified)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsResumableEntityID::SetLastModified(PRTime aLastModified)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean equals (in nsIResumableEntityID other); */
NS_IMETHODIMP nsResumableEntityID::Equals(nsIResumableEntityID *other, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIResumableEntityID_h__ */
