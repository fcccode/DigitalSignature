// config.cpp: implementation of the config class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#ifdef WIN32
#include "XMLSign.h"
#endif

#include "Signature.h"
#include <securexml/coresig.h>
#if __cplusplus
extern "C" {
#endif

#include <securexml/xs.h>
#include <securexml/utils.h>
#include <securexml/errors.h>
#include <securexml/cr.h>
#if __cplusplus
}
#endif
#include <securexml/DebugLog.h>
#include <securexml/base64.h>

#ifndef WIN32
#define USES_CONVERSION
#endif

extern unsigned char Base64Chars[];

/*
<?xml version="1.0" encoding="utf-8" ?>
<configuration>
	<appSettings>
		<add key="AddWindowImage" value="1" />
		<add key="CaptureOnce" value="0" />
		<add key="CrlChecking" value="0" />
		<add key="EnvelopingFlag" value="2" />
		<add key="PhysicalSignatureFile" value="" />
		<add key="PhysicalSignatureUsage" value="2" />
		<add key="TimeStampURL" value="http://time-b.timefreq.bldrdoc.gov:13" />
		<add key="TimeStamping" value="0" />
		<add key="TimeStampFormat" value="0" />
		<add key="TimeStampCritical" value="0" />
		<add key="DoDCompliance" value="0" />
		<add key="CertificateTrustExplicit" value="0" />
		<add key="TrustedRoots" value="C:\temp\trstedRoot_1.cer" />
		<add key="TrustedRoots" value="C:\temp\trstedRoot_2.cer" />
		<add key="CertificatePolicyExplicit" value="0" />
		<add key="CertificatePathLengthChecking" value="0" />
		<add key="CertificateChainValidation" value="0" />
		<add key="CertificatePolicyChecking" value="0" />
		<add key="CertificatePolicyCount" value="2" />
		<add key="CertificatePolicy" value="1.0.3.4.5.6" />
		<add key="CertificatePolicy" value="1.0.3.4.5.6.7.8" />
		<add key="CRLLocationCount" value="2" />
		<add key="CRLLocation" value="C:\temp\MyCrl_0.crl" />
		<add key="CRLLocation" value="C:\temp\MyCrl_1.crl" />
		<add key="OverwriteFile" value="1" />
		<add key="ExcludeSignerCertificate" value="0" />
		<add key="DetailedVerificationFlag" value="0" />
		<add key="Base64EncodeXML" value="0" />
		<add key="Base64DecodeXML" value="0" />
		<add key="IncludeCamResponse" value="0" />
		<add key="CamServerHost" value="www.infomosaic.com" />
		<add key="CamServerPort" value="7777" />
		<add key="UseCam" value="0" />
		<add key="AgencyId" value="AA_Agency_Id" />
		<add key="AllowedCertIssuerCount" value="2" />
		<add key="AllowedCertIssuerName" value="C3 ID CA" />
		<add key="AllowedCertIssuerName" value="Infomosaic" />
		<add key="CRLCacheDbConnectionString" value="DRIVER={sql server};SERVER=SUPPORTCOMP;DATABASE=SECUREXML;UID=sa;PWD=password" />
		<add key="UseCRLCache" value="1" />
		<add key="CRLCacheTimeoutInMinutes" value="120" />

	</appSettings>
</configuration>
*/


const xmlChar *CConfig::appSettings = (const xmlChar *)"appSettings";
const xmlChar *CConfig::envelopingFlag = (const xmlChar *)"EnvelopingFlag";
const xmlChar *CConfig::addWindowImage = (const xmlChar *)"AddWindowImage";
const xmlChar *CConfig::captureOnce = (const xmlChar *)"CaptureOnce";
const xmlChar *CConfig::crlChecking = (const xmlChar *)"CrlChecking";
const xmlChar *CConfig::physicalSignatureFile = (const xmlChar *)"PhysicalSignatureFile";
const xmlChar *CConfig::physicalSignatureUsage = (const xmlChar *)"PhysicalSignatureUsage";
const xmlChar *CConfig::timeStampURL = (const xmlChar *)"TimeStampURL";
const xmlChar *CConfig::timeStamping = (const xmlChar *)"TimeStamping";
const xmlChar *CConfig::timeStampFormat = (const xmlChar *)"TimeStampFormat";
const xmlChar *CConfig::timeStampCritical = (const xmlChar *)"TimeStampCritical";

