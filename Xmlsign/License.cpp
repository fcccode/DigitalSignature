// License.cpp: implementation of the License class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include <fstream>
#include <securexml/base64.h>

#if __cplusplus
extern "C" {
#endif

#include <securexml/xs.h>
#include <securexml/utils.h>
#include <libxml/xmlschemas.h>
#include <securexml/DebugLog.h>

#ifdef SOLARIS
#include <string.h>
extern char * strcasestr(const char* haystack, const char* needle);
#endif

#if __cplusplus
}
#endif

#ifndef WIN32
#define USES_CONVERSION
#endif

#include "License.h"

#ifdef UNIX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define StrStrI strcasestr
extern void GetSystemTimeLinux(SYSTEMTIME *);
#endif

unsigned char * HeapW2A(BSTR bstrStr);

const xmlChar *CLicense::LICENSE = (const xmlChar *)"SecureXMLLicense";
const xmlChar *CLicense::VERSION = (const xmlChar *)"Version";
const xmlChar *CLicense::EXP_DATE = (const xmlChar *)"Expiration";
const xmlChar *CLicense::MAINT_EXP_DATE = (const xmlChar *)"MaintenanceExpiration";
const xmlChar *CLicense::ISSUE_DATE = (const xmlChar *)"IssueDate";
const xmlChar *CLicense::YEAR = (const xmlChar *)"Year";
const xmlChar *CLicense::MON = (const xmlChar *)"Month";
const xmlChar *CLicense::DAY = (const xmlChar *)"Day";
const xmlChar *CLicense::OPERATIONS = (const xmlChar *)"Operations";
const xmlChar *CLicense::VERIFY = (const xmlChar *)"Verify";
const xmlChar *CLicense::CREATE = (const xmlChar *)"Create";
const xmlChar *CLicense::ENCRYPT = (const xmlChar *)"Encrypt";
const xmlChar *CLicense::DECRYPT = (const xmlChar *)"Decrypt";
const xmlChar *CLicense::SECURESIGN = (const xmlChar *)"SecureSign";
const xmlChar *CLicense::SECURESIGNPROFESSIONAL = (const xmlChar *)"SecureSignProfessional";
const xmlChar *CLicense::SECURESIGNENTERPRISE = (const xmlChar *)"SecureSignEnterprise";
const xmlChar *CLicense::SECURESIGNSERVER = (const xmlChar *)"SecureSignServer";
const xmlChar *CLicense::TYPE = (const xmlChar *)"Type";
const xmlChar *CLicense::SERVER = (const xmlChar *)"Server";
const xmlChar *CLicense::CLIENT = (const xmlChar *)"Client";
const xmlChar *CLicense::DEMO = (const xmlChar *)"Demo";
const xmlChar *CLicense::DEVELOPMENT = (const xmlChar *)"Development";
const xmlChar *CLicense::LICENSE_KEY = (const xmlChar *)"LicenseKey";
const xmlChar *CLicense::NUM_LICENSE = (const xmlChar *)"NumLicense";
const xmlChar *CLicense::WINDOWS_CLIENT = (const xmlChar *)"WindowsClient";
const xmlChar *CLicense::LINUX_CLIENT = (const xmlChar *)"LinuxClient";
const xmlChar *CLicense::MAC_CLIENT = (const xmlChar *)"MacClient";
const xmlChar *CLicense::SOLARIS_CLIENT = (const xmlChar *)"SolarisClient";
const xmlChar *CLicense::SIGNATURE = (const xmlChar *)"Signature";

const xmlChar *CLicense::LICENSEE = (const xmlChar *)"Licensee";
const xmlChar *CLicense::LICENSER = (const xmlChar *)"Licensor";
const xmlChar *CLicense::COMPANY = (const xmlChar *)"Company";
const xmlChar *CLicense::USER = (const xmlChar *)"User";
const xmlChar *CLicense::HOSTNAME = (const xmlChar *)"HostName";

