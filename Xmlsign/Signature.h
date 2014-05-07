/*****************************************************************************************
 * Copyright: (c) 2000-2002 Infomosaic Corporation.
 * All rights reserved.
 * It is violation of international law to use this code without proper written authorization
 * and license agreement from Infomosaic Corporation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL INFOMOSAIC CORPORATION  OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * Author: 
 * Date:   
 * Change history:
 *
 * Date		|	Modified By		|	Brief description of the modification
 *
 *
 *****************************************************************************************
 */
// Signature.h : Declaration of the CSignature

#ifndef __SIGNATURE_H_
#define __SIGNATURE_H_

#ifdef WIN32
#include "resource.h"       // main symbols
#include <objsafe.h>
#undef UNIX
#endif

#include <docobj.h>			// IOleCommandTarget interface declaration
#include <ocidl.h>			// IObjectWithSite interface declaration
#ifdef WIN32
#include <shobjidl.h>		// IShellBrowser interface declaration
#endif

#if __cplusplus
extern "C" {
#endif

#include <securexml/ax.h>
#include <securexml/errors.h>
#include <securexml/cr.h>

#if __cplusplus
}
#endif


#include "config.h"
#include "CAMClient.h"
#include "CertVerify.h"
#include "BufferVariant.h"
#include "License.h"

#ifdef WIN32

#include "ShowSelectCert.h"
#import "..\NetscapeCert\_NetscapeCert.tlb"
#import "..\lib\ocspAx.dll"
using namespace NetscapeCert;
using namespace ocspAX;

#elif UNIX

#ifdef USE_XPCOM
#include <nsString.h>
#endif

#ifdef SOLARIS
#include <securexml/atlcomcliSolaris.h>
#else
#include <securexml/atlcomcliLinux.h>
#endif

#ifdef USE_XPCOM
#include <nsCOMPtr.h>
#include <nsIServiceManager.h>
#include <nsIComponentManager.h>
#include <nsIGenericFactory.h>

#ifdef USE_OCSP
#include "OcspClientL.h"
#endif
#endif
#endif

#include <string>
#include <list>

#define NOT_INITIALIZED		-1
#define USE_PFX_CERT		-2
#define USE_BASE64_CERT		-3
#define ACTIVE_CERT_INFO	-3

#define WITHOUT_COMMENTS		0
#define WITH_COMMENTS			1
#define EXC_WITHOUT_COMMENTS	2
#define EXC_WITH_COMMENTS		3

#define MAX_PROP_COUNT		64
#define SIGN_ALLOWED		0x01
#define VERIFY_ALLOWED		0x02
#define ENCRYPT_ALLOWED		0x04
#define DECRYPT_ALLOWED		0x08
#define SECURESIGN_ALLOWED	0x10
#define SECURESIGN_PROF_ALLOWED	0x20
#define SECURESIGN_ENTR_ALLOWED	0x40
#define SECURESIGN_SERVER_ALLOWED 0x80

#define MAX_TS_PROP_ATTR	1024

#define GUNZIP_BLOCK_SIZE	16*1024
#define CERT_SERIAL_PLAIN_HEX	1

#define NO_PHYSICAL_SIG			0
#define FILE_PHYSICAL_SIG		1
#define CAPTURE_PHYSICAL_SIG	2
#define BUF_PHYSICAL_SIG		3

// Various possible physical signature image sources
#define IMAGE_FROM_FILE		"Stored Disk Image"
#define IMAGE_FROM_MOUSE	"Live Mouse Signature Image"
#define IMAGE_FROM_TABLET	"Live Signature Pad Image"

// Various element Id prefixes
#define SIG_IMAGE_OBJECT_ID_PREFIX	"SignatureImage_"
#define WINDOW_IMAGE_OBJECT_ID_PREFIX	"WindowImage_"

//Various File Names
#define SECUREXML_CONFIG_FILENAME	"SecureXML.config"
#define SECUREXML_LICENSE_FILENAME	"SecureXMLLicense.xml"

// Language specific resource only dll file names
#define ENGLISH_RESOURCE_DLL	"EnglishDiag.dll"
#define FRENCH_RESOURCE_DLL		"FrenchDiag.dll"
#define HUNGARIAN_RESOURCE_DLL	"HungarianDiag.dll"
#define JAPANESE_RESOURCE_DLL	"JapaneseDiag.dll"
#define SPANISH_RESOURCE_DLL	"SpanishDiag.dll"
#define GERMAN_RESOURCE_DLL		"GermanDiag.dll"
#define PORTUGUESE_RESOURCE_DLL "PortugueseDiag.dll"

//Netscape Certificate Store support
#define NETSCAPESTORE		"Netscape"

//Ocsp certificate validation related defines
#define FORMAT_BASE64		3

#define CERT_GOOD			0x01
#define CERT_UNKNOWN		0x02
#define CERT_REVOKED		0x04
#define RESPONSE_VERIFIED	0x10
#define INCLUDE_TEXT_RESPONSE	0x01
#define INCLUDE_BIN_RESPONSE	0x02

/* defines for various supported time formats */

#define TIME_RFC			0
#define TIME_VB_NOW			1
#define TIME_JS_UTC			2

#define TIME_NO_SRVR				0
#define TIME_RFC_867_SRVR			1
#define TIME_SNTP_RFC_1305_SRVR		2
#define TIME_RFC_3161_SRVR			3

#define TIME_STAMP_PREFIX			"Timestamp_"
#define TIME_STAMP_FORMAT			L"TimeStampFormat"
#define TIME_STAMP_PROTOCOL			L"TimeStampProtocol"
#define TIME_RFC_867_PROTOCOL			L"DAYTIME-RFC-867"
#define TIME_SNTP_RFC_1305_PROTOCOL		L"SNTP-RFC-1305"
#define TIME_RFC_3161_PROTOCOL			L"RFC-3161"
//#define TIME_SNTP_RFC_1305_PREFIX	"SntpTimestamp_"
//#define TIME_RFC_3161_PREFIX		"Rfc3161Timestamp_"

