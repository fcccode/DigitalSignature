// PemObject.cpp : Implementation of CPemObject

#include "stdafx.h"
#include "PemObject.h"
#include ".\pemobject.h"
extern "C" {
#include "pem2pfx.h"
}


unsigned char * HeapW2A(BSTR bstrStr)
{
	unsigned char *ptr, *newPtr=NULL, *curPtr=NULL; 
	unsigned int *szPtr;
	unsigned int sizeM;
	

	ptr = (unsigned char *)bstrStr;
	if (ptr == NULL)
		return NULL;
	szPtr = (unsigned int *)(ptr - sizeof(int));
	sizeM = (*szPtr)/2;
	newPtr = (unsigned char *)malloc(sizeM+1);
	curPtr=newPtr;

	for (unsigned int i=0; i<sizeM; i++)
	{
		*curPtr = *(unsigned char *)(bstrStr + i);
		curPtr++;
	}
	*curPtr = '\0';
	
	return(newPtr);
}

// CPemObject


STDMETHODIMP CPemObject::CovertToPFX(BSTR pemFileName, BSTR pemPassword, BSTR* pfxFilePath)
{
	unsigned char *charPemFileName;
	unsigned char *charPfxFileName=NULL;
	char *charPemPassword;

USES_CONVERSION;

	CComBSTR	tmpCcBstr;

	tmpCcBstr = pemFileName;
	if (tmpCcBstr.Length() == 0)
	{
		return S_FALSE;
	}
	charPemFileName = HeapW2A(pemFileName);
	charPemPassword = W2A(pemPassword);
	charPfxFileName = (unsigned char *)Pem2Pfx((char *)charPemFileName, charPemPassword);
	free(charPemFileName);
	if (charPfxFileName == NULL)
	{
		return S_FALSE;
	}
	*pfxFilePath = A2WBSTR((LPCSTR) charPfxFileName);
	free(charPfxFileName);
	return S_OK;
}
