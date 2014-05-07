// CertStore.cpp : Implementation of CCertStore

#include "stdafx.h"
#include "CertStore.h"
#include ".\certstore.h"
#include "NetscapeUtil.h"
#include <malloc.h>

#if __cplusplus
extern "C" {
#endif

#include <libxml/parser.h>
#include <libxml/xmlschemas.h>

#if __cplusplus
}
#endif

extern "C" {
BOOL DebugLogEnabled = FALSE;
BOOL MemoryLogEnabled = FALSE;
BOOL LogEnabled = FALSE;
}

extern unsigned char * HeapW2A(BSTR bstrStr);


// CCertStore

CCertStore::CCertStore()
{
	HRESULT res = S_FALSE;
	//res = NetscapeUtilStart(&nsStoreHandle);
	//if (res != S_OK)
	//nsStoreHandle = NULL;
	certListSize=0;
	certList = NULL;
	memset(nsStorePassword, 0, MAX_PATH);
}

CCertStore::~CCertStore()
{
	HRESULT rs=0;
	//if (nsStoreHandle != NULL) {		
	//	rs = NetscapeUtilStop(nsStoreHandle);
	//	if (rs == S_FALSE) {
	//		DebugBreak();
	//	}		
	//}
	if (certList != NULL)
	{
//		MessageBox(NULL, "Going to free memory", "NetscapeCert Object", MB_OK);
		for (int i=0; i<certListSize; i++)
		{
			if ((certList[i] != NULL) && (certList[i]->certificate != NULL))
			{
				free(certList[i]->certificate);
				free(certList[i]);
			}
		}
		free(certList);
	}
}

STDMETHODIMP CCertStore::GetCertificateList(ULONG* certCount, BSTR* pVal)
{
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL, rootNode=NULL, parent=NULL;
	xmlChar *mem=NULL;
	int iSize=0;
	char buffer[20];
	HRESULT result = S_FALSE;
	HRESULT res = S_FALSE;

	if (certList != NULL)
	{
		for (int i=0; i<certListSize; i++)
		{
			if ((certList[i] != NULL) && (certList[i]->certificate != NULL))
			{
				free(certList[i]->certificate);
				free(certList[i]);
			}
		}
		free(certList);
	}
	res = NetscapeUtilStart(&nsStoreHandle);
	if (res != S_OK) 
	{
		nsStoreHandle = NULL;
		return S_FALSE;
	}
	else 
	{		
		certList = axGetNetscapeCertList(&certListSize, nsStoreHandle, (char *)nsStorePassword);
		*certCount = certListSize;
		doc = xmlNewDoc((const unsigned char *)"1.0");
		cur = xmlNewDocNode(doc,NULL,(const unsigned char *)"CertDescData",NULL);

		// add root element
		xmlDocSetRootElement(doc,cur);
		rootNode = cur;
		cur = xmlNewNode(NULL,(const unsigned char *)"CertificateCount");
		sprintf((char *)buffer, "%d", certListSize);
		xmlNodeSetContent(cur,(const unsigned char *)buffer);
		cur = xmlAddChild(rootNode, cur);

		for (int i=0; i<certListSize; i++)
		{
			unsigned char *tmpPtr = NULL;
			CComBSTR tmpBstr = NULL;

			cur = xmlNewNode(NULL,(const unsigned char *)"Certificate");
			cur = xmlAddChild(rootNode, cur);

			parent = cur;

			cur = xmlNewNode(NULL,(const unsigned char *)"SerialNumber");
			xmlNodeSetContent(cur, certList[i]->serialNumber);
			cur = xmlAddChild(parent, cur);

			cur = xmlNewNode(NULL,(const unsigned char *)"Issuer");
			tmpBstr = certList[i]->issuer;
			tmpPtr = HeapW2A(tmpBstr);
			xmlNodeSetContent(cur,(const unsigned char *)tmpPtr);
			cur = xmlAddChild(parent, cur);
			free(tmpPtr);

			cur = xmlNewNode(NULL,(const unsigned char *)"Subject");
			tmpBstr = certList[i]->subject;
			tmpPtr = HeapW2A(tmpBstr);
			xmlNodeSetContent(cur,(const unsigned char *)tmpPtr);
			cur = xmlAddChild(parent, cur);
			free(tmpPtr);

			cur = xmlNewNode(NULL,(const unsigned char *)"ShortSubject");
			tmpBstr = certList[i]->shortSubject;
			tmpPtr = HeapW2A(tmpBstr);
			xmlNodeSetContent(cur,(const unsigned char *)tmpPtr);
			cur = xmlAddChild(parent, cur);
			free(tmpPtr);

			cur = xmlNewNode(NULL,(const unsigned char *)"NotAfter");
			xmlNodeSetContent(cur,(const unsigned char *)certList[i]->notAfter);
			cur = xmlAddChild(parent, cur);

			if (certList[i]->certificate != NULL)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"X509Certificate");
				xmlNodeSetContent(cur,(const unsigned char *)certList[i]->certificate);
				cur = xmlAddChild(parent, cur);
			}
		}

		xmlDocDumpMemory(doc,&mem,(int *)&iSize);
		xmlFreeDoc(doc);
		*pVal = A2WBSTR((LPCSTR)mem, iSize);
		if (nsStoreHandle != NULL) {		
			res = NetscapeUtilStop(nsStoreHandle);
			if (res == S_FALSE) {
				return S_FALSE;
			}		
		}
		return S_OK;
	}
}

STDMETHODIMP CCertStore::put_NetscapeStorePassword(BSTR newVal)
{
	char *nsPassword=NULL;

	int bstrByteSize = (int)SysStringByteLen(newVal);
	if (bstrByteSize > 0)
	{
		nsPassword = (char *)HeapW2A(newVal);
		memcpy(nsStorePassword, (const void *)nsPassword, (strlen(nsPassword) + 1));
		free(nsPassword);
	}
	return S_OK;
}

STDMETHODIMP CCertStore::ExportNetscapeCert(BSTR certSerialNumber, BSTR* pfxFilePath)
{
	HRESULT hr;
	HRESULT res = S_FALSE;
	char tempFilePath[MAX_PATH];
	char tempFileName[MAX_PATH];
	char *charCertSerialNumber;

	USES_CONVERSION;
	
	res = NetscapeUtilStart(&nsStoreHandle);
	if (res != S_OK) {
		nsStoreHandle = NULL;
		return S_FALSE;
	}
	else {		

		GetTempPath(MAX_PATH, (LPTSTR) tempFilePath);
		GetTempFileName((LPCTSTR)tempFilePath, (LPCTSTR)"NSS", 0, (LPTSTR)tempFileName);

		charCertSerialNumber = (char *)HeapW2A(certSerialNumber);

		hr = axExportNetscapeCert(tempFileName, charCertSerialNumber, nsStorePassword, nsStoreHandle, nsStorePassword);
		*pfxFilePath = A2WBSTR((LPCSTR)tempFileName);
		free(charCertSerialNumber);

		if (nsStoreHandle != NULL) {		
			res = NetscapeUtilStop(nsStoreHandle);
			if (res == S_FALSE) {
				return S_FALSE;
			}		
		}
		return S_OK;
	}
}
