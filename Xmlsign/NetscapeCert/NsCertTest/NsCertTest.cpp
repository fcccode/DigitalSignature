// NsCertTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NetscapeUtil.h"
#import "..\release\NetscapeCert.dll"
using namespace NetscapeCert;

int _tmain(int argc, _TCHAR* argv[])
{
	PCERT_DESCR *list = NULL;
	ICertStore *certStorePtr;
	IUnknown *pUnknown;
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(__uuidof(CCertStore), NULL, CLSCTX_INPROC_SERVER, 
						  IID_IUnknown, (void **) &pUnknown);
	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = pUnknown->QueryInterface(__uuidof(ICertStore), (void **) &certStorePtr);
	if (FAILED(hr))
	{
		pUnknown->Release();
		return FALSE;
	}

	pUnknown->Release();
	unsigned long certCount;
	BSTR nsPassword = A2WBSTR("SecureXML");
	certStorePtr->NetscapeStorePassword = nsPassword;
	char *certList = certStorePtr->GetCertificateList(&certCount);
	list = (PCERT_DESCR *)certList;
	for (int i = 0; i < certCount; i++)
	{
		printf("%s\n", list[i]->subject);
		printf("%s\n", list[i]->notAfter);
		_bstr_t pfxFilePath = certStorePtr->ExportNetscapeCert(_bstr_t(list[i]->serialNumber));
		printf("Exported to %s\n", (char *)pfxFilePath);
	}
	getchar();
	certStorePtr->Release();
	return 0;
}