const xmlChar *CConfig::doDCompliance = (const xmlChar *)"DoDCompliance";
const xmlChar *CConfig::certificateTrustExplicit = (const xmlChar *)"CertificateTrustExplicit";
const xmlChar *CConfig::trustedRootCount = (const xmlChar *)"TrustedRootCount";
const xmlChar *CConfig::trustedRoot = (const xmlChar *)"TrustedRoot";
const xmlChar *CConfig::certificatePolicyExplicit = (const xmlChar *)"CertificatePolicyExplicit";
const xmlChar *CConfig::certificatePathLengthChecking = (const xmlChar *)"CertificatePathLengthChecking";
const xmlChar *CConfig::certificateChainValidation = (const xmlChar *)"CertificateChainValidation";
const xmlChar *CConfig::certificatePolicyChecking = (const xmlChar *)"CertificatePolicyChecking";
const xmlChar *CConfig::certificatePolicyCount = (const xmlChar *)"CertificatePolicyCount";
const xmlChar *CConfig::certificatePolicy = (const xmlChar *)"CertificatePolicy";
const xmlChar *CConfig::cRLLocationCount = (const xmlChar *)"CRLLocationCount";
const xmlChar *CConfig::cRLLocation = (const xmlChar *)"CRLLocation";
const xmlChar *CConfig::overwriteFile = (const xmlChar *)"OverwriteFile";
const xmlChar *CConfig::excludeSignerCertificate = (const xmlChar *)"ExcludeSignerCertificate";
const xmlChar *CConfig::detailedVerificationFlag = (const xmlChar *)"DetailedVerificationFlag";
const xmlChar *CConfig::base64EncodeXML = (const xmlChar *)"Base64EncodeXML";
const xmlChar *CConfig::base64DecodeXML = (const xmlChar *)"Base64DecodeXML";
const xmlChar *CConfig::includeCamResponse = (const xmlChar *)"IncludeCamResponse";
const xmlChar *CConfig::camServerHost = (const xmlChar *)"CamServerHost";
const xmlChar *CConfig::camServerPort = (const xmlChar *)"CamServerPort";
const xmlChar *CConfig::useCam = (const xmlChar *)"UseCam";
const xmlChar *CConfig::agencyId = (const xmlChar *)"AgencyId";
const xmlChar *CConfig::allowedCertIssuerCount = (const xmlChar *)"AllowedCertIssuerCount";
const xmlChar *CConfig::allowedCertIssuerName = (const xmlChar *)"AllowedCertIssuerName";
const xmlChar *CConfig::crlCacheDbConnectionString = (const xmlChar *)"CRLCacheDbConnectionString";
const xmlChar *CConfig::useCRLCache =(const xmlChar *)"UseCRLCache";
const xmlChar *CConfig::crlCacheTimeoutInMinutes =(const xmlChar *)"CRLCacheTimeoutInMinutes";



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConfig::CConfig(CSignature *theSigObj)
{
	curSig = theSigObj;
	ConfigFile = NULL;

	curSig->EnvelopingFlag = 0;
	curSig->AddWindowImageFlag = FALSE;
	curSig->CaptureSigOnce = FALSE;
	curSig->DoDCompliance = FALSE;
	curSig->PhysicalSigUsage = NO_PHYSICAL_SIG;
	curSig->TimeStampURL = A2WBSTR((LPCSTR) defaultTimeServiceUrl);;
	curSig->TimeStampOption = 0;
	curSig->TimeStampFormat = TIME_RFC;
	curSig->TimeStampCritical = FALSE;

	curSig->PfxPassword.pbData = NULL;
	curSig->PfxX509Cert = NULL;
	curSig->B64PfxDataPtr = NULL;
	curSig->PfxCertDataBlob.cbData = 0;
	curSig->PfxCertDataBlob.pbData = NULL;
	curSig->RecipientCertificateStore = A2WBSTR((LPCSTR)"addressbook");
	curSig->SignatureCaptured = FALSE;

	curSig->DetailedVerificationReportFlag = TRUE;
	curSig->ExcludeSignerCertificateFlag = FALSE;
	curSig->OverwriteFileFlag = FALSE;
	curSig->UseHMAC = FALSE;
	curSig->camServerHost=NULL;
	curSig->camServerPort=7777;
	curSig->useCam = FALSE;
	curSig->Base64EncodeXML = FALSE;
	curSig->Base64DecodeXML = FALSE;
	curSig->allowedCertIssuerCount = 0;
	curSig->allowedCertIssuerNames = NULL;
}

