#include <iostream>
using namespace std;

#include "infomosaic_securexml_Signature.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef STRICT
#define STRICT
#endif

#ifdef WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#undef LINUX
#endif


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
#include <atlcom.h>
#include <atlwin.h>
#include <commctrl.h>
//#include <gdiplus.h>
#include <windows.h>

#endif

#include "infomosaic_securexml_Signature.h"
#include "Signature.h"

#ifndef WIN32
#include <securexml/CharConversion.h>
#else
/* dump a line (16 bytes) of memory, starting at pointer ptr for len
   bytes */
void ldump(char *ptr, unsigned int len);
/* Print out a header for a hex dump starting at address st. Each
   entry shows the least significant nybble of the address for that
   column. */
void head(long st);
/* Dump a region of memory, starting at ptr for ct bytes */
void dump(char *ptr, unsigned int ct);
#endif

#include "BufferVariant.h"

static BSTR jstring2bstr(JNIEnv *env, jstring str);

static jstring bstr2jstring(JNIEnv *env, BSTR bstr)
{
    jstring retStr = NULL;
    if (bstr != NULL)
    {
		retStr = env->NewString((const jchar *)bstr, SysStringLen(bstr));
    }
    return retStr;
}

static BSTR jstring2bstr(JNIEnv *env, jstring str) {
	BSTR bstr1=NULL;
	if (str!=NULL)
	{
		const jchar *c1 = env->GetStringChars(str, 0);
		CComBSTR tmpBstr = CComBSTR(c1);
		bstr1 = tmpBstr.Detach();
		env->ReleaseStringChars(str, c1);
	}
    return bstr1;
}

static VARIANT jbytearray2variant(JNIEnv *env, jbyteArray arr)
{
	jsize len = env->GetArrayLength(arr);
	jbyte *body = env->GetByteArrayElements(arr, 0);
	// Now lets convert it to Variant
	CBufferVariant m_binaryData;
	m_binaryData.AssignData((const void *)body, (long) len);
	env->ReleaseByteArrayElements(arr, body, 0);
	return m_binaryData.Copy();
}

static jbyteArray variant2jbytearray(JNIEnv *env, VARIANT arr)
{
	jbyteArray m_byteArray=NULL;
	CBufferVariant m_binaryData(arr);
	jsize arraySize = (jsize)m_binaryData.GetLength();
	m_byteArray = env->NewByteArray(arraySize);
	env->SetByteArrayRegion(m_byteArray, 0, arraySize, (jbyte *)(char *)m_binaryData);
	return m_byteArray;
}

static VARIANT jstringarray2variant(JNIEnv *env, jobjectArray arr)
{
	VARIANT *outVariant;
	SAFEARRAY *outArray;
	SAFEARRAYBOUND rgsabound[1];
	
	jsize len = env->GetArrayLength(arr);

	outVariant = (VARIANT *)zMalloc(sizeof(VARIANT));
	outArray = (SAFEARRAY *)zMalloc(sizeof(SAFEARRAY *));

	VariantInit(outVariant);

	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = len;

	outArray = SafeArrayCreate(VT_BSTR, 1, rgsabound);
	for (long i=0; i<(long)len; i++)
	{
		jstring s = (jstring)env->GetObjectArrayElement(arr, i);
		const jchar *str = env->GetStringChars(s, NULL);
		CComBSTR bs(str);
		BSTR bstr = bs.Detach();
		long x = i;
		SafeArrayPutElement(outArray,&x,bstr);
		env->ReleaseStringChars(s, str);
	}
	(*outVariant).vt = (VT_ARRAY | VT_BSTR);
	(*outVariant).parray = outArray;
	return *outVariant;
}

static jobjectArray variant2jstringarray(JNIEnv *env, VARIANT arr, CSignature *sig)
{
	jobjectArray m_stringArray=NULL;
	jsize arraySize = NULL;
	BSTR *bstrStringArr=NULL;
	bstrStringArr = sig->GetBstrArrayFromVariant(arr, (UINT *)&arraySize);
	m_stringArray = env->NewObjectArray(arraySize,env->FindClass("java/lang/String"),env->NewStringUTF(""));
	for (int i=0; i<arraySize; i++)
	{
		env->SetObjectArrayElement(m_stringArray,i,env->NewString((const jchar *)bstrStringArr[i], SysStringLen(bstrStringArr[i])));
		SysFreeString(bstrStringArr[i]);
	}
	zFree(bstrStringArr);
	return m_stringArray;
}


/*
 * Class:     infomosaic_securexml_Signature
 * Method:    createSignatureObject
 * Signature: ()V
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_createSignatureObject
  (JNIEnv *env, jobject _this)
{
   CSignature *sig = NULL;
   try {
    sig = new CSignature();
   }catch(SigException &e){
	printf("Exception: %s\n", e.what());
	return 0;
   }
	return (jint) sig;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    destroySignatureObject
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_destroySignatureObject
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	//DebugBreak();
    if (sigObjIndex==0) return;
    delete (CSignature *)sigObjIndex;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getEnvelopingFlag
 * Signature: ()S
 */
