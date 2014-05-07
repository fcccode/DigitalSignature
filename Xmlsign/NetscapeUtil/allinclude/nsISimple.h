/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsISimple.idl
 */

#ifndef __gen_nsISimple_h__
#define __gen_nsISimple_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIVariant_h__
#include "nsIVariant.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsISimple */
#define NS_ISIMPLE_IID_STR "f485ed90-e868-4356-bb5b-afa040fca627"

#define NS_ISIMPLE_IID \
  {0xf485ed90, 0xe868, 0x4356, \
    { 0xbb, 0x5b, 0xaf, 0xa0, 0x40, 0xfc, 0xa6, 0x27 }}

class NS_NO_VTABLE nsISimple : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ISIMPLE_IID)

  /* attribute string yourName; */
  NS_IMETHOD GetYourName(char * *aYourName) = 0;
  NS_IMETHOD SetYourName(const char * aYourName) = 0;

  /* attribute AString wideName; */
  NS_IMETHOD GetWideName(nsAString & aWideName) = 0;
  NS_IMETHOD SetWideName(const nsAString & aWideName) = 0;

  /* attribute nsIVariant varTest; */
  NS_IMETHOD GetVarTest(nsIVariant * *aVarTest) = 0;
  NS_IMETHOD SetVarTest(nsIVariant * aVarTest) = 0;

  /* attribute nsIVariant varInt; */
  NS_IMETHOD GetVarInt(nsIVariant * *aVarInt) = 0;
  NS_IMETHOD SetVarInt(nsIVariant * aVarInt) = 0;

  /* attribute nsIVariant varByteArray; */
  NS_IMETHOD GetVarByteArray(nsIVariant * *aVarByteArray) = 0;
  NS_IMETHOD SetVarByteArray(nsIVariant * aVarByteArray) = 0;

  /* attribute nsIVariant varBstrArray; */
  NS_IMETHOD GetVarBstrArray(nsIVariant * *aVarBstrArray) = 0;
  NS_IMETHOD SetVarBstrArray(nsIVariant * aVarBstrArray) = 0;

  /* void write (); */
  NS_IMETHOD Write(void) = 0;

  /* void change (in string aValue); */
  NS_IMETHOD Change(const char *aValue) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISIMPLE \
  NS_IMETHOD GetYourName(char * *aYourName); \
  NS_IMETHOD SetYourName(const char * aYourName); \
  NS_IMETHOD GetWideName(nsAString & aWideName); \
  NS_IMETHOD SetWideName(const nsAString & aWideName); \
  NS_IMETHOD GetVarTest(nsIVariant * *aVarTest); \
  NS_IMETHOD SetVarTest(nsIVariant * aVarTest); \
  NS_IMETHOD GetVarInt(nsIVariant * *aVarInt); \
  NS_IMETHOD SetVarInt(nsIVariant * aVarInt); \
  NS_IMETHOD GetVarByteArray(nsIVariant * *aVarByteArray); \
  NS_IMETHOD SetVarByteArray(nsIVariant * aVarByteArray); \
  NS_IMETHOD GetVarBstrArray(nsIVariant * *aVarBstrArray); \
  NS_IMETHOD SetVarBstrArray(nsIVariant * aVarBstrArray); \
  NS_IMETHOD Write(void); \
  NS_IMETHOD Change(const char *aValue); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISIMPLE(_to) \
  NS_IMETHOD GetYourName(char * *aYourName) { return _to GetYourName(aYourName); } \
  NS_IMETHOD SetYourName(const char * aYourName) { return _to SetYourName(aYourName); } \
  NS_IMETHOD GetWideName(nsAString & aWideName) { return _to GetWideName(aWideName); } \
  NS_IMETHOD SetWideName(const nsAString & aWideName) { return _to SetWideName(aWideName); } \
  NS_IMETHOD GetVarTest(nsIVariant * *aVarTest) { return _to GetVarTest(aVarTest); } \
  NS_IMETHOD SetVarTest(nsIVariant * aVarTest) { return _to SetVarTest(aVarTest); } \
  NS_IMETHOD GetVarInt(nsIVariant * *aVarInt) { return _to GetVarInt(aVarInt); } \
  NS_IMETHOD SetVarInt(nsIVariant * aVarInt) { return _to SetVarInt(aVarInt); } \
  NS_IMETHOD GetVarByteArray(nsIVariant * *aVarByteArray) { return _to GetVarByteArray(aVarByteArray); } \
  NS_IMETHOD SetVarByteArray(nsIVariant * aVarByteArray) { return _to SetVarByteArray(aVarByteArray); } \
  NS_IMETHOD GetVarBstrArray(nsIVariant * *aVarBstrArray) { return _to GetVarBstrArray(aVarBstrArray); } \
  NS_IMETHOD SetVarBstrArray(nsIVariant * aVarBstrArray) { return _to SetVarBstrArray(aVarBstrArray); } \
  NS_IMETHOD Write(void) { return _to Write(); } \
  NS_IMETHOD Change(const char *aValue) { return _to Change(aValue); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISIMPLE(_to) \
  NS_IMETHOD GetYourName(char * *aYourName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetYourName(aYourName); } \
  NS_IMETHOD SetYourName(const char * aYourName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetYourName(aYourName); } \
  NS_IMETHOD GetWideName(nsAString & aWideName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWideName(aWideName); } \
  NS_IMETHOD SetWideName(const nsAString & aWideName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetWideName(aWideName); } \
  NS_IMETHOD GetVarTest(nsIVariant * *aVarTest) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVarTest(aVarTest); } \
  NS_IMETHOD SetVarTest(nsIVariant * aVarTest) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetVarTest(aVarTest); } \
  NS_IMETHOD GetVarInt(nsIVariant * *aVarInt) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVarInt(aVarInt); } \
  NS_IMETHOD SetVarInt(nsIVariant * aVarInt) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetVarInt(aVarInt); } \
  NS_IMETHOD GetVarByteArray(nsIVariant * *aVarByteArray) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVarByteArray(aVarByteArray); } \
  NS_IMETHOD SetVarByteArray(nsIVariant * aVarByteArray) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetVarByteArray(aVarByteArray); } \
  NS_IMETHOD GetVarBstrArray(nsIVariant * *aVarBstrArray) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVarBstrArray(aVarBstrArray); } \
  NS_IMETHOD SetVarBstrArray(nsIVariant * aVarBstrArray) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetVarBstrArray(aVarBstrArray); } \
  NS_IMETHOD Write(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Write(); } \
  NS_IMETHOD Change(const char *aValue) { return !_to ? NS_ERROR_NULL_POINTER : _to->Change(aValue); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSimple : public nsISimple
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISIMPLE

  nsSimple();
  virtual ~nsSimple();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSimple, nsISimple)

