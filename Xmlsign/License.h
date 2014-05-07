// License.h: interface for the License class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __LICENSE_H
#define __LICENSE_H

#include <windows.h>
#include <string>

#include <securexml/base64.h>

#ifdef WIN32
#include <atltime.h>
#elif SOLARIS
#include <securexml/atltimeSolaris.h>
#elif defined LINUX || defined __powerpc__
#include <securexml/atltimeLinux.h>
#endif

using namespace std;

#if __cplusplus
extern "C" {
#endif

#include <libxml/parser.h>
#include <libxml/xmlschemas.h>
#include <securexml/ax.h>
#include <securexml/xs.h>
#include <securexml/errors.h>
#include <securexml/utils.h>

#if __cplusplus
}
#endif


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//static DWORD dwMinorVersion;

class CLicense  
{

public:
	CLicense();
	virtual ~CLicense();

	void setLicenseFile(char *licFile) {
		licenseFile = licFile;
	}
	char *getLicenseFile() const {
		return licenseFile;
	}
	BOOL getSignAllowed() {
		if (isSignAllowed)
			return isSignAllowed;
		else
			return floatingLicenseStatus();
	}
	BOOL getVerifyAllowed() {
		if (isVerifyAllowed)
			return isVerifyAllowed;
		else
			return floatingLicenseStatus();
	}
	BOOL getEncryptAllowed() {
		if (isEncryptAllowed)
			return isEncryptAllowed;
		else
			return floatingLicenseStatus();
	}
	BOOL getDecryptAllowed(){
		if (isDecryptAllowed)
			return isDecryptAllowed;
		else
			return floatingLicenseStatus();
	}
	BOOL getSecureSignAllowed(){
		if (isSecureSignAllowed)
			return isSecureSignAllowed;
		else
			return floatingLicenseStatus();
	}

	BOOL getSecureSignProfessionalAllowed(){
		if (isSecureSignProfessionalAllowed)
			return isSecureSignProfessionalAllowed;
		else
			return floatingLicenseStatus();
	}

	BOOL getSecureSignEnterpriseAllowed(){
		if (isSecureSignEnterpriseAllowed)
			return isSecureSignEnterpriseAllowed;
		else
			return floatingLicenseStatus();
	}

	BOOL getSecureSignServerAllowed() const {
		return isSecureSignServerAllowed;
	}
	BOOL checkLicense(){
		if (isLicenseValid)
			return isLicenseValid;
		else
			return floatingLicenseStatus();
	}
	BOOL isLicenseDemo() const {
		return isDemoLic;
	}
	BOOL isLicenseDevelopment() const {
		return isDevelopmentLic;
	}

	int getLicensedUserCount() const {
		return num_of_lic;
	}

	int getMaintExpiryYear() const {
		return maintExpYear;
	}
	int getMaintExpiryMonth() const {
		return maintExpMon;
	}
	int getMaintExpiryDay() const {
		return maintExpDay;
	}

	BOOL isClientLinux() const {
		return linuxClient;
	}

	BOOL isClientWindows() const {
		return windowsClient;
	}

	BOOL isClientSolaris() const {
		return solarisClient;
	}

	BOOL isClientMac() const {
		return macClient;
	}

	BOOL getLicenseDetails(PGLOBAL_SIG);		// Sets the values from license file.
	BOOL verifyLicense(PGLOBAL_SIG);
	static void Get_CRC_CheckSum(PVOID pBuffer, ULONG ulSize, PULONG pulSeed);
	static long getHostOsType(void);

