/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIAuthModule.idl
 */

#ifndef __gen_nsIAuthModule_h__
#define __gen_nsIAuthModule_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIAuthModule */
#define NS_IAUTHMODULE_IID_STR "991eff7c-a8ba-441a-b71b-753bd8e6d6be"

#define NS_IAUTHMODULE_IID \
  {0x991eff7c, 0xa8ba, 0x441a, \
    { 0xb7, 0x1b, 0x75, 0x3b, 0xd8, 0xe6, 0xd6, 0xbe }}

class NS_NO_VTABLE nsIAuthModule : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IAUTHMODULE_IID)

  /**
     * Called to initialize an auth module.  The other methods cannot be called
     * unless this method succeeds.
     *
     * @param aDomain
     *        the authentication domain, which may be null if not applicable.
     * @param aUsername
     *        the user's login name
     * @param aPassword
     *        the user's password
     */
  /* void init (in wstring aDomain, in wstring aUsername, in wstring aPassword); */
  NS_IMETHOD Init(const PRUnichar *aDomain, const PRUnichar *aUsername, const PRUnichar *aPassword) = 0;

  /**
     * Called to get the next token in a sequence of authentication steps.
     *
     * @param aInToken
     *        A buffer containing the input token (e.g., a challenge from a
     *        server).  This may be null.
     * @param aInTokenLength
     *        The length of the input token.
     * @param aOutToken
     *        If getNextToken succeeds, then aOutToken will point to a buffer
     *        to be sent in response to the server challenge.  The length of
     *        this buffer is given by aOutTokenLength.  The buffer at aOutToken
     *        must be recycled with a call to nsMemory::Free.
     * @param aOutTokenLength
     *        If getNextToken succeeds, then aOutTokenLength contains the
     *        length of the buffer (number of bytes) pointed to by aOutToken.
     */
  /* void getNextToken ([const] in voidPtr aInToken, in unsigned long aInTokenLength, out voidPtr aOutToken, out unsigned long aOutTokenLength); */
  NS_IMETHOD GetNextToken(const void * aInToken, PRUint32 aInTokenLength, void * *aOutToken, PRUint32 *aOutTokenLength) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIAUTHMODULE \
  NS_IMETHOD Init(const PRUnichar *aDomain, const PRUnichar *aUsername, const PRUnichar *aPassword); \
  NS_IMETHOD GetNextToken(const void * aInToken, PRUint32 aInTokenLength, void * *aOutToken, PRUint32 *aOutTokenLength); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIAUTHMODULE(_to) \
  NS_IMETHOD Init(const PRUnichar *aDomain, const PRUnichar *aUsername, const PRUnichar *aPassword) { return _to Init(aDomain, aUsername, aPassword); } \
  NS_IMETHOD GetNextToken(const void * aInToken, PRUint32 aInTokenLength, void * *aOutToken, PRUint32 *aOutTokenLength) { return _to GetNextToken(aInToken, aInTokenLength, aOutToken, aOutTokenLength); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIAUTHMODULE(_to) \
  NS_IMETHOD Init(const PRUnichar *aDomain, const PRUnichar *aUsername, const PRUnichar *aPassword) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(aDomain, aUsername, aPassword); } \
  NS_IMETHOD GetNextToken(const void * aInToken, PRUint32 aInTokenLength, void * *aOutToken, PRUint32 *aOutTokenLength) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNextToken(aInToken, aInTokenLength, aOutToken, aOutTokenLength); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAuthModule : public nsIAuthModule
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIAUTHMODULE

  nsAuthModule();
  virtual ~nsAuthModule();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAuthModule, nsIAuthModule)

nsAuthModule::nsAuthModule()
{
  /* member initializers and constructor code */
}

nsAuthModule::~nsAuthModule()
{
  /* destructor code */
}

/* void init (in wstring aDomain, in wstring aUsername, in wstring aPassword); */
NS_IMETHODIMP nsAuthModule::Init(const PRUnichar *aDomain, const PRUnichar *aUsername, const PRUnichar *aPassword)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getNextToken ([const] in voidPtr aInToken, in unsigned long aInTokenLength, out voidPtr aOutToken, out unsigned long aOutTokenLength); */
NS_IMETHODIMP nsAuthModule::GetNextToken(const void * aInToken, PRUint32 aInTokenLength, void * *aOutToken, PRUint32 *aOutTokenLength)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

/**
 * nsIAuthModule implementations are registered under the following contract
 * ID prefix:
 */
#define NS_AUTH_MODULE_CONTRACTID_PREFIX \
    "@mozilla.org/network/auth-module;1?name="

#endif /* __gen_nsIAuthModule_h__ */
