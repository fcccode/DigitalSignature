// TestSecureXmlPayload.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Signature.h"
#include "SecureXmlPayload.h"

#ifndef WIN32
#include <securexml/CharConversion.h>
#endif

OLECHAR szModulePath[MAX_PATH];
CComModule _Module;

void s_log(const char* format, ...);

//*****************************************************************************
//
//  NAME: log
//
//*****************************************************************************
void s_log(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  FILE *f = fopen("c:\\temp\\sigproxy.log","a");
  vfprintf(f,format, args);
  fclose(f);
  va_end(args);
}

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned long xmlByteSize;
	FILE *fp;
	bool isArray=false;
	int  arraySize=0;
	
	EnterLog;

	SecureXmlPayload *sp = new SecureXmlPayload(), *sp1;
	sp->SetSourceProcessId(1);
	sp->SetSignatureObjectId(9);
	sp->SetApiName((const char *)"setCRLLocation");
	sp->SetNonce((const char *)"This is my nonce 1");
	sp->SetParamCount(3);
	
	sp->SetParamType(0, "StringArray", true, 3);
	sp->SetParamValue(0, 0, "http://www.infomosaic.com");
	sp->SetParamValue(0, 1, "http://www.infomosaic.net");
	sp->SetParamValue(0, 2, "http://www.infomosaic.org");

	sp->SetParamType(1, "String", false, 1);
	sp->SetParamValue(1, 0, "This is param 2");

	sp->SetParamType(2, "StringArray", true, 3);
	sp->SetParamValue(2, 0, "This is param 3 item 0");
	sp->SetParamValue(2, 1, "This is param 3 item 1");
	sp->SetParamValue(2, 2, "This is param 3 item 2");

	char *payloadXml = sp->GetPayloadXml(&xmlByteSize);
	fp = fopen((const char *)"output1.xml", (const char *)"w");
	fprintf(fp,"%s\n", payloadXml);
	fclose(fp);

	char *payloadXmlSaved = (char *)malloc(xmlByteSize + 1);
	memset(payloadXmlSaved, 0, xmlByteSize + 1);
	memcpy(payloadXmlSaved, payloadXml, xmlByteSize);

	sp->SetSourceProcessId(2);
	sp->SetSignatureObjectId(8);
	sp->SetApiName((const char *)"getCRLLocation");
	sp->SetNonce((const char *)"This is my nonce 2");
	sp->SetParamCount(1);
	sp->SetParamType(0, "StringArray", true, 3);
	sp->SetParamValue(0, 0, "http://www.infomosaic.org");
	sp->SetParamValue(0, 1, "http://www.infomosaic.com");
	sp->SetParamValue(0, 2, "http://www.infomosaic.net");
	payloadXml = sp->GetPayloadXml(&xmlByteSize);
	fp = fopen((const char *)"output2.xml", (const char *)"w");
	fprintf(fp,"%s\n", payloadXml);
	fclose(fp);

	sp->SetSourceProcessId(3);
	sp->SetSignatureObjectId(7);
	sp->SetApiName((const char *)"getSecureXMLPath");
	sp->SetNonce((const char *)"This is my nonce 3");
	sp->SetParamCount(1);
	sp->SetParamType(0, "String", false, 0);
	sp->SetParamValue(0, 0, "C:\\temp");
	payloadXml = sp->GetPayloadXml(&xmlByteSize);
	fp = fopen((const char *)"output3.xml", (const char *)"w");
	fprintf(fp,"%s\n", payloadXml);
	fclose(fp);

	delete sp;

	sp = new SecureXmlPayload();
	sp1 = new SecureXmlPayload();

	sp->SetPayloadXml((const char *)payloadXmlSaved);
	printf("Source Process Id = %d\n", sp->GetSourceProcessId());
	printf("Signature Object Id = %d\n", sp->GetSignatureObjectId());
	printf("Api Name = %s\n", sp->GetApiName());
	printf("Nonce = %s\n", sp->GetNonce());
	printf("Param Count = %d\n", sp->GetParamCount());
	for (int i=0; i < sp->GetParamCount(); i++)
	{
		char * dataType = sp->GetParamType(i, &isArray, &arraySize);
		printf("Param %d Param Type = %s, isArray = %d, ArraySize = %d\n", i, dataType, isArray, arraySize);
	}
	payloadXml = sp->GetPayloadXml(&xmlByteSize);
	fp = fopen((const char *)"output4.xml", (const char *)"w");
	fprintf(fp,"%s\n", payloadXml);
	fclose(fp);
	free(payloadXmlSaved);

	VARIANT paramValue = sp->GetParamValue(0);
	unsigned int itemCount;
	BSTR *bstrList = GetBstrArrayFromVariant(paramValue, &itemCount);
	printf("Item Count = %d\n", itemCount);
	for (unsigned int itemIndex=0; itemIndex < itemCount; itemIndex++)
	{
		char *charItemValue = (char *)HeapW2A(bstrList[itemIndex]);
		printf("Item Value = %s\n", charItemValue);
		SysFreeString(bstrList[itemIndex]);
		zFree(charItemValue);
	}
	zFree(bstrList);

	sp->SetApiName("createSignatureObject");
	sp->SetSignatureObjectId((unsigned long)0);
	sp->SetParamCount(0);
	SecureXmlPayload *oPayload = sp->InvokeAPI();

	sp1->SetApiName("createSignatureObject");
	sp1->SetSignatureObjectId((unsigned long)0);
	sp1->SetParamCount(0);
	SecureXmlPayload *oPayload1 = sp1->InvokeAPI();

	if (oPayload != NULL)
	{
		// SelectActiveCertificate
		sp->SetApiName("selectActiveCertificate");
		sp->SetSignatureObjectId(oPayload->GetSignatureObjectId());
		sp->SetParamCount(0);
		oPayload = sp->InvokeAPI();
		printf("Selected Certificate Id = %s\n", oPayload->GetParamValue(0,0));

		// GetHostName
		sp->SetApiName("getHostName");
		sp->SetSignatureObjectId(oPayload->GetSignatureObjectId());
		sp->SetParamCount(0);
		oPayload = sp->InvokeAPI();
		payloadXml = oPayload->GetPayloadXml(&xmlByteSize);
		printf("Hostname XML = %s\n", payloadXml);

		// SignDataStr
		sp->SetApiName("signDataStr");
		sp->SetParamCount(1);
		sp->SetParamType(0, "String", false, 1);
		sp->SetParamValue(0,0, (char *)"This is a test");
		printf("About to call Invoke for signDataStr\n");
		oPayload = sp->InvokeAPI();
		payloadXml = oPayload->GetPayloadXml(&xmlByteSize);
		printf("Signed Xml = %s\n", payloadXml);

		// GetError
		sp->SetApiName("getError");
		sp->SetParamCount(0);
		oPayload = sp->InvokeAPI();
		payloadXml = oPayload->GetPayloadXml(&xmlByteSize);
		printf("Error = %s\n", payloadXml);

		// ReadAll
		sp->SetApiName("readAll");
		sp->SetParamCount(1);
		sp->SetParamType(0, "String", false, 1);
		sp->SetParamValue(0,0, "C:\\temp\\signature.tmpl");
		oPayload = sp->InvokeAPI();
		printf("Read all result = %s\n", oPayload->GetParamValue(0,0));

		// ReadAllByteArray
		sp->SetApiName("readAllByteArray");
		sp->SetParamCount(1);
		sp->SetParamType(0, "String", false, 1);
		sp->SetParamValue(0,0, "C:\\temp\\signature.tmpl");
		oPayload = sp->InvokeAPI();
		printf("Read all result = %s\n", oPayload->GetParamValue(0,0));


		// VerifyPFXCertCRL
		
		// setDoDCompliance
		sp->SetApiName("setDoDCompliance");
		sp->SetParamCount(1);
		sp->SetParamType(0, "Integer", false, 1);
		sp->SetParamValue(0,0,1);
		sp->InvokeAPI();

		// setCRLLocation
		sp->SetApiName("setCRLLocation");
		sp->SetParamCount(1);
		sp->SetParamType(0, "StringArray", true, 3);
		sp->SetParamValue(0,0,"C:\\ActiveX\\XMLSign\\JITC\\X509tests\\test4\\Trust Anchor CRL CP.01.01.crl");
		sp->SetParamValue(0,1,"C:\\ActiveX\\XMLSign\\JITC\\X509tests\\test4\\Intermediate CRL 2 CP.02.01.crl");
		sp->SetParamValue(0,2,"C:\\ActiveX\\XMLSign\\JITC\\X509tests\\test4\\Intermediate CRL 1 CP.02.01.crl");
		sp->InvokeAPI();

		// setTrustedRoots
		sp->SetApiName("setTrustedRoots");
		sp->SetParamCount(1);
		sp->SetParamType(0, "StringArray", true, 1);
		sp->SetParamValue(0,0,"C:\\ActiveX\\XMLSign\\JITC\\X509tests\\test4\\Trust Anchor CP.01.01.crt");
		sp->InvokeAPI();

		// VerifyPFXCertCRL
		sp->SetApiName("verifyPFXCertCRL");
		sp->SetParamCount(4);
		
		sp->SetParamType(0, "String", false, 1);
		sp->SetParamType(1, "String", false, 1);
		sp->SetParamType(2, "String", false, 1);
		sp->SetParamType(3, "Integer", false, 1);

		sp->SetParamValue(0,0,"C:\\ActiveX\\XMLSign\\JITC\\X509tests\\test4\\test4.p12");
		sp->SetParamValue(1,0,"password");
		sp->SetParamValue(2,0,"");
		sp->SetParamValue(3,0,1);
		oPayload = sp->InvokeAPI();
		payloadXml = oPayload->GetPayloadXml(&xmlByteSize);
		printf("verifyPFXCertCRL response Xml = %s\n", payloadXml);


		// setCRLLocation
		sp->SetApiName("setCRLLocation");
		sp->SetParamCount(1);
		sp->SetParamType(0, "StringArray", true, 2);
		sp->SetParamValue(0,0,"C:\\ActiveX\\XMLSign\\JITC\\X509tests\\test3\\Trust Anchor CRL CP.01.01.crl");
		sp->SetParamValue(0,1,"C:\\ActiveX\\XMLSign\\JITC\\X509tests\\test3\\Intermediate CRL CP.01.03.crl");
		sp->InvokeAPI();


		// VerifyPFXCertCRL
		sp->SetApiName("verifyPFXCertCRL");
		sp->SetParamCount(4);
		
		sp->SetParamType(0, "String", false, 1);
		sp->SetParamType(1, "String", false, 1);
		sp->SetParamType(2, "String", false, 1);
		sp->SetParamType(3, "Integer", false, 1);

		sp->SetParamValue(0,0,"C:\\ActiveX\\XMLSign\\JITC\\X509tests\\test3\\test3.p12");
		sp->SetParamValue(1,0,"password");
		sp->SetParamValue(2,0,"");
		sp->SetParamValue(3,0,1);
		oPayload = sp->InvokeAPI();
		payloadXml = oPayload->GetPayloadXml(&xmlByteSize);
		printf("verifyPFXCertCRL response Xml = %s\n", payloadXml);

		// Test SetPayloadXml
		SecureXmlPayload *iPayload = new SecureXmlPayload();
		iPayload->SetPayloadXml((const char *)sp->GetPayloadXml(&xmlByteSize));
		oPayload = iPayload->InvokeAPI();
		payloadXml = oPayload->GetPayloadXml(&xmlByteSize);
		printf("verifyPFXCertCRL response Xml = %s\n", payloadXml);

		// GetError
		iPayload->SetApiName("getError");
		iPayload->SetParamCount(0);
		oPayload = iPayload->InvokeAPI();
		payloadXml = oPayload->GetPayloadXml(&xmlByteSize);
		printf("Error = %s\n", payloadXml);

		// DestroySignatureObject
		sp->SetSignatureObjectId(oPayload->GetSignatureObjectId());
		sp->SetApiName("destroySignatureObject");
		oPayload = sp->InvokeAPI();
	}
	delete sp;
#ifdef LOGGING
	DumpUnfreed();
#endif
	ExitLog;
	return 0;
}