CConfig::~CConfig()
{
	if (ConfigFile != NULL)
		zFree(ConfigFile);
	ConfigFile = NULL;
}


void CConfig::getConfigDetailsFromDom(xmlNodePtr startNode)
{
	xmlChar *curKeyName  = NULL;
	xmlChar *curKeyValue = NULL;
	xmlNodePtr curr = startNode;
	UINT trustRootItemNumber = 0;
	UINT trustRootItemCount = 0;
	BYTE *dataPtr=NULL, *rootCertData=NULL;
	DWORD dataSize;
	DWORD encodedDataSize;
	BYTE *encodedDataPtr;
	UINT crlItemNumber = 0;
	UINT crlItemCount = 0;
	UINT policyItemNumber = 0;
	UINT policyItemCount = 0;
	BOOL newVal;
	UINT allowedCertIssuerItemCount = 0;
	UINT allowedCertIssuerItemNumber = 0;


USES_CONVERSION;

	for ( ; curr != NULL; curr = curr->next) 
	{
		if (! xmlStrcmp(curr->name, (const unsigned char *)"appSettings"))
			break;
	}

	if (curr != NULL)
		curr = curr->xmlChildrenNode;

	for ( ; curr != NULL; curr = curr->next) 
	{	

		if (curKeyName != NULL)
		{
			xmlFree(curKeyName);
			curKeyName = NULL;
		}
		
		if (curKeyValue != NULL)
		{
			xmlFree(curKeyValue);
			curKeyValue = NULL;
		}
		
		curKeyName	=  xmlGetProp(curr, (const unsigned char *)"key");
		
		if (curKeyName == NULL)
			continue;
		
		curKeyValue	=  xmlGetProp(curr, (const unsigned char *)"value");

		if (curKeyValue == NULL)
			continue;
		
//DebugBreak();		
		if (! xmlStrcmp(curKeyName, envelopingFlag)) 
		{			
			curSig->EnvelopingFlag = (BOOL)(atoi((const char *)curKeyValue));			
			continue;
		}

		if (! xmlStrcmp(curKeyName, addWindowImage)) 
		{			
			curSig->AddWindowImageFlag = (BOOL)(atoi((const char *)curKeyValue));			
			continue;
		}

		if (! xmlStrcmp(curKeyName, captureOnce)) 
		{			
			curSig->CaptureSigOnce = (BOOL)(atoi((const char *)curKeyValue));			
			continue;
		}
		if (! xmlStrcmp(curKeyName, crlChecking)) 
		{			
			BOOL CrlCheckEnabled = (BOOL) (atoi((const char *)curKeyValue));
			if (curSig->DoDCompliance == FALSE)
				if (CrlCheckEnabled)
					curSig->CertVerifyParams.verificationOptions |= VERIFY_CRL;
				else
					curSig->CertVerifyParams.verificationOptions &= (~VERIFY_CRL);
			continue;
		}
		if (! xmlStrcmp(curKeyName, certificatePolicyChecking)) 
		{			
			newVal = (BOOL) (atoi((const char *)curKeyValue));
			if (curSig->DoDCompliance == FALSE)
				if (newVal)
					curSig->CertVerifyParams.verificationOptions |= VERIFY_POLICY;
				else
					curSig->CertVerifyParams.verificationOptions &= (~VERIFY_POLICY);
			continue;
		}

		if (! xmlStrcmp(curKeyName, certificateTrustExplicit)) 
		{			
			newVal = (BOOL) (atoi((const char *)curKeyValue));
			if (curSig->DoDCompliance == FALSE)
				if (newVal)
					curSig->CertVerifyParams.verificationOptions |= EXPLICIT_TRUST;
				else
					curSig->CertVerifyParams.verificationOptions &= (~EXPLICIT_TRUST);
			continue;
		}

		if (! xmlStrcmp(curKeyName, certificatePolicyExplicit)) 
		{			
			newVal = (BOOL) (atoi((const char *)curKeyValue));
			if (newVal)
				curSig->CertVerifyParams.verificationOptions |= POLICY_EXPLICIT;
			else
				curSig->CertVerifyParams.verificationOptions &= (~POLICY_EXPLICIT);
			continue;
		}

		if (! xmlStrcmp(curKeyName, certificateChainValidation)) 
		{			
			newVal = (BOOL) (atoi((const char *)curKeyValue));
			if (curSig->DoDCompliance == FALSE)
				if (newVal)
				{
					curSig->CertVerifyParams.verificationOptions |= VERIFY_CHAIN;
					curSig->CertVerifyParams.verificationOptions |= VERIFY_PATH_LENGTH;
				}
				else
				{
					curSig->CertVerifyParams.verificationOptions &= (~VERIFY_CHAIN);
					curSig->CertVerifyParams.verificationOptions &= (~VERIFY_PATH_LENGTH);
				}
			continue;
		}

		if (! xmlStrcmp(curKeyName, certificatePathLengthChecking)) 
		{			
			newVal = (BOOL) (atoi((const char *)curKeyValue));
			if (curSig->DoDCompliance == FALSE)
				if (newVal)
					curSig->CertVerifyParams.verificationOptions |= VERIFY_PATH_LENGTH;
				else
					curSig->CertVerifyParams.verificationOptions &= (~VERIFY_PATH_LENGTH);
			continue;
		}

		if (! xmlStrcmp(curKeyName, doDCompliance)) 
		{			
			curSig->DoDCompliance = (BOOL) (atoi((const char *)curKeyValue));
			if (curSig->DoDCompliance)
				curSig->CertVerifyParams.verificationOptions |=	(VERIFY_CRL | 
													VERIFY_POLICY | 
													VERIFY_CHAIN | 
													VERIFY_PATH_LENGTH |
													EXPLICIT_TRUST);
			else
			{
				curSig->CertVerifyParams.verificationOptions &= (~VERIFY_CRL);
				curSig->CertVerifyParams.verificationOptions &= (~VERIFY_POLICY);
				curSig->CertVerifyParams.verificationOptions &= (~VERIFY_CHAIN);
				curSig->CertVerifyParams.verificationOptions &= (~VERIFY_PATH_LENGTH);
				curSig->CertVerifyParams.verificationOptions &= (~EXPLICIT_TRUST);
			}
			continue;
		}

		if (! xmlStrcmp(curKeyName, physicalSignatureFile)) 
		{
			int filePathSize = strlen((const char *)curKeyValue);

			if (filePathSize < MAX_PATH)
				strcpy((char *) curSig->PhysicalSignatureFileName,(const char *)curKeyValue);
			else
				setError(curSig->SigHandle, FILE_PATH_TOO_LONG);
			continue;
		}

		if (! xmlStrcmp(curKeyName, physicalSignatureUsage)) 
		{			
			curSig->PhysicalSigUsage = atoi((const char *)curKeyValue);
			if (curSig->PhysicalSigUsage != NO_PHYSICAL_SIG)
			{		
#ifdef WIN32
				HWND desktopHwnd;
				desktopHwnd = GetDesktopWindow();	
				GetClientRect(desktopHwnd, &curSig->SignatureCaptureWindowDim);		
				curSig->SignatureCaptureWindowDim.left = (curSig->SignatureCaptureWindowDim.right / 2) - 175; // UpperX		
				curSig->SignatureCaptureWindowDim.top = (curSig->SignatureCaptureWindowDim.bottom / 2) - 125; // UpperY		
				curSig->SignatureCaptureWindowDim.bottom = 250; // Height
				curSig->SignatureCaptureWindowDim.right = 350;  // Width
#endif
			}

			continue;
		}

		if (! xmlStrcmp(curKeyName, timeStampURL)) 
		{			
			curSig->TimeStampURL = A2WBSTR((const char *)curKeyValue);	
			continue;
		}
		if (! xmlStrcmp(curKeyName, timeStamping)) 
		{			
			curSig->TimeStampOption = atoi((const char *)curKeyValue);
			continue;
		}

		if (! xmlStrcmp(curKeyName, timeStampFormat)) 
		{			
			curSig->TimeStampFormat = atoi((const char *)curKeyValue);
			continue;
		}

		if (! xmlStrcmp(curKeyName, timeStampCritical)) 
		{			
			curSig->TimeStampCritical = atoi((const char *)curKeyValue);
			continue;
		}

		if (! xmlStrcmp(curKeyName, detailedVerificationFlag)) 
		{			
			curSig->DetailedVerificationReportFlag = (BOOL)(atoi((const char *)curKeyValue));
			continue;
		}
		if (! xmlStrcmp(curKeyName, excludeSignerCertificate)) 
		{			
			curSig->ExcludeSignerCertificateFlag = (BOOL)(atoi((const char *)curKeyValue));
			continue;
		}
		if (! xmlStrcmp(curKeyName, overwriteFile)) 
		{			
			curSig->OverwriteFileFlag = (BOOL)(atoi((const char *)curKeyValue));
			continue;
		}
		if (! xmlStrcmp(curKeyName, camServerHost)) 
		{			
			curSig->camServerHost = (unsigned char *)zMalloc(strlen((const char *)curKeyValue) +1);
			strcpy((char *)curSig->camServerHost, (const char *)curKeyValue);
			continue;
		}
		if (! xmlStrcmp(curKeyName, camServerPort)) 
		{			
			curSig->camServerPort = (USHORT)(atoi((const char *)curKeyValue));
			if (curSig->pCamClient != NULL)
				curSig->pCamClient->camServerPortNumber = curSig->camServerPort;
			continue;
		}
		if (! xmlStrcmp(curKeyName, useCam)) 
		{			
			newVal = (BOOL)(atoi((const char *)curKeyValue));
			if (curSig->useCam) // Already enabled hence do nothing if newVal != 0
			{
				if (newVal == 0)
				{
					if (curSig->pCamClient != NULL)
					{
						delete curSig->pCamClient;
						curSig->pCamClient = NULL;
					}
					curSig->useCam = newVal;
					continue;
				}
				else
					continue;
			}
			else 
				if (newVal)
				{
					curSig->pCamClient = new CCAMClient();
					curSig->useCam = newVal;
					curSig->pCamClient->camServerPortNumber = curSig->camServerPort;
				}
			continue;
		}
		if (! xmlStrcmp(curKeyName, base64EncodeXML)) 
		{			
			curSig->Base64EncodeXML = (BOOL)(atoi((const char *)curKeyValue));
			continue;
		}
		if (! xmlStrcmp(curKeyName, base64DecodeXML)) 
		{			
			curSig->Base64DecodeXML = (BOOL)(atoi((const char *)curKeyValue));
			continue;
		}
		if (! xmlStrcmp(curKeyName, includeCamResponse)) 
		{			
			curSig->IncludeCamResponse = (BOOL)(atoi((const char *)curKeyValue));
			continue;
		}
		if (! xmlStrcmp(curKeyName, agencyId)) 
		{			
			strcpy((char *)curSig->agencyId, (const char *)curKeyValue);
			continue;
		}
		if (! xmlStrcmp(curKeyName, trustedRootCount)) 
		{			
			if (curSig->CertVerifyParams.trustRootCertCount != 0)
			{
				for (unsigned int i=0; i < curSig->CertVerifyParams.trustRootCertCount; i++)
					zFree(curSig->CertVerifyParams.trustRootCerts[i]);
				zFree(curSig->CertVerifyParams.trustRootCerts);
			}
			curSig->CertVerifyParams.trustRootCertCount = (UINT)(atoi((const char *)curKeyValue));
			trustRootItemCount = curSig->CertVerifyParams.trustRootCertCount;
			curSig->CertVerifyParams.trustRootCerts = (char **) zMalloc(sizeof(char *) * trustRootItemCount);
			memset(curSig->CertVerifyParams.trustRootCerts, 0, sizeof(char *) * trustRootItemCount);
			continue;
		}

		if (! xmlStrcmp(curKeyName, trustedRoot)) 
		{			
			if ((trustRootItemCount != 0) && (trustRootItemNumber < trustRootItemCount))
			{
				dataPtr = xsDereferenceURI((char *)curKeyValue, &dataSize);
				if (dataPtr != NULL)
				{
					rootCertData = (BYTE *)zMalloc(dataSize + 1);
					if (rootCertData == NULL)
					{
						setError(curSig->SigHandle, MEMORY_FAULT);
						zFree(dataPtr);
						for (UINT i=0; i < trustRootItemCount; i++)
						{
							if (curSig->CertVerifyParams.trustRootCerts[i] != NULL)
							{
								zFree(curSig->CertVerifyParams.trustRootCerts[i]);
								curSig->CertVerifyParams.trustRootCerts[i] = NULL;
							}
						}
						zFree(curSig->CertVerifyParams.trustRootCerts);
						curSig->CertVerifyParams.trustRootCerts = NULL;
						curSig->CertVerifyParams.trustRootCertCount = 0;
						trustRootItemCount = 0;
						trustRootItemNumber = 0;
						continue;
					}
					memcpy(rootCertData, dataPtr, dataSize);
					*(rootCertData + dataSize) = '\0';
					for (UINT i=0; i < dataSize; i++)
					{
						if (strchr((const char *)Base64Chars, *(rootCertData + i)) == NULL)
						{
							if ((*(rootCertData + i) == 0x0d) ||
								(*(rootCertData + i) == 0x0a) ||
								(*(rootCertData + i) == 0x20))
								continue;
							// The data is not base64 encoded, so lets encode it now
							encodedDataSize = base64encodeSize(dataSize);
							encodedDataPtr = (BYTE *)zMalloc(encodedDataSize + 1);
							encodedDataSize = base64encode(rootCertData, dataSize, encodedDataPtr, encodedDataSize + 1);
							zFree(rootCertData);
							rootCertData = encodedDataPtr;
							break;
						}
					}
					curSig->CertVerifyParams.trustRootCerts[trustRootItemNumber] = (LPSTR)rootCertData;
					zFree(dataPtr);
					trustRootItemNumber++;
					continue;
				}
				else
				{
					setError(curSig->SigHandle, FILE_NOT_FOUND);
					for (UINT i=0; i < trustRootItemCount; i++)
					{
						if (curSig->CertVerifyParams.trustRootCerts[i] != NULL)
						{
							zFree(curSig->CertVerifyParams.trustRootCerts[i]);
							curSig->CertVerifyParams.trustRootCerts[i] = NULL;
						}
					}
					zFree(curSig->CertVerifyParams.trustRootCerts);
					curSig->CertVerifyParams.trustRootCerts = NULL;
					curSig->CertVerifyParams.trustRootCertCount = 0;
					trustRootItemCount = 0;
					trustRootItemNumber = 0;
					continue;
				}
			}
			else
			{
				trustRootItemNumber = 0;
				trustRootItemCount = 0;
			}
			continue;
		}

		if (! xmlStrcmp(curKeyName, cRLLocationCount)) 
		{			
			if (curSig->CertVerifyParams.altCrlCount != 0)
			{
				for (unsigned int i=0; i < curSig->CertVerifyParams.altCrlCount; i++)
					zFree(curSig->CertVerifyParams.crlAltUrl[i]);
				zFree(curSig->CertVerifyParams.crlAltUrl);
			}
			curSig->CertVerifyParams.altCrlCount = (UINT)(atoi((const char *)curKeyValue));
			crlItemCount = curSig->CertVerifyParams.altCrlCount;
			curSig->CertVerifyParams.crlAltUrl = (char **) zMalloc(sizeof(char *) * crlItemCount);
			memset(curSig->CertVerifyParams.crlAltUrl, 0, sizeof(char *) * crlItemCount);
			continue;
		}

		if (! xmlStrcmp(curKeyName, cRLLocation)) 
		{			
			if ((crlItemCount != 0) && (crlItemNumber < crlItemCount))
			{
				curSig->CertVerifyParams.crlAltUrl[crlItemNumber] = (LPSTR)zMalloc(strlen((const char *)curKeyValue) + 1);
				strcpy(curSig->CertVerifyParams.crlAltUrl[crlItemNumber], (const char *)curKeyValue);
				crlItemNumber++;
			}
			else
			{
				crlItemCount = 0;
				crlItemNumber = 0;
			}
			continue;
		}


		if (! xmlStrcmp(curKeyName, certificatePolicyCount)) 
		{			
			if (curSig->CertVerifyParams.userPolicyCount != 0)
			{
				for (unsigned int i=0; i < curSig->CertVerifyParams.userPolicyCount; i++)
					zFree(curSig->CertVerifyParams.userPolicySet[i]);
				zFree(curSig->CertVerifyParams.userPolicySet);
			}
			curSig->CertVerifyParams.userPolicyCount = (UINT)(atoi((const char *)curKeyValue));
			policyItemCount = curSig->CertVerifyParams.userPolicyCount;
			curSig->CertVerifyParams.userPolicySet = (char **) zMalloc(sizeof(char *) * policyItemCount);
			memset(curSig->CertVerifyParams.userPolicySet, 0, sizeof(char *) * policyItemCount);
			continue;
		}

		if (! xmlStrcmp(curKeyName, certificatePolicy)) 
		{			
			if ((policyItemCount != 0) && (policyItemNumber < policyItemCount))
			{
				curSig->CertVerifyParams.userPolicySet[policyItemNumber] = (LPSTR)zMalloc(strlen((const char *)curKeyValue) + 1);
				strcpy(curSig->CertVerifyParams.userPolicySet[policyItemNumber], (const char *)curKeyValue);
				policyItemNumber++;
			}
			else
			{
				policyItemCount = 0;
				policyItemNumber = 0;
			}
			continue;
		}

		if (! xmlStrcmp(curKeyName, allowedCertIssuerCount)) 
		{			
			if (curSig->allowedCertIssuerCount != 0)
			{
				for (unsigned int i=0; i < curSig->allowedCertIssuerCount; i++)
					SysFreeString(curSig->allowedCertIssuerNames[i]);
				zFree(curSig->allowedCertIssuerNames);
			}
			curSig->allowedCertIssuerCount = (UINT)(atoi((const char *)curKeyValue));
			allowedCertIssuerItemCount = curSig->allowedCertIssuerCount;
			curSig->allowedCertIssuerNames = (LPWSTR *) zMalloc(sizeof(WCHAR *) * allowedCertIssuerItemCount);
			memset(curSig->allowedCertIssuerNames, 0, sizeof(char *) * allowedCertIssuerItemCount);
			continue;
		}

		if (! xmlStrcmp(curKeyName, allowedCertIssuerName)) 
		{			
			unsigned char *utf16CharStr=NULL;
			int utf16ByteLen=0, utf8ByteLen=0;
			utf8ByteLen = strlen((const char *)curKeyValue);
			utf16ByteLen = utf8ByteLen * 2;
			utf16CharStr = (unsigned char *)zMalloc(utf16ByteLen);
			UTF8ToUTF16LE(utf16CharStr, &utf16ByteLen, (const unsigned char*)curKeyValue, &utf8ByteLen);
			BSTR bstrCurKeyValue = SysAllocStringByteLen((LPCSTR)utf16CharStr, utf16ByteLen);
			zFree(utf16CharStr);
			if ((allowedCertIssuerItemCount != 0) && (allowedCertIssuerItemNumber < allowedCertIssuerItemCount))
			{
				curSig->allowedCertIssuerNames[allowedCertIssuerItemNumber] = bstrCurKeyValue;
				allowedCertIssuerItemNumber++;
			}
			else
			{
				allowedCertIssuerItemCount = 0;
				allowedCertIssuerItemNumber = 0;
				SysFreeString(bstrCurKeyValue);
			}
			continue;
		}
#ifdef WIN32
		if (! xmlStrcmp(curKeyName,crlCacheDbConnectionString)) 
		{			
			curSig->CRLCacheDbConnectionString = A2WBSTR((LPCSTR)curKeyValue);
			continue;
		}
		if (! xmlStrcmp(curKeyName,useCRLCache)) 
		{			
			BOOL newVal = (BOOL)(atoi((const char *)curKeyValue));
			if (curSig->CertVerifyParams.pCrlCache != NULL)
			{
				delete curSig->CertVerifyParams.pCrlCache;
				if (newVal == FALSE)
				{
					curSig->CertVerifyParams.pCrlCache = NULL;
				}
				else
				{
					curSig->CertVerifyParams.pCrlCache = new CRLCache(curSig->CRLCacheDbConnectionString.m_str, curSig->SigHandle);
					curSig->CertVerifyParams.pCrlCache->SetCRLTimeOut(curSig->crlCacheTimeoutInMinutes);
				}
			}
			else
				if (newVal != FALSE)
				{
					curSig->CertVerifyParams.pCrlCache = new CRLCache(curSig->CRLCacheDbConnectionString.m_str, curSig->SigHandle);
					curSig->CertVerifyParams.pCrlCache->SetCRLTimeOut(curSig->crlCacheTimeoutInMinutes);
				}
			continue;
		}
		if (! xmlStrcmp(curKeyName, crlCacheTimeoutInMinutes)) 
		{			
			curSig->crlCacheTimeoutInMinutes = (ULONG)(atoi((const char *)curKeyValue));
			if (curSig->CertVerifyParams.pCrlCache != NULL)
				curSig->CertVerifyParams.pCrlCache->SetCRLTimeOut(curSig->crlCacheTimeoutInMinutes);

			continue;
		}
#endif
		xmlFree(curKeyName);
		xmlFree(curKeyValue);
		curKeyName = NULL;
		curKeyValue = NULL;

	}
}