nsSimple::nsSimple()
{
  /* member initializers and constructor code */
}

nsSimple::~nsSimple()
{
  /* destructor code */
}

/* attribute string yourName; */
NS_IMETHODIMP nsSimple::GetYourName(char * *aYourName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSimple::SetYourName(const char * aYourName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString wideName; */
NS_IMETHODIMP nsSimple::GetWideName(nsAString & aWideName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSimple::SetWideName(const nsAString & aWideName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIVariant varTest; */
NS_IMETHODIMP nsSimple::GetVarTest(nsIVariant * *aVarTest)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSimple::SetVarTest(nsIVariant * aVarTest)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIVariant varInt; */
NS_IMETHODIMP nsSimple::GetVarInt(nsIVariant * *aVarInt)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSimple::SetVarInt(nsIVariant * aVarInt)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIVariant varByteArray; */
NS_IMETHODIMP nsSimple::GetVarByteArray(nsIVariant * *aVarByteArray)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSimple::SetVarByteArray(nsIVariant * aVarByteArray)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIVariant varBstrArray; */
NS_IMETHODIMP nsSimple::GetVarBstrArray(nsIVariant * *aVarBstrArray)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsSimple::SetVarBstrArray(nsIVariant * aVarBstrArray)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void write (); */
NS_IMETHODIMP nsSimple::Write()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void change (in string aValue); */
NS_IMETHODIMP nsSimple::Change(const char *aValue)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsISimple_h__ */
