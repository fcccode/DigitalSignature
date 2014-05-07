// VerifyCert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "XMLSign_h.h"
#include "XMLSign_i.c"

int _tmain(int argc, _TCHAR* argv[])
{
	HRESULT hr;
	IUnknown *pUnknown;
	ISignature *pSig;
	BSTR verifyR;
	BSTR inputData;
	VARIANT *certList;
	SAFEARRAY *certArray;
	SAFEARRAYBOUND rgsabound[1];
	BSTR arrElement;
	BSTR certFilenameArr[2];
	long k;
	BOOL result;

	hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		printf("%s","CoInitialize failed.\n");
		exit(0);
	}

	hr = CoCreateInstance(CLSID_Signature, NULL, CLSCTX_INPROC_SERVER, 
						  IID_IUnknown, (void **) &pUnknown);
	if (FAILED(hr))
	{
		printf("%s","CoCreateInstance failed.\n");
		exit(0);
	}

	hr = pUnknown->QueryInterface(IID_ISignature, (void **) &pSig);
	if (FAILED(hr))
	{
		printf("%s","QueryInterface failed.\n");
		exit(0);
	}

	pUnknown->Release();

	USES_CONVERSION;

	pSig->put_CertSerialNumberFormat(1);
	pSig->SetActiveCertificate(A2WBSTR("00 b8 ed"), &result);

	certList = (VARIANT *)malloc(sizeof(VARIANT));
	certArray = (SAFEARRAY *)malloc(sizeof(SAFEARRAY *));

	VariantInit(certList);

	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = 1; // one crl location

	certArray = SafeArrayCreate(VT_BSTR, 
								1,
								rgsabound);
	if (certArray == NULL)
	{
		exit(1);
	}
	certFilenameArr[0] = A2WBSTR((LPCSTR)"./test19/Trust Anchor CRL CP.01.01.crl");
	for (k=0; k<(long)rgsabound[0].cElements; k++)
	{
		arrElement = certFilenameArr[k];
		hr = SafeArrayPutElement(certArray, &k, arrElement);
		if (hr != S_OK)
		{
			exit(1);
		}
	}
	(*certList).vt = (VT_ARRAY | VT_BSTR);
	(*certList).parray = certArray;

	hr = pSig->put_CRLLocation(*certList);

	if (hr != S_OK)
	{
		printf("%s","ReadAll failed.\n");
		exit(0);
	}
	pSig->put_DoDCompliance(1);
	certFilenameArr[0] = A2WBSTR((LPCSTR)"./test19/Trust Anchor CP.01.01.crt");
	for (k=0; k<(long)rgsabound[0].cElements; k++)
	{
		arrElement = certFilenameArr[k];
		hr = SafeArrayPutElement(certArray, &k, arrElement);
		if (hr != S_OK)
		{
			exit(1);
		}
	}
	(*certList).vt = (VT_ARRAY | VT_BSTR);
	(*certList).parray = certArray;
	pSig->put_TrustedRoots(*certList);


	hr = pSig->VerifyPFXCertCRL(A2WBSTR(argv[1]), A2WBSTR("password"), A2WBSTR(""), 1, &result);

	printf("After SecureXMLVerify\n");


	if (hr != S_OK)
	{
		printf("%s","SecureXMLVerify failed.\n");
		exit(0);
	}

	
	printf("%ws", verifyR);
	SysFreeString(inputData);
	SysFreeString(verifyR);

	hr = pSig->put_SignatureID(0, L"MySignature");
	BSTR tmpSignedXMLFileName;
	hr = pSig->Sign(L"catalog.xml", &tmpSignedXMLFileName);
	hr = pSig->put_OverwriteFile(1);
	hr = pSig->SaveXMLSignature(L"catalogSigned.xml");
    SysFreeString(tmpSignedXMLFileName);
	pSig->Release();
	CoUninitialize();

	return 0;
}