	static const xmlChar *LICENSE;
	static const xmlChar *VERSION;
	static const xmlChar *EXP_DATE;
	static const xmlChar *MAINT_EXP_DATE;
	static const xmlChar *ISSUE_DATE;
	static const xmlChar *YEAR;
	static const xmlChar *MON;
	static const xmlChar *DAY;
	static const xmlChar *OPERATIONS;
	static const xmlChar *VERIFY;
	static const xmlChar *CREATE;
	static const xmlChar *ENCRYPT;
	static const xmlChar *DECRYPT;
	static const xmlChar *SECURESIGN;
	static const xmlChar *SECURESIGNPROFESSIONAL;
	static const xmlChar *SECURESIGNENTERPRISE;
	static const xmlChar *SECURESIGNSERVER;
	static const xmlChar *TYPE;
	static const xmlChar *SERVER;
	static const xmlChar *CLIENT;
	static const xmlChar *DEMO;
	static const xmlChar *DEVELOPMENT;
	static const xmlChar *LICENSE_KEY;
	static const xmlChar *NUM_LICENSE;
	static const xmlChar *WINDOWS_CLIENT;
	static const xmlChar *LINUX_CLIENT;
	static const xmlChar *MAC_CLIENT;
	static const xmlChar *SOLARIS_CLIENT;
	static const xmlChar *SIGNATURE;

	static const xmlChar *LICENSEE;
	static const xmlChar *LICENSER;
	static const xmlChar *COMPANY;
	static const xmlChar *USER;
	static const xmlChar *HOSTNAME;
	CTime releaseTime;
	int releaseYear, releaseMonth, releaseDay;

private:

	char *licenseFile;		// The name of the file with LicenseKey

	// The following values are embedded into the license file
	// After parsing a signed license file, we can get these value

	int expYear, expMon, expDay;
	int issYear, issMon, issDay;
	int maintExpYear, maintExpMon, maintExpDay;
	BOOL isVerifyAllowed;		// Is Verification by the application allowed.
	BOOL isSignAllowed;			// Is Signing also allowed.
	BOOL isEncryptAllowed;		// Is encryption also allowed.
	BOOL isDecryptAllowed;		// Is decryption also allowed.
	BOOL isSecureSignAllowed;	// Does the user have a valid SecureSign license
	BOOL isSecureSignProfessionalAllowed;	// Does the user have a valid SecureSign Professional license
	BOOL isSecureSignEnterpriseAllowed;	// Does the user have a valid SecureSign Enterprise license
	BOOL isSecureSignServerAllowed;	// Does the user have a valid SecureSign license
	BOOL isServerLic;			// Is there a server license.
	BOOL isClientLic;			// Is there a client license
	BOOL isDemoLic;				// Is this a demo license.
	BOOL isDevelopmentLic;		// Is this a development license
	BSTR version;				// The version number of the license file
	BSTR licenseKey;			// The LicenseKey can be stored here
	BOOL isLicenseValid;		// Indicates whether the license is valid or not.
	BOOL isLicenseFloating;
	int num_of_lic;
	BOOL windowsClient;
	BOOL linuxClient;
	BOOL macClient;
	BOOL solarisClient;

	PSIG_STATUS *sigArr;
	int signum;

	BSTR licenser, company, user, hostname;

	CTime floatingLicenseTime;
	const static int licenseTimeout = 30;

public:
	BOOL getFormSignAllowed(unsigned char *inputXML, unsigned int size, PGLOBAL_SIG SigHandle);
	BOOL verifyFormSchema(xmlChar *templateSource, xmlDocPtr doc, PGLOBAL_SIG SigHandle);
	BOOL validateXmlWithSchema(xmlChar *schemaDataStr, xmlDocPtr doc, PGLOBAL_SIG SigHandle);
	BOOL verifyTemplateSignature(xmlChar *templateSource, unsigned int sizeM, PGLOBAL_SIG SigHandle);
	BOOL verifyTemplateSchema(xmlChar *templateSource,PGLOBAL_SIG SigHandle);
	void verifyFloatingLicense(unsigned char *inputXMLStr, unsigned long size, PGLOBAL_SIG SigHandle);
	BOOL floatingLicenseStatus();
};

#endif // #define __LICENSE_H