JNIEXPORT jshort JNICALL Java_infomosaic_securexml_Signature_CgetEnvelopingFlag
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
    if (sigObjIndex==0) return -1;
    jshort tmp = 0;
    CSignature *sig = (CSignature *) sigObjIndex;
    sig->get_EnvelopingFlag(&tmp);
    return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setEnvelopingFlag
 * Signature: (S)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetEnvelopingFlag
  (JNIEnv *env, jobject _this, jint sigObjIndex, jshort newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
    sig->put_EnvelopingFlag(newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getRecipientCertificateStore
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetRecipientCertificateStore
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
	BSTR recipientCertStore = NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	if (sig->get_RecipientCertificateStore(&recipientCertStore) == S_OK)
	{
		str = env->NewString((const jchar *)recipientCertStore, SysStringLen(recipientCertStore));
		SysFreeString(recipientCertStore);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setRecipientCertificateStore
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetRecipientCertificateStore
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring storeName)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstrStoreName = jstring2bstr(env, storeName);
	sig->put_RecipientCertificateStore(bstrStoreName);
	SysFreeString(bstrStoreName);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignerCertificate
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetSignerCertificate
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL;
	if (sig->get_SignerCertificate((long)sigIndex, &bstr) == S_OK)
	{
		if (bstr != NULL)
		{
			str = bstr2jstring(env, bstr);
			SysFreeString(bstr);
		}
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setSignerCertificate
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetSignerCertificate
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint index, jstring certData)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env, certData);
	sig->put_SignerCertificate(index, bstr);
	SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignatureID
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetSignatureID
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL;
	sig->get_SignatureID((long)sigIndex, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setSignatureID
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetSignatureID
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint position, jstring id)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
    BSTR bstrid = jstring2bstr(env,id);
    sig->put_SignatureID((long)position,(OLECHAR *)bstrid);
    if (bstrid) SysFreeString(bstrid);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getProperties
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetProperties
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex, jint propIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL;
	sig->get_Properties((long)sigIndex, (long) propIndex, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setProperties
 * Signature: (IILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetProperties
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex, jint propIndex, jstring propVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
    BSTR bstr = jstring2bstr(env, propVal);
    sig->put_Properties((long)sigIndex,(long)propIndex,bstr);
    if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getBase64EncodeXML
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetBase64EncodeXML
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return 0;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal = 0;
	sig->get_Base64EncodeXML(&retVal);
	tmp = (jint) retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setBase64EncodeXML
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetBase64EncodeXML
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_Base64EncodeXML((BOOL)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getBase64DecodeXML
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetBase64DecodeXML
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return 0;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal = 0;
	sig->get_Base64DecodeXML(&retVal);
	tmp = (jint) retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setBase64DecodeXML
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetBase64DecodeXML
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_Base64DecodeXML((BOOL)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getDocumentURI
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetDocumentURI
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex, jint refIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL;
	sig->get_DocumentURI((long)sigIndex, (long) refIndex, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getDigestObjectStatus
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetDigestObjectStatus
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex, jint refIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return 0;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal = 0;
	sig->get_DigestObjectStatus((long)sigIndex, (long)refIndex, &retVal);
	tmp = (jint) retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getLanguage
 * Signature: ()I
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetLanguage
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL;
	sig->get_Language(&bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setLogLevel
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetLanguage
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
    BSTR bstr = jstring2bstr(env, newVal);
    sig->put_Language(bstr);
    if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignatureStatus
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetSignatureStatus
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return 0;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal = 0;
	sig->get_SignatureStatus((long)sigIndex,&retVal);
	tmp = (jint) retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getPhysicalSignatureUsage
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetPhysicalSignatureUsage
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return 0;
    CSignature *sig = (CSignature *) sigObjIndex;
	long retVal = 0;
	sig->get_PhysicalSignatureUsage(&retVal);
	tmp = (jint) retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setPhysicalSignatureUsage
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetPhysicalSignatureUsage
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_PhysicalSignatureUsage((long) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getPhysicalSignatureFile
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetPhysicalSignatureFile
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL;
	sig->get_PhysicalSignatureFile(&bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setPhysicalSignatureFile
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetPhysicalSignatureFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring filePath)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
    BSTR bstr = jstring2bstr(env, filePath);
    sig->put_PhysicalSignatureFile(bstr);
    if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCapturedSignatureFile
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetCapturedSignatureFile
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL;
	sig->get_CapturedSignatureFile(&bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    sign
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_Csign
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring uri)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
    BSTR bstr = jstring2bstr(env,uri);
    BSTR retval=NULL;
    sig->Sign((OLECHAR *) bstr, (OLECHAR **)&retval);
	if (retval) {
		str = env->NewString((const jchar *)retval, SysStringLen(retval));
		SysFreeString(retval);
	}
	if (bstr) SysFreeString(bstr);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getIncludeCamResponse
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetIncludeCamResponse
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return 0;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal = 0;
	sig->get_IncludeCamResponse(&retVal);
	tmp = (jint) retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setIncludeCamResponse
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetIncludeCamResponse
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_IncludeCamResponse((BOOL) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    saveXMLSignature
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsaveXMLSignature
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring filePath)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
    BSTR bstrUri = jstring2bstr(env,filePath);
    sig->SaveXMLSignature(bstrUri);
    if (bstrUri) SysFreeString(bstrUri);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    verify
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_Cverify
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring uri)
{
    if (sigObjIndex==0) return 0;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstrUri = jstring2bstr(env,uri);
	BOOL retVal;
	sig->Verify((OLECHAR *)bstrUri, &retVal);
	if (bstrUri) SysFreeString(bstrUri);
	return retVal;
}

/*

 * Class:     infomosaic_securexml_Signature
 * Method:    getError
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetError
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	BSTR bstrError=NULL;
	jstring retStr=NULL;
    if (sigObjIndex==0) return retStr;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->GetError((OLECHAR **)&bstrError);
	if (bstrError) {
		retStr = env->NewString((const jchar *)bstrError, SysStringLen(bstrError));
		SysFreeString(bstrError);
	}
	return retStr;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setOverwriteFile
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetOverwriteFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
    sig->put_OverwriteFile(newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    pFXExportCertificate
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CpFXExportCertificate
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring certID, jstring password)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL, bstr1=NULL, bstr2=NULL;
	bstr1 = jstring2bstr(env, certID);
	bstr2 = jstring2bstr(env, password);
	sig->PFXExportCertificate(bstr1, bstr2, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	SysFreeString(bstr1);
	SysFreeString(bstr2);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    verifyDetached
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CverifyDetached
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring uri)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,uri);
	BOOL rval =0;
	sig->VerifyDetached(bstr,&rval);
	if (bstr) SysFreeString(bstr);
	tmp = rval;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getLastError
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetLastError
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
    jint tmp = 0;
    if (sigObjIndex==0) return -1;
    CSignature *sig = (CSignature *) sigObjIndex;
    sig->GetLastError((long *)&tmp);
    return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getX509Certificate
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetX509Certificate
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring certID)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL;
	BSTR bstr1 = jstring2bstr(env, certID);
	sig->GetX509Certificate(bstr1, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    viewCertificate
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CviewCertificate
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring certID)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env, certID);
	sig->ViewCertificate(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCertificateCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetCertificateCount
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
    jint tmp = 0;
    if (sigObjIndex==0) return -1;
    CSignature *sig = (CSignature *) sigObjIndex;
    sig->get_CertificateCount((long *)&tmp);
    return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCertificateInfo
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetCertificateInfo
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint certIndex, jint valIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL;
	sig->GetCertificateInfo((long)certIndex, (long) valIndex, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setActiveCertificate
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CsetActiveCertificate
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring certID)
{
	jint tmp=0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env, certID);
	BOOL retVal=0;
	sig->SetActiveCertificate(bstr, &retVal);
	if (bstr) SysFreeString(bstr);
	tmp = retVal;
	return tmp;

}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignedDocumentPath
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetSignedDocumentPath
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex, jint uriIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL;
	sig->get_SignedDocumentPath((long)sigIndex, (long) uriIndex, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignerSubject
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetSignerSubject
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring sigId)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL, bstr1=NULL;
	bstr1 = jstring2bstr(env, sigId);
	sig->get_SignerSubject(bstr1, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	if (bstr1)
		SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCertIssuer
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetCertIssuer
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring sigId)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL, bstr1=NULL;
	bstr1 = jstring2bstr(env, sigId);
	sig->get_CertIssuer(bstr1, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	if (bstr1)
		SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCertExpiry
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetCertExpiry
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring sigId)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL, bstr1=NULL;
	bstr1 = jstring2bstr(env, sigId);
	sig->get_CertExpiry(bstr1, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	if (bstr1)
		SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCertSerialNumber
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetCertSerialNumber
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring sigId)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL, bstr1=NULL;
	bstr1 = jstring2bstr(env, sigId);
	sig->get_CertSerialNumber(bstr1, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	if (bstr1)
		SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    fileExists
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CfileExists
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring filePath)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal=0;
	BSTR bstr = jstring2bstr(env, filePath);
	sig->FileExists(bstr, &retVal);
	tmp = (jint)retVal;
	if (bstr) SysFreeString(bstr);
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getFailedUriCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetFailedUriCount
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	long retVal=0;
	sig->get_FailedUriCount(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getTotalUriCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetTotalUriCount
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	long retVal=0;
	sig->get_TotalUriCount(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getFailedUriFullPath
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetFailedUriFullPath
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint index)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL;
	sig->get_FailedUriFullPath((long)index, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setFailedUriFullPath
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetFailedUriFullPath
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint index, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);

	sig->put_FailedUriFullPath((long)index,bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getFailedUri
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetFailedUri
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint index)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL;
	sig->get_FailedUri((long)index, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignatureCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetSignatureCount
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	long retVal=0;
	sig->get_SignatureCount(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    signXMLStr
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsignXMLStr
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring xmlStr, jstring signatureId)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR b1 = jstring2bstr(env,xmlStr);
	BSTR b2 = jstring2bstr(env,signatureId);
	BSTR retVal= NULL;
	sig->SignXMLStr(b1,b2,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (b1) SysFreeString(b1);
	if (b2) SysFreeString(b2);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    readAll
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CreadAll
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring filePath)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr=NULL, bstr1=NULL;
	bstr1 = jstring2bstr(env, filePath);
	sig->ReadAll(bstr1, &bstr);
	if (bstr) {
		str = bstr2jstring(env, bstr);
		SysFreeString(bstr);
	}
	if (bstr1)
		SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    saveXMLStr
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsaveXMLStr
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring inputXmlStr, jstring filePath)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	BSTR bstr1 = jstring2bstr(env,inputXmlStr);
	BSTR bstr2 = jstring2bstr(env,filePath);
	sig->SaveXMLStr(bstr1,bstr2,&retVal);
	if (bstr1) SysFreeString(bstr1);
	if (bstr2) SysFreeString(bstr2);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    signHTML
 * Signature: (Ljava/lang/Object;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsignHTML
  (JNIEnv *env, jobject _this, jint sigObjIndex, jobject document)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
 //   CSignature *sig = (CSignature *) sigObjIndex;
	//BSTR retVal = NULL;
	//sig->SignHTML((IDispatch *)document,&retVal);
	//if (retVal) {
	//	str = bstr2jstring(env,retVal);
	//	SysFreeString(retVal);
	//}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    secureXMLVerify
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsecureXMLVerify
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring signedXml)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	BSTR bstr = jstring2bstr(env,signedXml);
	sig->SecureXMLVerify(bstr,&retVal);
	if (bstr) SysFreeString(bstr);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCSP
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCSP
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring cspName)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,cspName);
	sig->SetCSP(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignedHTML
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetSignedHTML
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring signedHtmlXML)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	BSTR bstr = jstring2bstr(env,signedHtmlXML);
	sig->GetSignedHTML(bstr,&retVal);
	if (bstr) SysFreeString(bstr);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    signFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsignFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring inputFile, jstring outputFile)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr1 = jstring2bstr(env,inputFile);
	BSTR bstr2 = jstring2bstr(env,outputFile);
	sig->SignFile(bstr1,bstr2);
	if (bstr1) SysFreeString(bstr1);
	if (bstr2) SysFreeString(bstr2);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignedFileObject
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetSignedFileObject
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring signedXML, jstring saveDir)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	BSTR bstr = jstring2bstr(env,signedXML);
	BSTR bstr1 = jstring2bstr(env, saveDir);
	sig->GetSignedFileObject(bstr,bstr1,&retVal);
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setStoreName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetStoreName
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring storeName)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
    BSTR bstr1 = jstring2bstr(env,storeName);
    sig->SetStoreName((OLECHAR *)bstr1);
    if (bstr1) SysFreeString(bstr1);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getStoreName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetStoreName
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->GetStoreName(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    signXMLEnveloped
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsignXMLEnveloped
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring inputXML, jstring sigId)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	BSTR bstr1 = jstring2bstr(env,inputXML);
	BSTR bstr2 = jstring2bstr(env,sigId);
	sig->SignXMLEnveloped(bstr1,bstr2,&retVal);
	if (bstr1) SysFreeString(bstr1);
	if (bstr2) SysFreeString(bstr2);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getVersion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetVersion
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->GetVersion(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getLicenseStatus
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetLicenseStatus
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	long retVal=0;
	sig->GetLicenseStatus(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getPropertyCount
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetPropertyCount
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	long retVal=0;
	sig->GetPropertyCount((long)sigIndex, &retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    viewAnyCertificate
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CviewAnyCertificate
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring inputX509Data)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,inputX509Data);
	sig->ViewAnyCertificate(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    selectActiveCertificate
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CselectActiveCertificate
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->SelectActiveCertificate(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    verifyXMLStr
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CverifyXMLStr
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring signedXML)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal=0;
	BSTR bstr = jstring2bstr(env, signedXML);
	sig->VerifyXMLStr(bstr, &retVal);
	tmp = (jint)retVal;
	if (bstr) SysFreeString(bstr);
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setActivePFXFileCert
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsetActivePFXFileCert
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring pfxFileName, jstring pfxPassword)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
    BSTR ret = NULL; 

    BSTR bstr1 = jstring2bstr(env,pfxFileName);
    BSTR bstr2 = jstring2bstr(env,pfxPassword);

    sig->SetActivePFXFileCert((OLECHAR *)bstr1,(OLECHAR *)bstr2,(OLECHAR **)&ret);
	if (ret) {
		str = env->NewString((const jchar *)ret, SysStringLen(ret));
		SysFreeString(ret);
	}
    if (bstr1) SysFreeString(bstr1);
    if (bstr2) SysFreeString(bstr2);
	
    return str; 

}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    pFXExportActiveCertificate
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CpFXExportActiveCertificate
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring password)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	BSTR bstr1 = jstring2bstr(env,password);
	sig->PFXExportActiveCertificate(bstr1,&retVal);
	if (bstr1) SysFreeString(bstr1);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getHostName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetHostName
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->get_HostName(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getTimeStampURL
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetTimeStampURL
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->get_TimeStampURL(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setTimeStampURL
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetTimeStampURL
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_TimeStampURL(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getTimeStamping
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetTimeStamping
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal=0;
	sig->get_TimeStamping(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setTimeStamping
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetTimeStamping
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_TimeStamping((BOOL)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getHostOsType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetHostOsType
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	long retVal=0;
	sig->get_HostOsType(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCrlChecking
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetCrlChecking
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal=0;
	sig->get_CrlChecking(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCrlChecking
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCrlChecking
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_CrlChecking((BOOL)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSigCertStatus
 * Signature: (ILjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetSigCertStatus
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex, jstring atTime, jint timeFormat)
{
 if (sigObjIndex==0) return 0;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstrAtTime=NULL;
	if (atTime)
		bstrAtTime = jstring2bstr(env, atTime);
	long retVal;
	sig->get_SigCertStatus(sigIndex, (OLECHAR *)bstrAtTime, timeFormat, &retVal);
	
	if (bstrAtTime) SysFreeString(bstrAtTime);
	return retVal;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    verifyX509CertCRL
 * Signature: (Ljava/lang/String;Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CverifyX509CertCRL
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring certData, jstring atTime, jint timeFormat)
{
	jint tmp = 0;
	if (sigObjIndex==0) return 0;
    CSignature *sig = (CSignature *) sigObjIndex;

	BOOL retVal = FALSE;
	BSTR b1 = jstring2bstr(env,certData);
	BSTR b2 = jstring2bstr(env,atTime);
	sig->VerifyX509CertCRL(b1,b2,(long)timeFormat,&retVal);

	if (b1) SysFreeString(b1);
	if (b2) SysFreeString(b2);
	tmp =retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    verifyPFXCertCRL
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CverifyPFXCertCRL
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring pfxFileName, jstring pfxPassword, jstring atTime, jint timeFormat)
{
	jint tmp = 0;
	if (sigObjIndex==0) return 0;
    CSignature *sig = (CSignature *) sigObjIndex;

	BOOL retVal = FALSE;
	BSTR b1 = jstring2bstr(env,pfxFileName);
	BSTR b2 = jstring2bstr(env,pfxPassword);
	BSTR b3 = jstring2bstr(env,atTime);
	sig->VerifyPFXCertCRL(b1,b2,b3,(long)timeFormat,&retVal);
	if (b1) SysFreeString(b1);
	if (b2) SysFreeString(b2);
	if (b3) SysFreeString(b3);
	tmp =retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getAddWindowImage
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetAddWindowImage
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal=0;
	sig->get_AddWindowImage(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setAddWindowImage
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetAddWindowImage
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_AddWindowImage((BOOL) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCRLLocation
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCRLLocation
  (JNIEnv *env, jobject _this, jint sigObjIndex, jobjectArray newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v = jstringarray2variant(env,newVal);
	sig->put_CRLLocation(v);
	VariantClear(&v);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    verifyActiveCertificate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CverifyActiveCertificate
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal=0;
	sig->VerifyActiveCertificate(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCertificatePolicy
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCertificatePolicy
  (JNIEnv *env, jobject _this, jint sigObjIndex, jobjectArray newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v = jstringarray2variant(env,newVal);
	sig->put_CertificatePolicy(v);
	VariantClear(&v);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getAuthorityConstrainedPolicy
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_infomosaic_securexml_Signature_CgetAuthorityConstrainedPolicy
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jobjectArray tmp=NULL;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v;
	VariantInit(&v);
	sig->get_AuthorityConstrainedPolicy(&v);
	tmp = variant2jstringarray(env, v, sig);
	VariantClear(&v);
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getUserConstrainedPolicy
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_infomosaic_securexml_Signature_CgetUserConstrainedPolicy
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jobjectArray tmp=NULL;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v;
	VariantInit(&v);
	sig->get_UserConstrainedPolicy(&v);
	tmp = variant2jstringarray(env, v, sig);
	VariantClear(&v);
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCertificatePolicyChecking
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCertificatePolicyChecking
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_CertificatePolicyChecking((BOOL) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCertificateChainValidation
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCertificateChainValidation
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_CertificateChainValidation((BOOL) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCertificatePathLengthChecking
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCertificatePathLengthChecking
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_CertificatePathLengthChecking((BOOL) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setConfigFileName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetConfigFileName
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_ConfigFileName(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setDoDCompliance
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetDoDCompliance
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_DoDCompliance((BOOL) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCertificatePolicyExplicit
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetCertificatePolicyExplicit
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal=0;
	sig->get_CertificatePolicyExplicit(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCertificatePolicyExplicit
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCertificatePolicyExplicit
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_CertificatePolicyExplicit((BOOL) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCertificateTrustExplicit
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCertificateTrustExplicit
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_CertificateTrustExplicit((BOOL) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    signXMLXpathStr
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsignXMLXpathStr
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring xmlStr, jstring xpathExp, jstring signatureId)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;

	BSTR b1 = jstring2bstr(env,xmlStr);
	BSTR b2 = jstring2bstr(env,xpathExp);
	BSTR b3 = jstring2bstr(env,signatureId);
	BSTR retVal =NULL;

	sig->SignXMLXpathStr(b1,b2,b3,&retVal);

	if (b1) SysFreeString(b1);
	if (b2) SysFreeString(b2);
	if (b3) SysFreeString(b3);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}

	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getUseHMAC
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetUseHMAC
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal=0;
	sig->get_UseHMAC(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setUseHMAC
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetUseHMAC
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_UseHMAC((BOOL) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getHMACPassword
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetHMACPassword
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->get_HMACPassword(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setHMACPassword
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetHMACPassword
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_HMACPassword(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    changeOrAddProperty
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CchangeOrAddProperty
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring propertyName, jstring propertyValue)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr1 = jstring2bstr(env,propertyName);
	BSTR bstr2 = jstring2bstr(env,propertyValue);
	sig->ChangeOrAddProperty(bstr1, bstr2);
	if (bstr1) SysFreeString(bstr1);
	if (bstr2) SysFreeString(bstr2);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setDetailedVerificationFlag
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetDetailedVerificationFlag
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_DetailedVerificationFlag(newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    captureLiveSignature
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CcaptureLiveSignature
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->CaptureLiveSignature(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    signDataStr
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsignDataStr
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring dataStr)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,dataStr);
	BSTR retVal= NULL;
	sig->SignDataStr(bstr,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setExcludeSignerCertificate
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetExcludeSignerCertificate
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_ExcludeSignerCertificate((BOOL)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    coSignXMLStr
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CcoSignXMLStr
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring signedDataXMLStr)
{
	jstring str=NULL;

    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR b1 = jstring2bstr(env,signedDataXMLStr);
	BSTR retVal= NULL;
	sig->CoSignXMLStr(b1, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (b1) SysFreeString(b1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    coSignFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CcoSignFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring inputSignedXMLFile, jstring outFileName)
{
	jstring str=NULL;

    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR b1 = jstring2bstr(env,inputSignedXMLFile);
	BSTR b2 = jstring2bstr(env,outFileName);
	BSTR retVal= NULL;
	sig->CoSignFile(b1,b2, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (b1) SysFreeString(b1);
	if (b2) SysFreeString(b2);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    signFiles
 * Signature: ([Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsignFiles
  (JNIEnv *env, jobject _this, jint sigObjIndex, jobjectArray fileList, jstring outFileName)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v = jstringarray2variant(env,fileList);
	BSTR bstr = jstring2bstr(env,outFileName);
	BSTR retVal =NULL;
	sig->SignFiles(v,bstr,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	VariantClear(&v);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setRecipientCertificates
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetRecipientCertificates
  (JNIEnv *env, jobject _this, jint sigObjIndex, jobjectArray newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v = jstringarray2variant(env,newVal);
	sig->put_RecipientCertificates(v);
	VariantClear(&v);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    encryptStr
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CencryptStr
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring inputStr)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,inputStr);
	BSTR retVal =NULL;
	sig->EncryptStr(bstr,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    decryptStr
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CdecryptStr
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring cipherText)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,cipherText);
	BSTR retVal =NULL;
	sig->DecryptStr(bstr,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    encryptFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CencryptFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring inputFile, jstring outputFile)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,inputFile);
	BSTR bstr1 = jstring2bstr(env,outputFile);
	BSTR retVal =NULL;
	sig->EncryptFile(bstr,bstr1,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    decryptFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CdecryptFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring inputFile, jstring outputFile)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,inputFile);
	BSTR bstr1 = jstring2bstr(env,outputFile);
	BSTR retVal =NULL;
	sig->DecryptFile(bstr,bstr1,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setTrustedRoots
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetTrustedRoots
  (JNIEnv *env, jobject _this, jint sigObjIndex, jobjectArray newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v = jstringarray2variant(env,newVal);
	sig->put_TrustedRoots(v);
	VariantClear(&v);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setRecipientCertificateFiles
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetRecipientCertificateFiles
  (JNIEnv *env, jobject _this, jint sigObjIndex, jobjectArray newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v = jstringarray2variant(env,newVal);
	sig->put_RecipientCertificateFiles(v);
	VariantClear(&v);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setDetachedObjects
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetDetachedObjects
  (JNIEnv *env, jobject _this, jint sigObjIndex, jobjectArray newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v = jstringarray2variant(env,newVal);
	sig->put_DetachedObjects(v);
	VariantClear(&v);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setAttachedObjects
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetAttachedObjects
  (JNIEnv *env, jobject _this, jint sigObjIndex, jobjectArray newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v = jstringarray2variant(env,newVal);
	sig->put_AttachedObjects(v);
	VariantClear(&v);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    readAllBase64
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CreadAllBase64
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring uri)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,uri);
	BSTR retVal =NULL;
	sig->ReadAllBase64(bstr,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setDecryptionPFXCertFile
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetDecryptionPFXCertFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_DecryptionPFXCertFile(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setDecryptUsingPFXFileCert
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetDecryptUsingPFXFileCert
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_DecryptUsingPFXFileCert((BOOL)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setDecryptionPFXPassword
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetDecryptionPFXPassword
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_DecryptionPFXPassword(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setXpathNamespace
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetXpathNamespace
  (JNIEnv *env, jobject _this, jint sigObjIndex, jobjectArray newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v = jstringarray2variant(env,newVal);
	sig->put_XpathNamespace(v);
	VariantClear(&v);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCamServerHost
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetCamServerHost
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal =NULL;
	sig->get_CamServerHost(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCamServerHost
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCamServerHost
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_CamServerHost(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCamServerPort
 * Signature: ()S
 */
JNIEXPORT jshort JNICALL Java_infomosaic_securexml_Signature_CgetCamServerPort
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jshort tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	USHORT retVal=0;
	sig->get_CamServerPort(&retVal);
	tmp = (jshort)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCamServerPort
 * Signature: (S)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCamServerPort
  (JNIEnv *env, jobject _this, jint sigObjIndex, jshort newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_CamServerPort((USHORT) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getUseCam
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetUseCam
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal=0;
	sig->get_UseCam(&retVal);
	tmp = (jint) retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setUseCam
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetUseCam
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_UseCam((BOOL) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getAgencyId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetAgencyId
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal =NULL;
	sig->get_AgencyId(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setAgencyId
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetAgencyId
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_AgencyId(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCamValidationResponse
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetCamValidationResponse
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal =NULL;
	sig->get_CamValidationResponse(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSigPropValueByName
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetSigPropValueByName
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex, jstring propertyName)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,propertyName);
	BSTR retVal =NULL;
	sig->GetSigPropValueByName((long) sigIndex, bstr, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    base64DecodeBufferToFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_Cbase64DecodeBufferToFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring encodedBuffer, jstring outFilePath)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,encodedBuffer);
	BSTR bstr1 = jstring2bstr(env,outFilePath);
	BSTR retVal =NULL;
	sig->Base64DecodeBufferToFile(bstr,bstr1,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    base64DecodeFileToFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_Cbase64DecodeFileToFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring encodedFilePath, jstring outFilePath)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,encodedFilePath);
	BSTR bstr1 = jstring2bstr(env,outFilePath);
	BSTR retVal =NULL;
	sig->Base64DecodeFileToFile(bstr,bstr1,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    gunZipFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgunZipFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring gZippedFile, jstring gUnZippedFile)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,gZippedFile);
	BSTR bstr1 = jstring2bstr(env,gUnZippedFile);
	BSTR retVal =NULL;
	sig->GunZipFile(bstr,bstr1,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCertSerialNumberFormat
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetCertSerialNumberFormat
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	long retVal=0;
	sig->get_CertSerialNumberFormat(&retVal);
	tmp = (jint) retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCertSerialNumberFormat
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCertSerialNumberFormat
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_CertSerialNumberFormat((long)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    secureXMLVerifyFileToBuffer
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsecureXMLVerifyFileToBuffer
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring signedXMLFile)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,signedXMLFile);
	BSTR retVal =NULL;
	sig->SecureXMLVerifyFileToBuffer(bstr,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    secureXMLVerifyFileToFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsecureXMLVerifyFileToFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring signedXMLFile, jstring outFilePath)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,signedXMLFile);
	BSTR bstr1 = jstring2bstr(env,outFilePath);
	BSTR retVal =NULL;
	sig->SecureXMLVerifyFileToFile(bstr, bstr1, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    deleteSignatureFromXMLStr
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CdeleteSignatureFromXMLStr
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring signedXMLStr, jstring sigId)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,signedXMLStr);
	BSTR bstr1 = jstring2bstr(env,sigId);
	BSTR retVal =NULL;
	sig->DeleteSignatureFromXMLStr(bstr, bstr1, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    deleteSignatureFromFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CdeleteSignatureFromFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring signedXMLFile, jstring sigId, jstring outFilePath)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,signedXMLFile);
	BSTR bstr1 = jstring2bstr(env,sigId);
	BSTR bstr2 = jstring2bstr(env,outFilePath);
	BSTR retVal =NULL;
	sig->DeleteSignatureFromFile(bstr, bstr1,bstr2, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	if (bstr2) SysFreeString(bstr2);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setAllowedCertIssuerNames
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetAllowedCertIssuerNames
  (JNIEnv *env, jobject _this, jint sigObjIndex, jobjectArray newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v = jstringarray2variant(env,newVal);
	sig->put_AllowedCertIssuerNames(v);
	VariantClear(&v);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCRLCacheDbConnectionString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetCRLCacheDbConnectionString
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal =NULL;
	sig->get_CRLCacheDbConnectionString(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCRLCacheDbConnectionString
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCRLCacheDbConnectionString
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_AgencyId(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getUseCRLCache
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetUseCRLCache
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal=0;
	sig->get_UseCRLCache(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setUseCRLCache
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetUseCRLCache
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_UseCRLCache((BOOL)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCRLCacheTimeoutInMinutes
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCRLCacheTimeoutInMinutes
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_CRLCacheTimeoutInMinutes((ULONG)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCanonicalizationMethod
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCanonicalizationMethod
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_CanonicalizationMethod((ULONG) newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getNetscapeStorePassword
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetNetscapeStorePassword
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal =NULL;
	sig->get_NetscapeStorePassword(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setNetscapeStorePassword
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetNetscapeStorePassword
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;

    BSTR bstr1 = jstring2bstr(env, newVal);

    sig->put_NetscapeStorePassword((OLECHAR *)bstr1);

    if (bstr1) SysFreeString(bstr1);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setActivePEMFileCert
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsetActivePEMFileCert
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring pemFileName, jstring pemPassword)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
#ifdef WIN32
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,pemFileName);
	BSTR bstr1 = jstring2bstr(env,pemPassword);
	BSTR retVal =NULL;
	sig->SetActivePEMFileCert(bstr, bstr1, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
#endif
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSecureXMLPath
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetSecureXMLPath
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal =NULL;
	sig->get_SecureXMLPath(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignedDocumentCount
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetSignedDocumentCount
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	LONG retVal=0;
	sig->get_SignedDocumentCount((long)sigIndex, &retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    signXMLByteArray
 * Signature: ([BLjava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_Signature_CsignXMLByteArray
  (JNIEnv *env, jobject _this, jint sigObjIndex, jbyteArray xmlByteArray, jstring signatureId)
{
	jbyteArray tmp=NULL;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v1 = jbytearray2variant(env,xmlByteArray);
	BSTR b1 = jstring2bstr(env,signatureId);
	VARIANT retVal;
	VariantInit(&retVal);
	sig->SignXMLByteArray(v1,b1,&retVal);

	if (b1) SysFreeString(b1);
	VariantClear(&v1);
	tmp = variant2jbytearray(env,retVal);
	VariantClear(&retVal);

	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    saveXMLByteArray
 * Signature: ([BLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsaveXMLByteArray
  (JNIEnv *env, jobject _this, jint sigObjIndex, jbyteArray xmlByteArray, jstring outFilePath)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v1 = jbytearray2variant(env,xmlByteArray);
	BSTR b1 = jstring2bstr(env,outFilePath);
	BSTR retVal = NULL;
	sig->SaveXMLByteArray(v1,b1,&retVal);
	if (b1) SysFreeString(b1);
	VariantClear(&v1);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    readAllByteArray
 * Signature: (Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_Signature_CreadAllByteArray
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring fileName)
{
	jbyteArray tmp=NULL;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT retVal;
	VariantInit(&retVal);
	BSTR b1 = jstring2bstr(env,fileName);
	sig->ReadAllByteArray(b1,&retVal);
	tmp = variant2jbytearray(env,retVal);
	if (b1) SysFreeString(b1);
	VariantClear(&retVal);
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    verifyXMLByteArray
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CverifyXMLByteArray
  (JNIEnv *env, jobject _this, jint sigObjIndex, jbyteArray signedXmlByteArray)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v1 = jbytearray2variant(env,signedXmlByteArray);
	BOOL retVal = 0;
	sig->VerifyXMLByteArray(v1,&retVal);
	VariantClear(&v1);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    secureXMLVerifyByteArray
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_Signature_CsecureXMLVerifyByteArray
  (JNIEnv *env, jobject _this, jint sigObjIndex, jbyteArray signedXmlByteArray)
{
	jbyteArray tmp=NULL;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v1 = jbytearray2variant(env,signedXmlByteArray);
	VARIANT retVal;
	VariantInit(&retVal);
	sig->SecureXMLVerifyByteArray(v1,&retVal);
	VariantClear(&v1);
	tmp = variant2jbytearray(env,retVal);
	VariantClear(&retVal);

	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    signXMLXpathByteArray
 * Signature: ([BLjava/lang/String;Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_Signature_CsignXMLXpathByteArray
  (JNIEnv *env, jobject _this, jint sigObjIndex, jbyteArray inputXmlByteArray, jstring xpathExp, jstring signatureId)
{
	jbyteArray tmp=NULL;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;

	VARIANT retVal;
	VariantInit(&retVal);
	VARIANT v1 = jbytearray2variant(env,inputXmlByteArray);
	BSTR b1 = jstring2bstr(env,xpathExp);
	BSTR b2 = jstring2bstr(env,signatureId);

	sig->SignXMLXpathByteArray(v1,b1,b2,&retVal);
	tmp = variant2jbytearray(env,retVal);
	if (b1) SysFreeString(b1);
	if (b2) SysFreeString(b2);
	VariantClear(&v1);
	VariantClear(&retVal);

	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    signXMLEnvelopedByteArray
 * Signature: ([BLjava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_Signature_CsignXMLEnvelopedByteArray
  (JNIEnv *env, jobject _this, jint sigObjIndex, jbyteArray inputXmlByteArray, jstring sigId)
{
	jbyteArray tmp=NULL;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;

	VARIANT retVal;
	VariantInit(&retVal);
	VARIANT v1 = jbytearray2variant(env,inputXmlByteArray);
	BSTR b1 = jstring2bstr(env,sigId);

	sig->SignXMLEnvelopedByteArray(v1,b1,&retVal);
	tmp = variant2jbytearray(env,retVal);
	if (b1) SysFreeString(b1);
	VariantClear(&v1);
	VariantClear(&retVal);

	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    base64DecodeByteArrayToFile
 * Signature: ([BLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_Cbase64DecodeByteArrayToFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jbyteArray encodedBuffer, jstring outFilePath)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v1 = jbytearray2variant(env,encodedBuffer);
	BSTR b1 = jstring2bstr(env,outFilePath);
	BSTR retVal = NULL;
	sig->Base64DecodeByteArrayToFile(v1,b1,&retVal);
	if (b1) SysFreeString(b1);
	VariantClear(&v1);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    base64DecodeByteArrayToByteArray
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_Signature_Cbase64DecodeByteArrayToByteArray
  (JNIEnv *env, jobject _this, jint sigObjIndex, jbyteArray encodedBuffer)
{
	jbyteArray tmp=NULL;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;

	VARIANT retVal;
	VariantInit(&retVal);
	VARIANT v1 = jbytearray2variant(env,encodedBuffer);
	sig->Base64DecodeByteArrayToByteArray(v1,&retVal);
	tmp = variant2jbytearray(env,retVal);
	VariantClear(&v1);
	VariantClear(&retVal);

	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    base64EncodeByteArrayToByteArray
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_Signature_Cbase64EncodeByteArrayToByteArray
  (JNIEnv *env, jobject _this, jint sigObjIndex, jbyteArray inputBinary)
{
	jbyteArray tmp=NULL;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;

	VARIANT retVal;
	VariantInit(&retVal);
	VARIANT v1 = jbytearray2variant(env,inputBinary);
	sig->Base64EncodeByteArrayToByteArray(v1,&retVal);
	tmp = variant2jbytearray(env,retVal);
	VariantClear(&v1);
	VariantClear(&retVal);

	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    base64EncodeByteArrayToFile
 * Signature: ([BLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_Cbase64EncodeByteArrayToFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jbyteArray inputBinary, jstring outFilePath)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v1 = jbytearray2variant(env,inputBinary);
	BSTR b1 = jstring2bstr(env,outFilePath);
	BSTR retVal = NULL;
	sig->Base64EncodeByteArrayToFile(v1,b1,&retVal);
	if (b1) SysFreeString(b1);
	VariantClear(&v1);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    base64EncodeStrToFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_Cbase64EncodeStrToFile
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring inputStr, jstring outFilePath)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,inputStr);
	BSTR bstr1 = jstring2bstr(env,outFilePath);
	BSTR retVal =NULL;
	sig->Base64EncodeStrToFile(bstr, bstr1, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    base64EncodeStrToStr
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_Cbase64EncodeStrToStr
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring inputStr)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,inputStr);
	BSTR retVal =NULL;
	sig->Base64EncodeStrToStr(bstr, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setActivePFXB64Data
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsetActivePFXB64Data
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring b64PfxData, jstring pfxPassword)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,b64PfxData);
	BSTR bstr1 = jstring2bstr(env,pfxPassword);
	BSTR retVal =NULL;
	sig->SetActivePFXB64Data(bstr, bstr1, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    CgetFloatingLicense
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetFloatingLicense
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return NULL;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = NULL;
	sig->get_FloatingLicense(&bstr);
	if (bstr != NULL)
	{
		str = bstr2jstring(env,bstr);
		SysFreeString(bstr);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setFloatingLicense
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetFloatingLicense
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_FloatingLicense(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getLicensedUserCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetLicensedUserCount
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	LONG retVal=0;
	sig->get_LicensedUserCount(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setIncludeCRLInSignature
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetIncludeCRLInSignature
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_IncludeCRLInSignature((BOOL)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getUsedCRLList
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_infomosaic_securexml_Signature_CgetUsedCRLList
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jobjectArray tmp=NULL;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;

	VARIANT retVal;
	VariantInit(&retVal);
	sig->get_UsedCRLList(&retVal);
	tmp = variant2jstringarray(env,retVal, sig);
	VariantClear(&retVal);

	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getErrorDetail
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetErrorDetail
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint errorNum)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal =NULL;
	sig->GetErrorDetail((LONG)errorNum, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setPhysicalSignatureB64Str
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetPhysicalSignatureB64Str
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_PhysicalSignatureB64Str(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignedInfoDigest
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetSignedInfoDigest
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring xmlStr, jstring signatureId)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,xmlStr);
	BSTR bstr1 = jstring2bstr(env,signatureId);
	BSTR retVal =NULL;
	sig->GetSignedInfoDigest(bstr, bstr1, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getX509CertificateChain
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetX509CertificateChain
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring certID)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,certID);
	BSTR retVal =NULL;
	sig->GetX509CertificateChain(bstr, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setSignerCertificateChain
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetSignerCertificateChain
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_SignerCertificateChain(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setSignatureImageId
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetSignatureImageId
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_SignatureImageId(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignatureImageId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetSignatureImageId
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal =NULL;
	sig->get_SignatureImageId(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    signSignedInfoDigest
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CsignSignedInfoDigest
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring b64CertData, jstring b64SignedInfoDigest)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,b64CertData);
	BSTR bstr1 = jstring2bstr(env,b64SignedInfoDigest);
	BSTR retVal =NULL;
	sig->SignSignedInfoDigest(bstr, bstr1, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	if (bstr1) SysFreeString(bstr1);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    applySignatureValue
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CapplySignatureValue
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring b64SigValXml)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,b64SigValXml);
	BSTR retVal =NULL;
	sig->ApplySignatureValue(bstr, &retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	if (bstr) SysFreeString(bstr);
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignedInfoDigestFromByteArray
 * Signature: ([BLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetSignedInfoDigestFromByteArray
  (JNIEnv *env, jobject _this, jint sigObjIndex, jbyteArray xmlByteArray, jstring signatureId)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v1 = jbytearray2variant(env,xmlByteArray);
	BSTR b1 = jstring2bstr(env,signatureId);
	BSTR retVal = NULL;
	sig->GetSignedInfoDigestFromByteArray(v1,b1,&retVal);
	if (b1) SysFreeString(b1);
	VariantClear(&v1);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    applySignatureValueGetByteArray
 * Signature: (Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_Signature_CapplySignatureValueGetByteArray
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring b64SigValXml)
{
	jbyteArray tmp=NULL;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;

	VARIANT retVal;
	VariantInit(&retVal);
	BSTR b1 = jstring2bstr(env,b64SigValXml);

	sig->ApplySignatureValueGetByteArray(b1,&retVal);
	tmp = variant2jbytearray(env,retVal);
	if (b1) SysFreeString(b1);
	VariantClear(&retVal);

	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignedDocumentB64Str
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetSignedDocumentB64Str
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex, jint uriIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->GetSignedDocumentB64Str((long)sigIndex,(long)uriIndex,&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignedDocumentByteArray
 * Signature: (II)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_Signature_CgetSignedDocumentByteArray
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint sigIndex, jint uriIndex)
{
	jbyteArray tmp=NULL;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;

	VARIANT retVal;
	VariantInit(&retVal);
	sig->GetSignedDocumentByteArray((long)sigIndex, (long) uriIndex, &retVal);
	tmp = variant2jbytearray(env,retVal);
	VariantClear(&retVal);

	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCertValidationTransactionId
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetCertValidationTransactionId
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->get_CertValidationTransactionId(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setCertValidationTransactionId
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetCertValidationTransactionId
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_CertValidationTransactionId(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getIgnoreIncompleteSignature
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetIgnoreIncompleteSignature
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal=0;
	sig->get_IgnoreIncompleteSignature(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setIgnoreIncompleteSignature
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetIgnoreIncompleteSignature
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_IgnoreIncompleteSignature((BOOL)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getSignatureIndexToVerify
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetSignatureIndexToVerify
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	LONG retVal=0;
	sig->get_SignatureIndexToVerify(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setSignatureIndexToVerify
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetSignatureIndexToVerify
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_SignatureIndexToVerify((LONG)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getUseOcsp
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetUseOcsp
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	BOOL retVal=0;
	sig->get_UseOcsp(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setUseOcsp
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetUseOcsp
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_UseOcsp((BOOL)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getOcspTrustedRespSignerCertPath
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetOcspTrustedRespSignerCertPath
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->get_OcspTrustedRespSignerCertPath(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setOcspTrustedRespSignerCertPath
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetOcspTrustedRespSignerCertPath
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_OcspTrustedRespSignerCertPath(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getOcspReqSignerPFXCertPath
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetOcspReqSignerPFXCertPath
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->get_OcspReqSignerPFXCertPath(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setOcspReqSignerPFXCertPath
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetOcspReqSignerPFXCertPath
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_OcspReqSignerPFXCertPath(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getOcspReqSignerPFXCertPassword
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetOcspReqSignerPFXCertPassword
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->get_OcspReqSignerPFXCertPassword(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setOcspReqSignerPFXCertPassword
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetOcspReqSignerPFXCertPassword
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_OcspReqSignerPFXCertPassword(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getOcspResponderURL
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetOcspResponderURL
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->get_OcspResponderURL(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setOcspResponderURL
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetOcspResponderURL
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_OcspResponderURL(bstr);
	if (bstr) SysFreeString(bstr);
 //if (sigObjIndex==0) return;
 //   CSignature *sig = (CSignature *) sigObjIndex;
	//const char *cUrl = env->GetStringUTFChars(newVal, 0);
	//BSTR bstrUrl = A2WBSTR(cUrl);
	//sig->put_OcspResponderURL((OLECHAR *)bstrUrl);

	//env->ReleaseStringUTFChars(newVal, cUrl);
	//if (bstrUrl) SysFreeString(bstrUrl);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getOcspTextResponse
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetOcspTextResponse
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->get_OcspTextResponse(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
	//BSTR bstrResp;
	//jstring retStr=NULL;
 //if (sigObjIndex==0) return retStr;
 //   CSignature *sig = (CSignature *) sigObjIndex;
	//sig->get_OcspTextResponse((OLECHAR **)&bstrResp);
	//if (bstrResp) {
	//	retStr = env->NewString((const jchar *)bstrResp, SysStringLen(bstrResp));
	//	SysFreeString(bstrResp);
	//}
	//return retStr;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getOcspB64Response
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetOcspB64Response
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->get_OcspB64Response(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getCertRevocationDate
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_Signature_CgetCertRevocationDate
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jstring str=NULL;
    if (sigObjIndex==0) return str;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR retVal = NULL;
	sig->get_CertRevocationDate(&retVal);
	if (retVal) {
		str = bstr2jstring(env,retVal);
		SysFreeString(retVal);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    getIncludeOcspResponse
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_Signature_CgetIncludeOcspResponse
  (JNIEnv *env, jobject _this, jint sigObjIndex)
{
	jint tmp = 0;
    if (sigObjIndex==0) return tmp;
    CSignature *sig = (CSignature *) sigObjIndex;
	LONG retVal=0;
	sig->get_IncludeOcspResponse(&retVal);
	tmp = (jint)retVal;
	return tmp;
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setIncludeOcspResponse
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetIncludeOcspResponse
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_IncludeOcspResponse((LONG)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setProxyHost
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetProxyHost
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_ProxyHost(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setProxyPort
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetProxyPort
  (JNIEnv *env, jobject _this, jint sigObjIndex, jint newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	sig->put_ProxyPort((USHORT)newVal);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setProxyUserName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetProxyUserName
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_ProxyUserName(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    setProxyPassword
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetProxyPassword
  (JNIEnv *env, jobject _this, jint sigObjIndex, jstring newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	BSTR bstr = jstring2bstr(env,newVal);
	sig->put_ProxyPassword(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * Class:     infomosaic_securexml_Signature
 * Method:    CsetInclusiveNamespacePrefixList
 * Signature: (I[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_Signature_CsetInclusiveNamespacePrefixList
  (JNIEnv *env, jobject _this, jint sigObjIndex, jobjectArray newVal)
{
    if (sigObjIndex==0) return;
    CSignature *sig = (CSignature *) sigObjIndex;
	VARIANT v = jstringarray2variant(env,newVal);
	sig->put_InclusiveNamespacePrefixList(v);
	VariantClear(&v);
}
