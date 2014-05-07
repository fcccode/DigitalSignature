// TrySign.c : Defines the entry point for the console application.
//


#define COBJMACROS

#include <stdio.h>
#include "XMLSign_h.h" /* this file name is XMLSign.h for Visual Studio 6.0 */
#include "XMLSign_i.c"

BSTR A2WBSTR(LPCSTR lp)
{
	BSTR str = NULL;
	int nConvertedLen;
	int nAllocLen;
	int nResult;

	if (lp == NULL )
		return NULL;
	nConvertedLen = MultiByteToWideChar(CP_ACP, 0, lp, -1, NULL, NULL);
	nAllocLen = nConvertedLen;
	nAllocLen -= 1;  // Don't allocate terminating '\0'
	str = SysAllocStringLen(NULL, nAllocLen);
	if (str != NULL)
	{
		nResult = MultiByteToWideChar(CP_ACP, 0, lp, -1, str, nConvertedLen);
	}
	return str;
}

void main()
{
	HRESULT hr;
	IUnknown *pUnknown;
	ISignature *pSig;
	BSTR tmpFileName;
	BSTR inputData, outputData;
	LONG status;
	int signatureCount;
	int certificateCount;
	int referenceCount;
	BSTR signerName;
	BSTR certIssuer;
	BSTR docURI;
	BSTR sigId;
	int i,j;
	VARIANT *certList;
	SAFEARRAY *certArray;
	SAFEARRAYBOUND rgsabound[1];
	BSTR arrElement;
	BSTR certFilenameArr[2];
	long k;

	/* Initialize Windows COM Infrastructure */

	hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		printf("%s","CoInitialize failed.\n");
		exit(0);
	}


	/* Create an instance of SecureXML ActiveX */
	hr = CoCreateInstance(&CLSID_Signature, NULL, CLSCTX_INPROC_SERVER, 
						  &IID_IUnknown, (void **) &pUnknown);
	if (FAILED(hr))
	{
		printf("%s","CoCreateInstance failed.\n");
		exit(0);
	}

	/* Create a XMLSign.Signature Object and obtain it's handle */

	hr = ISignature_QueryInterface(pUnknown, &IID_ISignature, (void **) &pSig);
	if (FAILED(hr))
	{
		printf("%s","QueryInterface failed.\n");
		exit(0);
	}

	/* Now pSig is a pointer to a XMLSign.Signature Object */

	/* Since we don't want any more Signature objects, release the handle to ActiveX */
	ISignature_Release(pUnknown);


	/* Lets invoke some methods and set a few properties to make sure we can use it */

	hr = ISignature_ReadAll(pSig, A2WBSTR((LPCSTR)"../include/TwoSignature.xml"), &inputData);
	if (FAILED(hr))
	{
		printf("%s","ReadAll failed.\n");
		exit(0);
	}

	/* Verify the signature from the above file */

	hr = ISignature_VerifyXMLStr(pSig, inputData, &status);
	if (status)
	{

		printf("Signature Verified Successfully\n");

		ISignature_get_SignatureCount(pSig, &signatureCount);
		printf("Signature Count = %d\n", signatureCount);

		for (i=0; i < signatureCount; i++)
		{
			ISignature_get_SignatureID(pSig, i, &sigId);
			ISignature_get_SignerSubject(pSig, sigId, &signerName);
			ISignature_get_CertIssuer(pSig, sigId, &certIssuer);

			printf("Signature #%d, Signer Name = %ws\n\n", i, signerName);
			printf("Signature #%d, Certificate Issued By %ws\n\n", i, certIssuer);

			ISignature_get_TotalUriCount(pSig, &referenceCount);

			for (j=0; j < referenceCount; j++)
			{
				ISignature_get_DocumentURI(pSig, i, j, &docURI);
				printf("Signature #%d Document URI #%d = %ws\n", i, j, docURI);
				/* Release memory allocated by SecureXML */
				SysFreeString(docURI);
			}
			/* Release memory allocated by SecureXML */
			SysFreeString(sigId);
			SysFreeString(signerName);
			SysFreeString(certIssuer);
		}

	}

	hr = ISignature_get_CertificateCount(pSig, &certificateCount);

	printf("You have %d PKI certificates installed in your computer\n", certificateCount);

	if (status == 0)
		exit(0);

	hr = ISignature_put_SignatureID(pSig, 0, A2WBSTR((LPCSTR)"MySignature"));

	hr = ISignature_put_EnvelopingFlag(pSig, 2);

	hr = ISignature_put_PhysicalSignatureUsage(pSig, 2);

	hr = ISignature_Sign(pSig, A2WBSTR((LPCSTR)"../include/catalog.xml"), &tmpFileName);

	DeleteFile((LPCTSTR)"catalogSigned.xml");

	hr = ISignature_SaveXMLSignature(pSig,A2WBSTR((LPCSTR)"catalogSigned.xml"));

	printf("Signature saved as catalogSigned.xml\n");

	hr = ISignature_Verify(pSig, A2WBSTR((LPCSTR)"catalogSigned.xml"), &status);

	if (status)
	{

		ISignature_get_SignatureCount(pSig, &status);
		printf("Signature Verified Successfully\n");
		printf("Signature Count = %d\n", status);
	}
	/* Release memory allocated by SecureXML */
	SysFreeString(inputData);
	SysFreeString(tmpFileName);

	certList = (VARIANT *)malloc(sizeof(VARIANT));
	certArray = (SAFEARRAY *)malloc(sizeof(SAFEARRAY *));

	VariantInit(certList);

	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = 2; // Encrypting for two recipients

	certArray = SafeArrayCreate(VT_BSTR, 
								1,
								rgsabound);
	if (certArray == NULL)
	{
		exit(1);
	}
	certFilenameArr[0] = A2WBSTR((LPCSTR)"../include/test1.cer");
	certFilenameArr[1] = A2WBSTR((LPCSTR)"../include/test2.cer");
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

	hr = ISignature_put_RecipientCertificateFiles(pSig, *certList);
//	hr = ISignature_put_RecipientCertificateStore(pSig, A2WBSTR((LPCSTR)"MY"));

	hr = ISignature_EncryptStr(pSig, A2WBSTR((LPCSTR)"This is a test input"), &inputData);
	printf("Encrypted Output = %ws\n", inputData);

	ISignature_put_DecryptionPFXCertFile(pSig, A2WBSTR((LPCSTR)"../include/test2.pfx"));
	ISignature_put_DecryptUsingPFXFileCert(pSig, 1);
	hr = ISignature_DecryptStr(pSig, inputData, &outputData);
	printf("\nDecrypted Output = %ws\n", outputData);

	i = getchar();
	ISignature_Release(pSig);
	CoUninitialize();

}

