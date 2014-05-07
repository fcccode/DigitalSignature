#include "stdafx.h"
#include "XMLSign.h"
#include "XMLSign_i.c"

int main(int argc, char* argv[])
{
	HRESULT hr;
	IUnknown *pUnknown;
	ISignature *pSig;
	BSTR verifyR;
	BSTR inputData;
	long lastError=0;

	USES_CONVERSION;

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

	hr = pSig->ReadAll(L"../include/TwoSignature.xml", &inputData);

	printf("After ReadAll\n");
	if (hr != S_OK)
	{
		printf("%s","ReadAll failed.\n");
		exit(0);
	}

	hr = pSig->SecureXMLVerify(inputData, &verifyR);

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
	hr = pSig->put_EnvelopingFlag(2);
	hr = pSig->Sign(A2WBSTR("../include/catalog.xml"), &tmpSignedXMLFileName);
	hr = pSig->put_OverwriteFile(1);
	hr = pSig->SaveXMLSignature(L"catalogSignedEnveloped.xml");
    SysFreeString(tmpSignedXMLFileName);

	hr = pSig->SignFile(A2WBSTR("../include/f2.txt"), A2WBSTR("f1docS.xml"));
	hr = pSig->GetLastError(&lastError);
	printf("last error = %d\n", lastError);
	pSig->Release();
	CoUninitialize();

	return 0;
}

