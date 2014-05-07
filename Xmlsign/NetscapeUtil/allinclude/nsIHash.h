/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM /home/manoj/mozilla/security/manager/ssl/public/nsIHash.idl
 */

#ifndef __gen_nsIHash_h__
#define __gen_nsIHash_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#define NS_HASH_CONTRACTID "@mozilla.org/nsHash;1"

/* starting interface:    nsIHash */
#define NS_IHASH_IID_STR "a31a3028-ae28-11d5-ba4b-00108303b117"

#define NS_IHASH_IID \
  {0xa31a3028, 0xae28, 0x11d5, \
    { 0xba, 0x4b, 0x00, 0x10, 0x83, 0x03, 0xb1, 0x17 }}

class NS_NO_VTABLE nsIHash : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IHASH_IID)

  enum { HASH_AlgNULL = 0 };

  enum { HASH_AlgMD2 = 1 };

  enum { HASH_AlgMD5 = 2 };

  enum { HASH_AlgSHA1 = 3 };

  enum { MD2_LEN = 16U };

  enum { MD5_LEN = 16U };

  enum { SHA1_LEN = 20U };

  enum { MAX_HASH_LEN = 20U };

  /* unsigned long resultLen (in short aAlg); */
  NS_IMETHOD ResultLen(PRInt16 aAlg, PRUint32 *_retval) = 0;

  /* void create (in short aAlg); */
  NS_IMETHOD Create(PRInt16 aAlg) = 0;

  /* void begin (); */
  NS_IMETHOD Begin(void) = 0;

  /* void update (in UnsignedCharPtr aBuf, in unsigned long aLen); */
  NS_IMETHOD Update(unsigned char * aBuf, PRUint32 aLen) = 0;

  /* void end (in UnsignedCharPtr aHash, out unsigned long aLen, in unsigned long aMaxLen); */
  NS_IMETHOD End(unsigned char * aHash, PRUint32 *aLen, PRUint32 aMaxLen) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIHASH \
  NS_IMETHOD ResultLen(PRInt16 aAlg, PRUint32 *_retval); \
  NS_IMETHOD Create(PRInt16 aAlg); \
  NS_IMETHOD Begin(void); \
  NS_IMETHOD Update(unsigned char * aBuf, PRUint32 aLen); \
  NS_IMETHOD End(unsigned char * aHash, PRUint32 *aLen, PRUint32 aMaxLen); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIHASH(_to) \
  NS_IMETHOD ResultLen(PRInt16 aAlg, PRUint32 *_retval) { return _to ResultLen(aAlg, _retval); } \
  NS_IMETHOD Create(PRInt16 aAlg) { return _to Create(aAlg); } \
  NS_IMETHOD Begin(void) { return _to Begin(); } \
  NS_IMETHOD Update(unsigned char * aBuf, PRUint32 aLen) { return _to Update(aBuf, aLen); } \
  NS_IMETHOD End(unsigned char * aHash, PRUint32 *aLen, PRUint32 aMaxLen) { return _to End(aHash, aLen, aMaxLen); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIHASH(_to) \
  NS_IMETHOD ResultLen(PRInt16 aAlg, PRUint32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->ResultLen(aAlg, _retval); } \
  NS_IMETHOD Create(PRInt16 aAlg) { return !_to ? NS_ERROR_NULL_POINTER : _to->Create(aAlg); } \
  NS_IMETHOD Begin(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Begin(); } \
  NS_IMETHOD Update(unsigned char * aBuf, PRUint32 aLen) { return !_to ? NS_ERROR_NULL_POINTER : _to->Update(aBuf, aLen); } \
  NS_IMETHOD End(unsigned char * aHash, PRUint32 *aLen, PRUint32 aMaxLen) { return !_to ? NS_ERROR_NULL_POINTER : _to->End(aHash, aLen, aMaxLen); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsHash : public nsIHash
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIHASH

  nsHash();

private:
  ~nsHash();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsHash, nsIHash)

nsHash::nsHash()
{
  /* member initializers and constructor code */
}

nsHash::~nsHash()
{
  /* destructor code */
}

/* unsigned long resultLen (in short aAlg); */
NS_IMETHODIMP nsHash::ResultLen(PRInt16 aAlg, PRUint32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void create (in short aAlg); */
NS_IMETHODIMP nsHash::Create(PRInt16 aAlg)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void begin (); */
NS_IMETHODIMP nsHash::Begin()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void update (in UnsignedCharPtr aBuf, in unsigned long aLen); */
NS_IMETHODIMP nsHash::Update(unsigned char * aBuf, PRUint32 aLen)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void end (in UnsignedCharPtr aHash, out unsigned long aLen, in unsigned long aMaxLen); */
NS_IMETHODIMP nsHash::End(unsigned char * aHash, PRUint32 *aLen, PRUint32 aMaxLen)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIHash_h__ */