/* defines for Email Server Type*/
#define EMAIL_SRVR_SMTP			1
#define EMAIL_SRVR_EXCH			2
#define DEFAULT_CONN_STR		L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\\Program Files\\Infomosaic\\SecureXML\\SecureXML.mdb"
/*
 * This protocol is widely used by small computers running MS-DOS and similar operating systems. 
 * The server listens on port 13, and responds to requests in either tcp/ip or udp/ip formats. The 
 * standard does not specify an exact format for the Daytime Protocol, but requires that the time 
 * is sent using standard ASCII characters. NIST chose a time code format similar to the one used 
 * by its dial-up Automated Computer Time Service (ACTS), as shown below:
 *
 * JJJJJ YR-MO-DA HH:MM:SS TT L H msADV UTC(NIST) OTM
 * 
 * where:
 * JJJJJ is the Modified Julian Date (MJD). The MJD is the last five digits of the Julian Date, 
 * which is simply a count of the number of days since January 1, 4713 B.C. To get the Julian Date, 
 * add 2.4 million to the MJD.
 * 
 * YR-MO-DA is the date. It shows the last two digits of the year, the month, and the current day of month.
 * 
 * HH:MM:SS is the time in hours, minutes, and seconds. The time is always sent as Coordinated Universal Time (UTC). 
 * An offset needs to be applied to UTC to obtain local time. For example, Mountain Time in the U. S. is 7 hours 
 * behind UTC during Standard Time, and 6 hours behind UTC during Daylight Saving Time.
 * 
 * TT is a two digit code (00 to 99) that indicates whether the United States is on Standard Time (ST) or 
 * Daylight Saving Time (DST). It also indicates when ST or DST is approaching. This code is set to 00 when 
 * ST is in effect, or to 50 when DST is in effect. During the month in which the time change actually occurs, 
 * this number will decrement every day until the change occurs. For example, during the month of October, 
 * the U.S. changes from DST to ST. On October 1, the number will change from 50 to the actual number of days 
 * until the time change. It will decrement by 1 every day until the change occurs at 2 a.m. local time when 
 * the value is 1. Likewise, the spring change is at 2 a.m. local time when the value reaches 51.
 * 
 * L is a one-digit code that indicates whether a leap second will be added or subtracted at midnight on the 
 * last day of the current month. If the code is 0, no leap second will occur this month. If the code is 1, 
 * a positive leap second will be added at the end of the month. This means that the last minute of the month 
 * will contain 61 seconds instead of 60. If the code is 2, a second will be deleted on the last day of the 
 * month. Leap seconds occur at a rate of about one per year. They are used to correct for irregularity in 
 * the earth's rotation. The correction is made just before midnight UTC (not local time).
 * 
 * H is a health digit that indicates the health of the server. If H=0, the server is healthly. If H=1, then 
 * the server is operating properly but its time may be in error by up to 5 seconds. This state should change 
 * to fully healthy within 10 minutes. If H=2, then the server is operating properly but its time is known 
 * to be wrong by more than 5 seconds. If H=4, then a hardware or software failure has occurred and the 
 * amount of the time error is unknown.
 *
 * msADV displays the number of milliseconds that NIST advances the time code to partially compensate for 
 * network delays. The advance is currently set to 50.0 milliseconds.
 *
 * The label UTC(NIST) is contained in every time code. It indicates that you are receiving Coordinated 
 * Universal Time (UTC) from the National Institute of Standards and Technology (NIST).
 *
 * OTM (on-time marker) is an asterisk (*). The time values sent by the time code refer to the arrival time 
 * of the OTM. In other words, if the time code says it is 12:45:45, this means it is 12:45:45 when the OTM arrives.
 *
 * Example:
 *
 * 52478 02-07-23 22:37:41 50 0 0 558.1 UTC(NIST) 
*/


struct BufferLinkedList
{
	unsigned char *bufferPtr;
	unsigned long bufferSize;
	struct BufferLinkedList *next;
};
struct TempFilePathInfo {
	      char	fileName[MAX_PATH * 2];
      };
typedef TempFilePathInfo TEMP_FILE_INFO;

typedef list <TEMP_FILE_INFO *> TempFileList;
int UTF16LEToUTF8(unsigned char* out, int *outlen, const unsigned char* inb, int *inlenb);
int UTF8ToUTF16LE(unsigned char* outb, int *outlen, const unsigned char* in, int *inlen);
unsigned char * HeapW2A(BSTR bstrStr);

#ifdef UNIX
#define ATL_NO_VTABLE
#undef STDMETHOD
#define STDMETHOD(method) NS_METHOD method
#undef STDMETHODIMP
#define STDMETHODIMP NS_METHOD
#endif

#ifdef JNIBINDING
#undef NS_METHOD
#define NS_METHOD long
#undef STDMETHOD
#define STDMETHOD(method) NS_METHOD method
#undef STDMETHODIMP
#define STDMETHODIMP NS_METHOD
#endif

/////////////////////////////////////////////////////////////////////////////
// CSignature

class ATL_NO_VTABLE CSignature
#ifdef WIN32
#ifndef JNIBINDING
:	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSignature, &CLSID_Signature>,
	public IDispatchImpl<ISignature, &IID_ISignature, &LIBID_XMLSIGNLib>,
	public IOleCommandTarget,
	public IObjectWithSite
