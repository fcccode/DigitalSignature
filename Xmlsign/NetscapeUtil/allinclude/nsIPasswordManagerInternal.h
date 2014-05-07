/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIPasswordManagerInternal.idl
 */

#ifndef __gen_nsIPasswordManagerInternal_h__
#define __gen_nsIPasswordManagerInternal_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIPasswordManagerInternal */
#define NS_IPASSWORDMANAGERINTERNAL_IID_STR "f22cd1a0-3709-11d6-a63a-0010a401eb10"

#define NS_IPASSWORDMANAGERINTERNAL_IID \
  {0xf22cd1a0, 0x3709, 0x11d6, \
    { 0xa6, 0x3a, 0x00, 0x10, 0xa4, 0x01, 0xeb, 0x10 }}

/** 
 * An optional interface for obtaining fields of
 * logins that were collected by the password manager
 */
class NS_NO_VTABLE nsIPasswordManagerInternal : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IPASSWORDMANAGERINTERNAL_IID)

  /**
   * A Call to find a login in the password manager list that matches the
   * specified parameters. If any input parameter is null, it is
   * not tested for when looking for the match.
   *
   * @param aHostURI The uri part of a login to search for, or null
   * @param aUsername The username part of a login to search for, or null
   * @param aPassword The password part of a login to search for, or null
   * @param aHostURIFound The uri found in the login
   * @param aUsernameFound The username found in the login
   * @param aPasswordFound The password found in the login
   */
  /* void findPasswordEntry (in AUTF8String aHostURI, in AString aUsername, in AString aPassword, out AUTF8String aHostURIFound, out AString aUsernameFound, out AString aPasswordFound); */
  NS_IMETHOD FindPasswordEntry(const nsACString & aHostURI, const nsAString & aUsername, const nsAString & aPassword, nsACString & aHostURIFound, nsAString & aUsernameFound, nsAString & aPasswordFound) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIPASSWORDMANAGERINTERNAL \
  NS_IMETHOD FindPasswordEntry(const nsACString & aHostURI, const nsAString & aUsername, const nsAString & aPassword, nsACString & aHostURIFound, nsAString & aUsernameFound, nsAString & aPasswordFound); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIPASSWORDMANAGERINTERNAL(_to) \
  NS_IMETHOD FindPasswordEntry(const nsACString & aHostURI, const nsAString & aUsername, const nsAString & aPassword, nsACString & aHostURIFound, nsAString & aUsernameFound, nsAString & aPasswordFound) { return _to FindPasswordEntry(aHostURI, aUsername, aPassword, aHostURIFound, aUsernameFound, aPasswordFound); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIPASSWORDMANAGERINTERNAL(_to) \
  NS_IMETHOD FindPasswordEntry(const nsACString & aHostURI, const nsAString & aUsername, const nsAString & aPassword, nsACString & aHostURIFound, nsAString & aUsernameFound, nsAString & aPasswordFound) { return !_to ? NS_ERROR_NULL_POINTER : _to->FindPasswordEntry(aHostURI, aUsername, aPassword, aHostURIFound, aUsernameFound, aPasswordFound); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsPasswordManagerInternal : public nsIPasswordManagerInternal
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIPASSWORDMANAGERINTERNAL

  nsPasswordManagerInternal();
  virtual ~nsPasswordManagerInternal();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsPasswordManagerInternal, nsIPasswordManagerInternal)

nsPasswordManagerInternal::nsPasswordManagerInternal()
{
  /* member initializers and constructor code */
}

nsPasswordManagerInternal::~nsPasswordManagerInternal()
{
  /* destructor code */
}

/* void findPasswordEntry (in AUTF8String aHostURI, in AString aUsername, in AString aPassword, out AUTF8String aHostURIFound, out AString aUsernameFound, out AString aPasswordFound); */
NS_IMETHODIMP nsPasswordManagerInternal::FindPasswordEntry(const nsACString & aHostURI, const nsAString & aUsername, const nsAString & aPassword, nsACString & aHostURIFound, nsAString & aUsernameFound, nsAString & aPasswordFound)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIPasswordManagerInternal_h__ */
