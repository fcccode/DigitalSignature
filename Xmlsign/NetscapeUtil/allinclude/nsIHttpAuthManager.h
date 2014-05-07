/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIHttpAuthManager.idl
 */

#ifndef __gen_nsIHttpAuthManager_h__
#define __gen_nsIHttpAuthManager_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIHttpAuthManager */
#define NS_IHTTPAUTHMANAGER_IID_STR "81328d02-74df-4724-8a53-8fac43841c5c"

#define NS_IHTTPAUTHMANAGER_IID \
  {0x81328d02, 0x74df, 0x4724, \
    { 0x8a, 0x53, 0x8f, 0xac, 0x43, 0x84, 0x1c, 0x5c }}

class NS_NO_VTABLE nsIHttpAuthManager : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IHTTPAUTHMANAGER_IID)

  /**
     * Lookup auth identity.
     *
     * @param hostPort
     *        the "host:port" of the server issuing a challenge.
     * @param realm
     *        optional string identifying auth realm.
     * @param path
     *        optional string identifying auth path. empty for proxy auth.
     * @param userDomain
     *        return value containing user domain.
     * @param userName
     *        return value containing user name.
     * @param userPassword
     *        return value containing user password.
     */
  /* void getAuthIdentity (in ACString aHost, in PRInt32 aPort, in ACString aRealm, in ACString aPath, out AString aUserDomain, out AString aUserName, out AString aUserPassword); */
  NS_IMETHOD GetAuthIdentity(const nsACString & aHost, PRInt32 aPort, const nsACString & aRealm, const nsACString & aPath, nsAString & aUserDomain, nsAString & aUserName, nsAString & aUserPassword) = 0;

  /**
     * Store auth identity.
     *
     * @param hostPort
     *        the "host:port" of the server issuing a challenge.
     * @param realm
     *        optional string identifying auth realm.
     * @param path
     *        optional string identifying auth path. empty for proxy auth.
     * @param userDomain
     *        optional string containing user domain.
     * @param userName
     *        optional string containing user name.
     * @param userPassword
     *        optional string containing user password.
     */
  /* void setAuthIdentity (in ACString aHost, in PRInt32 aPort, in ACString aRealm, in ACString aPath, in AString aUserDomain, in AString aUserName, in AString aUserPassword); */
  NS_IMETHOD SetAuthIdentity(const nsACString & aHost, PRInt32 aPort, const nsACString & aRealm, const nsACString & aPath, const nsAString & aUserDomain, const nsAString & aUserName, const nsAString & aUserPassword) = 0;

  /**
     * Clear all auth cache.
     */
  /* void clearAll (); */
  NS_IMETHOD ClearAll(void) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIHTTPAUTHMANAGER \
  NS_IMETHOD GetAuthIdentity(const nsACString & aHost, PRInt32 aPort, const nsACString & aRealm, const nsACString & aPath, nsAString & aUserDomain, nsAString & aUserName, nsAString & aUserPassword); \
  NS_IMETHOD SetAuthIdentity(const nsACString & aHost, PRInt32 aPort, const nsACString & aRealm, const nsACString & aPath, const nsAString & aUserDomain, const nsAString & aUserName, const nsAString & aUserPassword); \
  NS_IMETHOD ClearAll(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIHTTPAUTHMANAGER(_to) \
  NS_IMETHOD GetAuthIdentity(const nsACString & aHost, PRInt32 aPort, const nsACString & aRealm, const nsACString & aPath, nsAString & aUserDomain, nsAString & aUserName, nsAString & aUserPassword) { return _to GetAuthIdentity(aHost, aPort, aRealm, aPath, aUserDomain, aUserName, aUserPassword); } \
  NS_IMETHOD SetAuthIdentity(const nsACString & aHost, PRInt32 aPort, const nsACString & aRealm, const nsACString & aPath, const nsAString & aUserDomain, const nsAString & aUserName, const nsAString & aUserPassword) { return _to SetAuthIdentity(aHost, aPort, aRealm, aPath, aUserDomain, aUserName, aUserPassword); } \
  NS_IMETHOD ClearAll(void) { return _to ClearAll(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIHTTPAUTHMANAGER(_to) \
  NS_IMETHOD GetAuthIdentity(const nsACString & aHost, PRInt32 aPort, const nsACString & aRealm, const nsACString & aPath, nsAString & aUserDomain, nsAString & aUserName, nsAString & aUserPassword) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAuthIdentity(aHost, aPort, aRealm, aPath, aUserDomain, aUserName, aUserPassword); } \
  NS_IMETHOD SetAuthIdentity(const nsACString & aHost, PRInt32 aPort, const nsACString & aRealm, const nsACString & aPath, const nsAString & aUserDomain, const nsAString & aUserName, const nsAString & aUserPassword) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAuthIdentity(aHost, aPort, aRealm, aPath, aUserDomain, aUserName, aUserPassword); } \
  NS_IMETHOD ClearAll(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ClearAll(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsHttpAuthManager : public nsIHttpAuthManager
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIHTTPAUTHMANAGER

  nsHttpAuthManager();
  virtual ~nsHttpAuthManager();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsHttpAuthManager, nsIHttpAuthManager)

nsHttpAuthManager::nsHttpAuthManager()
{
  /* member initializers and constructor code */
}

nsHttpAuthManager::~nsHttpAuthManager()
{
  /* destructor code */
}

/* void getAuthIdentity (in ACString aHost, in PRInt32 aPort, in ACString aRealm, in ACString aPath, out AString aUserDomain, out AString aUserName, out AString aUserPassword); */
NS_IMETHODIMP nsHttpAuthManager::GetAuthIdentity(const nsACString & aHost, PRInt32 aPort, const nsACString & aRealm, const nsACString & aPath, nsAString & aUserDomain, nsAString & aUserName, nsAString & aUserPassword)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setAuthIdentity (in ACString aHost, in PRInt32 aPort, in ACString aRealm, in ACString aPath, in AString aUserDomain, in AString aUserName, in AString aUserPassword); */
NS_IMETHODIMP nsHttpAuthManager::SetAuthIdentity(const nsACString & aHost, PRInt32 aPort, const nsACString & aRealm, const nsACString & aPath, const nsAString & aUserDomain, const nsAString & aUserName, const nsAString & aUserPassword)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void clearAll (); */
NS_IMETHODIMP nsHttpAuthManager::ClearAll()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIHttpAuthManager_h__ */