#endif
#endif
{
public:
	CSignature();
	~CSignature();

#ifdef WIN32
#ifndef JNIBINDING
// See UpdateRegistry static function below
// DECLARE_REGISTRY_RESOURCEID(IDR_SIGNATURE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSignature)
	COM_INTERFACE_ENTRY(ISignature)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IOleCommandTarget)
	COM_INTERFACE_ENTRY(IObjectWithSite)
END_COM_MAP()
#endif
#endif

// ISignature
public:
	STDMETHOD(put_CertificateTrustExplicit)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_CertificatePolicyExplicit)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_CertificatePolicyExplicit)(/*[in]*/ BOOL newVal);
	STDMETHOD(put_DoDCompliance)(/*[in]*/ BOOL newVal);
	STDMETHOD(put_CertificatePathLengthChecking)(/*[in]*/ BOOL newVal);
	STDMETHOD(put_CertificateChainValidation)(/*[in]*/ BOOL newVal);
	STDMETHOD(put_CertificatePolicyChecking)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_UserConstrainedPolicy)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_AuthorityConstrainedPolicy)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_CertificatePolicy)(/*[in]*/ VARIANT newVal);
	STDMETHOD(VerifyActiveCertificate)(BOOL *result);
	STDMETHOD(put_CRLLocation)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_ConfigFileName)(/*[in]*/ BSTR newVal);
	BSTR * GetBstrArrayFromVariant(VARIANT fileList, UINT *itemCount);
	STDMETHOD(SignFiles)(/*[in]*/ VARIANT fileList, /*[in]*/ BSTR outFileName, /*[out, retval]*/ BSTR *outFilePath);
	STDMETHOD(CoSignFile)(/*[in]*/ BSTR inputSignedXMLFile, /*[in]*/ BSTR outFileName, /*[out, retval]*/ BSTR *outFilePath);
	STDMETHOD(put_OverwriteFile)(/*[in]*/ BOOL newVal);
	STDMETHOD(CoSignXMLStr)(/*[in]*/ BSTR signedDataXMLStr, /*[out, retval]*/ BSTR *coSignedXMLStr);
	STDMETHOD(put_ExcludeSignerCertificate)(/*[in]*/ BOOL newVal);
	STDMETHOD(SignDataStr)(/*[in]*/ BSTR dataStrPtr, /*[out, retval]*/ BSTR *signedXMLStr);
	STDMETHOD(CaptureLiveSignature)(/*[out, retval]*/ BSTR *signatureFilePath);
	STDMETHOD(put_DetailedVerificationFlag)(/*[in]*/ BOOL newVal);
	STDMETHOD(ChangeOrAddProperty)(BSTR propertyName, BSTR propertyValue);
	STDMETHOD(get_HMACPassword)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_HMACPassword)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_UseHMAC)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_UseHMAC)(/*[in]*/ BOOL newVal);
	STDMETHOD(SignXMLXpathStr)(BSTR xmlStr, BSTR xpathExp, BSTR signatureId, BSTR *signedXMLStr);

	
	STDMETHOD(get_AddWindowImage)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_AddWindowImage)(/*[in]*/ BOOL newVal);
	void AddWindowImage(xmlNodePtr sigNode, xmlNodePtr signedInfoNode, char *charSigId);
	BOOL GetPhysicalSignatureFromMouse(char *filePathBuf, int bufSize, char *guidStr);
	BOOL GetPhysicalSignatureFromTablet(char *filePathBuf, int bufSize, char *guidStr);
	HRESULT	ShowFileSignature(char *filePathBuf, char *outFilePathBuf, BOOL sigCapturedOnce, RECT *windowDim, char *guidStr);
	BOOL CaptureCurrentWindowImage (char *imageFilePath, char *guidStr);

	STDMETHOD(VerifyPFXCertCRL)(/*[in]*/ BSTR pfxFileName, /*[in]*/ BSTR pfxPassword, /*[in]*/ BSTR atTime, /*[in]*/ long timeFormat, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(VerifyX509CertCRL)(/*[in]*/ BSTR certData, /*[in]*/ BSTR atTime, /*[in]*/ long timeFormat, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_SigCertStatus)(/*[in]*/ long sigIndex, /*[in]*/ BSTR atTime, /*[in]*/ long timeFormat, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_CrlChecking)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_CrlChecking)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_HostOsType)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_TimeStamping)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_TimeStamping)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_TimeStampURL)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_TimeStampURL)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_HostName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(PFXExportActiveCertificate)(/*[in]*/ BSTR password, /*[out, retval]*/ BSTR *pfxFilePath);
	STDMETHOD(SetActivePFXFileCert)(/*[in]*/ BSTR pfxFileName, /*[in]*/ BSTR pfxPassword, /*[out, retval]*/ BSTR *pfxX509Cert);
	STDMETHOD(VerifyXMLStr)(/*[in]*/ BSTR signedXML, /*[out, retval]*/ BOOL *sigStatus);
	STDMETHOD(SelectActiveCertificate)(/*[out, retval]*/ BSTR *certID);
	STDMETHOD(ViewAnyCertificate)(/*[in]*/ BSTR inputX509Data);

// IOleCommandTarget
	HRESULT STDMETHODCALLTYPE QueryStatus(const GUID *pguidCmdGroup, ULONG cCmds, OLECMD prgCmds[], OLECMDTEXT *pCmdText);
	HRESULT STDMETHODCALLTYPE Exec(const GUID *pguidCmdGroup, DWORD nCmdID, DWORD nCmdExecOpt, VARIANTARG *pvaIn, VARIANTARG *pvaOut );

