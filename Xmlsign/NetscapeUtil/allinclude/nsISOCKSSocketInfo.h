/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsISOCKSSocketInfo.idl
 */

#ifndef __gen_nsISOCKSSocketInfo_h__
#define __gen_nsISOCKSSocketInfo_h__


#ifndef __gen_nsIProxy_h__
#include "nsIProxy.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#include "prtypes.h"
#include "prio.h"

/* starting interface:    nsISOCKSSocketInfo */
#define NS_ISOCKSSOCKETINFO_IID_STR "8f755c44-1dd2-11b2-a613-91117453fa95"

#define NS_ISOCKSSOCKETINFO_IID \
  {0x8f755c44, 0x1dd2, 0x11b2, \
    { 0xa6, 0x13, 0x91, 0x11, 0x74, 0x53, 0xfa, 0x95 }}

class NS_NO_VTABLE nsISOCKSSocketInfo : public nsIProxy {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ISOCKSSOCKETINFO_IID)

  /* attribute prNetAddr destinationAddr; */
  NS_IMETHOD GetDestinationAddr(PRNetAddr * *aDestinationAddr) = 0;
  NS_IMETHOD SetDestinationAddr(PRNetAddr * aDestinationAddr) = 0;

  /* attribute prNetAddr externalProxyAddr; */
  NS_IMETHOD GetExternalProxyAddr(PRNetAddr * *aExternalProxyAddr) = 0;
  NS_IMETHOD SetExternalProxyAddr(PRNetAddr * aExternalProxyAddr) = 0;

  /* attribute prNetAddr internalProxyAddr; */
  NS_IMETHOD GetInternalProxyAddr(PRNetAddr * *aInternalProxyAddr) = 0;
  NS_IMETHOD SetInternalProxyAddr(PRNetAddr * aInternalProxyAddr) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISOCKSSOCKETINFO \
  NS_IMETHOD GetDestinationAddr(PRNetAddr * *aDestinationAddr); \
  NS_IMETHOD SetDestinationAddr(PRNetAddr * aDestinationAddr); \
  NS_IMETHOD GetExternalProxyAddr(PRNetAddr * *aExternalProxyAddr); \
  NS_IMETHOD SetExternalProxyAddr(PRNetAddr * aExternalProxyAddr); \
  NS_IMETHOD GetInternalProxyAddr(PRNetAddr * *aInternalProxyAddr); \
  NS_IMETHOD SetInternalProxyAddr(PRNetAddr * aInternalProxyAddr); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISOCKSSOCKETINFO(_to) \
  NS_IMETHOD GetDestinationAddr(PRNetAddr * *aDestinationAddr) { return _to GetDestinationAddr(aDestinationAddr); } \
  NS_IMETHOD SetDestinationAddr(PRNetAddr * aDestinationAddr) { return _to SetDestinationAddr(aDestinationAddr); } \
  NS_IMETHOD GetExternalProxyAddr(PRNetAddr * *aExternalProxyAddr) { return _to GetExternalProxyAddr(aExternalProxyAddr); } \
  NS_IMETHOD SetExternalProxyAddr(PRNetAddr * aExternalProxyAddr) { return _to SetExternalProxyAddr(aExternalProxyAddr); } \
  NS_IMETHOD GetInternalProxyAddr(PRNetAddr * *aInternalProxyAddr) { return _to GetInternalProxyAddr(aInternalProxyAddr); } \
  NS_IMETHOD SetInternalProxyAddr(PRNetAddr * aInternalProxyAddr) { return _to SetInternalProxyAddr(aInternalProxyAddr); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISOCKSSOCKETINFO(_to) \
  NS_IMETHOD GetDestinationAddr(PRNetAddr * *aDestinationAddr) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDestinationAddr(aDestinationAddr); } \
  NS_IMETHOD SetDestinationAddr(PRNetAddr * aDestinationAddr) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDestinationAddr(aDestinationAddr); } \
  NS_IMETHOD GetExternalProxyAddr(PRNetAddr * *aExternalProxyAddr) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetExternalProxyAddr(aExternalProxyAddr); } \
  NS_IMETHOD SetExternalProxyAddr(PRNetAddr * aExternalProxyAddr) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetExternalProxyAddr(aExternalProxyAddr); } \
  NS_IMETHOD GetInternalProxyAddr(PRNetAddr * *aInternalProxyAddr) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInternalProxyAddr(aInternalProxyAddr); } \
  NS_IMETHOD SetInternalProxyAddr(PRNetAddr * aInternalProxyAddr) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInternalProxyAddr(aInternalProxyAddr); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSOCKSSocketInfo : public nsISOCKSSocketInfo
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISOCKSSOCKETINFO

  nsSOCKSSocketInfo();
  virtual ~nsSOCKSSocketInfo();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSOCKSSocketInfo, nsISOCKSSocketInfo)

nsSOCKSSocketInfo::nsSOCKSSocketInfo()
{
  /* member initializers and constructor code */
}

nsSOCKSSocketInfo::~nsSOCKSSocketInfo()
{
  /* destructor code */
}

/* attribute prNetAddr destinationAddr; */
NS_IMETHODIMP nsSOCKSSocketInfo::GetDestinationAddr(PRNetAddr * *aDestinationAddr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSOCKSSocketInfo::SetDestinationAddr(PRNetAddr * aDestinationAddr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute prNetAddr externalProxyAddr; */
NS_IMETHODIMP nsSOCKSSocketInfo::GetExternalProxyAddr(PRNetAddr * *aExternalProxyAddr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSOCKSSocketInfo::SetExternalProxyAddr(PRNetAddr * aExternalProxyAddr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute prNetAddr internalProxyAddr; */
NS_IMETHODIMP nsSOCKSSocketInfo::GetInternalProxyAddr(PRNetAddr * *aInternalProxyAddr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSOCKSSocketInfo::SetInternalProxyAddr(PRNetAddr * aInternalProxyAddr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsISOCKSSocketInfo_h__ */