/**
 * getConfigDetails:
 *
 * Open the file at configFile. Verify the signature of the file
 * Get the details from the config xml file and assign the values of
 * the variables appropriately.
 *
 */
BOOL CConfig::getConfigDetails(PGLOBAL_SIG SigHandle)
{

	xmlDocPtr doc = NULL;

	doc = xmlParseFile((const char *)ConfigFile);
	if (!doc) {
		// cout << "Couldn't parse the license file" << endl;
		setError(SigHandle, XML_PARSER_ERROR);
		return FALSE;
	}
	xmlNodePtr root = xmlDocGetRootElement(doc);
	xmlNodePtr curr = root->xmlChildrenNode;

	getConfigDetailsFromDom(curr);

	xmlFreeDoc(doc);

	return TRUE;
}


BOOL CConfig::setConfigDetails(BSTR confXMLStr)
{
	xmlDocPtr doc = NULL;
	CComBSTR tmpBstr;

USES_CONVERSION;

	tmpBstr = confXMLStr;

	unsigned char *wConfXMLStr = HeapW2A(confXMLStr);
	doc = xmlParseMemory((const char *)wConfXMLStr, tmpBstr.Length());
	zFree(wConfXMLStr);
	if (!doc) {
		// cout << "Couldn't parse the config xml" << endl;
		setError(curSig->SigHandle, XML_PARSER_ERROR);
		return FALSE;
	}

	xmlNodePtr root = xmlDocGetRootElement(doc);
	xmlNodePtr curr = root->xmlChildrenNode;

	getConfigDetailsFromDom(curr);

	xmlFreeDoc(doc);

	return TRUE;

}