// IObjectWithSite
	STDMETHODIMP SetSite(IUnknown* pUnkSite);
	STDMETHODIMP GetSite(REFIID riid, void **ppvSite);

	STDMETHOD(GetPropertyCount)(/*[in]*/ long sigIndex, /*[out, retval]*/ long *propCount);
	STDMETHOD(GetLicenseStatus)(/*[out, retval]*/ long *licStatus);
	STDMETHOD(GetVersion)(/*[out, retval]*/ BSTR *version);
	STDMETHOD(SignXMLEnveloped)(/*[in]*/ BSTR inputXML, /*[in]*/ BSTR sigId, /*[out, retval]*/ BSTR *signedXML);
	//CSignature(BSTR StoreName);
	STDMETHOD(GetStoreName)(/*[out, retval]*/ BSTR *storeName);
	STDMETHOD(SetStoreName)(/*[in]*/ BSTR storeName);
	STDMETHOD(GetSignedFileObject)(/*[in]*/ BSTR signedXML, /*[in]*/ BSTR saveDir, /*[out, retval]*/ BSTR *signedFilePath);
	STDMETHOD(SignFile)(/*[in]*/ BSTR inputFile, /*[in]*/ BSTR outputFile);
	STDMETHOD(GetSignedHTML)(/*[in]*/ BSTR signedHtmlXML, /*[out, retval]*/ BSTR *originalHTML);
	STDMETHOD(SetCSP)(/*[in]*/ BSTR CSPName);
	STDMETHOD(SecureXMLVerify)(/*[in]*/ BSTR signedXML, /*[out, retval]*/ BSTR *verificationResponse);
	STDMETHOD(SignHTML)(/*[in]*/ IDispatch *document, /*[out, retval]*/ BSTR *signedHTML);
	STDMETHOD(SaveXMLStr)(/*[in]*/ BSTR inputXMLStr, /*[in]*/ BSTR fileName, /*[out, retval]*/ BSTR *path);
	STDMETHOD(ReadAll)(/*[in]*/ BSTR fileName, /*[out, retval]*/ BSTR *fileDataStr);
	STDMETHOD(SignXMLStr)(/*[in]*/ BSTR xmlStr, /*[in]*/ BSTR signatureId, /*[out, retval]*/ BSTR *signedXMLStr);
	STDMETHOD(get_SignatureCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_FailedUri)(long index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_FailedUriFullPath)(long index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FailedUriFullPath)(long index, /*[in]*/ BSTR newVal);
	STDMETHOD(get_TotalUriCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_FailedUriCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(FileExists)(/*[in]*/ BSTR fileName, /*[out, retval]*/ BOOL *fileStatus);
	STDMETHOD(get_CertSerialNumber)(/*[in]*/ BSTR sigId, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_CertExpiry)(/*[in]*/ BSTR sigId, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_CertIssuer)(/*[in]*/ BSTR sigId, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_SignerSubject)(/*[in]*/ BSTR sigId, /*[out, retval]*/ BSTR *pVal);
//	HRESULT SetSignatureValues(int signatureType);
	STDMETHOD(get_SignedDocumentPath)(/*[in]*/long sigIndex, /*[in]*/ long uriIndex, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(SetActiveCertificate)(/*[in]*/ BSTR certID, /*[out, retval]*/ BOOL *status);
	STDMETHOD(GetCertificateInfo)(/*[in]*/ long index, /*[in]*/ long valIndex, /*[out, retval]*/ BSTR *value);
	STDMETHOD(get_CertificateCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(ViewCertificate)(/*[in]*/ BSTR certID);
	STDMETHOD(GetX509Certificate)(/*[in]*/ BSTR certID, /*[out, retval]*/ BSTR *certData);
	STDMETHOD(GetLastError)(/*[out, retval]*/ long *errorNum);
	STDMETHOD(VerifyDetached)(/*[in]*/ BSTR signatureFileName, /*[out, retval]*/ BOOL *sigStatus);
	STDMETHOD(PFXExportCertificate)(/*[in]*/ BSTR certID, /*[in]*/ BSTR password, /*[out, retval]*/ BSTR *pfxFilePath);
	void Empty();
	void FreeUriArr();
	void FetchSignatureStatus(BOOL verifyResult, BOOL extractSignedContent);
	BOOL ReadAllBin(BSTR fileName, unsigned char **binData, DWORD *dwFileSize);
	BYTE *xsDereferenceBstrURI (BSTR bstrRef, DWORD *cbRef);
	unsigned char * xsRemoveBstrPath(BSTR fileName);

	BOOL CreateSigFromTmplBlob(xmlDocPtr doc, char *sigId, unsigned char **signedXML, int *signedXMLSize);
	void AddPhysicalSignature(xmlNodePtr sigNode, xmlNodePtr signedInfoNode, char *charSigId);

#ifdef NSS
	static int SwapUnicodeBytes(SECItem *uniItem)
	{
#if !defined MAC && !defined SOLARIS
		unsigned int i;
		unsigned char a;
		if((uniItem == NULL) || (uniItem->len % 2)) {
			return -1;
		}
		for(i = 0; i < uniItem->len; i += 2) {
			a = uniItem->data[i];
			uniItem->data[i] = uniItem->data[i+1];
			uniItem->data[i+1] = a;
		}
#endif
		return 0;
	}
#endif

#ifdef WIN32
	static _ATL_REGMAP_ENTRY RegEntries[];
	// Default implementation does not pass _ATL_REGMAP_ENTRY array
	// DECLARE_REGISTRY_RESOURCEID(IDR_SIGNATURE)
	static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
	{
		return _Module.UpdateRegistryFromResource(IDR_SIGNATURE, bRegister, RegEntries);
	}


BEGIN_CATEGORY_MAP(CSignature)
	IMPLEMENTED_CATEGORY(CATID_SafeForScripting)
	IMPLEMENTED_CATEGORY(CATID_SafeForInitializing)
END_CATEGORY_MAP()
#endif

	PSIG_STATUS *sgArr;
	int err, signum;
	PURI_PATH *uriArr, *failedUriArr;
	int failedUriCount, totalUriCount;

#ifdef WIN32
	IShellBrowser *pSite;
#endif
	
	UINT RecipientCertificateCount;
	LPSTR *RecipientCertificateList;

	CComBSTR DecrytionPfxCertFile;
	BOOL DecryptUsingPfxFileCert;
	DS_DATA_BLOB DecrytionPfxPassword;

	UINT DetachedObjectCount;
	LPSTR *DetachedObjectList;
	UINT AttachedObjectCount;
	BSTR *AttachedObjectList;
	UINT SignedObjectIdCount;
	BSTR *SignedObjectIdList;
//	LPSTR *AttachedObjectList;

	UINT XpathNamespaceCount;
	LPSTR *XpathNamespaceList;

	LPSTR InclusiveNamespaceList;

	int PropertyCount;
	PCERT_DESCR *cV;
	PCERT_DESCR *cVSigner;
	PCERT_DESCR *cVRecipient;
	int count;
	long CurrentCertificate;
	long CertificateCount;
	long RecipientCertCount;
	CComBSTR ErrorString;
	unsigned char *Properties[MAX_PROP_COUNT];
	CComBSTR SignatureID;
	CComBSTR SignerCertificate; 
	CComBSTR SignerSubject;		// Set after Verify
	CComBSTR CertIssuer;		// Set after Verify
	CComBSTR CertExpiry;		// Set after Verify
	CComBSTR CertSerialNumber;	// Set after Verify
	char szTempName[MAX_PATH]; 
	short DigestMethod;
	CComBSTR DocumentURI;
	CComBSTR RecipientCertificateStore;
	short EnvelopingFlag;
	PGLOBAL_SIG SigHandle;
	CComBSTR StoreName;
	CLicense LicObj;
	CConfig ConfObj;
	CComBSTR ReleaseVersion;
	DS_DATA_BLOB PfxPassword;
	DS_DATA_BLOB HMACPassword;
	unsigned char *PfxX509Cert;
	unsigned char  *B64PfxDataPtr;
	DS_DATA_BLOB PfxCertDataBlob;
	PCERT_DESCR  PfxCertInfo;
	CComBSTR	TimeStampURL;
	int			TimeStampOption;
	long		TimeStampFormat;
	BOOL		TimeStampCritical;
	BOOL		DoDCompliance;
	long	PhysicalSigUsage;
	BOOL	CaptureSigOnce;
	BOOL	SignatureCaptured;
	char	PhysicalSignatureFileName[MAX_PATH+1];
	char	CapturedSignatureFileName[MAX_PATH+1];
	char	WindowImageFileName[MAX_PATH+1];
	RECT	SignatureCaptureWindowDim;
	string	SigImageGuid;
	BOOL	AddWindowImageFlag;
	//GdiplusStartupInput gdiplusStartupInput;
	//ULONG_PTR gdiplusToken;

	BOOL UseHMAC;
	CComBSTR HMACKey;
#ifdef WIN32
	CShowSelectCert *dlg;
	CShowSelectCert *dlgRecipient;
#endif
	BOOL DetailedVerificationReportFlag;
	BOOL ExcludeSignerCertificateFlag;
	BOOL OverwriteFileFlag;
	VERIFICATION_PARAMS CertVerifyParams;
	unsigned char *camServerHost;
	USHORT		  camServerPort;
	CCAMClient *pCamClient;
	BOOL	useCam;
	BOOL	useOcsp;
#ifdef WIN32
	IOcspClient *pOcspClient;
#elif defined UNIX && defined USE_OCSP
	nsCOMPtr<IOcspClientL> pOcspClient;
#endif
	unsigned char agencyId[MAX_PATH];
	BOOL Base64EncodeXML;
	BOOL Base64DecodeXML;
	BOOL IncludeCamResponse;
	BOOL IncludeCRLInSignature;
	unsigned char *CamResponseAsciiCert;
	unsigned char *CamResponseCaSignedMsg;
	int CamResponseAsciiCertSize;
	int CamResponseCaSignedMsgSize;
	unsigned char *CamResponseTransactionId;

	CComBSTR ocspTextResponse;
	CComBSTR ocspB64Response;
	CComBSTR ocspRevocationReason;
	CComBSTR ocspRevocationTime;
	CComBSTR ocspResponderUrl;
	CComBSTR ocspOutputResponderUrl;
	CComBSTR ocspRequestSignerB64PfxCert;
	CComBSTR ocspRequestSignerB64PfxCertPath;
	CComBSTR ocspRequestSignerB64PfxCertPassword;
	CComBSTR ocspInputNonce;
	CComBSTR ocspOutputNonce;
	CComBSTR ocspResponseCACertPath;
	long IncludeOcspResponse;
	CComBSTR proxyHost;
	USHORT   proxyPort;
	CComBSTR proxyUserName;
	CComBSTR proxyPassword;

	char pout[MAX_PATH * 2], pout2[MAX_PATH * 2];
	LONG CertSerialNumberFormat;

	LPWSTR *allowedCertIssuerNames;
	UINT  allowedCertIssuerCount;

	long CanonicalizationMethod;
	static const string FL_LIC2;
	static const string FL_LIC7;
	static const string FL_LIC4;
	static const string FL_LIC9;
	static const string FL_LIC6;
	static const string FL_LIC10;
	static const string FL_LIC1;
	static const string FL_LIC5;
	static const string FL_LIC8;
	static const string FL_LIC3;

	HINSTANCE		m_hInstEnglish,	m_hInstFrench, m_hInstJapanese, 
					m_hInstHungarian, m_hInstSpanish, m_hInstGerman, m_hInstPortuguese;
	BOOL	FileAccessRestricted;

#ifdef WIN32
	CRLCache *pCrlCache;
	CComBSTR CRLCacheDbConnectionString;
	long crlCacheTimeoutInMinutes;
	ICertStore	*nsCertStoreObj;
#endif
	BSTR		nsStorePassword;
	BOOL		UsingNetscape;
	CComBSTR	SecureXMLPath;
	CComBSTR	Language;
	TempFileList *tmpFileList;
	unsigned char *PhysicalSignatureB64Str;
	BOOL		calculateDigestOnly;
	unsigned char *signerCertChain;
	unsigned int signerCertChainSize;
	BOOL	IgnoreIncompleteSignature;
	long	SigIndexToVerify;
#ifndef WIN32
	static const char *SecureXMLVersion;
	static const char *ReleaseTime;
#endif
	inline LPWSTR ANSIToUnicode(LPCSTR String)
	{
		LPWSTR lpszW = new WCHAR[strlen(String) + 1];
		for(size_t I = 0; I <= strlen(String); I++)
			lpszW[I] = (WCHAR) String[I];
	
		return lpszW;
	};

	inline bool GetIDispatchProperty(const LPDISPATCH _lpDispatch, LPCSTR _Name, CComVariant& _ExVariant)
	{
		bool Ret = false;
	
		DISPID dispid = 0;
		OLECHAR FAR* szMember = ANSIToUnicode(_Name);
	
		HRESULT Hr = _lpDispatch->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
	
		if(Hr == S_OK)
		{
			VARIANT pVarResult;
	
			DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
			EXCEPINFO excepinfo;
			UINT nArgErr;
	
			Ret = true;
	
			try
			{
				Hr = _lpDispatch->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET,
										&dispparamsNoArgs, &pVarResult, &excepinfo, &nArgErr);
			}
			catch(...)
			{
				Ret = false;
			}
			
			CComVariant ExVariant(pVarResult);
			_ExVariant = ExVariant;
		}
		delete szMember;
		return Ret;
	};

	STDMETHOD(GetError)(/*[out, retval]*/ BSTR *errorString);
	STDMETHOD(Verify)(/*[in]*/ BSTR signatureFileName, /*[out, retval]*/ BOOL *sigStatus);
	STDMETHOD(SaveXMLSignature)(/*[in]*/ BSTR sigFileName);

	//STDMETHOD(GetXMLSignature)(/*[out, retval]*/ BSTR *xmlSignature);
	STDMETHOD(get_IncludeCamResponse)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_IncludeCamResponse)(/*[in]*/ BOOL newVal);

	STDMETHOD(Sign)(/*[in]*/ BSTR URI, /*[out, retval]*/ BSTR *tempFileName);
	STDMETHOD(get_PhysicalSignatureFile)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_PhysicalSignatureFile)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_CapturedSignatureFile)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_PhysicalSignatureUsage)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PhysicalSignatureUsage)(/*[in]*/ long newVal);
	STDMETHOD(get_SignatureStatus)(/*[in]*/ long sigIndex, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_Language)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Language)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_DigestObjectStatus)(/*[in]*/ long sigIndex, /*[in]*/ long uriIndex, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_DocumentURI)(/*[in]*/long sigIndex, /*[in]*/ long uriIndex, /*[out, retval]*/ BSTR *pVal);