static inline void SysFreeStringLocal(BSTR str)
{
    DWORD* bufferPointer;

    /* NULL is a valid parameter */
    if(!str) return;

    /*
     * We have to be careful when we free a BSTR pointer, it points to
     * the beginning of the string but it skips the byte count contained
     * before the string.
     */
    bufferPointer = (DWORD*)str;
        
    bufferPointer--;
        
    /*
     * Free the memory from its "real" origin.
     */
    zFree(bufferPointer);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLicense::CLicense()
{

	licenseFile = NULL;
	isLicenseValid = TRUE; // By default the license is valid

	licenseKey = NULL;
	expYear = expMon = expDay = 0;
	issYear = issMon = issDay = 0;
	maintExpYear = maintExpMon = maintExpDay = 0;
	num_of_lic = 0;


	long osType;

	osType = getHostOsType();

	if ((osType != 0) && (osType != VER_NT_WORKSTATION))
		 /* It is not a client machine as it is some sort of windows server product */
	{
		isVerifyAllowed = FALSE;
		isDecryptAllowed = FALSE;
	}
	else
	{
		isVerifyAllowed = TRUE; // Verification is always allowed for client machines
		isDecryptAllowed = TRUE; // Decryption is always allowed for client machines
	}
	
	isSignAllowed = FALSE;
	isEncryptAllowed = FALSE;
	isSecureSignAllowed = FALSE;
	isSecureSignProfessionalAllowed = FALSE;
	isSecureSignEnterpriseAllowed = FALSE;

	isSecureSignServerAllowed = FALSE;

	isServerLic = FALSE;
	isClientLic = FALSE;
	isDemoLic	= TRUE; /* by default every license is a demo license */
	isDevelopmentLic = FALSE;
	isLicenseFloating = FALSE;

	sigArr = NULL;
	signum = 0;

	licenser = company = user = hostname = version = NULL;
	num_of_lic = 0;
	linuxClient = windowsClient = solarisClient = macClient = 0;
#ifdef WIN32
#ifdef FREE_SECURESIGN
	LPSTR commandLine = _strlwr(GetCommandLine());
	if (strstr(commandLine, "securesign.exe") != NULL)
	{
		isSignAllowed = TRUE;
		isVerifyAllowed = TRUE;
		isSecureSignAllowed = TRUE;
		isEncryptAllowed = TRUE;
	}
#endif
#endif
}

CLicense::~CLicense()
{
#ifdef WIN32
	SysFreeString(licenseKey);
	SysFreeString(licenser);
	SysFreeString(company);
	SysFreeString(user);
	SysFreeString(hostname);
	SysFreeString(version);
#else
	SysFreeStringLocal(licenseKey);
	SysFreeStringLocal(licenser);
	SysFreeStringLocal(company);
	SysFreeStringLocal(user);
	SysFreeStringLocal(hostname);
	SysFreeStringLocal(version);
#endif
}


/**
 * getLicenseDetails:
 *
 * Open the file at LicenseKeyFile. Verify the signature of the file
 * Get the details from the signed xml file and assign the values of
 * the variables appropriately.
 *
 */

BOOL CLicense::getLicenseDetails(PGLOBAL_SIG SigHandle) {

	xmlDocPtr doc = NULL;
	unsigned char *tmpCharPtr=NULL;

	doc = xmlParseFile((const char *)licenseFile);
	if (!doc) {
		// cout << "Couldn't parse the license file" << endl;
		setError(SigHandle, XML_PARSER_ERROR);
		return FALSE;
	}

	xmlNodePtr root = xmlDocGetRootElement(doc);
	xmlNodePtr curr = root->xmlChildrenNode;
	// cout << "Root element name is " << root->name << endl;

	for ( ; curr != NULL; curr = curr->next) {

		if (! xmlStrcmp(curr->name, VERSION)) {
			tmpCharPtr = xmlNodeListGetString(doc, curr->xmlChildrenNode, 1);
			version = A2WBSTR((const char *)tmpCharPtr);
			xmlFree(tmpCharPtr);
			continue;
		}

		if (! xmlStrcmp(curr->name, LICENSER)) {
			tmpCharPtr = xmlNodeListGetString(doc, curr->xmlChildrenNode, 1);
			licenser = A2WBSTR((const char *)tmpCharPtr);
			xmlFree(tmpCharPtr);
			continue;
		}

		if (! xmlStrcmp(curr->name, LICENSEE)) {
			xmlNodePtr licensee = curr->xmlChildrenNode;
			while (licensee != NULL) {
				if (! xmlStrcmp(licensee->name, COMPANY))
				{
					tmpCharPtr = xmlNodeListGetString(doc, licensee->xmlChildrenNode, 1);
					company = A2WBSTR((const char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
				}
				if (! xmlStrcmp(licensee->name, USER))
				{
					tmpCharPtr = xmlNodeListGetString(doc, licensee->xmlChildrenNode, 1);
					user = A2WBSTR((const char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
				}
				if (! xmlStrcmp(licensee->name, HOSTNAME))
				{
					tmpCharPtr = xmlNodeListGetString(doc, licensee->xmlChildrenNode, 1);
					hostname = A2WBSTR((const char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
				}
				licensee = licensee->next;
			}
			continue;
		}

		if (! xmlStrcmp(curr->name, EXP_DATE)) {
			xmlNodePtr date = curr->xmlChildrenNode;
			while (date != NULL) {
				if (! xmlStrcmp(date->name, YEAR))
				{
					tmpCharPtr = xmlNodeListGetString(doc, date->xmlChildrenNode, 1);
					expYear = atoi((char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
				}
				if (! xmlStrcmp(date->name, MON))
				{
					tmpCharPtr = xmlNodeListGetString(doc, date->xmlChildrenNode, 1);
					expMon = atoi((char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
				}
				if (! xmlStrcmp(date->name, DAY))
				{
					tmpCharPtr = xmlNodeListGetString(doc, date->xmlChildrenNode, 1);
					expDay = atoi((char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
				}
				date = date->next;
			}
			continue;
		}

		if (! xmlStrcmp(curr->name, MAINT_EXP_DATE)) {
			xmlNodePtr date = curr->xmlChildrenNode;
			while (date != NULL) {
				if (! xmlStrcmp(date->name, YEAR))
				{
					tmpCharPtr = xmlNodeListGetString(doc, date->xmlChildrenNode, 1);
					maintExpYear = atoi((char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
				}
				if (! xmlStrcmp(date->name, MON))
				{
					tmpCharPtr = xmlNodeListGetString(doc, date->xmlChildrenNode, 1);
					maintExpMon = atoi((char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
				}
				if (! xmlStrcmp(date->name, DAY))
				{
					tmpCharPtr = xmlNodeListGetString(doc, date->xmlChildrenNode, 1);
					maintExpDay = atoi((char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
				}
				date = date->next;
			}
			continue;
		}

		if (! xmlStrcmp(curr->name, ISSUE_DATE)) {
			xmlNodePtr date = curr->xmlChildrenNode;
			while (date != NULL) {
				if (! xmlStrcmp(date->name, YEAR))
				{
					tmpCharPtr = xmlNodeListGetString(doc, date->xmlChildrenNode, 1);
					issYear = atoi((char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
				}
				if (! xmlStrcmp(date->name, MON))
				{
					tmpCharPtr = xmlNodeListGetString(doc, date->xmlChildrenNode, 1);
					issMon = atoi((char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
				}
				if (! xmlStrcmp(date->name, DAY))
				{
					tmpCharPtr = xmlNodeListGetString(doc, date->xmlChildrenNode, 1);
					issDay = atoi((char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
				}
				date = date->next;
			}
			continue;
		}

		if (! xmlStrcmp(curr->name, OPERATIONS)) {
			xmlNodePtr op = curr->xmlChildrenNode;
			while (op != NULL) {
				int tmpInt;

				if (op->xmlChildrenNode != NULL)
				{
					tmpCharPtr = xmlNodeListGetString(doc, op->xmlChildrenNode, 1);
					tmpInt = atoi((char *)tmpCharPtr);
					xmlFree(tmpCharPtr);
					if (! xmlStrcmp(op->name, VERIFY))
						isVerifyAllowed = tmpInt;

					if (! xmlStrcmp(op->name, CREATE))
						isSignAllowed = tmpInt;

					if (! xmlStrcmp(op->name, ENCRYPT))
						isEncryptAllowed = tmpInt;

					if (! xmlStrcmp(op->name, DECRYPT))
						isDecryptAllowed = tmpInt;

					if (! xmlStrcmp(op->name, SECURESIGN))
						isSecureSignAllowed = tmpInt;

					if (! xmlStrcmp(op->name, SECURESIGNPROFESSIONAL))
						isSecureSignProfessionalAllowed = tmpInt;

					if (! xmlStrcmp(op->name, SECURESIGNENTERPRISE))
						isSecureSignEnterpriseAllowed = tmpInt;

					if (! xmlStrcmp(op->name, SECURESIGNSERVER))
						isSecureSignServerAllowed = tmpInt;
				}
				op = op->next;
			}
			continue;
		}

		if (! xmlStrcmp(curr->name, TYPE)) {
			xmlNodePtr type = curr->xmlChildrenNode;
			while (type != NULL) {
				int tmpInt;

				if (type->xmlChildrenNode != NULL)
				{
					tmpCharPtr = xmlNodeListGetString(doc, type->xmlChildrenNode, 1);
					tmpInt = atoi((char *)tmpCharPtr);
					xmlFree(tmpCharPtr);

					if (! xmlStrcmp(type->name, SERVER))
						isServerLic = tmpInt;

					if (! xmlStrcmp(type->name, CLIENT))
						isClientLic = tmpInt;

					if (! xmlStrcmp(type->name, DEMO))
						isDemoLic = tmpInt;

					if (! xmlStrcmp(type->name, DEVELOPMENT))
						isDevelopmentLic = tmpInt;
				}

				type = type->next;
			}
			continue;
		}

		if (! xmlStrcmp(curr->name, LICENSE_KEY)) {
			tmpCharPtr = xmlNodeListGetString(doc, curr->xmlChildrenNode, 1);
			licenseKey = A2WBSTR((const char *)tmpCharPtr);
			xmlFree(tmpCharPtr);
			continue;
		}

		if (! xmlStrcmp(curr->name, NUM_LICENSE)) {
			tmpCharPtr = xmlNodeListGetString(doc, curr->xmlChildrenNode, 1);
			num_of_lic = atoi((char *)tmpCharPtr);
			xmlFree(tmpCharPtr);
			continue;
		}
		
		if (! xmlStrcmp(curr->name, WINDOWS_CLIENT)) {
			tmpCharPtr = xmlNodeListGetString(doc, curr->xmlChildrenNode, 1);
			windowsClient = atoi((char *)tmpCharPtr);
			xmlFree(tmpCharPtr);
			continue;
		}

		if (! xmlStrcmp(curr->name, SOLARIS_CLIENT)) {
			tmpCharPtr = xmlNodeListGetString(doc, curr->xmlChildrenNode, 1);
			solarisClient = atoi((char *)tmpCharPtr);
			xmlFree(tmpCharPtr);
			continue;
		}
		if (! xmlStrcmp(curr->name, LINUX_CLIENT)) {
			tmpCharPtr = xmlNodeListGetString(doc, curr->xmlChildrenNode, 1);
			linuxClient = atoi((char *)tmpCharPtr);
			xmlFree(tmpCharPtr);
			continue;
		}
		if (! xmlStrcmp(curr->name, MAC_CLIENT)) {
			tmpCharPtr = xmlNodeListGetString(doc, curr->xmlChildrenNode, 1);
			macClient = atoi((char *)tmpCharPtr);
			xmlFree(tmpCharPtr);
			continue;
		}
	}

	xmlFreeDoc(doc);

	return TRUE;
}

long CLicense::getHostOsType(void)
{
    BOOL bOsVersionInfoEx;
	OSVERSIONINFOEX osvi;
   // Try calling GetVersionEx using the OSVERSIONINFOEX structure.
   // If that fails, try using the OSVERSIONINFO structure.

   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

#ifdef WIN32
   if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
   {
      // If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
      osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
      if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
	  {
		  return 0;
	  }
   }
#endif
#ifdef LOGGING
   char buffer[BUFSIZ];
   ZeroMemory(buffer, BUFSIZ);
   sprintf((char *)buffer, "dwOSVersionInfoSize = %x", osvi.dwOSVersionInfoSize);
   DebugLog((const char *)buffer);
   sprintf((char *)buffer, "dwBuildNumber = %x", osvi.dwBuildNumber);
   DebugLog((const char *)buffer);
   sprintf((char *)buffer, "dwMajorVersion = %x", osvi.dwMajorVersion);
   DebugLog((const char *)buffer);
   sprintf((char *)buffer, "dwMinorVersion = %x", osvi.dwMinorVersion);
   DebugLog((const char *)buffer);
   sprintf((char *)buffer, "dwPlatformId = %x", osvi.dwPlatformId);
   DebugLog((const char *)buffer);
   sprintf((char *)buffer, "wProductType = %x", osvi.wProductType);
   DebugLog((const char *)buffer);
#endif
   return( (long) osvi.wProductType);
}

BOOL CLicense::verifyLicense(PGLOBAL_SIG SigHandle) {

	ULONG crcValue=0xff01ff01;
	// Here we are verifying the signature of the license file.
	// If license file is modified, the signature verification will fail.
	int ret_val = axVerifyFile((const xmlChar *)licenseFile, NULL, FALSE, -1, SigHandle);
	if (!ret_val) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		isSignAllowed = FALSE;
		return FALSE;
	}
	// We also need to verify that the license is signed with our certificate

	// Sizes of the strings 1024 + 1024 + 460
	sigArr = axGetSignature(&signum, SigHandle);
	if (signum != 1) {
		// There can't be more than one signature in the license file.
		setError(SigHandle, INVALID_SECUREXML_LIC);
		isSignAllowed = FALSE;
		xsFree(SigHandle);
		return FALSE;
	}
	string cert_in_lic;
	
	if (sigArr[0]->signerCert && sigArr[0]->signerCert->certificate)
		cert_in_lic = (char *)(sigArr[0]->signerCert->certificate);
	else {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		isSignAllowed = FALSE;
		xsFree(SigHandle);
		return FALSE;
	}
	xsFree(SigHandle);
	// This is the certificate that should be used to create XML Licenses for
	// Infomosaic Corporation. This is being incorporated into the birary
	// executable to check against the license used.

	const string Cert1 = "MIIHVDCCBjygAwIBAgIKJbmN0QAAAAABVDANBgkqhkiG9w0BAQUFADCBvzEiMCAGCSqGSIb3DQEJARYTaW5mb0BpbmZvbW9zYWljLmNvbTELMAkGA1UEBhMCVVMxCzAJBgNVBAgTAkNBMREwDwYDVQQHEwhTYW4gSm9zZTEfMB0GA1UEChMWSW5mb21vc2FpYyBDb3Jwb3JhdGlvbjEqMCgGA1UECxMhWE1MIERpZ2l0YWwgU2lnbmF0dXJlIERldmVsb3BtZW50MR8wHQYDVQQDExZJbmZvbW9zYWljIENvcnBvcmF0aW9uMB4XDTAyMDUyMzIzMjYxN1oXDTAzMDUyMzIzMzYxN1owgcIxIzAhBgkqhkiG9w0BCQEWFHNhbGVzQGluZm9tb3NhaWMuY29tMQswCQYDVQQGEwJVUzELMAkGA1UECBMCQ0ExETAPBgNVBAcTCFNhbiBKb3NlMR8wHQYDVQQKExZJbmZvbW9zYWljIENvcnBvcmF0aW9uMSowKAYDVQQLEyFYTUwgRGlnaXRhbCBTaWduYXR1cmUgRGV2ZWxvcG1lbnQxITAfBgNVBAMTGFNlY3VyZVhNTCBMaWNlbnNlIFNpZ25lcjCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAvpEsRpF1jACKaOFENwvBnk47MnBywKvwZ3asWNLr+L3ibjrsxpA+yBMRbRXoYaEK4goGyH2qdANCfBPc0SMwiAWSY/moSSRBxcqL5kmgMeJB37Lw6cKy0HU2UC9kwg5bXgdBn2JeM4sN+/n4No7iteft75zuqGI8Z0BqNOQ2m+cCAwEAAaOCA88wggPLMA4GA1UdDwEB/wQEAwIE8DATBgNVHSUEDDAKBggrBgEFBQcDAjAdBgNVHQ4EFgQUBn2JDstuotvk/TRfp7CvueNy/oowgfsGA1UdIwSB8zCB8IAUyDoe8/LPn+bACFA7aurljP5Nte6hgcWkgcIwgb8xIjAgBgkqhkiG9w0BCQEWE2luZm9A";
// Insert some junk data so that search for X509 cert match in the dll fails
	const int	 junk1[5] = {0xff01ff01, 0x0112abcd, 0x45fa23cd, 0x010afc01, 0x4578fbd1};
	const string Cert3 = "cnRFbnJvbGwvaW5mb21vc2FpYy1zcnZyLmluZm9tb3NhaWMubmV0X0luZm9tb3NhaWMlMjBDb3Jwb3JhdGlvbi5jcnQwDQYJKoZIhvcNAQEFBQADggEBAKcMX8EMUUnaLgv+d31IpemMMlDDmvUlPLu6T/sFsh3j7eQrjUhsVKTZ303Q+2dh0Qv7REfPLCb1T1Uxbj9bCaEh2UVZSwDdDXETO5QztkLyQZXWPfaUMbHQU/sXMZ7PZBfVo6pMRSTKKY7Lc7wWuDI4HsKDt1Ny2LTyZZdei3LNwLA3WhxuYDzrrTYL0IDOU4HxYhSsQqRUPWhZzBL0QKH/KBspukXK8X5ZdSNJKHDcdyqftaln5FSrh/uth+9fdJIRiJhXKSvnotetBsTRRz4DAR6yLyLou8LTYhfFKHRi7ZOAKmbpkQhtdqXXMkzSoUqvnCIJ5w9WkQGP/9WBKT4=";	
// Insert some junk data so that search for X509 cert match in the dll fails
	const int	 junk2[5] = { 0x0112abcd, 0xff01ff01, 0x45fa23cd, 0x4578fbd1, 0x010afc01};
	const string Cert2 = "aW5mb21vc2FpYy5jb20xCzAJBgNVBAYTAlVTMQswCQYDVQQIEwJDQTERMA8GA1UEBxMIU2FuIEpvc2UxHzAdBgNVBAoTFkluZm9tb3NhaWMgQ29ycG9yYXRpb24xKjAoBgNVBAsTIVhNTCBEaWdpdGFsIFNpZ25hdHVyZSBEZXZlbG9wbWVudDEfMB0GA1UEAxMWSW5mb21vc2FpYyBDb3Jwb3JhdGlvboIQN2ikHVFArblPpz2OZYaSNjCCATgGA1UdHwSCAS8wggErMIHToIHQoIHNhoHKbGRhcDovLy9DTj1JbmZvbW9zYWljJTIwQ29ycG9yYXRpb24sQ049aW5mb21vc2FpYy1zcnZyLENOPUNEUCxDTj1QdWJsaWMlMjBLZXklMjBTZXJ2aWNlcyxDTj1TZXJ2aWNlcyxDTj1Db25maWd1cmF0aW9uLERDPWluZm9tb3NhaWMsREM9bmV0P2NlcnRpZmljYXRlUmV2b2NhdGlvbkxpc3Q/YmFzZT9vYmplY3RjbGFzcz1jUkxEaXN0cmlidXRpb25Qb2ludDBToFGgT4ZNaHR0cDovL2luZm9tb3NhaWMtc3J2ci5pbmZvbW9zYWljLm5ldC9DZXJ0RW5yb2xsL0luZm9tb3NhaWMlMjBDb3Jwb3JhdGlvbi5jcmwwggFJBggrBgEFBQcBAQSCATswggE3MIG6BggrBgEFBQcwAoaBrWxkYXA6Ly8vQ049SW5mb21vc2FpYyUyMENvcnBvcmF0aW9uLENOPUFJQSxDTj1QdWJsaWMlMjBLZXklMjBTZXJ2aWNlcyxDTj1TZXJ2aWNlcyxDTj1Db25maWd1cmF0aW9uLERDPWluZm9tb3NhaWMsREM9bmV0P2NBQ2VydGlmaWNhdGU/YmFzZT9vYmplY3RjbGFzcz1jZXJ0aWZpY2F0aW9uQXV0aG9yaXR5MHgGCCsGAQUFBzAChmxodHRwOi8vaW5mb21vc2FpYy1zcnZyLmluZm9tb3NhaWMubmV0L0Nl";

	string X509Cert = Cert1 + Cert2 + Cert3;

	Get_CRC_CheckSum((PVOID) X509Cert.c_str(), (ULONG) X509Cert.length(), &crcValue);
	if (crcValue != 0xE771) // Someone patched the dll with a different X509 cert
	{
		setError(SigHandle, INVALID_SECUREXML_LIC);
		isSignAllowed = FALSE;
		return FALSE;
	}
	if (X509Cert != cert_in_lic) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		isSignAllowed = FALSE;
		return FALSE;
	}
	// Now check the date etc.. of the license.
	SYSTEMTIME t;
#ifdef WIN32
	GetSystemTime(&t);
#else
	GetSystemTimeLinux(&t);
#endif
	int currYear = t.wYear;
	int currMon = t.wMonth;
	int currDay = t.wDay;

	bool isexp = true;
	if (currYear < expYear)
		isexp = false;
	else if (currYear == expYear)
		if (currMon < expMon)
			isexp = false;
		else if (currMon == expMon)
			if (currDay <= expDay)
				isexp = false;

	if (isexp) {
		setError(SigHandle, LICENSE_EXPIRED);
		isSignAllowed = FALSE;
		num_of_lic = 0;
		return FALSE;
	}

#ifdef WIN32
	releaseYear = releaseTime.GetYear();
	releaseMonth = releaseTime.GetMonth();
	releaseDay = releaseTime.GetDay();
#endif

	isexp = true;
	if (releaseYear < maintExpYear)
		isexp = false;
	else
	{
		if (releaseYear == maintExpYear)
		{
			if (releaseMonth < maintExpMon)
				isexp = false;
			else 
			{
				if (releaseMonth == maintExpMon)
				{
					if (releaseDay <= maintExpDay)
					{
						isexp = false;
					}
				}
			}
		}
	}

	if (isexp) {
		setError(SigHandle, LICENSE_EXPIRED);
		isSignAllowed = FALSE;
		isVerifyAllowed = FALSE; // Maintenance has expired so don't allow either sign or verify
		num_of_lic = 0;
		return FALSE;
	}

	char lpBuffer[MAX_PATH];
	unsigned long lpnSize=MAX_PATH;
	char *licHostName;

USES_CONVERSION;

	licHostName = (char *)HeapW2A(hostname);
	if (strcmp((const char *)licHostName,"TrialHost"))
	{
#ifdef WIN32
		GetComputerName( lpBuffer,  // name buffer
						&lpnSize                // size of name buffer
						);
#else
		gethostname(lpBuffer, MAX_PATH);
#endif
		if (!(StrStrI((const char *)licHostName, (const char *)lpBuffer)))
		{
			setError(SigHandle, INVALID_SECUREXML_LIC);
			isSignAllowed = FALSE;
			zFree(licHostName);
			return FALSE;
		}
	}
	zFree(licHostName);

	long osType;

	osType = getHostOsType();
	if ((osType != 0) && (osType != VER_NT_WORKSTATION))
		 /* It is not a client machine as it is some sort of windows server product */
	{
		if (isServerLic == FALSE)
		{
			setError(SigHandle, INVALID_SECUREXML_LIC);
			isLicenseValid = FALSE;
			return FALSE;
		}
	}
	else
	{
		if (isClientLic == FALSE)
		{
			setError(SigHandle, INVALID_SECUREXML_LIC);
			isSignAllowed = FALSE;
			return FALSE;
		}
	}

	// We verified the values in the license file.

	isLicenseValid = TRUE;
	return TRUE;
}

WORD wCRC16a[16]={
    0000000,    0140301,    0140601,    0000500,
    0141401,    0001700,    0001200,    0141101,
    0143001,    0003300,    0003600,    0143501,
    0002400,    0142701,    0142201,    0002100,
};
WORD wCRC16b[16]={
    0000000,    0146001,    0154001,    0012000,
    0170001,    0036000,    0024000,    0162001,
    0120001,    0066000,    0074000,    0132001,
    0050000,    0116001,    0104001,    0043000,
};

void CLicense::Get_CRC_CheckSum(PVOID pBuffer, ULONG ulSize, PULONG pulSeed)
{
  PBYTE    pb;
  BYTE    bTmp;

  for (pb=(BYTE *)pBuffer; ulSize; ulSize--, pb++)
  {
    bTmp=(BYTE)(((WORD)*pb)^((WORD)*pulSeed));    // Xor CRC with new char
    *pulSeed=((*pulSeed)>>8) ^ wCRC16a[bTmp&0x0F] ^ wCRC16b[bTmp>>4];
  }
}

void CLicense::verifyFloatingLicense(unsigned char *inputXMLStr, unsigned long size, PGLOBAL_SIG SigHandle)
{
	const string cert4 = "LmluZm9tb3NhaWMubmV0X0luZm9tb3NhaWMlMjBDb3Jwb3JhdGlvbigxKS5jcnQwDQYJKoZIhvcNAQEFBQADggEBAFrOd7OXXrIwQB5Fz+AZTt2mgvdXkJlrneuWoyEF3DSoZfSdGqaORmWEdNcWbcxmN+xl81bWwCmdi99emBvH0sIEvS9u8y4c93zG/qg3+Icu3/KNYDGAXBWJFdnCyTPfBdhTw1AmXOHepQ9i2C51S4wA8keQoaH1yCwQjcSA3cRAlweg0BkpBM1NRx+jOlMgLmCETb+8iZ1vDQZ0SBulO60cX7pdD/cQUE5mbeII/enkaECj8eC9CuPrhmL5D3B0xSgXOGryWNIAl1gcIM2+wt+D92vN8n0WiZ1LA9DNvZPY17DePeEEwxk1Kd33C+F9Tw9q57b4rsjY/PaM9Gi8FG0=";
	const int	 junk1[5] = {0xff01ff01, 0x0112abcd, 0x45fa23cd, 0x010afc01, 0x4578fbd1};
	const string cert2 = "b24xJjAkBgNVBAsTHU1ha2luZyBEaWdpdGFsIFNpZ25hdHVyZSBFYXN5MSowKAYDVQQDEyFTZWN1cmVYTUwgRmxvYXRpbmcgTGljZW5zZSBJc3N1ZXIwgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBALgb0p8Fh0O1DwZyXDONau+SqVvM3IDvqDDjMLQ8uR4BnGXjiGqgjdrH4obZekYYcjWIWu01vPMAYYHH198gmsFxHphndAsPllBUl0iX4JEhyBtZAo7koED+J+9aMNkVAjkA4AG17Z/MfglAH+/EwsvI9nPwwsW1P9lFcQsZivIxAgMBAAGjggIzMIICLzAOBgNVHQ8BAf8EBAMCBPAwEwYDVR0lBAwwCgYIKwYBBQUHAwIwHQYDVR0OBBYEFAX3Ts8591e+/KCE4jgHJqKw5EqzMIH6BgNVHSMEgfIwge+AFMg6HvPyz5/mwAhQO2rq5Yz+TbXuoYHEpIHBMIG+MSIwIAYJKoZIhvcNAQkB";
	const int	 junk2[5] = { 0x0112abcd, 0xff01ff01, 0x45fa23cd, 0x4578fbd1, 0x010afc01};
	const string cert1 = "MIIFvzCCBKegAwIBAgIKFDX9YgABAAAG5DANBgkqhkiG9w0BAQUFADCBvjEiMCAGCSqGSIb3DQEJARYTaW5mb0BpbmZvbW9zYWljLmNvbTELMAkGA1UEBhMCVVMxCzAJBgNVBAgTAkNBMRQwEgYDVQQHEwtTYW50YSBDbGFyYTEfMB0GA1UEChMWSW5mb21vc2FpYyBDb3Jwb3JhdGlvbjEmMCQGA1UECxMdTWFraW5nIERpZ2l0YWwgU2lnbmF0dXJlIEVhc3kxHzAdBgNVBAMTFkluZm9tb3NhaWMgQ29ycG9yYXRpb24wHhcNMDMxMDAzMjIyOTUxWhcNMTMxMDAzMjE1OTUzWjCByjEjMCEGCSqGSIb3DQEJARYUc2FsZXNAaW5mb21vc2FpYy5jb20xCzAJBgNVBAYTAlVTMQswCQYDVQQIEwJDQTEUMBIGA1UEBxMLU2FudGEgQ2xhcmExHzAdBgNVBAoTFkluZm9tb3NhaWMgQ29ycG9yYXRp";
	const int	 junk3[5] = { 0x0112a123, 0xff01ff01, 0x45fa23cd, 0x4578fbd1, 0x010afc01};
	const string cert3 = "FhNpbmZvQGluZm9tb3NhaWMuY29tMQswCQYDVQQGEwJVUzELMAkGA1UECBMCQ0ExFDASBgNVBAcTC1NhbnRhIENsYXJhMR8wHQYDVQQKExZJbmZvbW9zYWljIENvcnBvcmF0aW9uMSYwJAYDVQQLEx1NYWtpbmcgRGlnaXRhbCBTaWduYXR1cmUgRWFzeTEfMB0GA1UEAxMWSW5mb21vc2FpYyBDb3Jwb3JhdGlvboIQKiQ6i/TBzo1KZki1g15oZzBeBgNVHR8EVzBVMFOgUaBPhk1odHRwOi8vaW5mb21vc2FpYy1zcnZyLmluZm9tb3NhaWMubmV0L0NlcnRFbnJvbGwvSW5mb21vc2FpYyUyMENvcnBvcmF0aW9uLmNybDCBiwYIKwYBBQUHAQEEfzB9MHsGCCsGAQUFBzAChm9odHRwOi8vaW5mb21vc2FpYy1zcnZyLmluZm9tb3NhaWMubmV0L0NlcnRFbnJvbGwvaW5mb21vc2FpYy1zcnZy";

//	const string cert3 = "YmFzZT9vYmplY3RjbGFzcz1jZXJ0aWZpY2F0aW9uQXV0aG9yaXR5MHgGCCsGAQUFBzAChmxodHRwOi8vaW5mb21vc2FpYy1zcnZyLmluZm9tb3NhaWMubmV0L0NlcnRFbnJvbGwvaW5mb21vc2FpYy1zcnZyLmluZm9tb3NhaWMubmV0X0luZm9tb3NhaWMlMjBDb3Jwb3JhdGlvbi5jcnQwDQYJKoZIhvcNAQEFBQADggEBADkFy7R4bgPZoWi1v0Nro7J0ZSNpa8xAuzgwa9ff5dJDuiB3ER4EAiws5O3DFUv8W0dfsFX262PJKk1jkcIRwox7e5ZzKU+1XUVc6vM9vXk1lvYiNsy5n4h9fUskMJNnotky2Z8SZ/7vL+iGeOP9Wti5U779Ues2BxZMHaFYR+dzWpz6xC64rqwSBDeZq3VIXFfXnS3q7yqEGS287Q4P8jAntM7ImN2brFieSL597nNSW7pEOlFRV462A3IPzTTjQSoS5M99XqIyCfw+NL8oyfOoV8mhVm0JmqlodYAelJpwDswGUuzdSjJl91iBluMJR0uMx4mE+KkeV1+r7HF7A4U=";
// Insert some junk data so that search for X509 cert match in the dll fails
//	const string cert2 = "/7Ufng45apgE7V1MIH6BgNVHSMEgfIwge+AFMg6HvPyz5/mwAhQO2rq5Yz+TbXuoYHEpIHBMIG+MSIwIAYJKoZIhvcNAQkBFhNpbmZvQGluZm9tb3NhaWMuY29tMQswCQYDVQQGEwJVUzELMAkGA1UECBMCQ0ExFDASBgNVBAcTC1NhbnRhIENsYXJhMR8wHQYDVQQKExZJbmZvbW9zYWljIENvcnBvcmF0aW9uMSYwJAYDVQQLEx1NYWtpbmcgRGlnaXRhbCBTaWduYXR1cmUgRWFzeTEfMB0GA1UEAxMWSW5mb21vc2FpYyBDb3Jwb3JhdGlvboIQdOykPAAmzJZAPfFU7pEKWDCCATgGA1UdHwSCAS8wggErMIHToIHQoIHNhoHKbGRhcDovLy9DTj1JbmZvbW9zYWljJTIwQ29ycG9yYXRpb24sQ049aW5mb21vc2FpYy1zcnZyLENOPUNEUCxDTj1QdWJsaWMlMjBLZXklMjBTZXJ2aWNlcyxDTj1TZXJ2aWNlcyxDTj1Db25maWd1cmF0aW9uLERDPWluZm9tb3NhaWMsREM9bmV0P2NlcnRpZmljYXRlUmV2b2NhdGlvbkxpc3Q/YmFzZT9vYmplY3RjbGFzcz1jUkxEaXN0cmlidXRpb25Qb2ludDBToFGgT4ZNaHR0cDovL2luZm9tb3NhaWMtc3J2ci5pbmZvbW9zYWljLm5ldC9DZXJ0RW5yb2xsL0luZm9tb3NhaWMlMjBDb3Jwb3JhdGlvbi5jcmwwggFJBggrBgEFBQcBAQSCATswggE3MIG6BggrBgEFBQcwAoaBrWxkYXA6Ly8vQ049SW5mb21vc2FpYyUyMENvcnBvcmF0aW9uLENOPUFJQSxDTj1QdWJsaWMlMjBLZXklMjBTZXJ2aWNlcyxDTj1TZXJ2aWNlcyxDTj1Db25maWd1cmF0aW9uLERDPWluZm9tb3NhaWMsREM9bmV0P2NBQ2VydGlmaWNhdGU/";
// Insert some junk data so that search for X509 cert match in the dll fails
//	const string cert1 = "MIIHWjCCBkKgAwIBAgIKGg1iMAAAAAAGsjANBgkqhkiG9w0BAQUFADCBvjEiMCAGCSqGSIb3DQEJARYTaW5mb0BpbmZvbW9zYWljLmNvbTELMAkGA1UEBhMCVVMxCzAJBgNVBAgTAkNBMRQwEgYDVQQHEwtTYW50YSBDbGFyYTEfMB0GA1UEChMWSW5mb21vc2FpYyBDb3Jwb3JhdGlvbjEmMCQGA1UECxMdTWFraW5nIERpZ2l0YWwgU2lnbmF0dXJlIEVhc3kxHzAdBgNVBAMTFkluZm9tb3NhaWMgQ29ycG9yYXRpb24wHhcNMDMwOTEyMDAyMTM5WhcNMDQwOTEyMDAzMTM5WjCByjEjMCEGCSqGSIb3DQEJARYUc2FsZXNAaW5mb21vc2FpYy5jb20xCzAJBgNVBAYTAlVTMQswCQYDVQQIEwJDQTEUMBIGA1UEBxMLU2FudGEgQ2xhcmExHzAdBgNVBAoTFkluZm9tb3NhaWMgQ29ycG9yYXRpb24xJjAkBgNVBAsTHU1ha2luZyBEaWdpdGFsIFNpZ25hdHVyZSBFYXN5MSowKAYDVQQDEyFTZWN1cmVYTUwgRmxvYXRpbmcgTGljZW5zZSBJc3N1ZXIwgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBAOjh54QWn49CV32AgiWGReEAN4VkufrByl0QW8LblTfJu8C5Uge66I31M6puAz9HtXI+EFSIKbahbQpR4uM/wroeD5oEnL3kHiWyRRBipFqF5JkvMShg6x0Y+OTec1ooSEWkBkujsk4vW8wKsQGaxbjlxCfPvIsN7bzX1dpgWvBHAgMBAAGjggPOMIIDyjAOBgNVHQ8BAf8EBAMCBPAwEwYDVR0lBAwwCgYIKwYBBQUHAwIwHQYDVR0OBBYEFAByQ3GdrZYaO";
	ULONG crcValue=0xff01ff01;
	
	string X509Cert = cert1 + cert2 + cert3 + cert4;

	EnterLog;
//	DebugBreak();

	// Here we are verifying the signature of the license file.
	// If license file is modified, the signature verification will fail.
	int ret_val = axVerify((const xmlChar *)inputXMLStr, size, NULL, FALSE, -1, 1, SigHandle);
	if (!ret_val) {
		DebugLog("axVerify() for floating license xml failed");
		setError(SigHandle, INVALID_SECUREXML_LIC);
		isSignAllowed = FALSE;
		return;
	}

	// We also need to verify that the license is signed with our certificate

	// Sizes of the strings 1024 + 1024 + 460

	sigArr = axGetSignature(&signum, SigHandle);

	if (signum != 1) {
		// There can't be more than one signature in the license file.
		DebugLog("signum != 1 from axGetSignature() after axVerify() for floating license xml");
		setError(SigHandle, INVALID_SECUREXML_LIC);
		isSignAllowed = FALSE;
		return;
	}

	string cert_in_lic;
	
	if (sigArr[0]->signerCert && sigArr[0]->signerCert->certificate)
		cert_in_lic = (char *)(sigArr[0]->signerCert->certificate);
	else {
		DebugLog("Certificate not present in the output from axGetSignature()");
		setError(SigHandle, INVALID_SECUREXML_LIC);
		isSignAllowed = FALSE;
		return;
	}

	// This is the certificate that should be used to create floating Licenses for
	// Infomosaic Corporation. This is being incorporated into the birary
	// executable to check against the license used.
	Get_CRC_CheckSum((PVOID) X509Cert.c_str(), (ULONG) X509Cert.length(), &crcValue);
	if (crcValue != 0xF3E9) // Someone patched the dll with a different X509 cert
//	if (crcValue != 0x5C68) // Someone patched the dll with a different X509 cert
	{
		DebugLog("Checksum validation failed");
		setError(SigHandle, INVALID_SECUREXML_LIC);
		isSignAllowed = FALSE;
		return;
	}
	if (X509Cert != cert_in_lic) {
		DebugLog("X509 Data not the same as expected in floating license");
		setError(SigHandle, INVALID_SECUREXML_LIC);
		isSignAllowed = FALSE;
		return;
	}

	// Now check the date etc.. of the license.

	unsigned int length = strlen((const char *)(sigArr[0]->refArray[0]->refObject->encodedData));
	size = base64decodeSize(length);
	unsigned char *timeStr = (unsigned char *)zMalloc(size+1);
	if ((size = base64decode(sigArr[0]->refArray[0]->refObject->encodedData, timeStr, size+1)) == -1)
	{
		DebugLog("Base64 decode failed");
		setError(SigHandle, INVALID_SECUREXML_LIC);
		isLicenseFloating = FALSE;
		return;
	}
	int propNumber = sigArr[0]->propNumber;
	char *equalPtr=NULL;
	for (int i=0; i<propNumber; i++)
	{
		if (strstr((const char *)sigArr[0]->propArray[i], (const char *)"MaintExpiryYear") != NULL)
		{
			equalPtr = strchr((const char *)sigArr[0]->propArray[i], '=');
			maintExpYear = atoi((const char *)++equalPtr);
		}
		if (strstr((const char *)sigArr[0]->propArray[i], (const char *)"MaintExpiryMonth") != NULL)
		{
			equalPtr = strchr((const char *)sigArr[0]->propArray[i], '=');
			maintExpMon = atoi((const char *)++equalPtr);
		}
		if (strstr((const char *)sigArr[0]->propArray[i], (const char *)"MaintExpiryDay") != NULL)
		{
			equalPtr = strchr((const char *)sigArr[0]->propArray[i], '=');
			maintExpDay = atoi((const char *)++equalPtr);
		}
		if (strstr((const char *)sigArr[0]->propArray[i], (const char *)"LinuxClient") != NULL)
		{
			equalPtr = strchr((const char *)sigArr[0]->propArray[i], '=');
			linuxClient = atoi((const char *)++equalPtr);
		}
		if (strstr((const char *)sigArr[0]->propArray[i], (const char *)"WindowsClient") != NULL)
		{
			equalPtr = strchr((const char *)sigArr[0]->propArray[i], '=');
			windowsClient = atoi((const char *)++equalPtr);
		}
		if (strstr((const char *)sigArr[0]->propArray[i], (const char *)"SolarisClient") != NULL)
		{
			equalPtr = strchr((const char *)sigArr[0]->propArray[i], '=');
			solarisClient = atoi((const char *)++equalPtr);
		}
		if (strstr((const char *)sigArr[0]->propArray[i], (const char *)"MacClient") != NULL)
		{
			equalPtr = strchr((const char *)sigArr[0]->propArray[i], '=');
			macClient = atoi((const char *)++equalPtr);
		}
	}

#ifdef WIN32
	releaseYear = releaseTime.GetYear();
	releaseMonth = releaseTime.GetMonth();
	releaseDay = releaseTime.GetDay();
#endif
	
	bool isexp = true;
	if (releaseYear < maintExpYear)
		isexp = false;
	else
	{
		if (releaseYear == maintExpYear)
		{
			if (releaseMonth < maintExpMon)
				isexp = false;
			else 
			{
				if (releaseMonth == maintExpMon)
				{
					if (releaseDay <= maintExpDay)
					{
						isexp = false;
					}
				}
			}
		}
	}

	if (isexp) {
		setError(SigHandle, LICENSE_EXPIRED);
		isSignAllowed = FALSE;
		isVerifyAllowed = FALSE; // Maintenance has expired so don't allow either sign or verify
		num_of_lic = 0;
		isLicenseFloating = FALSE;
		return;
	}

#ifdef WIN32
	if (windowsClient == 0)
	{
		setError(SigHandle, INVALID_SECUREXML_LIC);
		isSignAllowed = FALSE;
		isVerifyAllowed = FALSE;
		isLicenseFloating = FALSE;
		num_of_lic = 0;
		DebugLog("WindowsClient is not allowed");
		return;
	}
#endif

	//DebugBreak();
	LPSYSTEMTIME floatLicTimeStamp = vbNowTimeToSystem((BYTE *)(char *)timeStr);
	DebugLog("Time in floating license data = ");
	DebugLog((const char *)timeStr);
	CTime licTime(*floatLicTimeStamp, -1);

	floatingLicenseTime = licTime;
	isLicenseFloating = TRUE;
	zFree(timeStr);
	zFree(floatLicTimeStamp);
	ExitLog;
}

BOOL CLicense::floatingLicenseStatus()
{
	SYSTEMTIME t;
	int allowedTimeOut=licenseTimeout;
//DebugBreak();
	if (isLicenseFloating == TRUE)
	{
#ifdef LOGGING
		unsigned char buffer[BUFSIZ];
#endif
#ifdef WIN32
		GetSystemTime(&t);
#else
		GetSystemTimeLinux(&t);
#endif
		CTime curTime(t, -1);
		CTimeSpan timeDiff = curTime - floatingLicenseTime;
#ifdef LOGGING
		sprintf((char *)buffer, "Time difference = %d", timeDiff.GetTotalMinutes());
		DebugLog((const char *)buffer);
#endif
		//if (::dwMinorVersion == 0)
		//	allowedTimeOut += 60;

		if (timeDiff.GetTotalMinutes() >= allowedTimeOut)
		{
			isLicenseFloating = FALSE;
			return FALSE;
		}
		else
			return TRUE;
	}
	else
		return FALSE;
}

BOOL CLicense::verifyTemplateSignature(xmlChar *templateSource, unsigned int sizeM, PGLOBAL_SIG SigHandle)
{
	ULONG crcValue=0xff01ff01;
	xmlXPathContextPtr xpathPtr=NULL;
	xmlXPathObjectPtr xpathResultPtr=NULL;

	int ret_val = axVerify((const xmlChar *)templateSource, sizeM, NULL, FALSE, -1, 1, SigHandle);

	if (!ret_val) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return FALSE;
	}

	// We also need to verify that the license is signed with our certificate

	// Sizes of the strings 1024 + 1024 + 460

	sigArr = axGetSignature(&signum, SigHandle);

	if (signum != 1) {
		// There can't be more than one signature in the license file.
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return FALSE;
	}

	string cert_in_lic;
	
	if (sigArr[0]->signerCert && sigArr[0]->signerCert->certificate)
		cert_in_lic = (char *)(sigArr[0]->signerCert->certificate);
	else {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return FALSE;
	}

	// This is the certificate that should be used to create XML Licenses for
	// Infomosaic Corporation. This is being incorporated into the birary
	// executable to check against the license used.

	const string Cert1 = "MIIHVDCCBjygAwIBAgIKJbmN0QAAAAABVDANBgkqhkiG9w0BAQUFADCBvzEiMCAGCSqGSIb3DQEJARYTaW5mb0BpbmZvbW9zYWljLmNvbTELMAkGA1UEBhMCVVMxCzAJBgNVBAgTAkNBMREwDwYDVQQHEwhTYW4gSm9zZTEfMB0GA1UEChMWSW5mb21vc2FpYyBDb3Jwb3JhdGlvbjEqMCgGA1UECxMhWE1MIERpZ2l0YWwgU2lnbmF0dXJlIERldmVsb3BtZW50MR8wHQYDVQQDExZJbmZvbW9zYWljIENvcnBvcmF0aW9uMB4XDTAyMDUyMzIzMjYxN1oXDTAzMDUyMzIzMzYxN1owgcIxIzAhBgkqhkiG9w0BCQEWFHNhbGVzQGluZm9tb3NhaWMuY29tMQswCQYDVQQGEwJVUzELMAkGA1UECBMCQ0ExETAPBgNVBAcTCFNhbiBKb3NlMR8wHQYDVQQKExZJbmZvbW9zYWljIENvcnBvcmF0aW9uMSowKAYDVQQLEyFYTUwgRGlnaXRhbCBTaWduYXR1cmUgRGV2ZWxvcG1lbnQxITAfBgNVBAMTGFNlY3VyZVhNTCBMaWNlbnNlIFNpZ25lcjCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAvpEsRpF1jACKaOFENwvBnk47MnBywKvwZ3asWNLr+L3ibjrsxpA+yBMRbRXoYaEK4goGyH2qdANCfBPc0SMwiAWSY/moSSRBxcqL5kmgMeJB37Lw6cKy0HU2UC9kwg5bXgdBn2JeM4sN+/n4No7iteft75zuqGI8Z0BqNOQ2m+cCAwEAAaOCA88wggPLMA4GA1UdDwEB/wQEAwIE8DATBgNVHSUEDDAKBggrBgEFBQcDAjAdBgNVHQ4EFgQUBn2JDstuotvk/TRfp7CvueNy/oowgfsGA1UdIwSB8zCB8IAUyDoe8/LPn+bACFA7aurljP5Nte6hgcWkgcIwgb8xIjAgBgkqhkiG9w0BCQEWE2luZm9A";
// Insert some junk data so that search for X509 cert match in the dll fails
	const int	 junk1[5] = {0xff01ff01, 0x0112abcd, 0x45fa23cd, 0x010afc01, 0x4578fbd1};
	const string Cert3 = "cnRFbnJvbGwvaW5mb21vc2FpYy1zcnZyLmluZm9tb3NhaWMubmV0X0luZm9tb3NhaWMlMjBDb3Jwb3JhdGlvbi5jcnQwDQYJKoZIhvcNAQEFBQADggEBAKcMX8EMUUnaLgv+d31IpemMMlDDmvUlPLu6T/sFsh3j7eQrjUhsVKTZ303Q+2dh0Qv7REfPLCb1T1Uxbj9bCaEh2UVZSwDdDXETO5QztkLyQZXWPfaUMbHQU/sXMZ7PZBfVo6pMRSTKKY7Lc7wWuDI4HsKDt1Ny2LTyZZdei3LNwLA3WhxuYDzrrTYL0IDOU4HxYhSsQqRUPWhZzBL0QKH/KBspukXK8X5ZdSNJKHDcdyqftaln5FSrh/uth+9fdJIRiJhXKSvnotetBsTRRz4DAR6yLyLou8LTYhfFKHRi7ZOAKmbpkQhtdqXXMkzSoUqvnCIJ5w9WkQGP/9WBKT4=";	
// Insert some junk data so that search for X509 cert match in the dll fails
	const int	 junk2[5] = { 0x0112abcd, 0xff01ff01, 0x45fa23cd, 0x4578fbd1, 0x010afc01};
	const string Cert2 = "aW5mb21vc2FpYy5jb20xCzAJBgNVBAYTAlVTMQswCQYDVQQIEwJDQTERMA8GA1UEBxMIU2FuIEpvc2UxHzAdBgNVBAoTFkluZm9tb3NhaWMgQ29ycG9yYXRpb24xKjAoBgNVBAsTIVhNTCBEaWdpdGFsIFNpZ25hdHVyZSBEZXZlbG9wbWVudDEfMB0GA1UEAxMWSW5mb21vc2FpYyBDb3Jwb3JhdGlvboIQN2ikHVFArblPpz2OZYaSNjCCATgGA1UdHwSCAS8wggErMIHToIHQoIHNhoHKbGRhcDovLy9DTj1JbmZvbW9zYWljJTIwQ29ycG9yYXRpb24sQ049aW5mb21vc2FpYy1zcnZyLENOPUNEUCxDTj1QdWJsaWMlMjBLZXklMjBTZXJ2aWNlcyxDTj1TZXJ2aWNlcyxDTj1Db25maWd1cmF0aW9uLERDPWluZm9tb3NhaWMsREM9bmV0P2NlcnRpZmljYXRlUmV2b2NhdGlvbkxpc3Q/YmFzZT9vYmplY3RjbGFzcz1jUkxEaXN0cmlidXRpb25Qb2ludDBToFGgT4ZNaHR0cDovL2luZm9tb3NhaWMtc3J2ci5pbmZvbW9zYWljLm5ldC9DZXJ0RW5yb2xsL0luZm9tb3NhaWMlMjBDb3Jwb3JhdGlvbi5jcmwwggFJBggrBgEFBQcBAQSCATswggE3MIG6BggrBgEFBQcwAoaBrWxkYXA6Ly8vQ049SW5mb21vc2FpYyUyMENvcnBvcmF0aW9uLENOPUFJQSxDTj1QdWJsaWMlMjBLZXklMjBTZXJ2aWNlcyxDTj1TZXJ2aWNlcyxDTj1Db25maWd1cmF0aW9uLERDPWluZm9tb3NhaWMsREM9bmV0P2NBQ2VydGlmaWNhdGU/YmFzZT9vYmplY3RjbGFzcz1jZXJ0aWZpY2F0aW9uQXV0aG9yaXR5MHgGCCsGAQUFBzAChmxodHRwOi8vaW5mb21vc2FpYy1zcnZyLmluZm9tb3NhaWMubmV0L0Nl";

	string X509Cert = Cert1 + Cert2 + Cert3;

	Get_CRC_CheckSum((PVOID) X509Cert.c_str(), (ULONG) X509Cert.length(), &crcValue);
	if (crcValue != 0xE771) // Someone patched the dll with a different X509 cert
	{
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return FALSE;
	}
	if (X509Cert != cert_in_lic) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return FALSE;
	}
	return TRUE;
}

BOOL CLicense::validateXmlWithSchema(xmlChar *schemaDataStr, xmlDocPtr doc, PGLOBAL_SIG SigHandle)
{
	xmlSchemaParserCtxtPtr schemaParserCtxtPtr = xmlSchemaNewMemParserCtxt((const char *)schemaDataStr, strlen((const char *)schemaDataStr));
	xmlSchemaPtr		   schemaPtr		   = xmlSchemaParse(schemaParserCtxtPtr);
	xmlSchemaValidCtxtPtr  schemaValidCtxtPtr = xmlSchemaNewValidCtxt (schemaPtr);
	int validationResult = xmlSchemaValidateDoc(schemaValidCtxtPtr, doc);
	xmlSchemaFreeValidCtxt(schemaValidCtxtPtr);
	xmlSchemaFree(schemaPtr);
	xmlSchemaFreeParserCtxt(schemaParserCtxtPtr);

//#endif
	// We verified the values in the license file.
	if (validationResult == 0)
		return TRUE;
	else
		return FALSE;
}


BOOL CLicense::verifyFormSchema(xmlChar *templateSource, xmlDocPtr doc, PGLOBAL_SIG SigHandle)
{
	xmlXPathContextPtr xpathPtr=NULL;
	xmlXPathObjectPtr xpathResultPtr=NULL;

// Now lets verify that the form being signed conforms to the schema in the licensed form template
// In order to do this, we must first remove all SecureSign addded XML elements and signatures
// from the form document.
	char *ptemp = (char *)zMalloc(4096);

	sprintf (ptemp,"(//. | //@* | //namespace::*)[self::idsig:Signature | self::SignedObject | self::documentID]");

	xpathPtr = xmlXPathNewContext(doc);

	// register additional namespace for the signature
	if (xmlXPathRegisterNs(xpathPtr,(const unsigned char *)NS_PREFIX,(const unsigned char *)SIGNATURE_URI)!=0)
	{
		setError(SigHandle, XPATH_ERROR);
		zFree(ptemp);
		return FALSE;
	}


	// apply XPath
	xpathResultPtr = xmlXPathEvalExpression((const unsigned char *)ptemp, xpathPtr);
	if (xpathResultPtr == NULL) 
	{
		// not found
		setError(SigHandle, SIG_NOT_FOUND);
		zFree(ptemp);
		xmlXPathFreeContext(xpathPtr);
		return FALSE;
	}

	if ((xpathResultPtr->nodesetval!=NULL) && (xpathResultPtr->nodesetval->nodeTab!=NULL)) 
	{
		// we found something, try to parse it
		// start traversing the document, looking for Signature's children elements
		for (int i = 0; i < xpathResultPtr->nodesetval->nodeNr; i++)
		{
			xmlNodePtr secureSignNode = xpathResultPtr->nodesetval->nodeTab[i];
			xmlUnlinkNode(secureSignNode);
			xmlFreeNode(secureSignNode);
		}
	}
    xmlXPathFreeObject(xpathResultPtr);
	xmlXPathFreeContext(xpathPtr);

	// Now doc is ready to be processed against the SchemaData present in the licensed form template
//DebugBreak();

//#if _DEBUG_
//	xmlChar *mem=NULL;
//	int iSize=0;
//	FILE *hOutFile;
//	xmlDocDumpMemory(doc,&mem,&iSize);
//	// open file in write mode 
//	hOutFile = fopen("C:\\temp\\ObjectsRemoved.xml","wb");
//	fwrite(mem, 1, iSize, hOutFile);
//	fclose(hOutFile);
//	xmlFree(mem);
//#endif
// Now lets verify that the form being signed conforms to the schema in the licensed form template
// In order to do this, we must first remove all SecureSign addded XML elements and signatures
// from the form document.

	xmlDocPtr templateXMLDoc = xmlParseMemory((const char *)templateSource, strlen((const char *)templateSource));
//#if _DEBUG_
//	// open file in write mode 
//	hOutFile = fopen("C:\\temp\\TemplateSource.xml","wb");
//	fwrite(templateSource, 1, strlen((const char *)templateSource), hOutFile);
//	fclose(hOutFile);
//#endif

	xmlChar *schemaData=NULL;
	xmlNodePtr schemaDataNode=NULL;

	if (!templateXMLDoc) 
	{
		setError(SigHandle, XML_PARSER_ERROR);
		return FALSE;
	}
	ptemp = (char *)zMalloc(4096);
	sprintf (ptemp,"(//. | //@* | //namespace::*)[self::SchemaData]");
	xpathPtr = xmlXPathNewContext(templateXMLDoc);

	// apply XPath
	xpathResultPtr = xmlXPathEvalExpression((const unsigned char *)ptemp, xpathPtr);
	if (xpathResultPtr == NULL) 
	{
		// not found
		setError(SigHandle, XPATH_ERROR);
		zFree(ptemp);
		xmlXPathFreeContext(xpathPtr);
		xmlFreeDoc(templateXMLDoc);
		return FALSE;
	}

	if ((xpathResultPtr->nodesetval!=NULL) && (xpathResultPtr->nodesetval->nodeTab!=NULL)) 
	{
		// we found something, must be the schema data node
		schemaDataNode = xpathResultPtr->nodesetval->nodeTab[0];
		schemaDataNode = schemaDataNode->children;
		schemaData = xmlNodeGetContent(schemaDataNode);
	}
	else
	{
        xmlXPathFreeObject(xpathResultPtr);
		xmlXPathFreeContext(xpathPtr);
		zFree(ptemp);
		xmlFreeDoc(templateXMLDoc);
		return FALSE;
	}

    xmlXPathFreeObject(xpathResultPtr);
	xmlXPathFreeContext(xpathPtr);
	zFree(ptemp);

	BOOL result = validateXmlWithSchema(schemaData, doc, SigHandle);
	xmlFree(schemaData);
	return result;
}

BOOL CLicense::getFormSignAllowed(unsigned char *inputXML, unsigned int size, PGLOBAL_SIG SigHandle)
{
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL, parent=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlXPathContextPtr xpathPtr=NULL;
	xmlXPathObjectPtr xpathResultPtr=NULL;
	char *ptemp=NULL;
	BOOL templateFound=FALSE;
	xmlChar *base64EncodedTemplateSource;
	xmlChar *base64DecodedTemplateSource;
	unsigned int sizeM;
	BOOL result = FALSE;

	// original document
	doc = xmlParseMemory((const char *)inputXML,size);
	if (!doc) 
	{
		setError(SigHandle, XML_PARSER_ERROR);
		return FALSE;
	}

	ptemp = (char *)zMalloc(4096);

	sprintf (ptemp,"(//. | //@* | //namespace::*)[ancestor-or-self::ifmc:SignedObject[@Id='%s']]","TemplateSource");

	xpathPtr = xmlXPathNewContext(doc);

	if (xpathPtr == NULL)
	{
		setError(SigHandle, XPATH_ERROR);
		zFree(ptemp);
		xmlFreeDoc(doc);
		return FALSE;
	}

	// register additional namespace for the signature
	if (xmlXPathRegisterNs(xpathPtr,(const unsigned char *)"ifmc",(const unsigned char *)"http://www.infomosaic.net")!=0)
	{
		setError(SigHandle, XPATH_ERROR);
		xmlFreeDoc(doc);
		zFree(ptemp);
		return S_FALSE;
	}

	// apply XPath
	xpathResultPtr = xmlXPathEvalExpression((const unsigned char *)ptemp, xpathPtr);
	if (xpathResultPtr == NULL) 
	{
		// not found
		setError(SigHandle, INVALID_XML);
		zFree(ptemp);
		xmlXPathFreeContext(xpathPtr);
		xmlFreeDoc(doc);
		return FALSE;
	}

	if ((xpathResultPtr->nodesetval!=NULL) && (xpathResultPtr->nodesetval->nodeTab!=NULL)) 
	{
		// we found something, try to parse it
		sigNode = xpathResultPtr->nodesetval->nodeTab[0];
		base64EncodedTemplateSource = xmlNodeGetContent(sigNode);

		if (base64EncodedTemplateSource == NULL)
		{
			setError(SigHandle, INVALID_XML);
			zFree(ptemp);
			xmlXPathFreeObject(xpathResultPtr);
			xmlXPathFreeContext(xpathPtr);
			xmlFreeDoc(doc);
			return FALSE;
		}

		sizeM = strlen((const char *)base64EncodedTemplateSource);
		sizeM = base64decodeSize(sizeM);
		base64DecodedTemplateSource = (unsigned char *)zMalloc(sizeM+1);
		if ((sizeM = base64decode(base64EncodedTemplateSource,base64DecodedTemplateSource,sizeM+1))==-1)
		{
			xmlFree(base64EncodedTemplateSource);
			zFree(base64DecodedTemplateSource);
			setError(SigHandle, BASE64_ERROR);
			zFree(ptemp);
			xmlXPathFreeObject(xpathResultPtr);
			xmlXPathFreeContext(xpathPtr);
			xmlFreeDoc(doc);
			return FALSE;
		}
		xmlFree(base64EncodedTemplateSource);
		result = verifyTemplateSignature(base64DecodedTemplateSource, sizeM, SigHandle);
		//if (result != 0)
		//{
		//	result = verifyFormSchema(base64DecodedTemplateSource, doc, SigHandle);
		//}
		zFree(base64DecodedTemplateSource);
	}

	zFree(ptemp);
	xmlXPathFreeObject(xpathResultPtr);
	xmlXPathFreeContext(xpathPtr);
	xmlFreeDoc(doc);

	return result;
}
BOOL CLicense::verifyTemplateSchema(xmlChar *templateSource,PGLOBAL_SIG SigHandle)
{
	char *ptemp;
	xmlDocPtr templateXMLDoc = xmlParseMemory((const char *)templateSource, strlen((const char *)templateSource));
	xmlChar *schemaData=NULL;
	xmlNodePtr schemaDataNode=NULL;
	xmlNodePtr xmlDataNode=NULL;
	xmlChar *xmlData;
	xmlXPathContextPtr xpathPtr=NULL;
	xmlXPathObjectPtr xpathResultPtr=NULL;
	BOOL result=FALSE;

	if (!templateXMLDoc) 
	{
		setError(SigHandle, XML_PARSER_ERROR);
		return FALSE;
	}
	ptemp = (char *)zMalloc(4096);
	sprintf (ptemp,"(//. | //@* | //namespace::*)[self::SchemaData | self::XmlData]");
	xpathPtr = xmlXPathNewContext(templateXMLDoc);

	// apply XPath
	xpathResultPtr = xmlXPathEvalExpression((const unsigned char *)ptemp, xpathPtr);
	if (xpathResultPtr == NULL) 
	{
		// not found
		setError(SigHandle, XPATH_ERROR);
		zFree(ptemp);
		xmlXPathFreeContext(xpathPtr);
		xmlFreeDoc(templateXMLDoc);
		return FALSE;
	}

	if ((xpathResultPtr->nodesetval!=NULL) && (xpathResultPtr->nodesetval->nodeTab!=NULL)) 
	{
		// we found something, must be schema data  and Xml data nodes
		if (!strcmp((const char *)xpathResultPtr->nodesetval->nodeTab[0]->name, "XmlData"))
		{
			xmlDataNode = xpathResultPtr->nodesetval->nodeTab[0]->children;
			xmlData = xmlNodeGetContent(xmlDataNode);
			schemaDataNode = xpathResultPtr->nodesetval->nodeTab[1]->children;
			schemaData = xmlNodeGetContent(schemaDataNode);
		}
		else
		{
			xmlDataNode = xpathResultPtr->nodesetval->nodeTab[1]->children;
			xmlData = xmlNodeGetContent(xmlDataNode);
			schemaDataNode = xpathResultPtr->nodesetval->nodeTab[0]->children;
			schemaData = xmlNodeGetContent(schemaDataNode);
		}
	}
	else
	{
		xmlXPathFreeObject(xpathResultPtr);
		xmlXPathFreeContext(xpathPtr);
		zFree(ptemp);
		xmlFreeDoc(templateXMLDoc);
		return FALSE;
	}

	xmlXPathFreeObject(xpathResultPtr);
	xmlXPathFreeContext(xpathPtr);
	zFree(ptemp);

	xmlDocPtr doc;
	size_t instanceXmlStrSize = strlen((const char *)xmlData);
	doc = xmlParseMemory((const char *)xmlData, instanceXmlStrSize);
	xmlFree(xmlData);

	result = validateXmlWithSchema(schemaData, doc, SigHandle);
	xmlFree(schemaData);
	xmlFreeDoc(doc);
	xmlFreeDoc(templateXMLDoc);
	return result;
}
