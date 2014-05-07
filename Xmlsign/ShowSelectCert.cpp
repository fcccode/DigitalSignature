// ShowSelectCert.cpp : Implementation of CShowSelectCert
#include "stdafx.h"
#include "ShowSelectCert.h"
#include "XMLSign.h"
#include "signature.h"
#include "resource.h"       // main symbols
#include <atlhost.h>
#include <securexml/base64.h>
#include <securexml/DebugLog.h>

/////////////////////////////////////////////////////////////////////////////
// CShowSelectCert

CShowSelectCert::CShowSelectCert(/*CSignature *theSigObj,*/
								 unsigned char *storeName,
								 PCERT_DESCR *certList,
								 long certCount)
{
	DWORD dwSizeBuf=0;
	BYTE *buff=NULL;
	char s[30];
	char *d;

	certSelected = FALSE;

	issuer = (WCHAR **) zMalloc(certCount * sizeof(char *));
	subject = (WCHAR **) zMalloc(certCount * sizeof(char *));
	notAfter = (char **) zMalloc(certCount * sizeof(char *));
	decodedDataPtr = (char **) zMalloc(certCount * sizeof(char *));
	memset(issuer, 0, certCount * sizeof(char *));
	memset(subject, 0, certCount * sizeof(char *));
	memset(notAfter, 0, certCount * sizeof(char *));
	memset(decodedDataPtr, 0, certCount * sizeof(char *));

	strcpy((char *)StoreName, (const char *)storeName);

	nCurrentRow = 0;
	count = certCount;
	cV = certList;

	for (int i=0; i<count; i++)
	{
		serialNo = cV[i]->serialNumber;
		dwSizeBuf = base64decodeSize(strlen((const char *)serialNo));
		buff = (unsigned char *)zMalloc(dwSizeBuf+1);
		memset(buff,0,dwSizeBuf+1);
		if ((dwSizeBuf = base64decode(serialNo,buff,dwSizeBuf+1))==-1) 
		{	
			if (buff) zFree(buff);
			buff = NULL;
		}
		d = (char *)zMalloc(256);
		memset(d,0,256);
		for(int j=dwSizeBuf;j>0;j--){
			sprintf(s,"%02x",(int)buff[j-1]);
			strcat(d,s);
			strcat(d," ");
		}
		if (buff)
			zFree(buff);
		buff=NULL;

		decodedDataPtr[i] = d;
		
		issuer[i] = (WCHAR *)cV[i]->issuer;
		subject[i] = (WCHAR *)cV[i]->shortSubject;
		notAfter[i] = (char *)cV[i]->notAfter;
	}	
}


CShowSelectCert::~CShowSelectCert()
{
	for (int i=0; i<count;i++)
	{
		if (decodedDataPtr[i])
		{
			zFree(decodedDataPtr[i]);
		}
	}
	zFree(issuer);
	zFree(subject);
	zFree(notAfter);
	zFree(decodedDataPtr);
	Detach();
}

char * CShowSelectCert::getCertificateData(int index)
{
	certificate = (char *)cV[index]->certificate;
	return certificate;
}

LRESULT CShowSelectCert::OnClickedButton1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	axViewAnyCertificate(cV[nCurrentRow]->certificate);
	return 0;
}