//	STDMETHOD(get_DigestAlgorithm)(/*[in]*/long sigIndex, /*[in]*/ long uriIndex, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Base64DecodeXML)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_Base64DecodeXML)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_Base64EncodeXML)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_Base64EncodeXML)(/*[in]*/ BOOL newVal);
	//STDMETHOD(get_SignatureAlgorithm)(/*[in]*/ long index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Properties)(/*in*/ long sigIndex, /*in*/ long propIndex, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Properties)(/*in*/ long sigIndex, /*in*/ long propIndex, /*[in]*/ BSTR newVal);
	STDMETHOD(get_SignatureID)(/*[in]*/ long index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_SignatureID)(/*[in]*/ long index,/*[in]*/ BSTR newVal);
	STDMETHOD(get_SignerCertificate)(/*in*/ long index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_SignerCertificate)(/*in*/ long index, /*[in]*/ BSTR newVal);
	STDMETHOD(get_RecipientCertificateStore)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_RecipientCertificateStore)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_EnvelopingFlag)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_EnvelopingFlag)(/*[in]*/ short newVal);
protected:
	BOOL DecryptBlob(PDS_DATA_BLOB cBlob, PDS_DATA_BLOB dBlob, BYTE *inFile, BYTE *outFile);
public:
	STDMETHOD(put_XpathNamespace)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_RecipientCertificates)(VARIANT newVal);
	STDMETHOD(EncryptStr)(BSTR inputStr, BSTR* cipherStr);
	STDMETHOD(DecryptStr)(BSTR cipherText, BSTR* plainText);
	STDMETHOD(EncryptFile)(BSTR inputFile, BSTR outputFile, BSTR* encryptedFile);
	STDMETHOD(DecryptFile)(BSTR inputFile, BSTR outputFile, BSTR* decryptedFile);
	//BYTE * EncryptBlob(DS_DATA_BLOB * blobPtr, unsigned long * encryptedSize);
	BYTE * CSignature::EncryptBlob(DS_DATA_BLOB * blobPtr, BOOL base64EncodeOutput, unsigned long * encryptedSize, BSTR inputFile, BSTR outputFile);
	STDMETHOD(put_TrustedRoots)(VARIANT newVal);
	STDMETHOD(put_RecipientCertificateFiles)(VARIANT newVal);
	BOOL CheckCertificateValidity(BYTE * certData, LPSYSTEMTIME pSysTime, PDS_DATA_BLOB password, VERIFICATION_PARAMS * certVerParams, PGLOBAL_SIG pg_sig);
	BOOL crVerifyCertificateUsingCam(BYTE **certData, UINT certNum, LPSYSTEMTIME pSysTime, LPWSTR hKey, VERIFICATION_PARAMS *certVerParams, PGLOBAL_SIG pg_sig);
	BOOL crVerifyCertificateUsingOcsp(BYTE **certificateList, UINT certificateCount, LPSYSTEMTIME pSysTime, LPWSTR hKey, VERIFICATION_PARAMS *certVerParams, PGLOBAL_SIG pg_sig);
	STDMETHOD(put_DetachedObjects)(VARIANT newVal);
	STDMETHOD(put_AttachedObjects)(VARIANT newVal);
	STDMETHOD(ReadAllBase64)(BSTR uri, BSTR* base64EncodedData);
	STDMETHOD(put_DecryptionPFXCertFile)(BSTR newVal);
	STDMETHOD(put_DecryptUsingPFXFileCert)(BOOL newVal);
	STDMETHOD(put_DecryptionPFXPassword)(BSTR newVal);
	STDMETHOD(get_CamServerHost)(BSTR* pVal);
	STDMETHOD(put_CamServerHost)(BSTR newVal);
	STDMETHOD(get_CamServerPort)(USHORT* pVal);
	STDMETHOD(put_CamServerPort)(USHORT newVal);
	STDMETHOD(get_UseCam)(BOOL* pVal);
	STDMETHOD(put_UseCam)(BOOL newVal);
	STDMETHOD(get_AgencyId)(BSTR* pVal);
	STDMETHOD(put_AgencyId)(BSTR newVal);
	STDMETHOD(get_CamValidationResponse)(BSTR* pVal);
	STDMETHOD(GetSigPropValueByName)(LONG sigIndex, BSTR propName, BSTR* propValue);
	STDMETHOD(Base64DecodeBufferToFile)(BSTR encodedBuffer, BSTR outFilePath, BSTR* decodedFilePath);
	STDMETHOD(Base64DecodeFileToFile)(BSTR encodedFilePath, BSTR outFilePath, BSTR* decodedFilePath);
	STDMETHOD(GunZipFile)(BSTR gZippedFile, BSTR gUnZippedFile, BSTR* gUnZippedFilePath);
	void FreeBufferLinkedList(BufferLinkedList * listHeadPtr);
	STDMETHOD(get_CertSerialNumberFormat)(LONG *pVal);
	STDMETHOD(put_CertSerialNumberFormat)(LONG newVal);
	unsigned char *Base64BinToPlainHex(unsigned char *base64Bin);
	unsigned char *PlainHexToBase64Bin(unsigned char *plainHex);
	STDMETHOD(SecureXMLVerifyFileToBuffer)(BSTR signedXMLFile, BSTR* verificationResponse);
	STDMETHOD(SecureXMLVerifyFileToFile)(BSTR signedXMLFile, BSTR outFilePath, BSTR* verificationResponseFilePath);
	STDMETHOD(DeleteSignatureFromXMLStr)(BSTR signedXMLStr,  BSTR sigId, BSTR* newSigXMLStr);
	STDMETHOD(DeleteSignatureFromFile)(BSTR signedXMLFile, BSTR sigId, BSTR outFilePath, BSTR* newSigFilePath);
	STDMETHOD(put_AllowedCertIssuerNames)(VARIANT newVal);
	STDMETHOD(get_CRLCacheDbConnectionString)(BSTR* pVal);
	STDMETHOD(put_CRLCacheDbConnectionString)(BSTR newVal);
	STDMETHOD(get_UseCRLCache)(BOOL* pVal);
	STDMETHOD(put_UseCRLCache)(BOOL newVal);
	STDMETHOD(put_CRLCacheTimeoutInMinutes)(long newVal);
	STDMETHOD(put_CanonicalizationMethod)(long newVal);
	STDMETHOD(get_NetscapeStorePassword)(BSTR* pVal);
	STDMETHOD(put_NetscapeStorePassword)(BSTR newVal);
	STDMETHOD(SetActivePEMFileCert)(BSTR pemFileName, BSTR pemPassword, BSTR* pemX509Cert);
	STDMETHOD(get_SecureXMLPath)(BSTR* pVal);
	STDMETHOD(get_SignedDocumentCount)(LONG sigIndex, LONG* pVal);
	STDMETHOD(SignXMLByteArray)(VARIANT xmlByteArray, BSTR signatureId, VARIANT* signedXMLByteArray);
	STDMETHOD(SaveXMLByteArray)(VARIANT inputXmlByteArray, BSTR fileName, BSTR* path);
	STDMETHOD(ReadAllByteArray)(BSTR fileName, VARIANT* fileDataByteArray);
	STDMETHOD(VerifyXMLByteArray)(VARIANT signedXmlByteArray, BOOL * sigStatus);
	STDMETHOD(SecureXMLVerifyByteArray)(VARIANT signedXmlByteArray, VARIANT* verificationResponseByteArray);
	STDMETHOD(SignXMLXpathByteArray)(VARIANT inputXmlByteArray, BSTR xpathExp, BSTR signatureId, VARIANT* signedXmlByteArray);
	STDMETHOD(SignXMLEnvelopedByteArray)(VARIANT inputXmlByteArray, BSTR sigId, VARIANT* signedXmlByteArray);
	STDMETHOD(Base64DecodeByteArrayToFile)(VARIANT encodedBuffer, BSTR outFilePath, BSTR* decodedFilePath);
	STDMETHOD(Base64DecodeByteArrayToByteArray)(VARIANT encodedBuffer, VARIANT* decodedBuffer);
	STDMETHOD(Base64EncodeByteArrayToByteArray)(VARIANT inputBinary, VARIANT* encodedBuffer);
	STDMETHOD(Base64EncodeByteArrayToFile)(VARIANT inputBinary, BSTR outFilePath, BSTR* encodedFilePath);
	STDMETHOD(Base64EncodeStrToFile)(BSTR inputStr, BSTR outFilePath, BSTR *encodedFilePath);
	STDMETHOD(Base64EncodeStrToStr)(BSTR inputStr, BSTR* encodedStr);
	STDMETHOD(SetActivePFXB64Data)(BSTR b64PfxData, BSTR pfxPassword, BSTR* pfxX509Cert);
	STDMETHOD(get_FloatingLicense)(BSTR *floatingLicenseStr);
	STDMETHOD(put_FloatingLicense)(BSTR newVal);
	STDMETHOD(get_LicensedUserCount)(LONG* pVal);
	STDMETHOD(put_IncludeCRLInSignature)(BOOL newVal);
	STDMETHOD(get_UsedCRLList)(VARIANT* pVal);
	STDMETHOD(GetErrorDetail)(LONG errorNum, BSTR* errorDesc);
	STDMETHOD(put_PhysicalSignatureB64Str)(BSTR newVal);
	STDMETHOD(GetSignedInfoDigest)(BSTR xmlStr, BSTR signatureId, BSTR* signedInfoDigest);
	STDMETHOD(GetX509CertificateChain)(BSTR certID, BSTR* certChainAsXmlStr);
	BYTE ** getSignerCertChain(UINT * certificateCount);
	STDMETHOD(put_SignerCertificateChain)(BSTR newVal);
	STDMETHOD(get_SignatureImageId)(BSTR* pVal);
	STDMETHOD(put_SignatureImageId)(BSTR newVal);
	STDMETHOD(SignSignedInfoDigest)(BSTR b64CertData, BSTR b64SignedInfoDigest, BSTR* b64SigValXml);
	STDMETHOD(ApplySignatureValue)(BSTR b64SigValXml, BSTR* signedXML);
	STDMETHOD(GetSignedInfoDigestFromByteArray)(VARIANT xmlByteArray, BSTR signatureId, BSTR* signedInfoDigest);
	STDMETHOD(ApplySignatureValueGetByteArray)(BSTR b64SigValXml, VARIANT* signedXmlByteArray);
	STDMETHOD(GetSignedDocumentB64Str)(LONG sigIndex, LONG uriIndex, BSTR* signedDocB64Str);
	STDMETHOD(GetSignedDocumentByteArray)(LONG sigIndex, LONG uriIndex, VARIANT* signedDocumentByteArray);
	STDMETHOD(get_CertValidationTransactionId)(BSTR* pVal);
	STDMETHOD(put_CertValidationTransactionId)(BSTR newVal);
	STDMETHOD(get_IgnoreIncompleteSignature)(BOOL* pVal);
	STDMETHOD(put_IgnoreIncompleteSignature)(BOOL newVal);
	STDMETHOD(get_SignatureIndexToVerify)(LONG* pVal);
	STDMETHOD(put_SignatureIndexToVerify)(LONG newVal);
	STDMETHOD(get_UseOcsp)(BOOL* pVal);
	STDMETHOD(put_UseOcsp)(BOOL newVal);
	STDMETHOD(get_OcspTrustedRespSignerCertPath)(BSTR* pVal);
	STDMETHOD(put_OcspTrustedRespSignerCertPath)(BSTR newVal);
	STDMETHOD(get_OcspReqSignerPFXCertPath)(BSTR* pVal);
	STDMETHOD(put_OcspReqSignerPFXCertPath)(BSTR newVal);
	STDMETHOD(get_OcspReqSignerPFXCertPassword)(BSTR* pVal);
	STDMETHOD(put_OcspReqSignerPFXCertPassword)(BSTR newVal);
	STDMETHOD(get_OcspResponderURL)(BSTR* pVal);
	STDMETHOD(put_OcspResponderURL)(BSTR newVal);
	STDMETHOD(get_OcspTextResponse)(BSTR* pVal);
	STDMETHOD(get_OcspB64Response)(BSTR* pVal);
	STDMETHOD(get_CertRevocationDate)(BSTR* pVal);
	STDMETHOD(get_IncludeOcspResponse)(LONG* pVal);
	STDMETHOD(put_IncludeOcspResponse)(LONG newVal);
	STDMETHOD(put_ProxyHost)(BSTR newVal);
	STDMETHOD(put_ProxyPort)(USHORT newVal);
	STDMETHOD(put_ProxyUserName)(BSTR newVal);
	STDMETHOD(put_ProxyPassword)(BSTR newVal);
	STDMETHOD(put_InclusiveNamespacePrefixList)(VARIANT newVal);
	xmlDocPtr PrepareSignatureEnvelopeFromObjects(char *charSigId, xmlNodePtr * sigNode, xmlNodePtr * signedInfoNode);
	BSTR createSgts();
	STDMETHOD(get_TimeStampFormat)(LONG* pVal);
	STDMETHOD(put_TimeStampFormat)(LONG newVal);
	STDMETHOD(get_TimeStampCritical)(LONG* pVal);
	STDMETHOD(put_TimeStampCritical)(LONG newVal);
	STDMETHOD(put_SignedObjectId)(VARIANT newVal);
};

class SigException : public exception {
	char *err;
public:
	SigException(char *msg = "Internal error occured.") {
		err = msg;
	}
	virtual const char *what() const throw() {
		return err;
	}
};

#if __cplusplus
extern "C" {
#endif

HRESULT WINAPI VariantFromByteArray(VARIANTARG *pVar, const char *bArr, long nLength);

#if __cplusplus
}
#endif


#endif //__SIGNATURE_H_
