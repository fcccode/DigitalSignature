// config.h: interface for the config class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIG_H__CEEE8877_45A4_45BA_8039_D6133D5FDE0F__INCLUDED_)
#define AFX_CONFIG_H__CEEE8877_45A4_45BA_8039_D6133D5FDE0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <libxml/parser.h>
#include <securexml/ax.h>
#include <securexml/errors.h>
#include <securexml/utils.h>
#include <securexml/DebugLog.h>


class CConfig  
{
public:
	BOOL setConfigDetails(BSTR confXMLStr);
	void getConfigDetailsFromDom(xmlNodePtr startNode);

	static const xmlChar *appSettings;
	static const xmlChar *envelopingFlag;
	static const xmlChar *addWindowImage;
	static const xmlChar *captureOnce;
	static const xmlChar *crlChecking;
	static const xmlChar *physicalSignatureFile;
	static const xmlChar *physicalSignatureUsage;
	static const xmlChar *timeStampURL;
	static const xmlChar *timeStamping;
	static const xmlChar *timeStampFormat;
	static const xmlChar *timeStampCritical;
	static const xmlChar *doDCompliance;
	static const xmlChar *certificateTrustExplicit;
	static const xmlChar *trustedRootCount;
	static const xmlChar *trustedRoot;
	static const xmlChar *certificatePolicyExplicit;
	static const xmlChar *certificatePathLengthChecking;
	static const xmlChar *certificateChainValidation;
	static const xmlChar *certificatePolicyChecking;
	static const xmlChar *certificatePolicyCount;
	static const xmlChar *certificatePolicy;
	static const xmlChar *cRLLocationCount;
	static const xmlChar *cRLLocation;
	static const xmlChar *overwriteFile;
	static const xmlChar *excludeSignerCertificate;
	static const xmlChar *detailedVerificationFlag;
	static const xmlChar *base64EncodeXML;
	static const xmlChar *base64DecodeXML;
	static const xmlChar *includeCamResponse;
	static const xmlChar *camServerHost;
	static const xmlChar *camServerPort;
	static const xmlChar *useCam;
	static const xmlChar *agencyId;
	static const xmlChar *allowedCertIssuerCount;
	static const xmlChar *allowedCertIssuerName;
	static const xmlChar *crlCacheDbConnectionString;
	static const xmlChar *useCRLCache;
	static const xmlChar *crlCacheTimeoutInMinutes;

	BOOL getConfigDetails(PGLOBAL_SIG);
	char *ConfigFile;
	BSTR sgarr;
	class CSignature *curSig;
	
	void setConfigFile(char *configFile) {
		ConfigFile = (char *)zMalloc(strlen(configFile) + 1);
		strcpy(ConfigFile, configFile);
	}

	

	CConfig()
	{
		ConfigFile = NULL;
	}
	CConfig(CSignature *curSig);
	virtual ~CConfig();

};

#endif // !defined(AFX_CONFIG_H__CEEE8877_45A4_45BA_8039_D6133D5FDE0F__INCLUDED_)
