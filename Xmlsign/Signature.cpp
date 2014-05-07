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
// Signature.cpp : Implementation of CSignature

#include "StdAfx.h"

#ifdef WIN32
#include "XMLSign.h"
#include <mshtml.h>
#include <oleacc.h>
#include <atltime.h>
#include <stdio.h>
#elif UNIX

#ifndef SOLARIS
#include <uuid/uuid.h>
#else
#include "uuid.h"
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#include "Signature.h"
#include <windows.h>

#ifdef WIN32
#include <winver.h>
#endif

#ifndef NSS
#include <wincrypt.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>

#ifndef SOLARIS
#include <exdisp.h>
#endif

#include <fstream>
#include "zlib/zlib.h"

#if __cplusplus
extern "C" {
#endif

#include <securexml/coresig.h>
#include <securexml/xs.h>
#include <securexml/utils.h>
#include <securexml/errors.h>
#include <securexml/cr.h>
#include <securexml/DebugLog.h>
#include "pem2pfx.h"

#ifdef WIN32
#include <securepad/securepad.h>
#include "securepad_i.c"
#endif

extern unsigned char *errorMsgTable[];

#ifdef UNIX
#include <securexml/SysBufferLinux.h>
#include <securexml/unicodeLinux.h>
#include <securexml/addStrLinux.h>
#define USES_CONVERSION
DEFINE_GUID(GUID_NULL, 0,0,0,0,0,0,0,0,0,0,0);
#endif

#if __cplusplus
}
#endif

#include <securexml/base64.h>
#include "Sntp.h"

#ifdef WIN32
#include ".\signature.h"
#include <strsafe.h>
#import "..\NetscapeCert\_NetscapeCert.tlb"
#import "PemUtil\Release\PemUtil.dll"
#import "..\lib\ocspAx.dll"
#import "SigWinImage\Release\SigWinImage.dll"

using namespace NetscapeCert;
using namespace PemUtil;
using namespace ocspAX;
using namespace SigWinImage;

#elif UNIX

#ifdef USE_XPCOM
#include <nsCOMPtr.h>
#include <nsVariant.h>
#endif

#endif

//extern HRESULT	CaptureMouseSignature(char *filePathBuf, BOOL sigCapturedOnce, RECT *windowDim, char *guidStr);
//extern HRESULT	ShowFileSignature(char *filePathBuf, char *outFilePathBuf, BOOL sigCapturedOnce, RECT *windowDim, char *guidStr);
//extern BOOL CaptureCurrentWindowImage (char *imageFilePath, char *guidStr);

#ifdef WIN32
#ifndef JNIBINDING
extern OLECHAR szModulePath[];
_ATL_REGMAP_ENTRY CSignature::RegEntries[] = { { OLESTR("ModulePath"), szModulePath}, { NULL, NULL} };
#endif
void GuidToString(GUID *guid, char *guidStr);
#endif

unsigned char Base64Chars[] ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

#ifdef UNIX
#ifdef USE_XPCOM
extern VARIANT nsVar2VarConvert(nsIVariant *nsVar);
extern nsresult Var2nsVarConvert(VARIANT var, nsCOMPtr<nsIWritableVariant>);
#endif
extern void GetSystemTimeLinux(SYSTEMTIME *);
#endif

extern unsigned char * HeapW2A(BSTR bstrStr);
extern unsigned char * HeapWCHAR2A(WCHAR *wcharStr);
extern void FileEncoding(unsigned char *);
extern void PrintBstr(BSTR);

extern "C" {
BOOL DebugLogEnabled = TRUE;
BOOL MemoryLogEnabled = TRUE;
BOOL LogEnabled = TRUE;
}

static const unsigned int RestrictedProgramCount = 4;
static char *RestrictedProgramList[] = { "netscp",
								"iexplore",
								"mozilla",
								"firefox"
							};

/////////////////////////////////////////////////////////////////////////////
// CSignature 

#ifndef WIN32
const char *CSignature::SecureXMLVersion = "2.5.145.45";
const char *CSignature::ReleaseTime = "12/05/2005 10:19:10 PM";
#endif

const string CSignature::FL_LIC2 =
	"CqD09vDlKUxOwqxJTcGQSrtVoOZzOATyJZYxggEYMBMGCSqGSIb3DQEJFTEGBAQBAAAAMGMGCSsGAQQBgjcRATFWHlQATQBpAGMAcgBvAHMAbwBmAHQAIABCAGEAcwBlACAAQwByAHkAcAB0AG8AZwByAGEAcABoAGkAYwAgAFAAcgBvAHYAaQBkAGUAcgAgAHYAMQAuADAwgZsGCSqGSIb3DQEJFDGBjR6BigAzADkAZgBmAGQAMgAwAGQAZAA1AGIANAAzADUAOQBhADcAOQA1ADQAZgAyAGEAZQA5AGMAYQAzAGYAMQBhADUAXwBjADYANABjAGYAYwBiADIALQA0AGUAOQBkAC0ANAAxAGIAYQAtAGIAZAAyADYALQAyADYAMQBjADkAOABkAGQAMgAwADYAODCCDI8GCSqGSIb3DQEHBqCCDIAwggx8AgEAMIIMdQYJKoZIhvcNAQcBMBwGCiqGSIb3DQEMAQYwDgQIZmD5BywuWgYCAgfQgIIMSCBOXKF4xx6o+dvu45pFLvWjUB44S/1w504WVp4KKUgKFZOvfGIfJbIOlHp/ZbkXjqc5NdJ4KoVLq21ZmSS6ROrMIdKJlcB7AvCmJN0fuZxqe5+azq6va9Kuo7XyGZSd1AMpYwGWA54d4LXCBlnO3iH6tHDe+uTQTuAQizcWATiv59Nby7iFrilGhyO7YqN8v+Z7bVJBIR5L4cudepQeOcWhHDu2ULI14HqPY/pW7biy18OcONcMvojt7MN1A5v5M7xjNI8SOizJlBaTKQ+aFivPXuDLyab5XKEUv4dSfgaine66XLNP+jk1WSTLZHxY7GWUj5PANVLB+is7WOtdm+ALjoVIYpHcnBfArrQPh3qq8a9vKNmI8q5nqCNMlRJ6hiST5D5efZAYF2/qi6CBNPaHaJk17Z0TWgsHK0oQOsFZFERyGUo0oB8fRZHDpuXvFv1Np8/cS7867atVxkxaUIGLX94uBlfsqFXDIrSX";
const string CSignature::FL_LIC7 =
	"UHmvkICg2lRPGAMG2AIqs16Hqjnp+j6FGg8VzqioenSNN6HH1VgAZmQq0LN7I9YVseMCx6KK1CkzHeqmyZr3DgNVGofUkzDSNe6KIdc9YVHGaTEoFNT7V2IJQv2L6HytuAMuMDswHzAHBgUrDgMCGgQUa6XzwBso6MhKYmYoywZj78RFceUEFA/6/K0CTxwzEPFw7/6jgBvpSsQJAgIH0A==";
const string CSignature::FL_LIC4 =
	"Y8TEQMJMCxXAxf8bPmgzWQLguurAzn6bqxJ+KkLKFGMJx7/oX2DU0wfmqV7YknpsPp9zS8ENH2aJ+9Xe7qPwaaFOW9BcIGOXWNO4uERDLzuir2hO91ex+wKwGb8kommigD+whv6gjqseN9oaKcd8jv+et/UqVBNqKRKrXkTQuXuK0wmF41PfJ4CM9RHn/1Pl3ctyRFS4OMkstDfrtaFx3Op6rmyRORhTjguonQ4+C3kHnjIPo7s3129/0/PhHhuaxTTzWiV1L48Nve6wKMC2nBHEqTuttDxQ3tIhF2O8zpkGFx8g4VPGZRya31Y8iPhH55kqaVUYopAVGbCmnquVgaiydb7wcnKis+BSoaE7kYLT2Ey9JjYlNxIbKNfUxReM4wIwojHQxDTy/xvhbqsMv0yWdBfrz8yFFSkiNjubV+mfhil0eTZ+xshOYydKtoiCLavKqiiShNrbbOaUEgtmG6WeZpVkk6h2pthUUdkuhY7/QCb2TFYyzh9PeqU///IGCIFjjCJ9JLofLGpwWQaNftb7eZ1dNIu/NwG0DsFICT9jEU2Ji7qE5BZ8bSGhY4RCmFMe6oaQodmkfCKMpBjo8sn01/wXvQDuYVSj9Ai8+KfI9nClf+d1Le+1tmLfqf/tJOT+qIpb4lTwpAbhI21KSz2yxLNRYG1FX1Gpi2kGel06feDwH0BbsfwhiSGuBxjXqKCC61mBBbVyqIARbdcLR6GZt1/RqJ3x61Z4lReFhbafKOwKUKmgWvV1xEsSy+HWRJOowAMJRSM1SFycT7m/m6mjBzl0tYCeMslOdgfV+2AOS2N0gnQa+1XTxvfC3h6S6aH1rTckTru7XLS/zQ6uz5Ottf4VWgOOr9lqQViYzFnrWbnopua4uaxX+tjjgOgsav3IaphYgSrmhyGNoia5d5igPwr/S+jw4yPuoeaIqKr6fEFL95X3flGhjNNa/hsg3PmLOJMLh6bMkJSBp3Dhb91qHVnczaUvCRt2BT4c";
const string CSignature::FL_LIC9 =
	"pXfQ/mdS7IRdWlYYMCA+WRLHMPh0yJG/1xAtWj7s5tZBR8vjN9u";
const string CSignature::FL_LIC6 =
	"C7mkE79KQdPrdI+u0/hc04UTtjvmixSrFrMsyQTj8Qa9/VgNhnAQdVDlpmseg/UN+nRl4aSU1XxNRLJW6mwULWIy2oMkdlUM5EPWZtdkgju06VF8elbmqV83jczP1u9ZmWt1tb4fNnZFXacvDICjsf4v9lywXdMkAdL3R3QC2irH85U/+T5UcXy0GKaHu267dsQ6CvW9KVpQVhmpwG+VKe8GMfa6iVrELK6OzuCZTUPA2NygU4t5WcKzif0k2PphELICpUICyk0lljOl+K6WsbLm9uiP6sDLhZDuAduyUsD1cbk9Ld4aUtICcevJV8HQPdaf6kv1/rwfy5rrMjfQm0R7qOW7nq5NMzIuC2bRTlamu8i/WJ4B2fPNUTyNGip6QzznhrZHLgraw6X+PI73tuuscoXKE0jsLAmAGO6x8LxSNKP9JOCnfqogRoSWWusAqpSbVgrb1a4T5kjSUpTarhPxnTZr0pFOr4gIMh7EAWzP5MrgL00xVkB+YSZO+zh8ERJyk7/eILFWROaGetTO7hw6MqTZJWeaqwt+AUfaR8+s/L7hBRW8f5c3AgMkLYuZ7LT8vTXfx+ZbbWQHqXGA07EvHbcKdcdWuCZPP6tZghstI/TZZko8PD77C6YmKOXAcyaCarxGpxOpB+npXmuUoYq2rvGER6Kp7Oqw9asvDflyxztD7zpEG+xH9PrQutGWrzA7MB8wBwYFKw4DAhoEFAWYQYNKeznyhd4r/ccgvkZC/oQABBQX0hGT3zvy+g96yp80pdWqIjjJ7QICB9A=";
const string CSignature::FL_LIC10 =
	"+OvbSsu8av2p9rQBT90eK8ML5zTxR1gdt7at5Xkom+9RI1GKaRlh2gfcN/i38rwjtwotOr7i6";
const string CSignature::FL_LIC1 =
	"MIIQ8AIBAzCCEKwGCSqGSIb3DQEHAaCCEJ0EghCZMIIQlTCCA/4GCSqGSIb3DQEHAaCCA+8EggPrMIID5zCCA+MGCyqGSIb3DQEMCgECoIICtjCCArIwHAYKKoZIhvcNAQwBAzAOBAj3HeWAAnVoZAICB9AEggKQZKqxNZ4EGsxyM7X4lFwnjun8KfDj6WESEwbH3bGFdOCGtqS+oy42+ws9En774h9b7i3G3b87zMa+mfBNTH6I/3NqUg+MdF0Kh6kcjGPXjVgD6ojBVwV2JHfj7kWtrV8pGOLNPjLChSh24QJ5ffhiezFUB0Ak4G5wbWCR1OW3MqOMVItLHdKdJzQG3Uj4K8VWbZmz8FlxtJzcog2vTZpkGdBxP5a6+ONyBd95T6UnkPnXqc47YYIMjeCuXb1q2BRVSAG4XZj+I0WY62uCl5dTYnB9UpvJjFlI4F0Heb3BAfUmcEZOB0GytzsWyW2OpnpZJ4chrmZ/XTZ/qqRoHYMdR6QB2eYXeWakdSoIz1feJcBpLI5vb97qU/D+o5yXJsrSwBGRf4Wlby5U82+qSC9qSh0wsEgE5RvV9+anXLaDxXUZz+pq5HF6aQ4vXI3pHiYMpOwBzeoaNMtP0AhRDsBR5ZQ1luTJXRiGnLQBQt9Qh89mD86+zgxY0jqQ705WIqrSMpG4+rlmHWI6qLnqFOttIrN5pn9wT9XVTvC7GJVlUz6+MUCn40/20vhdqYrNzGmTRCMh4Ur59LDXH7cogsME+scbdRTG+SaAFrtdagi/2pxGRS+oun9yauRktgQA3y+R+kBu8y+mj1A80ef2KrBoovsVgSDJBwloujhXoeB1an91A+XRdEfQt98zpkXxEZ4WfYogruySOHrsSeX77bO1TB4fiBQLEc0hJHqLRcPePVT/OcF6ELUt085VPmu7Jsstp3S7uqfxfdmpGDy38BQ70uO/utcP6EBkkOFKXGCrRdGGfc4insahwSvmGhP20UtByso85EK4";
const string CSignature::FL_LIC5 =
	"0OQbFpRmbUSxGFsM2IfRPcmTuj6GQIL7HOaBdFDnvFda2G9JBbo6jdYjB1v2Yd/DKCjaTkgeYv23dhOifdTxw8lTwPY4XBAekqYugtJA6HMibY/sLPvlT+TkSONJK2hHYQ/9pU/UqhBQDBfNFLw/mBke9dZatVE2P/3mu7nRb1GvSx1wshJmAiP9iDVp6888+P7GBoJe0aGUhYXbCkO6XaPrGZ6iahVB5641sSHqUAxOE3IjHOqCxaWLMREduSbSRYcCWwqPQfK/NFRYZiE7kZmQ1CMItYp0AFfXDaoLf7TYQQYgltQkrGA2G/BlSveEaXPaaFJBEWq3yR+0GJRRMBUSywVPjAfQB52KJ+AlKjXv4Ljgt5kWCEa4C5Juzj77gu95MlkHZ3zneBpTpylNVN42/LT2Chn5v4s0K+XSPUhmUkSZ/Tgi8g8NZf5Cb8AuVQLXa32ec2g8/almzZf4T4f27BYg3XQNNbymAjxdDM+6Y3X2wgLWUnpJKfztXDgiImZYpB2rcDYhIJcSSPjkX992Frs7nrfWoAMdLIqCXEYtNHC6T4oRxYQV+Kf5SujGNQTaLzbWK2CveoqJEL7JuPHkr8voxTPj4E/MdiMlufzD0pdTx7+DPl82ViudyTFx8vElHmc2XMlgat4pB67IufXvujU2BC5FRqoUhX79gGNK0jhKqr/ZvL7zI46uqwQrsuizNiWRBrVuVdJ/lc6rx1iqqTQvD9IA17/PUwH9d6jcot9xMNHMcCtV4l1Lv0In83IEECp4jPVf7xaiJZ96FiNw9b12UpmYS3ntPKpl/wUzSrRijNwzKxHdzom+h7RiMWClqM+cpAxf2GmFroe823UB1IkUD0NPBNVys+ytl75U8o/i4eOF5EjJOko3IQDzjmPUTtOWZEVo1z14jF2UNR26TaOr037CFY+LmPgkZj7wW53MxEAxx0N0FQikVuLDjNKPdAJjlQyhwg1MPWeDG+pi2yx7AbvgzOQvSFpx";
const string CSignature::FL_LIC8 =
	"zCCEewGCSqGSIb3DQEHAaCCEd0EghHZMIIR1TCCA/4GCSqGSIb3DQEHAaCCA+8EggPrMIID5zCCA+MGCyqGSIb3DQEMCgECoIICtjCCArIwHAYKKoZIhvcNAQwBAzAOBAjRCuvybYFG2QICB9AEggKQikDH4PsWWvIs2DLre2xYmcJFvSgR32l";
const string CSignature::FL_LIC3 =
	"77kdP1ceKQe/kBTCR6qS9u262fN7H5xIvY3WJxUtJl/33sepuCBwRMApWpR9T45qkFsHUfWJalzWluV+pSauk104QVV43UATFVgLxd2OeEwqSNU7UGqHCe4TnMt6IcMSFHPZhnRdvaZ3hFIURhAuNep357YAa40urJ4kxIAdB2Bezs1OHn4vWbz3NLoxaHE5Jbf2jdyBRKI5RzIOew9vX8Rs6EVBE/aRrOyMcOWTXB+AODKlaCMbMEvDYATFALYfpqOec/62Uqwuz3CaBk/0+kljuEnjWoDzmHa+2ukjOvlfDopdc1f2aed9/RkURfGz5hMlV6zPoKJTi2HtbwZrCB/9jqqM4dvAxmF1057OPDGGM9+I/BGU/Dvh7JMUegFgQ+1oOcZqX9X7tT07qh0qFsMbLkIsZi6ZlW1eNuqpCm3CB9mHy0BGxhE5/ypFMz8R2/qp3iFWEhDrJoJ/tbwB7CAmnrpkMSJliaCauNH/nY91Pil6ATEyOpxDM5+mloM4SomBIBL+5DOFsNlBjnXK/GpIDDmcA+HOWNbP96ymQwt+ZM3eLu2c5pbLIosEMVRfTbL3+42jkrLrJEf2XqptG/7e2dPwKWlENdDBCezl1kvlmUx5uXjTmyiVG614y9YNz4+S3fbJAk1tYdiQfVBu+98qDO9XtnegeoKFnsWdbGVEFkmlLRp6dCuVZYqPnECzM8uRTLxzu0uehdfYufD8BD1eDyCgu79WtmLIR252bgUZ28HaGOKFUUkGPDRefioj+Zh4DJb93r5N4E7/MLLcjsdNIFsGh/7ke+IftJuXreH9P/k6aloptITCOnv/cLfGYDDNmrQ+oguhAC0HtysCO/iP0AxZ8IMExE6RPJ+mKHwZLwCK+CTSLFrp9siVRdCGKK9+HlWKDWsUh7Hqgl14krKRlU7HsEYvoCgkVfTRVWW6DVx1OYSt7egpS6OCP9ADcZrr79Uz6+0xnqMdXeq7ZyW2U1+FpCgPQTT0Nnl+";

// need this to bypass same member function of CSignature clas inside of implementation.
static int getlasterror()
{
	return GetLastError();
}

///
/// Callback for streaming encrypting to store encrypted content
///
BOOL WINAPI encryptCallback(IN const void *pvArg,  //in
  IN BYTE *pbData,       //in
  IN DWORD cbData,       //in
  IN BOOL fFinal)
{
	FILE *hFile = (FILE*) pvArg;
	if (fwrite(pbData, cbData, 1, hFile) == 0)
	{
		return FALSE;
	}
	if (ferror(hFile))
	{
		return FALSE;
	}
	if (fFinal)
	{
		fclose(hFile);
	}
	return TRUE;
}

CSignature::CSignature()
{
	int numCerts;
	PCERT_DESCR *certPtr;
	unsigned char *tmpCharPtr=NULL;

	sgArr=NULL;
	err=0;
	signum=0;
	uriArr=NULL;
	failedUriArr=NULL;
	failedUriCount=0;
	totalUriCount = 0;
#ifdef WIN32
	dlg = NULL;
	dlgRecipient = NULL;
#endif
	BOOL fileStatus=FALSE;
	BOOL configfileStatus=FALSE;

	count = 0;
	EnvelopingFlag = DETACHED;
	CertificateCount = 0;
	RecipientCertCount = 0;
	RecipientCertificateCount = 0;
	RecipientCertificateList = NULL;
	CurrentCertificate = NOT_INITIALIZED;
	PropertyCount = 0;
	Language = "EN";
#ifdef WIN32
	m_hInstEnglish=	m_hInstFrench= m_hInstJapanese=m_hInstGerman=m_hInstSpanish=m_hInstHungarian=m_hInstPortuguese=0;
#endif
	PfxPassword.pbData = NULL;
	PfxPassword.cbData = 0;
	PfxX509Cert = NULL;
	B64PfxDataPtr = NULL;
	PfxCertDataBlob.cbData = 0;
	PfxCertDataBlob.pbData = NULL;
	PfxCertInfo = NULL;
	TimeStampOption = FALSE;
	TimeStampFormat = TIME_RFC;
	TimeStampCritical = FALSE;
	AddWindowImageFlag = FALSE;
	DoDCompliance = FALSE;
	PhysicalSigUsage = NO_PHYSICAL_SIG;
	CaptureSigOnce	 = FALSE;
	SignatureCaptured = FALSE;
	DetailedVerificationReportFlag = TRUE;
	ExcludeSignerCertificateFlag = FALSE;
	OverwriteFileFlag = FALSE;
	UseHMAC = FALSE;
	DetachedObjectCount = 0;
	DetachedObjectList = NULL;
	AttachedObjectCount = 0;
	AttachedObjectList = NULL;
	SignedObjectIdCount = 0;
	SignedObjectIdList = NULL;
	DecryptUsingPfxFileCert = FALSE;
	DecrytionPfxPassword.pbData = NULL;
	DecrytionPfxPassword.cbData = 0;
	XpathNamespaceCount = 0;
	XpathNamespaceList = NULL;
	camServerHost=NULL;
	camServerPort=7777;
	pCamClient=NULL;
	useCam = FALSE;
	memset((void *)agencyId,0,MAX_PATH);
	strcpy((char *)agencyId, (const char *)"Infomosaic SecureXML");
	Base64EncodeXML = FALSE;
	Base64DecodeXML = FALSE;
	IncludeCamResponse = FALSE;
	IncludeCRLInSignature = FALSE;
	CamResponseCaSignedMsg = NULL;
	CamResponseAsciiCert = NULL;
	CamResponseCaSignedMsgSize = 0;
	CamResponseAsciiCertSize = 0;
	CertSerialNumberFormat = 0;
	cVRecipient = NULL;
	cV = NULL;
	cVSigner = NULL;
	allowedCertIssuerNames=NULL;
	allowedCertIssuerCount=0;
#ifdef WIN32
	pCrlCache = NULL;
	CRLCacheDbConnectionString = DEFAULT_CONN_STR;
	crlCacheTimeoutInMinutes = 0;
#endif
	CanonicalizationMethod = WITH_COMMENTS;
	UsingNetscape = FALSE;
#ifdef WIN32
	nsCertStoreObj = NULL;
	FileAccessRestricted = FALSE;
#endif
	nsStorePassword = L"";
	HMACPassword.pbData = NULL;
	HMACPassword.cbData = 0;
	tmpFileList = new (TempFileList);
	PhysicalSignatureB64Str = NULL;
	calculateDigestOnly = FALSE;
	signerCertChain = NULL;
	signerCertChainSize = 0;
	IgnoreIncompleteSignature = FALSE;
	SigIndexToVerify = -1;
	useOcsp = FALSE;
#ifdef USE_OCSP
	pOcspClient = NULL;
#endif
	IncludeOcspResponse = 0;
	InclusiveNamespaceList = NULL;

	EnterObjectLog;
	memset((void *)&CertVerifyParams,0, sizeof(VERIFICATION_PARAMS));
	memset((void *)PhysicalSignatureFileName, 0, MAX_PATH);
	memset((void *)CapturedSignatureFileName, 0, MAX_PATH);
	memset((void *)szTempName, 0, MAX_PATH);

#ifdef WIN32
	LPSTR commandLine = _strlwr(GetCommandLine());
	for (int i=0; i<RestrictedProgramCount;i++)
	{
		if (strstr(commandLine, RestrictedProgramList[i]) != NULL)
		{
			FileAccessRestricted = TRUE;
			break;
		}
	}
//	AtlAxWinInit();
#endif

	CertVerifyParams.verificationOptions |= VERIFY_CRL_REC; // Always verify the certificate with the CRL included
															// current time is used for verification

	for (int i=0; i < MAX_PROP_COUNT; i++)
		Properties[i] = NULL;

	USES_CONVERSION;
#ifdef NSS
	SigHandle = axInit(NULL,NULL);
	if (!SigHandle) {
	   throw SigException("Library initialization failed");
	}	
#else
	SigHandle = axInit();
#endif

	SigHandle->useFastC14N=TRUE;
	ConfObj = CConfig(this);
	StoreName = A2WBSTR((LPCSTR)"MY");
//	RecipientCertificateStore = A2WBSTR((LPCSTR)"addressbook");

	HKEY hkey;
	LONG lret;
	const int BUF_SIZE = 400;
	TCHAR securexml_path[BUF_SIZE];
	DWORD buflen = BUF_SIZE;
	DWORD junk, versionInfoSize;
	unsigned char *versionBuffer=NULL;
	void *lplpBuffer;
	UINT puLen;
	VS_FIXEDFILEINFO *versionStruct;
	unsigned long versionMS, versionLS;
	char charVerLS[34], charVersionStr[70];
	const char *reg_entry = "CLSID\\{D300C133-A6F6-4FB4-A734-4865FBF5A3B1}\\InprocServer32";
#ifdef WIN32
	const char FILE_SEP = '\\';
	const char *FILE_SEP_STR = "\\";
	string license_file = "C:\\Program Files\\Infomosaic\\SecureXML\\SecureXMLLicense.xml";
	string config_file = "C:\\Program Files\\Infomosaic\\SecureXML\\SecureXML.config";
#ifdef JNIBINDING
	LPTSTR lpFilePart=NULL;
	HMODULE hMod = GetModuleHandle("SignatureL.dll");
	DWORD retPathLen = GetModuleFileName(hMod,(LPTSTR)securexml_path,BUF_SIZE);
	//DWORD retPathLen = SearchPath(NULL,"SignatureL.dll",NULL,BUF_SIZE,(LPTSTR)securexml_path,&lpFilePart);
	if (retPathLen==0 || retPathLen > BUF_SIZE) {
		throw SigException("DLL not found");
	}
#else
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT,
		reg_entry, 0, KEY_QUERY_VALUE, &hkey) != ERROR_SUCCESS) {
		setError(SigHandle, DLL_NOT_REGISTERED);
	} else {
		lret = RegQueryValueEx(hkey, NULL, NULL, NULL,
								(LPBYTE) securexml_path, &buflen);
		if (lret != ERROR_SUCCESS)
			setError(SigHandle, DLL_NOT_REGISTERED);
	}
	RegCloseKey(hkey);
#endif

	string dll_file = securexml_path;
	unsigned int pos = dll_file.rfind(FILE_SEP);
	if (pos != -1){
		// This looks at the registry entry for the actual install directory
		license_file = dll_file.substr(0, pos) + FILE_SEP_STR + SECUREXML_LICENSE_FILENAME;
		config_file = dll_file.substr(0, pos) + FILE_SEP_STR + SECUREXML_CONFIG_FILENAME;
		SecureXMLPath = A2WBSTR((char *)dll_file.substr(0, pos).c_str());
	}
/* Lets try to load the English dialog resource file */
	if(!m_hInstEnglish)
		m_hInstEnglish = LoadLibraryW(_bstr_t("EnglishDiag.dll"));
	if (m_hInstEnglish == NULL)
		m_hInstEnglish = LoadLibraryW(_bstr_t((dll_file.substr(0, pos) + FILE_SEP_STR + ENGLISH_RESOURCE_DLL).c_str()));
	if (m_hInstEnglish != NULL)
		_Module.SetResourceInstance(m_hInstEnglish);
	else
		m_hInstEnglish = _Module.GetResourceInstance();

#else
	const char FILE_SEP = '/';
	const char *FILE_SEP_STR = "/";
	string license_file = "/usr/local/infomosaic/SecureXMLLicense.xml";
	string config_file = "/usr/local/infomosaic/SecureXML.config";
	SecureXMLPath = A2WBSTR("/usr/local/infomosaic");
#endif

#ifdef WIN32
	versionInfoSize = GetFileVersionInfoSize(
											 securexml_path,
											 (LPDWORD) &junk
											 );

	if (versionInfoSize==0) {
		char buf[BUF_SIZE];
		sprintf(buf,"No version information found in DLL: %s",securexml_path);
		throw SigException(buf);
	}
	versionBuffer = (unsigned char *)zMalloc(versionInfoSize);

	GetFileVersionInfo(	securexml_path,
						(DWORD) 0,
						versionInfoSize,
						(LPVOID) versionBuffer
						);

	VerQueryValue((const LPVOID) versionBuffer,
				  "\\",
				  &lplpBuffer,
				   &puLen
				);

	versionStruct = (VS_FIXEDFILEINFO *) lplpBuffer;

	versionMS = versionStruct->dwProductVersionMS;
	versionLS = versionStruct->dwProductVersionLS;

	sprintf(charVersionStr, "%d.%d", (versionMS >> 16), (versionMS & 0xFFFF));
	sprintf(charVerLS, ".%d.%d", (versionLS >> 16), (versionLS & 0xFFFF));

	strcat(charVersionStr, (const char *)charVerLS);

	ReleaseVersion.m_str = A2WBSTR((LPCSTR)charVersionStr);

	DebugLog(charVersionStr);

    //Before reading any strings out of the resource, we must first determine the code page
    //and language.  The code to get this information follows.
    VerQueryValue((const LPVOID) versionBuffer, "\\VarFileInfo\\Translation", &lplpBuffer, &puLen);
    //Convert those four bytes into a 8-digit hexadecimal string.
	short *languageCode=NULL, *codePage=NULL;
	languageCode = (short *)lplpBuffer;
	codePage = languageCode + 1;
	sprintf(charVersionStr, "\\StringFileInfo\\%04x%04x\\PrivateBuild", *languageCode, *codePage);
	DebugLog(charVersionStr);

	VerQueryValue((const LPVOID) versionBuffer,
				  charVersionStr, // ==  \StringFileInfo\040904b0\PrivateBuild
				  &lplpBuffer,
				   &puLen
				);
	lstrcpy((LPTSTR)charVersionStr, (LPCTSTR) lplpBuffer);
	DebugLog(charVersionStr);
	LPSYSTEMTIME releaseTimeStamp = vbNowTimeToSystem((BYTE *)(char *)charVersionStr);
	CTime releaseTime(*releaseTimeStamp, -1);

	LicObj.releaseTime = releaseTime;
	
	zFree(versionBuffer);
	zFree(releaseTimeStamp);
#else
	ReleaseVersion.m_str = A2WBSTR((LPCSTR)CSignature::SecureXMLVersion);
	LPSYSTEMTIME releaseTimeStamp = vbNowTimeToSystem((BYTE *)(char *)CSignature::ReleaseTime);
	LicObj.releaseYear = releaseTimeStamp->wYear;
	LicObj.releaseMonth = releaseTimeStamp->wMonth;
	LicObj.releaseDay	= releaseTimeStamp->wDay;
#endif

	// Check if the license file exists
	FILE *fHandle = fopen((char *)license_file.c_str(), "r");
	if (fHandle == NULL)
		fileStatus = FALSE;
	else
	{
		fileStatus = TRUE;
		fclose(fHandle);
	}
	fHandle = fopen((char *)config_file.c_str(), "r");
	if (fHandle == NULL)
		configfileStatus = FALSE;
	else
	{
		configfileStatus = TRUE;
		fclose(fHandle);
	}
	if (fileStatus) // License file exists
	{
		LicObj.setLicenseFile((char *)license_file.c_str());
		if (LicObj.getLicenseDetails(SigHandle))
			LicObj.verifyLicense(SigHandle);
	}
	else // License file not found
		setError(SigHandle, NO_SECUREXML_LIC);	

	if (configfileStatus) // Config file exists
	{	
		ConfObj.setConfigFile((char *)config_file.c_str());
		ConfObj.getConfigDetails(SigHandle);
	}


	tmpCharPtr = HeapW2A(StoreName.m_str);
#ifdef NSS
	if ((certPtr = axGetCertificateList(tmpCharPtr, &numCerts, SigHandle )) != NULL)
#else
	if ((certPtr = axGetCertificateList(tmpCharPtr, &numCerts )) != NULL)
#endif
	{
		CertificateCount = (long) numCerts;
		if (numCerts > 0)
			cVSigner = certPtr;
		else
		{
			cVSigner = NULL;
		}
	}

	if ((allowedCertIssuerCount != 0) && (CertificateCount != 0))
	{
		int *indexArray = (int *)zMalloc(sizeof(int) * CertificateCount);
		int allowedCertCount = 0;

		for (unsigned int i=0; i < allowedCertIssuerCount; i++)
		{
			for(int j=0; j < CertificateCount; j++)
			{
				if (!strcmp((const char*)allowedCertIssuerNames[i], (const char *)cVSigner[j]->issuer))
				{
					indexArray[allowedCertCount] = j;
					allowedCertCount++;
				}
			}
		}
		for (int i=0; i<CertificateCount; i++)
		{
			BOOL certificateAllowed = FALSE;
			for (int j=0; j<allowedCertCount; j++)
			{
				if (indexArray[j] == i)
				{
					certificateAllowed = TRUE;
					break;
				}
			}
			if (certificateAllowed == FALSE)
			{
				if (cVSigner[i]->certificate != NULL)
					zFree(cVSigner[i]->certificate);
				zFree(cVSigner[i]);
			}
		}
		CertificateCount = allowedCertCount;
		cV = (PCERT_DESCR *)zMalloc(sizeof(PCERT_DESCR *) * CertificateCount);
		for (int i=0; i<CertificateCount; i++)
			cV[i] = cVSigner[indexArray[i]];
		zFree(cVSigner);
		zFree(indexArray);
	}
	else
		cV = cVSigner;
#ifdef WIN32
	if (CertificateCount)
	{
		dlg = new CShowSelectCert(/*this,*/ tmpCharPtr, cV,  CertificateCount);
//		dlg->Create(NULL);
	}
#endif
	zFree(tmpCharPtr);

#ifndef NSS
	tmpCharPtr = HeapW2A(RecipientCertificateStore.m_str);
	if ((certPtr = axGetRecipientCertificateList(tmpCharPtr, &numCerts )) != NULL)
	{
		RecipientCertCount = (long) numCerts;
		if (numCerts > 0)
			cVRecipient = certPtr;
		else
		{
			cVRecipient = NULL;
		}
	}
#ifdef WIN32
	if (RecipientCertCount)
	{
		dlgRecipient = new CShowSelectCert(/*this,*/ tmpCharPtr, cVRecipient, RecipientCertCount);
//		dlgRecipient->Create(NULL);
	}
#endif
	zFree(tmpCharPtr);
#endif
	// Initialize GDI+.
//	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	ExitObjectLog;
}

CSignature::~CSignature()
{
	EnterObjectLog;
	Empty();

//	GdiplusShutdown(gdiplusToken);
#ifdef LOGGING
	DumpUnfreed();
#endif
	ExitObjectLog;
}

void CSignature::Empty()
{
	unsigned int i;
	EnterObjectLog;
	EnvelopingFlag = DETACHED;
	DigestMethod  = 1;

	if (tmpFileList != NULL)
	{
		for (TempFileList::iterator j = tmpFileList->begin(); j != tmpFileList->end(); j++)
		{
			if ((*j) != NULL)
			{
				char cbuf[512];				
				char *p = (char *)(*j)->fileName;
				if (p) {
					strcpy(cbuf,p);
#ifdef WIN32
					if (DeleteFile((LPCTSTR) cbuf) == 0)
					DeleteFileW((LPWSTR) cbuf);
#else
					if (unlink((LPCTSTR) cbuf) != 0)
					{
						unsigned char *afileName = HeapW2A((LPWSTR)cbuf);
						unlink((const char *)afileName);
						zFree(afileName);
					}
#endif
				}
			}
		}
		delete tmpFileList;
		tmpFileList = NULL;
	}

	DocumentURI.Empty();
	SignerCertificate.Empty();
	SignatureID.Empty();
	ReleaseVersion.Empty();
	SignerSubject.Empty();		// Set after Verify
	CertIssuer.Empty();		// Set after Verify
	CertExpiry.Empty();		// Set after Verify
	CertSerialNumber.Empty();	// Set after Verify
	DocumentURI.Empty();
	RecipientCertificateStore.Empty();
	SecureXMLPath.Empty();
	StoreName.Empty();
	TimeStampURL.Empty();
	HMACKey.Empty();
#ifdef WiN32
	CRLCacheDbConnectionString.Empty();
#endif
	ocspTextResponse.Empty();
	ocspB64Response.Empty();
	ocspRevocationTime.Empty();
	ocspRevocationReason.Empty();

	if (signerCertChain != NULL)
		zFree(signerCertChain);

	if (PhysicalSignatureB64Str != NULL)
		zFree(PhysicalSignatureB64Str);

	if (B64PfxDataPtr != NULL)
		zFree(B64PfxDataPtr);
	
	if (PfxCertDataBlob.pbData != NULL)
		zFree(PfxCertDataBlob.pbData);
	
	if (PfxPassword.pbData != NULL)
		zFree(PfxPassword.pbData);
	
	if (HMACPassword.pbData) 
		zFree (HMACPassword.pbData);

	if (PfxX509Cert != NULL)
		zFree(PfxX509Cert);

	for (i=0; i<MAX_PROP_COUNT; i++)
	{
		if (Properties[i] != NULL)
		{
			zFree(Properties[i]);
			Properties[i] = NULL;
		}
	}

	FreeUriArr();

	//if ((UsingNetscape == FALSE) || (allowedCertIssuerCount != 0))
		if (cV != NULL)
		{
			for (i=0; i<(UINT)CertificateCount; i++)
			{
				if (cV[i]->certificate != NULL)
					zFree(cV[i]->certificate);
				zFree(cV[i]);
			}
			zFree(cV);
			cV = NULL;
		}
	if (cVRecipient != NULL)
	{
		for (i=0; i<(UINT)RecipientCertCount; i++)
		{
			if (cVRecipient[i]->certificate != NULL)
				zFree(cVRecipient[i]->certificate);
			zFree(cVRecipient[i]);
		}
		zFree(cVRecipient);
		cVRecipient = NULL;
	}
#ifdef WIN32
	if ((UsingNetscape == TRUE) && (nsCertStoreObj != NULL))
	{
		nsCertStoreObj->Release();
		CoUninitialize();
	}
#endif
#ifdef USE_OCSP
	if ((useOcsp == TRUE) && (pOcspClient != NULL))
	{
#ifdef WIN32
		pOcspClient->Release();
		CoUninitialize();
#endif
		pOcspClient = NULL;
	}
#endif

#ifdef WIN32
	//////////free show select cert obj
   if (CertificateCount)
	   delete dlg;
   if (RecipientCertCount)
       delete dlgRecipient;
#endif

	if (CertVerifyParams.altCrlCount != 0)
	{
		for (i=0; i < CertVerifyParams.altCrlCount; i++)
			zFree(CertVerifyParams.crlAltUrl[i]);
		zFree(CertVerifyParams.crlAltUrl);
	}
	if ((CertVerifyParams.trustRootCertCount != 0) &&
		(CertVerifyParams.trustRootCerts != NULL))
	{
		for (i=0; i < CertVerifyParams.trustRootCertCount; i++)
			if (CertVerifyParams.trustRootCerts[i] != NULL)
				zFree(CertVerifyParams.trustRootCerts[i]);
		zFree(CertVerifyParams.trustRootCerts);
	}
	if ((CertVerifyParams.userPolicyCount != 0) && (CertVerifyParams.userPolicySet != NULL))
	{
		for (i=0; i < CertVerifyParams.userPolicyCount; i++)
		{
			if (CertVerifyParams.userPolicySet[i] != NULL)
				zFree(CertVerifyParams.userPolicySet[i]);
		}
		zFree(CertVerifyParams.userPolicySet);
		CertVerifyParams.userPolicyCount = 0;
		CertVerifyParams.userPolicySet = NULL;
	}
	if ((CertVerifyParams.userPolicySetCountOut != 0) && 
		(CertVerifyParams.userPolicySetOut != NULL))
	{
		for (i=0; i < CertVerifyParams.userPolicySetCountOut; i++)
		{
			if (CertVerifyParams.userPolicySetOut[i] != NULL)
				zFree(CertVerifyParams.userPolicySetOut[i]);
		}
		zFree(CertVerifyParams.userPolicySetOut);
		CertVerifyParams.userPolicySetCountOut = 0;
		CertVerifyParams.userPolicySetOut = NULL;
	}

	if ((CertVerifyParams.authPolicySetCountOut != 0) && 
		(CertVerifyParams.authPolicySetOut != NULL))
	{
		for (i=0; i < CertVerifyParams.authPolicySetCountOut; i++)
		{
			if (CertVerifyParams.authPolicySetOut[i] != NULL)
				zFree(CertVerifyParams.authPolicySetOut[i]);
		}
		zFree(CertVerifyParams.authPolicySetOut);
		CertVerifyParams.authPolicySetCountOut = 0;
		CertVerifyParams.authPolicySetOut = NULL;
	}
	if ((CertVerifyParams.usedCrlCount != 0) &&
		(CertVerifyParams.usedCrlList != NULL))
	{
		for (i=0; i < CertVerifyParams.usedCrlCount; i++)
		{
			if (CertVerifyParams.usedCrlList[i] != NULL)
			{
				zFree(CertVerifyParams.usedCrlList[i]);
				CertVerifyParams.usedCrlList[i] = NULL;
			}
		}
		zFree(CertVerifyParams.usedCrlList);
		CertVerifyParams.usedCrlList = NULL;
		CertVerifyParams.usedCrlCount = 0;
	}

	if ((RecipientCertificateCount != 0) && 
		(RecipientCertificateList != NULL))
	{
		for (i=0; i < RecipientCertificateCount; i++)
		{
			if (RecipientCertificateList[i] != NULL)
				zFree(RecipientCertificateList[i]);
		}
		zFree(RecipientCertificateList);
		RecipientCertificateCount = 0;
		RecipientCertificateList = NULL;
	}

	if ((allowedCertIssuerCount != 0) && 
		(allowedCertIssuerNames != NULL))
	{
		for (i=0; i < allowedCertIssuerCount; i++)
		{
			if (allowedCertIssuerNames[i] != NULL)
				SysFreeString(allowedCertIssuerNames[i]);
		}
		zFree(allowedCertIssuerNames);
		allowedCertIssuerCount = 0;
		allowedCertIssuerNames = NULL;
	}

	if ((DetachedObjectCount != 0) && 
		(DetachedObjectList != NULL))
	{
		for (i=0; i < DetachedObjectCount; i++)
		{
			if (DetachedObjectList[i] != NULL)
				zFree(DetachedObjectList[i]);
		}
		zFree(DetachedObjectList);
		DetachedObjectCount = 0;
		DetachedObjectList = NULL;
	}
	if ((AttachedObjectCount != 0) && 
		(AttachedObjectList != NULL))
	{
		for (i=0; i < AttachedObjectCount; i++)
		{
			if (AttachedObjectList[i] != NULL)
//				zFree(AttachedObjectList[i]);
				SysFreeString(AttachedObjectList[i]);
		}
		zFree(AttachedObjectList);
		AttachedObjectCount = 0;
		AttachedObjectList = NULL;
	}
	if ((SignedObjectIdCount != 0) && 
		(SignedObjectIdList != NULL))
	{
		for (i=0; i < SignedObjectIdCount; i++)
		{
			if (SignedObjectIdList[i] != NULL)
				SysFreeString(SignedObjectIdList[i]);
		}
		zFree(SignedObjectIdList);
		SignedObjectIdCount = 0;
		SignedObjectIdList = NULL;
	}
	if ((XpathNamespaceCount != 0) && 
		(XpathNamespaceList != NULL))
	{
		for (i=0; i < XpathNamespaceCount; i++)
		{
			if (XpathNamespaceList[i] != NULL)
				zFree(XpathNamespaceList[i]);
		}
		zFree(XpathNamespaceList);
		XpathNamespaceCount = 0;
		XpathNamespaceList = NULL;
	}
	if (pCamClient != NULL)
	{
		delete pCamClient;
		pCamClient = NULL;
	}
	if (camServerHost != NULL)
		zFree(camServerHost);
	camServerHost = NULL;
	if (CamResponseCaSignedMsg != NULL)
		zFree(CamResponseCaSignedMsg);
	if (CamResponseAsciiCert != NULL)
		zFree(CamResponseAsciiCert);
	if (PfxCertInfo != NULL)
		zFree(PfxCertInfo);
	if (SigHandle != NULL)
	{
		axFree(SigHandle);
		SigHandle = NULL;
	}
	if (InclusiveNamespaceList != NULL)
		zFree(InclusiveNamespaceList);

	ExitObjectLog;
}

void CSignature::FreeUriArr()
{
	EnterObjectLog;
	if (uriArr == NULL)
		return;
	for (int i=0; i<totalUriCount; i++)
	{
		if (uriArr[i]->sigId != NULL)
		{
			zFree(uriArr[i]->sigId);
			uriArr[i]->sigId=NULL;
		}
		if (uriArr[i]->URI != NULL)
		{
			zFree(uriArr[i]->URI);
			uriArr[i]->URI = NULL;
		}
		if (uriArr[i]->fullPath != NULL)
		{
			zFree(uriArr[i]->fullPath);
			uriArr[i]->fullPath = NULL;
		}
		zFree(uriArr[i]);
		uriArr[i] = NULL;
	}
	zFree(uriArr);
	uriArr=NULL;
	if (failedUriArr != NULL)
		zFree(failedUriArr);
	failedUriArr = NULL;
	totalUriCount = 0;
	failedUriCount = 0;
	ExitObjectLog;
}


#ifdef WIN32
#ifndef JNIBINDING
ULONG CSignature::AddRef()
{
	count++;
	return TRUE;
}

ULONG CSignature::Release()
{
	count--;
/*
	if (count == 0)
	{
		for (int i=0; i<CertificateCount; i++)
		{
			zFree(cV[i]);
		}
		zFree(cV);
		cV = NULL;
	}
*/
	if (count == 0)
		delete this;
  return TRUE;
}
#endif
#endif

STDMETHODIMP CSignature::get_EnvelopingFlag(short *pVal)
{
	HRESULT hResult=S_OK;
	EnterObjectLog;

	*pVal = EnvelopingFlag;
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::put_EnvelopingFlag(short newVal)
{
	HRESULT hResult=S_OK;

	EnterObjectLog;
	EnvelopingFlag = newVal;
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::get_RecipientCertificateStore(BSTR *pVal)
{
	HRESULT hResult=S_OK;

	EnterObjectLog;
	*pVal = RecipientCertificateStore.Copy();
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::put_RecipientCertificateStore(BSTR newVal)
{
	int numCerts;
	UINT i;
	PCERT_DESCR *certPtr;
	HRESULT hResult=S_OK;
	unsigned char *tmpCharPtr;

	EnterObjectLog;

USES_CONVERSION;

	RecipientCertificateStore.Empty();
	RecipientCertificateStore = newVal;
	if (RecipientCertificateStore.Length() == 0)
		RecipientCertificateStore = A2WBSTR((LPCSTR)"addressbook");

	if (cVRecipient != NULL)
	{
		for (i=0; i<(UINT)RecipientCertCount; i++)
		{
			if (cVRecipient[i]->certificate)
				zFree(cVRecipient[i]->certificate);
			zFree(cVRecipient[i]);
		}
		zFree(cVRecipient);
		cVRecipient = NULL;
	}

	tmpCharPtr = HeapW2A(RecipientCertificateStore.m_str);
	if ((certPtr = axGetRecipientCertificateList(tmpCharPtr, &numCerts )) != NULL)
	{
		RecipientCertCount = (long) numCerts;
		if (numCerts > 0)
			cVRecipient = certPtr;
		else
		{
			cVRecipient = NULL;
		}
	}

#ifdef WIN32
	if (RecipientCertCount)
	{
		delete dlgRecipient;
		dlgRecipient = new CShowSelectCert(/*this,*/ tmpCharPtr, cVRecipient, RecipientCertCount);
//		dlgRecipient->Create(NULL);
	}
#endif
	zFree(tmpCharPtr);
	ExitObjectLog;

	return hResult;
}

STDMETHODIMP CSignature::get_SignerCertificate(long index, BSTR *pVal)
{
	HRESULT hResult=S_OK;

	*pVal = NULL;
	
	EnterObjectLog;
	
	if (sgArr==NULL)
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	if ((index >= signum) || (index < 0))
	{
		setError(SigHandle, SIG_INDEX_ERROR);
		return S_FALSE;
	}

USES_CONVERSION;
	*pVal = A2WBSTR((LPCSTR)sgArr[index]->signerCert->certificate);
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::put_SignerCertificate(long index, BSTR newVal)
{
	HRESULT hResult=S_OK;
	EnterObjectLog;

	SignerCertificate = newVal;

	if (SignerCertificate.Length() != 0)
	{
		CurrentCertificate = USE_BASE64_CERT;
	}
	else
	{
		CurrentCertificate = NOT_INITIALIZED;
	}
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::get_SignatureID(long index, BSTR *pVal)
{
	HRESULT hResult=S_OK;
	EnterObjectLog;

	*pVal = NULL;

	if (sgArr==NULL)
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	if ((index >= signum) || (index < 0))
	{
		setError(SigHandle, SIG_INDEX_ERROR);
		return S_FALSE;
	}

USES_CONVERSION;
	*pVal = A2WBSTR((LPCSTR)sgArr[index]->sigId);
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::put_SignatureID(long index, BSTR newVal)
{
	HRESULT hResult=S_OK;
	EnterObjectLog;

	SignatureID = newVal;
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::get_Properties(long sigIndex, long propIndex, BSTR *pVal)
{
	*pVal = NULL;

	EnterObjectLog;
	if (sgArr==NULL)
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	if ((sigIndex >= signum) || (sigIndex < 0))
	{
		setError(SigHandle, SIG_INDEX_ERROR);
		return S_FALSE;
	}
	if (propIndex >= sgArr[sigIndex]->propNumber)
	{
		setError(SigHandle, PROP_INDEX_ERROR);
		return S_FALSE;
	}
	unsigned char *utf16CharStr=NULL;
	int utf16ByteLen=0, utf8ByteLen=0;
	utf8ByteLen = strlen((const char *)sgArr[sigIndex]->propArray[propIndex]);
	utf16ByteLen = utf8ByteLen * 2;
	utf16CharStr = (unsigned char *)zMalloc(utf16ByteLen);
	UTF8ToUTF16LE(utf16CharStr, &utf16ByteLen, (const unsigned char*)sgArr[sigIndex]->propArray[propIndex], &utf8ByteLen);
	*pVal = SysAllocStringByteLen((LPCSTR)utf16CharStr, utf16ByteLen);
	zFree(utf16CharStr);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_Properties(long sigIndex, long propIndex, BSTR newVal)
{

	EnterObjectLog;

	if (propIndex < MAX_PROP_COUNT)
	{
		if (Properties[propIndex] != NULL)
		{
			zFree(Properties[propIndex]);
			Properties[propIndex] = NULL;
		}
			
		Properties[propIndex] = HeapW2A(newVal);
		PropertyCount = propIndex+1;
	}
	else
	{
		setError(SigHandle, PROP_INDEX_ERROR);
		return S_FALSE;
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_IncludeCamResponse(/*[out, retval]*/ BOOL *pVal)
{
	EnterObjectLog;
	*pVal = IncludeCamResponse;
	ExitObjectLog;
	return S_OK;
}
STDMETHODIMP CSignature::put_IncludeCamResponse(/*[in]*/ BOOL newVal)
{
	EnterObjectLog;
	IncludeCamResponse = newVal;
	ExitObjectLog;
	return S_OK;
}


STDMETHODIMP CSignature::get_Base64EncodeXML(/*[out, retval]*/ BOOL *pVal)
{
	EnterObjectLog;
	*pVal = Base64EncodeXML;
	ExitObjectLog;
	return S_OK;
}
STDMETHODIMP CSignature::put_Base64EncodeXML(/*[in]*/ BOOL newVal)
{
	EnterObjectLog;
	Base64EncodeXML = newVal;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_Base64DecodeXML(/*[out, retval]*/ BOOL *pVal)
{
	EnterObjectLog;
	*pVal = Base64DecodeXML;
	ExitObjectLog;
	return S_OK;
}
STDMETHODIMP CSignature::put_Base64DecodeXML(/*[in]*/ BOOL newVal)
{
	EnterObjectLog;
	Base64DecodeXML = newVal;
	ExitObjectLog;
	return S_OK;
}


STDMETHODIMP CSignature::get_DocumentURI(long sigIndex, long uriIndex, BSTR *pVal)
{
	HRESULT hResult=S_OK;
	int maxUri=0;

	EnterObjectLog;

	*pVal = NULL;

	if (sgArr==NULL)
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	if ((sigIndex >= signum) || (sigIndex < 0))
	{
		setError(SigHandle, SIG_INDEX_ERROR);
		return S_FALSE;
	}

	maxUri = sgArr[sigIndex]->refNumber;
	
	if ((uriIndex >= maxUri) || (uriIndex < 0))
	{
		setError(SigHandle, URI_INDEX_ERROR);
		return S_FALSE;
	}

USES_CONVERSION;
	unsigned char *utf16CharStr=NULL;
	int utf16ByteLen=0, utf8ByteLen=0;
	utf8ByteLen = strlen((const char *)sgArr[sigIndex]->refArray[uriIndex]->URI);
	utf16ByteLen = utf8ByteLen * 2;
	utf16CharStr = (unsigned char *)zMalloc(utf16ByteLen);
	UTF8ToUTF16LE(utf16CharStr, &utf16ByteLen, (const unsigned char*)sgArr[sigIndex]->refArray[uriIndex]->URI, &utf8ByteLen);
	*pVal = SysAllocStringByteLen((LPCSTR)utf16CharStr, utf16ByteLen);
	zFree(utf16CharStr);

//	*pVal = A2WBSTR((LPCSTR)sgArr[sigIndex]->refArray[uriIndex]->URI);
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::get_DigestObjectStatus(long sigIndex, long uriIndex, BOOL *pVal)
{
	HRESULT hResult=S_OK;
	int maxUri=0;

	EnterObjectLog;

	*pVal = FALSE;

	if (sgArr==NULL)
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	if ((sigIndex >= signum) || (sigIndex < 0))
	{
		setError(SigHandle, SIG_INDEX_ERROR);
		return S_FALSE;
	}

	maxUri = sgArr[sigIndex]->refNumber;

	if ((uriIndex >= maxUri) || (uriIndex < 0))
	{
		setError(SigHandle, URI_INDEX_ERROR);
		return S_FALSE;
	}

	*pVal = sgArr[sigIndex]->refArray[uriIndex]->status;
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::get_Language(BSTR *pVal)
{
	HRESULT hResult=S_OK;
	*pVal = Language.Copy();
	return hResult;
}

STDMETHODIMP CSignature::put_Language(BSTR newVal)
{
	HRESULT hResult=S_OK;
	HINSTANCE	hInstLocal= NULL;
	LCID		lcid= NULL;
	const char *FILE_SEP_STR = "\\";

#ifdef WIN32
	unsigned char *charSecureXMLPath = HeapW2A(SecureXMLPath.m_str);
	string dllPath = (char *)charSecureXMLPath;
	zFree(charSecureXMLPath);

	Language = newVal;
	if (Language.Length() != 0)
	{
		unsigned char *charLang = HeapW2A(newVal);
		string lang = (char *)charLang;
		zFree(charLang);
		if (lang == "FR")
		{
			/* Lets try to load the English dialog resource file */
			if(!m_hInstFrench)
				m_hInstFrench = LoadLibraryW(_bstr_t(FRENCH_RESOURCE_DLL));
			if (m_hInstFrench == NULL)
			{
				if (dllPath.length() != 0)
					m_hInstFrench = LoadLibraryW(_bstr_t((dllPath + FILE_SEP_STR + FRENCH_RESOURCE_DLL).c_str()));
			}
			hInstLocal = m_hInstFrench;
			if (hInstLocal != NULL)
			{
				_Module.SetResourceInstance(hInstLocal);
				if (dlg != NULL)
				{
					delete dlg;
					dlg = NULL;
				}
				unsigned char *tmpCharPtr = HeapW2A(StoreName.m_str);
				if (CertificateCount)
				{
					dlg = new CShowSelectCert(/*this,*/ tmpCharPtr, cV,  CertificateCount);
				}
				zFree(tmpCharPtr);
			}
		}
		else if (lang == "JP")
			{
				if(!m_hInstJapanese)
					m_hInstJapanese = LoadLibraryW(_bstr_t(JAPANESE_RESOURCE_DLL));
				if (m_hInstJapanese == NULL)
				{
					if (dllPath.length() != 0)
						m_hInstJapanese = LoadLibraryW(_bstr_t((dllPath + FILE_SEP_STR + JAPANESE_RESOURCE_DLL).c_str()));
				}
				hInstLocal = m_hInstJapanese;
				if (hInstLocal != NULL)
				{
					_Module.SetResourceInstance(hInstLocal);
					if (dlg != NULL)
					{
						delete dlg;
						dlg = NULL;
					}
					unsigned char *tmpCharPtr = HeapW2A(StoreName.m_str);
					if (CertificateCount)
					{
						dlg = new CShowSelectCert(/*this,*/ tmpCharPtr, cV,  CertificateCount);
					}
					zFree(tmpCharPtr);
				}
			}
		else if (lang == "HU")
			{
				if(!m_hInstHungarian)
					m_hInstHungarian = LoadLibraryW(_bstr_t(HUNGARIAN_RESOURCE_DLL));
				if (m_hInstHungarian == NULL)
				{
					if (dllPath.length() != 0)
						m_hInstHungarian = LoadLibraryW(_bstr_t((dllPath + FILE_SEP_STR + HUNGARIAN_RESOURCE_DLL).c_str()));
				}
				hInstLocal = m_hInstHungarian;
				if (hInstLocal != NULL)
				{
					_Module.SetResourceInstance(hInstLocal);
					if (dlg != NULL)
					{
						delete dlg;
						dlg = NULL;
					}
					unsigned char *tmpCharPtr = HeapW2A(StoreName.m_str);
					if (CertificateCount)
					{
						dlg = new CShowSelectCert(/*this,*/ tmpCharPtr, cV,  CertificateCount);
					}
					zFree(tmpCharPtr);
				}
			}
		else if (lang == "ES")
			{
				if(!m_hInstSpanish)
					m_hInstSpanish = LoadLibraryW(_bstr_t(SPANISH_RESOURCE_DLL));
				if (m_hInstSpanish == NULL)
				{
					if (dllPath.length() != 0)
						m_hInstSpanish = LoadLibraryW(_bstr_t((dllPath + FILE_SEP_STR + SPANISH_RESOURCE_DLL).c_str()));
				}
				hInstLocal = m_hInstSpanish;
				if (hInstLocal != NULL)
				{
					_Module.SetResourceInstance(hInstLocal);
					if (dlg != NULL)
					{
						delete dlg;
						dlg = NULL;
					}
					unsigned char *tmpCharPtr = HeapW2A(StoreName.m_str);
					if (CertificateCount)
					{
						dlg = new CShowSelectCert(/*this,*/ tmpCharPtr, cV,  CertificateCount);
					}
					zFree(tmpCharPtr);
				}
			}
		else if (lang == "DE")
			{
				if(!m_hInstGerman)
					m_hInstGerman = LoadLibraryW(_bstr_t(GERMAN_RESOURCE_DLL));
				if (m_hInstGerman == NULL)
				{
					if (dllPath.length() != 0)
						m_hInstGerman = LoadLibraryW(_bstr_t((dllPath + FILE_SEP_STR + GERMAN_RESOURCE_DLL).c_str()));
				}
				hInstLocal = m_hInstGerman;
				if (hInstLocal != NULL)
				{
					_Module.SetResourceInstance(hInstLocal);
					if (dlg != NULL)
					{
						delete dlg;
						dlg = NULL;
					}
					unsigned char *tmpCharPtr = HeapW2A(StoreName.m_str);
					if (CertificateCount)
					{
						dlg = new CShowSelectCert(/*this,*/ tmpCharPtr, cV,  CertificateCount);
					}
					zFree(tmpCharPtr);
				}
			}
		else if (lang == "PT")
			{
				if(!m_hInstPortuguese)
					m_hInstPortuguese = LoadLibraryW(_bstr_t(PORTUGUESE_RESOURCE_DLL));
				if (m_hInstPortuguese == NULL)
				{
					if (dllPath.length() != 0)
						m_hInstPortuguese = LoadLibraryW(_bstr_t((dllPath + FILE_SEP_STR + PORTUGUESE_RESOURCE_DLL).c_str()));
				}
				hInstLocal = m_hInstPortuguese;
				if (hInstLocal != NULL)
				{
					_Module.SetResourceInstance(hInstLocal);
					if (dlg != NULL)
					{
						delete dlg;
						dlg = NULL;
					}
					unsigned char *tmpCharPtr = HeapW2A(StoreName.m_str);
					if (CertificateCount)
					{
						dlg = new CShowSelectCert(/*this,*/ tmpCharPtr, cV,  CertificateCount);
					}
					zFree(tmpCharPtr);
				}
			}
		else
			{
				if (m_hInstEnglish != NULL)
				{
					_Module.SetResourceInstance(m_hInstEnglish);
					if (dlg != NULL)
					{
						delete dlg;
						dlg = NULL;
					}
					unsigned char *tmpCharPtr = HeapW2A(StoreName.m_str);
					if (CertificateCount)
					{
						dlg = new CShowSelectCert(/*this,*/ tmpCharPtr, cV,  CertificateCount);
					}
					zFree(tmpCharPtr);
				}
			}
	}
#endif
	return hResult;
}

STDMETHODIMP CSignature::get_SignatureStatus(long sigIndex, BOOL *pVal)
{
	HRESULT hResult=S_OK;
	*pVal = FALSE;
	EnterObjectLog;

	USES_CONVERSION;

	if (sgArr==NULL)
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	if ((sigIndex >= signum) || (sigIndex < 0))
	{
		setError(SigHandle, SIG_INDEX_ERROR);
		return S_FALSE;
	}

	*pVal = sgArr[sigIndex]->status;
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::get_PhysicalSignatureUsage(long *pVal)
{
	HRESULT hResult=S_OK;
	EnterObjectLog;
	*pVal = PhysicalSigUsage;
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::put_PhysicalSignatureUsage(long newVal)
{
	HRESULT hResult=S_OK;
	HWND	desktopHwnd;
	EnterObjectLog;
	PhysicalSigUsage = newVal;
	

	if (newVal != NO_PHYSICAL_SIG)
	{
#ifdef WIN32	
		desktopHwnd = GetDesktopWindow();	
		GetClientRect(desktopHwnd, &SignatureCaptureWindowDim);		
		SignatureCaptureWindowDim.left = (SignatureCaptureWindowDim.right / 2) - 175; // UpperX		
		SignatureCaptureWindowDim.top = (SignatureCaptureWindowDim.bottom / 2) - 125; // UpperY		
		SignatureCaptureWindowDim.bottom = 250; // Height
		SignatureCaptureWindowDim.right = 350;  // Width
#endif
	}
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::get_PhysicalSignatureFile(BSTR *pVal)
{
	HRESULT hResult=S_OK;
	int		filePathSize;
	EnterObjectLog;
	USES_CONVERSION;

	filePathSize = strlen((const char *)PhysicalSignatureFileName);

	if (filePathSize != 0)
		*pVal = A2WBSTR((LPCSTR)PhysicalSignatureFileName);
	else
		setError(SigHandle, FILE_PATH_NOT_SET);

	ExitObjectLog;

	return hResult;
}

STDMETHODIMP CSignature::put_PhysicalSignatureFile(BSTR newVal)
{
	HRESULT hResult=S_OK;
	EnterObjectLog;
	char *charNewVal;
	int		filePathSize;
	CComBSTR ccBstrNewVal;

	USES_CONVERSION;

	ccBstrNewVal = newVal;

	if (ccBstrNewVal.Length() == 0)
	{
		setError(SigHandle, FILE_NOT_FOUND);
		return S_FALSE;
	}

	charNewVal = (char *)HeapW2A(newVal);
	filePathSize = strlen(charNewVal);

	if (filePathSize < MAX_PATH)
	{
		strcpy((char *) PhysicalSignatureFileName, charNewVal);
		//Image image(newVal);
		//SignatureCaptureWindowDim.bottom = image.GetHeight(); // Height
		//SignatureCaptureWindowDim.right = image.GetWidth();  // Width
	}
	else
		setError(SigHandle, FILE_PATH_TOO_LONG);
	
	zFree(charNewVal);
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::get_CapturedSignatureFile(BSTR *pVal)
{
	HRESULT hResult=S_OK;
	int		filePathSize;
	EnterObjectLog;
USES_CONVERSION;

	filePathSize = strlen((const char *)CapturedSignatureFileName);

	if (filePathSize != 0)
		*pVal = A2WBSTR((LPCSTR)CapturedSignatureFileName);
	else
		setError(SigHandle, FILE_PATH_NOT_SET);
	ExitObjectLog;
	return hResult;
}
/**
 * xsRemoveBstrPath
 * @fileName: (in) path
 *
 * Removes absolute elements from path
 *
 * Returns: file name in utf-8 format
 */
unsigned char * CSignature::xsRemoveBstrPath(BSTR fileName) 
{
	char *porg;
	wchar_t *p, *wporg;
	int bareFileNameLen = 0;
	int utf8CharStrLen = 0;
	unsigned char *utf8CharStr = NULL;
	unsigned int bstrByteSize = SysStringByteLen(fileName);
	unsigned char *tmpBuf = (unsigned char *)zMalloc(bstrByteSize+2);

	USES_CONVERSION;

	memcpy(tmpBuf, fileName, bstrByteSize+2);

	porg = (char *)HeapW2A(fileName);

	//porg = (char *)fileName;
	if (((strnicmp(porg,"http://",7))==0) || ((strnicmp(porg,"ldap://",7))==0))
	{
		bareFileNameLen = bstrByteSize;
		utf8CharStrLen = bareFileNameLen * 2;
		utf8CharStr = (unsigned char *) zMalloc(utf8CharStrLen);
		memset(utf8CharStr, 0, utf8CharStrLen);
		UTF16LEToUTF8(utf8CharStr, &utf8CharStrLen, (const unsigned char *)tmpBuf, &bareFileNameLen);
		zFree(tmpBuf);
		zFree(porg);
		return utf8CharStr;
	}

	wporg = (wchar_t *)tmpBuf;
	if ((p = wcsrchr (wporg,L'\\')) != NULL) {
		wporg = ++p;
	}

	if ((p = wcsrchr(wporg,L'/')) != NULL) {
		wporg = ++p;
	}

	bareFileNameLen = bstrByteSize + 2 - ((char *)wporg - (char *)tmpBuf);
	utf8CharStrLen = bareFileNameLen +10;
	utf8CharStr = (unsigned char *) zMalloc(utf8CharStrLen);
	memset(utf8CharStr, 0, utf8CharStrLen);
	UTF16LEToUTF8(utf8CharStr, &utf8CharStrLen, (const unsigned char *)wporg, &bareFileNameLen);
	zFree(tmpBuf);
	zFree(porg);

	return utf8CharStr;
}

STDMETHODIMP CSignature::Sign(BSTR URI, BSTR *tempFileName)
{
	HRESULT hResult=S_OK;
	unsigned char *byteArraySig;
	BSTR fileDataStr;
	BSTR signedXMLStr;
	DWORD  dwBytesToWrite;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	char *charSigId=NULL;
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL, parent=NULL, sigNode=NULL, signedInfoNode=NULL;
	char pout[256], pout2[256];
	BYTE *pbDocument;		// Object BLOB to sign
	DWORD cbDocument=0;
	BYTE *pbData=NULL;
	DWORD cbData=0;
	BOOL freeCharSigId = FALSE;

	EnterObjectLog;

	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (!LicObj.getSignAllowed()) {
		setError(SigHandle, NO_SIGNING_LIC);
		return S_FALSE;
	}

	USES_CONVERSION;

	DocumentURI = URI;

	if (DocumentURI.Length() == 0)
	{
		setError(SigHandle, FILE_NOT_FOUND);
		return S_FALSE;
	}

	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

  if (EnvelopingFlag != ENVELOPED) // Creating enveloping or detached signature
  {
	/*
	* Signature
	*/

	if (SignatureID.Length() == 0)
	{
#ifdef WIN32
		CoCreateGuid(&sigGuid);
		GuidToString(&sigGuid, guidStr);
#else
		uuid_generate(sigGuid);
		uuid_unparse(sigGuid, guidStr);
#endif
		charSigId = guidStr;
	}
	else
	{
		charSigId = (char *)HeapW2A(SignatureID.m_str);
		freeCharSigId = TRUE;
	}

	doc = xmlNewDoc((const unsigned char *)"1.0");
	// document, namespace, element name, element content
	cur = xmlNewDocNode(doc,NULL,(const unsigned char *)"Signature",NULL);
	xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
	sigNode = cur;
	xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
	// add root element
	xmlDocSetRootElement(doc,cur);
	parent = cur;

	/*
	* SignedInfo
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
	signedInfoNode = cur;
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	* Canonicalization Method
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
	switch(CanonicalizationMethod)
	{
		case WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
			break;
		case WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
			break;
		case EXC_WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			break;
		case EXC_WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			break;
		default:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
	}

	cur = xmlAddChild(parent,cur);
	/*
	* Reference
	*/
	if (EnvelopingFlag == ENVELOPING)
	{
		//DebugBreak();
		cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
		sprintf (pout,"REF_Enveloping_%s",charSigId);
		if ((SignedObjectIdCount != 0) && (SignedObjectIdCount > AttachedObjectCount) && (SignedObjectIdList[AttachedObjectCount] != NULL))
		{
			unsigned char *objectId = HeapW2A(SignedObjectIdList[AttachedObjectCount]);
			strcpy(&pout2[1], (const char *)objectId);
			zFree(objectId);
			pout2[0] = '#';
		}
		else
		{
            sprintf (pout2,"#OBJECT_%s",charSigId);
		}
		xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)pout);
		xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)pout2);
		cur = xmlAddChild(parent,cur);
/***
 ***	<ds:Transform Algorithm="http://www.w3.org/2001/10/xml-exc-c14n#">
			<ec:InclusiveNamespaces PrefixList="dsig soap #default"
				xmlns:ec="http://www.w3.org/2001/10/xml-exc-c14n#"/>
		</ds:Transform>
*/
		parent = cur;

		if ((CanonicalizationMethod == EXC_WITH_COMMENTS) ||
			(CanonicalizationMethod == EXC_WITHOUT_COMMENTS))
		{
			/*
			* Transforms
			*/
			cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
			cur = xmlAddChild(parent,cur);
			parent = cur;

			/*
			* Transform
			*/
			cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			}
			cur = xmlAddChild(parent,cur);
			parent = cur;
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_WITH_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_NO_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			cur = xmlAddChild(parent,cur);		
		}

		//read file/web page
		if ((pbDocument = xsDereferenceBstrURI(
			DocumentURI.m_str,					// file name or URI
			&cbDocument))==NULL) {		// (in/out) size of data
				setError(SigHandle, DEREF_URI_ERROR);
				if (freeCharSigId)
					zFree(charSigId);
				return S_FALSE;
			}

		cur = xmlNewNode(NULL,(const unsigned char *)"Object");
		//sprintf (pout,"OBJECT_%s",charSigId);
		xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)&pout2[1]);

		xmlDocPtr pxdoc=NULL;
		pxdoc = xmlParseMemory((const char *)pbDocument,cbDocument);
		if (pxdoc == NULL) {
			// no xml content
			// Base64 encode the data since we don't know what it is
			cbData = base64encodeSize(cbDocument);
			// allocate memory
			if(!(pbData = (BYTE*)zMalloc(cbData+1)))
				{
				setError(SigHandle, MEMORY_FAULT);
				if (freeCharSigId)
					zFree(charSigId);
				return S_FALSE;
			}
			if (base64encode(pbDocument,cbDocument,(unsigned char*)pbData,cbData)==-1) {
				setError(SigHandle, BASE64_ERROR);
				if (freeCharSigId)
					zFree(charSigId);
				return S_FALSE;
			}
			*(pbData+cbData)='\0';
			xmlNewProp(cur, (const unsigned char *)"Encoding", (const unsigned char *)ALG_BASE64);
			xmlNodeSetContent(cur,(const unsigned char *)pbData);	
			zFree(pbData);
			zFree(pbDocument);
			pbData = NULL;
			pbDocument = NULL;
		}else{
			// render internal 
			xmlNodePtr nCur = NULL;
		    xmlNodePtr intCur = NULL;
			intCur = xmlDocGetRootElement(pxdoc);
			nCur = xmlCopyNode(intCur,1);
			xmlAddChild(cur,nCur);
			xmlFreeDoc(pxdoc);
			zFree(pbDocument);
			pbDocument = NULL;
		}
		cur = xmlAddChild(sigNode,cur);
		parent = cur;

		//cur = xmlNewNode(NULL,(const unsigned char *)"SignatureProperties"); 
		//cur = xmlAddChild(parent,cur);
		//parent = cur;

		//cur = xmlNewNode(NULL,(const unsigned char *)"SignatureProperty"); 
		//xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)"URI");
		//xmlNewProp(cur, (const unsigned char *)"Target", (const unsigned char *)charSigId);
		//unsigned char *bareFileName = xsRemoveBstrPath(DocumentURI.m_str);
		//xmlNodeSetContent(cur,(const unsigned char *)bareFileName);
		//cur = xmlAddChild(parent,cur);
		//zFree(bareFileName);
	} // ENVELOPING

#ifdef WIN32
	if (AddWindowImageFlag == TRUE)
		AddWindowImage(sigNode, signedInfoNode, charSigId);

	if (PhysicalSigUsage != NO_PHYSICAL_SIG)		  
		AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif

	//xmlDocDumpMemory(doc,&crBlob.pbData,(int *)&crBlob.cbData);
	//xmlFreeDoc(doc);

	/*
	 * init Signature. crBlob contains XML - envelope document
	 */

	if (!(CreateSigFromTmplBlob(
								//&crBlob,
								doc,
								charSigId, &byteArraySig, (int *)&dwBytesToWrite)))
	{
		//zFree(crBlob.pbData);
		if (byteArraySig != NULL)
		{
			xmlFree(byteArraySig);
		}
		*tempFileName = A2WBSTR((const char *) NULL);
		if (freeCharSigId)
			zFree(charSigId);
		return S_FALSE;
	}
	else
	{
		if (byteArraySig != NULL)
		{
			signedXMLStr = A2WBSTR((LPCSTR)byteArraySig, (int)dwBytesToWrite);
			if (Base64EncodeXML == TRUE)
				zFree(byteArraySig);
			else
				xmlFree(byteArraySig);
		}
	}
  }
  else
  {
	if ((pbDocument = xsDereferenceBstrURI(
		DocumentURI.m_str,					// file name or URI
		&cbDocument))==NULL) 
	{		// (in/out) size of data
		setError(SigHandle, DEREF_URI_ERROR);
		if (freeCharSigId)
			zFree(charSigId);
		return S_FALSE;
	}

	unsigned char *dataPtr = pbDocument;
	if (((*dataPtr == 0xff) && (*(dataPtr +1) == 0xfe)) || // Little Endian
		((*dataPtr == 0xfe) && (*(dataPtr +1) == 0xff))) // Big Endian
	{
		// This is a UTF-16 file, so no need to do a char * to BSTR conversion
		// Just allocate memory and copy data and put the size information in front
		fileDataStr = ::SysAllocStringByteLen((LPCSTR)dataPtr, (UINT)cbDocument);
	}
	else
	{
		fileDataStr = A2WBSTR((LPCSTR)dataPtr, cbDocument);
	}
	zFree(pbDocument);
	  
	if (SignXMLStr(fileDataStr, SignatureID.m_str, &signedXMLStr) != S_OK)
	{
		SysFreeString(fileDataStr);
		*tempFileName = A2WBSTR((const char *) NULL);
		return S_FALSE;
	}
	SysFreeString(fileDataStr);
  }
	BSTR savedFileName=NULL;
	SaveXMLStr(signedXMLStr, NULL, &savedFileName);
	char *wSavedFileName = (char *)HeapW2A(savedFileName);
	strcpy(szTempName, wSavedFileName);
	zFree(wSavedFileName);
	SysFreeString(signedXMLStr);
	*tempFileName = A2WBSTR(szTempName);
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::SaveXMLSignature(BSTR sigFileName)
{

	HRESULT hResult=S_OK;
	CComBSTR ccBstrSigFileName;
	
	EnterObjectLog;

	ccBstrSigFileName = sigFileName;

	if (ccBstrSigFileName.Length() == 0)
	{
		setError(SigHandle, FILE_NOT_FOUND);
		return S_FALSE;
	}
	
	// Move the temporary file to the new text file.
 USES_CONVERSION;

	char *wSigFileName = (char *)HeapW2A(sigFileName);
#ifdef WIN32
	if (OverwriteFileFlag)
		DeleteFile(wSigFileName);

	if (!MoveFile(szTempName, wSigFileName)) 
	{
#else
	if (OverwriteFileFlag)
		unlink(wSigFileName);
	
	if (rename(szTempName, wSigFileName) != 0)
	{ 
#endif
		setError(SigHandle, IO_ERROR);
		zFree(wSigFileName);
		return S_FALSE;
	} 	
	zFree(wSigFileName);
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::Verify(BSTR signatureFileName, BOOL *sigStatus)
{

	HRESULT hResult=S_OK;
	BSTR inputXML;
	EnterObjectLog;
	*sigStatus = FALSE;
	hResult = ReadAll(signatureFileName, &inputXML);
	if (hResult != S_OK)
		return S_FALSE;
	if (uriArr != NULL)
	{
		SigHandle->locArray = uriArr;
		SigHandle->locNumber = totalUriCount;
	}
	hResult = VerifyXMLStr(inputXML, sigStatus);
	SysFreeString(inputXML);
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::VerifyDetached(BSTR signatureFileName, BOOL *sigStatus)
{
	HRESULT hResult=S_OK;
	EnterObjectLog;
	*sigStatus = 0;
	if (uriArr == NULL)
		return S_FALSE;

	SigHandle->locArray = uriArr;
	SigHandle->locNumber = totalUriCount;
	hResult = Verify(signatureFileName,sigStatus);
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::GetError(BSTR *errorString)
{
	HRESULT hResult=S_OK;
	EnterObjectLog;
	const char *err = (const char *) axGetError(SigHandle);

	if (err != NULL)
	{
		ErrorString = err;
		*errorString = ErrorString.Copy();
		zFree((void *)err);
	}
	else
		*errorString = NULL;
	ExitObjectLog;
	return hResult;
}


STDMETHODIMP CSignature::GetLastError(long *errorNum)
{
	EnterObjectLog;
	*errorNum = axGetLastError(SigHandle);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::GetX509Certificate(BSTR certID, BSTR *certData)
{
	CComBSTR tmpCertId;
	unsigned char *base64CertId;
	BOOL certificateFound = FALSE;
	EnterObjectLog;
	tmpCertId = certID;
	if (tmpCertId.Length() == 0)
	{
		setError(SigHandle, CERT_NOT_FOUND);
		DebugLog("tmpCertId.Length() == 0");
		return S_FALSE;
	}

USES_CONVERSION;
	if (CertSerialNumberFormat == CERT_SERIAL_PLAIN_HEX)
	{
		unsigned char *wCertID = HeapW2A(certID);
		base64CertId = PlainHexToBase64Bin(wCertID);
		zFree(wCertID);
	}
	else
		base64CertId = HeapW2A(certID);
	DebugLog((const char *)base64CertId);
	for (int i=0;i<CertificateCount;i++)
	{
		if (!(StrCmp((const char *)cV[i]->serialNumber, (const char *)base64CertId)))
		{
			*certData = A2WBSTR((LPCSTR) cV[i]->certificate);
			certificateFound = TRUE;
			break;
		}
	}
	if (base64CertId)
	{
		zFree(base64CertId);
		base64CertId = NULL;
	}
	if (certificateFound == FALSE)
	{
		setError(SigHandle, CERT_NOT_FOUND);
		return S_FALSE;
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::ViewCertificate(BSTR certID)
{
	CComBSTR tmpCertId;
	unsigned char *base64CertId;
	BOOL certificateFound = FALSE;

	USES_CONVERSION;
	EnterObjectLog;
	tmpCertId = certID;
	if (tmpCertId.Length() == 0)
	{
		setError(SigHandle, CERT_NOT_FOUND);
		return S_FALSE;
	}
	if (CertSerialNumberFormat == CERT_SERIAL_PLAIN_HEX)
	{
		unsigned char *wCertID = HeapW2A(certID);
		base64CertId = PlainHexToBase64Bin(wCertID);
		zFree(wCertID);
	}
	else
		base64CertId = HeapW2A(certID);

	for (int i=0;i<CertificateCount;i++)
	{
		if (!(StrCmp((const char *)cV[i]->serialNumber, (const char *)base64CertId)))
		{
			axViewAnyCertificate(cV[i]->certificate);
			certificateFound = TRUE;
			break;
		}
	}
	if (base64CertId)
	{
		zFree(base64CertId);
		base64CertId = NULL;
	}

	if (certificateFound == FALSE)
	{
		setError(SigHandle, CERT_NOT_FOUND);
		return S_FALSE;
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_CertificateCount(long *pVal)
{
	EnterObjectLog;
	*pVal = CertificateCount;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::GetCertificateInfo(long index, long valIndex, BSTR *value)
{
	BOOL providePfxCertInfo = FALSE;
	BOOL provideActiveCertInfo = FALSE;
	BOOL provideBase64CertInfo = FALSE;
	unsigned char *plainHexPtr=NULL;

	EnterObjectLog;

	//The following logic does not cover the case when CurrentCertificate == USE_BASE64_CERT
	//It will lead to a memory fault

	if ((CurrentCertificate == USE_PFX_CERT) &&
		(index == USE_PFX_CERT))
		providePfxCertInfo = TRUE;
	else
		if ((CurrentCertificate >= 0) && (index == ACTIVE_CERT_INFO))
			provideActiveCertInfo = TRUE;
		else
			if ((CurrentCertificate == USE_BASE64_CERT) && (index == ACTIVE_CERT_INFO))
				provideBase64CertInfo = TRUE;

	if ((providePfxCertInfo == FALSE) && 
		(provideActiveCertInfo == FALSE) && 
		((index < 0) || (index >= CertificateCount)))
	{
		setError(SigHandle, CERT_INDEX_ERROR);
		return S_FALSE;
	}
	else
	{
		switch (valIndex)
		{
			case 1:	if (providePfxCertInfo)
						if (CertSerialNumberFormat == CERT_SERIAL_PLAIN_HEX)
						{
							plainHexPtr = Base64BinToPlainHex(PfxCertInfo->serialNumber);
							*value = A2WBSTR((LPCSTR)plainHexPtr);
							zFree(plainHexPtr);
						}
						else
							*value = A2WBSTR((LPCSTR)PfxCertInfo->serialNumber);
					else 
						if (provideActiveCertInfo)
							if (CertSerialNumberFormat == CERT_SERIAL_PLAIN_HEX)
							{
								plainHexPtr = Base64BinToPlainHex(cV[CurrentCertificate]->serialNumber);
								*value = A2WBSTR((LPCSTR)plainHexPtr);
								zFree(plainHexPtr);
							}
							else
								*value = A2WBSTR((LPCSTR)cV[CurrentCertificate]->serialNumber);
						else
							if (CertSerialNumberFormat == CERT_SERIAL_PLAIN_HEX)
							{
								plainHexPtr = Base64BinToPlainHex(cV[index]->serialNumber);
								*value = A2WBSTR((LPCSTR)plainHexPtr);
								zFree(plainHexPtr);
							}
							else
								*value = A2WBSTR((LPCSTR)cV[index]->serialNumber);
					break;
			case 2: if (providePfxCertInfo)
                         *value = SysAllocString((const OLECHAR *)PfxCertInfo->issuer);
					else if (provideActiveCertInfo)
						*value = SysAllocString((const OLECHAR *)cV[CurrentCertificate]->issuer);
					else
						*value = SysAllocString((const OLECHAR *)cV[index]->issuer);
					break;
			case 3:	if (providePfxCertInfo)
                         *value = SysAllocString((const OLECHAR *)PfxCertInfo->subject);
					else if (provideActiveCertInfo)
						*value = SysAllocString((const OLECHAR *)cV[CurrentCertificate]->subject);
					else
						*value = SysAllocString((const OLECHAR *)cV[index]->subject);
					break;
			case 4: if (providePfxCertInfo)
                         *value = A2WBSTR((LPCSTR)PfxCertInfo->notAfter);
					else if (provideActiveCertInfo)
						*value = A2WBSTR((LPCSTR)cV[CurrentCertificate]->notAfter);
					else
						*value = A2WBSTR((LPCSTR)cV[index]->notAfter);
					break;
			case 5: if (providePfxCertInfo)
                         *value = SysAllocString((const OLECHAR *)PfxCertInfo->shortSubject);
					else if (provideActiveCertInfo)
						*value = SysAllocString((const OLECHAR *)cV[CurrentCertificate]->shortSubject);
					else
						*value = SysAllocString((const OLECHAR *)cV[index]->shortSubject);
					break;
			default: 
					setError(SigHandle, CERT_VAL_INDEX_ERROR);
					return S_FALSE;
					break;
		}
	}
	ExitObjectLog;
	return S_OK;
}


STDMETHODIMP CSignature::SetActiveCertificate(BSTR certID, BOOL *status)
{
#ifdef LOGGING
	char buffer[BUFSIZ];
	memset(buffer, 0, BUFSIZ);
#endif
	int i;
	CComBSTR tmpCertId;
	unsigned char *base64CertId=NULL;

	*status = FALSE;

	EnterObjectLog;

	tmpCertId = certID;
#ifdef LOGGING
	sprintf((char *)buffer, "tmpCertId.Length() = %d", tmpCertId.Length());
	DebugLog((const char *)buffer);
#endif
	if (tmpCertId.Length() == 0)
	{
		setError(SigHandle, CERT_NOT_FOUND);
		return S_FALSE;
	}
USES_CONVERSION;
	if (CertSerialNumberFormat == CERT_SERIAL_PLAIN_HEX)
	{
		unsigned char *wCertID = HeapW2A(certID);
		base64CertId = PlainHexToBase64Bin(wCertID);
		zFree(wCertID);
	}
	else
		base64CertId = HeapW2A(certID);
	DebugLog((const char *)base64CertId);
	for (i=0;i<CertificateCount;i++)
	{
		if (!(StrCmp((const char *)cV[i]->serialNumber, (const char *)base64CertId)))
		{
			CurrentCertificate = i;
			*status = TRUE;
			break;
		}
		*status = FALSE;
	}
	if (base64CertId)
	{
		zFree(base64CertId);
		base64CertId = NULL;
	}

	if ((i==CertificateCount) && (*status == FALSE))
	{
		setError(SigHandle, CERT_NOT_FOUND);
		CurrentCertificate = NOT_INITIALIZED;
		DebugLog((const char *)"(i==CertificateCount) && (*status == FALSE)");
		return S_FALSE;
	}
	if (PfxCertInfo != NULL)
	{
		if (PfxCertInfo->certificate != NULL)
		{
			zFree(PfxCertInfo->certificate);
			PfxCertInfo->certificate = NULL;
		}
		zFree(PfxCertInfo);
		PfxCertInfo = NULL;
	}
#ifdef WIN32
	if ((UsingNetscape) && (nsCertStoreObj != NULL))
	{
		BSTR pfxX509Cert;

		_bstr_t pfxFilePath = nsCertStoreObj->ExportNetscapeCert(_bstr_t(cV[CurrentCertificate]->serialNumber));
		SetActivePFXFileCert(pfxFilePath, nsStorePassword, &pfxX509Cert);
		DeleteFile((LPCTSTR)(char *)pfxFilePath);
	}
#endif
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_SignedDocumentPath(long sigIndex, long uriIndex, BSTR *pVal)
{
	int maxUri=0;

	*pVal = NULL;

	EnterObjectLog;

	if (sgArr==NULL)
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	if ((sigIndex >= signum) || (sigIndex < 0))
	{
		setError(SigHandle, SIG_INDEX_ERROR);
		return S_FALSE;
	}

	maxUri = sgArr[sigIndex]->refNumber;

	if ((uriIndex >= maxUri) || (uriIndex < 0))
	{
		setError(SigHandle, URI_INDEX_ERROR);
		return S_FALSE;
	}

	if (uriArr == NULL)
	{
		setError(SigHandle, DOC_PATH_NOT_FOUND);
		return S_FALSE;
	}

USES_CONVERSION;

	for (int k=0; k<totalUriCount; k++)
	{
		if (!(strcmp((const char *)sgArr[sigIndex]->refArray[uriIndex]->URI, (const char *)uriArr[k]->URI)))
		{
			*pVal = A2WBSTR((LPCSTR)uriArr[k]->fullPath);
			ExitObjectLog;
			return S_OK;
		}
	}
	setError(SigHandle, DOC_PATH_NOT_FOUND);
	return S_FALSE;
}



void CSignature::FetchSignatureStatus(BOOL verifyResult, BOOL extractSignedContent)
{
	int i,j, refNum=0, totalLocNum=0, failedLocNum=0;
	PURI_STATUS *refArr=NULL;
	PURI_PATH uriPath=NULL;
#ifdef WIN32
	HANDLE hTempFile; 
#else
	FILE *hTempFile;
#endif
	DWORD  dwBytesWritten, dwBytesToWrite;
	char TempPath[MAX_PATH];
	char *decodedDataPtr;

	EnterObjectLog;
	
USES_CONVERSION;
	if (uriArr != NULL)
		FreeUriArr();
	failedUriCount = 0;
	totalUriCount  = 0;
	sgArr = axGetSignature(&signum, SigHandle); // Get the full signature stats

	if (signum == 0) // No signature was found or XML error
		return;

	if (verifyResult != TRUE) // At Least One Signature Verification failed
	{
	// Find out how many URIs were signed and how many failed verification

		for (i=0; i<signum; i++) // For each signature in the document
		{
			refNum = sgArr[i]->refNumber; // Number of URI in this signature
			refArr = sgArr[i]->refArray;  // The URI Array itself
				
			if (sgArr[i]->status == FALSE) // Signature verification failed
				for (j=0; j<refNum; j++)
				{
					if (refArr[j]->status == FALSE)
						failedUriCount++; // Increase the number of failed URI by one
					totalUriCount++;	  // Increase the total URI count by one
				}
			else // Signature verification was successful
				totalUriCount += refNum; // Increase the total number of URIs by refNum
		}

		uriArr = (PURI_PATH *)zMalloc(sizeof(PURI_PATH)*totalUriCount);
		failedUriArr = (PURI_PATH *)zMalloc(sizeof(PURI_PATH)*failedUriCount);

		for (i=0; i<signum; i++) // For each signature in the document
		{
			refNum = sgArr[i]->refNumber; // Number of URI in this signature
			refArr = sgArr[i]->refArray;  // The URI Array itself
				
			if (sgArr[i]->status == FALSE) // Signature verification failed
			{
				for (j=0; j<refNum; j++)
				{
					uriPath = (PURI_PATH) zMalloc(sizeof(URI_PATH));
					uriPath->fullPath = (unsigned char *)zMalloc(MAX_PATH * 2);
					uriPath->sigId = (unsigned char *)zMalloc(MAX_PATH);
					uriPath->URI = (unsigned char *)zMalloc (MAX_PATH);
					
					if (sgArr[i]->sigId != NULL)
						strcpy((char *)uriPath->sigId,(const char *)sgArr[i]->sigId);
					if (refArr[j]->URI != NULL)
						strcpy((char *)uriPath->URI,(const char *)refArr[j]->URI);
					if (refArr[j]->URI != NULL)
						strcpy((char *)uriPath->fullPath,(const char *)refArr[j]->URI);

						
					if (refArr[j]->status == FALSE)
					{
						failedUriArr[failedLocNum] = uriPath;
						failedLocNum++;
					}
					uriArr[totalLocNum] = uriPath; // Failed Uris are referenced 2 places
					totalLocNum++;
				}
			}
			else // Signature verification was successful
				for (j=0; j<refNum; j++)
				{
					uriPath = (PURI_PATH) zMalloc(sizeof(URI_PATH));
					uriPath->fullPath = (unsigned char *)zMalloc(MAX_PATH * 2);
					uriPath->sigId = (unsigned char *)zMalloc(MAX_PATH);
					uriPath->URI = (unsigned char *)zMalloc (MAX_PATH);

					if (sgArr[i]->sigId != NULL)
						strcpy((char *)uriPath->sigId,(const char *)sgArr[i]->sigId);
					if (refArr[j]->URI != NULL)
					{
						strcpy((char *)uriPath->URI,(const char *)refArr[j]->URI);
						strcpy((char *)uriPath->fullPath,(const char *)refArr[j]->URI);
					}


					uriArr[totalLocNum] = uriPath;
					totalLocNum++;
				}
			if (extractSignedContent == TRUE)
			{
				for (int m=0; m<refNum; m++)
				{
					for (int k=0; k<totalLocNum; k++) 
					{
						if ((!(strcmp((const char *)refArr[m]->URI, (const char *)uriArr[k]->URI))) &&
							(refArr[m]->refObject != NULL))
						{
							GetTempPath((DWORD)MAX_PATH, TempPath);
							GetTempFileName(TempPath, // dir. for temp. files 
								"INFM",                // temp. file name prefix 
								0,                    // create unique name 
								szTempName);          // buffer for name 
#ifdef WIN32
							hTempFile = CreateFile((LPCSTR) szTempName,  // file name 
								GENERIC_READ | GENERIC_WRITE, // open for read/write 
								0,                            // do not share 
								NULL,                         // no security 
								CREATE_ALWAYS,                // overwrite existing file
								FILE_ATTRIBUTE_NORMAL,        // normal file 
								NULL);                        // no attr. template 
							if (hTempFile == INVALID_HANDLE_VALUE) 
								break;
#else
							hTempFile = fopen(szTempName, "w+");
							if (!hTempFile)
								break;
#endif
							TEMP_FILE_INFO *tmpFilePath = new (TEMP_FILE_INFO);
							strcpy((char *)tmpFilePath->fileName, szTempName);
							tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
							dwBytesToWrite = base64decodeSize((DWORD)strlen((const char *)refArr[m]->refObject->encodedData));
							decodedDataPtr = (char *)zMalloc (dwBytesToWrite+1);
							memset(decodedDataPtr,0,dwBytesToWrite+1);
							if ((dwBytesToWrite = base64decode(refArr[m]->refObject->encodedData,(unsigned char *)decodedDataPtr,dwBytesToWrite))==-1) 
						{
							// Close file. 
#ifdef WIN32
							CloseHandle(hTempFile); 
#else
							fclose(hTempFile);
#endif
							zFree(decodedDataPtr);
							continue;
						}

							// Write the signature buffer to the temporary file. 
#ifdef WIN32
							WriteFile(hTempFile, decodedDataPtr, dwBytesToWrite , 
										&dwBytesWritten, NULL); 
							// Close file. 
							CloseHandle(hTempFile);
#else
							dwBytesWritten = fwrite(decodedDataPtr, 1, dwBytesToWrite, hTempFile);
							fclose(hTempFile);
#endif
							zFree(decodedDataPtr);
							strcpy((char *)uriArr[k]->fullPath, szTempName);
							break;
						}
					}
				}
			}

		} /* end for each signature in the document loop */
		return;
	} // end if signature failed

	// signature verification was successful

	for (i=0; i<signum; i++) // For each signature in the document
	{
		refNum = sgArr[i]->refNumber; // Number of URI in this signature
		totalUriCount += refNum; // Increase the total number of URIs by refNum
	}

	uriArr = (PURI_PATH *)zMalloc(sizeof(PURI_PATH)*totalUriCount);
	failedUriArr = NULL; // Signature verification was successful
	totalLocNum = 0;

	for (i=0; i<signum; i++) // For each signature in the document
	{
		refNum = sgArr[i]->refNumber; // Number of URI in this signature
		refArr = sgArr[i]->refArray;  // The URI Array itself
				
		for (j=0; j<refNum; j++)
		{
			uriPath = (PURI_PATH) zMalloc(sizeof(URI_PATH));
			uriPath->fullPath = (unsigned char *)zMalloc(MAX_PATH * 2);
			uriPath->sigId = (unsigned char *)zMalloc(MAX_PATH);
			uriPath->URI = (unsigned char *)zMalloc (MAX_PATH);

			if (sgArr[i]->sigId != NULL)
				strcpy((char *)uriPath->sigId,(const char *)sgArr[i]->sigId);
			if (refArr[j]->URI != NULL)
			{
				strcpy((char *)uriPath->URI,(const char *)refArr[j]->URI);
				strcpy((char *)uriPath->fullPath,(const char *)refArr[j]->URI);
			}


			uriArr[totalLocNum] = uriPath;
			totalLocNum++;
		}

		if (extractSignedContent == TRUE)
		{
			for (int m=0; m<refNum; m++)
			{
				for (int k=0; k<totalLocNum; k++) 
				{
					if ((!(strcmp((const char *)refArr[m]->URI, (const char *)uriArr[k]->URI))) &&
						(refArr[m]->refObject != NULL))
					{
						GetTempPath((DWORD)MAX_PATH, TempPath);
						GetTempFileName(TempPath, // dir. for temp. files 
							"INFM",                // temp. file name prefix 
							0,                    // create unique name 
							szTempName);          // buffer for name 
#ifdef WIN32
						hTempFile = CreateFile((LPCSTR) szTempName,  // file name 
							GENERIC_READ | GENERIC_WRITE, // open for read/write 
							0,                            // do not share 
							NULL,                         // no security 
							CREATE_ALWAYS,                // overwrite existing file
							FILE_ATTRIBUTE_NORMAL,        // normal file 
							NULL);                        // no attr. template 
						if (hTempFile == INVALID_HANDLE_VALUE) 
							break;
#else
						hTempFile = fopen(szTempName, "w+");
						if (!hTempFile)
							break;
#endif
						TEMP_FILE_INFO *tmpFilePath = new (TEMP_FILE_INFO);
						strcpy((char *)tmpFilePath->fileName, szTempName);
						tmpFileList->insert(tmpFileList->begin(), tmpFilePath);

						dwBytesToWrite = base64decodeSize((DWORD)strlen((const char *)refArr[m]->refObject->encodedData));
						decodedDataPtr = (char *)zMalloc (dwBytesToWrite+1);
						memset(decodedDataPtr,0,dwBytesToWrite+1);
						if ((dwBytesToWrite = base64decode(refArr[m]->refObject->encodedData,(unsigned char *)decodedDataPtr,dwBytesToWrite))==-1) 
						{
#ifdef WIN32
							// Close file. 
							CloseHandle(hTempFile);
#else
							fclose(hTempFile);
#endif
							zFree(decodedDataPtr);
							continue;
						}
#ifdef WIN32
						// Write the signature buffer to the temporary file. 
						WriteFile(hTempFile, decodedDataPtr, dwBytesToWrite , 
									&dwBytesWritten, NULL); 
						// Close file. 
						CloseHandle(hTempFile); 
#else
						dwBytesWritten = fwrite(decodedDataPtr, 1, dwBytesToWrite, hTempFile);
						fclose(hTempFile);
#endif
						zFree(decodedDataPtr);
						strcpy((char *)uriArr[k]->fullPath, szTempName);
						break;
					}
				}
			}
		}
	}
	ExitObjectLog;
}


STDMETHODIMP CSignature::get_SignerSubject(BSTR sigId, BSTR *pVal)
{
	CComBSTR tmpSigId;
	EnterObjectLog;
	tmpSigId = sigId;
	if (tmpSigId.Length() == 0)
	{
		setError(SigHandle, SIG_NOT_FOUND);
		return S_FALSE;
	}
USES_CONVERSION;
	*pVal = NULL;

	if ((sgArr==NULL) || (signum == 0))
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}

	for (int i=0; i < signum; i++)
	{
		unsigned char *wSigId = HeapW2A(sigId);
		if (!strcmp((const char *)sgArr[i]->sigId, (const char *)wSigId))
		{
			*pVal = SysAllocString((const OLECHAR *)sgArr[i]->signerCert->subject);
			zFree(wSigId);
			ExitObjectLog;
			return S_OK;
		}
		zFree(wSigId);
	}
	setError(SigHandle, SIG_NOT_FOUND);
	return S_FALSE;
}

STDMETHODIMP CSignature::get_CertIssuer(BSTR sigId, BSTR *pVal)
{
	CComBSTR tmpSigId;
	EnterObjectLog;
	tmpSigId = sigId;
	if (tmpSigId.Length() == 0)
	{
		setError(SigHandle, SIG_NOT_FOUND);
		return S_FALSE;
	}

USES_CONVERSION;
	*pVal = NULL;

	if ((sgArr==NULL) || (signum == 0))
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	for (int i=0; i < signum; i++)
	{
		unsigned char *wSigId = HeapW2A(sigId);
		if (!strcmp((const char *)sgArr[i]->sigId, (const char *)wSigId))
		{
			*pVal = SysAllocString((const OLECHAR *)sgArr[i]->signerCert->issuer);
			zFree(wSigId);
			ExitObjectLog;
			return S_OK;
		}
		zFree(wSigId);
	}
	setError(SigHandle, SIG_NOT_FOUND);
	return S_FALSE;
}

STDMETHODIMP CSignature::get_CertExpiry(BSTR sigId, BSTR *pVal)
{
	CComBSTR tmpSigId;
	EnterObjectLog;
	tmpSigId = sigId;
	if (tmpSigId.Length() == 0)
	{
		setError(SigHandle, SIG_NOT_FOUND);
		return S_FALSE;
	}
USES_CONVERSION;
	*pVal = NULL;

	if ((sgArr==NULL) || (signum == 0))
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	for (int i=0; i < signum; i++)
	{
		unsigned char *wSigId = HeapW2A(sigId);
		if (!strcmp((const char *)sgArr[i]->sigId, (const char *)wSigId))
		{
			*pVal = A2WBSTR((LPCSTR)sgArr[i]->signerCert->notAfter);
			zFree(wSigId);
			ExitObjectLog;
			return S_OK;
		}
		zFree(wSigId);
	}
	setError(SigHandle, SIG_NOT_FOUND);
	return S_FALSE;
}

STDMETHODIMP CSignature::get_CertSerialNumber(BSTR sigId, BSTR *pVal)
{
	CComBSTR tmpSigId;
	unsigned char *plainTextHex;
	unsigned char *charSigId=NULL;
	EnterObjectLog;
	tmpSigId = sigId;
	if (tmpSigId.Length() == 0)
	{
		setError(SigHandle, SIG_NOT_FOUND);
		return S_FALSE;
	}

USES_CONVERSION;
	*pVal = NULL;

	if ((sgArr==NULL) || (signum == 0))
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	charSigId = HeapW2A(sigId);
	for (int i=0; i < signum; i++)
	{
		if (!strcmp((const char *)sgArr[i]->sigId, (const char *)charSigId))
		{
			if (CertSerialNumberFormat == CERT_SERIAL_PLAIN_HEX)
			{
				plainTextHex = Base64BinToPlainHex(sgArr[i]->signerCert->serialNumber);
				*pVal = A2WBSTR((LPCSTR)plainTextHex);
				zFree(plainTextHex);
			}
			else
				*pVal = A2WBSTR((LPCSTR)sgArr[i]->signerCert->serialNumber);
			zFree(charSigId);
			ExitObjectLog;
			return S_OK;
		}
	}
	setError(SigHandle, SIG_NOT_FOUND);
	zFree(charSigId);
	ExitObjectLog;
	return S_FALSE;
}

STDMETHODIMP CSignature::FileExists(BSTR fileName, BOOL *fileStatus)
{
	FILE *hFileHandle; 

	CComBSTR tmpFileName;
	EnterObjectLog;
	tmpFileName = fileName;
	if (tmpFileName.Length() == 0)
	{
		*fileStatus = FALSE; // File does not exist
		return S_FALSE;
	}


USES_CONVERSION;

	// open file and read contest
#ifdef WIN32
	if ((hFileHandle = _wfopen (fileName,L"rb"))==NULL) 
#elif UNIX
	unsigned char *utf8Name = HeapW2A(fileName);
	if ((hFileHandle = fopen((const char *)utf8Name, "rb")) == NULL)
#endif
	{
		*fileStatus = FALSE; // File does not exist
	}
	else
	{
		*fileStatus = TRUE;   // File exists
		// Close file. 
		fclose(hFileHandle); 
	}
#ifdef UNIX
	zFree(utf8Name);
#endif
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_FailedUriCount(long *pVal)
{
	EnterObjectLog;
	*pVal = (long)failedUriCount;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_TotalUriCount(long *pVal)
{
	EnterObjectLog;
	*pVal = (long)totalUriCount;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_FailedUriFullPath(long index, BSTR *pVal)
{
	EnterObjectLog;
	if ((sgArr==NULL) || (signum == 0))
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}

	if ((index >= failedUriCount) || (index < 0))
	{
		setError(SigHandle, URI_INDEX_ERROR);
		return S_FALSE;
	}
	if (failedUriArr == NULL)
	{
		setError(SigHandle, URI_INDEX_ERROR);
		return S_FALSE;
	}

USES_CONVERSION;
	*pVal = A2WBSTR((LPCSTR)failedUriArr[index]->fullPath);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_FailedUriFullPath(long index, BSTR newVal)
{
	EnterObjectLog;
	if ((sgArr==NULL) || (signum == 0))
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	if ((index >= failedUriCount) || (index < 0))
	{
		setError(SigHandle, URI_INDEX_ERROR);
		return S_FALSE;
	}
	if (failedUriArr == NULL)
	{
		setError(SigHandle, URI_INDEX_ERROR);
		return S_FALSE;
	}

	CComBSTR tmpNewVal;

	tmpNewVal = newVal;
	if (tmpNewVal.Length() == 0)
	{
		setError(SigHandle, FILE_NOT_FOUND);
		return S_FALSE;
	}

USES_CONVERSION;

	if (failedUriArr[index]->fullPath != NULL)
	{
		zFree(failedUriArr[index]->fullPath);
		failedUriArr[index]->fullPath = NULL;
	}

	failedUriArr[index]->fullPath = (unsigned char *)HeapW2A(newVal);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_FailedUri(long index, BSTR *pVal)
{
	EnterObjectLog;
	if ((sgArr==NULL) || (signum == 0))
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}

	if ((index >= failedUriCount) || (index < 0))
	{
		setError(SigHandle, URI_INDEX_ERROR);
		return S_FALSE;
	}
	if (failedUriArr == NULL)
	{
		setError(SigHandle, URI_INDEX_ERROR);
		return S_FALSE;
	}

USES_CONVERSION;

	*pVal = A2WBSTR((LPCSTR)failedUriArr[index]->URI);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_SignatureCount(long *pVal)
{
	EnterObjectLog;
	*pVal = signum;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::SignXMLStr(BSTR xmlStr, BSTR signatureId, BSTR *signedXMLStr)
{
	char *charXMLStr=NULL, *charSigId=NULL, *curCharSigId=NULL;
	unsigned char *charSignedXMLStr=NULL;
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL, parent=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlChar *mem=NULL;
	int iSize=0;
	CComBSTR	sigId;
	unsigned char *ptr, *newPtr=NULL, *curPtr=NULL; 
	unsigned int *szPtr;
	unsigned int sizeM;

	xmlXPathContextPtr xpathPtr=NULL;
	xmlXPathObjectPtr xpathResultPtr=NULL;
	char *ptemp=NULL;
	BOOL freeNewPtr = FALSE;

#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	BOOL templateFound=FALSE;

	EnterObjectLog;
	//if (! LicObj.checkLicense()) {
	//	setError(SigHandle, INVALID_SECUREXML_LIC);
	//	return S_FALSE;
	//}
//DebugBreak();
	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	USES_CONVERSION;

	BOOL freeCharSigId = FALSE;
	sigId = signatureId;
	if (sigId.Length() == 0)
		charSigId = NULL;
	else
	{
		charSigId = (char *)HeapW2A(signatureId);
		freeCharSigId = TRUE;
	}

	if (charSigId == NULL)
		if (SignatureID.Length() == 0)
		{
//#ifdef WIN32
//			CoCreateGuid(&sigGuid);
//			GuidToString(&sigGuid, guidStr);
//#else
//			uuid_generate(sigGuid);
//			uuid_unparse(sigGuid, guidStr);
//#endif
//			charSigId = guidStr;
		}
		else
		{
			charSigId = (char *)HeapW2A(SignatureID.m_str);
			freeCharSigId = TRUE;
		}

	if ((xmlStr != 0) && (SysStringByteLen(xmlStr) != 0))
	{
		if (Base64DecodeXML == FALSE)
		{
			ptr = (unsigned char *)xmlStr;
			szPtr = (unsigned int *)(ptr - sizeof(int));
			sizeM = (*szPtr);

			if (((*ptr == 0xff) && (*(ptr + 1) == 0xfe)) ||
				((*ptr == 0xfe) && (*(ptr + 1) == 0xff)))
			{
				// There is no need to put the UTF 16 header since the data is already in utf-16 format
				newPtr = ptr;
			}
			else
			{
				newPtr = (unsigned char *)zMalloc(sizeM + 4);
				freeNewPtr = TRUE;
				FileEncoding(newPtr);
				memcpy(newPtr+2, ptr, sizeM + 2);
				sizeM += 4;
			}
		}
		else
		{
			ptr = HeapW2A(xmlStr);
			sizeM = strlen((const char *)ptr);
			sizeM = base64decodeSize(sizeM);
			newPtr = (unsigned char *)zMalloc(sizeM+1);
			freeNewPtr = TRUE;
			if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
			{
				zFree(ptr);
				zFree(newPtr);
				setError(SigHandle, BASE64_ERROR);
				if (freeCharSigId)
					zFree(charSigId);
				return S_FALSE;
			}
			zFree(ptr);
		}
		if (! LicObj.getSignAllowed()) 
		{
			if (!LicObj.getFormSignAllowed(newPtr, sizeM, SigHandle))
			{
				setError(SigHandle, NO_SIGNING_LIC);
				if (freeCharSigId)
					zFree(charSigId);
				if (freeNewPtr)
					zFree(newPtr);
				return S_FALSE;
			}
		}

		// original document
		doc = xmlParseMemory((const char *)newPtr,sizeM);
		if (freeNewPtr)
			zFree(newPtr);

		if (!doc) 
		{
			setError(SigHandle, XML_PARSER_ERROR);
			if (freeCharSigId)
				zFree(charSigId);
			return S_FALSE;
		}

		root = xmlDocGetRootElement(doc);
		if (charSigId != NULL)
			sigNode = xsSigNodeById((const xmlNodePtr) root, (const xmlChar *)charSigId);
		else
			sigNode = xsSigNodeWithNoIdNoSigValue((const xmlNodePtr) root);
		if (sigNode != NULL)
		{
			templateFound = TRUE;
			cur = sigNode->xmlChildrenNode;
			while (cur)
			{
					if (!(xmlStrcmp(cur->name, (const xmlChar *) "SignedInfo")))
					{
						signedInfoNode = cur;
						break;
					}
					cur = cur->next;
			}  // end while cur != NULL
		}
		cur = root->xmlChildrenNode;
		if (templateFound == FALSE) // A Signature element with matching Id was not found
		{
			// Add a new Signature element

			/*
			* Signature
			*/

			cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
			sigNode = cur;
			if (charSigId != NULL)
				xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
			cur = xmlAddChild(root,cur);
			//xmlNewNs(cur,(const unsigned char *)"http://www.w3.org/2000/09/xmldsig#",(const unsigned char *)NULL);

			xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
			parent = cur;

			/*
			* SignedInfo
			*/
			cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
			signedInfoNode = cur;
			cur = xmlAddChild(parent,cur);
			parent = cur;

			/*
			* Canonicalization Method
			*/
			cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
			switch(CanonicalizationMethod)
			{
				case WITH_COMMENTS:
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
					break;
				case WITHOUT_COMMENTS:
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
					break;
				case EXC_WITH_COMMENTS:
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
					break;
				case EXC_WITHOUT_COMMENTS:
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
					break;
				default:
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
			}
			cur = xmlAddChild(parent,cur);
			/*
			* Reference
			*/
			cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
			cur = xmlAddChild(parent,cur);

			xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)"");
			parent = cur;

			/*
			* Transforms
			*/
		
			cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
			cur = xmlAddChild(parent,cur);
			parent = cur;

			/*
			* Transform
			*/

			if ((CanonicalizationMethod == EXC_WITH_COMMENTS) ||
				(CanonicalizationMethod == EXC_WITHOUT_COMMENTS))
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
				if (CanonicalizationMethod == EXC_WITH_COMMENTS)
				{
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
				}
				else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
				{
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
				}
				cur = xmlAddChild(parent,cur);
				parent = cur;
				if (CanonicalizationMethod == EXC_WITH_COMMENTS)
				{
					cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
					xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_WITH_COMM,(const unsigned char *)"ec");
					xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
				}
				else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
				{
					cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
					xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_NO_COMM,(const unsigned char *)"ec");
					xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
				}
				cur = xmlAddChild(parent,cur);
				parent = parent->parent;
			}

			cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_ENVELOPED_SIG);
			cur = xmlAddChild(parent,cur);		
		}
	}
	else
	{
		if ((AttachedObjectCount != 0) || (DetachedObjectCount !=0))
		{
			doc = PrepareSignatureEnvelopeFromObjects(charSigId, &sigNode, &signedInfoNode);
			if (doc == NULL)
			{
				if (freeCharSigId)
					zFree(charSigId);
				return S_FALSE;
			}
		}
		else
		{
			if (freeCharSigId)
				zFree(charSigId);
			setError(SigHandle, XML_PARSER_ERROR);
			return S_FALSE;
		}
	}

#ifdef WIN32
	  if (AddWindowImageFlag == TRUE)
		  AddWindowImage(sigNode, signedInfoNode, charSigId);

	  if (PhysicalSigUsage != NO_PHYSICAL_SIG)		  
		  AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif 
	/*
	 * init Signature. crBlob contains XML - envelope document
	 */
	short tmpEnvFlag = EnvelopingFlag;
	EnvelopingFlag = ENVELOPED;

	if (!(CreateSigFromTmplBlob(
								//&crBlob,
								doc,
								charSigId, &charSignedXMLStr, &iSize)))
	{
		if (charSignedXMLStr != NULL)
		{
			xmlFree(charSignedXMLStr);
		}
		EnvelopingFlag = tmpEnvFlag;
		*signedXMLStr = NULL;
		if (freeCharSigId)
			zFree(charSigId);
		ExitObjectLog;
		return S_FALSE;
	}
	else
	{
		if (charSignedXMLStr != NULL)
		{
			unsigned char *dataPtr = charSignedXMLStr;

			if (((*dataPtr == 0xff) && (*(dataPtr +1) == 0xfe)) ||
				((*dataPtr == 0xfe) && (*(dataPtr +1) == 0xff)))
			{
				// This is a UTF-16 file, so no need to do a char * to BSTR conversion
				// Just allocate memory and copy data and put the size information in front
				*signedXMLStr = ::SysAllocStringByteLen((LPCSTR)dataPtr, iSize);
				xmlFree(dataPtr);
			}
			else
			{
				*signedXMLStr = A2WBSTR((LPCSTR)dataPtr, iSize);
				if (Base64EncodeXML == TRUE)
					zFree(dataPtr);
				else
					xmlFree(dataPtr);
			}
		}
	}
	EnvelopingFlag = tmpEnvFlag;
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return S_OK;
}

/**
 * xsDereferenceBstrURI
 * @ref: (in) URI or file path
 * @cbRef: (out) size of result
 *
 * get HTTP of file context of URI
 *
 * Returns: pointer to the data
 */
BYTE * CSignature::xsDereferenceBstrURI (
	BSTR bstrRef,
	DWORD *cbRef)
{
FILE *fdoc;
#ifdef WIN32
struct _stat statbuf;
#elif UNIX
struct stat statbuf;
#endif
unsigned int res=0;
char *contentType = NULL;
unsigned char *content=NULL;
DS_DATA_BLOB **pDataBlob;
URI ref;

USES_CONVERSION;

	unsigned char *abstrRef = HeapW2A(bstrRef);
	ref = (URI)abstrRef;

	if (ref == NULL) {
		return NULL;
	}

		// is it URI?
	if ((strnicmp(ref,"http://",7))==0) {
		content = xsHTTPFetch(ref, (int *) cbRef);
		if (content == NULL) {
#ifdef _DEBUG
	printf("Cannot fetch content: %s\n",ref);
#endif
			zFree(abstrRef);
			return NULL;
		}
		zFree(abstrRef);
		return content;
	}
	if (strnicmp(ref,"ldap:",5)==0) 
	{
		pDataBlob = fetchLDAP_URL((BYTE *)ref);
		if (pDataBlob == NULL || pDataBlob[0] == NULL) {
			zFree(abstrRef);
			return NULL;
		}
		else
		{
			*cbRef = pDataBlob[0]->cbData;
			content = pDataBlob[0]->pbData;
			int i=0;
			while (pDataBlob[i]) {
				zFree(pDataBlob[i]->pbData);
				zFree(pDataBlob[i]);
				i++;
			}
			zFree(pDataBlob);
			zFree(abstrRef);
			return(content);
		}
	}

	if ((strnicmp(ref,"file://",7))==0) {
		ref = ref+8;
	}
	zFree(abstrRef);
		// open file and read contest
#ifdef WIN32
	if ((fdoc = _wfopen(bstrRef,L"rb"))==NULL) {
		return NULL;
	}
	_wstat (bstrRef, &statbuf );
#elif UNIX
	unsigned char *utf8Ref = HeapW2A(bstrRef);
	if ((fdoc = fopen((const char *)utf8Ref, "rb")) == NULL)
	{
		zFree(utf8Ref);
		return NULL;
	}
	stat((const char *)utf8Ref, &statbuf);
	zFree(utf8Ref);
#endif

	*cbRef = statbuf.st_size;
	content = (unsigned char *) zMalloc (*cbRef+1);
	memset(content,0,*cbRef+1);
	fread(content, 1, statbuf.st_size, fdoc);
	fclose( fdoc );
	return content;
}


STDMETHODIMP CSignature::ReadAll(BSTR fileName, BSTR *fileDataStr)
{
	unsigned char *dataPtr;
	DWORD	dwFileSize;
	unsigned char *charFileName;

	USES_CONVERSION;
	EnterObjectLog;
	*fileDataStr = A2WBSTR((LPCSTR)NULL);
	charFileName = HeapW2A(fileName);

	if ((charFileName == NULL) || (strlen((const char *)charFileName) == 0))
	{
		setError(SigHandle, DEREF_URI_ERROR);
		zFree(charFileName);
		ExitObjectLog;
		return S_FALSE;
	}

	dataPtr = xsDereferenceBstrURI(fileName, &dwFileSize);
	if (dataPtr == NULL)
	{
		setError(SigHandle, FILE_NOT_FOUND);
		zFree(charFileName);
		ExitObjectLog;
		return S_FALSE;
	}
	else
	{
		if (((*dataPtr == 0xff) && (*(dataPtr +1) == 0xfe)) ||
			((*dataPtr == 0xfe) && (*(dataPtr +1) == 0xff)))
		{
			// This is a UTF-16 file, so no need to do a char * to BSTR conversion
			// Just allocate memory and copy data and put the size information in front
			*fileDataStr = ::SysAllocStringByteLen((LPCSTR)dataPtr, (UINT)dwFileSize);
			zFree(dataPtr);
		}
		else
		{
			*fileDataStr = A2WBSTR((LPCSTR)dataPtr, dwFileSize);
			zFree(dataPtr);
		}
		zFree(charFileName);
		ExitObjectLog;
		return S_OK;
	}
}

BOOL CSignature::ReadAllBin(BSTR fileName, unsigned char **binData, DWORD *dwFileSize)
{
	EnterObjectLog;
	if ((fileName == NULL) || (SysStringLen(fileName) == 0))
	{
		setError(SigHandle, DEREF_URI_ERROR);
		return S_FALSE;
	}
	*binData = xsDereferenceBstrURI(fileName, dwFileSize);
	if (*binData == NULL)
		return S_FALSE;
	else
	{
		ExitObjectLog;
		return S_OK;
	}
}


STDMETHODIMP CSignature::SaveXMLStr(BSTR inputXMLStr, BSTR fileName, BSTR *path)
{
	FILE *hInFile; 
	BOOL writeResult;
	char *charInputXMLStr;
	int fileSize;
	CComBSTR ccBstrFileName;
	BSTR bstrFileName;
	char TempPath[MAX_PATH];
	CComBSTR tmpXmlStr;
	BOOL freeMemory=FALSE;
	TEMP_FILE_INFO	*tmpFilePath = NULL;

	EnterObjectLog;
	*path = A2WBSTR((const char *) NULL);
	tmpXmlStr = inputXMLStr;
	if (tmpXmlStr.Length() == 0)
	{
		setError(SigHandle, IO_ERROR);
		DebugLog("Input XML String is empty");
		return S_FALSE;
	}

	USES_CONVERSION;
	ccBstrFileName = fileName;

	if ((ccBstrFileName.Length() == 0) || (FileAccessRestricted == TRUE))
	{
		// Create temporary file for saving input XML String
		GetTempPath((DWORD)MAX_PATH, TempPath); 
		GetTempFileName(TempPath, // dir. for temp. files 
			"INF",                // temp. file name prefix 
			0,                    // create unique name 
			szTempName);          // buffer for name 
		bstrFileName = A2WBSTR(szTempName);
		tmpFilePath = new (TEMP_FILE_INFO);
		strcpy((char *)tmpFilePath->fileName, szTempName);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
	}
	else
		bstrFileName = SysAllocString(fileName);

	// open file in write mode 
#ifdef WIN32
	if ((hInFile = _wfopen(bstrFileName,L"wb"))==NULL) {
#elif UNIX
	unsigned char *utf8FileName = HeapW2A(bstrFileName);
	if ((hInFile = fopen((const char *)utf8FileName, "wb")) == NULL) {
			zFree(utf8FileName);
#endif
			setError(SigHandle, IO_ERROR);
			DebugLog("Could not create file");
			if (tmpFilePath != NULL)
			{
				tmpFileList->remove(tmpFilePath);
			}
			SysFreeString(bstrFileName);
			return S_FALSE;
	}
#ifdef UNIX
	zFree(utf8FileName);
#endif

	unsigned char *ptr = (unsigned char *)inputXMLStr;
	unsigned int *szPtr = (unsigned int *)(ptr - sizeof(int));
	fileSize = (*szPtr);

	if (((*ptr == 0xff) && (*(ptr +1) == 0xfe)) ||
		((*ptr == 0xfe) && (*(ptr +1) == 0xff)))
	{
		// The data is in utf-16 format so do not convert to char *
		charInputXMLStr = (char *)ptr;
	}
	else
	{
		charInputXMLStr = (char *)HeapW2A(inputXMLStr);
		fileSize = strlen(charInputXMLStr);
		freeMemory = TRUE;
	}

	if ((writeResult = fwrite(charInputXMLStr, 1, fileSize, hInFile)) == 0)
	{
		setError(SigHandle, IO_ERROR);
		DebugLog("Could not write to file");
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}
	if (ferror(hInFile))
	{
		setError(SigHandle, IO_ERROR);
		DebugLog("Could not write to file");
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}

	fclose(hInFile);
	//tmpXmlStr = bstrFileName;
	//*path = tmpXmlStr.Copy();
	*path = bstrFileName;
	if (freeMemory)
		zFree(charInputXMLStr);
	ExitObjectLog;
	return S_OK;
}

#ifdef WIN32
STDMETHODIMP CSignature::SignHTML(IDispatch *document, BSTR *signedHTML)
{
	IHTMLDocument3 *curDoc;
	IHTMLElement	*htmlElement;
	BSTR htmlstr;
	char *charHtmlStr;
	DS_DATA_BLOB crBlob;
	int htmlSize;
	unsigned char *certData=NULL;
	keyinfo *ki=NULL;
	char *charSigId=NULL;
	unsigned char *signedXML=NULL;
	char guidStr[50];
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif

	EnterObjectLog;
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (!LicObj.getSignAllowed()) {
		setError(SigHandle, NO_SIGNING_LIC);
		return S_FALSE;
	}

	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	xmlDocPtr doc= NULL;
	xmlNodePtr cur=NULL, rootNode=NULL, parent=NULL, commNode=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlNsPtr curNs=NULL;
	xmlChar *mem=NULL;
	xmlDtdPtr dtd=NULL;
	int iSize=0;

	crBlob.cbData = 0;
	crBlob.pbData = NULL;

	USES_CONVERSION;

	document->QueryInterface(IID_IHTMLDocument3, (void **)&curDoc);

	curDoc->get_documentElement(&htmlElement);
	htmlElement->get_outerHTML(&htmlstr);

	charHtmlStr = (char *)HeapW2A(htmlstr);
/* To be Added by Alex
<!DOCTYPE InfomosaicSecureXML [
  <!ATTLIST SignedHTML Id ID #IMPLIED>
]>

*/


	doc = xmlNewDoc((const unsigned char *)"1.0");
	// document, namespace, element name, element content
	cur = xmlNewDocNode(doc,NULL,(const unsigned char *)"InfomosaicSecureXML",NULL);

	// if you want any namespace definition here
	curNs = xmlNewNs(cur,(const unsigned char *)"http://www.infomosaic.net/SignHTML/DTD.htm",(const unsigned char *)"infomosaic");
	xmlSetNs(cur,curNs);


	// add root element
	xmlDocSetRootElement(doc,cur);
	rootNode = cur;

	//// add some comment
	//commNode = xmlNewDocComment(doc,(const unsigned char *)"HTML Signed by Infomosaic SecureXML http://www.infomosaic.net");
	//cur = xmlAddChild(rootNode,commNode);
	/*
	 * SignedHTML
	*/
	cur = xmlNewNode(curNs,(const unsigned char *)"SignedHTML"); // Using the parent element's name space
	cur = xmlAddChild(rootNode,cur);
	xmlNewProp(cur, (const unsigned char *)"Encoding", (const unsigned char *)ALG_BASE64);
	xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)"HTMLData");

	// Base64 encode
	htmlSize = strlen((const char *)charHtmlStr);
	crBlob.cbData = base64encodeSize(htmlSize);
	// allocate memory
	if(!(crBlob.pbData = (unsigned char*)zMalloc(crBlob.cbData+1)))
	{
		return S_FALSE;
	}
	if (base64encode((unsigned char *)charHtmlStr,htmlSize,(unsigned char*)crBlob.pbData,crBlob.cbData)==-1) {
		return S_FALSE;
	}
	*(crBlob.pbData+crBlob.cbData)='\0';

	zFree(charHtmlStr);

	xmlNodeSetContent(cur,(const unsigned char *)crBlob.pbData);

	/*
	 * Signature
	*/

	BOOL freeCharSigId = FALSE;
	if (SignatureID.Length() == 0)
	{
#ifdef WIN32
		CoCreateGuid(&sigGuid);
		GuidToString(&sigGuid, guidStr);
#else
		uuid_generate(sigGuid);
		uuid_unparse(sigGuid, guidStr);
#endif
		charSigId = guidStr;
	}
	else
	{
		charSigId = (char *)HeapW2A(SignatureID.m_str);
		freeCharSigId = TRUE;
	}

	cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
	sigNode = cur;
	xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
	cur = xmlAddChild(rootNode,cur);
	xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
	parent = cur;

	/*
	 * SignedInfo
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
	signedInfoNode = cur;
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	 * Canonicalization Method
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
	switch(CanonicalizationMethod)
	{
		case WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
			break;
		case WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
			break;
		case EXC_WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			break;
		case EXC_WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			break;
		default:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
	}
	cur = xmlAddChild(parent,cur);

	/*
	 * Reference
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
	cur = xmlAddChild(parent,cur);
	xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)"#HTMLData");
	parent = cur;

	/*
	 * Transforms
	 */
	
	cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	 * Transform
	 */
	
	cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
	xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_BASE64);
	cur = xmlAddChild(parent,cur);

	if (AddWindowImageFlag == TRUE)
        AddWindowImage(sigNode, signedInfoNode, charSigId);

	if (PhysicalSigUsage != NO_PHYSICAL_SIG)
		AddPhysicalSignature(sigNode, signedInfoNode, charSigId);

	short tmpEnvFlag = EnvelopingFlag;
	EnvelopingFlag = ENVELOPED;

	if (!(CreateSigFromTmplBlob(
								doc,
								(char *)charSigId, &signedXML, &iSize)))
	{
		if (signedXML != NULL)
			zFree(signedXML);
		EnvelopingFlag = tmpEnvFlag;
		if (freeCharSigId)
			zFree(charSigId);
		ExitObjectLog;
		return S_FALSE;
	}
	EnvelopingFlag = tmpEnvFlag;

	*signedHTML = A2WBSTR((LPCSTR)signedXML, iSize);
	if (Base64EncodeXML == TRUE)
		zFree(signedXML);
	else
		xmlFree(signedXML);
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return S_OK;
}
#endif

STDMETHODIMP CSignature::SecureXMLVerify(BSTR signedXML, BSTR *verificationResponse)
{
	int i,j,refNum=0, totalLocNum=0, failedLocNum=0;
	PURI_STATUS *refArr=NULL;
	PURI_PATH uriPath=NULL;
	long sigStatus;

#ifdef LOG_WS
	char charTempFileName[MAX_PATH];
	char xmlTempFileName[MAX_PATH];
	BSTR bstrTempFileName, returnBstrTempFileName;
#endif

	xmlDocPtr doc= NULL;
	xmlNodePtr cur=NULL, rootNode=NULL, parent=NULL, commNode=NULL;
	xmlNsPtr curNs=NULL;
	xmlChar *mem=NULL;
	xmlDtdPtr dtd=NULL;
	int iSize=0;
	char buffer[200];
	unsigned char *ptr, *newPtr=NULL, *curPtr=NULL;
	unsigned int *szPtr;
	unsigned int sizeM;
	BOOL freeNewPtr=FALSE;

	unsigned char *pbData=NULL, *pbDocument=NULL, *plainTextHex=NULL;

	USES_CONVERSION;

	EnterObjectLog;
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		*verificationResponse = A2WBSTR((LPCSTR)"<?xml version=\"1.0\" ?>\n<Error>Invalid SecureXML License</Error>");
		return S_FALSE;
	}
	if (!LicObj.getVerifyAllowed()) {
		setError(SigHandle, NO_VERIFICATION_LIC);
		*verificationResponse = A2WBSTR((LPCSTR)"<?xml version=\"1.0\" ?>\n<Error>No SecureXML Verification License</Error>");
		return S_FALSE;
	}

	if ((signedXML == NULL) || (SysStringByteLen(signedXML) == 0))
	{
		setError(SigHandle, XML_PARSER_ERROR);
		*verificationResponse = A2WBSTR((LPCSTR)"<?xml version=\"1.0\" ?>\n<Error>XML Parser Error</Error>");
		return S_FALSE;
	}

	if (Base64EncodeXML == TRUE)
	{
		ptr = HeapW2A(signedXML);
		sizeM = strlen((const char *)ptr);
		sizeM = base64decodeSize(sizeM);
		if(!(newPtr = (BYTE *)zMalloc(sizeM+1)))
		{
			zFree(ptr);
			*verificationResponse = A2WBSTR((LPCSTR)"<?xml version=\"1.0\" ?>\n<Error>Out of memory</Error>");
			return S_FALSE;
		}
		freeNewPtr = TRUE;
		if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
		{
			zFree(ptr);
			zFree(newPtr);
			setError(SigHandle, BASE64_ERROR);
			*verificationResponse = A2WBSTR((LPCSTR)"<?xml version=\"1.0\" ?>\n<Error>Base64 Decode Error</Error>");
			return S_FALSE;
		}
		zFree(ptr);
	}
	else
	{
		ptr = (unsigned char *)signedXML;
		szPtr = (unsigned int *)(ptr - sizeof(int));
		sizeM = (*szPtr);

		if (((*ptr == 0xff) && (*(ptr +1) == 0xfe)) ||
			((*ptr == 0xfe) && (*(ptr +1) == 0xff)))
		{
			// There is no need to put the UTF 16 header since the data is already in utf-16 format
			newPtr = ptr;
		}
		else
		{
			newPtr = (unsigned char *)zMalloc(sizeM + 4);
			freeNewPtr = TRUE;

			FileEncoding(newPtr);
//			*newPtr = 0xFF;
//			*(newPtr + 1) = 0xFE;

			memcpy(newPtr+2, ptr, sizeM + 2);
			sizeM += 4;
		}
	}

#ifdef LOG_WS
	GetTempFileName((LPCTSTR)"C:\\temp\\SecureXML_WS_LOGS", "sxvf", 0, (char *)charTempFileName);
	bstrTempFileName = A2WBSTR((LPCSTR)charTempFileName);
	SaveXMLStr(signedXML, bstrTempFileName, &returnBstrTempFileName);
	strcpy(xmlTempFileName, charTempFileName);
	strcat(xmlTempFileName, (char *)".xml");
	MoveFile((LPCTSTR)charTempFileName, xmlTempFileName);
	SysFreeString(bstrTempFileName);
#endif

	SigHandle->locArray = uriArr;
	SigHandle->locNumber = totalUriCount;


	if (HMACKey.Length() == 0)
		sigStatus = (BOOL) axVerify((const unsigned char *)newPtr, sizeM, NULL, IgnoreIncompleteSignature, SigIndexToVerify, DetailedVerificationReportFlag, SigHandle);
	else
	{
		/*
		 * This might not work on Windows 95/98
		 */
		xsCoreSetCSP((unsigned char *)"Microsoft Enhanced Cryptographic Provider v1.0",SigHandle);
		sigStatus = (BOOL) axVerify((const unsigned char *)newPtr, sizeM, &HMACPassword, IgnoreIncompleteSignature, SigIndexToVerify, DetailedVerificationReportFlag, SigHandle);
	}
	if (freeNewPtr)
		zFree(newPtr);

	//if (DetailedVerificationReportFlag == TRUE)
	//	FetchSignatureStatus(sigStatus);
	//else
	//	sgArr = axGetSignature(&signum, SigHandle); // Get the full signature stats
	FetchSignatureStatus(sigStatus, DetailedVerificationReportFlag);

	doc = xmlNewDoc((const unsigned char *)"1.0");
	// document, namespace, element name, element content
	cur = xmlNewDocNode(doc,NULL,(const unsigned char *)"XMLSignatureVerificationResponse",NULL);

	// if you want any namespace definition here
	curNs = xmlNewNs(cur,(const unsigned char *)"http://www.infomosaic.net/XMLSign/VerifyResponse/DTD.htm",NULL/*(const unsigned char *)"infomosaic"*/);
	//xmlSetNs(cur,curNs);

	// add root element
	xmlDocSetRootElement(doc,cur);
	rootNode = cur;

	// add some comment
	commNode = xmlNewDocComment(doc,(const unsigned char *)"1.2 Verified by Infomosaic SecureXML http://www.infomosaic.net");
	cur = xmlAddChild(rootNode,commNode);
	/*
	 * SignatureCount
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"SignatureCount"); // Using the parent element's name space
	cur = xmlAddChild(rootNode,cur);
	itoa(signum, (char *)buffer, 10);
	xmlNodeSetContent(cur,(const unsigned char *)buffer);

	if (signum == 0) // No signature was found or XML error
	{
		/*
		* SignatureStatus
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"SignatureStatus"); // Using the parent element's name space
		cur = xmlAddChild(rootNode,cur);

		/*
		* subnodes of SignatureStatus
		*/
		parent = cur;
		cur = xmlNewNode(NULL,(const unsigned char *)"SignatureId");
		cur = xmlAddChild(parent,cur);
		cur = xmlNewNode(NULL,(const unsigned char *)"SignatureAlgorithm");
		cur = xmlAddChild(parent,cur);	
		cur = xmlNewNode(NULL,(const unsigned char *)"Status");
		// Add signature status value of failed
		itoa(FALSE, (char *)buffer, 10);
		xmlNodeSetContent(cur,(const unsigned char *)buffer);
		cur = xmlAddChild(parent,cur);

		cur = xmlNewNode(NULL,(const unsigned char *)"LastError");
		// Add last error code
		itoa(axGetLastError(SigHandle), (char *)buffer, 10);
		xmlNodeSetContent(cur,(const unsigned char *)buffer);
		cur = xmlAddChild(parent,cur);

		if (axGetLastError(SigHandle) != 0)
		{
			// add comment with additional errors
			commNode = xmlNewDocComment(doc,(const unsigned char *)axGetError(SigHandle));
			cur = xmlAddChild(parent,commNode);
		}

		
		cur = xmlNewNode(NULL,(const unsigned char *)"ReferenceCount");
		// Set reference count to zero
		xmlNodeSetContent(cur,(const unsigned char *)"0");
		cur = xmlAddChild(parent,cur);
		cur = xmlNewNode(NULL,(const unsigned char *)"Reference");
		cur = xmlAddChild(parent,cur);
	}
	else // There was at least one signature in the document
	{
		for (i=0; i<signum; i++) // For each signature in the document
		{
			refNum = sgArr[i]->refNumber; // Number of URI in this signature
			refArr = sgArr[i]->refArray;  // The URI Array itself

		    /*
			 * SignatureStatus
			 */
			cur = xmlNewNode(NULL,(const unsigned char *)"SignatureStatus"); // Using the parent element's name space
			cur = xmlAddChild(rootNode,cur);

			/*
			* subnodes of SignatureStatus
			*/
			parent = cur;
			cur = xmlNewNode(NULL,(const unsigned char *)"SignatureId");

			if (sgArr[i]->sigId != NULL)
			{
				xmlNodeSetContent(cur,(const unsigned char *)sgArr[i]->sigId);
			}
			cur = xmlAddChild(parent,cur);
				
			cur = xmlNewNode(NULL,(const unsigned char *)"SignatureAlgorithm");
			if (sgArr[i]->sigMethod != NULL)
			{
				xmlNodeSetContent(cur,(const unsigned char *)sgArr[i]->sigMethod);
			}
			cur = xmlAddChild(parent,cur);
			
			cur = xmlNewNode(NULL,(const unsigned char *)"Status");
			long certStatus=0;

			if ((CertVerifyParams.verificationOptions & (~VERIFY_CRL_REC)) &&
				(sgArr[i]->status != FALSE) && (sgArr[i]->certificatesCount != 0))
			{
				sigStatus = 0;
				get_SigCertStatus(i, NULL, 0, &certStatus);
				if (certStatus != 0)
				{
					// Add signature status value of failed
					itoa(FALSE, (char *)buffer, 10);
					sgArr[i]->status = FALSE;
				}
				else
					itoa(TRUE, (char *)buffer, 10);
			}
			else
				itoa(sgArr[i]->status, (char *)buffer, 10);

			xmlNodeSetContent(cur,(const unsigned char *)buffer);
			cur = xmlAddChild(parent,cur);

			cur = xmlNewNode(NULL,(const unsigned char *)"LastError");
			if ((CertVerifyParams.verificationOptions & (~VERIFY_CRL_REC)) &&
				(certStatus != 0))
			{
				itoa(certStatus, (char *)buffer, 10);
			}
			else
				itoa(sgArr[i]->lasterror, (char *)buffer, 10);

			xmlNodeSetContent(cur,(const unsigned char *)buffer);
			cur = xmlAddChild(parent,cur);	

			if ((axGetLastError(SigHandle) != 0) && (CertVerifyParams.verificationOptions & (~VERIFY_CRL_REC)) &&
				(certStatus != 0))
			{
				// add comment with additional errors
				unsigned char * errStr = axGetError(SigHandle);
				commNode = xmlNewDocComment(doc,(const unsigned char *)errStr);
				zFree(errStr);
				cur = xmlAddChild(parent,commNode);
			}
			else
				if (sgArr[i]->lasterror != 0)
				{
					commNode = xmlNewDocComment(doc,(const unsigned char *)errorMsgTable[sgArr[i]->lasterror]);
					cur = xmlAddChild(parent,commNode);
				}
					

			cur = xmlNewNode(NULL,(const unsigned char *)"ReferenceCount");
			itoa(refNum, (char *)buffer, 10);
			xmlNodeSetContent(cur,(const unsigned char *)buffer);
			cur = xmlAddChild(parent,cur);

			if (sgArr[i]->signerCert != NULL)
			{
				unsigned char *utf8CharStr=NULL;
				int	utf8CharStrLen=0, utf16CharStrLen=0, utf16StrByteLen=0;

				cur = xmlNewNode(NULL,(const unsigned char *)"CertificateInfo");
				cur = xmlAddChild(parent,cur);
				// Adding subnodes of CertificateInfo
				parent = cur;
				cur = xmlNewNode(NULL,(const unsigned char *)"Subject");
				if (sgArr[i]->certificatesCount != 0)
					if ((utf16CharStrLen = wcslen(sgArr[i]->signerCert->subject)) != 0)
					{
						utf16StrByteLen = utf16CharStrLen * 2;
						utf8CharStrLen = utf16StrByteLen * 2;
						utf8CharStr = (unsigned char *)zMalloc(utf8CharStrLen);
						memset(utf8CharStr, 0, utf8CharStrLen);
						UTF16LEToUTF8(utf8CharStr, &utf8CharStrLen, (const unsigned char *)sgArr[i]->signerCert->subject, &utf16StrByteLen);
						xmlNodeSetContent(cur,(const unsigned char *)utf8CharStr);
						zFree(utf8CharStr);
					}
				cur = xmlAddChild(parent,cur);

				cur = xmlNewNode(NULL,(const unsigned char *)"ShortSubject");
				if (sgArr[i]->certificatesCount != 0)
					if ((utf16CharStrLen = wcslen(sgArr[i]->signerCert->shortSubject)) != 0)
					{
						utf16StrByteLen = utf16CharStrLen * 2;
						utf8CharStrLen = utf16StrByteLen * 2;
						utf8CharStr = (unsigned char *)zMalloc(utf8CharStrLen);
						memset(utf8CharStr, 0, utf8CharStrLen);
						UTF16LEToUTF8(utf8CharStr, &utf8CharStrLen, (const unsigned char *)sgArr[i]->signerCert->shortSubject, &utf16StrByteLen);
						xmlNodeSetContent(cur,(const unsigned char *)utf8CharStr);
						zFree(utf8CharStr);
					}
					//if (sgArr[i]->signerCert->subject != NULL)
					//	xmlNodeSetContent(cur,(const unsigned char *)sgArr[i]->signerCert->shortSubject);
				cur = xmlAddChild(parent,cur);

				cur = xmlNewNode(NULL,(const unsigned char *)"CertificateIssuer");
				if (sgArr[i]->certificatesCount != 0)
					if ((utf16CharStrLen = wcslen(sgArr[i]->signerCert->issuer)) != 0)
					{
						utf16StrByteLen = utf16CharStrLen * 2;
						utf8CharStrLen = utf16StrByteLen * 2;
						utf8CharStr = (unsigned char *)zMalloc(utf8CharStrLen);
						memset(utf8CharStr, 0, utf8CharStrLen);
						UTF16LEToUTF8(utf8CharStr, &utf8CharStrLen, (const unsigned char *)sgArr[i]->signerCert->issuer, &utf16StrByteLen);
						xmlNodeSetContent(cur,(const unsigned char *)utf8CharStr);
						zFree(utf8CharStr);
					}
					//if (sgArr[i]->signerCert->issuer != NULL)
					//	xmlNodeSetContent(cur,(const unsigned char *)sgArr[i]->signerCert->issuer);
				cur = xmlAddChild(parent,cur);
				
				cur = xmlNewNode(NULL,(const unsigned char *)"CertificateSerialNumber");
				if (sgArr[i]->certificatesCount != 0)
					if (sgArr[i]->signerCert->serialNumber != NULL)
					{
						if (CertSerialNumberFormat == CERT_SERIAL_PLAIN_HEX)
						{
							plainTextHex = Base64BinToPlainHex(sgArr[i]->signerCert->serialNumber);
							xmlNodeSetContent(cur,(const unsigned char *)plainTextHex);
							zFree(plainTextHex);
						}
						else
							xmlNodeSetContent(cur,(const unsigned char *)sgArr[i]->signerCert->serialNumber);
					}
				cur = xmlAddChild(parent,cur);
				
				cur = xmlNewNode(NULL,(const unsigned char *)"CertificateExpiration");
				if (sgArr[i]->certificatesCount != 0)
					if (sgArr[i]->signerCert->notAfter != NULL)
						xmlNodeSetContent(cur,(const unsigned char *)sgArr[i]->signerCert->notAfter);
				cur = xmlAddChild(parent,cur);
				parent = parent->parent;
			}


			for (j=0; j<refNum; j++) // for each reference that was signed
			{

				cur = xmlNewNode(NULL,(const unsigned char *)"Reference");
				cur = xmlAddChild(parent,cur);

				// Add subnodes of Reference
				parent = cur;

				cur = xmlNewNode(NULL,(const unsigned char *)"URI");
				if (refArr[j]->URI != NULL)
				{
					xmlNodeSetContent(cur,(const unsigned char *)refArr[j]->URI);
				}
				cur = xmlAddChild(parent,cur);

				cur = xmlNewNode(NULL,(const unsigned char *)"DigestMethod");
				if (refArr[j]->digestMethod != NULL)
				{
					xmlNodeSetContent(cur,(const unsigned char *)refArr[j]->digestMethod);
				}
				cur = xmlAddChild(parent,cur);
				
				cur = xmlNewNode(NULL,(const unsigned char *)"DigestStatus");
				itoa(refArr[j]->status, (char *)buffer, 10);
				xmlNodeSetContent(cur,(const unsigned char *)buffer);
				cur = xmlAddChild(parent,cur);

				
				cur = xmlNewNode(NULL,(const unsigned char *)"SignedObject");
				if (refArr[j]->refObject != NULL)
				{
					if (refArr[j]->refObject->encoding != NULL)
						xmlNewProp(cur, (const unsigned char *)"Encoding", (const unsigned char *)refArr[j]->refObject->encoding);
					if (refArr[j]->refObject->encodedData != NULL)
					{
						xmlNodeSetContent(cur,(const unsigned char *)refArr[j]->refObject->encodedData);
					}
				}
				cur = xmlAddChild(parent,cur);
				parent = parent->parent;
			} // end for each reference

			cur = xmlNewNode(NULL,(const unsigned char *)"PropertyCount");
			itoa(sgArr[i]->propNumber, (char *)buffer, 10);
			xmlNodeSetContent(cur,(const unsigned char *)buffer);
			cur = xmlAddChild(parent,cur);

			cur = xmlNewNode(NULL,(const unsigned char *)"SignatureProperties");
			cur = xmlAddChild(parent,cur);

			// Add subnodes of SignatureProperties
			parent = cur;

			char *charTsProp;
			char *equalPtr;

			for (j = 0; j < sgArr[i]->propNumber;  j++)
			{
				// Adding Signature properties
				cur = xmlNewNode(NULL,(const unsigned char *)"Property");
				cur = xmlAddChild(parent,cur);

				// Adding subnodes of Property
				parent = cur;
				charTsProp = (char *)sgArr[i]->propArray[j];

				equalPtr = StrChr(charTsProp, '=');
				*equalPtr = '\0';

				cur = xmlNewNode(NULL,(const unsigned char *)"Name");
				xmlNodeSetContent(cur,(const unsigned char *)charTsProp);
				cur = xmlAddChild(parent,cur);

				cur = xmlNewNode(NULL,(const unsigned char *)"Value");
				xmlNodeSetContent(cur,(const unsigned char *)(equalPtr+1));
				*equalPtr = '='; //Restore the value

				cur = xmlAddChild(parent,cur);
				parent = parent->parent;
			}

		} /* end for each signature in the document loop */
	}
	xmlDocDumpMemoryEnc(doc,&mem,&iSize, "UTF-16");
	*verificationResponse = SysAllocStringByteLen((LPCSTR)mem, iSize);
	xmlFreeDoc(doc);
	xmlFree(mem);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::SetCSP(BSTR CSPName)
{
USES_CONVERSION;
	
	CComBSTR tmpNewVal;

	EnterObjectLog;
	tmpNewVal = CSPName;
	if (tmpNewVal.Length() == 0)
	{
		setError(SigHandle, INVALID_CSP);
		return S_FALSE;
	}
	unsigned char *wCSPName = HeapW2A(CSPName);
	xsCoreSetCSP(wCSPName, SigHandle);
	zFree(wCSPName);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::GetSignedHTML(BSTR signedHtmlXML, BSTR *originalHTML)
{
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL;
	char *encodedHTML=NULL;
	DWORD  dwBytesToWrite;
	char *decodedDataPtr=NULL;
	char *charSignedHtmlXML;
	CComBSTR tmpSignedXML;

	EnterObjectLog;
	tmpSignedXML = signedHtmlXML;
	if (tmpSignedXML.Length() == 0)
	{
		setError(SigHandle, XML_PARSER_ERROR);
		return S_FALSE;
	}

	USES_CONVERSION;

	charSignedHtmlXML = (char *)HeapW2A(signedHtmlXML);
	// parse main document
	doc = xmlParseMemory((const char *)charSignedHtmlXML,strlen(charSignedHtmlXML));
	zFree(charSignedHtmlXML);
	if (!doc) {
		setError(SigHandle, XML_PARSER_ERROR);
		return S_FALSE;
	}
	root = xmlDocGetRootElement(doc);
	cur = root->xmlChildrenNode;
	while (cur)
	{
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "SignedHTML"))) {
			// content
			encodedHTML = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			break;
		}
		cur = cur->next;
	}
	if (encodedHTML != NULL)
	{
		dwBytesToWrite = base64decodeSize((DWORD)strlen((const char *)encodedHTML));
		decodedDataPtr = (char *)zMalloc (dwBytesToWrite+1);
		memset(decodedDataPtr,0,dwBytesToWrite+1);
		dwBytesToWrite = base64decode((unsigned char *)encodedHTML,(unsigned char *)decodedDataPtr,dwBytesToWrite);
		*originalHTML = A2WBSTR((LPCSTR)decodedDataPtr);
		zFree(decodedDataPtr);
		zFree(encodedHTML);
	}
	xmlFreeDoc(doc);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::SignFile(BSTR inputFile, BSTR outputFile)
{
	DS_DATA_BLOB crBlob;
	DWORD fileSize=0;
	unsigned char *binFileData;
	unsigned char *signedXML;
	FILE *hFile;
	unsigned int writeResult;
	unsigned char *bareFileName=NULL;
	char *charSigId;
	xmlValidCtxtPtr ctxt;
	xmlDtdPtr dtd =NULL;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	char objectId[50];

	EnterObjectLog;
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (!LicObj.getSignAllowed()) {
		setError(SigHandle, NO_SIGNING_LIC);
		return S_FALSE;
	}

	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	xmlDocPtr doc= NULL;
	xmlNodePtr cur=NULL, rootNode=NULL, parent=NULL, commNode=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlNsPtr curNs=NULL;
	xmlChar *mem=NULL;
	int iSize=0;

	crBlob.cbData = 0;
	crBlob.pbData = NULL;

USES_CONVERSION;

/* To be Added by Alex
<!DOCTYPE InfomosaicSecureXML [
  <!ATTLIST SignedHTML Id ID #IMPLIED>
]>

*/

//	charInputFile = (char *)HeapW2A(inputFile);
	bareFileName = xsRemoveBstrPath(inputFile);
 //	UTF16LEToUTF8(unsigned char* out, int *outlen,
 //           const unsigned char* inb, int *inlenb)
//	bareFileNameLen = SysStringByteLen(inputFile) - ((char *)bareFileName - (char *)inputFile);

	if (ReadAllBin(inputFile, &binFileData, &fileSize) == S_FALSE)
	{
		setError(SigHandle, FILE_NOT_FOUND);
//		zFree(charInputFile);
		return S_FALSE; // File does not exist just return
	}
	//File Exists so lets start the processing

	doc = xmlNewDoc((const unsigned char *)"1.0");
	// DTD
    dtd = xmlNewDtd(doc, BAD_CAST "SignatureEnvelope",NULL,NULL);
	// create DTD validation context
    ctxt = xmlNewValidCtxt();
	// add ATTLIST
	xmlAddAttributeDecl(ctxt, dtd, BAD_CAST "infomosaic:SignedObject",
                    BAD_CAST "Id", NULL, 
					XML_ATTRIBUTE_ID, XML_ATTRIBUTE_IMPLIED, 
					NULL, NULL);		    
	
    xmlAddChild((xmlNodePtr) doc, (xmlNodePtr) dtd);
	xmlFreeValidCtxt(ctxt);

	// document, namespace, element name, element content
	cur = xmlNewDocNode(doc,NULL,(const unsigned char *)"SignatureEnvelope",NULL);

	// if you want any namespace definition here
	curNs = xmlNewNs(cur,(const unsigned char *)"http://www.infomosaic.net/SignData/DTD.htm",(const unsigned char *)"infomosaic");
	xmlSetNs(cur,curNs);

	// add root element
	xmlDocSetRootElement(doc,cur);
	rootNode = cur;

	/*
	 * SignedObject
	*/

#ifdef WIN32
	CoCreateGuid(&sigGuid);
	GuidToString(&sigGuid, &objectId[1]);
#else
	uuid_generate(sigGuid);
	uuid_unparse(sigGuid, &objectId[1]);
#endif
	objectId[0] = '#';
	
	cur = xmlNewNode(curNs,(const unsigned char *)"SignedObject"); // Using the parent element's name space
	cur = xmlAddChild(rootNode,cur);
	xmlNewProp(cur, (const unsigned char *)"Encoding", (const unsigned char *)ALG_BASE64);
	xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)&objectId[1]);
	xmlNewProp(cur, (const unsigned char *)"FileName", (const unsigned char *)bareFileName);
	zFree(bareFileName);

//	zFree(charInputFile);
	crBlob.cbData = base64encodeSize(fileSize);
	// allocate memory
	if(!(crBlob.pbData = (unsigned char*)zMalloc(crBlob.cbData+1)))
	{
		setError(SigHandle, MEMORY_FAULT);
		zFree(binFileData);
		xmlFreeDoc(doc);
		return S_FALSE;
	}
	if (base64encode((unsigned char *)binFileData,fileSize,(unsigned char*)crBlob.pbData,crBlob.cbData)==-1) 
	{
		setError(SigHandle, MEMORY_FAULT);
		zFree(crBlob.pbData);
		zFree(binFileData);
		xmlFreeDoc(doc);
		return S_FALSE;
	}
	*(crBlob.pbData+crBlob.cbData)='\0';

	zFree(binFileData);

	xmlNodeSetContent(cur,(const unsigned char *)crBlob.pbData);

	zFree(crBlob.pbData);
	crBlob.pbData = NULL;

	/*
	 * Signature
	*/

	BOOL freeCharSigId = FALSE;
	if (SignatureID.Length() == 0)
	{
#ifdef WIN32
		CoCreateGuid(&sigGuid);
		GuidToString(&sigGuid, guidStr);
#else
		uuid_generate(sigGuid);
		uuid_unparse(sigGuid, guidStr);
#endif
		charSigId = guidStr;
	}
	else
	{
		charSigId = (char *)HeapW2A(SignatureID.m_str);
		freeCharSigId = TRUE;
	}

	cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
	sigNode = cur;
	xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
	cur = xmlAddChild(rootNode,cur);
	xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
	parent = cur;

	/*
	 * SignedInfo
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
	signedInfoNode = cur;
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	 * Canonicalization Method
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
	switch(CanonicalizationMethod)
	{
		case WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
			break;
		case WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
			break;
		case EXC_WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			break;
		case EXC_WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			break;
		default:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
	}
	cur = xmlAddChild(parent,cur);
	/*
	 * Reference
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
	cur = xmlAddChild(parent,cur);
	xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)objectId);
	parent = cur;

	/*
	 * Transforms
	 */
	
	cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	 * Transform
	 */
	
	cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
	xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_BASE64);
	cur = xmlAddChild(parent,cur);

#ifdef WIN32
	if (AddWindowImageFlag == TRUE)
        	AddWindowImage(sigNode, signedInfoNode, charSigId);

	if (PhysicalSigUsage != NO_PHYSICAL_SIG)
		AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif

	short tmpEnvFlag = EnvelopingFlag;
	EnvelopingFlag = ENVELOPED;

	if (!(CreateSigFromTmplBlob(doc, charSigId, &signedXML, &iSize)))
	{
		if (signedXML != NULL)
			xmlFree(signedXML);
		EnvelopingFlag = tmpEnvFlag;
		if (freeCharSigId)
			zFree(charSigId);
		return S_FALSE;
	}
	EnvelopingFlag = tmpEnvFlag;

	// open file in write mode 
//	charOutputFile = W2A(outputFile);

	if (freeCharSigId)
		zFree(charSigId);

#ifdef WIN32
	if ((hFile = _wfopen(outputFile,L"wb"))==NULL) {
#elif UNIX
	unsigned char *utf8File = HeapW2A(outputFile);
	if ((hFile = fopen((const char *)utf8File, "wb")) == NULL) {
		zFree(utf8File);
#endif
		setError(SigHandle, IO_ERROR);
		return S_FALSE;
	}
#ifdef UNIX
	zFree(utf8File);
#endif

	fileSize = iSize;

	if ((writeResult = fwrite(signedXML, 1, fileSize, hFile)) == 0)
	{
		setError(SigHandle, IO_ERROR);
		xmlFree(signedXML);
		return S_FALSE;
	}
	if (ferror(hFile))
	{
		setError(SigHandle, IO_ERROR);
		xmlFree(signedXML);
		return S_FALSE;
	}
	fclose(hFile);
	if (Base64EncodeXML == TRUE)
		zFree(signedXML);
	else
		xmlFree(signedXML);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::GetSignedFileObject(BSTR signedXML, BSTR saveDir, BSTR *signedFilePath)
{
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL;
	char *signedFileName=NULL;
	char *encodedFileData=NULL;
	DWORD  dwBytesToWrite;
	char *decodedDataPtr=NULL;
	WCHAR *fullFilePath=NULL;
	FILE *hFile; 
	BOOL writeResult;
	char *charSignedXML=NULL;
	char *charSaveDir=NULL;
	CComBSTR tmpSignedXML;
	unsigned char *ptr, *newPtr=NULL, *curPtr=NULL; 
	unsigned int *szPtr;
	unsigned int sizeM;
	BOOL freeNewPtr = FALSE;

	EnterObjectLog;
	*signedFilePath = 	A2WBSTR((const char *) NULL);

	
	tmpSignedXML = signedXML;
	if (tmpSignedXML.Length() == 0)
	{
		setError(SigHandle, XML_PARSER_ERROR);
		return S_FALSE;
	}
	if (Base64EncodeXML == TRUE)
	{
		ptr = HeapW2A(signedXML);
		sizeM = strlen((const char *)ptr);
		sizeM = base64decodeSize(sizeM);
		if(!(newPtr = (BYTE *)zMalloc(sizeM+1)))
		{
			zFree(ptr);
			return S_FALSE;
		}
		freeNewPtr = TRUE;
		if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
		{
			zFree(ptr);
			zFree(newPtr);
			setError(SigHandle, BASE64_ERROR);
			return S_FALSE;
		}
		zFree(ptr);
	}
	else
	{
		ptr = (unsigned char *)signedXML;
		szPtr = (unsigned int *)(ptr - sizeof(int));
		sizeM = (*szPtr);

		if (((*ptr == 0xff) && (*(ptr +1) == 0xfe)) ||
			((*ptr == 0xfe) && (*(ptr +1) == 0xff)))
		{
			// There is no need to put the UTF 16 header since the data is already in utf-16 format
			newPtr = ptr;
		}
		else
		{
			newPtr = (unsigned char *)zMalloc(sizeM + 4);
			freeNewPtr = TRUE;

			FileEncoding(newPtr);
//			*newPtr = 0xFF;
//			*(newPtr + 1) = 0xFE;

			memcpy(newPtr+2, ptr, sizeM + 2);
			sizeM += 4;
		}
	}

	USES_CONVERSION;

	// parse main document
	doc = xmlParseMemory((const char *)newPtr,sizeM);
	if (freeNewPtr)
		zFree(newPtr);

	if (!doc) 
	{
		setError(SigHandle, XML_PARSER_ERROR);
		return S_FALSE;
	}
	root = xmlDocGetRootElement(doc);
	cur = root->xmlChildrenNode;
	while (cur)
	{
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "SignedObject"))) {
			// content
			signedFileName = (char *)xmlGetProp(cur, (const unsigned char *)"FileName");
			encodedFileData = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			break;
		}
		cur = cur->next;
	}

	if ((signedFileName != NULL) && (encodedFileData != NULL))
	{
		unsigned char *utf16CharStr=NULL;
		int utf16ByteLen=0, utf8ByteLen=0;
		utf8ByteLen = strlen((const char *)signedFileName);
		utf16ByteLen = utf8ByteLen * 2;
		utf16CharStr = (unsigned char *)zMalloc(utf16ByteLen);
		UTF8ToUTF16LE(utf16CharStr, &utf16ByteLen, (const unsigned char*)signedFileName, &utf8ByteLen);
		BSTR bstrSignedFileName = SysAllocStringByteLen((LPCSTR)utf16CharStr, utf16ByteLen);
		zFree(utf16CharStr);
		xmlFree(signedFileName);

		dwBytesToWrite = base64decodeSize((DWORD)strlen((const char *)encodedFileData));
		decodedDataPtr = (char *) zMalloc (dwBytesToWrite+1);
		memset(decodedDataPtr,0,dwBytesToWrite+1);
		dwBytesToWrite = base64decode((unsigned char *)encodedFileData,(unsigned char *)decodedDataPtr,dwBytesToWrite);

		fullFilePath = (WCHAR *)zMalloc(MAX_PATH * 2);
		memset(fullFilePath, 0, MAX_PATH * 2);

		tmpSignedXML.Empty();
		tmpSignedXML = saveDir;
		if (tmpSignedXML.Length() == 0)
		{
			GetTempPathW((DWORD)MAX_PATH, fullFilePath);
		}
		else
		{
//			charSaveDir = W2A(saveDir);
			wcscat(fullFilePath, saveDir);
			wcscat(fullFilePath, (const WCHAR *)L"\\");
		}

		wcscat(fullFilePath, (const WCHAR *)bstrSignedFileName);
		SysFreeString(bstrSignedFileName);

		// open file in write mode 
#ifdef WIN32
		if ((hFile = _wfopen(fullFilePath,L"wb"))==NULL) {
#elif UNIX
		unsigned char *utf8FilePath = HeapWCHAR2A(fullFilePath);
		if ((hFile = fopen((const char *)utf8FilePath, "wb")) == NULL) {
			zFree(utf8FilePath);
#endif
			
			setError(SigHandle, IO_ERROR);
			zFree(decodedDataPtr);
			xmlFree(encodedFileData);
			zFree(fullFilePath);
			xmlFreeDoc(doc);
			return S_FALSE;
		}
#ifdef UNIX
		zFree(utf8FilePath);
#endif

		if ((writeResult = fwrite(decodedDataPtr, 1, dwBytesToWrite, hFile)) == 0)
		{
			setError(SigHandle, IO_ERROR);
			zFree(decodedDataPtr);
			xmlFree(encodedFileData);
			zFree(fullFilePath);
			xmlFreeDoc(doc);
			return S_FALSE;
		}
		if (ferror(hFile))
		{
			setError(SigHandle, IO_ERROR);
			zFree(decodedDataPtr);
			xmlFree(encodedFileData);
			zFree(fullFilePath);
			xmlFreeDoc(doc);
			return S_FALSE;
		}

		fclose(hFile);
		zFree(decodedDataPtr);
		xmlFree(encodedFileData);
		*signedFilePath = SysAllocString((const OLECHAR *)fullFilePath);
		TEMP_FILE_INFO *tmpFilePath = new (TEMP_FILE_INFO);
		wcscpy((WCHAR *)tmpFilePath->fileName, fullFilePath);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
		zFree(fullFilePath);
	}
	xmlFreeDoc(doc);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::SetStoreName(BSTR storeName)
{
	CComBSTR tmpStoreName;
	unsigned char *tmpCharPtr;
	EnterObjectLog;
	tmpStoreName = storeName;
	if (tmpStoreName.Length() == 0)
	{
		setError(SigHandle, NO_CERT_STORE);
		return S_FALSE;
	}

	//free cV and SigHandle
	if ((UsingNetscape == FALSE) || (allowedCertIssuerCount != 0))
		if (cV != NULL)
		{
			for (int i=0; i<CertificateCount; i++)
			{
				if (cV[i] != NULL)
				{
					if (cV[i]->certificate != NULL)
						zFree(cV[i]->certificate);
					zFree(cV[i]);
				}
			}
			zFree(cV);
			cV = NULL;
		}
#ifdef WIN32
	//free showselect cert obj
	if (CertificateCount != 0)
		if (dlg != NULL)
			delete dlg;
#endif

	if (SigHandle != NULL)
	{
		axFree(SigHandle);
		SigHandle = NULL;
	}

	StoreName = storeName;

	//do all initialization
	int numCerts;
	PCERT_DESCR *certPtr;

	sgArr=NULL;
	err=0;
	signum=0;
	uriArr=NULL;
	failedUriArr=NULL;
	failedUriCount=0;
	totalUriCount = 0;

	CertificateCount = 0;
	CurrentCertificate = NOT_INITIALIZED;

	USES_CONVERSION;
#ifdef NSS
	unsigned char *nsp = (unsigned char *)HeapW2A(nsStorePassword);
	if (!nsp) {
		nsp = (unsigned char *)zMalloc(sizeof(char));
		*nsp = '\0';
	}
	SigHandle = axInit(nsp, HeapW2A(storeName));
	if (!SigHandle) {
	   throw SigException("Library initialization failed");
	}	

	zFree((void *)nsp);
#else
	SigHandle = axInit();
#endif
	SigHandle->useFastC14N=TRUE;

	tmpCharPtr = HeapW2A(StoreName.m_str);

	if (strcmp((const char *)tmpCharPtr, NETSCAPESTORE))
	{
#ifdef WIN32
		// Store name is not Netscape
		if ((UsingNetscape == TRUE) && (nsCertStoreObj != NULL))
		{
			nsCertStoreObj->Release();
			CoUninitialize();
		}
#endif
		UsingNetscape = FALSE;
#ifdef NSS
		if ((certPtr = axGetCertificateList(tmpCharPtr, &numCerts, SigHandle )) != NULL)
#else
		if ((certPtr = axGetCertificateList(tmpCharPtr, &numCerts )) != NULL)
#endif
		{
			CertificateCount = (long) numCerts;
			if (numCerts > 0)
				cVSigner = certPtr;
			else
			{
				cVSigner = NULL;
				//return;
			}
		}
	}
	else // The store name is Netscape hence do the netscape cert processing
	{
#ifdef NSS
		UsingNetscape = FALSE;
		if ((certPtr = axGetCertificateList(tmpCharPtr, &numCerts, SigHandle )) != NULL)
		{
			CertificateCount = (long) numCerts;
			if (numCerts > 0)
				cVSigner = certPtr;
			else
			{
				cVSigner = NULL;
			}
		}
#else
		IUnknown *pUnknown;
#ifdef WIN32
		if ((UsingNetscape == TRUE) && (nsCertStoreObj != NULL))
		{
			nsCertStoreObj->Release();
			CoUninitialize();
		}

		CoInitialize(NULL);
		HRESULT hr = CoCreateInstance(__uuidof(CCertStore), NULL, CLSCTX_LOCAL_SERVER, 
							IID_IUnknown, (void **) &pUnknown);
		if (FAILED(hr))
		{
			UsingNetscape = FALSE;
			CoUninitialize();
			return S_FALSE;
		}

		hr = pUnknown->QueryInterface(__uuidof(ICertStore), (void **) &nsCertStoreObj);
		if (FAILED(hr))
		{
			pUnknown->Release();
			UsingNetscape = FALSE;
			CoUninitialize();
			return S_FALSE;
		}
		pUnknown->Release();

		nsCertStoreObj->NetscapeStorePassword = nsStorePassword;
//		DebugBreak();
		//VARIANT varCertList;
		//VariantInit(&varCertList);
		//varCertList = nsCertStoreObj->GetCertificateList((unsigned long *)&numCerts);
		BSTR bstrCertListXml = (BSTR) nsCertStoreObj->GetCertificateList((unsigned long *)&numCerts);
		CertificateCount = (long) numCerts;
		if (numCerts > 0)
		{
			//CBufferVariant m_binaryData;
			UsingNetscape = TRUE;
			PCERT_DESCR *certList = (PCERT_DESCR *)zMalloc(CertificateCount * sizeof(PCERT_DESCR));
			unsigned char *certListXml = HeapW2A(bstrCertListXml);
			xmlDocPtr doc = xmlParseMemory((const char *)certListXml, strlen((const char *)certListXml));
			zFree(certListXml);
			xmlNodePtr root = xmlDocGetRootElement(doc);
			xmlNodePtr cur = root->xmlChildrenNode;
			xmlNodePtr parent = cur;
			int certIndex = 0;
			while ((cur) && (certIndex < CertificateCount))
			{
				if (!(xmlStrcmp(cur->name, (const xmlChar *) "Certificate"))) {
					PCERT_DESCR certDescPtr = (PCERT_DESCR)zMalloc(sizeof(CERT_DESCR));
					certList[certIndex++] = certDescPtr;
					// content
					parent = cur;
					cur = cur->children;
					for (;cur != NULL; cur = cur->next)
					{
						if (!(xmlStrcmp(cur->name, (const xmlChar *)"SerialNumber")))
						{
							char *serialNumber = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
							strcpy((char *)certDescPtr->serialNumber, (const char *)serialNumber);
							xmlFree(serialNumber);
						}
						if (!(xmlStrcmp(cur->name, (const xmlChar *)"Issuer")))
						{
							char *issuer = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
							BSTR bstrIssuer = (BSTR)zMalloc(512*2);
							memset(bstrIssuer, 0, 512*2);
							MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)issuer, strlen((const char *)issuer), bstrIssuer, 512);
							StringCbCopyW(certDescPtr->issuer, 512, bstrIssuer);
							xmlFree(issuer);
							zFree(bstrIssuer);
						}
						if (!(xmlStrcmp(cur->name, (const xmlChar *)"Subject")))
						{
							char *subject = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
							BSTR bstrSubject = (BSTR)zMalloc(512*2);
							memset(bstrSubject, 0, 512*2);
							MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)subject, strlen((const char *)subject), bstrSubject, 512);
							StringCbCopyW(certDescPtr->subject, 512, bstrSubject);
							xmlFree(subject);
							zFree(bstrSubject);
						}
						if (!(xmlStrcmp(cur->name, (const xmlChar *)"ShortSubject")))
						{
							char *shortSubject = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
							BSTR bstrShortSubject = (BSTR)zMalloc(512*2);
							memset(bstrShortSubject, 0, 512*2);
							MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)shortSubject, strlen((const char *)shortSubject), bstrShortSubject, 512);
							StringCbCopyW(certDescPtr->shortSubject, 512, bstrShortSubject);
							xmlFree(shortSubject);
							zFree(bstrShortSubject);
						}
						if (!(xmlStrcmp(cur->name, (const xmlChar *)"NotAfter")))
						{
							char *notAfter = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
							strcpy((char *)certDescPtr->notAfter, (const char *)notAfter);
							xmlFree(notAfter);
						}
						if (!(xmlStrcmp(cur->name, (const xmlChar *)"X509Certificate")))
						{
							char *x509Certificate = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
							certDescPtr->certificate = (unsigned char *)zMalloc(strlen((const char *)x509Certificate) + 1);
							strcpy((char *)certDescPtr->certificate, (const char *)x509Certificate);
							xmlFree(x509Certificate);
						}
					}
				}
				cur = parent->next;
				parent = cur;
			}
			
			//m_binaryData = varCertList;
			//long dataLength = m_binaryData.GetLength();
			//char * dataPtr = (char *)((void *)m_binaryData);
			//char *tmpPtr = dataPtr;

			//PCERT_DESCR *certList= (PCERT_DESCR *)zMalloc(numCerts * sizeof(PCERT_DESCR));
			//for (int i=0; i<numCerts; i++)
			//{
			//	certList[i] = (PCERT_DESCR) zMalloc(sizeof(CERT_DESCR));
			//	memcpy (certList[i], tmpPtr, sizeof(CERT_DESCR));
			//	int certSize = (int)certList[i]->certificate;
			//	certList[i]->certificate = (unsigned char *) zMalloc(certSize);
			//	strcpy((char *)certList[i]->certificate, tmpPtr + sizeof(CERT_DESCR));
			//	tmpPtr += sizeof(CERT_DESCR) + certSize;
			//}
			cVSigner = (PCERT_DESCR *)certList;
		}
		else
		{
			UsingNetscape = FALSE;
			cVSigner = NULL;
			nsCertStoreObj->Release();
			CoUninitialize();
		}
#endif
#endif
	}
	if ((allowedCertIssuerCount != 0) && (CertificateCount != 0))
	{
		int *indexArray = (int *)zMalloc(sizeof(int) * CertificateCount);
		int allowedCertCount = 0;

		for (unsigned int i=0; i < allowedCertIssuerCount; i++)
		{
			for(int j=0; j < CertificateCount; j++)
			{
				if (!strcmp((const char*)allowedCertIssuerNames[i], (const char *)cVSigner[j]->issuer))
				{
					indexArray[allowedCertCount] = j;
					allowedCertCount++;
				}
			}
		}
		for (int i=0; i<CertificateCount; i++)
		{
			BOOL certificateAllowed = FALSE;
			for (int j=0; j<allowedCertCount; j++)
			{
				if (indexArray[j] == i)
				{
					certificateAllowed = TRUE;
					break;
				}
			}
			if ((certificateAllowed == FALSE) && (UsingNetscape == FALSE))
			{
				if (cVSigner[i]->certificate != NULL)
					zFree(cVSigner[i]->certificate);
				zFree(cVSigner[i]);
			}
		}
		CertificateCount = allowedCertCount;
		cV = (PCERT_DESCR *)zMalloc(sizeof(PCERT_DESCR *) * CertificateCount);
		for (int i=0; i<CertificateCount; i++)
			cV[i] = cVSigner[indexArray[i]];
		if (UsingNetscape == FALSE)
			zFree(cVSigner);
		zFree(indexArray);
	}
	else
		cV = cVSigner;
#ifdef WIN32
	// initialise SelectCert
	if (CertificateCount != 0)
	{
		dlg = new CShowSelectCert(/*this,*/ tmpCharPtr, cV, CertificateCount);	
//		dlg->Create(NULL);
	}
#endif
	zFree(tmpCharPtr);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::GetStoreName(BSTR *storeName)
{
	EnterObjectLog;
	*storeName = StoreName.Copy();
	ExitObjectLog;
	return S_OK;
}


STDMETHODIMP CSignature::SignXMLEnveloped(BSTR inputXML, BSTR sigId, BSTR *signedXML)
{
	DS_DATA_BLOB crBlob;
	unsigned char *certData=NULL;
	keyinfo *ki=NULL;
	unsigned char *charSignedXML;
	char *charSigId;
	int charInputLength;
	unsigned char *ptr, *newPtr=NULL, *curPtr=NULL; 
	unsigned int *szPtr;
	unsigned int sizeM;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	
	EnterObjectLog;
	//if (! LicObj.checkLicense()) {
	//	setError(SigHandle, INVALID_SECUREXML_LIC);
	//	return S_FALSE;
	//}
	//if (!LicObj.getSignAllowed()) {
	//	setError(SigHandle, NO_SIGNING_LIC);
	//	return S_FALSE;
	//}

	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	xmlDocPtr doc= NULL;
	xmlNodePtr cur=NULL, rootNode=NULL, parent=NULL, commNode=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlNsPtr curNs=NULL;
	xmlChar *mem=NULL;
	xmlDtdPtr dtd=NULL;
	int iSize=0;

	crBlob.cbData = 0;
	crBlob.pbData = NULL;

USES_CONVERSION;

/* To be Added by Alex
<!DOCTYPE InfomosaicSecureXML [
  <!ATTLIST SignedHTML Id ID #IMPLIED>
]>

*/
	CComBSTR tmpInputXML;

	tmpInputXML = inputXML;
	charInputLength = tmpInputXML.Length();

	if (charInputLength == 0)
	{
		setError(SigHandle, XML_PARSER_ERROR);
		return S_FALSE;
	}

	BOOL freeNewPtr = FALSE;
	if (Base64DecodeXML == FALSE)
	{
		ptr = (unsigned char *)inputXML;
		szPtr = (unsigned int *)(ptr - sizeof(int));
		sizeM = (*szPtr);

		if (((*ptr == 0xff) && (*(ptr +1) == 0xfe)) ||
			((*ptr == 0xfe) && (*(ptr +1) == 0xff)))
		{
			// There is no need to put the UTF 16 header since the data is already in utf-16 format
			newPtr = ptr;
		}
		else
		{
			newPtr = (unsigned char *)zMalloc(sizeM + 4);
			freeNewPtr = TRUE;

			FileEncoding(newPtr);
			memcpy(newPtr+2, ptr, sizeM + 2);
			sizeM += 4;
		}
	}
	else
	{
		ptr = HeapW2A(inputXML);
		sizeM = strlen((const char *)ptr);
		sizeM = base64decodeSize(sizeM);
		newPtr = (unsigned char *)zMalloc(sizeM+1);
		freeNewPtr = TRUE;
		if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
		{
			zFree(ptr);
			zFree(newPtr);
			setError(SigHandle, BASE64_ERROR);
			return S_FALSE;
		}
		zFree(ptr);
	}

	if (! LicObj.getSignAllowed()) 
	{
		if (!LicObj.getFormSignAllowed(newPtr, sizeM, SigHandle))
		{
			setError(SigHandle, NO_SIGNING_LIC);
			return S_FALSE;
		}
	}

	doc = xmlParseMemory((const char *)newPtr,sizeM);
	if (freeNewPtr)
		zFree(newPtr);
	if (!doc) {
		setError(SigHandle,XML_PARSER_ERROR);
		return S_FALSE;
	}
	rootNode = xmlDocGetRootElement(doc);

	/*
	 * Signature
	*/

	tmpInputXML = sigId;

	BOOL freeCharSigId = FALSE;
	if (tmpInputXML.Length() == 0)
		charSigId = NULL;
	else
	{
		charSigId = (char *)HeapW2A(sigId);
		freeCharSigId = TRUE;
	}

	if (charSigId == NULL)
		if (SignatureID.Length() == 0)
		{
#ifdef WIN32
			CoCreateGuid(&sigGuid);
			GuidToString(&sigGuid, guidStr);
#else
			uuid_generate(sigGuid);
			uuid_unparse(sigGuid, guidStr);
#endif
			charSigId = guidStr;
		}
		else
		{
			charSigId = (char *)HeapW2A(SignatureID.m_str);
			freeCharSigId = TRUE;
		}

	cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
	sigNode = cur;
	xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
	cur = xmlAddChild(rootNode,cur);
	xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
	parent = cur;

	/*
	 * SignedInfo
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
	signedInfoNode = cur;
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	 * Canonicalization Method
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
	switch(CanonicalizationMethod)
	{
		case WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
			break;
		case WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
			break;
		case EXC_WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			break;
		case EXC_WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			break;
		default:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
	}
	cur = xmlAddChild(parent,cur);
	/*
	 * Reference
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
	cur = xmlAddChild(parent,cur);
	xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)"");
	parent = cur;

	/*
	 * Transforms
	 */
	
	cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	 * Transform
	 */
	
	if ((CanonicalizationMethod == EXC_WITH_COMMENTS) ||
		(CanonicalizationMethod == EXC_WITHOUT_COMMENTS))
	{
		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		if (CanonicalizationMethod == EXC_WITH_COMMENTS)
		{
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
		}
		else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
		{
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
		}
		cur = xmlAddChild(parent,cur);
		parent = cur;
		if (CanonicalizationMethod == EXC_WITH_COMMENTS)
		{
			cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
			xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_WITH_COMM,(const unsigned char *)"ec");
			xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
		}
		else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
		{
			cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
			xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_NO_COMM,(const unsigned char *)"ec");
			xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
		}
		cur = xmlAddChild(parent,cur);
		parent = parent->parent;
	}

	cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
	xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_ENVELOPED_SIG);
	cur = xmlAddChild(parent,cur);

#ifdef WIN32
	if (AddWindowImageFlag == TRUE)
		AddWindowImage(sigNode, signedInfoNode, charSigId);

	if (PhysicalSigUsage != NO_PHYSICAL_SIG)
		AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif

	short tmpEnvFlag = EnvelopingFlag;
	EnvelopingFlag = ENVELOPED;

	if (!(CreateSigFromTmplBlob(doc, (char *)charSigId, &charSignedXML, &iSize)))
	{
		if (charSignedXML != NULL)
			xmlFree(charSignedXML);
		EnvelopingFlag = tmpEnvFlag;
		if (freeCharSigId)
			zFree(charSigId);
		return S_FALSE;
	}
	else
	{
		if (charSignedXML != NULL)
		{
			unsigned char *dataPtr = charSignedXML;

			if (((*dataPtr == 0xff) && (*(dataPtr +1) == 0xfe)) ||
				((*dataPtr == 0xfe) && (*(dataPtr +1) == 0xff)))
			{
				// This is a UTF-16 file, so no need to do a char * to BSTR conversion
				// Just allocate memory and copy data and put the size information in front
				*signedXML = ::SysAllocStringByteLen((LPCSTR)dataPtr, (UINT)iSize);
				xmlFree(dataPtr);
			}
			else
			{
				*signedXML = A2WBSTR((LPCSTR)dataPtr, iSize);
				if (Base64EncodeXML == TRUE)
					zFree(dataPtr);
				else
					xmlFree(dataPtr);
			}
		}
	}
	EnvelopingFlag = tmpEnvFlag;
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::GetVersion(BSTR *version)
{
// The commented code is to get the right CRC value which then needs to be put
// into the License.cpp verifyLicense() function to protect from dll tamperment
// Every time we choose a different X509 certificate to issue licenses, we need
// to uncomment this portion, change the X509 data, call GetVersion from a client, 
// get the CRC value. Then change License.cpp verifyLicense() function, comment 
// this code again and recompile.

/*
	ULONG crcValue=0xff01ff01;
	char charCRC[33];
*/
USES_CONVERSION;
	*version = ReleaseVersion.Copy();
/*
	const string Cert1 = "MIIHVDCCBjygAwIBAgIKJbmN0QAAAAABVDANBgkqhkiG9w0BAQUFADCBvzEiMCAGCSqGSIb3DQEJARYTaW5mb0BpbmZvbW9zYWljLmNvbTELMAkGA1UEBhMCVVMxCzAJBgNVBAgTAkNBMREwDwYDVQQHEwhTYW4gSm9zZTEfMB0GA1UEChMWSW5mb21vc2FpYyBDb3Jwb3JhdGlvbjEqMCgGA1UECxMhWE1MIERpZ2l0YWwgU2lnbmF0dXJlIERldmVsb3BtZW50MR8wHQYDVQQDExZJbmZvbW9zYWljIENvcnBvcmF0aW9uMB4XDTAyMDUyMzIzMjYxN1oXDTAzMDUyMzIzMzYxN1owgcIxIzAhBgkqhkiG9w0BCQEWFHNhbGVzQGluZm9tb3NhaWMuY29tMQswCQYDVQQGEwJVUzELMAkGA1UECBMCQ0ExETAPBgNVBAcTCFNhbiBKb3NlMR8wHQYDVQQKExZJbmZvbW9zYWljIENvcnBvcmF0aW9uMSowKAYDVQQLEyFYTUwgRGlnaXRhbCBTaWduYXR1cmUgRGV2ZWxvcG1lbnQxITAfBgNVBAMTGFNlY3VyZVhNTCBMaWNlbnNlIFNpZ25lcjCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAvpEsRpF1jACKaOFENwvBnk47MnBywKvwZ3asWNLr+L3ibjrsxpA+yBMRbRXoYaEK4goGyH2qdANCfBPc0SMwiAWSY/moSSRBxcqL5kmgMeJB37Lw6cKy0HU2UC9kwg5bXgdBn2JeM4sN+/n4No7iteft75zuqGI8Z0BqNOQ2m+cCAwEAAaOCA88wggPLMA4GA1UdDwEB/wQEAwIE8DATBgNVHSUEDDAKBggrBgEFBQcDAjAdBgNVHQ4EFgQUBn2JDstuotvk/TRfp7CvueNy/oowgfsGA1UdIwSB8zCB8IAUyDoe8/LPn+bACFA7aurljP5Nte6hgcWkgcIwgb8xIjAgBgkqhkiG9w0BCQEWE2luZm9A";
// Insert some junk data so that search for X509 cert match in the dll fails
	const int	 junk1[5] = {0xff01ff01, 0x0112abcd, 0x45fa23cd, 0x010afc01, 0x4578fbd1};
	const string Cert2 = "aW5mb21vc2FpYy5jb20xCzAJBgNVBAYTAlVTMQswCQYDVQQIEwJDQTERMA8GA1UEBxMIU2FuIEpvc2UxHzAdBgNVBAoTFkluZm9tb3NhaWMgQ29ycG9yYXRpb24xKjAoBgNVBAsTIVhNTCBEaWdpdGFsIFNpZ25hdHVyZSBEZXZlbG9wbWVudDEfMB0GA1UEAxMWSW5mb21vc2FpYyBDb3Jwb3JhdGlvboIQN2ikHVFArblPpz2OZYaSNjCCATgGA1UdHwSCAS8wggErMIHToIHQoIHNhoHKbGRhcDovLy9DTj1JbmZvbW9zYWljJTIwQ29ycG9yYXRpb24sQ049aW5mb21vc2FpYy1zcnZyLENOPUNEUCxDTj1QdWJsaWMlMjBLZXklMjBTZXJ2aWNlcyxDTj1TZXJ2aWNlcyxDTj1Db25maWd1cmF0aW9uLERDPWluZm9tb3NhaWMsREM9bmV0P2NlcnRpZmljYXRlUmV2b2NhdGlvbkxpc3Q/YmFzZT9vYmplY3RjbGFzcz1jUkxEaXN0cmlidXRpb25Qb2ludDBToFGgT4ZNaHR0cDovL2luZm9tb3NhaWMtc3J2ci5pbmZvbW9zYWljLm5ldC9DZXJ0RW5yb2xsL0luZm9tb3NhaWMlMjBDb3Jwb3JhdGlvbi5jcmwwggFJBggrBgEFBQcBAQSCATswggE3MIG6BggrBgEFBQcwAoaBrWxkYXA6Ly8vQ049SW5mb21vc2FpYyUyMENvcnBvcmF0aW9uLENOPUFJQSxDTj1QdWJsaWMlMjBLZXklMjBTZXJ2aWNlcyxDTj1TZXJ2aWNlcyxDTj1Db25maWd1cmF0aW9uLERDPWluZm9tb3NhaWMsREM9bmV0P2NBQ2VydGlmaWNhdGU/YmFzZT9vYmplY3RjbGFzcz1jZXJ0aWZpY2F0aW9uQXV0aG9yaXR5MHgGCCsGAQUFBzAChmxodHRwOi8vaW5mb21vc2FpYy1zcnZyLmluZm9tb3NhaWMubmV0L0Nl";
// Insert some junk data so that search for X509 cert match in the dll fails
	const int	 junk2[5] = { 0x0112abcd, 0xff01ff01, 0x45fa23cd, 0x4578fbd1, 0x010afc01};

	const string Cert3 = "cnRFbnJvbGwvaW5mb21vc2FpYy1zcnZyLmluZm9tb3NhaWMubmV0X0luZm9tb3NhaWMlMjBDb3Jwb3JhdGlvbi5jcnQwDQYJKoZIhvcNAQEFBQADggEBAKcMX8EMUUnaLgv+d31IpemMMlDDmvUlPLu6T/sFsh3j7eQrjUhsVKTZ303Q+2dh0Qv7REfPLCb1T1Uxbj9bCaEh2UVZSwDdDXETO5QztkLyQZXWPfaUMbHQU/sXMZ7PZBfVo6pMRSTKKY7Lc7wWuDI4HsKDt1Ny2LTyZZdei3LNwLA3WhxuYDzrrTYL0IDOU4HxYhSsQqRUPWhZzBL0QKH/KBspukXK8X5ZdSNJKHDcdyqftaln5FSrh/uth+9fdJIRiJhXKSvnotetBsTRRz4DAR6yLyLou8LTYhfFKHRi7ZOAKmbpkQhtdqXXMkzSoUqvnCIJ5w9WkQGP/9WBKT4=";	
	string X509Cert = Cert1 + Cert2 + Cert3;

	License::Get_CRC_CheckSum((PVOID) X509Cert.c_str(), (ULONG) X509Cert.length(), &crcValue);
	ltoa(crcValue, (char *)charCRC, 16);
	*version = A2WBSTR((LPCSTR)charCRC);
*/
	return S_OK;
}

STDMETHODIMP CSignature::GetLicenseStatus(long *licStatus)
{
	int licenseValue = 0;

	if (LicObj.checkLicense())
	{
		if (LicObj.getSignAllowed())
			licenseValue = licenseValue | SIGN_ALLOWED;
		else
			licenseValue &= ~SIGN_ALLOWED;
		
		if (LicObj.getVerifyAllowed())
			licenseValue = licenseValue | VERIFY_ALLOWED;
		else
			licenseValue &= ~VERIFY_ALLOWED;

		if (LicObj.getEncryptAllowed())
			licenseValue = licenseValue | ENCRYPT_ALLOWED;
		else
			licenseValue &= ~ENCRYPT_ALLOWED;
		
		if (LicObj.getDecryptAllowed())
			licenseValue = licenseValue | DECRYPT_ALLOWED;
		else
			licenseValue &= ~DECRYPT_ALLOWED;
		
		if (LicObj.getSecureSignAllowed())
			licenseValue = licenseValue | SECURESIGN_ALLOWED;
		else
			licenseValue &= ~SECURESIGN_ALLOWED;

		if (LicObj.getSecureSignProfessionalAllowed())
			licenseValue = licenseValue | SECURESIGN_PROF_ALLOWED;
		else
			licenseValue &= ~SECURESIGN_PROF_ALLOWED;

		if (LicObj.getSecureSignEnterpriseAllowed())
			licenseValue = licenseValue | SECURESIGN_ENTR_ALLOWED;
		else
			licenseValue &= ~SECURESIGN_ENTR_ALLOWED;

		if (LicObj.getSecureSignServerAllowed())
			licenseValue = licenseValue | SECURESIGN_SERVER_ALLOWED;
		else
			licenseValue &= ~SECURESIGN_SERVER_ALLOWED;
	}
	*licStatus = licenseValue;

	return S_OK;
}

STDMETHODIMP CSignature::GetPropertyCount(long sigIndex, long *propCount)
{
	EnterObjectLog;
	if ((sigIndex < signum) && (signum != 0))
		*propCount = sgArr[sigIndex]->propNumber;
	else
		*propCount = 0;
	ExitObjectLog;
	return S_OK;
}


#ifdef WIN32
HRESULT STDMETHODCALLTYPE CSignature::QueryStatus(const GUID *pguidCmdGroup,	// Pointer to command group
					ULONG cCmds,				// Number of commands in prgCmds array
					OLECMD prgCmds[],			// Array of commands
					OLECMDTEXT *pCmdText)		// Pointer to name or status of command
{
	HRESULT hr = E_POINTER;
	if (prgCmds != NULL) {

		for (ULONG i = 0; i < cCmds; i++)
			prgCmds[i].cmdf = OLECMDF_SUPPORTED | OLECMDF_ENABLED;

		hr = S_OK;
	}

	return hr;
}


HRESULT STDMETHODCALLTYPE CSignature::Exec(const GUID *pguidCmdGroup,	// Pointer to command group
						 DWORD nCmdID,				// Identifier of command to execute
						 DWORD nCmdExecOpt,			// Options for executing the command
						 VARIANTARG *pvaIn,			// Pointer to input arguments
						 VARIANTARG *pvaOut)		// Pointer to command output
{

	HRESULT hr = E_FAIL;

	// Return error messages if proper parameters are not passed.
	if (pguidCmdGroup != NULL)
		return OLECMDERR_E_UNKNOWNGROUP;
	if (nCmdID != 0)
		return OLECMDERR_E_NOTSUPPORTED;
	if (nCmdExecOpt == OLECMDEXECOPT_SHOWHELP)
		return OLECMDERR_E_NOHELP;

	// Get a reference to the IShellBrowser from GetSite
	IShellBrowser *iShBro;
	HRESULT hres = GetSite(IID_IShellBrowser, (void **)&iShBro);
	if (FAILED(hres))
		return hr;

	// Get the HWND object from the IShellBrowser
	HWND hwnd;
	hres = iShBro->GetWindow(&hwnd);
	if (FAILED(hres))
		return hr;

	// Find out the class name of the HWND object
	char winclass[100];
	if (GetClassName(hwnd, winclass, 100) == 0)
		return hr;

	string str(winclass);
	// If the name is not "IEFrame", it is an error
	if (str.compare("IEFrame"))
		return hr;

	// Get the Shell DocObject View and then the Internet Explorer_Server
	// These are child windows of the HWND object we have
	HWND hwndchild = FindWindowEx(hwnd, NULL, "Shell DocObject View", NULL);
	if (hwndchild == NULL)
		return hr;
	hwndchild = FindWindowEx(hwndchild, NULL, "Internet Explorer_Server", NULL);
	if (hwndchild == NULL)
		return hr;
	
	// Need to load the OLEACC library to be able to get IHTMLDocument2 from the window
	CoInitialize(NULL);
	HINSTANCE hInst = ::LoadLibrary( _T("OLEACC.DLL") );
	CComPtr<IHTMLDocument2> spDoc;
	LRESULT lRes;

	UINT nMsg = ::RegisterWindowMessage( _T("WM_HTML_GETOBJECT") );
	::SendMessageTimeout(hwndchild, nMsg, 0L, 0L, SMTO_ABORTIFHUNG, 1000, (DWORD*)&lRes);

	LPFNOBJECTFROMLRESULT pfObjectFromLresult = (LPFNOBJECTFROMLRESULT)::GetProcAddress(hInst, _T("ObjectFromLresult") );
	if (pfObjectFromLresult == NULL)
		return hr;

	// Get a reference to the IHTMLDocument2 window
	hres = (*pfObjectFromLresult)(lRes, IID_IHTMLDocument2, 0, (void**)&spDoc);
	if (FAILED(hres))
		return hr;

	// Get the body and then the document of the HTMLDocument
	IHTMLElement *spElem;
	hres = spDoc->get_body(&spElem);
	if (FAILED(hres))
		return hr;

	IDispatch *spDisp;
	hres = spElem->get_document(&spDisp);
	if (FAILED(hres))
		return hr;

	// Call the SignHTML function which signs the object and gives the XML.
	BSTR signedHTML;
	hres = SignHTML(spDisp, &signedHTML);
	if (hres == S_FALSE) {
		// SysFreeString(signedHTML);
		return hr;
	}

	unsigned char *buff = HeapW2A(signedHTML);
	ofstream sFile("C:\\Tmp\\SecureXMLsignedHTML.xml");
	sFile << buff << endl;
	sFile.close();
	zFree(buff);

	// Get the original HTML signed by using the GetSignedHTML function.
	BSTR origHTML;
	hres = GetSignedHTML(signedHTML, &origHTML);
	if (hres == S_FALSE) {
		SysFreeString(signedHTML);
		// SysFreeString(origHTML);
		return hr;
	}

	buff = HeapW2A(origHTML);
	ofstream oFile("C:\\Tmp\\SecureXMLorigHTML.html");
	oFile << buff << endl;
	oFile.close(); zFree(buff);

	SysFreeString(signedHTML);
	SysFreeString(origHTML);
	return S_OK;

}


STDMETHODIMP CSignature::SetSite(IUnknown* pUnkSite) {

	if (pUnkSite)
		HRESULT hr = pUnkSite->QueryInterface(IID_IShellBrowser, (LPVOID *)&pSite);

	ofstream ofile;
	ofile.open("C:\\Tmp\\setsiteinv.txt", ios_base::app);
	ofile << "We are in Setsite" << endl;
	ofile.close();

	return S_OK;
}

STDMETHODIMP CSignature::GetSite(REFIID riid, void **ppvSite) {

	if (pSite)
		return pSite->QueryInterface(riid, ppvSite);

	return E_FAIL;

}
#endif

STDMETHODIMP CSignature::ViewAnyCertificate(BSTR inputX509Data)
{
	unsigned char *charX509Data;
	CComBSTR	tmpCcBstr;
	EnterObjectLog;
	tmpCcBstr = inputX509Data;
	if (tmpCcBstr.Length() == 0)
	{
		setError(SigHandle, CERT_NOT_FOUND);
		return(S_FALSE);
	}
	charX509Data = HeapW2A(inputX509Data);
	axViewAnyCertificate(charX509Data);
	zFree(charX509Data);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::SelectActiveCertificate(BSTR *certID)
{
	char *certData=NULL;
	unsigned char *plainTextHex = NULL;

	*certID = NULL;
	EnterObjectLog;
USES_CONVERSION;
//DebugBreak();
#ifdef WIN32
	if (CertificateCount != 0)
	{
        certData = dlg->selectCertificate();
	}
#endif
	if (certData != NULL)
	{
		int i = 0;
		for (i = 0; i < CertificateCount; i++)
		{
			if (!(StrCmp((const char *)cV[i]->certificate, (const char *)certData)))
			{
				CurrentCertificate = i;
				if (CertSerialNumberFormat == CERT_SERIAL_PLAIN_HEX)
				{
					plainTextHex = Base64BinToPlainHex(cV[i]->serialNumber);
					*certID = A2WBSTR((LPCSTR)plainTextHex);
					zFree(plainTextHex);
				}
				else
					*certID = A2WBSTR((LPCSTR)cV[i]->serialNumber);
				break;
			}
		}
		if ((i==CertificateCount) && (*certID == NULL))
		{
			setError(SigHandle, CERT_NOT_FOUND);
			CurrentCertificate = NOT_INITIALIZED;
			return S_FALSE;
		}
	}
	else
	{
		setError(SigHandle, CERT_NOT_FOUND);
		CurrentCertificate = NOT_INITIALIZED;
		return S_FALSE;
	}
	if (PfxCertInfo != NULL)
	{
		if (PfxCertInfo->certificate != NULL)
			zFree(PfxCertInfo->certificate);
		zFree(PfxCertInfo);
		PfxCertInfo = NULL;
	}
#ifdef WIN32
	if ((UsingNetscape) && (nsCertStoreObj != NULL))
	{
		BSTR pfxX509Cert;
		CComBSTR certSerialNumber = (char *)cV[CurrentCertificate]->serialNumber;
		_bstr_t pfxFilePath = nsCertStoreObj->ExportNetscapeCert(certSerialNumber.m_str);
		SetActivePFXFileCert(pfxFilePath, nsStorePassword, &pfxX509Cert);
		DeleteFile((LPCTSTR)(char *)pfxFilePath);
	}
#endif
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::VerifyXMLStr(BSTR signedXML, BOOL *sigStatus)
{
	HRESULT hResult=S_OK;
	long certStatus=FALSE;
	unsigned char *ptr, *newPtr=NULL, *curPtr=NULL;
	unsigned int *szPtr;
	unsigned int sizeM;
	BOOL freeNewPtr=FALSE;
	
	EnterObjectLog;


	*sigStatus = FALSE;
	if (!LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (!LicObj.getVerifyAllowed()) {
		setError(SigHandle, NO_VERIFICATION_LIC);
		return S_FALSE;
	}

	if ((signedXML == NULL) || (SysStringByteLen(signedXML) == 0))
	{
		setError(SigHandle, XML_PARSER_ERROR);
		return S_FALSE;
	}

	if (Base64EncodeXML == TRUE)
	{
		ptr = HeapW2A(signedXML);
		sizeM = strlen((const char *)ptr);
		sizeM = base64decodeSize(sizeM);
		if(!(newPtr = (BYTE *)zMalloc(sizeM+1)))
		{
			zFree(ptr);
			setError(SigHandle, MEMORY_FAULT);
			return S_FALSE;
		}
		freeNewPtr = TRUE;
		if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
		{
			zFree(ptr);
			zFree(newPtr);
			setError(SigHandle, BASE64_ERROR);
			return S_FALSE;
		}
		zFree(ptr);
	}
	else
	{
		ptr = (unsigned char *)signedXML;
		szPtr = (unsigned int *)(ptr - sizeof(int));
		sizeM = (*szPtr);

		if (((*ptr == 0xff) && (*(ptr +1) == 0xfe)) ||
			((*ptr == 0xfe) && (*(ptr +1) == 0xff)))
		{
			// There is no need to put the UTF 16 header since the data is already in utf-16 format
			newPtr = ptr;
		}
		else
		{
			newPtr = (unsigned char *)zMalloc(sizeM + 4);
			freeNewPtr = TRUE;

			FileEncoding(newPtr);
			memcpy(newPtr+2, ptr, sizeM + 2);
			sizeM += 4;
		}
	}

	*sigStatus = TRUE;
	if (uriArr != NULL)
	{
		SigHandle->locArray = uriArr;
		SigHandle->locNumber = totalUriCount;
	}

	if (HMACKey.Length() == 0)
		*sigStatus = (BOOL) axVerify((const unsigned char *)newPtr, sizeM, NULL, IgnoreIncompleteSignature, SigIndexToVerify, DetailedVerificationReportFlag, SigHandle);
	else
	{
		/*
		 * This might not work on Windows 95/98
		 */
		xsCoreSetCSP((unsigned char *)"Microsoft Enhanced Cryptographic Provider v1.0",SigHandle);
		*sigStatus = (BOOL) axVerify((const unsigned char *)newPtr, sizeM, &HMACPassword, IgnoreIncompleteSignature, SigIndexToVerify, DetailedVerificationReportFlag, SigHandle);
	}

	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	//if (DetailedVerificationReportFlag)
	//	FetchSignatureStatus(*sigStatus);
	//else
	//	sgArr = axGetSignature(&signum, SigHandle); // Get the full signature stats
	FetchSignatureStatus(*sigStatus, DetailedVerificationReportFlag);

	if ((*sigStatus != FALSE) && (CertVerifyParams.verificationOptions))
	{
		for (int i=0; i<signum; i++) // For each signature in the document
		{
			// certificate is present in the signature, validate it
			if (sgArr[i]->certificatesCount != 0)
			{
				get_SigCertStatus(i, NULL, 0, &certStatus);
				if (certStatus != 0)
				{
					// Add signature status value of failed
					*sigStatus = FALSE;
					sgArr[i]->status = FALSE;
					break;
				}
			}
		}
	}
	if (freeNewPtr)
		zFree(newPtr);
	ExitObjectLog;
	return hResult;

}

STDMETHODIMP CSignature::SetActivePFXFileCert(BSTR pfxFileName, BSTR pfxPassword, BSTR *pfxX509Cert)
{
	DWORD fileSize,dwBytesToWrite;
	char *certData=NULL;
	unsigned char *binFileData=NULL;
//	unsigned char *charPfxFileName;
	unsigned char *ptr;
	unsigned int *szPtr;
	unsigned int sizeM;
USES_CONVERSION;
	EnterObjectLog;
	CComBSTR	tmpCcBstr;

	tmpCcBstr = pfxFileName;
	if (tmpCcBstr.Length() == 0)
	{
		setError(SigHandle, FILE_NOT_FOUND);
		return S_FALSE;
	}
//	charPfxFileName = HeapW2A(pfxFileName);
	
	if (ReadAllBin(pfxFileName, &binFileData, &fileSize) == S_FALSE)
	{
		setError(SigHandle, IO_ERROR);
//		zFree(charPfxFileName);
		return S_FALSE;
	}

	if (PfxPassword.pbData != NULL)
	{
		zFree(PfxPassword.pbData);
		PfxPassword.pbData = NULL;
	}

	ptr = (unsigned char *)pfxPassword;

	if (ptr != NULL)
	{
		szPtr = (unsigned int *)(ptr - sizeof(int));
		sizeM = *szPtr;

		if (sizeM == 0) {
			PfxPassword.pbData = NULL;
			PfxPassword.cbData = 0;
		}
		else
		{
			sizeM += 2; // BSTR size does not include the terminating null so add 2 to the size
			PfxPassword.pbData		= (unsigned char *) zMalloc(sizeM);
			memcpy(PfxPassword.pbData, ptr, sizeM);
			PfxPassword.cbData = sizeM;
		}
	}

	dwBytesToWrite	= base64encodeSize(fileSize);
	
	if (B64PfxDataPtr != NULL)
		zFree(B64PfxDataPtr);

	B64PfxDataPtr = (unsigned char *)zMalloc (dwBytesToWrite+1);
	
	memset(B64PfxDataPtr,0,dwBytesToWrite+1);
	dwBytesToWrite = base64encode(binFileData,fileSize, B64PfxDataPtr,dwBytesToWrite+1);

	PfxCertDataBlob.cbData = fileSize;
	
	if (PfxCertDataBlob.pbData != NULL)
		zFree(PfxCertDataBlob.pbData);
	
	PfxCertDataBlob.pbData = binFileData; // Remember to free this memory in Empty()

	if (PfxX509Cert != NULL)
		zFree(PfxX509Cert);

	if (PfxCertInfo != NULL)
	{
		// Since PfxX509Cert and PfxCertInfo->certificate point to the same memory location
		// and we just freed PfxX509Cert above, we can't free PfxCertInfo->certificate as well
		zFree(PfxCertInfo);
		PfxCertInfo = NULL;
	}
#ifdef NSS
	SECItem spwd;
	spwd.data = PfxPassword.pbData;
	spwd.len  = PfxPassword.cbData;
	if (SwapUnicodeBytes(&spwd)!=0) {
		ExitObjectLog;
		setError(SigHandle, PFX_BAD_PASSWORD);
		return S_FALSE;
	}

	PfxX509Cert	= crPFX2X509(&PfxCertDataBlob, &spwd, &PfxCertInfo, SigHandle);
#else
	PfxX509Cert	= crPFX2X509(&PfxCertDataBlob, (LPCWSTR) PfxPassword.pbData, &PfxCertInfo, SigHandle);
#endif

	if (PfxX509Cert != NULL)
	{
		*pfxX509Cert	= A2WBSTR((LPCSTR) PfxX509Cert);
		CurrentCertificate = USE_PFX_CERT;
	}
	else
	{
		ExitObjectLog;
		setError(SigHandle, PFX_BAD_PASSWORD);
		return S_FALSE;
	}

//	zFree(charPfxFileName);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP	CSignature::PFXExportCertificate(BSTR certID, BSTR password, BSTR *pfxFilePath)
{
	unsigned char *charCertId, *charStoreName;
	PDS_DATA_BLOB pPFXDataBlob;
	char TempPath[MAX_PATH], TempName[MAX_PATH];
#ifdef WIN32
	HANDLE hTempFile;
#else
	FILE *hTempFile;
#endif
	DWORD dwBytesWritten;
	unsigned char *ptr;
	unsigned int *szPtr;
	unsigned int sizeM;
	LPCWSTR pfxPassword=NULL;

	USES_CONVERSION;

	CComBSTR	tmpCcBstr;
	EnterObjectLog;
	tmpCcBstr = certID;
	if (tmpCcBstr.Length() == 0)
	{
		setError(SigHandle, CERT_NOT_FOUND);
		return S_FALSE;
	}
	
	charCertId = (unsigned char *)HeapW2A(certID);
	charStoreName = (unsigned char *)HeapW2A(StoreName.m_str);

	ptr = (unsigned char *)password;

	if (ptr != NULL)
	{
		szPtr = (unsigned int *)(ptr - sizeof(int));
		sizeM = *szPtr;

		if (sizeM == 0)
			pfxPassword = NULL;
		else
		{
			sizeM += 2; // BSTR size does not include the terminating null so add 2 to the size
			pfxPassword		= (LPCWSTR) zMalloc(sizeM);
			memcpy((void *)pfxPassword, ptr, sizeM);
		}
	}


	pPFXDataBlob = axExportCertificate(charStoreName, charCertId, pfxPassword, SigHandle);
	
	if (pfxPassword != NULL)
		zFree((void *)pfxPassword);
	zFree(charCertId);
	zFree(charStoreName);

	if (pPFXDataBlob != NULL)
	{
		// Create a temporary file. 
		GetTempPath((DWORD)MAX_PATH, TempPath); 
		GetTempFileName(TempPath, // dir. for temp. files 
			"INFM",                // temp. file name prefix 
			0,                    // create unique name 
			TempName);          // buffer for name 
#ifdef WIN32
		hTempFile = CreateFile((LPCSTR) TempName,  // file name 
			GENERIC_READ | GENERIC_WRITE, // open for read/write 
			0,                            // do not share 
			NULL,                         // no security 
			CREATE_ALWAYS,                // overwrite existing file
			FILE_ATTRIBUTE_NORMAL,        // normal file 
			NULL);                        // no attr. template 
		if (hTempFile == INVALID_HANDLE_VALUE) 
#else
		hTempFile = fopen(TempName, "w+");
		if (!hTempFile)
#endif
		{ 
			setError(SigHandle, IO_ERROR);
			zFree(pPFXDataBlob->pbData);
			zFree(pPFXDataBlob);
			return S_FALSE;
		}
 
		// Write the signature buffer to the temporary file. 
#ifdef WIN32
		WriteFile(hTempFile, pPFXDataBlob->pbData, pPFXDataBlob->cbData, 
				&dwBytesWritten, NULL);
		// Close file. 
 		CloseHandle(hTempFile);
#else
		fwrite(pPFXDataBlob->pbData, 1, pPFXDataBlob->cbData, hTempFile);
		fclose(hTempFile);
#endif
		zFree(pPFXDataBlob->pbData);
		zFree(pPFXDataBlob);

		*pfxFilePath = A2WBSTR(TempName);

		TEMP_FILE_INFO *tmpFilePath = new (TEMP_FILE_INFO);
		strcpy((char *)tmpFilePath->fileName, TempName);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
		ExitObjectLog;
		return S_OK;
	}
	else
		return S_FALSE;
}

//showSystemTime(LPSYSTEMTIME systemTime)
//{
//	char buffer[MAX_PATH];
//	sprintf(buffer, "Year = %4d\nMonth = %4d\nDay = %4d\nHour = %4d\nMinute = %4d\nSecond = %4d\n", 
//		systemTime->wYear, systemTime->wMonth, systemTime->wDay,
//		systemTime->wHour, systemTime->wMinute, systemTime->wSecond);
//	MessageBox(NULL, (LPCTSTR)buffer, (LPCTSTR)"showSystemTime", MB_OK);
//}

BOOL CSignature::CreateSigFromTmplBlob(
									   xmlDocPtr doc,
									   char *sigId, 
									   unsigned char **signedXML, 
									   int *signedXmlSize)
{
	unsigned char *signingCert=NULL;
	keyinfo *ki=NULL;
	x509data *curX509Data=NULL;
	x509group *curX509Group=NULL;
	DWORD fileSize;
	unsigned char *binFileData=NULL;
	char *charInputFile=NULL;
	BYTE **certificateList=NULL;
	UINT certificateListCount=0;
	UINT i,j;
	PURI_PATH *tmpUriArr=NULL;
	PURI_PATH tmpUriPath=NULL;
	int iSigMethod=0;

	BYTE **pbData=NULL;
	DWORD cbData=0;
	BYTE *pbDocument=NULL;		// Object BLOB to sign
	DWORD cbDocument=0;
	char *varprop[1];
	reference *pref=NULL;
	BOOL result;
	BOOL freeSigningCert=FALSE;
	BSTR bstrPropName, bstrPropValue;

	USES_CONVERSION;
	EnterObjectLog;
	memset(pout,0,MAX_PATH*2);
	memset(pout2,0,MAX_PATH*2);
	st_transform *ptrs=NULL;
	XS_ALGORITHM trAlgorithm=0;

	*signedXML = NULL;
	/*
	 * init Signature. crBlob contains XML - envelope document
	 */

	if (xsInitSignature(sigId, doc, SigHandle)!=TRUE) 
	{
		return FALSE;
	}
//	DebugBreak();
	if (UseHMAC != TRUE)
	{
		if (calculateDigestOnly == FALSE)
		{
			if ((CurrentCertificate == NOT_INITIALIZED)	&& (CertificateCount != 0))
			{
#ifdef WIN32
				signingCert = (unsigned char *)dlg->selectCertificate();
#endif
				if (signingCert != NULL)
				{
					for (int i=0;i<CertificateCount;i++)
					{
						if (!(StrCmp((const char *)cV[i]->certificate, (const char *)signingCert)))
						{
							CurrentCertificate = i;
							break;
						}
					}
#ifdef WIN32
					if ((UsingNetscape) && (nsCertStoreObj != NULL))
					{
//						DebugBreak();
						BSTR pfxX509Cert;
						CComBSTR certSerialNumber = (char *)cV[CurrentCertificate]->serialNumber;
						_bstr_t pfxFilePath = nsCertStoreObj->ExportNetscapeCert(certSerialNumber.m_str);
						SetActivePFXFileCert(pfxFilePath, nsStorePassword, &pfxX509Cert);
						signingCert = B64PfxDataPtr;
						DeleteFile((LPCTSTR)(char *)pfxFilePath);
					}
#endif
				}
			}
			else
				if (CurrentCertificate == USE_PFX_CERT)
					signingCert = B64PfxDataPtr;
				else
					if (CurrentCertificate == USE_BASE64_CERT)
					{
						freeSigningCert = TRUE;
						signingCert = (unsigned char *)HeapW2A(SignerCertificate.m_str);
					}
					else
						if ((CurrentCertificate >= 0) && (cV != NULL) && (cV[CurrentCertificate] != NULL))
							signingCert = cV[CurrentCertificate]->certificate;

			if (signingCert == NULL)
			{
				setError(SigHandle, NO_CERTIFICATE);
				return FALSE;
			}
			// We don't need the whole certificate chain if any of the following is true
			// 1. Cam is being used and ExcludeSignerCertificate != 0
			// 2. No certificate verification options other than VERIFY_CRL_REC are enabled and 
			// ExcludeSignerCertificate != 0
			//if (!(((useCam) && (ExcludeSignerCertificateFlag != 0)) ||
			//	(!(CertVerifyParams.verificationOptions &= (~VERIFY_CRL_REC)) && (ExcludeSignerCertificateFlag != 0))))
			//{
#ifdef NSS
				SECItem siPwd;
				siPwd.data = PfxPassword.pbData;
				siPwd.len  = PfxPassword.cbData;

				certificateList = crGetSignerCertChain(	signingCert,
													&siPwd,
													&certificateListCount,
													SigHandle);
#else
				certificateList = crGetSignerCertChain(	signingCert,
													(LPWSTR)PfxPassword.pbData,
													&certificateListCount,
													SigHandle);
#endif
			//}
			//else
			//{
			//	certificateList = (BYTE **)zMalloc(sizeof (BYTE *) * 1);
			//	certificateList[0] = (BYTE *)zMalloc(strlen((const char *)signingCert) + 1);
			//	strcpy((char *)certificateList[0], (const char *)signingCert);
			//	certificateListCount = 1;
			//}

			if (certificateList == NULL)
			{
				if (freeSigningCert == TRUE)
					zFree(signingCert);
				return FALSE;
			}
		}
		else
		{// use the signer certificate chain set by a previous call to SetSignerCertChain method
			certificateList = getSignerCertChain(&certificateListCount);
			if (certificateList != NULL)
				signingCert = certificateList[0];
		}
//DebugBreak();
		if (certificateList != NULL)
		{
			if ((CertVerifyParams.usedCrlCount != 0) &&
				(CertVerifyParams.usedCrlList != NULL))
			{
				for (UINT i=0; i < CertVerifyParams.usedCrlCount; i++)
				{
					if (CertVerifyParams.usedCrlList[i] != NULL)
						zFree(CertVerifyParams.usedCrlList[i]);
				}
				zFree(CertVerifyParams.usedCrlList);
				CertVerifyParams.usedCrlList = NULL;
				CertVerifyParams.usedCrlCount = 0;
			}

			if (((CertVerifyParams.verificationOptions & (~VERIFY_CRL_REC)) || (useCam) || (useOcsp)) &&
				(certificateList != NULL))
			{
				SYSTEMTIME	tsSysTime;
#ifdef WIN32
				GetSystemTime(&tsSysTime);
#else
				GetSystemTimeLinux(&tsSysTime);
#endif
				if (useCam)
					result = crVerifyCertificateUsingCam(certificateList,
										certificateListCount,
										&tsSysTime, 
										(LPWSTR)PfxPassword.pbData, 
										&CertVerifyParams,
										SigHandle);
				else
					if (useOcsp)
						result = crVerifyCertificateUsingOcsp(certificateList,
											certificateListCount,
											&tsSysTime, 
											(LPWSTR)PfxPassword.pbData, 
											&CertVerifyParams,
											SigHandle);
					else {
#ifdef NSS
						SECItem s;
						s.data = PfxPassword.pbData;
						s.len  = PfxPassword.cbData;
						result = crVerifyCertificate(certificateList,
											certificateListCount,
											&tsSysTime, 
											&s, 
											&CertVerifyParams,
											SigHandle);
#else
						result = crVerifyCertificate(certificateList,
											certificateListCount,
											&tsSysTime, 
											(LPWSTR)PfxPassword.pbData, 
											&CertVerifyParams,
											SigHandle);
#endif
					}
				if (result == FALSE)
				{
					for (i=0; i < certificateListCount; i++)
					{
						zFree(certificateList[i]);
					}
					zFree(certificateList);
					if (freeSigningCert == TRUE)
						zFree(signingCert);
					return FALSE;
				}
			}

			/*
			* set <X509Data> certificate
			*/
			if (ExcludeSignerCertificateFlag != 1)// Either include the whole chain or just the end certificate
			{
				ki = xsCoreAddKeyInfo(SigHandle);
				curX509Data = xsCoreAddX509Data(ki, SigHandle);

				if (ExcludeSignerCertificateFlag == 0)// Include the whole chain of certificates
				{
					for (i=0; i < certificateListCount; i++)
					{
						char *crlData = NULL;

						curX509Group = xsCoreAddX509Group(curX509Data, SigHandle);
						if ((IncludeCRLInSignature == TRUE) && (CertVerifyParams.usedCrlCount != 0))
						{
							crlData = CertVerifyParams.usedCrlList[i];
						}

						if (xsCoreSetX509Group(curX509Group,NULL,NULL,(char *)certificateList[i],crlData, NULL, NULL, SigHandle)!=TRUE)
						{
							for (j=0; j < certificateListCount; j++)
							{
								zFree(certificateList[j]);
							}
							zFree(certificateList);
							if (freeSigningCert == TRUE)
								zFree(signingCert);
							return FALSE;
						}
					}
				}
				if (ExcludeSignerCertificateFlag == 2) //Just include the signer end certificate
				{
					char *crlData = NULL;
					curX509Group = xsCoreAddX509Group(curX509Data, SigHandle);
					if ((IncludeCRLInSignature == TRUE) && (CertVerifyParams.usedCrlCount != 0))
					{
						crlData = CertVerifyParams.usedCrlList[0];
					}
					if (xsCoreSetX509Group(curX509Group,NULL,NULL,(char *)certificateList[0],crlData, NULL, NULL, SigHandle)!=TRUE)
					{
						for (j=0; j < certificateListCount; j++)
						{
							zFree(certificateList[j]);
						}
						zFree(certificateList);
						if (freeSigningCert == TRUE)
							zFree(signingCert);
						return FALSE;
					}
				}
			} // ExcludeSignerCertificateFlag != 1
		}
	}

	if (EnvelopingFlag == DETACHED) {
		// prepare URI array, one element
		tmpUriArr = (PURI_PATH *)zMalloc(sizeof(PURI_PATH));
		tmpUriPath = (PURI_PATH) zMalloc(sizeof(URI_PATH));
		tmpUriPath->fullPath = (unsigned char *)zMalloc(MAX_PATH*2);
		char *wDocURI = (char *)HeapW2A(DocumentURI.m_str);
		strcpy((char *)tmpUriPath->fullPath, wDocURI);
		zFree(wDocURI);
		tmpUriPath->sigId = (unsigned char *)zMalloc(MAX_PATH);
		strcpy((char *)tmpUriPath->sigId,sigId);
		tmpUriPath->URI = (unsigned char *)zMalloc (MAX_PATH*2);
		unsigned char *bareFileName = xsRemoveBstrPath(DocumentURI.m_str);
		strcpy((char *)tmpUriPath->URI,(const char *)bareFileName);
		tmpUriArr[0] = tmpUriPath;

		// set global structures
		SigHandle->locArray = tmpUriArr;
		SigHandle->locNumber = 1;
		sprintf (pout,"REF_Detached_%s",SigHandle->sig->param_id);
		if ((xsGenerateReference(pout,IFM_SHA1,NULL, (const char *)bareFileName,SigHandle))==NULL) 
		{ 
			for (i=0; i < certificateListCount; i++)
			{
				zFree(certificateList[i]);
			}
			zFree(certificateList);
			if (freeSigningCert == TRUE)
				zFree(signingCert);
			zFree(bareFileName);
			return FALSE;
		}
		zFree(bareFileName);
}
	if (DetachedObjectCount != 0)
	{
		// prepare URI array, DetachedObjectCount elements
		tmpUriArr = (PURI_PATH *)zMalloc(sizeof(PURI_PATH) * DetachedObjectCount);

		for (i=0; i < DetachedObjectCount; i++)
		{
			tmpUriPath = (PURI_PATH) zMalloc(sizeof(URI_PATH));
			tmpUriPath->fullPath = (unsigned char *)zMalloc(MAX_PATH*2);
			strcpy((char *)tmpUriPath->fullPath,(const char *)DetachedObjectList[i]);
			tmpUriPath->sigId = (unsigned char *) zMalloc(MAX_PATH);
			strcpy((char *)tmpUriPath->sigId,sigId);
			tmpUriPath->URI = (unsigned char *) zMalloc (MAX_PATH*2);
			strcpy((char *)tmpUriPath->URI,xsRemovePath((const char *)DetachedObjectList[i]));
			tmpUriArr[i] = tmpUriPath;
		}
		// set global structures
		SigHandle->locArray = tmpUriArr;
		SigHandle->locNumber = DetachedObjectCount;
		for (i=0; i < DetachedObjectCount; i++)
		{
			sprintf (pout,"REF_Detached_%s_%d",SigHandle->sig->param_id, i);
			if ((xsGenerateReference(pout,IFM_SHA1,NULL, xsRemovePath((const char *)DetachedObjectList[i]),SigHandle))==NULL) 
			{ 
				for (j=0; j < certificateListCount; j++)
				{
					zFree(certificateList[j]);
				}
				zFree(certificateList);
				if (freeSigningCert == TRUE)
					zFree(signingCert);
				return FALSE;
			}
		}
	}
	if (AttachedObjectCount != 0)
	{
		pbData = (BYTE **)zMalloc(sizeof(BYTE *) * AttachedObjectCount);
		if (pbData == NULL)
		{
			setError(SigHandle, MEMORY_FAULT);
			for (j=0; j < certificateListCount; j++)
			{
				zFree(certificateList[j]);
			}
			zFree(certificateList);
			if (freeSigningCert == TRUE)
				zFree(signingCert);
			return FALSE;
		}
		memset(pbData, 0, sizeof(BYTE *) * AttachedObjectCount);
	}
	for (i=0; i < AttachedObjectCount; i++)
	{
		if ((pbDocument = xsDereferenceBstrURI(
			AttachedObjectList[i],
			&cbDocument))==NULL) {		// (in/out) size of data
				setError(SigHandle, DEREF_URI_ERROR);
				for (j=0; j < certificateListCount; j++)
				{
					zFree(certificateList[j]);
				}
				zFree(certificateList);
				if (freeSigningCert == TRUE)
					zFree(signingCert);
				return FALSE;
			}
		// Base64 encode
		cbData = base64encodeSize(cbDocument);
		// allocate memory
		if (pbData[i]) zFree (pbData[i]);
		pbData[i] = NULL;
		if(!(pbData[i] = (BYTE *)zMalloc(cbData+1)))
		{
			zFree(pbDocument);
			setError(SigHandle, MEMORY_FAULT);
			for (j=0; j < certificateListCount; j++)
			{
				zFree(certificateList[j]);
			}
			zFree(certificateList);
			if (freeSigningCert == TRUE)
				zFree(signingCert);
			return FALSE;
		}
		if (base64encode(pbDocument,cbDocument,(unsigned char*)pbData[i],cbData)==-1) 
		{
			setError(SigHandle, BASE64_ERROR);
			zFree(pbDocument);
			zFree(pbData[i]);
			for (j=0; j < certificateListCount; j++)
			{
				zFree(certificateList[j]);
			}
			zFree(certificateList);
			if (freeSigningCert == TRUE)
				zFree(signingCert);
			return FALSE;
		}
		*(pbData[i]+cbData)='\0';
		zFree(pbDocument);
		sprintf (	pout2,
					"OBJECT_%s_%d",
					SigHandle->sig->param_id, 
					i);
		varprop[0] = NULL;
		varprop[0] = (char *)zMalloc(MAX_PATH*2);
		memset(varprop[0],0,MAX_PATH*2);
//		sprintf(varprop[0],"URI_%s=%s",pout2,xsRemovePath((const char *)AttachedObjectList[i]));
		sprintf(varprop[0], "URI_%s",pout2);
		bstrPropName = A2WBSTR((LPCSTR)varprop[0]);
		unsigned char *tmpCharPtr = xsRemoveBstrPath(AttachedObjectList[i]);
		bstrPropValue = A2WBSTR((LPCSTR)tmpCharPtr);
		zFree(tmpCharPtr);
		ChangeOrAddProperty(bstrPropName, bstrPropValue);
		SysFreeString(bstrPropName);
		SysFreeString(bstrPropValue);
//		if ((xsGenerateObject(pout2,(const char *)pbData[i],(const char**)varprop,1,SigHandle))==NULL)
		if ((xsGenerateObject(pout2,(const char *)pbData[i],(const char**)NULL,0,SigHandle))==NULL)
		{
			if (varprop[0]) zFree(varprop[0]);
			setError(SigHandle, XMLSIGLIB_ERROR);
			zFree(pbData[i]);
			for (j=0; j < certificateListCount; j++)
			{
				zFree(certificateList[j]);
			}
			zFree(certificateList);
			if (freeSigningCert == TRUE)
				zFree(signingCert);
			return FALSE;
		}
		if (varprop[0]) zFree(varprop[0]);
		varprop[0] = NULL;
		sprintf (pout,"REF_Attached_%s_%d",SigHandle->sig->param_id, i);
		sprintf (pout2,"#OBJECT_%s_%d",SigHandle->sig->param_id, i);
		if ((pref = xsGenerateReference(pout,IFM_SHA1,NULL,pout2, SigHandle))==NULL) 
		{
			setError(SigHandle, XMLSIGLIB_ERROR);
			for (j=0; j < certificateListCount; j++)
			{
				zFree(certificateList[j]);
			}
			zFree(certificateList);
			if (freeSigningCert == TRUE)
				zFree(signingCert);
			return FALSE;
		}
		if (xsGenerateTransform(BASE64,pref, SigHandle)==NULL) 
		{
			setError(SigHandle, XMLSIGLIB_ERROR);
			return FALSE;
		}
	}

	if (TimeStampOption)
	{
		if (TimeStampOption == TIME_SNTP_RFC_1305_SRVR)
		{
#ifdef WIN32
			DebugLog("TimeStampOption == TIME_SNTP_RFC_1305_SRVR");
			//Initialise the winsock stack
			WSADATA wsaData;
			BYTE wsMajorVersion = 1;
			BYTE wsMinorVersion = 1;
			WORD wVersionRequested = MAKEWORD(wsMinorVersion, wsMajorVersion);   
			if (WSAStartup(wVersionRequested, &wsaData) == 0) 
			{
				DebugLog("WSAStartup successful. Initializing CSNTPClient object");
				//Do the actual NTP Query
				CSNTPClient sntp;
				NtpServerResponse response;
				unsigned char *hostUrl = HeapW2A(TimeStampURL.m_str);
				if (sntp.GetServerTime((LPCTSTR)hostUrl, response))
				{
					DebugLog("sntp.GetServerTime() returned non-zero response");
					string day, month;
					CNtpTime newTime(CNtpTime::GetCurrentTime() + response.m_LocalClockOffset);
					SYSTEMTIME sntpTime = newTime;
					char *timeBuffer=NULL;
					switch (TimeStampFormat)
					{
						case TIME_RFC:
							timeBuffer = systemTimeToRfcTime(sntpTime);
							bstrPropValue = A2WBSTR((LPCSTR)timeBuffer);
							zFree(timeBuffer);
							break;
						case TIME_VB_NOW:
							timeBuffer = systemTimeToVbNowTime(sntpTime);
							bstrPropValue = A2WBSTR((LPCSTR)timeBuffer);
							zFree(timeBuffer);
							break;
						case TIME_JS_UTC:
//							showSystemTime(&sntpTime);
							timeBuffer = systemTimeToJsUtcTime(sntpTime);
//							MessageBox(NULL, (LPCTSTR)timeBuffer, "CreateSigFromTmplBlob", MB_OK);
							bstrPropValue = A2WBSTR((LPCSTR)timeBuffer);
							zFree(timeBuffer);
							break;
						default:
							timeBuffer = systemTimeToRfcTime(sntpTime);
							bstrPropValue = A2WBSTR((LPCSTR)timeBuffer);
							zFree(timeBuffer);
					}
					string propNameStr = TIME_STAMP_PREFIX;
					propNameStr += sigId;
					bstrPropName = A2WBSTR((LPCSTR)propNameStr.c_str());
					DebugLog(propNameStr.c_str());
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					SysFreeString(bstrPropValue);
					//Don't forget to release out use of the winsock stack
					WSACleanup();
					bstrPropName = SysAllocString((const OLECHAR *)TIME_STAMP_FORMAT);
					switch (TimeStampFormat)
					{
						case TIME_RFC:
							bstrPropValue = SysAllocString(L"0");
							break;
						case TIME_VB_NOW:
							bstrPropValue = SysAllocString(L"1");
							break;
						case TIME_JS_UTC:
							bstrPropValue = SysAllocString(L"2");
							break;
						default:
							bstrPropValue = SysAllocString(L"0");
					}
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					SysFreeString(bstrPropValue);
					bstrPropName = A2WBSTR((LPCSTR)"TimeStampURL");
					bstrPropValue = TimeStampURL.m_str;
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					bstrPropName = SysAllocString((const OLECHAR *)TIME_STAMP_PROTOCOL);
					bstrPropValue = SysAllocString((const OLECHAR *)TIME_SNTP_RFC_1305_PROTOCOL);
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					SysFreeString(bstrPropValue);
				}
				else
				{
					DebugLog("sntp.GetServerTime() failed. Returned zero as response.");
					//Don't forget to release out use of the winsock stack
					WSACleanup();
					setError(SigHandle, TIME_STAMP_FAILED);
					if (TimeStampCritical == TRUE)
					{
						for (j=0; j < certificateListCount; j++)
						{
							zFree(certificateList[j]);
						}
						zFree(certificateList);
						if (freeSigningCert == TRUE)
							zFree(signingCert);
						if (hostUrl != NULL)
							zFree(hostUrl);
						return FALSE;
					}
				}
				if (hostUrl != NULL)
					zFree(hostUrl);
			}
#endif
		}
		else
		{
			if (TimeStampOption == TIME_RFC_867_SRVR)
			{
				unsigned char *tsUrl=NULL;
				BOOL freeTsUrl = FALSE;
				unsigned char *buf=NULL;
				DWORD tsSize=0;

				if (TimeStampURL.Length() == 0) 
				{
					tsUrl = (unsigned char *)defaultTimeServiceUrl;
				}
				else
				{
					tsUrl = HeapW2A(TimeStampURL.m_str);
					freeTsUrl = TRUE;
				}
				DebugLog((const char *)tsUrl);
				int len =strlen((const char *)tsUrl);
				int index =0;
				char *p = (char *)tsUrl;
				if (!(strcmp((const char *)tsUrl, "SystemTime")))
				{
					buf = getSystemTimeAsRfcTime();
					tsSize = strlen((const char *)buf);
				}
				else
					buf = xsHTTPFetch((const char *)tsUrl, (int *) &tsSize);
				if (freeTsUrl)
					zFree(tsUrl);

				if ((buf != NULL) && (tsSize != 0))
				{
					char *timeBuffer=NULL;
					LPSYSTEMTIME systemTime = rfcTimeToSystem((BYTE *)buf);

					switch (TimeStampFormat)
					{
						case TIME_RFC:
							bstrPropValue = A2WBSTR((LPCSTR)buf);
							break;
						case TIME_VB_NOW:
							timeBuffer = systemTimeToVbNowTime(*systemTime);
							bstrPropValue = A2WBSTR((LPCSTR)timeBuffer);
							zFree(timeBuffer);
							break;
						case TIME_JS_UTC:
							timeBuffer = systemTimeToJsUtcTime(*systemTime);
							bstrPropValue = A2WBSTR((LPCSTR)timeBuffer);
							zFree(timeBuffer);
							break;
						default:
							bstrPropValue = A2WBSTR((LPCSTR)buf);
					}
					zFree(systemTime);
					string propNameStr = TIME_STAMP_PREFIX;
					propNameStr += sigId;
					bstrPropName = A2WBSTR((LPCSTR)propNameStr.c_str());
					DebugLog(propNameStr.c_str());
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					SysFreeString(bstrPropValue);

					bstrPropName = SysAllocString((const OLECHAR *)TIME_STAMP_FORMAT);
					switch (TimeStampFormat)
					{
						case TIME_RFC:
							bstrPropValue = SysAllocString(L"0");
							break;
						case TIME_VB_NOW:
							bstrPropValue = SysAllocString(L"1");
							break;
						case TIME_JS_UTC:
							bstrPropValue = SysAllocString(L"2");
							break;
						default:
							bstrPropValue = SysAllocString(L"0");
					}
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					SysFreeString(bstrPropValue);
					bstrPropName = A2WBSTR((LPCSTR)"TimeStampURL");
					bstrPropValue = TimeStampURL.m_str;
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					bstrPropName = SysAllocString((const OLECHAR *)TIME_STAMP_PROTOCOL);
					bstrPropValue = SysAllocString((const OLECHAR *)TIME_RFC_867_PROTOCOL);
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					SysFreeString(bstrPropValue);
					zFree(buf);
				}
				else
				{
					DebugLog("RFC-867 Time stamp failed. Returned null as response.");
					setError(SigHandle, TIME_STAMP_FAILED);
					if (TimeStampCritical == TRUE)
					{
						for (j=0; j < certificateListCount; j++)
						{
							zFree(certificateList[j]);
						}
						zFree(certificateList);
						if (freeSigningCert == TRUE)
							zFree(signingCert);
						return FALSE;
					}
				}
			}
		}
	}

	if (UseHMAC != TRUE)
	{
		if (((CertVerifyParams.verificationOptions & VERIFY_CRL) || (useCam) || (useOcsp)) &&
				(certificateList != NULL))
		{
			bstrPropName = A2WBSTR((LPCSTR)"CertificateValidationMethod");
			if (useCam)
			{
				bstrPropValue = A2WBSTR((LPCSTR)"CAM");
				ChangeOrAddProperty(bstrPropName, bstrPropValue);
				SysFreeString(bstrPropName);
				SysFreeString(bstrPropValue);
				bstrPropName = A2WBSTR((LPCSTR)"CamServerHost");
				bstrPropValue = A2WBSTR((LPCSTR)camServerHost);
				ChangeOrAddProperty(bstrPropName, bstrPropValue);
				SysFreeString(bstrPropName);
				SysFreeString(bstrPropValue);
				if (CamResponseTransactionId != NULL)
				{
					bstrPropName = A2WBSTR((LPCSTR)"CamTransactionId");
					bstrPropValue = A2WBSTR((LPCSTR)CamResponseTransactionId);
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					SysFreeString(bstrPropValue);
				}

				if (IncludeCamResponse)
				{
					bstrPropName = A2WBSTR((LPCSTR)"CamValidationResponse");
					bstrPropValue = A2WBSTR((LPCSTR)CamResponseCaSignedMsg, CamResponseCaSignedMsgSize);
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					SysFreeString(bstrPropValue);
				}
			}
			else 			
				if (useOcsp)
				{
					bstrPropValue = A2WBSTR((LPCSTR)"OCSP");
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					SysFreeString(bstrPropValue);
					bstrPropName = A2WBSTR((LPCSTR)"OcspResponderURL");
					bstrPropValue = ocspResponderUrl;
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					if (ocspOutputNonce.Length() != 0)
					{
						bstrPropName = A2WBSTR((LPCSTR)"OcspNonce");
						bstrPropValue = ocspOutputNonce;
						ChangeOrAddProperty(bstrPropName, bstrPropValue);
						SysFreeString(bstrPropName);
					}

					if (IncludeOcspResponse & INCLUDE_TEXT_RESPONSE)
					{
						bstrPropName = A2WBSTR((LPCSTR)"OcspTextResponse");
						bstrPropValue = ocspTextResponse;
						ChangeOrAddProperty(bstrPropName, bstrPropValue);
						SysFreeString(bstrPropName);
					}
					if (IncludeOcspResponse & INCLUDE_BIN_RESPONSE)
					{
						bstrPropName = A2WBSTR((LPCSTR)"OcspBinaryResponse");
						bstrPropValue = ocspB64Response;
						ChangeOrAddProperty(bstrPropName, bstrPropValue);
						SysFreeString(bstrPropName);
					}
				}
				else
				{
					bstrPropValue = A2WBSTR((LPCSTR)"CRL");
					ChangeOrAddProperty(bstrPropName, bstrPropValue);
					SysFreeString(bstrPropName);
					SysFreeString(bstrPropValue);
				}
		}

		if (((CertVerifyParams.verificationOptions &= (~VERIFY_CRL_REC)) && !useCam &&!useOcsp) &&
				(certificateList != NULL))
		{
				string verOptions = "";
				bstrPropName = A2WBSTR((LPCSTR)"CertificateVerificationOptions");
				BOOL addComma = FALSE;
				if (CertVerifyParams.verificationOptions & VERIFY_CRL)
				{
					verOptions += "VERIFY_CRL";
					addComma = TRUE;
				}
				if (CertVerifyParams.verificationOptions & VERIFY_CHAIN)
				{
					if (addComma)
						verOptions += ", ";
					verOptions += "VERIFY_CHAIN";
					addComma = TRUE;
				}
				if (CertVerifyParams.verificationOptions & VERIFY_PATH_LENGTH)
				{
					if (addComma)
						verOptions += ", ";
					verOptions += "VERIFY_PATH_LENGTH";
					addComma = TRUE;
				}
				if (CertVerifyParams.verificationOptions & VERIFY_POLICY)
				{
					if (addComma)
						verOptions += ", ";
					verOptions += "VERIFY_POLICY";
					addComma = TRUE;
				}
				if (CertVerifyParams.verificationOptions & POLICY_EXPLICIT)
				{
					if (addComma)
						verOptions += ", ";
					verOptions += "POLICY_EXPLICIT";
					addComma = TRUE;
				}
				if (CertVerifyParams.verificationOptions & EXPLICIT_TRUST)
				{
					if (addComma)
						verOptions += ", ";
					verOptions += "EXPLICIT_TRUST";
					addComma = TRUE;
				}

				bstrPropValue = A2WBSTR((LPCSTR)verOptions.c_str());
				ChangeOrAddProperty(bstrPropName, bstrPropValue);
				SysFreeString(bstrPropName);
				SysFreeString(bstrPropValue);
		}
	}

	// if hmac true && PhysicalSigUsage == NO_PHYSICAL_SIG set error return

	if ((PhysicalSigUsage == NO_PHYSICAL_SIG) && (UseHMAC == TRUE) && (HMACKey.Length() == 0))
	{
		setError(SigHandle, NO_HMAC_PASSWORD);
		return FALSE;
	}


	if (PhysicalSigUsage != NO_PHYSICAL_SIG)
	{
		if (SigImageGuid.length() != 0)
		{
			bstrPropName = A2WBSTR((LPCSTR)"SignatureImageId");
			bstrPropValue = A2WBSTR((LPCSTR)SigImageGuid.c_str());

			ChangeOrAddProperty(bstrPropName, bstrPropValue);
			SysFreeString(bstrPropName);
			SysFreeString(bstrPropValue);
		}
		if(UseHMAC == TRUE)
		{
			if (HMACKey.Length() == 0) // No password provided, use sig image hash as password
			{
				// call function to get sig file and create hash and return value in 
				// pfxpassword & set HMAC as signature method
				charInputFile = (char *)CapturedSignatureFileName;
				BSTR bstrCapturedSignatureFileName = A2WBSTR((LPCSTR)CapturedSignatureFileName);
				if (ReadAllBin(bstrCapturedSignatureFileName, &binFileData, &fileSize) == S_FALSE)
				{
					setError(SigHandle, IO_ERROR);
					zFree(charInputFile);
					SysFreeString(bstrCapturedSignatureFileName);
					return FALSE;
				}
				SysFreeString(bstrCapturedSignatureFileName);
//				zFree(charInputFile);
				
				
				DS_DATA_BLOB objectBlob;				
				
				BYTE *pbDigest=NULL;

				DWORD cbDigest=0;

				objectBlob.cbData = fileSize;	
				objectBlob.pbData = NULL;
				if(!(objectBlob.pbData = (unsigned char*)zMalloc(objectBlob.cbData+1)))
				{
					SigImageGuid = "";
					setError(SigHandle, MEMORY_FAULT);
					zFree(binFileData);
					return FALSE;
				}
				memcpy(objectBlob.pbData,binFileData,fileSize);
				
				if (!crComputeHash(
					CALG_SHA1,
					NULL,
					&objectBlob,			// (in) Object data
					NULL,				// (in/out) digest: pointer 
					&cbDigest,
					SigHandle)) {
					setError(SigHandle, DIGEST_ERROR);
					err=TRUE; 

				}	//&pKey			
				
				if (pbDigest) zFree (pbDigest);
				pbDigest = NULL;
				if(!(pbDigest = (BYTE*)zMalloc(cbDigest+1)))	{
					setError(SigHandle, MEMORY_FAULT);
					err=TRUE; 
				}
				if (!crComputeHash(
					CALG_SHA1,
					NULL,
					&objectBlob,			// (in) Object data
					pbDigest,				// (in/out) digest: pointer 
					&cbDigest,
					SigHandle)) {			// (in/out) digest: size 
					setError(SigHandle, DIGEST_ERROR);
					err=TRUE; 
				}	//&pKey	
				
				// allocate memory				
				if (HMACPassword.pbData) zFree (HMACPassword.pbData);
				HMACPassword.pbData = NULL;
				HMACPassword.cbData = 0;
				cbDigest = cbDigest-18;
				// encode digest value
				HMACPassword.cbData = base64encodeSize(cbDigest);
				if(!(HMACPassword.pbData = (BYTE*)zMalloc(HMACPassword.cbData+1))) {
					setError(SigHandle, MEMORY_FAULT);
					err=TRUE; 
				}
				memset (HMACPassword.pbData,0,HMACPassword.cbData+1);
				if (base64encode(pbDigest,cbDigest,HMACPassword.pbData,HMACPassword.cbData)==-1) {
					setError(SigHandle, BASE64_ERROR);
					err=TRUE; 
				}
				if (objectBlob.pbData) zFree (objectBlob.pbData);
				objectBlob.pbData = NULL;
				objectBlob.cbData = 0;				
				
			}
		}
	}

	//if (LicObj.isLicenseDemo())
	//{
	//	bstrPropName = A2WBSTR((LPCSTR)"SecureXMLLicenseUsed");;
	//	bstrPropValue = A2WBSTR((LPCSTR)"Non Production Demo License");
	//	ChangeOrAddProperty(bstrPropName, bstrPropValue);
	//	SysFreeString(bstrPropName);
	//	SysFreeString(bstrPropValue);
	//}

	//if (LicObj.isLicenseDevelopment())
	//{
	//	bstrPropName = A2WBSTR((LPCSTR)"SecureXMLLicenseUsed");;
	//	bstrPropValue = A2WBSTR((LPCSTR)"Non Production Development License");
	//	ChangeOrAddProperty(bstrPropName, bstrPropValue);
	//	SysFreeString(bstrPropName);
	//	SysFreeString(bstrPropValue);
	//}

	// create <Object ID="Properties">
	if (PropertyCount>0) {
	// create <Reference> for PROPERTIES
		sprintf (pout,"REF_Properties_%s",SigHandle->sig->param_id);
		sprintf (pout2,"#PROPERTIES_%s",SigHandle->sig->param_id);
		if ((pref = xsGenerateReference(pout,IFM_SHA1,NULL,pout2, SigHandle))==NULL) 
		{
			for (j=0; j < certificateListCount; j++)
			{
				zFree(certificateList[j]);
			}
			zFree(certificateList);
			if (freeSigningCert == TRUE)
				zFree(signingCert);
			return S_FALSE;
		}
		if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
		{
			trAlgorithm = CANON_EXC_NO_COMM;
		}
		else if (CanonicalizationMethod == EXC_WITH_COMMENTS)
		{
			trAlgorithm = CANON_EXC_WITH_COMM;
		}
		if (trAlgorithm)
			if ((ptrs = xsGenerateTransform(trAlgorithm,pref,SigHandle))!=NULL) 
			{
				if (InclusiveNamespaceList != NULL)
				{
					unsigned char *tmp = (unsigned char *)zMalloc(strlen(InclusiveNamespaceList) + 1);
					strcpy((char *)tmp, InclusiveNamespaceList);
					ptrs->prefixList = (unsigned char *)tmp;
				}
			}


		sprintf (pout2,"PROPERTIES_%s",SigHandle->sig->param_id);
		if ((xsGenerateObject(pout2,NULL,(const char**)Properties,PropertyCount,SigHandle))==NULL) 
		{
			for (j=0; j < certificateListCount; j++)
			{
				zFree(certificateList[j]);
			}
			zFree(certificateList);
			if (freeSigningCert == TRUE)
				zFree(signingCert);
			return S_FALSE;
		}
	}

	//if (TimeStampOption == TIME_RFC_867_SRVR)
	//{
	//	unsigned char *wTimeStampURL = HeapW2A(TimeStampURL.m_str);
	//	xsCoreAddTimestamp(SigHandle, wTimeStampURL);
	//	zFree(wTimeStampURL);
	//}

	/* 
	 * sign it and generate other XML sections
	 */

	if(UseHMAC != TRUE)
	{
		if (calculateDigestOnly == FALSE)
		{
			if (!xsSign(
				(const char *)signingCert,	// base64 encoded certificate with public key, or base64 encoded pfx data
				&PfxPassword,		// if signingCert is NULL, it is HMAC key, if certData is Pfx it is the password
									// ignored otherwise
				SigHandle
 				)) 
			{
				for (j=0; j < certificateListCount; j++)
				{
					zFree(certificateList[j]);
				}
				zFree(certificateList);
				if (freeSigningCert == TRUE)
					zFree(signingCert);
				return FALSE;
			}
			*signedXML = xsCoreGenerateXMLSec(SigHandle, signedXmlSize);
		}
		else // Calculate digest only. Signature value will be calculated on the client computer
		{
			/*
			* Get signed info
			*/
			PDS_DATA_BLOB pcrBlob=NULL;	// <SignedInfo> data
			BYTE *pbHash;			// SHA1 hash
			DWORD dwHashLen=20;			// 
			PBYTE pbSignature=NULL;		// signature BLOB
			DWORD dwSigLen=0;			// signature BLOB
			PBYTE pbPublicKey=NULL;		// (out) pub key BLOB
			DWORD dwKeyLen=0;			// (out) pub key BLOB
			DWORD sigalgtype=0;
			if (signingCert == NULL)
			{
				PfxPassword.cbData = 0;
				if (PfxPassword.pbData != NULL)
					zFree(PfxPassword.pbData);
				PfxPassword.pbData = NULL;
			}

			pbHash = (BYTE *)zMalloc(dwHashLen);

			if ((pcrBlob = xsGetSignedInfo(
				(const char *)signingCert,
				&PfxPassword,		// if signingCert is NULL, it is HMAC key, if certData is Pfx it is the password
				SigHandle))==NULL) 
			{
				for (j=0; j < certificateListCount; j++)
				{
					zFree(certificateList[j]);
				}
				zFree(certificateList);
				if (freeSigningCert == TRUE)
					zFree(signingCert);
				return FALSE;
			}

			/*
			* Get SHA1 digest of it
			*/
			if (!crComputeHash(
				CALG_SHA1,
				NULL,		// HMAC key, not used
				pcrBlob,	// (in) Object data
				pbHash,		// (in/out) digest: pointer 
				&dwHashLen,	// (in/out) 20 for SHA1
				SigHandle)) 
			{	
				for (j=0; j < certificateListCount; j++)
				{
					zFree(certificateList[j]);
				}
				zFree(certificateList);
				if (freeSigningCert == TRUE)
					zFree(signingCert);
				if (pcrBlob != NULL)
				{
					if (pcrBlob->pbData != NULL)
						zFree(pcrBlob->pbData);
					zFree(pcrBlob);
				}
				xmlFree(pcrBlob->pbData);
				zFree(pcrBlob);
				return FALSE;
			}
			*signedXML = pbHash;
			*signedXmlSize = dwHashLen;
			xmlFree(pcrBlob->pbData);
			zFree(pcrBlob);
		}
	}
	else 
	{
		/*
		 * HMAC as signature method 
		 */ 
		if (xsCoreSetSignatureMethod(NULL,ALG_HMACSHA1,0,NULL, SigHandle)!=TRUE) 
		{
			return FALSE;
		}

		/*
		 * This might not work on Windows 95/98
		 */
		xsCoreSetCSP((unsigned char *)"Microsoft Enhanced Cryptographic Provider v1.0",SigHandle);

		if (!xsSign(
				NULL,	// base64 encoded certificate with public key, or base64 encoded pfx data
				&HMACPassword,	// if signingCert is NULL, it is HMAC key, if certData is Pfx it is the password
									// ignored otherwise
				SigHandle
 				)) 
			{
				return FALSE;
			}
		*signedXML = xsCoreGenerateXMLSec(SigHandle, signedXmlSize);
	}
	
	/*
	 * get result XML as string and save it
	 */
//	xmlDocPtr tmpDocPtr = NULL;


	if (UseHMAC == FALSE)
	{
		if ((certificateListCount != 0) && (certificateList != NULL))
		{
			for (i=0; i < certificateListCount; i++)
			{
				zFree(certificateList[i]);
			}
			zFree(certificateList);
		}
		if (freeSigningCert == TRUE)
			zFree(signingCert);
	}
	if (AttachedObjectCount != 0)
	{
		for (i=0; i < AttachedObjectCount; i++)
			if (pbData[i] != NULL)
				zFree(pbData[i]);
		zFree(pbData);
	}

	if ((EnvelopingFlag == DETACHED) ||
		(DetachedObjectCount != 0))
	{
		if (SigHandle->locNumber != 0)
		{
			for (i=0; i < (UINT)SigHandle->locNumber; i++)
			{
				if (SigHandle->locArray[i] != NULL)
				{
					if (SigHandle->locArray[i]->fullPath != NULL)
					{
						zFree(SigHandle->locArray[i]->fullPath);
						SigHandle->locArray[i]->fullPath = NULL;
					}
					if (SigHandle->locArray[i]->sigId != NULL)
					{
						zFree(SigHandle->locArray[i]->sigId);
						SigHandle->locArray[i]->sigId = NULL;
					}
					if (SigHandle->locArray[i]->URI != NULL)
					{
						zFree(SigHandle->locArray[i]->URI);
						SigHandle->locArray[i]->URI = NULL;
					}
					zFree(SigHandle->locArray[i]);
					SigHandle->locArray[i] = NULL;
				}
			}
			zFree(SigHandle->locArray);
			SigHandle->locArray = NULL;
			SigHandle->locNumber = 0;
		}
	}
	if ((Base64EncodeXML == TRUE) && (calculateDigestOnly == FALSE))
	{
	// Base64 encode
		int srcSize;
		unsigned int cbData;
		unsigned char *pbData;
		srcSize = *signedXmlSize;
		cbData = base64encodeSize(srcSize);

		if(!(pbData = (BYTE *)zMalloc(cbData+1)))
		{
			zFree(*signedXML);
			setError(SigHandle, MEMORY_FAULT);
			return FALSE;
		}
		if ((cbData  = base64encode(*signedXML,srcSize,(unsigned char*)pbData,cbData+1))==-1) 
		{
			setError(SigHandle, BASE64_ERROR);
			zFree(*signedXML);
			zFree(pbData);
			return FALSE;
		}
		*(pbData+cbData)='\0';
		xmlFree(*signedXML);
		*signedXML = pbData;
		*signedXmlSize = cbData;
	}
	ExitObjectLog;	 
	return TRUE;
}

STDMETHODIMP CSignature::PFXExportActiveCertificate(BSTR password, BSTR *pfxFilePath)
{
	BSTR certId;
	EnterObjectLog;
	if ((CurrentCertificate != NOT_INITIALIZED) && (CurrentCertificate != USE_PFX_CERT) && (CurrentCertificate != USE_BASE64_CERT))
	{
		certId = A2WBSTR((LPCSTR)cV[CurrentCertificate]->serialNumber);
		PFXExportCertificate(certId, password, pfxFilePath);
		SysFreeString(certId);
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_HostName(BSTR *pVal)
{
	char lpBuffer[MAX_PATH];
	unsigned long lpnSize=MAX_PATH;

USES_CONVERSION;
	EnterObjectLog;
#ifdef WIN32
	GetComputerName(lpBuffer,           // name buffer
				&lpnSize                // size of name buffer
				);
#else
	gethostname(lpBuffer, MAX_PATH);
#endif
	*pVal = A2WBSTR((LPCSTR)lpBuffer);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_TimeStampURL(BSTR *pVal)
{
	EnterObjectLog;
	*pVal = TimeStampURL.Copy();
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_TimeStampURL(BSTR newVal)
{
	EnterObjectLog;
	TimeStampURL.Empty();
	TimeStampURL = newVal;
	ExitObjectLog;
	return S_OK;
}


STDMETHODIMP CSignature::get_TimeStamping(BOOL *pVal)
{
	EnterObjectLog;
	*pVal = TimeStampOption;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_TimeStamping(BOOL newVal)
{
	EnterObjectLog;
	TimeStampOption = newVal;
	if (TimeStampURL.Length() == 0)
	{
		TimeStampURL = A2WBSTR((LPCSTR) defaultTimeServiceUrl);
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_HostOsType(long *pVal)
{
	EnterObjectLog;
#ifdef WIN32
	*pVal = CLicense::getHostOsType();
#endif
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_CrlChecking(BOOL *pVal)
{
	EnterObjectLog;
	*pVal = CertVerifyParams.verificationOptions & VERIFY_CRL;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_CrlChecking(BOOL newVal)
{
	EnterObjectLog;
	if (DoDCompliance == FALSE)
		if (newVal)
			CertVerifyParams.verificationOptions |= VERIFY_CRL;
		else
			CertVerifyParams.verificationOptions &= (~VERIFY_CRL);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_SigCertStatus(long sigIndex, BSTR atTime, long timeFormat, long *pVal)
{
	HRESULT hResult=S_OK;
	*pVal = FALSE;
	char *tsAttrText, *tsData;
	CComBSTR localAtTime;
	SYSTEMTIME tsSysTime;
	LPSYSTEMTIME ptsSysTime;
	char *charLocAtTime;
	BOOL result;
	int timeStampFormat=0;

	USES_CONVERSION;
	//DebugBreak();
	EnterObjectLog;
	if (sgArr==NULL)
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	if ((sigIndex >= signum) || (sigIndex < 0))
	{
		setError(SigHandle, SIG_INDEX_ERROR);
		return S_FALSE;
	}

	localAtTime = atTime;
	CertVerifyParams.recCrlCount = sgArr[sigIndex]->crlDataCount;
	CertVerifyParams.recCrlList  = (LPSTR *)sgArr[sigIndex]->crlDataList;

	if ((CertVerifyParams.usedCrlCount != 0) &&
		(CertVerifyParams.usedCrlList != NULL))
	{
		for (UINT i=0; i < CertVerifyParams.usedCrlCount; i++)
		{
			if (CertVerifyParams.usedCrlList[i] != NULL)
				zFree(CertVerifyParams.usedCrlList[i]);
		}
		zFree(CertVerifyParams.usedCrlList);
		CertVerifyParams.usedCrlList = NULL;
		CertVerifyParams.usedCrlCount = 0;
	}

	if (sgArr[sigIndex]->certificatesCount != 0) // There is a certificate available
	{
		BSTR tsProp=NULL;
		CComBSTR propName;
		// Check to see if signature time stamp is provided

		if (localAtTime.Length() == 0) // No time is provided
		{
			tsAttrText = (char *)zMalloc(MAX_TS_PROP_ATTR);
			memset(tsAttrText,0,MAX_TS_PROP_ATTR);

			strcat(tsAttrText, (const char *)TIME_STAMP_PREFIX);
			if (sgArr[sigIndex]->sigId != NULL)
			{
				strcat(tsAttrText, (const char *)sgArr[sigIndex]->sigId);
			}

			propName = tsAttrText;
			zFree(tsAttrText);

			GetSigPropValueByName(sigIndex, propName.m_str, &tsProp);
			if (tsProp != NULL)
			{
				tsData = (char *)HeapW2A(tsProp);
				SysFreeString(tsProp);
				tsProp = NULL;
				//Time stamp string has been found. Now lets find out what format it is in
				propName = TIME_STAMP_FORMAT;
				GetSigPropValueByName(sigIndex, propName.m_str, &tsProp);
				if (tsProp == NULL)
				{
					timeStampFormat = TIME_RFC;
				}
				else
				{
					if (!(wcscmp((const WCHAR *)L"1",tsProp)))
					{
						timeStampFormat = TIME_VB_NOW;
					}
					else
						if (!(wcscmp((const WCHAR *)L"2", tsProp)))
						{
							timeStampFormat = TIME_JS_UTC;
						}
						else
						{
							timeStampFormat = TIME_RFC;
						}
				}
				// Now covert this time to SYSTEMTIME and call crVerifyCertificate
				switch (timeStampFormat)
				{
					case TIME_RFC:		ptsSysTime = rfcTimeToSystem((unsigned char *)tsData);
										break;
					case TIME_VB_NOW:	ptsSysTime = vbNowTimeToSystem((unsigned char *)tsData);
										break;
					case TIME_JS_UTC:	ptsSysTime = jsUtcTimeToSystem((BYTE *)tsData);
										break;
					default:			ptsSysTime = rfcTimeToSystem((unsigned char *)tsData);
				}
				zFree(tsData);
				if (useCam)
					result = crVerifyCertificateUsingCam(sgArr[sigIndex]->certificates,
										sgArr[sigIndex]->certificatesCount,
										ptsSysTime, 
										NULL, 
										&CertVerifyParams,
										SigHandle);
				else
					if (useOcsp)
						result = crVerifyCertificateUsingOcsp(sgArr[sigIndex]->certificates,
											sgArr[sigIndex]->certificatesCount,
											ptsSysTime, 
											NULL, 
											&CertVerifyParams,
											SigHandle);
					else
						result = crVerifyCertificate(sgArr[sigIndex]->certificates,
											sgArr[sigIndex]->certificatesCount,
											ptsSysTime, 
											NULL, 
											&CertVerifyParams,
											SigHandle);

				if (result == FALSE)
				{
					*pVal = axGetLastError(SigHandle);
				}
				else
					*pVal = 0;
				zFree(ptsSysTime);
				SysFreeString(tsProp);
			}
			else // TimeStamp Not Found so use current system time
			{
#ifdef WIN32
				GetSystemTime(&tsSysTime);
#else
				GetSystemTimeLinux(&tsSysTime);
#endif
				if (useCam)
					result = crVerifyCertificateUsingCam(sgArr[sigIndex]->certificates,
										sgArr[sigIndex]->certificatesCount,
										&tsSysTime, 
										NULL, 
										&CertVerifyParams,
										SigHandle);
				else
					if (useOcsp)
						result = crVerifyCertificateUsingOcsp(sgArr[sigIndex]->certificates,
											sgArr[sigIndex]->certificatesCount,
											&tsSysTime, 
											NULL, 
											&CertVerifyParams,
											SigHandle);
					else
						result = crVerifyCertificate(sgArr[sigIndex]->certificates,
											sgArr[sigIndex]->certificatesCount,
											&tsSysTime, 
											NULL, 
											&CertVerifyParams,
											SigHandle);

				if (result == FALSE)
				{
					*pVal = axGetLastError(SigHandle);
				}
				else
					*pVal = 0;
			}
		} // No Time Provided
		else
		{ // Time was provided

			charLocAtTime = (char *)HeapW2A(atTime);
			// Now covert this time to SYSTEMTIME and call crVerifyCertificate

			switch(timeFormat)
			{
				case TIME_RFC:
						ptsSysTime = rfcTimeToSystem((unsigned char *)charLocAtTime);
						break;
				case TIME_VB_NOW:
						ptsSysTime = vbNowTimeToSystem((unsigned char *)charLocAtTime);
						localTimeToUtcTime(ptsSysTime);
						break;
				case TIME_JS_UTC:
						ptsSysTime = jsUtcTimeToSystem((unsigned char *)charLocAtTime);
						break;
				default:
					break;
			}
			zFree(charLocAtTime);

			if (useCam)
				result = crVerifyCertificateUsingCam(sgArr[sigIndex]->certificates,
									sgArr[sigIndex]->certificatesCount,
									ptsSysTime, 
									NULL, 
									&CertVerifyParams,
									SigHandle);
			else
				if (useOcsp)
					result = crVerifyCertificateUsingOcsp(sgArr[sigIndex]->certificates,
										sgArr[sigIndex]->certificatesCount,
										ptsSysTime, 
										NULL, 
										&CertVerifyParams,
										SigHandle);
				else
					result = crVerifyCertificate(sgArr[sigIndex]->certificates,
										sgArr[sigIndex]->certificatesCount,
										ptsSysTime, 
										NULL, 
										&CertVerifyParams,
										SigHandle);
			if (result == FALSE)
			{
				*pVal = axGetLastError(SigHandle);
			}
			else
				*pVal = 0;
			zFree(ptsSysTime);

		}
	} // There is a certificate available
	else
		*pVal = CERT_NOT_FOUND;
	ExitObjectLog;
	return hResult;

}

STDMETHODIMP CSignature::VerifyX509CertCRL(BSTR certData, BSTR atTime, long timeFormat, BOOL *pVal)
{
	CComBSTR locCertData, locAtTime;
	unsigned char *charCertData;
	SYSTEMTIME	tsSysTime;
	CComBSTR localAtTime;
	LPSYSTEMTIME ptsSysTime;
	char *charLocAtTime;

	USES_CONVERSION;

	EnterObjectLog;

	locCertData = certData;
	locAtTime	= atTime;

	if ((CertVerifyParams.usedCrlCount != 0) &&
		(CertVerifyParams.usedCrlList != NULL))
	{
		for (UINT i=0; i < CertVerifyParams.usedCrlCount; i++)
		{
			if (CertVerifyParams.usedCrlList[i] != NULL)
				zFree(CertVerifyParams.usedCrlList[i]);
		}
		zFree(CertVerifyParams.usedCrlList);
		CertVerifyParams.usedCrlList = NULL;
		CertVerifyParams.usedCrlCount = 0;
	}

	if (locCertData.Length() != 0) // Certificate data present
	{
		charCertData = HeapW2A(certData);

		if (locAtTime.Length() == 0) // Use system time
		{
#ifdef WIN32
			GetSystemTime(&tsSysTime);
#else
			GetSystemTimeLinux(&tsSysTime);
#endif
			*pVal = CheckCertificateValidity(charCertData, 
										&tsSysTime, 
										NULL, 
										&CertVerifyParams,
										SigHandle);
		}
		else
		{ 
			charLocAtTime = (char *)HeapW2A(atTime);
			// Now covert this time to SYSTEMTIME and call CheckCertificateValidity

			switch(timeFormat)
			{
				case TIME_RFC:
					ptsSysTime = rfcTimeToSystem((unsigned char *)charLocAtTime);
					break;
			case TIME_VB_NOW:
					ptsSysTime = vbNowTimeToSystem((unsigned char *)charLocAtTime);
					localTimeToUtcTime(ptsSysTime);
					break;
			case TIME_JS_UTC:
					ptsSysTime = jsUtcTimeToSystem((unsigned char *)charLocAtTime);
					break;
			default:
					break;
			}
			charLocAtTime = (char *)HeapW2A(atTime);

			*pVal = CheckCertificateValidity(charCertData, 
										ptsSysTime, 
										NULL, 
										&CertVerifyParams,
										SigHandle);
			zFree(ptsSysTime);
		}
		zFree(charCertData);

	}
	else
	{
		setError(SigHandle, CERT_NOT_FOUND);
		*pVal = FALSE;
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::VerifyPFXCertCRL(BSTR pfxFileName, BSTR pfxPassword, BSTR atTime, long timeFormat, BOOL *pVal)
{
	DWORD fileSize,dwBytesToWrite;
	char *certData=NULL;
	unsigned char *binFileData=NULL;
//	unsigned char *charPfxFileName;
	unsigned char *b64PfxDataPtr;

	unsigned char *ptr;
	unsigned int *szPtr;
	unsigned int sizeM;
	DS_DATA_BLOB blobPfxPassword;
	CComBSTR locAtTime;
	SYSTEMTIME tsSysTime;
	LPSYSTEMTIME ptsSysTime;
	char *charLocAtTime;

USES_CONVERSION;
// DebugBreak();
	CComBSTR	tmpCcBstr;

	EnterObjectLog;
	tmpCcBstr = pfxFileName;
	if (tmpCcBstr.Length() == 0)
	{
		setError(SigHandle, FILE_NOT_FOUND);
		return S_FALSE;
	}

	blobPfxPassword.cbData =0;
	locAtTime = atTime;

	if ((CertVerifyParams.usedCrlCount != 0) &&
		(CertVerifyParams.usedCrlList != NULL))
	{
		for (UINT i=0; i < CertVerifyParams.usedCrlCount; i++)
		{
			if (CertVerifyParams.usedCrlList[i] != NULL)
				zFree(CertVerifyParams.usedCrlList[i]);
		}
		zFree(CertVerifyParams.usedCrlList);
		CertVerifyParams.usedCrlList = NULL;
		CertVerifyParams.usedCrlCount = 0;
	}

//	charPfxFileName = HeapW2A(pfxFileName);
	
	if (ReadAllBin(pfxFileName, &binFileData, &fileSize) == S_FALSE)
	{
		setError(SigHandle, IO_ERROR);
//		zFree(charPfxFileName);
		return S_FALSE;
	}

	ptr = (unsigned char *)pfxPassword;

	if (ptr != NULL)
	{
		szPtr = (unsigned int *)(ptr - sizeof(int));
		sizeM = *szPtr;

		if (sizeM == 0)
			blobPfxPassword.pbData = NULL;
		else
		{
			sizeM += 2; // BSTR size does not include the terminating null so add 2 to the size
			blobPfxPassword.pbData		= (unsigned char *) zMalloc(sizeM);
			blobPfxPassword.cbData = sizeM;
			memcpy(blobPfxPassword.pbData, ptr, sizeM);
#ifdef NSS
			SECItem s;
			s.data = blobPfxPassword.pbData;
			s.len  = blobPfxPassword.cbData;
			SwapUnicodeBytes(&s);
#endif
		}
	}
	else {
		blobPfxPassword.pbData = NULL;
		blobPfxPassword.cbData = 0;
	}

	dwBytesToWrite	= base64encodeSize(fileSize);
	
	b64PfxDataPtr = (unsigned char *) zMalloc (dwBytesToWrite+1);
	
	memset(b64PfxDataPtr,0,dwBytesToWrite+1);
	dwBytesToWrite = base64encode(binFileData,fileSize, b64PfxDataPtr,dwBytesToWrite+1);
	zFree(binFileData);

	if (locAtTime.Length() == 0) // Use system time
	{
#ifdef WIN32
		GetSystemTime(&tsSysTime);
#else
		GetSystemTimeLinux(&tsSysTime);
#endif

		*pVal = CheckCertificateValidity(b64PfxDataPtr, 
									&tsSysTime, 
									&blobPfxPassword, 
									&CertVerifyParams,
									SigHandle);
	}
	else
	{ 
		charLocAtTime = (char *)HeapW2A(atTime);
		// Now covert this time to SYSTEMTIME and call CheckCertificateValidity
		switch(timeFormat)
		{
			case TIME_RFC:
				ptsSysTime = rfcTimeToSystem((unsigned char *)charLocAtTime);
				break;
			case TIME_VB_NOW:
				ptsSysTime = vbNowTimeToSystem((unsigned char *)charLocAtTime);
				localTimeToUtcTime(ptsSysTime);
				break;
			case TIME_JS_UTC:
				ptsSysTime = jsUtcTimeToSystem((unsigned char *)charLocAtTime);
				break;
			default:
				break;
		}
		zFree(charLocAtTime);

		*pVal = CheckCertificateValidity(b64PfxDataPtr, 
									ptsSysTime, 
									&blobPfxPassword, 
									&CertVerifyParams,
									SigHandle);
		zFree(ptsSysTime);
	}
//	zFree(charPfxFileName);
	zFree(b64PfxDataPtr);
	if (blobPfxPassword.cbData!=0)
		zFree(blobPfxPassword.pbData);

	ExitObjectLog;
	return S_OK;
}

#ifdef WIN32
// D300C133-A6F6-4FB4-A734-4865FBF5A3B1
//
//	typedef struct {
//		unsigned long  Data1;
//		unsigned short Data2;
//		unsigned short Data3;
//		byte           Data4[ 8 ];
//	} GUID;
void GuidToString(GUID *guid, char *guidStr)
{
	unsigned short data1, data2, data3, data4, data5, data6, data7, data8;
	data1 = *(unsigned char *)&guid->Data4[0];
	data2 = *(unsigned char *)&guid->Data4[1];
	data3 = *(unsigned char *)&guid->Data4[2];
	data4 = *(unsigned char *)&guid->Data4[3];
	data5 = *(unsigned char *)&guid->Data4[4];
	data6 = *(unsigned char *)&guid->Data4[5];
	data7 = *(unsigned char *)&guid->Data4[6];
	data8 = *(unsigned char *)&guid->Data4[7];

	sprintf(guidStr, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", 
			guid->Data1, 
			guid->Data2,
			guid->Data3,
			data1, data2, data3, data4,
			data5, data6, data7, data8);

}

/* AddPhysicalSignature(xmlNodePtr sigNode, xmlNodePtr signedInfoNode, char *charSigId)
 *
 * This function will not add any thing to the input XML if anything is missing
 *
 * If everything is fine, it will add an <Object> element Id="SignatureImage_charSigId" to sigNode
 *
 * <Object Id="SignatureImage_charSigId" Encoding="http://www.w3.org/2000/09/xmldsig#base64">
 *
 * It will also add a <Reference> element to the signedInfoNode
 *
 * <Reference Type="http://www.w3.org/2000/09/xmldsig#Object" URI="#SignatureImage_charSigId">
 *	<Transforms>
 *		<Transform Algorithm="http://www.w3.org/2000/09/xmldsig#base64" /> 
 *	</Transforms>
 * </Reference>
 */


void CSignature::AddPhysicalSignature(xmlNodePtr sigNode, xmlNodePtr signedInfoNode, char *charSigId)
{
	DS_DATA_BLOB crBlob;
	DWORD fileSize;
	unsigned char *binFileData;
	BOOL captureResult=FALSE;
	char *charInputFile;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	FILE *fHandle;
	xmlNodePtr cur=NULL, parent=NULL;
	unsigned char objectId[MAX_PATH];
	unsigned char uriPath[MAX_PATH + 1];
	int sigIdLength=0;
	TEMP_FILE_INFO *tmpFilePath = NULL;
	BSTR bstrCapturedSigFileName = NULL;
	EnterObjectLog;

	if ((sigNode == NULL) || (signedInfoNode == NULL) || (charSigId == NULL))
		return; // Do Nothing

	sigIdLength = strlen(SIG_IMAGE_OBJECT_ID_PREFIX) + strlen(charSigId);

	if (sigIdLength >= MAX_PATH)
		return;

	strcpy((char *)objectId, SIG_IMAGE_OBJECT_ID_PREFIX);
	strcat((char *)objectId, charSigId);

	strcpy((char *)uriPath, "#");
	strcat((char *)uriPath, (const char *)objectId);

	// First decide where to get the signature image from

	switch (PhysicalSigUsage)
	{
		case	FILE_PHYSICAL_SIG:	
									charInputFile = (char *)PhysicalSignatureFileName;
									if (strlen((const char *)charInputFile) == 0)
									{
										break;
									}
									else
									{
										if ((fHandle = fopen(charInputFile, "r")) == NULL)
											break;
										else
											fclose(fHandle);
									}
#ifdef WIN32
									CoCreateGuid(&sigGuid);
									GuidToString(&sigGuid, guidStr);
#else
									uuid_generate(sigGuid);
									uuid_unparse(sigGuid, guidStr);
#endif
									SigImageGuid = guidStr;

									memset((void *)CapturedSignatureFileName, 0, MAX_PATH);
									ShowFileSignature(charInputFile, (char *)CapturedSignatureFileName, SignatureCaptured, &SignatureCaptureWindowDim, guidStr);
									if (strlen((const char *)CapturedSignatureFileName) == 0)
									{
										SigImageGuid = "";
										SignatureCaptured = FALSE;
										break;
									}
									tmpFilePath = new (TEMP_FILE_INFO);
									strcpy((char *)tmpFilePath->fileName, (const char *)CapturedSignatureFileName);
									tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
									SignatureCaptured = TRUE;

									bstrCapturedSigFileName = A2WBSTR((LPCSTR)CapturedSignatureFileName);
									if (ReadAllBin(bstrCapturedSigFileName, &binFileData, &fileSize) == S_FALSE)
									{
										SigImageGuid = "";
										setError(SigHandle, IO_ERROR);
										zFree(charInputFile);
										SysFreeString(bstrCapturedSigFileName);
										return;
									}
									SysFreeString(bstrCapturedSigFileName);
									crBlob.cbData = base64encodeSize(fileSize);
									// allocate memory
									crBlob.pbData = NULL;
									if(!(crBlob.pbData = (unsigned char*)zMalloc(crBlob.cbData+1)))
									{
										SigImageGuid = "";
										setError(SigHandle, MEMORY_FAULT);
										zFree(binFileData);
										return;
									}
									if (base64encode((unsigned char *)binFileData,fileSize,(unsigned char*)crBlob.pbData,crBlob.cbData)==-1) 
									{
										SigImageGuid = "";
										setError(SigHandle, MEMORY_FAULT);
										zFree(crBlob.pbData);
										zFree(binFileData);
										return;
									}
									*(crBlob.pbData+crBlob.cbData)='\0';

									zFree(binFileData);

									// Add Object element to the Signature node

									cur = xmlNewNode(NULL,(const unsigned char *)"Object");
									xmlAddChild(sigNode, cur);
									xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)objectId);
									xmlNewProp(cur, (const unsigned char *)"Encoding", (const unsigned char *)ALG_BASE64);
									xmlNodeSetContent(cur,(const unsigned char *)crBlob.pbData);
									zFree(crBlob.pbData);

									// Now add the reference element to the SignedInfo node

									/*
									 * Reference
									*/
									cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
									cur = xmlAddChild(signedInfoNode,cur);
									xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)uriPath);
									parent = cur;

									/*
									 * Transforms
									 */
	
									cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
									cur = xmlAddChild(parent,cur);
									parent = cur;

									/*
									 * Transform
									 */
	
									cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
									xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_BASE64);
									cur = xmlAddChild(parent,cur);


									break;

		case	CAPTURE_PHYSICAL_SIG:
#ifdef WIN32
									CoCreateGuid(&sigGuid);
									GuidToString(&sigGuid, guidStr);
#else
									uuid_generate(sigGuid);
									uuid_unparse(sigGuid, guidStr);
#endif
									SigImageGuid = guidStr;
				
									memset((void *)CapturedSignatureFileName, 0, MAX_PATH);
									captureResult = GetPhysicalSignatureFromTablet((char *)CapturedSignatureFileName, MAX_PATH, guidStr);
									
									if (captureResult)
									{
										SignatureCaptured = TRUE;
										
									}
									else
									{	
										captureResult = GetPhysicalSignatureFromMouse((char *)CapturedSignatureFileName, MAX_PATH, guidStr);
										
										if (captureResult)
										{
											SignatureCaptured = TRUE;
										}
										else
										{
											SigImageGuid = "";
											SignatureCaptured = FALSE;
											return;
										}
									}
									tmpFilePath = new (TEMP_FILE_INFO);
									strcpy((char *)tmpFilePath->fileName, (const char *)CapturedSignatureFileName);
									tmpFileList->insert(tmpFileList->begin(), tmpFilePath);

//									charInputFile = (char *)CapturedSignatureFileName;
									bstrCapturedSigFileName = A2WBSTR((LPCSTR)CapturedSignatureFileName);
									if (ReadAllBin(bstrCapturedSigFileName, &binFileData, &fileSize) == S_FALSE)
									{
										SigImageGuid = "";
										setError(SigHandle, IO_ERROR);
//										zFree(charInputFile);
										SysFreeString(bstrCapturedSigFileName);
										return;
									}
									SysFreeString(bstrCapturedSigFileName);
									crBlob.cbData = base64encodeSize(fileSize);
									// allocate memory
									crBlob.pbData = NULL;
									if(!(crBlob.pbData = (unsigned char*)zMalloc(crBlob.cbData+1)))
									{
										SigImageGuid = "";
										setError(SigHandle, MEMORY_FAULT);
										zFree(binFileData);
										return;
									}
									if (base64encode((unsigned char *)binFileData,fileSize,(unsigned char*)crBlob.pbData,crBlob.cbData)==-1) 
									{
										SigImageGuid = "";
										setError(SigHandle, MEMORY_FAULT);
										zFree(crBlob.pbData);
										zFree(binFileData);
										return;
									}
									*(crBlob.pbData+crBlob.cbData)='\0';

									zFree(binFileData);

									// Add Object element to the Signature node

									cur = xmlNewNode(NULL,(const unsigned char *)"Object");
									xmlAddChild(sigNode, cur);
									xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)objectId);
									xmlNewProp(cur, (const unsigned char *)"Encoding", (const unsigned char *)ALG_BASE64);
									xmlNodeSetContent(cur,(const unsigned char *)crBlob.pbData);
									zFree(crBlob.pbData);

									// Now add the reference element to the SignedInfo node

									/*
									 * Reference
									*/
									cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
									cur = xmlAddChild(signedInfoNode,cur);
									xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)uriPath);
									parent = cur;

									/*
									 * Transforms
									 */
	
									cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
									cur = xmlAddChild(parent,cur);
									parent = cur;

									/*
									 * Transform
									 */
	
									cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
									xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_BASE64);
									cur = xmlAddChild(parent,cur);

									break;
		case	BUF_PHYSICAL_SIG:
									if (PhysicalSignatureB64Str != NULL)
									{
										// Add Object element to the Signature node

										cur = xmlNewNode(NULL,(const unsigned char *)"Object");
										xmlAddChild(sigNode, cur);
										xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)objectId);
										xmlNewProp(cur, (const unsigned char *)"Encoding", (const unsigned char *)ALG_BASE64);
										xmlNodeSetContent(cur,(const unsigned char *)PhysicalSignatureB64Str);

										// Now add the reference element to the SignedInfo node
										/*
										* Reference
										*/
										cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
										cur = xmlAddChild(signedInfoNode,cur);
										xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)uriPath);
										parent = cur;

										/*
										* Transforms
										*/
										cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
										cur = xmlAddChild(parent,cur);
										parent = cur;

										/*
										* Transform
										*/
										cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
										xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_BASE64);
										cur = xmlAddChild(parent,cur);
									}
									break;
		case	NO_PHYSICAL_SIG:	

									break;
		default:
									break;
	}
	ExitObjectLog;
}

BOOL CSignature::GetPhysicalSignatureFromTablet(char *filePathBuf, int bufSize, char *guidStr)
{
	HRESULT hr;
	IUnknown *pUnknown;
	IePad *pEPad;
	BSTR bstrFilePath;
	char *charFilePath;
	BSTR bstrGuidStr;

USES_CONVERSION;
	EnterObjectLog;
	hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		return FALSE;
	}
	hr = CoCreateInstance(CLSID_ePad, NULL, CLSCTX_INPROC_SERVER, 
						  IID_IUnknown, (void **) &pUnknown);
	if (FAILED(hr))
	{
		CoUninitialize();
		return FALSE;
	}
	hr = pUnknown->QueryInterface(IID_IePad, (void **) &pEPad);
	if (FAILED(hr))
	{
		pUnknown->Release();
		CoUninitialize();
		return FALSE;
	}
	pUnknown->Release();
	pEPad->put_UpperX(SignatureCaptureWindowDim.left);
	pEPad->put_UpperY(SignatureCaptureWindowDim.top);
	pEPad->put_Width(SignatureCaptureWindowDim.right);
	pEPad->put_Height(SignatureCaptureWindowDim.bottom);
	bstrGuidStr = A2WBSTR(guidStr);
	hr = pEPad->GetPhysicalSignature(bstrGuidStr, &bstrFilePath);
	SysFreeString(bstrGuidStr);

	if (FAILED(hr))
	{
		pEPad->Release();
		CoUninitialize();
		return FALSE;
	}
	charFilePath = (char *)HeapW2A(bstrFilePath);
	strcpy(filePathBuf, charFilePath);
	zFree(charFilePath);
	pEPad->Release();
	CoUninitialize();
	ExitObjectLog;
	return TRUE;
}

BOOL CSignature::GetPhysicalSignatureFromMouse(char *filePathBuf, int bufSize, char *guidStr)
{
	IUnknown *pUnknown;
	ICaptureImage *captureImageObject;
	BSTR bstrFilePath;
	char *charFilePath;
	BOOL result = FALSE;

	USES_CONVERSION;
	EnterObjectLog;
#ifdef WIN32
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(__uuidof(CCaptureImage), NULL, CLSCTX_INPROC_SERVER, 
						IID_IUnknown, (void **) &pUnknown);
	if (FAILED(hr))
	{
		CoUninitialize();
		return S_FALSE;
	}

	hr = pUnknown->QueryInterface(__uuidof(ICaptureImage), (void **) &captureImageObject);
	if (FAILED(hr))
	{
		pUnknown->Release();
		CoUninitialize();
		return S_FALSE;
	}
	pUnknown->Release();

	bstrFilePath = captureImageObject->CaptureMouseSignature(_bstr_t(guidStr));
	captureImageObject->Release();
	CoUninitialize();
	if (bstrFilePath != NULL)
	{
		result = TRUE;
		charFilePath = (char *)HeapW2A(bstrFilePath);
		strcpy(filePathBuf, charFilePath);
		zFree(charFilePath);
	}
#endif
	ExitObjectLog;
	return result;

//	return CaptureMouseSignature(filePathBuf, SignatureCaptured, &SignatureCaptureWindowDim, guidStr);
}

void CSignature::AddWindowImage(xmlNodePtr sigNode, xmlNodePtr signedInfoNode, char *charSigId)
{
	DS_DATA_BLOB crBlob;
	DWORD fileSize;
	unsigned char *binFileData;
	BOOL captureResult=FALSE;
	xmlNodePtr cur=NULL, parent=NULL;
	unsigned char objectId[MAX_PATH+1];
	unsigned char uriPath[MAX_PATH + 1];
	int sigIdLength=0;

	EnterObjectLog;
	if ((sigNode == NULL) || (signedInfoNode == NULL) || (charSigId == NULL))
		return; // Do Nothing

	sigIdLength = strlen(WINDOW_IMAGE_OBJECT_ID_PREFIX) + strlen(charSigId);

	if (sigIdLength >= MAX_PATH)
		return;

	strcpy((char *)objectId, WINDOW_IMAGE_OBJECT_ID_PREFIX);
	strcat((char *)objectId, charSigId);
	strcpy((char *)uriPath, "#");
	strcat((char *)uriPath, (const char *)objectId);

	captureResult = CaptureCurrentWindowImage ((char *)WindowImageFileName, NULL);
	if (captureResult)
	{
		BSTR bstrCapturedWinFileName = A2WBSTR((LPCSTR)WindowImageFileName);
		if (ReadAllBin(bstrCapturedWinFileName, &binFileData, &fileSize) == S_FALSE)
		{
			setError(SigHandle, IO_ERROR);
			SysFreeString(bstrCapturedWinFileName);
			return;
		}
		SysFreeString(bstrCapturedWinFileName);
		crBlob.cbData = base64encodeSize(fileSize);
		// allocate memory
		crBlob.pbData = NULL;
		if(!(crBlob.pbData = (unsigned char*)zMalloc(crBlob.cbData+1)))
		{
			setError(SigHandle, MEMORY_FAULT);
			zFree(binFileData);
			return;
		}
		if (base64encode((unsigned char *)binFileData,fileSize,(unsigned char*)crBlob.pbData,crBlob.cbData)==-1) 
		{
			setError(SigHandle, MEMORY_FAULT);
			zFree(crBlob.pbData);
			zFree(binFileData);
			return;
		}
		*(crBlob.pbData+crBlob.cbData)='\0';

		zFree(binFileData);

		// Add Object element to the Signature node

		cur = xmlNewNode(NULL,(const unsigned char *)"Object");
		xmlAddChild(sigNode, cur);
		xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)objectId);
		xmlNewProp(cur, (const unsigned char *)"Encoding", (const unsigned char *)ALG_BASE64);
		xmlNodeSetContent(cur,(const unsigned char *)crBlob.pbData);
		zFree(crBlob.pbData);

		// Now add the reference element to the SignedInfo node

		/*
		 * Reference
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
		cur = xmlAddChild(signedInfoNode,cur);
		xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)uriPath);
		parent = cur;

		/*
		 * Transforms
		 */

		cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		 * Transform
		 */

		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_BASE64);
		cur = xmlAddChild(parent,cur);
#ifdef WIN32
		DeleteFile(WindowImageFileName);
#else
		unlink(WindowImageFileName);
#endif
	}
	ExitObjectLog;
}
#endif

STDMETHODIMP CSignature::get_AddWindowImage(BOOL *pVal)
{
	EnterObjectLog;
#ifdef WIN32
	*pVal = AddWindowImageFlag;
#endif
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_AddWindowImage(BOOL newVal)
{
	EnterObjectLog;
#ifdef WIN32
	AddWindowImageFlag = newVal;
#endif
	ExitObjectLog;
	return S_OK;
}


STDMETHODIMP CSignature::SignXMLXpathStr(BSTR xmlStr, BSTR xpathExp, BSTR signatureId, BSTR *signedXMLStr)
{
	char *charXMLStr=NULL, *charSigId=NULL, *curCharSigId=NULL;
	keyinfo *ki=NULL;
	unsigned char *charSignedXMLStr=NULL;
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL, parent=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlChar *mem=NULL;
	int iSize=0;
	CComBSTR	sigId;
	CComBSTR tmpXmlStr;
	CComBSTR tmpXpathStr;
	char *charTest;
	unsigned char *ptr, *newPtr=NULL, *curPtr=NULL;
	unsigned int *szPtr;
	unsigned int sizeM;
	xmlXPathContextPtr xpathPtr=NULL;
	xmlXPathObjectPtr xpathResultPtr=NULL;
	char *ptemp=NULL;
	BOOL templateFound=FALSE;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	UINT i;
	char *equalPtr;
	BOOL freeNewPtr=FALSE;

	EnterObjectLog;	
	//if (! LicObj.checkLicense()) {
	//	setError(SigHandle, INVALID_SECUREXML_LIC);
	//	return S_FALSE;
	//}
	//if (! LicObj.getSignAllowed()) {
	//	setError(SigHandle, NO_SIGNING_LIC);
	//	return S_FALSE;
	//}
	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	USES_CONVERSION;


	tmpXmlStr = xmlStr;
	if (tmpXmlStr.Length() == 0)
	{
		setError(SigHandle, XML_PARSER_ERROR);
		return S_FALSE;
	}

	BOOL freeCharSigId = FALSE;
	sigId = signatureId;
	if (sigId.Length() == 0)
		charSigId = NULL;
	else
	{
		charSigId = (char *)HeapW2A(signatureId);
		freeCharSigId = TRUE;
	}


	if (Base64DecodeXML == FALSE)
	{
		ptr = (unsigned char *)xmlStr;
		szPtr = (unsigned int *)(ptr - sizeof(int));
		sizeM = (*szPtr);

		if (((*ptr == 0xff) && (*(ptr +1) == 0xfe)) ||
			((*ptr == 0xfe) && (*(ptr +1) == 0xff)))
		{
			// There is no need to put the UTF 16 header since the data is already in utf-16 format
			newPtr = ptr;
		}
		else
		{
			newPtr = (unsigned char *)zMalloc(sizeM + 4);
			freeNewPtr = TRUE;

			FileEncoding(newPtr);
//			*newPtr = 0xFF;
//			*(newPtr + 1) = 0xFE;

			memcpy(newPtr+2, ptr, sizeM + 2);
			sizeM += 4;
		}
	}
	else
	{
		ptr = HeapW2A(xmlStr);
		sizeM = strlen((const char *)ptr);
		sizeM = base64decodeSize(sizeM);
		newPtr = (unsigned char *)zMalloc(sizeM+1);
		freeNewPtr = TRUE;
		if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
		{
			zFree(ptr);
			zFree(newPtr);
			if (freeCharSigId)
				zFree(charSigId);
			setError(SigHandle, BASE64_ERROR);
			return S_FALSE;
		}
		zFree(ptr);
	}

	if (! LicObj.getSignAllowed()) 
	{
		if (!LicObj.getFormSignAllowed(newPtr, sizeM, SigHandle))
		{
			setError(SigHandle, NO_SIGNING_LIC);
			if (freeCharSigId)
				zFree(charSigId);
			return S_FALSE;
		}
	}

	// original document
	doc = xmlParseMemory((const char *)newPtr,sizeM);
	if (freeNewPtr == TRUE)
		zFree(newPtr);

	if (!doc) 
	{
		setError(SigHandle, XML_PARSER_ERROR);
		if (freeCharSigId)
			zFree(charSigId);
		return S_FALSE;
	}

	if (charSigId == NULL)
		if (SignatureID.Length() == 0)
		{
//#ifdef WIN32
//			CoCreateGuid(&sigGuid);
//			GuidToString(&sigGuid, guidStr);
//#else
//			uuid_generate(sigGuid);
//			uuid_unparse(sigGuid, guidStr);
//#endif
//			charSigId = guidStr;
		}
		else
		{
			charSigId = (char *)HeapW2A(SignatureID.m_str);
			freeCharSigId = TRUE;
		}

	root = xmlDocGetRootElement(doc);
	if (charSigId != NULL)
		sigNode = xsSigNodeById((const xmlNodePtr) root, (const xmlChar *)charSigId);
	else
		sigNode = xsSigNodeWithNoIdNoSigValue((const xmlNodePtr) root);
	if (sigNode != NULL)
	{
		templateFound = TRUE;
		cur = sigNode->xmlChildrenNode;
		while (cur)
		{
				if (!(xmlStrcmp(cur->name, (const xmlChar *) "SignedInfo")))
				{
					signedInfoNode = cur;
					break;
				}
				cur = cur->next;
		}  // end while cur != NULL
	}
	  
	  if (templateFound == FALSE) // A Signature element with matching Id was not found
	  {
		  // Add a new Signature element
		/*
		* Signature
		*/

		cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
		sigNode = cur;
		if (charSigId != NULL)
			xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
		cur = xmlAddChild(root,cur);
		//xmlNewNs(cur,(const unsigned char *)"http://www.w3.org/2000/09/xmldsig#",(const unsigned char *)NULL);

		xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
		parent = cur;

	
		/*
		* SignedInfo
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
		signedInfoNode = cur;
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		 * Canonicalization Method
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
		switch(CanonicalizationMethod)
		{
			case WITH_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
				break;
			case WITHOUT_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
				break;
			case EXC_WITH_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
				break;
			case EXC_WITHOUT_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
				break;
			default:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
		}
		cur = xmlAddChild(parent,cur);
		/*
		* Reference
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
		cur = xmlAddChild(parent,cur);
		xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)"");
		parent = cur;

		/*
		* Transforms
		*/
	
		cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		* Transform
		*/
		if ((CanonicalizationMethod == EXC_WITH_COMMENTS) ||
			(CanonicalizationMethod == EXC_WITHOUT_COMMENTS))
		{
			cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			}
			cur = xmlAddChild(parent,cur);
			parent = cur;
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_WITH_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_NO_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			cur = xmlAddChild(parent,cur);
			parent = parent->parent;
		}
		/*
		* Transform
		*/
	
		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_ENVELOPED_SIG);
		cur = xmlAddChild(parent,cur);

		/*
		* Transform
		*/
		
		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_XPATH);
		cur = xmlAddChild(parent,cur);
		parent = cur;

		cur = xmlNewNode(NULL,(const unsigned char *)"XPath");
		if (XpathNamespaceCount != 0)
		{
			for (i=0; i < XpathNamespaceCount; i++)
			{
				equalPtr = StrChr(XpathNamespaceList[i], '=');
				if (equalPtr == NULL)
				{
					xmlNewNs(cur, (const unsigned char *)XpathNamespaceList[i], (const unsigned char *)NULL);
				}
				else
				{
					*equalPtr = '\0';
					xmlNewNs(cur, (const unsigned char *)equalPtr+1, (const unsigned char *)XpathNamespaceList[i]);
					*equalPtr = '=';
				}
			}
		}
		cur = xmlAddChild(parent,cur);
		tmpXpathStr = xpathExp;
		if (tmpXpathStr.Length() == 0)
		{
			setError(SigHandle, XML_PARSER_ERROR);
			if (freeCharSigId)
				zFree(charSigId);
			return S_FALSE;
		}

		charTest = (char *)HeapW2A(xpathExp);
		xmlNodeSetContent(cur,(const unsigned char *)charTest);
		zFree(charTest);
	  }
	  else // A Signature element with matching Id was found
	  {
		parent = signedInfoNode;
		/*
		* Reference
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
		cur = xmlAddChild(parent,cur);
		xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)"");
		parent = cur;

		/*
		* Transforms
		*/
	
		cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		* Transform
		*/
		if ((CanonicalizationMethod == EXC_WITH_COMMENTS) ||
			(CanonicalizationMethod == EXC_WITHOUT_COMMENTS))
		{
			cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			}
			cur = xmlAddChild(parent,cur);
			parent = cur;
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_WITH_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_NO_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			cur = xmlAddChild(parent,cur);
			parent = parent->parent;
		}

		/*
		* Transform
		*/
	
		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_ENVELOPED_SIG);
		cur = xmlAddChild(parent,cur);

		/*
		* Transform
		*/
		
		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_XPATH);
		cur = xmlAddChild(parent,cur);
		parent = cur;

		cur = xmlNewNode(NULL,(const unsigned char *)"XPath");
		if (XpathNamespaceCount != 0)
		{
			for (i=0; i < XpathNamespaceCount; i++)
			{
				equalPtr = StrChr(XpathNamespaceList[i], '=');
				if (equalPtr == NULL)
				{
					xmlNewNs(cur, (const unsigned char *)XpathNamespaceList[i], (const unsigned char *)NULL);
				}
				else
				{
					*equalPtr = '\0';
					xmlNewNs(cur, (const unsigned char *)equalPtr+1, (const unsigned char *)XpathNamespaceList[i]);
					*equalPtr = '=';
				}
			}
		}
		cur = xmlAddChild(parent,cur);
		tmpXpathStr = xpathExp;
		if (tmpXpathStr.Length() == 0)
		{
			setError(SigHandle, XML_PARSER_ERROR);
			if (freeCharSigId)
				zFree(charSigId);
			return S_FALSE;
		}

		charTest = (char *)HeapW2A(xpathExp);
		xmlNodeSetContent(cur,(const unsigned char *)charTest);
		zFree(charTest);
	  }
#ifdef WIN32
	  if (AddWindowImageFlag == TRUE)
		  AddWindowImage(sigNode, signedInfoNode, charSigId);

	  if (PhysicalSigUsage != NO_PHYSICAL_SIG)		  
		  AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif
	/*
	 * init Signature. crBlob contains XML - envelope document
	 */
	short tmpEnvFlag = EnvelopingFlag;
	EnvelopingFlag = ENVELOPED;

	if (!(CreateSigFromTmplBlob(doc,charSigId, &charSignedXMLStr, &iSize)))
	{
		if (charSignedXMLStr != NULL)
			xmlFree(charSignedXMLStr);
		EnvelopingFlag = tmpEnvFlag;
		if (freeCharSigId)
			zFree(charSigId);
		return S_FALSE;
	}
	else
	{
		if (charSignedXMLStr != NULL)
		{
			unsigned char *dataPtr = charSignedXMLStr;

			if (((*dataPtr == 0xff) && (*(dataPtr +1) == 0xfe)) ||
				((*dataPtr == 0xfe) && (*(dataPtr +1) == 0xff)))
			{
				// This is a UTF-16 file, so no need to do a char * to BSTR conversion
				// Just allocate memory and copy data and put the size information in front
				*signedXMLStr = ::SysAllocStringByteLen((LPCSTR)(dataPtr), iSize);
				xmlFree(dataPtr);
			}
			else
			{
				*signedXMLStr = A2WBSTR((LPCSTR)dataPtr, iSize);
				if (Base64EncodeXML == TRUE)
					zFree(dataPtr);
				else
					xmlFree(dataPtr);
			}
		}
	}
	EnvelopingFlag = tmpEnvFlag;
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_UseHMAC(BOOL *pVal)
{
	EnterObjectLog;
	*pVal = UseHMAC;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_UseHMAC(BOOL newVal)
{
	EnterObjectLog;
	UseHMAC = newVal;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_HMACPassword(BSTR *pVal)
{
	EnterObjectLog;
	*pVal = HMACKey.Copy();
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_HMACPassword(BSTR newVal)
{
	HMACKey = newVal;

	EnterObjectLog;
	if (HMACKey.Length() != 0)
	{
		if (HMACPassword.pbData) 
			zFree (HMACPassword.pbData);
		HMACPassword.pbData = NULL;
		HMACPassword.cbData = 0;								
		HMACPassword.cbData = base64encodeSize(HMACKey.Length());
		if(!(HMACPassword.pbData = (BYTE*)zMalloc(HMACPassword.cbData+1))) 
		{
			setError(SigHandle, MEMORY_FAULT);
			return FALSE;
		}
		memset (HMACPassword.pbData,0,HMACPassword.cbData+1);
		if (base64encode((unsigned char *)HMACKey.m_str,HMACKey.Length(),HMACPassword.pbData,HMACPassword.cbData)==-1) 
		{
			setError(SigHandle, BASE64_ERROR);
			return FALSE;
		}
	}
	else
	{
		if (HMACPassword.pbData) 
			zFree (HMACPassword.pbData);
		HMACPassword.pbData = NULL;
		HMACPassword.cbData = 0;
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::ChangeOrAddProperty(BSTR propertyName, BSTR propertyValue)
{
	int propIndex;
	CComBSTR tmpCcomBSTR;
	BOOL found=FALSE;
	unsigned char *utf8CharStr = NULL;
	int bstrByteSize = 0;

USES_CONVERSION;
	EnterObjectLog;
	tmpCcomBSTR = propertyName;

	if (tmpCcomBSTR.Length() == 0)
		return S_FALSE;

	tmpCcomBSTR = propertyValue;
	if (tmpCcomBSTR.Length() == 0)
		return S_FALSE;

	utf8CharStr = HeapW2A(propertyName);

	for (propIndex = 0; propIndex < PropertyCount; propIndex++)
	{
		if (Properties[propIndex] != NULL)
		{
			if (strstr((const char *)Properties[propIndex],(const char *)utf8CharStr) == NULL)
			{ // Property Name Not Found
				continue;
			}
			else
			{
				found = TRUE;
				break;
			}
		}
	}
	zFree(utf8CharStr);

	BSTR bstrPropStr = NULL;
	BSTR midBstr = SysAllocString(L"=");
	BSTR tempBstr1 = NULL;
	VarBstrCat(propertyName, midBstr, &tempBstr1);
	VarBstrCat(tempBstr1, propertyValue, &bstrPropStr);
	SysFreeString(midBstr);
	SysFreeString(tempBstr1);
	if (found)
	{
		zFree(Properties[propIndex]);
		Properties[propIndex] = HeapW2A(bstrPropStr);
	}
	else
	{
		put_Properties(0, PropertyCount, bstrPropStr);
	}
	SysFreeString(bstrPropStr);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_DetailedVerificationFlag(BOOL newVal)
{
	EnterObjectLog;
	DetailedVerificationReportFlag = newVal;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::CaptureLiveSignature(BSTR *signatureFilePath)
{
	BOOL captureResult=FALSE;
	HWND	desktopHwnd;
	TEMP_FILE_INFO	*tmpFilePath = NULL;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];

	EnterObjectLog;
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (!LicObj.getSignAllowed()) {
		setError(SigHandle, NO_SIGNING_LIC);
		return S_FALSE;
	}

	USES_CONVERSION;

#ifdef WIN32
	CoCreateGuid(&sigGuid);
	GuidToString(&sigGuid, guidStr);
#else
	uuid_generate(sigGuid);
	uuid_unparse(sigGuid, guidStr);
#endif
	SigImageGuid = guidStr;
	if (PhysicalSigUsage != FILE_PHYSICAL_SIG)
	{
#ifdef WIN32
		SignatureCaptured = FALSE;
		desktopHwnd = GetDesktopWindow();	
		GetClientRect(desktopHwnd, &SignatureCaptureWindowDim);		
		SignatureCaptureWindowDim.left = (SignatureCaptureWindowDim.right / 2) - 175; // UpperX		
		SignatureCaptureWindowDim.top = (SignatureCaptureWindowDim.bottom / 2) - 125; // UpperY		
		SignatureCaptureWindowDim.bottom = 250; // Height
		SignatureCaptureWindowDim.right = 350;  // Width

		memset((void *)CapturedSignatureFileName, 0, MAX_PATH);
		captureResult = GetPhysicalSignatureFromTablet((char *)CapturedSignatureFileName, MAX_PATH, guidStr);
		if (!captureResult)
		{	
			captureResult = GetPhysicalSignatureFromMouse((char *)CapturedSignatureFileName, MAX_PATH, guidStr);
		}
#endif
	}
	else
	{
#ifdef WIN32
		char *charInputFile = (char *)PhysicalSignatureFileName;
		FILE *fHandle = NULL;

		if (strlen((const char *)charInputFile) == 0)
		{
			captureResult = FALSE;
			goto putResultOut;
		}
		else
		{
			if ((fHandle = fopen(charInputFile, "r")) == NULL)
			{
				captureResult = FALSE;
				goto putResultOut;
			}
			else
				fclose(fHandle);
		}

		memset((void *)CapturedSignatureFileName, 0, MAX_PATH);
		ShowFileSignature(charInputFile, (char *)CapturedSignatureFileName, SignatureCaptured, &SignatureCaptureWindowDim, guidStr);
		if (strlen((const char *)CapturedSignatureFileName) == 0)
		{
			SigImageGuid = "";
			SignatureCaptured = FALSE;
			captureResult = FALSE;
			goto putResultOut;
		}
		captureResult = TRUE;
#endif
	}
putResultOut:
	if (captureResult)
	{
		*signatureFilePath = A2WBSTR((LPCSTR)CapturedSignatureFileName);
		tmpFilePath = new (TEMP_FILE_INFO);
		strcpy((char *)tmpFilePath->fileName, (const char *)CapturedSignatureFileName);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
		ExitObjectLog;
		return S_OK;
	}
	else
	{
		*signatureFilePath = A2WBSTR((LPCSTR) NULL);
		SigImageGuid = "";
		return S_FALSE;
	}
}

STDMETHODIMP CSignature::SignDataStr(BSTR dataStrPtr, BSTR *signedXMLStr)
{
	char *charDataStr=NULL;
	keyinfo *ki=NULL;
	unsigned char *charSignedXMLStr=NULL;
	xmlValidCtxtPtr ctxt;
	xmlDocPtr doc =NULL;
	xmlDtdPtr dtd =NULL;
	xmlNodePtr root=NULL, cur=NULL, rootNode=NULL, parent=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlChar *mem=NULL;
	xmlNsPtr curNs;
	int iSize=0;
	CComBSTR tmpDataStr;
	char *charSigId;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	char elementId[50];

	EnterObjectLog;

	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (! LicObj.getSignAllowed()) {
		setError(SigHandle, NO_SIGNING_LIC);
		return S_FALSE;
	}
	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	USES_CONVERSION;

	tmpDataStr = dataStrPtr;
	if (tmpDataStr.Length() == 0)
	{
		setError(SigHandle, NULL_DATA_STRING);
		return S_FALSE;
	}
	
	doc = xmlNewDoc((const unsigned char *)"1.0");

	// DTD
    dtd = xmlNewDtd(doc, BAD_CAST "SignatureEnvelope",NULL,NULL);
	// create DTD validation context
    ctxt = xmlNewValidCtxt();
	// add ATTLIST
	xmlAddAttributeDecl(ctxt, dtd, BAD_CAST "infomosaic:SignedObject",
                    BAD_CAST "Id", NULL, 
					XML_ATTRIBUTE_ID, XML_ATTRIBUTE_IMPLIED, 
					NULL, NULL);		    
	
    xmlAddChild((xmlNodePtr) doc, (xmlNodePtr) dtd);
	xmlFreeValidCtxt(ctxt);

	// document, namespace, element name, element content
	cur = xmlNewDocNode(doc,NULL,(const unsigned char *)"SignatureEnvelope",NULL);

	// if you want any namespace definition here
	curNs = xmlNewNs(cur,(const unsigned char *)"http://www.infomosaic.net/SignData/DTD.htm",(const unsigned char *)"infomosaic");
	xmlSetNs(cur,curNs);

	// add root element
	xmlDocSetRootElement(doc,cur);
	rootNode = cur;
	/*
	 * SignedDataString
	*/
	cur = xmlNewNode(curNs,(const unsigned char *)"SignedObject"); // Using the parent element's name space
	cur = xmlAddChild(rootNode,cur);
#ifdef WIN32
	CoCreateGuid(&sigGuid);
	GuidToString(&sigGuid, &elementId[1]);
#else
	uuid_generate(sigGuid);
	uuid_unparse(sigGuid, &elementId[1]);
#endif

	xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)&elementId[1]);
	xmlNewProp(cur, (const unsigned char *)"Encoding", (const unsigned char *)ALG_BASE64);
	elementId[0] = '#';

	charDataStr = (char *)HeapW2A(dataStrPtr);

	if (charDataStr == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		xmlFreeDoc(doc);
		return S_FALSE;
	}
	int encodedSize;
	unsigned char *encodedData;

	// Base64 encode
	encodedSize = base64encodeSize(strlen(charDataStr));
	if(!(encodedData = (unsigned char*)zMalloc(encodedSize+1)))
	{
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}
	if ((encodedSize = base64encode(	(unsigned char *)charDataStr,
						strlen(charDataStr),
						(unsigned char*)encodedData,
						encodedSize+1))==-1) 
	{
		setError(SigHandle, MEMORY_FAULT);
		zFree(encodedData);
		return S_FALSE;
	}
	*(encodedData+encodedSize)='\0';
	zFree(charDataStr);
	xmlNodeSetContent(cur,(const unsigned char *)encodedData);
	zFree(encodedData);
	/*
	 * Signature
	*/

	BOOL freeCharSigId = FALSE;
	if (SignatureID.Length() == 0)
	{
#ifdef WIN32
		CoCreateGuid(&sigGuid);
		GuidToString(&sigGuid, guidStr);
#else
		uuid_generate(sigGuid);
		uuid_unparse(sigGuid, guidStr);
#endif
		charSigId = guidStr;
	}
	else
	{
		charSigId = (char *)HeapW2A(SignatureID.m_str);
		freeCharSigId = TRUE;
	}

	cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
	sigNode = cur;
	xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
	cur = xmlAddChild(rootNode,cur);
	xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
	parent = cur;

	/*
	 * SignedInfo
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
	signedInfoNode = cur;
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	 * Canonicalization Method
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
	switch(CanonicalizationMethod)
	{
		case WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
			break;
		case WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
			break;
		case EXC_WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			break;
		case EXC_WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			break;
		default:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
	}
	cur = xmlAddChild(parent,cur);
	/*
	 * Reference
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
	cur = xmlAddChild(parent,cur);
	xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)elementId);
	parent = cur;

	/*
	 * Transforms
	 */
	
	cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	 * Transform
	 */
	
	cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
	xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_BASE64);
	cur = xmlAddChild(parent,cur);
#ifdef WIN32
	if (AddWindowImageFlag == TRUE)
		AddWindowImage(sigNode, signedInfoNode, charSigId);

	if (PhysicalSigUsage != NO_PHYSICAL_SIG)
		AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif
	short tmpEnvFlag = EnvelopingFlag;
	EnvelopingFlag = ENVELOPED;

	if (!(CreateSigFromTmplBlob(doc,charSigId, &charSignedXMLStr, &iSize)))
	{
		if (charSignedXMLStr != NULL)
			xmlFree(charSignedXMLStr);
		EnvelopingFlag = tmpEnvFlag;
		if (freeCharSigId)
			zFree(charSigId);
		return S_FALSE;
	}

	EnvelopingFlag = tmpEnvFlag;
	*signedXMLStr = A2WBSTR((const char *)charSignedXMLStr, iSize);
	if (Base64EncodeXML == TRUE)
		zFree(charSignedXMLStr);
	else
		xmlFree(charSignedXMLStr);
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_ExcludeSignerCertificate(BOOL newVal)
{
	EnterObjectLog;
	ExcludeSignerCertificateFlag = newVal;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_OverwriteFile(BOOL newVal)
{
	EnterObjectLog;
	OverwriteFileFlag = newVal;
	ExitObjectLog;
	return S_OK;
}


STDMETHODIMP CSignature::CoSignXMLStr(BSTR signedDataXMLStr, BSTR *coSignedXMLStr)
{
	char *charDataStr=NULL;
	keyinfo *ki=NULL;
	unsigned char *charSignedXMLStr=NULL;
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL, tmpNode, rootNode=NULL, parent=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlChar *mem=NULL;
	xmlNsPtr curNs=NULL;
	int iSize=0;
	CComBSTR tmpDataStr;
	char *charSigId, *elementEnc;
	BOOL result=0;
	xmlXPathContextPtr xpathPtr=NULL;
	xmlXPathObjectPtr xpathResultPtr=NULL;
	char *ptemp;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	unsigned char *ptr, *newPtr=NULL, *curPtr=NULL; 
	unsigned int *szPtr;
	unsigned int sizeM;
//	BOOL oldDetailedVerificationReportFlag;
	BOOL base64;
	int i, refNum=0;
	PURI_STATUS *refArr=NULL;
	PURI_PATH uriPath=NULL;
	
USES_CONVERSION;
	EnterObjectLog;
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (! LicObj.getSignAllowed()) {
		setError(SigHandle, NO_SIGNING_LIC);
		return S_FALSE;
	}
	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}
	tmpDataStr = signedDataXMLStr;
	if (tmpDataStr.Length() == 0)
	{
		setError(SigHandle, NULL_DATA_STRING);
		return S_FALSE;
	}

	/* we need detailed signature verification report so save the current status */
	//oldDetailedVerificationReportFlag = DetailedVerificationReportFlag;

	///* enable detailed verification */
	//DetailedVerificationReportFlag = 1;

	/* verify signature */
	VerifyXMLStr(signedDataXMLStr, &result);

	///* restore old flag value */
	//DetailedVerificationReportFlag = oldDetailedVerificationReportFlag;

	if (result == 0) // Signature verification failed
	{
		/* no need to set error code as VerifyXMLStr has already done that */
		return S_FALSE;
	}

	/* If the user has provided a signature Id, make sure there is no clash 
	 * with the signature in the input signed XML
	 */

	BOOL freeCharSigId = FALSE;
	if (SignatureID.Length() != 0)
	{ 
		charSigId = (char *)HeapW2A(SignatureID.m_str);
		freeCharSigId = TRUE;
		for (int i=0; i < signum; i++)
		{
			if (!strcmp((const char *)sgArr[i]->sigId, (const char *)charSigId))
			{
				setError(SigHandle, DUPLICATE_SIG_ID);
				zFree(charSigId);
				return S_FALSE; /* There already a signature with a matching Id */
			}
		}
	}
	else // no signature id provided, lets create one
	{
#ifdef WIN32
		CoCreateGuid(&sigGuid);
		GuidToString(&sigGuid, guidStr);
#else
		uuid_generate(sigGuid);
		uuid_unparse(sigGuid, guidStr);
#endif
		charSigId = guidStr;
	}


	/* The input has a valid signed XML so lets try to find element with Id == sData and sign it */

	BOOL freeNewPtr = FALSE;
	if (Base64DecodeXML == FALSE)
	{
		ptr = (unsigned char *)signedDataXMLStr;
		szPtr = (unsigned int *)(ptr - sizeof(int));
		sizeM = (*szPtr);

		if (((*ptr == 0xff) && (*(ptr + 1) == 0xfe)) ||
			((*ptr == 0xfe) && (*(ptr + 1) == 0xff)))
		{
			// There is no need to put the UTF 16 header since the data is already in utf-16 format
			newPtr = ptr;
		}
		else
		{
			newPtr = (unsigned char *)zMalloc(sizeM + 4);
			freeNewPtr = TRUE;

			FileEncoding(newPtr);
//			*newPtr = 0xFF;
//			*(newPtr + 1) = 0xFE;

			memcpy(newPtr+2, ptr, sizeM + 2);
			sizeM += 4;
		}
	}
	else
	{
		ptr = HeapW2A(signedDataXMLStr);
		sizeM = strlen((const char *)ptr);
		sizeM = base64decodeSize(sizeM);
		newPtr = (unsigned char *)zMalloc(sizeM+1);
		freeNewPtr = TRUE;
		if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
		{
			zFree(ptr);
			zFree(newPtr);
			setError(SigHandle, BASE64_ERROR);
			return S_FALSE;
		}
		zFree(ptr);
	}

	// original document
	doc = xmlParseMemory((const char *)newPtr,sizeM);
	if (freeNewPtr)
		zFree(newPtr);

	if (!doc) 
	{
		setError(SigHandle, XML_PARSER_ERROR);
		return S_FALSE;
	}

	ptemp = (char *)zMalloc(4096);

	sprintf (ptemp,"(//. | //@* | //namespace::*)[self::infomosaic:%s]","SignedObject");

	xpathPtr = xmlXPathNewContext(doc);

	// register additional namespace for the signature
	if (xmlXPathRegisterNs(xpathPtr,(const unsigned char *)"infomosaic",(const unsigned char *)"http://www.infomosaic.net/SignData/DTD.htm")!=0)
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
		setError(SigHandle, INVALID_SDATA_NS);
		xmlFreeDoc(doc);
		zFree(ptemp);
		return S_FALSE;
	}
	xmlXPathFreeObject(xpathResultPtr);

    rootNode = xmlDocGetRootElement(doc);

	/*
	 * Signature
	*/

	cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
	sigNode = cur;
	xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
	cur = xmlAddChild(rootNode,cur);
	xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
	parent = cur;

	/*
	 * SignedInfo
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
	signedInfoNode = cur;
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	 * Canonicalization Method
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
	switch(CanonicalizationMethod)
	{
		case WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
			break;
		case WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
			break;
		case EXC_WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			break;
		case EXC_WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			break;
		default:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
	}
	cur = xmlAddChild(parent,cur);
	/*
	 * Reference
	*/

	// Add a reference for each reference in the previous signature, except for Properties, 
	// Signature/Window Image and TimeStamp references
	// Lets only look at the first signature found i.e. i=0

	refNum = sgArr[0]->refNumber; // Number of URI in this signature
	refArr = sgArr[0]->refArray;  // The URI Array itself

	for (i=0; i < refNum; i++)
	{
		if (!(strstr((const char *)refArr[i]->URI,"SignatureImage_")) && 
			!(strstr((const char *)refArr[i]->URI,"WindowImage_")) &&
			!(strstr((const char *)refArr[i]->URI,TIME_STAMP_PREFIX)) && 
			//!(strstr((const char *)refArr[i]->URI,TIME_RFC_3161_PREFIX)) && 
			//!(strstr((const char *)refArr[i]->URI,TIME_SNTP_RFC_1305_PREFIX)) && 
			!(strstr((const char *)refArr[i]->URI,"PROPERTIES_")) &&
			!(strstr((const char *)refArr[i]->URI,"Comments_")))
		{

			cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
			cur = xmlAddChild(parent,cur);
			xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)refArr[i]->URI);
			parent = cur;

			sprintf (ptemp,"(//. | //@* | //namespace::*)[self::infomosaic:%s[@Id='%s']]","SignedObject", refArr[i]->URI+1);

			// apply XPath
			xpathResultPtr = xmlXPathEvalExpression((const unsigned char *)ptemp, xpathPtr);
			if (xpathResultPtr == NULL) 
			{
				// not found
				setError(SigHandle, INVALID_SDATA_NS);
				xmlFreeDoc(doc);
				zFree(ptemp);
				return S_FALSE;
			}


			if ((xpathResultPtr->nodesetval!=NULL) && (xpathResultPtr->nodesetval->nodeTab!=NULL)) 
			{
				// we found something, try to parse it
				// start traversing the document, looking for Signature's children elements
				tmpNode = xpathResultPtr->nodesetval->nodeTab[0];
				elementEnc = (char *)xmlGetProp(tmpNode, (const unsigned char *)"Encoding");
				if (elementEnc != NULL)
					if (!(strcmp(elementEnc, ALG_BASE64)))
						base64 = TRUE;
					else
						base64 = FALSE;
				else
					base64 = FALSE;

				zFree(elementEnc);

				/*
				 * Transforms
				 */
				
				cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
				cur = xmlAddChild(parent,cur);
				parent = cur;

				/*
				 * Transform
				 */

				if (base64)
				{
					cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_BASE64);
					cur = xmlAddChild(parent,cur);
				}
				else
				{
					/*
					* Transform
					*/
					if ((CanonicalizationMethod == EXC_WITH_COMMENTS) ||
						(CanonicalizationMethod == EXC_WITHOUT_COMMENTS))
					{
						cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
						if (CanonicalizationMethod == EXC_WITH_COMMENTS)
						{
							xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
						}
						else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
						{
							xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
						}
						cur = xmlAddChild(parent,cur);
						parent = cur;
						if (CanonicalizationMethod == EXC_WITH_COMMENTS)
						{
							cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
							xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_WITH_COMM,(const unsigned char *)"ec");
							xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
						}
						else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
						{
							cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
							xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_NO_COMM,(const unsigned char *)"ec");
							xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
						}
						cur = xmlAddChild(parent,cur);
						parent = parent->parent;
					}
					cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_XPATH);
					cur = xmlAddChild(parent,cur);
					parent = cur;

					cur = xmlNewNode(NULL,(const unsigned char *)"XPath");
					cur = xmlAddChild(parent,cur);
					xmlNodeSetContent(cur,(const unsigned char *)"self::text()");
				}
			}
			parent = signedInfoNode;
			xmlXPathFreeObject(xpathResultPtr);
		}
	}
	zFree(ptemp);
	xmlXPathFreeContext(xpathPtr);

#ifdef WIN32
	if (AddWindowImageFlag == TRUE)
		AddWindowImage(sigNode, signedInfoNode, charSigId);

	if (PhysicalSigUsage != NO_PHYSICAL_SIG)
		AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif
	short tmpEnvFlag = EnvelopingFlag;
	EnvelopingFlag = ENVELOPED;

	if (!(CreateSigFromTmplBlob(doc,
								charSigId, &charSignedXMLStr, &iSize)))
	{
		if (charSignedXMLStr != NULL)
			xmlFree(charSignedXMLStr);
		EnvelopingFlag = tmpEnvFlag;
		return S_FALSE;
	}
	EnvelopingFlag = tmpEnvFlag;
	*coSignedXMLStr = A2WBSTR((const char *)charSignedXMLStr, iSize);
	xmlFree(charSignedXMLStr);
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return S_OK;

}

STDMETHODIMP CSignature::CoSignFile(BSTR inputSignedXMLFile, BSTR outFileName, BSTR *outFilePath)
{
	BSTR coSignedXMLStr=NULL, inputXMLStr=NULL;
	HRESULT hr;

	EnterObjectLog;
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (!LicObj.getSignAllowed()) {
		setError(SigHandle, NO_SIGNING_LIC);
		return S_FALSE;
	}

	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}
	hr = ReadAll(inputSignedXMLFile, &inputXMLStr);
	if (hr != S_OK)
	{
		return S_FALSE; // File could not be read
	}

	hr = CoSignXMLStr(inputXMLStr, &coSignedXMLStr);
	if ((hr != S_OK) || (coSignedXMLStr == NULL))
	{
		SysFreeString(inputXMLStr);
		return S_FALSE; // Co signing failed
	}
	hr = SaveXMLStr(coSignedXMLStr, outFileName, outFilePath);
	if (hr != S_OK)
	{
		SysFreeString(inputXMLStr);
		SysFreeString(coSignedXMLStr);
		return S_FALSE; // file save failed
	}
	SysFreeString(inputXMLStr);
	SysFreeString(coSignedXMLStr);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::SignFiles(VARIANT fileList, BSTR outFileName, BSTR *outFilePath)
{
	UINT elementCount=0;
	UINT itemCount=0;
	BSTR	*bstrList=NULL;
	char *charInputFile=NULL;
	unsigned char *bareFileName=NULL;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char **objectId=NULL;
	const UINT maxGuidLen =	50;
	char guidStr[maxGuidLen];
	DS_DATA_BLOB crBlob;
	DWORD fileSize;
	unsigned char *binFileData=NULL;
	char *charSigId=NULL;
	xmlValidCtxtPtr ctxt;
	xmlDocPtr doc =NULL;
	xmlDtdPtr dtd =NULL;
	xmlNodePtr cur=NULL, rootNode=NULL, parent=NULL, commNode=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlNsPtr curNs=NULL;
	xmlChar *mem=NULL;
	int iSize=0;
	unsigned char *charSignedXMLStr=NULL;
	BSTR signedXMLBstr;
	HRESULT hResult=S_OK;
	short tmpEnvFlag = EnvelopingFlag;
	BOOL freeCharSigId = FALSE;

	EnterObjectLog;
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (!LicObj.getSignAllowed()) {
		setError(SigHandle, NO_SIGNING_LIC);
		return S_FALSE;
	}

	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

USES_CONVERSION;

	if ((fileList.vt != VT_BSTR) &&
		(fileList.vt != VT_DISPATCH) &&
		!(fileList.vt & VT_ARRAY) && 
		!(fileList.vt & VT_BYREF))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	bstrList = GetBstrArrayFromVariant(fileList, &itemCount);

	if ((bstrList == NULL) || (itemCount == 0))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	crBlob.cbData = 0;
	crBlob.pbData = NULL;

	doc = xmlNewDoc((const unsigned char *)"1.0");
	// DTD
    dtd = xmlNewDtd(doc, BAD_CAST "SignatureEnvelope",NULL,NULL);
	// create DTD validation context
    ctxt = xmlNewValidCtxt();
	// add ATTLIST
	xmlAddAttributeDecl(ctxt, dtd, BAD_CAST "infomosaic:SignedObject",
                    BAD_CAST "Id", NULL, 
					XML_ATTRIBUTE_ID, XML_ATTRIBUTE_IMPLIED, 
					NULL, NULL);		    
	
    xmlAddChild((xmlNodePtr) doc, (xmlNodePtr) dtd);
	xmlFreeValidCtxt(ctxt);
	// document, namespace, element name, element content
	cur = xmlNewDocNode(doc,NULL,(const unsigned char *)"SignatureEnvelope",NULL);

	// if you want any namespace definition here
	curNs = xmlNewNs(cur,(const unsigned char *)"http://www.infomosaic.net/SignData/DTD.htm",(const unsigned char *)"infomosaic");
	xmlSetNs(cur,curNs);

	// add root element
	xmlDocSetRootElement(doc,cur);
	rootNode = cur;
	/*
	 * SignedObject
	*/
	objectId = (char **) zMalloc(sizeof(char *) * itemCount);
	if (objectId == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		hResult = S_FALSE;
		goto ExitSignFiles;
	}
	memset(objectId, 0, sizeof(char *) * itemCount);

	for (elementCount=0; elementCount < itemCount; elementCount++)
	{
//		charInputFile = (char *)HeapW2A(bstrList[elementCount]);
		bareFileName  = xsRemoveBstrPath(bstrList[elementCount]);

		objectId[elementCount] = (char *) zMalloc (sizeof(char) * maxGuidLen);
		if (objectId[elementCount] == NULL)
		{
			setError(SigHandle, MEMORY_FAULT);
			hResult = S_FALSE;
			goto ExitSignFiles;
		}
#ifdef WIN32
		CoCreateGuid(&sigGuid);
		GuidToString(&sigGuid, objectId[elementCount]+1);
#else
		uuid_generate(sigGuid);
		uuid_unparse(sigGuid, objectId[elementCount] + 1);
#endif
		*objectId[elementCount] = '#';
		
		cur = xmlNewNode(curNs,(const unsigned char *)"SignedObject"); // Using the parent element's name space
		cur = xmlAddChild(rootNode,cur);
		xmlNewProp(cur, (const unsigned char *)"Encoding", (const unsigned char *)ALG_BASE64);
		xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)objectId[elementCount]+1);
		xmlNewProp(cur, (const unsigned char *)"FileName", (const unsigned char *)bareFileName);
		zFree(bareFileName);

		if (ReadAllBin(bstrList[elementCount], &binFileData, &fileSize) == S_FALSE)
		{
			setError(SigHandle, FILE_NOT_FOUND);
			zFree(charInputFile);
			xmlFreeDoc(doc);
			hResult = S_FALSE;
			goto ExitSignFiles;
		}
//		zFree(charInputFile);
		crBlob.cbData = base64encodeSize(fileSize);
		// allocate memory
		if(!(crBlob.pbData = (unsigned char*)zMalloc(crBlob.cbData+1)))
		{
			setError(SigHandle, MEMORY_FAULT);
			zFree(binFileData);
			xmlFreeDoc(doc);
			hResult = S_FALSE;
			goto ExitSignFiles;
		}
		if (base64encode((unsigned char *)binFileData,fileSize,(unsigned char*)crBlob.pbData,crBlob.cbData)==-1) 
		{
			setError(SigHandle, MEMORY_FAULT);
			zFree(crBlob.pbData);
			zFree(binFileData);
			xmlFreeDoc(doc);
			hResult = S_FALSE;
			goto ExitSignFiles;
		}
		*(crBlob.pbData+crBlob.cbData)='\0';

		zFree(binFileData);

		xmlNodeSetContent(cur,(const unsigned char *)crBlob.pbData);
		zFree(crBlob.pbData);
		crBlob.pbData = NULL;
		crBlob.cbData = 0;
	}
	/*
	 * Signature
	*/

	if (SignatureID.Length() == 0)
	{
#ifdef WIN32
		CoCreateGuid(&sigGuid);
		GuidToString(&sigGuid, guidStr);
#else
		uuid_generate(sigGuid);
		uuid_unparse(sigGuid, guidStr);
#endif
		charSigId = guidStr;
	}
	else
	{
		charSigId = (char *)HeapW2A(SignatureID.m_str);
		freeCharSigId = TRUE;
	}

	cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
	sigNode = cur;
	xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
	cur = xmlAddChild(rootNode,cur);
	xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
	parent = cur;

	/*
	 * SignedInfo
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
	signedInfoNode = cur;
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	 * Canonicalization Method
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
	switch(CanonicalizationMethod)
	{
		case WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
			break;
		case WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
			break;
		case EXC_WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			break;
		case EXC_WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			break;
		default:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
	}
	cur = xmlAddChild(parent,cur);
	/*
	 * Reference
	*/

	for (elementCount=0; elementCount < itemCount; elementCount++)
	{
		cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
		cur = xmlAddChild(parent,cur);
		xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)objectId[elementCount]);
		parent = cur;

		/*
		 * Transforms
		 */
		
		cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		 * Transform
		 */
		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_BASE64);
		cur = xmlAddChild(parent,cur);
		parent = signedInfoNode;
	}
#ifdef WIN32
	if (AddWindowImageFlag == TRUE)
		AddWindowImage(sigNode, signedInfoNode, charSigId);

	if (PhysicalSigUsage != NO_PHYSICAL_SIG)
		AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif
	EnvelopingFlag = ENVELOPED;

	if (!(CreateSigFromTmplBlob(doc,charSigId, &charSignedXMLStr, &iSize)))
	{
		if (charSignedXMLStr != NULL)
			xmlFree(charSignedXMLStr);
		hResult = S_FALSE;
		EnvelopingFlag = tmpEnvFlag;
		goto ExitSignFiles;
	}
	EnvelopingFlag = tmpEnvFlag;

	signedXMLBstr = A2WBSTR((const char *)charSignedXMLStr, iSize);
	if (Base64EncodeXML == TRUE)
		zFree(charSignedXMLStr);
	else
		xmlFree(charSignedXMLStr);

	hResult = SaveXMLStr(signedXMLBstr, outFileName, outFilePath);
	SysFreeString(signedXMLBstr);

ExitSignFiles:
	for (elementCount =0; elementCount < itemCount; elementCount++)
	{
		SysFreeString(bstrList[elementCount]);
		if (objectId != NULL)
			if (objectId[elementCount] != NULL)
				zFree(objectId[elementCount]);
	}
	zFree(bstrList);
	if (objectId != NULL)
		zFree(objectId);
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return hResult;
}

BSTR * CSignature::GetBstrArrayFromVariant(VARIANT fileList, UINT *itemCount)
{
	VARIANT **vA;
	UINT arrayDim, elementSize;
	long lBound, uBound;
	VARTYPE arrayType;
	long elementCount;
	BSTR	*bstrList = NULL;
	BSTR	tmpBstr;
	VARIANT *fList;
	CComBSTR tmpCcBstr;
	UINT numElements=0;

USES_CONVERSION;
	EnterObjectLog;
	fList = &fileList;
	*itemCount = 0;

	if (fileList.vt == 0x400c)
	{
		fList = fileList.pvarVal;
	}

	if (fList->vt == VT_BSTR) // This is just a BSTR so there is just one file being signed
	{
		tmpCcBstr = fList->bstrVal;
		if (tmpCcBstr.Length() == 0)
		{
			*itemCount = 0;
			goto getBstrArrayExit;
		}
		else
		{
			*itemCount = 1;
			bstrList = (BSTR *) zMalloc (sizeof(BSTR *));
			bstrList[0] = SysAllocString(fList->bstrVal);
		}
	}
	else
	{
		if (fList->vt & VT_ARRAY)
		{
			if (fList->vt & VT_BYREF)
			{
				arrayDim = SafeArrayGetDim(*(fList->pparray));
				SafeArrayGetLBound(*(fList->pparray), 1,  &lBound);
				SafeArrayGetUBound(*(fList->pparray), 1,  &uBound);
				SafeArrayGetVartype(*(fList->pparray), &arrayType);
				if (arrayType & VT_VARIANT)
				{
					vA = (VARIANT **)zMalloc(sizeof(VARIANT *) * (uBound - lBound + 1));
					for (elementCount=lBound; elementCount <= uBound; elementCount++)
					{
						elementSize = SafeArrayGetElemsize( *(fList->pparray));
						vA[elementCount - lBound]	= (VARIANT *)zMalloc(elementSize);
						SafeArrayGetElement(*(fList->pparray), &elementCount, vA[elementCount - lBound]);
					}
					bstrList = (BSTR *) zMalloc (sizeof(BSTR *) * (uBound - lBound + 1));
					memset((void *)bstrList, 0, sizeof(BSTR *) * (uBound - lBound + 1));
					for (elementCount=lBound; elementCount <= uBound; elementCount++)
					{
						tmpCcBstr = vA[elementCount - lBound]->bstrVal;
						if (tmpCcBstr.Length() == 0)
						{
							continue;
						}
						else
						{
							bstrList[numElements] = SysAllocString(vA[elementCount - lBound]->bstrVal);
							numElements++;
						}
					}
					for (elementCount=lBound; elementCount <= uBound; elementCount++)
					{
						VariantClear(vA[elementCount - lBound]);
						zFree(vA[elementCount - lBound]);
					}
					zFree(vA);
					*itemCount = numElements;
				}
			}
			else
			{
				arrayDim = SafeArrayGetDim(fList->parray);
				SafeArrayGetLBound(fList->parray, 1,  &lBound);
				SafeArrayGetUBound(fList->parray, 1,  &uBound);
				SafeArrayGetVartype(fList->parray, &arrayType);
				if (arrayType == VT_BSTR)
				{
					bstrList = (BSTR *) zMalloc (sizeof(BSTR *) * (uBound - lBound + 1));
					memset((void *)bstrList, 0, sizeof(BSTR *) * (uBound - lBound + 1));
					for (elementCount=lBound; elementCount <= uBound; elementCount++)
					{
						SafeArrayGetElement(fList->parray, &elementCount, &tmpBstr);
						tmpCcBstr = tmpBstr;
						if (tmpCcBstr.Length() == 0)
						{
							continue;
						}
						else
						{
							bstrList[numElements] = SysAllocString(tmpBstr);
							numElements++;
						}
					}
					*itemCount = numElements;
				}
				else if (arrayType == VT_VARIANT)
					{
						vA = (VARIANT **)zMalloc(sizeof(VARIANT *) * (uBound - lBound + 1));
						for (elementCount=lBound; elementCount <= uBound; elementCount++)
						{
							elementSize = SafeArrayGetElemsize( fList->parray);
							vA[elementCount - lBound]	= (VARIANT *)zMalloc(elementSize);
							SafeArrayGetElement(fList->parray, &elementCount, vA[elementCount - lBound]);
						}
						bstrList = (BSTR *) zMalloc (sizeof(BSTR *) * (uBound - lBound + 1));
						memset((void *)bstrList, 0, sizeof(BSTR *) * (uBound - lBound + 1));
						for (elementCount=lBound; elementCount <= uBound; elementCount++)
						{
							tmpCcBstr = vA[elementCount - lBound]->bstrVal;
							if (tmpCcBstr.Length() == 0)
							{
								continue;
							}
							else
							{
								bstrList[numElements] = SysAllocString(vA[elementCount - lBound]->bstrVal);
								numElements++;
							}
						}
						for (elementCount=lBound; elementCount <= uBound; elementCount++)
						{
							VariantClear(vA[elementCount - lBound]);
							zFree(vA[elementCount - lBound]);
						}
						zFree(vA);
						*itemCount = numElements;
					}
			}
		}
		else
		{
#ifdef WIN32
			if (fList->vt == VT_DISPATCH)
			{
				LPDISPATCH lpDispatch = fList->pdispVal;
				CComVariant ComVariant;
				bool Error = false;

				if (GetIDispatchProperty(lpDispatch, "length", ComVariant))
				{
					if (ComVariant.vt == VT_I4)
					{
//#ifdef WIN32
						CString TString;
//#else
//						char TString[50];
//#endif
						int Length = (int) ComVariant.lVal;
				
						bstrList = (BSTR *) zMalloc (sizeof(BSTR *) * Length);
						memset((void *)bstrList, 0, sizeof(BSTR *) * Length);
						for(int I = 0; I < Length; I++)
						{
//#ifdef WIN32
							TString.Format("%d", I);
//#else
//							sprintf(TString, "%d", I);
//#endif
							if(GetIDispatchProperty(lpDispatch, (LPCSTR) TString, ComVariant))
							{
								if (ComVariant.vt == VT_BSTR)
								{
									bstrList[I] = SysAllocString(ComVariant.bstrVal);
									numElements++;
								}
							}
						}
						*itemCount = numElements;
					}
				}
			}
#endif
		}
	}
getBstrArrayExit:
	ExitObjectLog;
	return bstrList;
}

STDMETHODIMP CSignature::put_ConfigFileName(BSTR newVal)
{
	BOOL configfileStatus=FALSE;

USES_CONVERSION;
	EnterObjectLog;
	FileExists(newVal, &configfileStatus);
	if (configfileStatus) // Config file exists
	{
		char *aNewVal = (char *)HeapW2A(newVal);
		ConfObj.setConfigFile(aNewVal);
		ConfObj.getConfigDetails(SigHandle);
		zFree(aNewVal);
		ExitObjectLog;
		return S_OK;
	}
	else
	{
		setError(SigHandle, NO_SECUREXML_CONFIG);
		return S_FALSE;
	}

}

STDMETHODIMP CSignature::put_CRLLocation(VARIANT newVal)
{
	UINT elementCount=0;
	UINT itemCount=0;
	BSTR	*bstrList=NULL;

	EnterObjectLog;


	if ((newVal.vt != VT_BSTR) &&
		(newVal.vt != VT_DISPATCH) &&
		!(newVal.vt & VT_ARRAY) && 
		!(newVal.vt & VT_BYREF))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}
	if (CertVerifyParams.altCrlCount != 0)
	{
		for (unsigned int i=0; i < CertVerifyParams.altCrlCount; i++)
			zFree(CertVerifyParams.crlAltUrl[i]);
		zFree(CertVerifyParams.crlAltUrl);
	}

	bstrList = GetBstrArrayFromVariant(newVal, &itemCount);

	if ((bstrList == NULL) || (itemCount == 0))
	{
		CertVerifyParams.crlAltUrl = NULL;
		CertVerifyParams.altCrlCount = 0;
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}
	CertVerifyParams.altCrlCount = itemCount;
	CertVerifyParams.crlAltUrl = (char **) zMalloc(sizeof(char *) * itemCount);
	if (CertVerifyParams.crlAltUrl == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}
	memset(CertVerifyParams.crlAltUrl, 0, sizeof(char *) * itemCount);

	for (elementCount =0; elementCount < itemCount; elementCount++)
	{
		CertVerifyParams.crlAltUrl[elementCount] = (char *)HeapW2A(bstrList[elementCount]);
		SysFreeString(bstrList[elementCount]);
	}
	zFree(bstrList);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::VerifyActiveCertificate(BOOL *result)
{
	SYSTEMTIME	tsSysTime;
	unsigned char *signingCert;
	BOOL freeSigningCert = FALSE;

USES_CONVERSION;
	EnterObjectLog;
	if (CurrentCertificate == NOT_INITIALIZED)
	{
		setError(SigHandle, NO_CERTIFICATE);
		*result = FALSE;
	}

	if (CurrentCertificate == USE_PFX_CERT)
		signingCert = B64PfxDataPtr;
	else
		if (CurrentCertificate == USE_BASE64_CERT)
		{
			signingCert = HeapW2A(SignerCertificate.m_str);
			freeSigningCert = TRUE;
		}
		else
			signingCert = cV[CurrentCertificate]->certificate;

	if ((CertVerifyParams.usedCrlCount != 0) &&
		(CertVerifyParams.usedCrlList != NULL))
	{
		for (UINT i=0; i < CertVerifyParams.usedCrlCount; i++)
		{
			if (CertVerifyParams.usedCrlList[i] != NULL)
				zFree(CertVerifyParams.usedCrlList[i]);
		}
		zFree(CertVerifyParams.usedCrlList);
		CertVerifyParams.usedCrlList = NULL;
		CertVerifyParams.usedCrlCount = 0;
	}

#ifdef WIN32
	GetSystemTime(&tsSysTime);
#else
	GetSystemTimeLinux(&tsSysTime);
#endif
	if (CheckCertificateValidity(signingCert, 
							&tsSysTime, 
							&PfxPassword,
							&CertVerifyParams,
							SigHandle) == FALSE)
	{
		*result = FALSE;
		if (freeSigningCert)
			zFree(signingCert);
		return S_FALSE;
	}

	*result = TRUE;
	if (freeSigningCert)
		zFree(signingCert);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_CertificatePolicy(VARIANT newVal)
{
	UINT elementCount=0;
	UINT itemCount=0;
	BSTR	*bstrList=NULL;

	EnterObjectLog;
	if ((newVal.vt != VT_BSTR) &&
		(newVal.vt != VT_DISPATCH) &&
		!(newVal.vt & VT_ARRAY) && 
		!(newVal.vt & VT_BYREF))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}
	if (CertVerifyParams.userPolicyCount != 0)
	{
		for (unsigned int i=0; i < CertVerifyParams.userPolicyCount; i++)
			zFree(CertVerifyParams.userPolicySet[i]);
		zFree(CertVerifyParams.userPolicySet);
	}

	bstrList = GetBstrArrayFromVariant(newVal, &itemCount);

	if ((bstrList == NULL) || (itemCount == 0))
	{// This is a valid way to clear user certificate policies, hence don't set any error
		CertVerifyParams.userPolicySet = NULL;
		CertVerifyParams.userPolicyCount = 0;
		return S_FALSE;
	}

	CertVerifyParams.userPolicyCount = itemCount;
	CertVerifyParams.userPolicySet = (char **) zMalloc(sizeof(char *) * itemCount);
	if (CertVerifyParams.userPolicySet == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}
	memset(CertVerifyParams.userPolicySet, 0, sizeof(char *) * itemCount);

	for (elementCount =0; elementCount < itemCount; elementCount++)
	{
		CertVerifyParams.userPolicySet[elementCount] = (char *)HeapW2A(bstrList[elementCount]);
		SysFreeString(bstrList[elementCount]);
	}
	zFree(bstrList);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_AuthorityConstrainedPolicy(VARIANT *pVal)
{
	VARIANT *outVariant;
	SAFEARRAY *outArray;
	SAFEARRAYBOUND rgsabound[1];
	HRESULT hr;
	
USES_CONVERSION;
	EnterObjectLog;
	outVariant = (VARIANT *)zMalloc(sizeof(VARIANT));
//	outArray = (SAFEARRAY *)zMalloc(sizeof(SAFEARRAY *));

	VariantInit(outVariant);

	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = CertVerifyParams.authPolicySetCountOut;

	outArray = SafeArrayCreate(VT_BSTR, 
								1,
								rgsabound);
	if (outArray == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}
	for (long i=0; i<(long)CertVerifyParams.authPolicySetCountOut; i++)
	{
		BSTR arrElement;
		arrElement = A2WBSTR(CertVerifyParams.authPolicySetOut[i]);
		hr = SafeArrayPutElement(outArray, &i, arrElement);
		if (hr != S_OK)
		{
			setError(SigHandle, MEMORY_FAULT);
			return S_FALSE;
		}
	}
	(*outVariant).vt = (VT_ARRAY | VT_BSTR);
	(*outVariant).parray = outArray;
	*pVal = *outVariant;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_UserConstrainedPolicy(VARIANT *pVal)
{
	VARIANT *outVariant;
	SAFEARRAY *outArray;
	SAFEARRAYBOUND rgsabound[1];
	HRESULT hr;
	
USES_CONVERSION;
	EnterObjectLog;
	outVariant = (VARIANT *)zMalloc(sizeof(VARIANT));
//	outArray = (SAFEARRAY *)zMalloc(sizeof(SAFEARRAY *));

	VariantInit(outVariant);
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = CertVerifyParams.userPolicySetCountOut;

	outArray = SafeArrayCreate(VT_BSTR, 
								1,
								rgsabound);
	if (outArray == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}
	for (long i=0; i<(long)CertVerifyParams.userPolicySetCountOut; i++)
	{
		BSTR arrElement;
		arrElement = A2WBSTR(CertVerifyParams.userPolicySetOut[i]);
		hr = SafeArrayPutElement(outArray, &i, arrElement);
		if (hr != S_OK)
		{
			setError(SigHandle, MEMORY_FAULT);
			return S_FALSE;
		}
	}
	(*outVariant).vt = (VT_ARRAY | VT_BSTR);
	(*outVariant).parray = outArray;

	*pVal = *outVariant;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_CertificatePolicyChecking(BOOL newVal)
{
	EnterObjectLog;
	if (DoDCompliance == FALSE)
		if (newVal)
			CertVerifyParams.verificationOptions |= VERIFY_POLICY;
		else
			CertVerifyParams.verificationOptions &= (~VERIFY_POLICY);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_CertificateChainValidation(BOOL newVal)
{
	EnterObjectLog;
	if (DoDCompliance == FALSE)
		if (newVal)
		{
			CertVerifyParams.verificationOptions |= VERIFY_CHAIN;
			CertVerifyParams.verificationOptions |= VERIFY_PATH_LENGTH;
		}
		else
		{
			CertVerifyParams.verificationOptions &= (~VERIFY_CHAIN);
			CertVerifyParams.verificationOptions &= (~VERIFY_PATH_LENGTH);
		}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_CertificatePathLengthChecking(BOOL newVal)
{
	EnterObjectLog;
	if (DoDCompliance == FALSE)
		if (newVal)
			CertVerifyParams.verificationOptions |= VERIFY_PATH_LENGTH;
		else
			CertVerifyParams.verificationOptions &= (~VERIFY_PATH_LENGTH);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_DoDCompliance(BOOL newVal)
{
	EnterObjectLog;
	DoDCompliance = newVal;
	if (newVal)
		CertVerifyParams.verificationOptions |=	(VERIFY_CRL | 
											VERIFY_POLICY | 
											VERIFY_CHAIN | 
											VERIFY_PATH_LENGTH |
											EXPLICIT_TRUST);
	else
	{
		CertVerifyParams.verificationOptions &= (~VERIFY_CRL);
		CertVerifyParams.verificationOptions &= (~VERIFY_POLICY);
		CertVerifyParams.verificationOptions &= (~VERIFY_CHAIN);
		CertVerifyParams.verificationOptions &= (~VERIFY_PATH_LENGTH);
		CertVerifyParams.verificationOptions &= (~EXPLICIT_TRUST);
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_CertificatePolicyExplicit(BOOL *pVal)
{
	EnterObjectLog;
	if (CertVerifyParams.explicitPolicyInd == 0)
		*pVal = TRUE;
	else
		*pVal = FALSE;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_CertificatePolicyExplicit(BOOL newVal)
{
	EnterObjectLog;
	if (newVal)
		CertVerifyParams.verificationOptions |= POLICY_EXPLICIT;
	else
		CertVerifyParams.verificationOptions &= (~POLICY_EXPLICIT);
	CertVerifyParams.explicitPolicyInd = newVal;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_CertificateTrustExplicit(BOOL newVal)
{
	EnterObjectLog;
	if (DoDCompliance == FALSE)
		if (newVal)
			CertVerifyParams.verificationOptions |= EXPLICIT_TRUST;
		else
			CertVerifyParams.verificationOptions &= (~EXPLICIT_TRUST);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_RecipientCertificates(VARIANT newVal)
{
	UINT elementCount=0;
	UINT itemCount=0;
	BSTR	*bstrList=NULL;

	EnterObjectLog;
	if ((newVal.vt != VT_BSTR) &&
		(newVal.vt != VT_DISPATCH) &&
		!(newVal.vt & VT_ARRAY) && 
		!(newVal.vt & VT_BYREF))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}
	if (RecipientCertificateCount != 0)
	{
		for (unsigned int i=0; i < RecipientCertificateCount; i++)
			zFree(RecipientCertificateList[i]);
		zFree(RecipientCertificateList);
		RecipientCertificateCount = 0;
	}

	bstrList = GetBstrArrayFromVariant(newVal, &itemCount);

	if ((bstrList == NULL) || (itemCount == 0))
	{
		RecipientCertificateList = NULL;
		RecipientCertificateCount = 0;
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	RecipientCertificateCount = itemCount;
	RecipientCertificateList = (char **) zMalloc(sizeof(char *) * itemCount);
	if (RecipientCertificateList == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}
	memset(RecipientCertificateList, 0, sizeof(char *) * itemCount);

	for (elementCount =0; elementCount < itemCount; elementCount++)
	{
		RecipientCertificateList[elementCount] = (char *)HeapW2A(bstrList[elementCount]);
		SysFreeString(bstrList[elementCount]);
	}
	zFree(bstrList);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::EncryptStr(BSTR inputStr, BSTR* cipherStr)
{
	CComBSTR ccBstrInputStr;
	DS_DATA_BLOB inputBlob;
	BYTE *encodedEncryptedData=NULL;
	unsigned long encodedEncryptedDataSize;

	EnterObjectLog;
	
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (!LicObj.getEncryptAllowed()) {
		setError(SigHandle, NO_ENCRYPT_LIC);
		return S_FALSE;
	}
	
	ccBstrInputStr = inputStr;
	if (ccBstrInputStr.Length() == 0)
	{
		setError(SigHandle, NULL_DATA_STRING);
		return S_FALSE;
	}

	USES_CONVERSION;

	inputBlob.pbData = (BYTE *)HeapW2A(inputStr);
	inputBlob.cbData = strlen((const char *)inputBlob.pbData) + 1;

	encodedEncryptedData = EncryptBlob(&inputBlob, TRUE,
										&encodedEncryptedDataSize, NULL, NULL);
	if (encodedEncryptedData == NULL)
		return S_FALSE;
	*cipherStr = A2WBSTR((LPCSTR)encodedEncryptedData, encodedEncryptedDataSize);
	zFree(encodedEncryptedData);
	zFree(inputBlob.pbData);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::DecryptStr(BSTR cipherText, BSTR* plainText)
{
	char* EncryptedString = NULL;
	BYTE*    pbEncryptedBlob = NULL;
	DWORD    cbEncryptedBlob =0;
	DS_DATA_BLOB cBlob;
	DS_DATA_BLOB dBlob;

	EncryptedString = (char *)HeapW2A(cipherText);

	cbEncryptedBlob = base64decodeSize((DWORD)strlen((const char *)EncryptedString));
	pbEncryptedBlob = (BYTE *) zMalloc (cbEncryptedBlob+1);
	memset(pbEncryptedBlob,0,cbEncryptedBlob+1);
	cbEncryptedBlob = base64decode((unsigned char *)EncryptedString,(unsigned char *)pbEncryptedBlob,cbEncryptedBlob);
	zFree(EncryptedString);

	cBlob.cbData = cbEncryptedBlob;
	cBlob.pbData = pbEncryptedBlob;
	dBlob.cbData = 0;
	dBlob.pbData = NULL;

	if (!DecryptBlob(&cBlob, &dBlob, NULL, NULL)) {
		zFree(pbEncryptedBlob);
		return S_FALSE;
	}
	if (dBlob.pbData) {
		*plainText = A2WBSTR((LPCSTR) dBlob.pbData,dBlob.cbData);
		zFree(dBlob.pbData);
	}else{
		*plainText = NULL;
	}
	return S_OK;
}

/*
 * Decryption helper.
 *
 * cBlob - encrypted data
 * dBlob - (out) decrypted data; caller must zFree it.
 * Another call convention uses 3rd and 4th parameters as file names rather than memory buffers.
 * 
 */
BOOL CSignature::DecryptBlob(PDS_DATA_BLOB cBlob, PDS_DATA_BLOB dBlob, BYTE *inFile, BYTE *outFile)
{
	DWORD cbDecryptedMessage = 0;

#ifdef NSS
	SECItem	pfxBlob;
	CERTCertificate *pct=NULL;

	// NSS doesn't trust the root certificate in the chain.
	// This part requires additional attention - implement PKCS7 on our own.
	setError(SigHandle, NSS_NOT_SUPPORTED);
	return FALSE;

#else
	CRYPT_DECRYPT_MESSAGE_PARA  DecryptParams;
	DWORD  DecryptParamsSize = sizeof(DecryptParams);
	HCRYPTPROV hCryptProv;
	HCERTSTORE hStoreHandle;
	CRYPT_DATA_BLOB	pfxBlob;
#endif

	BYTE*  pbDecryptedMessage = NULL;
	BOOL   fReturn = TRUE;
	BYTE*    pbEncryptedBlob = NULL;
	DWORD    cbEncryptedBlob =0;

	EnterObjectLog;
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return FALSE;
	}
	if (!LicObj.getDecryptAllowed()) {
		setError(SigHandle, NO_DECRYPT_LIC);
		return FALSE;
	}
	if ((!cBlob && !inFile)	|| 
		(!dBlob && !outFile)) {
		return FALSE;
	}

	if (cBlob) {
	    cbEncryptedBlob = cBlob->cbData;
	    pbEncryptedBlob = cBlob->pbData;
    }

#ifndef NSS
	if(!(CryptAcquireContext(
				&hCryptProv,         // Address for handle to be returned.
				NULL,                // Use the current user's logon name.
				MS_ENHANCED_PROV,    // Use the default provider.
				PROV_RSA_FULL,       // Need to both encrypt and sign.
				CRYPT_MACHINE_KEYSET )))                 // No flags needed.
	{ // Keyset does not exist. lets create one
		if(!(CryptAcquireContext(
				&hCryptProv,         // Address for handle to be returned.
				NULL,                // Use the current user's logon name.
				MS_ENHANCED_PROV,    // Use the default provider.
				PROV_RSA_FULL,       // Need to both encrypt and sign.
				CRYPT_NEWKEYSET | CRYPT_MACHINE_KEYSET )))   // No flags needed.
		{
			setError(SigHandle, CAPI_ACQUIRE_CNTX);
			return FALSE;
		}
	}
#endif
USES_CONVERSION;

	if ((DecryptUsingPfxFileCert) && (DecrytionPfxCertFile.Length() != 0))
	{
#ifdef NSS
		SECItem pwd;
		pwd.len = DecrytionPfxPassword.cbData + 1; // counting on '\0'
		pwd.data = (BYTE *) zMalloc(pwd.len);
		memset(pwd.data,0,pwd.len);
		memcpy(pwd.data,DecrytionPfxPassword.pbData,DecrytionPfxPassword.cbData);

		ReadAllBin(DecrytionPfxCertFile.m_str, &pfxBlob.data, (DWORD *) &pfxBlob.len);
		if ((pfxBlob.data != NULL) &&
			crNSS_PFXIsPFXBlob(&pfxBlob, &pwd, SigHandle))
		{
			if (!(pct = NSS_ImportPKCS12Object(&pfxBlob, &pwd, SigHandle))) {
				setError(SigHandle, PFX_IMPORT_FAILED);
				zFree(pfxBlob.data);
				return FALSE;
			}
		}else{
			setError(SigHandle, PFX_BAD_PASSWORD);
			if (pfxBlob.data)
				zFree(pfxBlob.data);
			return FALSE;
		}
		if (pfxBlob.data)
			zFree(pfxBlob.data);
		if (pwd.data) 
			zFree(pwd.data);
#else
		ReadAllBin(DecrytionPfxCertFile.m_str, &pfxBlob.pbData, &pfxBlob.cbData);
		if ((pfxBlob.pbData != NULL) &&
			(PFXIsPFXBlob(&pfxBlob)))
		{
			// this is PFX, import it and deal with temp store
			LPCWSTR password = (LPCWSTR) DecrytionPfxPassword.pbData;

			if (!PFXVerifyPassword(&pfxBlob, password, CRYPT_MACHINE_KEYSET))
			{
				setError(SigHandle, PFX_BAD_PASSWORD);
				zFree(pfxBlob.pbData);
				return FALSE;
			}
			if ((hStoreHandle =  PFXImportCertStore(
									&pfxBlob, 
									password, 
									CRYPT_MACHINE_KEYSET | CRYPT_EXPORTABLE
									)) == NULL)
			{
				setError(SigHandle, PFX_IMPORT_FAILED);
				zFree(pfxBlob.pbData);
				return FALSE;
			}
		}
		if (pfxBlob.pbData != NULL)
			zFree(pfxBlob.pbData);
#endif
	}
	else
	{
#ifdef NSS
		// enumerate all certificate from the store
		// --!!TODO
		setError(SigHandle, CAPI_OPEN_STORE);
		return FALSE;

#else
		char *aStoreName = (char *)HeapW2A(StoreName.m_str);
		if(!(hStoreHandle = CertOpenSystemStore(
			hCryptProv, aStoreName)))
		{
			setError(SigHandle, CAPI_OPEN_STORE);
			zFree(aStoreName);
			return FALSE;
		}
		zFree(aStoreName);
#endif
	}

#ifdef NSS
	// decrypt here
	// --!!TODO
#else

   if (pbEncryptedBlob != NULL) {
		HCERTSTORE CertStoreArray[] = {hStoreHandle};
		memset(&DecryptParams, 0, DecryptParamsSize);
		DecryptParams.cbSize = DecryptParamsSize;
		DecryptParams.dwMsgAndCertEncodingType = MY_ENCODING_TYPE;
		DecryptParams.cCertStore = 1;
		DecryptParams.rghCertStore = CertStoreArray;

		//--------------------------------------------------------------------
		//  Decrypt the message data.
		//  Call CryptDecryptMessage to get the returned data size.

		if(!(CryptDecryptMessage(
			&DecryptParams,
			pbEncryptedBlob,
			cbEncryptedBlob,
			NULL,
			&cbDecryptedMessage,
			NULL)))
		{
			long le = getlasterror();
			setError(SigHandle, CAPI_DECRYPT_MSG);
			return FALSE;
		}
		//--------------------------------------------------------------------
		// Allocate memory for the returned decrypted data.

		if(!(pbDecryptedMessage = (BYTE*)zMalloc(
			cbDecryptedMessage)))
		{
			setError(SigHandle, MEMORY_FAULT);
			return FALSE;
		}
		//--------------------------------------------------------------------
		// Call CryptDecryptMessage to decrypt the data.

		if(!(CryptDecryptMessage(
			&DecryptParams,
			pbEncryptedBlob,
			cbEncryptedBlob,
			pbDecryptedMessage,
			&cbDecryptedMessage,
			NULL)))
		{
			setError(SigHandle, DECRYPTION_FAILED);
			zFree(pbDecryptedMessage);
			return FALSE;
		}
    }else{
		// === streaming is tricky ===
		CMSG_CTRL_DECRYPT_PARA decryptPara;
		PCRYPT_KEY_PROV_INFO pKi = NULL;
		decryptPara.cbSize = sizeof (CMSG_CTRL_DECRYPT_PARA);
		decryptPara.hCryptProv = NULL;
	    HCRYPTMSG hMsg;
		CMSG_STREAM_INFO sInfo;
		PCMSG_STREAM_INFO psInfo = NULL;

		// open output file and pass it as an argument to callback function
		FILE *fout = fopen((const char*)outFile, "wb");
		if (!fout) {
			setError(SigHandle, IO_ERROR);
			return FALSE;
		}
		//DWORD eFlags = CMSG_DETACHED_FLAG;
		sInfo.cbContent = 0xFFFFFFFF;
		sInfo.pfnStreamOutput = encryptCallback;
		sInfo.pvArg = fout;
		psInfo = &sInfo;

		if(!(hMsg = CryptMsgOpenToDecode(
			MY_ENCODING_TYPE,      // Encoding type.
			0,			            // Detached Flags.
			0,                     // Use the default message type.
			hCryptProv,            // Cryptographic provider.
			NULL,                  // Recipient information.
			psInfo)))               // Stream information.
		{
			setError(SigHandle, CAPI_DECRYPT_MSG);
			return FALSE;
		}


		// read the file by portions in 38K
		FILE *ifHandle = fopen((const char*)inFile, "rb");
		BYTE buf[38400];
		BOOL lastCall = FALSE;
		long cnt=0;
		while(!lastCall) {
			int n = fread(buf,1,38400,ifHandle);
			if (n == 0 && !ferror(ifHandle)) {
				fclose(ifHandle);
				lastCall = TRUE;
			}
			if (feof(ifHandle)) {
				lastCall = TRUE;
			}
			if (ferror(ifHandle)!=0) {
				fclose(ifHandle);
				setError(SigHandle, IO_ERROR);
				if (sInfo.pvArg) fclose((FILE *)sInfo.pvArg);
				if (hMsg) CryptMsgClose(hMsg);
				return FALSE;
			}
			if (n>0) {
				cnt += n;
				if(!CryptMsgUpdate(
					hMsg,              // handle to the message
					buf,      // pointer to the signed data BLOB
					n,      // size of the data BLOB
					lastCall))             // last call
				{
					long e = getlasterror();
					setError(SigHandle, CAPI_DECRYPT_MSG);
					if (sInfo.pvArg) fclose((FILE *)sInfo.pvArg);
					if (hMsg) CryptMsgClose(hMsg);
					return FALSE;
				}

				// if provider is already defined it means we have already performed all steps below and may skip them
				if (decryptPara.hCryptProv == NULL) {

				//
				// For an enveloped message, after each call to CryptMsgUpdate, check to see if 
				// CMSG_ENVELOPE_ALGORITHM_PARAM is available by calling CryptMsgGetParam. 
				// CryptMsgGetParam will fail with LastError CRYPT_E_STREAM_MSG_NOT_READY until CryptMsgUpdate 
				// has processed enough of the message to make the CMSG_ENVELOPE_ALGORITHM_PARAM structure available. 
				// Once that structure is available, the application can iterate through the recipients, 
				// retrieving a CERT_INFO structure for each one using CryptMsgGetParam (CMSG_RECIPIENT_INFO_PARAM).
				//

				DWORD cbAlgParam =0;
				BYTE *pbAlgParam = NULL;

				if(!CryptMsgGetParam(
					hMsg,                  // handle to the message
					CMSG_ENVELOPE_ALGORITHM_PARAM,    // parameter type
					0,
					NULL,
					&cbAlgParam))       // size of the BLOB
				{
					if (getlasterror() != CRYPT_E_STREAM_MSG_NOT_READY) {
						setError(SigHandle, CAPI_DECRYPT_MSG);
						if (hMsg) CryptMsgClose(hMsg);
						return FALSE;
					}else{
						// check amount of passed data to prevent DOS attack
						// we allow max 100M
						if (cnt > 100 * 1024 * 1024) {
							setError(SigHandle, CAPI_DECRYPT_MSG);
							if (hMsg) CryptMsgClose(hMsg);
							return FALSE;
						}
					}
					continue;
				}

				// the structure is available.
				// Now we can get recipient info.

				// how many recipients we have?
				DWORD pRecCount = 0;
				DWORD cRecCount = sizeof(DWORD);
                if (!CryptMsgGetParam(
						hMsg, 
						CMSG_RECIPIENT_COUNT_PARAM,
                        0, 
						&pRecCount, 
						&cRecCount))
				{
					setError(SigHandle, CAPI_DECRYPT_MSG);
					if (hMsg) CryptMsgClose(hMsg);
					return FALSE;
				}

				// iterate through recipients to find correct certificate
				PCCERT_CONTEXT pCertContext = NULL;
				int recNum = 0;
				for (int ri=0; ri< pRecCount; ri++) {

					DWORD cbCertInfo = 0;
					PCERT_INFO pCertInfo = NULL;
					if (!CryptMsgGetParam(
							hMsg, 
							CMSG_RECIPIENT_INFO_PARAM,
							ri, 
							NULL, 
							&cbCertInfo))
					{
						setError(SigHandle, CAPI_DECRYPT_MSG);
						if (hMsg) CryptMsgClose(hMsg);
						return FALSE;
					}

					if (!(pCertInfo = (PCERT_INFO) zMalloc (cbCertInfo)))
					{
						setError(SigHandle, MEMORY_FAULT);
						if (hMsg) CryptMsgClose(hMsg);
						return FALSE;
					}

					if (!CryptMsgGetParam(
							hMsg, 
							CMSG_RECIPIENT_INFO_PARAM,
							ri, 
							pCertInfo, 
							&cbCertInfo))
					{
						setError(SigHandle, CAPI_DECRYPT_MSG);
						if (hMsg) CryptMsgClose(hMsg);
						if (pCertInfo) zFree(pCertInfo);
						return FALSE;
					}	                					

					if (pCertContext = CertGetSubjectCertificateFromStore(
							hStoreHandle,
							MY_ENCODING_TYPE, 
							pCertInfo)) 
					{
						if (pCertInfo) zFree(pCertInfo);
						recNum = ri;
						break;
					}
					if (pCertInfo) zFree(pCertInfo);
				}

				if (!pCertContext) {
					// not found suitable certificate, quit
					setError(SigHandle, CAPI_DECRYPT_MSG);
					if (hMsg) CryptMsgClose(hMsg);
					return FALSE;
				}

				DWORD cbKi = 0;				

				if (!CertGetCertificateContextProperty(
						pCertContext,
						CERT_KEY_PROV_INFO_PROP_ID, 
						NULL, 
						&cbKi)) 
				{
					setError(SigHandle, CAPI_DECRYPT_MSG);
					if (hMsg) CryptMsgClose(hMsg);
					if (pCertContext) CertFreeCertificateContext(pCertContext);
					return FALSE;
				}

				if (!(pKi = (PCRYPT_KEY_PROV_INFO) zMalloc(cbKi)))
				{
					setError(SigHandle, MEMORY_FAULT);
					if (hMsg) CryptMsgClose(hMsg);
					if (pCertContext) CertFreeCertificateContext(pCertContext);
					return FALSE;
				}

				if (!CertGetCertificateContextProperty(
						pCertContext,
						CERT_KEY_PROV_INFO_PROP_ID, 
						pKi, 
						&cbKi)) 
				{
					setError(SigHandle, CAPI_DECRYPT_MSG);
					if (hMsg) CryptMsgClose(hMsg);
					if (pCertContext) CertFreeCertificateContext(pCertContext);
					if (pKi) zFree(pKi);
					return FALSE;
				}

				HCRYPTPROV cryptProv = NULL;
				//BYTE *pName = HeapW2A(pKi->pwszContainerName);
				if (!CryptAcquireContext(
						&cryptProv, 
						W2A(pKi->pwszContainerName),
						// bug in CAPI: using pKi->pwszProvName gives NTE_BAD_FLAGS later because of unsupported key length
						MS_ENHANCED_PROV,
						//pKi->pwszProvName,
						pKi->dwProvType,      
						pKi->dwFlags))
				{
//					long l = getlasterror();
//					if(!(CryptAcquireContext(
//							&cryptProv,
//							pKi->pwszContainerName,
//							MS_ENHANCED_PROV,
//							//pKi->pwszProvName,
//							pKi->dwProvType,
//							CRYPT_NEWKEYSET | CRYPT_MACHINE_KEYSET )))
//					{
						long le = getlasterror();
						setError(SigHandle, CAPI_ACQUIRE_CNTX);
						if (hMsg) CryptMsgClose(hMsg);
						if (pCertContext) CertFreeCertificateContext(pCertContext);
						if (pKi) zFree(pKi);
						//zFree(pName);
						return FALSE;
//					}
				}
				//zFree(pName);

				decryptPara.hCryptProv = cryptProv;
				decryptPara.dwKeySpec = pKi->dwKeySpec;
				decryptPara.dwRecipientIndex = recNum;

				if (pCertContext) CertFreeCertificateContext(pCertContext);

				if (!CryptMsgControl(
					hMsg, 
					0, 
					CMSG_CTRL_DECRYPT,
					&decryptPara))
				{
					long le = getlasterror();
					setError(SigHandle, CAPI_DECRYPT_MSG);
					if (hMsg) CryptMsgClose(hMsg);
					if (pKi) zFree(pKi);
					if (decryptPara.hCryptProv) CryptReleaseContext(decryptPara.hCryptProv,0);
					return FALSE;
				}
				}
			}
		}
		if (pKi) zFree(pKi);
		if (decryptPara.hCryptProv) CryptReleaseContext(decryptPara.hCryptProv,0);
		if (hMsg) CryptMsgClose(hMsg);
		//if (sInfo.pvArg) fclose((FILE *)sInfo.pvArg); // it is closed by callback on success
	}

#endif

	if (dBlob) {
		dBlob->cbData = cbDecryptedMessage;
		dBlob->pbData = pbDecryptedMessage;
	}

	//--------------------------------------------------------------------
	// Clean up memory.
#ifdef NSS
	if (pct) {
		SEC_DeletePermCertificate(pct);
		CERT_DestroyCertificate(pct);
	}
#else
	CertCloseStore(
			hStoreHandle, 
			CERT_CLOSE_STORE_CHECK_FLAG);
	if(hCryptProv)
		CryptReleaseContext(hCryptProv,0);
#endif

	ExitObjectLog;
	return TRUE;
}

STDMETHODIMP CSignature::EncryptFile(BSTR inputFile, BSTR outputFile, BSTR* encryptedFile)
{
	CComBSTR ccBstrInputFile, ccBstrFileName;
	unsigned long encodedEncryptedDataSize;
	char TempPath[MAX_PATH];
	FILE *hFile;
	TEMP_FILE_INFO *tmpFilePath = NULL;
	BSTR bstrFileName=NULL;
	BOOL createTempFile = FALSE;
#ifdef WIN32
	const char *FILE_SEP_STR = "\\";
#else
	const char *FILE_SEP_STR = "/";
#endif

	EnterObjectLog;
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (!LicObj.getEncryptAllowed()) {
		setError(SigHandle, NO_ENCRYPT_LIC);
		return S_FALSE;
	}

	ccBstrInputFile = inputFile;
	if (ccBstrInputFile.Length() == 0)
	{
		setError(SigHandle, FILE_NOT_FOUND);
		return S_FALSE;
	}

	USES_CONVERSION;
	ccBstrFileName = outputFile;

	if ((ccBstrFileName.Length() != 0) && (FileAccessRestricted == TRUE))
	{
		unsigned char *charSecureXMLPath = HeapW2A(SecureXMLPath.m_str);
		string license_file = (char *)charSecureXMLPath;
		license_file += FILE_SEP_STR;
		license_file += SECUREXML_LICENSE_FILENAME;
		zFree(charSecureXMLPath);
		unsigned char *charOutFilePath = HeapW2A(outputFile);
		int length1 = strlen((const char *)charOutFilePath);
		int length2 = strlen(license_file.c_str());
		if (length1 != length2)
			createTempFile = TRUE;
		else
			if (strnicmp(license_file.c_str(), (const char *)charOutFilePath, length1) == 0)
				createTempFile = FALSE;
			else
				createTempFile = TRUE;
		//if (stricmp(license_file.c_str(), (const char *)charOutFilePath) == 0)
		//	createTempFile = FALSE;
		//else
		//	createTempFile = TRUE;
		zFree(charOutFilePath);
	}

	if ((ccBstrFileName.Length() == 0) || (createTempFile == TRUE))
	{
		// Create temporary file for saving encrypted data
		GetTempPath((DWORD)MAX_PATH, TempPath); 
		GetTempFileName(TempPath, // dir. for temp. files 
			"INF",                // temp. file name prefix 
			0,                    // create unique name 
			szTempName);          // buffer for name
		bstrFileName = A2WBSTR((LPCSTR)szTempName);
		tmpFilePath = new (TEMP_FILE_INFO);
		strcpy((char *)tmpFilePath->fileName, szTempName);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
	}
	else
		bstrFileName = SysAllocString(outputFile);

	// at this point we have output file name in bstrFileName, input file name in inputFile
	EncryptBlob(NULL, FALSE, &encodedEncryptedDataSize, inputFile, bstrFileName);
	if (encodedEncryptedDataSize==0) {
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}

	*encryptedFile = bstrFileName;
	ExitObjectLog;
	return S_OK;
}


STDMETHODIMP CSignature::DecryptFile(BSTR inputFile, BSTR outputFile, BSTR* decryptedFile)
{
	char* EncryptedString;
	BOOL   fReturn = TRUE;
	BSTR bstrEncryptedString;
	char TempPath[MAX_PATH];
	TEMP_FILE_INFO *tmpFilePath = NULL;

	EnterObjectLog;
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (!LicObj.getDecryptAllowed()) {
		setError(SigHandle, NO_DECRYPT_LIC);
		return S_FALSE;
	}

	CComBSTR ccBstrInputFile = inputFile;
	if (ccBstrInputFile.Length() == 0)
	{
		setError(SigHandle, FILE_NOT_FOUND);
		return S_FALSE;
	}

	CComBSTR ccBstrOutputFile = outputFile;
	if (ccBstrOutputFile.Length() == 0)
	{
		GetTempPath((DWORD)MAX_PATH, TempPath);
		GetTempFileName(TempPath, // dir. for temp. files 
			"INFM",                // temp. file name prefix 
			0,                    // create unique name 
			szTempName);          // buffer for name
		tmpFilePath = new (TEMP_FILE_INFO);
		strcpy((char *)tmpFilePath->fileName, szTempName);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
	}
	else
	{
		char *aOutputFile = (char *)HeapW2A(outputFile);
		strcpy(szTempName, aOutputFile);
		zFree(aOutputFile);
	}

	BYTE *cInFile = HeapW2A(inputFile);
	if (!DecryptBlob(NULL, NULL, cInFile, (BYTE *)szTempName)) {
		zFree(cInFile);
		return S_FALSE;
	}
	zFree(cInFile);

	*decryptedFile = A2WBSTR((LPCSTR)szTempName);
	ExitObjectLog;
	return S_OK;
}


/*
STDMETHODIMP CSignature::DecryptFile(BSTR inputFile, BSTR outputFile, BSTR* decryptedFile)
{
	char* EncryptedString;
	BOOL   fReturn = TRUE;
	BYTE*    pbEncryptedBlob;
	DWORD    cbEncryptedBlob;
	BSTR bstrEncryptedString;
	char TempPath[MAX_PATH];
	TEMP_FILE_INFO *tmpFilePath = NULL;
	DS_DATA_BLOB eBlob;
	DS_DATA_BLOB dBlob;

	EnterObjectLog;
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (!LicObj.getDecryptAllowed()) {
		setError(SigHandle, NO_DECRYPT_LIC);
		return S_FALSE;
	}

	CComBSTR ccBstrInputFile = inputFile;
	if (ccBstrInputFile.Length() == 0)
	{
		setError(SigHandle, FILE_NOT_FOUND);
		return S_FALSE;
	}
	eBlob.cbData = 0;
	eBlob.pbData = NULL;

	if (ReadAllBin(inputFile, &(eBlob.pbData), &(eBlob.cbData)) == S_FALSE)
	{
		if (eBlob.pbData != NULL)
		{
			zFree(eBlob.pbData);
			eBlob.pbData= NULL;
		}
	}
	if (!DecryptBlob(&eBlob,&dBlob, NULL, NULL)) {
		if (eBlob.pbData != NULL)
		{
			zFree(eBlob.pbData);
			eBlob.pbData= NULL;
		}
		//zFree(pbEncryptedBlob);		
		return S_FALSE;
	}
	//zFree(pbEncryptedBlob);
	if (eBlob.pbData != NULL)
	{
		zFree(eBlob.pbData);
		eBlob.pbData= NULL;
	}

	CComBSTR ccBstrOutputFile = outputFile;
	if (ccBstrOutputFile.Length() == 0)
	{
		GetTempPath((DWORD)MAX_PATH, TempPath);
		GetTempFileName(TempPath, // dir. for temp. files 
			"INFM",                // temp. file name prefix 
			0,                    // create unique name 
			szTempName);          // buffer for name
		tmpFilePath = new (TEMP_FILE_INFO);
		strcpy((char *)tmpFilePath->fileName, szTempName);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
	}
	else
	{
		char *aOutputFile = (char *)HeapW2A(outputFile);
		strcpy(szTempName, aOutputFile);
		zFree(aOutputFile);
	}

#ifdef WIN32
	HANDLE hTempFile;
	hTempFile = CreateFile((LPCSTR) szTempName,  // file name 
		GENERIC_READ | GENERIC_WRITE, // open for read/write 
		0,                            // do not share 
		NULL,                         // no security 
		CREATE_ALWAYS,                // overwrite existing file
		FILE_ATTRIBUTE_NORMAL,        // normal file 
		NULL);                        // no attr. template 
	if (hTempFile == INVALID_HANDLE_VALUE) 
	{
		setError(SigHandle, IO_ERROR);
		if (tmpFilePath != NULL)
			tmpFileList->remove(tmpFilePath);
		return S_FALSE;
	}
	DWORD dwBytesWritten;
	// Write the signature buffer to the temporary file. 
	WriteFile(hTempFile, dBlob.pbData, dBlob.cbData , 
				&dwBytesWritten, NULL); 
	// Close file. 
	CloseHandle(hTempFile);
#else
	FILE *hTempFile;
	hTempFile = fopen(szTempName, "w+");
	if (!hTempFile)
	{
		setError(SigHandle, IO_ERROR);
		if (tmpFilePath != NULL)
			tmpFileList->remove(tmpFilePath);
		return S_FALSE;
	}
	size_t dwBytesWritten = fwrite(dBlob.pbData, 1, dBlob.cbData, hTempFile);
	fclose(hTempFile);
#endif
	zFree(dBlob.pbData);
	*decryptedFile = A2WBSTR((LPCSTR)szTempName);
	ExitObjectLog;
	return S_OK;
}
*/
#ifdef NSS
/************************* NSS PKCS7 helpers ****************************/
static void
EncryptOut(void *arg, const char *buf, unsigned long len)
{
   FILE *out;
   out = (FILE *)arg; 
   fwrite (buf, len, 1, out);
}

static SECItem *
password_hardcode(void *arg, void *handle)
{
  SECItem *pw = NULL;
  PGLOBAL_SIG pg_sig = (PGLOBAL_SIG) arg;
  if (pg_sig->certStorePassword) {
	pw = (SECItem *) zMalloc(sizeof(SECItem));
	char *pass = (char *) PORT_Alloc( (strlen((char *) pg_sig->certStorePassword))*2 + 1);
	strcpy(pass,(const char *) pg_sig->certStorePassword);
	pw->data = (BYTE*) pass;
	pw->len = strlen(pass); //--!! do we need +1 here???
  }
  return pw;
}

/************************* END OF NSS PKCS7 helpers *********************/
#endif

// EncryptBlob encrypts and base64 encodes the encrypted data
// in file mode it always returns NULL, and sets encryptedSize to 0 when error.
BYTE * CSignature::EncryptBlob(DS_DATA_BLOB * blobPtr, BOOL base64EncodeOutput, unsigned long * encryptedSize, BSTR inFile, BSTR outFile)
{
#ifdef NSS
    SEC_PKCS7ContentInfo *cinfo=NULL;
    SEC_PKCS7EncoderContext *ecx=NULL;
    SECStatus rv;
    CERTCertDBHandle *certHandle;
    CERTCertificate **certs=NULL;
	char **certArray = NULL;
	int certCount =0;
	int i=0,j=0;
	SECItem derCert;
	int err=0;
	UINT encodedSize;
	unsigned char *encodedEncryptedData;
	DWORD cbRef = 0;
	BYTE *pbRef = NULL;
	FILE *outFile;

	// NSS doesn't trust the root certificate in the chain.
	// This part requires additional attention - implement PKCS7 on our own.
	setError(SigHandle, NSS_NOT_SUPPORTED);
	return NULL;

	EnterObjectLog;
	certHandle = CERT_GetDefaultCertDB();

	// get recipient certificate list or select one
	if (RecipientCertificateCount == 0)
	{
		certs = (CERTCertificate **) zMalloc(sizeof(CERTCertificate *));
#ifdef WIN32
		char *certData = dlgRecipient->selectCertificate();
#else
		char *certData = NULL;
#endif
		if (certData) {
			certCount =1;
			certArray = (char **) zMalloc(sizeof (char *));
			certArray[0] = certData;
		}
	}else{
		certCount =RecipientCertificateCount;
		certArray = (char **) zMalloc(sizeof (char *) * certCount);
		for (i=0;i<RecipientCertificateCount;i++) {
			certArray[i] = (char *)zMalloc(strlen(RecipientCertificateList[i])+1);
			strcpy(certArray[i],RecipientCertificateList[i]);
		}
	}

	if (certCount==0 || certArray==NULL) {
		return NULL;
	}
	certs = (CERTCertificate **) zMalloc(sizeof(CERTCertificate *) * certCount);
	memset(certs,0,sizeof(CERTCertificate *) * certCount);


	for (i=0;i<certCount;i++) {	
		derCert.len = base64decodeSize(strlen(certArray[i]));
		// allocate memory
		derCert.data = NULL;
		if(!(derCert.data = (BYTE*)zMalloc(derCert.len+1))){
			setError(SigHandle, MEMORY_FAULT);
			for (j=0;j<certCount;j++) {
				if (certArray[j]) zFree(certArray[j]);
				if (certs[j]) CERT_DestroyCertificate(certs[j]);
			}
			zFree(certArray);
			zFree(certs);
			return NULL;
		}
		if ((derCert.len = base64decode((unsigned char*)certArray[i],
									derCert.data,
									derCert.len))==-1) 
		{
			setError(SigHandle, MEMORY_FAULT);
			for (j=0;j<certCount;j++) {
				if (certArray[j]) zFree(certArray[j]);
				if (certs[j]) CERT_DestroyCertificate(certs[j]);
			}			
			zFree(derCert.data);
			zFree(certArray);
			zFree(certs);
			return NULL;
		}

		CERTCertificate *cert = DecodeDERCertificate(&derCert);
		if (!cert) {
			setError(SigHandle, CAPI_CREATE_CERT_CNTX);
			for (j=0;j<certCount;j++) {
				if (certArray[j]) zFree(certArray[j]);
				if (certs[j]) CERT_DestroyCertificate(certs[j]);
			}			
			zFree(derCert.data);
			zFree(certArray);
			zFree(certs);
			return NULL;
		}
		certs[i] = cert;
		zFree(derCert.data);
	}

	// clean helper array
	for (j=0;j<certCount;j++) {
		if (certArray[j]) zFree(certArray[j]);
	}			
	zFree(certArray);
	certArray=NULL;

	// at this point certs has all recipient certificates.
	// start PKCS7 message
	// bug in NSS - must fake key usage in order to go through
	certs[0]->keyUsage = KU_DIGITAL_SIGNATURE | KU_KEY_AGREEMENT_OR_ENCIPHERMENT | KU_KEY_CERT_SIGN;
    cinfo = SEC_PKCS7CreateEnvelopedData (certs[0],
					  certUsageEmailSigner,
					  NULL, SEC_OID_RC4, 0, 
					  (SECKEYGetPasswordKey) password_hardcode, SigHandle);
	if (cinfo == NULL) {
		err=TRUE;
		goto retLabel;
	}

	// add all recipients if we have more than 1	
    for (i=1; i<certCount; i++) {
		// bug in NSS - must fake key usage in order to go through
		certs[i]->keyUsage = KU_DIGITAL_SIGNATURE | KU_KEY_AGREEMENT_OR_ENCIPHERMENT | KU_KEY_CERT_SIGN;
		rv = SEC_PKCS7AddRecipient (cinfo, certs[i], certUsageEmailSigner,
				    NULL); // default db handle
		if (rv != SECSuccess) {
			err=TRUE;
			goto retLabel;
		}
    }

	// passing callback function to perform writing and parameter for it
	// for now using file.
#ifdef WIN32
	outFile = fopen("c:\\temp\\pkcs7.tmp","wb");
#else
	outFile = fopen("/tmp/SecureXML/pkcs7.tmp", "wb");
#endif
    ecx = SEC_PKCS7EncoderStart (cinfo, EncryptOut, outFile, NULL);
	if (ecx == NULL) {
		fclose(outFile);
		err=TRUE;
		goto retLabel;
	}

	rv = SEC_PKCS7EncoderUpdate(ecx, (const char *)blobPtr->pbData, blobPtr->cbData);
	if (rv != SECSuccess){
		fclose(outFile);
		err=TRUE;
		goto retLabel;
    }

	if (SEC_PKCS7EncoderFinish(ecx, NULL, NULL) != SECSuccess) {
		fclose(outFile);
		err=TRUE;
		goto retLabel;
	}

    SEC_PKCS7DestroyContentInfo (cinfo);
	fclose(outFile);
	//--TODO: delete file

	// read encrypted data from the file
	cbRef = 0;
#ifdef WIN32
	pbRef = xsDereferenceURI ("c:\\temp\\pkcs7.tmp",&cbRef);
#else
	pbRef = xsDereferenceURI("/tmp/SecureXML/pkcs7.tmp", &cbRef);
#endif
	
	if (base64EncodeOutput == TRUE)
	{
		// base64 encode data
		encodedSize = base64encodeSize(cbRef);
		if(!(encodedEncryptedData = (unsigned char*)zMalloc(encodedSize+1)))
		{
			setError(SigHandle, MEMORY_FAULT);
			zFree(pbRef);
			err=TRUE;
			goto retLabel;
		}
		if ((encodedSize = base64encode(	(unsigned char *)pbRef,
							cbRef,
							(unsigned char*)encodedEncryptedData,
							encodedSize))==-1) 
		{
			setError(SigHandle, MEMORY_FAULT);
			zFree(pbRef);
			zFree(encodedEncryptedData);
			err=TRUE;
			goto retLabel;
		}

		*(encodedEncryptedData+encodedSize)='\0';
		zFree(pbRef);
		*encryptedSize = encodedSize + 1;
	}
	else
	{
		encodedEncryptedData = pbRef;
		*encryptedSize = cbRef;
	}

retLabel:

	if (cinfo) SEC_PKCS7DestroyContentInfo (cinfo);
    if ( certs ) {
		for ( i = 0; i < certCount; i++ ) {
		    if ( certs[i] ) {
				CERT_DestroyCertificate(certs[i]);
			}
		}
	}

	zFree(certs);
	ExitObjectLog;
	if (err) {
		return NULL;
	}else{
		return encodedEncryptedData;
	}
#else
	PCCERT_CONTEXT pCertContext = NULL; 
	HCRYPTPROV hCryptProv=0;
	PCCERT_CONTEXT *RecipientCertContextArray;
	CRYPT_ALGORITHM_IDENTIFIER EncryptAlgorithm;
	CRYPT_ENCRYPT_MESSAGE_PARA EncryptParams;
	CMSG_RC4_AUX_INFO	RC4AuxInfo;
	HCRYPTMSG hMsg;

	BSTR bstrCertData=NULL;
	DWORD dwBufferSize = 0;
	int cbCert=0;
	BYTE *pbCert=NULL;
	char *certData;
	BYTE *pbContent=NULL;
	DWORD cbContent=0;
	LPSTR *curRecipientCertificateList;
	UINT  curRecipientCertificateCount;
	DWORD EncryptAlgSize;
	DWORD EncryptParamsSize;
	BYTE*    pbEncryptedBlob = NULL;
	DWORD    cbEncryptedBlob = 0;
	UINT i,j;

	USES_CONVERSION;
	EnterObjectLog;

	*encryptedSize = 0;

	if (blobPtr == NULL && inFile == NULL) return NULL;

	if (blobPtr!=NULL) {
		pbContent = (BYTE *)blobPtr->pbData;
		cbContent = blobPtr->cbData;
	}else{
		// cbContent equals file size
		BYTE *ifName = HeapW2A(inFile);
		HANDLE hFile; 
 
		hFile = CreateFile((LPCSTR)ifName,
                GENERIC_READ,              // open for reading 
                FILE_SHARE_READ,           // share for reading 
                NULL,                      // no security 
                OPEN_EXISTING,             // existing file only 
                FILE_ATTRIBUTE_NORMAL,     // normal file 
                NULL);                     // no attr. template 
		zFree(ifName);
		if (hFile == INVALID_HANDLE_VALUE) 
		{ 
			setError(SigHandle, IO_ERROR);
			return NULL;
		}
        cbContent = GetFileSize(hFile, NULL);
		CloseHandle(hFile);
	}

	if (RecipientCertificateCount == 0)
	{
		curRecipientCertificateList = (LPSTR *)zMalloc(sizeof(LPSTR *));
		RecipientCertContextArray = (PCCERT_CONTEXT *)zMalloc(sizeof(PCCERT_CONTEXT *));
		if ((RecipientCertContextArray == NULL) || 
			(curRecipientCertificateList == NULL))
		{
			setError(SigHandle, MEMORY_FAULT);
			return NULL;
		}
#ifdef WIN32
		if (RecipientCertCount != 0)
			curRecipientCertificateList[0]=	dlgRecipient->selectCertificate();
		else
#elif UNIX
		if (RecipientCertCount == 0)
#endif
		{
			zFree(curRecipientCertificateList);
			zFree(RecipientCertContextArray);
			setError(SigHandle, NO_CERTIFICATE);
			return NULL;
		}

		if (curRecipientCertificateList[0] == NULL)
		{
			zFree(curRecipientCertificateList);
			zFree(RecipientCertContextArray);
			setError(SigHandle, NO_CERTIFICATE);
			return NULL;
		}
		curRecipientCertificateCount = 1;
	}
	else
	{
		curRecipientCertificateCount = RecipientCertificateCount;
		curRecipientCertificateList  = RecipientCertificateList;
		RecipientCertContextArray = (PCCERT_CONTEXT *)zMalloc(sizeof(PCCERT_CONTEXT *) * curRecipientCertificateCount);
		if (RecipientCertContextArray == NULL)
		{
			setError(SigHandle, MEMORY_FAULT);
			return NULL;
		}

	}

	//--------------------------------------------------------------------
	// Get a handle to a cryptographic provider.
	//--------------------------------------------------------------------
	// Attempt to acquire a context and a key
	// container. The context will use the default CSP
	// for the RSA_FULL provider type. DwFlags is set to 0
	// to attempt to open an existing key container.

	if(!(CryptAcquireContext(
				&hCryptProv,           // Handle to the CSP
				NULL,                  // Container name 
				MS_ENHANCED_PROV,      // Use the default provider
				PROV_RSA_FULL,         // Provider type
				CRYPT_MACHINE_KEYSET )))				   // Flag values
	{ // Keyset does not exist. lets create one
		if(!(CryptAcquireContext(
				&hCryptProv,         // Address for handle to be returned.
				NULL,                // Use the current user's logon name.
				MS_ENHANCED_PROV,    // Use the default provider.
				PROV_RSA_FULL,       // Need to both encrypt and sign.
				CRYPT_NEWKEYSET | CRYPT_MACHINE_KEYSET )))   // No flags needed.
		{
			setError(SigHandle, CAPI_ACQUIRE_CNTX);
			return NULL;
		}
	}

	for (i=0; i<curRecipientCertificateCount; i++)
	{
		certData = (char *)curRecipientCertificateList[i];
		cbCert = base64decodeSize(strlen(certData));
		// allocate memory
		pbCert = NULL;
		if(!(pbCert = (BYTE*)zMalloc(cbCert+1)))
		{
			setError(SigHandle, MEMORY_FAULT);
			if (RecipientCertificateCount == 0)
				zFree(curRecipientCertificateList);
			for (j=0; j<i; i++)
			{
				CertFreeCertificateContext(RecipientCertContextArray[j]);
			}
			zFree(RecipientCertContextArray);
			return NULL;
		}

		if ((cbCert = base64decode((unsigned char*)certData,
									pbCert,
									cbCert))==-1) 
		{
			setError(SigHandle, MEMORY_FAULT);
			zFree(pbCert);
			if (RecipientCertificateCount == 0)
				zFree(curRecipientCertificateList);
			for (j=0; j<i; i++)
			{
				CertFreeCertificateContext(RecipientCertContextArray[j]);
			}
			zFree(RecipientCertContextArray);
			return NULL;
		}

		if(!(pCertContext = (CERT_CONTEXT *) CertCreateCertificateContext(
			MY_ENCODING_TYPE  ,            // The encoding type
			pbCert,   // The encoded data from the certificate retrieved
			cbCert)))  // The length of the encoded data
		{
			setError(SigHandle, CAPI_CREATE_CERT_CNTX);
			zFree(pbCert);
			if (RecipientCertificateCount == 0)
				zFree(curRecipientCertificateList);
			for (j=0; j<i; i++)
			{
				CertFreeCertificateContext(RecipientCertContextArray[j]);
			}
			zFree(RecipientCertContextArray);
			return NULL;
		}
		zFree(pbCert);
		
		DWORD pkalgid = CertOIDToAlgId(pCertContext->pCertInfo->SubjectPublicKeyInfo.Algorithm.pszObjId);

	// what type of algorithm?
		switch(GET_ALG_TYPE(pkalgid)) 
		{
			case ALG_TYPE_DSS:
				setError(SigHandle, INVALID_ENC_ALG);
				if (RecipientCertificateCount == 0)
					zFree(curRecipientCertificateList);
				for (j=0; j<i; i++)
				{
					CertFreeCertificateContext(RecipientCertContextArray[j]);
				}
				zFree(RecipientCertContextArray);
				return NULL;
				break;
			case ALG_TYPE_RSA:
				break;
			default:
				setError(SigHandle, INVALID_ENC_ALG);
				if (RecipientCertificateCount == 0)
					zFree(curRecipientCertificateList);
				for (j=0; j<i; i++)
				{
					CertFreeCertificateContext(RecipientCertContextArray[j]);
				}
				zFree(RecipientCertContextArray);
				return NULL;
		}

		//--------------------------------------------------------------------
		// Create a RecipientCertArray.

		RecipientCertContextArray[i] = pCertContext;
	}
	if (RecipientCertificateCount == 0)
		zFree(curRecipientCertificateList);

   PCERT_INFO *RecipientCertInfoArray = NULL;
   CMSG_ENVELOPED_ENCODE_INFO EnvelopedEncodeInfo;
   if (curRecipientCertificateCount)
      RecipientCertInfoArray = (PCERT_INFO *)zMalloc(sizeof(PCERT_INFO *) * curRecipientCertificateCount);
   for (int i=0; i< curRecipientCertificateCount; i++) {
     RecipientCertInfoArray[i] = RecipientCertContextArray[i]->pCertInfo;
   }
   EncryptAlgSize = sizeof(EncryptAlgorithm);
   memset(&EncryptAlgorithm, 0, EncryptAlgSize);
   EncryptAlgorithm.pszObjId = szOID_RSA_RC4;  


   //--------------------------------------------------------------------
   // Initialize the CMSG_ENVELOPED_ENCODE_INFO structure.

   memset(&EnvelopedEncodeInfo, 
       0,
       sizeof(CMSG_ENVELOPED_ENCODE_INFO));
   EnvelopedEncodeInfo.cbSize = sizeof(CMSG_ENVELOPED_ENCODE_INFO);
   EnvelopedEncodeInfo.hCryptProv = hCryptProv;
   EnvelopedEncodeInfo.ContentEncryptionAlgorithm = EncryptAlgorithm;
   RC4AuxInfo.cbSize = sizeof(CMSG_RC4_AUX_INFO);
   RC4AuxInfo.dwBitLen = 20;
   EnvelopedEncodeInfo.pvEncryptionAuxInfo = &RC4AuxInfo;
   EnvelopedEncodeInfo.cRecipients = curRecipientCertificateCount;
   EnvelopedEncodeInfo.rgpRecipients = RecipientCertInfoArray;

   //--------------------------------------------------------------------
   // Get the size of the encoded message BLOB.

   if(!(cbEncryptedBlob = CryptMsgCalculateEncodedLength(
     MY_ENCODING_TYPE,        // message encoding type
     0,                       // flags
     CMSG_ENVELOPED,          // message type
     &EnvelopedEncodeInfo,    // pointer to structure
     NULL,    // inner content OID, szOID_RSA_encryptedData
     cbContent)))           // size of content
   {
		setError(SigHandle, CAPI_ENCRYPT_MSG);
		for (i=0; i<curRecipientCertificateCount; i++)
		{
			CertFreeCertificateContext(RecipientCertContextArray[i]);
		}
		zFree(RecipientCertContextArray);
		if (RecipientCertInfoArray) zFree(RecipientCertInfoArray);
        return NULL;
   }

   CMSG_STREAM_INFO sInfo;
   sInfo.pvArg = NULL;
   PCMSG_STREAM_INFO psInfo = NULL;
   DWORD eFlags = 0;

   if (pbContent ==NULL) {
	   BYTE *fname = HeapW2A(outFile);
	   FILE *fout = fopen((const char*)fname, "wb");
	   zFree(fname);
	   if (!fout) {
		  setError(SigHandle, IO_ERROR);
		  for (i=0; i<curRecipientCertificateCount; i++)
		  {
		  	CertFreeCertificateContext(RecipientCertContextArray[i]);
		  }
		  zFree(RecipientCertContextArray);
		  if (RecipientCertInfoArray) zFree(RecipientCertInfoArray);
		  return NULL;
	   }
//	   sInfo.cbContent = cbEncryptedBlob;
	   sInfo.cbContent = 0xFFFFFFFF;
	   sInfo.pfnStreamOutput = encryptCallback;
	   sInfo.pvArg = fout;
	   psInfo = &sInfo;
	   eFlags = CMSG_DETACHED_FLAG;
   }
   //--------------------------------------------------------------------
   // Open a message to encode.
   if(!(hMsg = CryptMsgOpenToEncode(
     MY_ENCODING_TYPE,        // encoding type
     eFlags,                  // flags
     CMSG_ENVELOPED,          // message type
     &EnvelopedEncodeInfo,    // pointer to structure
     NULL,    // inner content OID
     psInfo)))                   // stream information (used for file encryption)
   {
		setError(SigHandle, CAPI_ENCRYPT_MSG);
		for (i=0; i<curRecipientCertificateCount; i++)
		{
			CertFreeCertificateContext(RecipientCertContextArray[i]);
		}
		zFree(RecipientCertContextArray);
		if (RecipientCertInfoArray) zFree(RecipientCertInfoArray);
		return NULL;
   }
   //--------------------------------------------------------------------
   // Update the message with the data.

   if (pbContent != NULL) {
		if(!CryptMsgUpdate(
			hMsg,              // handle to the message
			pbContent,      // pointer to the signed data BLOB
			cbContent,      // size of the data BLOB
			TRUE))             // last call
		{
				setError(SigHandle, CAPI_ENCRYPT_MSG);
				for (i=0; i<curRecipientCertificateCount; i++)
				{
					CertFreeCertificateContext(RecipientCertContextArray[i]);
				}
				zFree(RecipientCertContextArray);
				if (RecipientCertInfoArray) zFree(RecipientCertInfoArray);
				if (hMsg) CryptMsgClose(hMsg);
				return NULL;
		}
   
		//--------------------------------------------------------------------
		// Allocate memory for the returned BLOB.
		if(!(pbEncryptedBlob = (BYTE*)zMalloc(cbEncryptedBlob)))
		{
				setError(SigHandle, MEMORY_FAULT);
				for (i=0; i<curRecipientCertificateCount; i++)
				{
					CertFreeCertificateContext(RecipientCertContextArray[i]);
				}
				zFree(RecipientCertContextArray);
				if (RecipientCertInfoArray) zFree(RecipientCertInfoArray);
				if (hMsg) CryptMsgClose(hMsg);
				return NULL;
		}

		//--------------------------------------------------------------------
		// Get the resulting message.

		if(!CryptMsgGetParam(
			hMsg,                  // handle to the message
			CMSG_CONTENT_PARAM,    // parameter type
			0,                     // index
			pbEncryptedBlob,         // pointer to the enveloped,
									//  signed data BLOB
			&cbEncryptedBlob))       // size of the BLOB
		{
				setError(SigHandle, CAPI_ENCRYPT_MSG);
				for (i=0; i<curRecipientCertificateCount; i++)
				{
					CertFreeCertificateContext(RecipientCertContextArray[i]);
				}
				zFree(RecipientCertContextArray);
				if (RecipientCertInfoArray) zFree(RecipientCertInfoArray);
				if (hMsg) CryptMsgClose(hMsg);
				return NULL;
		}
    }else{
		// read the file by portions in 38K
		BYTE *ifName = HeapW2A(inFile);
		FILE *ifHandle = fopen((const char*)ifName, "rb");
		BYTE buf[38400];
		BOOL lastCall = FALSE;
		while(!lastCall) {
			int n = fread(buf,1,38400,ifHandle);
			if (n == 0 && !ferror(ifHandle)) {
				fclose(ifHandle);
				lastCall = TRUE;
			}
			if (feof(ifHandle)) {
				lastCall = TRUE;
			}
			if (ferror(ifHandle)!=0) {
				fclose(ifHandle);
				setError(SigHandle, IO_ERROR);
				for (i=0; i<curRecipientCertificateCount; i++)
				{
					CertFreeCertificateContext(RecipientCertContextArray[i]);
				}
				zFree(RecipientCertContextArray);
				if (RecipientCertInfoArray) zFree(RecipientCertInfoArray);
				if (sInfo.pvArg) fclose((FILE *)sInfo.pvArg);
				zFree(ifName);
				if (hMsg) CryptMsgClose(hMsg);
				return NULL;
			}
			if (n>0) {
				if(!CryptMsgUpdate(
					hMsg,              // handle to the message
					buf,      // pointer to the signed data BLOB
					n,      // size of the data BLOB
					lastCall))             // last call
				{
					long e = getlasterror();
					setError(SigHandle, CAPI_ENCRYPT_MSG);
					for (i=0; i<curRecipientCertificateCount; i++)
					{
						CertFreeCertificateContext(RecipientCertContextArray[i]);
					}
					zFree(RecipientCertContextArray);
					if (RecipientCertInfoArray) zFree(RecipientCertInfoArray);
					if (sInfo.pvArg) fclose((FILE *)sInfo.pvArg);
					zFree(ifName);
					if (hMsg) CryptMsgClose(hMsg);
					return NULL;
				}
			}
		}
		zFree(ifName);
		*encryptedSize = cbEncryptedBlob;
    }
	if (hMsg) CryptMsgClose(hMsg);
	//if (sInfo.pvArg) fclose((FILE *)sInfo.pvArg);

	for (i=0; i<curRecipientCertificateCount; i++)
	{
		CertFreeCertificateContext(RecipientCertContextArray[i]);
	}
	zFree(RecipientCertContextArray);
	if (RecipientCertInfoArray) zFree(RecipientCertInfoArray);

	UINT encodedSize;
	unsigned char *encodedEncryptedData;

	if (base64EncodeOutput == TRUE)
	{
		// Base64 encode
		encodedSize = base64encodeSize(cbEncryptedBlob);
		if(!(encodedEncryptedData = (unsigned char*)zMalloc(encodedSize+1)))
		{
			setError(SigHandle, MEMORY_FAULT);
			zFree(pbEncryptedBlob);
			return NULL;
		}
		if ((encodedSize = base64encode(	(unsigned char *)pbEncryptedBlob,
							cbEncryptedBlob,
							(unsigned char*)encodedEncryptedData,
							encodedSize))==-1) 
		{
			setError(SigHandle, MEMORY_FAULT);
			zFree(encodedEncryptedData);
			zFree(pbEncryptedBlob);
			return NULL;
		}
		*(encodedEncryptedData+encodedSize)='\0';
		zFree(pbEncryptedBlob);
		*encryptedSize = encodedSize + 1;
	}
	else
	{
		*encryptedSize = cbEncryptedBlob;
		encodedEncryptedData = pbEncryptedBlob;
	}
	ExitObjectLog;
	return encodedEncryptedData;
#endif
}

STDMETHODIMP CSignature::put_TrustedRoots(VARIANT newVal)
{
	UINT elementCount=0;
	UINT itemCount=0,i;
	BSTR	*bstrList=NULL;
	DWORD dataSize;
	BYTE *dataPtr, *rootCertData;
	DWORD encodedDataSize;
	BYTE *encodedDataPtr;
USES_CONVERSION;
	EnterObjectLog;
	if ((newVal.vt != VT_BSTR) &&
		(newVal.vt != VT_DISPATCH) &&
		!(newVal.vt & VT_ARRAY) && 
		!(newVal.vt & VT_BYREF))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}
	if (CertVerifyParams.trustRootCertCount != 0)
	{
		for (unsigned int i=0; i < CertVerifyParams.trustRootCertCount; i++)
			zFree(CertVerifyParams.trustRootCerts[i]);
		zFree(CertVerifyParams.trustRootCerts);
		CertVerifyParams.trustRootCertCount = 0;
	}

	bstrList = GetBstrArrayFromVariant(newVal, &itemCount);

	if ((bstrList == NULL) || (itemCount == 0))
	{
		CertVerifyParams.trustRootCerts = NULL;
		CertVerifyParams.trustRootCertCount = 0;
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	CertVerifyParams.trustRootCertCount = itemCount;
	CertVerifyParams.trustRootCerts = (char **) zMalloc(sizeof(char *) * itemCount);
	if (CertVerifyParams.trustRootCerts == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		CertVerifyParams.trustRootCertCount = 0;
		for (i =0; i < itemCount; i++)
			if (bstrList[i] != NULL)
				SysFreeString(bstrList[i]);
		zFree(bstrList);
		return S_FALSE;
	}
	memset(CertVerifyParams.trustRootCerts, 0, sizeof(char *) * itemCount);

	for (elementCount =0; elementCount < itemCount; elementCount++)
	{
		//char *aBstrList = (char *)HeapW2A(bstrList[elementCount]);
		//dataPtr = xsDereferenceURI(aBstrList, &dataSize);
		//zFree(aBstrList);
		if (ReadAllBin(bstrList[elementCount], &dataPtr, &dataSize) != S_FALSE)
		{
			rootCertData = (BYTE *)zMalloc(dataSize + 1);
			if (rootCertData == NULL)
			{
				setError(SigHandle, MEMORY_FAULT);
				for (i =0; i < itemCount; i++)
					if (bstrList[i] != NULL)
						SysFreeString(bstrList[i]);
				zFree(bstrList);
				zFree(dataPtr);
				for (i=0; i < elementCount; i++)
				{
					if (CertVerifyParams.trustRootCerts[i] != NULL)
					{
						zFree(CertVerifyParams.trustRootCerts[i]);
						CertVerifyParams.trustRootCerts[i] = NULL;
					}
				}
				zFree(CertVerifyParams.trustRootCerts);
				CertVerifyParams.trustRootCerts = NULL;
				CertVerifyParams.trustRootCertCount = 0;
				return S_FALSE;
			}
			memcpy(rootCertData, dataPtr, dataSize);
			*(rootCertData + dataSize) = '\0';
			for (i=0; i < dataSize; i++)
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
			CertVerifyParams.trustRootCerts[elementCount] = (LPSTR)rootCertData;
			zFree(dataPtr);
		}
		else
		{
			setError(SigHandle, FILE_NOT_FOUND);
			for (i =0; i < itemCount; i++)
				if (bstrList[i] != NULL)
					SysFreeString(bstrList[i]);
			zFree(bstrList);
			for (i=0; i < elementCount; i++)
			{
				if (CertVerifyParams.trustRootCerts[i] != NULL)
				{
					zFree(CertVerifyParams.trustRootCerts[i]);
					CertVerifyParams.trustRootCerts[i] = NULL;
				}
			}
			zFree(CertVerifyParams.trustRootCerts);
			CertVerifyParams.trustRootCerts = NULL;
			CertVerifyParams.trustRootCertCount = 0;
			return S_FALSE;
		}
	}
	for (i =0; i < itemCount; i++)
		if (bstrList[i] != NULL)
			SysFreeString(bstrList[i]);
	zFree(bstrList);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_RecipientCertificateFiles(VARIANT newVal)
{
	UINT elementCount=0,i;
	UINT itemCount=0;
	BSTR	*bstrList=NULL;
	DWORD dataSize;
	BYTE *dataPtr, *recpCertData;
	DWORD encodedDataSize;
	BYTE *encodedDataPtr;

USES_CONVERSION;
	EnterObjectLog;
	if ((newVal.vt != VT_BSTR) &&
		(newVal.vt != VT_DISPATCH) &&
		!(newVal.vt & VT_ARRAY) && 
		!(newVal.vt & VT_BYREF))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}
	if (RecipientCertificateCount != 0)
	{
		for (unsigned int i=0; i < RecipientCertificateCount; i++)
			zFree(RecipientCertificateList[i]);
		zFree(RecipientCertificateList);
		RecipientCertificateCount = 0;
		RecipientCertificateList = NULL;
	}

	bstrList = GetBstrArrayFromVariant(newVal, &itemCount);


	if ((bstrList == NULL) || (itemCount == 0))
	{
		RecipientCertificateList = NULL;
		RecipientCertificateCount = 0;
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	RecipientCertificateCount = itemCount;
	RecipientCertificateList = (char **) zMalloc(sizeof(char *) * itemCount);
	if (RecipientCertificateList == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		RecipientCertificateCount = 0;
		for (i =0; i < itemCount; i++)
			if (bstrList[i] != NULL)
				SysFreeString(bstrList[i]);
		zFree(bstrList);
		return S_FALSE;
	}
	memset(RecipientCertificateList, 0, sizeof(char *) * itemCount);

	for (elementCount =0; elementCount < itemCount; elementCount++)
	{
		//char *aBstrList = (char *)HeapW2A(bstrList[elementCount]);
		//dataPtr = xsDereferenceURI(aBstrList, &dataSize);
		//zFree(aBstrList);
		if (ReadAllBin(bstrList[elementCount], &dataPtr, &dataSize) != S_FALSE)
		{
			recpCertData = (BYTE *)zMalloc(dataSize + 1);
			if (recpCertData == NULL)
			{
				setError(SigHandle, MEMORY_FAULT);
				for (i =0; i < itemCount; i++)
					if (bstrList[i] != NULL)
						SysFreeString(bstrList[i]);
				zFree(bstrList);
				zFree(dataPtr);
				for (i=0; i < elementCount; i++)
				{
					if (RecipientCertificateList[i] != NULL)
					{
						zFree(RecipientCertificateList[i]);
						RecipientCertificateList[i] = NULL;
					}
				}
				zFree(RecipientCertificateList);
				RecipientCertificateList = NULL;
				RecipientCertificateCount = 0;
				return S_FALSE;
			}
			memcpy(recpCertData, dataPtr, dataSize);
			*(recpCertData + dataSize) = '\0';
			for (i=0; i < dataSize; i++)
			{
				if (strchr((const char *)Base64Chars, *(recpCertData + i)) == NULL)
				{
					if ((*(recpCertData + i) == 0x0d) ||
						(*(recpCertData + i) == 0x0a) ||
						(*(recpCertData + i) == 0x20))
						continue;
					// The data is not base64 encoded, so lets encode it now
					encodedDataSize = base64encodeSize(dataSize);
					encodedDataPtr = (BYTE *)zMalloc(encodedDataSize + 1);
					encodedDataSize = base64encode(recpCertData, dataSize, encodedDataPtr, encodedDataSize + 1);
					zFree(recpCertData);
					recpCertData = encodedDataPtr;
					break;
				}
			}
			RecipientCertificateList[elementCount] = (LPSTR)recpCertData;
			zFree(dataPtr);
		}
		else
		{
			setError(SigHandle, FILE_NOT_FOUND);
			for (i =0; i < itemCount; i++)
				if (bstrList[i] != NULL)
					SysFreeString(bstrList[i]);
			zFree(bstrList);
			for (i=0; i < elementCount; i++)
			{
				if (RecipientCertificateList[i] != NULL)
				{
					zFree(RecipientCertificateList[i]);
					RecipientCertificateList[i] = NULL;
				}
			}
			zFree(RecipientCertificateList);
			RecipientCertificateList = NULL;
			RecipientCertificateCount = 0;
			return S_FALSE;
		}
	}
	for (i =0; i < itemCount; i++)
		if (bstrList[i] != NULL)
			SysFreeString(bstrList[i]);
	zFree(bstrList);
	ExitObjectLog;
	return S_OK;
}

BOOL CSignature::CheckCertificateValidity(BYTE * certData, LPSYSTEMTIME pSysTime, PDS_DATA_BLOB password , VERIFICATION_PARAMS * certVerParams, PGLOBAL_SIG pg_sig)
{
	BYTE **certificateList;
	UINT certificateCount;
	BOOL result;
	EnterObjectLog;

	LPWSTR pwd = NULL;
	if (password) {
		pwd = (LPWSTR) password->pbData;
	}
#ifdef NSS
	// password is big endian, swap bytes
	SECItem s;
	s.len=0;
	if (password) {
		s.data = (BYTE *) zMalloc(password->cbData);
		s.len  = password->cbData;
		memcpy(s.data,password->pbData,s.len);
		SwapUnicodeBytes(&s);
		pwd = (LPWSTR) s.data;
	}
#endif

	if ((CertVerifyParams.usedCrlCount != 0) &&
		(CertVerifyParams.usedCrlList != NULL))
	{
		for (UINT i=0; i < CertVerifyParams.usedCrlCount; i++)
		{
			if (CertVerifyParams.usedCrlList[i] != NULL)
				zFree(CertVerifyParams.usedCrlList[i]);
		}
		zFree(CertVerifyParams.usedCrlList);
		CertVerifyParams.usedCrlList = NULL;
		CertVerifyParams.usedCrlCount = 0;
	}
#ifdef NSS
	SECItem spwd;
	if (password && password->cbData) {
		spwd.len = password->cbData;
		spwd.data = password->pbData;
	}else{
		spwd.data = (BYTE *) zMalloc(sizeof(char));
		spwd.data[0] = '\0';
		spwd.len = 1;
	}
	certificateList = crGetSignerCertChain(	certData,
											&spwd,
											&certificateCount,
											pg_sig);
#else
	certificateList = crGetSignerCertChain(	certData,
											pwd,
											&certificateCount,
											pg_sig);
#endif
	if (certificateList == NULL)
	{
		// use just this certificate
		if (useCam) {
			cleanupError(pg_sig);
			// if this is PFX, convert it to X509
			certificateList = (BYTE **) zMalloc(sizeof(BYTE *));
			if (crIsPFX(certData,password,pg_sig)) {
				DS_DATA_BLOB PfxCertDataBlob;
				BYTE *X509Cert=NULL;
				PfxCertDataBlob.cbData = base64decodeSize((DWORD)strlen((const char *)certData));
				PfxCertDataBlob.pbData = (BYTE *)zMalloc (PfxCertDataBlob.cbData+1);
				memset(PfxCertDataBlob.pbData,0,PfxCertDataBlob.cbData+1);
				PfxCertDataBlob.cbData = base64decode(certData,(unsigned char *)PfxCertDataBlob.pbData,PfxCertDataBlob.cbData); 
				if (PfxCertDataBlob.cbData==-1) {
					zFree(PfxCertDataBlob.pbData);
					setError(pg_sig, BASE64_ERROR);
					zFree(certificateList);
					return FALSE;
				}				
				PCERT_DESCR cdes[1];
				cdes[0]= NULL;
#ifdef NSS				
				X509Cert	= crPFX2X509(&PfxCertDataBlob, &spwd, cdes, pg_sig);
#else
				X509Cert	= crPFX2X509(&PfxCertDataBlob, (LPCWSTR) pwd, cdes, pg_sig);
#endif
				if (cdes[0] && cdes[0]->certificate) {
					zFree(cdes[0]->certificate);
				}
				zFree(PfxCertDataBlob.pbData);
				if (!X509Cert) {
					zFree(certificateList);
					return FALSE;
				}
				certificateList[0] = X509Cert;
				certificateCount=1;
			}else{
				certificateList[0] = (BYTE *) zMalloc(strlen((const char *)certData) +1);
				strcpy((char *)certificateList[0],(const char *)certData);
				certificateCount=1;
			}
		}else{
			return FALSE;
		}
	}
	if (useCam)
	{
		result = crVerifyCertificateUsingCam(certificateList,
								certificateCount,
								pSysTime, 
								pwd,
								&CertVerifyParams,
								pg_sig);
	}
	else
	{
#ifdef USE_OCSP
		if ((useOcsp) && (pOcspClient != NULL))
		{
			result = crVerifyCertificateUsingOcsp(certificateList,
								certificateCount,
								pSysTime, 
								pwd,
								&CertVerifyParams,
								pg_sig);
		}
		else
#endif
#ifdef NSS
			result = crVerifyCertificate(certificateList,
									certificateCount,
									pSysTime, 
									&spwd,
									&CertVerifyParams,
									pg_sig);
#else
			result = crVerifyCertificate(certificateList,
									certificateCount,
									pSysTime, 
									pwd,
									&CertVerifyParams,
									pg_sig);
#endif
	}
	for (UINT i=0; i < certificateCount; i++)
	{
		zFree(certificateList[i]);
	}
	zFree(certificateList);

#ifdef NSS
	if (s.len!=0) {
		zFree(s.data);
	}
#endif
	ExitObjectLog;
	return result;
}

STDMETHODIMP CSignature::put_DetachedObjects(VARIANT newVal)
{
	UINT elementCount=0;
	UINT itemCount=0;
	BSTR	*bstrList=NULL;

	EnterObjectLog;
	if ((newVal.vt != VT_BSTR) &&
		(newVal.vt != VT_DISPATCH) &&
		!(newVal.vt & VT_ARRAY) && 
		!(newVal.vt & VT_BYREF))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}
	if (DetachedObjectCount != 0)
	{
		for (unsigned int i=0; i < DetachedObjectCount; i++)
			zFree(DetachedObjectList[i]);
		zFree(DetachedObjectList);
		DetachedObjectCount = 0;
	}

	bstrList = GetBstrArrayFromVariant(newVal, &itemCount);

	if ((bstrList == NULL) || (itemCount == 0))
	{
		DetachedObjectList = NULL;
		DetachedObjectCount = 0;
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	DetachedObjectCount = itemCount;
	DetachedObjectList = (char **) zMalloc(sizeof(char *) * itemCount);
	if (DetachedObjectList == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}
	memset(DetachedObjectList, 0, sizeof(char *) * itemCount);

	for (elementCount =0; elementCount < itemCount; elementCount++)
	{
		DetachedObjectList[elementCount] = (char *)HeapW2A(bstrList[elementCount]);
		SysFreeString(bstrList[elementCount]);
	}
	zFree(bstrList);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_AttachedObjects(VARIANT newVal)
{
	UINT elementCount=0;
	UINT itemCount=0;
	BSTR	*bstrList=NULL;

	EnterObjectLog;
	if ((newVal.vt != VT_BSTR) &&
		(newVal.vt != VT_DISPATCH) &&
		!(newVal.vt & VT_ARRAY) && 
		!(newVal.vt & VT_BYREF))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}
	//if (AttachedObjectCount != 0)
	//{
	//	for (unsigned int i=0; i < AttachedObjectCount; i++)
	//		zFree(AttachedObjectList[i]);
	//	zFree(AttachedObjectList);
	//	AttachedObjectCount = 0;
	//}

	if (AttachedObjectCount != 0)
	{
		for (unsigned int i=0; i < AttachedObjectCount; i++)
			SysFreeString(AttachedObjectList[i]);
		zFree(AttachedObjectList);
		AttachedObjectCount = 0;
	}
	AttachedObjectList = GetBstrArrayFromVariant(newVal, &AttachedObjectCount);

//	bstrList = GetBstrArrayFromVariant(newVal, &itemCount);

	//if ((bstrList == NULL) || (itemCount == 0))
	//{
	//	AttachedObjectList = NULL;
	//	AttachedObjectCount = 0;
	//	setError(SigHandle, INVALID_VARIANT);
	//	return S_FALSE;
	//}

	//AttachedObjectCount = itemCount;
	//AttachedObjectList = (char **) zMalloc(sizeof(char *) * itemCount);
	//if (AttachedObjectList == NULL)
	//{
	//	setError(SigHandle, MEMORY_FAULT);
	//	return S_FALSE;
	//}
	//memset(AttachedObjectList, 0, sizeof(char *) * itemCount);

	//for (elementCount =0; elementCount < itemCount; elementCount++)
	//{
	//	AttachedObjectList[elementCount] = (char *)HeapW2A(bstrList[elementCount]);
	//	SysFreeString(bstrList[elementCount]);
	//}
	//zFree(bstrList);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::ReadAllBase64(BSTR uri, BSTR* base64EncodedData)
{
	BYTE *pbData=NULL;
	DWORD cbData=0;
	BYTE *pbDocument=NULL;		// Object BLOB to sign
	DWORD cbDocument=0;
	CComBSTR ccBstrUri;

	USES_CONVERSION;
	EnterObjectLog;
	ccBstrUri = uri;

	if (ccBstrUri.Length() == 0)
	{
		setError(SigHandle, DEREF_URI_ERROR);
		return S_FALSE;
	}
    
	if (ReadAllBin(uri, &pbDocument, &cbDocument) == S_FALSE)
	{ 
		setError(SigHandle, DEREF_URI_ERROR);
		return S_FALSE;
	}

	//charUri = (char *)HeapW2A(uri);
	//if ((pbDocument = xsDereferenceURI(
	//	(const char *)charUri,// file name or URI
	//	&cbDocument))==NULL) {		// (in/out) size of data
	//		setError(SigHandle, DEREF_URI_ERROR);
	//		zFree(charUri);
	//		return S_FALSE;
	//	}
	//zFree(charUri);
	// Base64 encode
	cbData = base64encodeSize(cbDocument);

	if(!(pbData = (BYTE *)zMalloc(cbData+1)))
	{
		zFree(pbDocument);
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}
	if (base64encode(pbDocument,cbDocument,(unsigned char*)pbData,cbData)==-1) 
	{
		setError(SigHandle, BASE64_ERROR);
		zFree(pbDocument);
		zFree(pbData);
		return S_FALSE;
	}
	*(pbData+cbData)='\0';
	zFree(pbDocument);
	*base64EncodedData = A2WBSTR((LPCSTR)pbData);
	zFree(pbData);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_DecryptionPFXCertFile(BSTR newVal)
{
	EnterObjectLog;
	DecrytionPfxCertFile = newVal;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_DecryptUsingPFXFileCert(BOOL newVal)
{
	EnterObjectLog;
	DecryptUsingPfxFileCert = newVal;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_DecryptionPFXPassword(BSTR newVal)
{
	unsigned char *ptr;
	unsigned int *szPtr;
	unsigned int sizeM;

	EnterObjectLog;
	if (DecrytionPfxPassword.pbData != NULL)
	{
		zFree(DecrytionPfxPassword.pbData);
		DecrytionPfxPassword.pbData = NULL;
	}

	ptr = (unsigned char *)newVal;

	if (ptr != NULL)
	{
		szPtr = (unsigned int *)(ptr - sizeof(int));
		sizeM = *szPtr;

		if (sizeM == 0)
			DecrytionPfxPassword.pbData = NULL;
		else
		{
			sizeM += 2; // BSTR size does not include the terminating null so add 2 to the size
			DecrytionPfxPassword.pbData		= (unsigned char *) zMalloc(sizeM);
			memcpy(DecrytionPfxPassword.pbData, ptr, sizeM);
		}
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_XpathNamespace(VARIANT newVal)
{
	UINT elementCount=0;
	UINT itemCount=0;
	BSTR	*bstrList=NULL;

	EnterObjectLog;
	if ((newVal.vt != VT_BSTR) &&
		(newVal.vt != VT_DISPATCH) &&
		!(newVal.vt & VT_ARRAY) && 
		!(newVal.vt & VT_BYREF))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}
	if (XpathNamespaceCount != 0)
	{
		for (unsigned int i=0; i < XpathNamespaceCount; i++)
			zFree(XpathNamespaceList[i]);
		zFree(XpathNamespaceList);
		XpathNamespaceCount = 0;
	}

	bstrList = GetBstrArrayFromVariant(newVal, &itemCount);

	if ((bstrList == NULL) || (itemCount == 0))
	{
		XpathNamespaceList = NULL;
		XpathNamespaceCount = 0;
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	XpathNamespaceCount = itemCount;
	XpathNamespaceList = (char **) zMalloc(sizeof(char *) * itemCount);
	if (XpathNamespaceList == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}
	memset(XpathNamespaceList, 0, sizeof(char *) * itemCount);

	for (elementCount =0; elementCount < itemCount; elementCount++)
	{
		XpathNamespaceList[elementCount] = (char *)HeapW2A(bstrList[elementCount]);
		SysFreeString(bstrList[elementCount]);
	}
	zFree(bstrList);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_CamServerHost(BSTR* pVal)
{
	EnterObjectLog;
	*pVal = A2WBSTR((LPCSTR)camServerHost);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_CamServerHost(BSTR newVal)
{
	EnterObjectLog;
	if (camServerHost != NULL)
	{
		zFree(camServerHost);
		camServerHost = NULL;
	}
	camServerHost = HeapW2A(newVal);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_CamServerPort(USHORT* pVal)
{
	EnterObjectLog;
    *pVal = camServerPort;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_CamServerPort(USHORT newVal)
{
	EnterObjectLog;
	camServerPort = newVal;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_UseCam(BOOL* pVal)
{
	EnterObjectLog;
	*pVal = useCam;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_UseCam(BOOL newVal)
{
	EnterObjectLog;
	if (useCam) // Already enabled hence do nothing if newVal != 0
	{
		if (newVal == 0)
		{
			if (pCamClient != NULL)
			{
				delete pCamClient;
				pCamClient = NULL;
			}
			useCam = newVal;
			ExitObjectLog;
			return S_OK;
		}
		else
		{
			ExitObjectLog;
			return S_OK;
		}
	}
	else 
		if (newVal)
		{
			put_UseOcsp(FALSE); // Disable OCSP based certificate validation
			pCamClient = new CCAMClient();
			useCam = newVal;
			pCamClient->camServerPortNumber = camServerPort;
		}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_AgencyId(BSTR* pVal)
{
	EnterObjectLog;
	*pVal = A2WBSTR((LPCSTR)agencyId);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_AgencyId(BSTR newVal)
{
	EnterObjectLog;
	USES_CONVERSION;
	char *aNewVal = (char *)HeapW2A(newVal);
	strcpy((char *)agencyId, aNewVal);
	zFree(aNewVal);
	ExitObjectLog;
	return S_OK;
}
BOOL CSignature::crVerifyCertificateUsingCam(BYTE **certificateList, 
								UINT certificateCount,
								LPSYSTEMTIME pSysTime, 
								LPWSTR hKey,
								VERIFICATION_PARAMS *certVerParams,
								PGLOBAL_SIG pg_sig)
{
	BOOL result;
	int status, errorNum;
	DWORD	certBufSize;
	unsigned char *certBufPtr;

	EnterObjectLog;
	result = TRUE;
	certBufSize = base64decodeSize((DWORD)strlen((const char *)certificateList[0]));
	certBufPtr = (unsigned char *) zMalloc (certBufSize+1);
	memset(certBufPtr,0,certBufSize+1);
	if ((certBufSize = base64decode(certificateList[0],(unsigned char *)certBufPtr,certBufSize))==-1)
	{
		setError(SigHandle, MEMORY_FAULT);
		zFree(certBufPtr);
		return FALSE;
	}

	pCamClient->validate(camServerHost, certBufPtr,
							certBufSize, agencyId, &status, 
							&CamResponseAsciiCert, 
							&CamResponseAsciiCertSize,
							&CamResponseCaSignedMsg, 
							&CamResponseCaSignedMsgSize);
	zFree(certBufPtr);
	if (CamResponseAsciiCert !=  NULL) //The response contains ASCII Certificate Information
	{
		char * transIdPtr = strstr((const char *)CamResponseAsciiCert, "TransID: ");
		if (transIdPtr != NULL)
			CamResponseTransactionId = (unsigned char *)(transIdPtr + 9);
		else
			CamResponseTransactionId = NULL;
	}
	if (status != 0)
	{
		result = FALSE;
		switch(status)
		{
			case 1: errorNum = CAM_CERT_REVOKED;
				break;
			case 2: errorNum = CAM_CERT_EXPIRED;
				break;
			case 3: errorNum = CAM_CERT_SUSPENDED;
				break;
			case 4: errorNum = CAM_CERT_FAILED_VERIFICATION;
				break;
			case 5: errorNum = CAM_CERT_ISSUER_NOT_FOUND;
				break;
			case 6: errorNum = CAM_CERT_NOT_PARSABLE;
				break;
			case 7: errorNum = CAM_CA_SYSTEM_BUSY;
				break;
			case 8: errorNum = CAM_CA_TIMEOUT;
				break;
			case 9: errorNum = CAM_CA_CERT_UNKNOWN;
				break;
			case 10: errorNum = CAM_CA_REQ_BAD;
				break;
			case 11: errorNum = CAM_CA_BAD_RESP_SIG;
				break;
			case 0xFF: errorNum = CAM_INTERNAL_ERROR;
				break;
			default: errorNum = CAM_INTERNAL_ERROR;
				break;
		}
		setError(SigHandle, errorNum);
	}
	ExitObjectLog;
	return result;
}
STDMETHODIMP CSignature::get_CamValidationResponse(BSTR* pVal)
{
	EnterObjectLog;
	if (CamResponseCaSignedMsg != NULL)
		*pVal = A2WBSTR((LPCSTR)CamResponseCaSignedMsg, CamResponseCaSignedMsgSize);
	ExitObjectLog;
	return S_OK;
}

BOOL CSignature::crVerifyCertificateUsingOcsp(BYTE **certificateList, 
								UINT certificateCount,
								LPSYSTEMTIME pSysTime, 
								LPWSTR hKey,
								VERIFICATION_PARAMS *certVerParams,
								PGLOBAL_SIG pg_sig)
{
	BOOL result;
	int status;

	EnterObjectLog;

	if (certificateCount < 2)
	{
		setError(pg_sig, CERT_CHAIN_ERROR);
		return FALSE;
	}
#ifdef USE_OCSP
	if (!useOcsp || (pOcspClient == NULL))
	{
		setError(pg_sig, OCSP_ERROR);
		return FALSE;
	}
#endif

	result = TRUE;

#ifdef WIN32
	if (ocspInputNonce.Length() != 0)
		pOcspClient->OcspNonce = _bstr_t(ocspInputNonce);
	else
		pOcspClient->OcspNonce = _bstr_t();

	pOcspClient->CheckCertificate = _bstr_t((const char *)certificateList[0]);
	pOcspClient->IssuerCertificate = _bstr_t((const char *)certificateList[1]);
	//pOcspClient->CheckCertificateFormat = FORMAT_BASE64;
	//pOcspClient->IssuerCertificateFormat = FORMAT_BASE64;
	pOcspClient->SignerPFXCertificate = 	_bstr_t(ocspRequestSignerB64PfxCert);
	pOcspClient->SignerPFXPassword  =		_bstr_t(ocspRequestSignerB64PfxCertPassword);
	pOcspClient->ResponderCAFileName  = _bstr_t(ocspResponseCACertPath);

	if (proxyHost.Length() != 0)
	{
		pOcspClient->proxyHost = _bstr_t(proxyHost);
		pOcspClient->proxyPort = proxyPort;
		pOcspClient->proxyUsername = _bstr_t(proxyUserName);
		pOcspClient->proxyPassword = _bstr_t(proxyPassword);
	}
	else
		pOcspClient->proxyHost = _bstr_t();

	status = pOcspClient->verify(_bstr_t(ocspResponderUrl));

	ocspTextResponse = (BSTR)pOcspClient->TextResponse;
	ocspB64Response = (BSTR)pOcspClient->Base64Response;
	ocspRevocationReason = (BSTR)pOcspClient->RevocationReason;
	ocspRevocationTime = (BSTR)pOcspClient->RevocationTime;
	ocspOutputResponderUrl = (BSTR)pOcspClient->responderUrl;
	ocspOutputNonce = (BSTR)pOcspClient->OcspNonce;
	ocspInputNonce.Empty(); // reset the value for the input Nonce so that it not reused

#elif defined UNIX && USE_OCSP
	if (ocspInputNonce.Length() != 0)
		pOcspClient->SetOcspNonce(nsString((PRUnichar *)((BSTR)ocspInputNonce)));
	else
		pOcspClient->SetOcspNonce(nsString((PRUnichar *)NULL));
	pOcspClient->SetCheckCertificate(nsString((PRUnichar *)((BSTR)CComBSTR((const char *)certificateList[0]))));
	pOcspClient->SetIssuerCertificate(nsString((PRUnichar *)((BSTR)CComBSTR((const char *)certificateList[1]))));
	pOcspClient->SetSignerPFXCertificate(nsString((PRUnichar *)((BSTR)CComBSTR(ocspRequestSignerB64PfxCert))));
	pOcspClient->SetSignerPFXPassword(nsString((PRUnichar *)((BSTR)CComBSTR(ocspRequestSignerB64PfxCertPassword))));
	pOcspClient->SetResponderCAFileName(nsString((PRUnichar *)((BSTR)CComBSTR(ocspResponseCACertPath))));

	if (proxyHost.Length() != 0)
	{
		pOcspClient->SetProxyHost(nsString((PRUnichar *)((BSTR)CComBSTR(proxyHost))));
		pOcspClient->SetProxyPort(proxyPort);
		pOcspClient->SetProxyUsername(nsString((PRUnichar *)((BSTR)CComBSTR(proxyUserName))));
		pOcspClient->SetProxyPassword(nsString((PRUnichar *)((BSTR)CComBSTR(proxyPassword))));
	}
	else
		pOcspClient->SetProxyHost(nsString((PRUnichar *)NULL));

	PRUint16 prStatus;
	pOcspClient->Verify(nsString((PRUnichar *)((BSTR)CComBSTR(ocspResponderUrl))), &prStatus);
	status = prStatus;

	nsString temp;
	pOcspClient->GetTextResponse(temp);
	ocspTextResponse = (BSTR)CComBSTR((LPCOLESTR)temp.get());
	pOcspClient->GetBase64Response(temp);
	ocspB64Response = (BSTR)CComBSTR((LPCOLESTR)temp.get());
	pOcspClient->GetRevocationReason(temp);
	ocspRevocationReason = (BSTR)CComBSTR((LPCOLESTR)temp.get());
	pOcspClient->GetRevocationTime(temp);
	ocspRevocationTime = (BSTR)CComBSTR((LPCOLESTR)temp.get());
	pOcspClient->GetResponderURL(temp);
	ocspOutputResponderUrl = (BSTR)CComBSTR((LPCOLESTR)temp.get());
	pOcspClient->GetOcspNonce(temp);
	ocspOutputNonce = (BSTR)CComBSTR((LPCOLESTR)temp.get());
	ocspInputNonce.Empty(); // reset the value for the input Nonce so that it not reused

#endif

	if ((status & CERT_GOOD) == 0)
	{
		if (status & CERT_UNKNOWN)
            setError(pg_sig, OCSP_CERT_UNKNOWN);
		else if (status & CERT_REVOKED)
			setError(pg_sig, OCSP_CERT_REVOKED);
		else
			setError(pg_sig, OCSP_ERROR);
		result = FALSE;
	}
	else // Certificate validated successfully
	{
		if ((ocspResponseCACertPath.Length() != 0) &&	// The trusted response signer cert is given and 
			((status & RESPONSE_VERIFIED) == 0))		// hence should be enforced
		{
			result = FALSE;
			setError(pg_sig, OCSP_CA_UNTRUSTED);
		}
		else
			result = TRUE;
	}

	ExitObjectLog;
	return result;
}
STDMETHODIMP CSignature::GetSigPropValueByName(LONG sigIndex, BSTR propName, BSTR* propValue)
{
	int maxPropCount=0, propIndex=0;
	unsigned char *charPropName=NULL;
	int nameLength=0;
	WCHAR *equalPtr;

	EnterObjectLog;
	if (sgArr==NULL)
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	if ((sigIndex >= signum) || (sigIndex < 0))
	{
		setError(SigHandle, SIG_INDEX_ERROR);
		return S_FALSE;
	}
	maxPropCount = sgArr[sigIndex]->propNumber;
	for (propIndex = 0; propIndex < maxPropCount; propIndex++)
	{
		BSTR propEntry;
		get_Properties(sigIndex, propIndex, &propEntry);
		equalPtr = wcschr(propEntry, L'=');
		if (equalPtr == NULL) continue;
		*equalPtr = L'\0';
		if (wcscmp((const WCHAR *)propEntry, propName) == 0)
		{
//			equalPtr = wcschr(propEntry, L'=');
			if (*(equalPtr+1) == L' ')
				equalPtr++;
			*propValue = SysAllocString(equalPtr+1);
			SysFreeString(propEntry);
			break;
		}
		SysFreeString(propEntry);
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::Base64DecodeBufferToFile(BSTR encodedBuffer, BSTR outFilePath, BSTR* decodedFilePath)
{
	unsigned char *ptr, *newPtr;
	DWORD sizeM;
	CComBSTR ccBstrFileName, ccBstrEncodedBuffer;
	char TempPath[MAX_PATH];
	FILE *hFile;
	TEMP_FILE_INFO *tmpFilePath = NULL;
	BSTR bstrFileName=NULL;
	BOOL createTempFile = FALSE;
#ifdef WIN32
	const char *FILE_SEP_STR = "\\";
#else
	const char *FILE_SEP_STR = "/";
#endif
	USES_CONVERSION;

	EnterObjectLog;
	ccBstrEncodedBuffer = encodedBuffer;
	if (ccBstrEncodedBuffer.Length() == 0)
	{
		setError(SigHandle, BASE64_ERROR);
		return S_FALSE;
	}
	ptr = HeapW2A(encodedBuffer);
	sizeM = strlen((const char *)ptr);
	sizeM = base64decodeSize(sizeM);
	newPtr = (unsigned char *)zMalloc(sizeM+1);
	if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
	{
		zFree(ptr);
		zFree(newPtr);
		setError(SigHandle, BASE64_ERROR);
		return S_FALSE;
	}
	zFree(ptr);

	ccBstrFileName = outFilePath;

	if ((ccBstrFileName.Length() != 0) && (FileAccessRestricted == TRUE))
	{
		unsigned char *charSecureXMLPath = HeapW2A(SecureXMLPath.m_str);
		string license_file = (char *)charSecureXMLPath;
		license_file += FILE_SEP_STR;
		license_file += SECUREXML_LICENSE_FILENAME;
		zFree(charSecureXMLPath);
		unsigned char *charOutFilePath = HeapW2A(outFilePath);
		int length1 = strlen((const char *)charOutFilePath);
		int length2 = strlen(license_file.c_str());
		if (length1 != length2)
			createTempFile = TRUE;
		else
			if (strnicmp(license_file.c_str(), (const char *)charOutFilePath, length1) == 0)
				createTempFile = FALSE;
			else
				createTempFile = TRUE;
		//if (stricmp(license_file.c_str(), (const char *)charOutFilePath) == 0)
		//	createTempFile = FALSE;
		//else
		//	createTempFile = TRUE;
		zFree(charOutFilePath);
	}

	if ((ccBstrFileName.Length() == 0) || (createTempFile == TRUE))
	{
		// Create temporary file for saving decoded data
		GetTempPath((DWORD)MAX_PATH, TempPath); 
		GetTempFileName(TempPath, // dir. for temp. files 
			"INF",                // temp. file name prefix 
			0,                    // create unique name 
			szTempName);          // buffer for name
		bstrFileName = A2WBSTR((LPCSTR)szTempName);
		tmpFilePath = new (TEMP_FILE_INFO);
		strcpy((char *)tmpFilePath->fileName, szTempName);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
	}
	else
		bstrFileName = SysAllocString(outFilePath);
//		strcpy((char *)szTempName,(const char *)W2A(outFilePath));
	// open file in write mode 
#ifdef WIN32
	if ((hFile = _wfopen(bstrFileName,L"wb"))==NULL) {
#elif UNIX
	unsigned char *utf8FileName = HeapW2A(bstrFileName);
	if ((hFile = fopen((const char *)utf8FileName, "wb")) == NULL) {
			zFree(utf8FileName);
#endif
			setError(SigHandle, IO_ERROR);
			SysFreeString(bstrFileName);
			zFree(newPtr);
			if (tmpFilePath != NULL)
			{
				tmpFileList->remove(tmpFilePath);
			}
			return S_FALSE;
	}
#ifdef UNIX
	zFree(utf8FileName);
#endif

	if (fwrite(newPtr, 1, sizeM, hFile) == 0)
	{
		setError(SigHandle, IO_ERROR);
		zFree(newPtr);
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}
	if (ferror(hFile))
	{
		setError(SigHandle, IO_ERROR);
		zFree(newPtr);
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}
	fclose(hFile);
	zFree(newPtr);
	*decodedFilePath = bstrFileName;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::Base64DecodeFileToFile(BSTR encodedFilePath, BSTR outFilePath, BSTR* decodedFilePath)
{
	BSTR bstrData;
	HRESULT readResult;

	USES_CONVERSION;
	EnterObjectLog;    
	if ((readResult = ReadAll(encodedFilePath,&bstrData)) == S_FALSE)
	{
		return S_FALSE;
	}
	Base64DecodeBufferToFile(bstrData, outFilePath, decodedFilePath);
	SysFreeString(bstrData);
	ExitObjectLog;
	return S_OK;
}

//STDMETHODIMP CSignature::GunZipB64GZippedStr(BSTR b64GZippedStr, BSTR* b64GunZippedStr)
//{
//	unsigned char *ptr;
//	Byte *compr;
//    uLong comprLen;
//    int err;
//    z_stream d_stream; /* decompression stream */
//	uLong uncompressedLength = 0;
//	BufferLinkedList *bufferHead=NULL, *bufferCur=NULL, *bufferPrev=NULL;
//	unsigned char *uncompressedData;
//	int srcSize;
//	unsigned int cbData;
//	unsigned char *pbData;
//
//	if (!LicObj.checkLicense()) {
//		setError(SigHandle, INVALID_SECUREXML_LIC);
//		return S_FALSE;
//	}
//	if (!LicObj.getVerifyAllowed()) {
//		setError(SigHandle, NO_VERIFICATION_LIC);
//		return S_FALSE;
//	}
//
//
//	ptr = HeapW2A(b64GZippedStr);
//	comprLen = strlen((const char *)ptr);
//	comprLen = base64decodeSize(comprLen);
//	compr = (unsigned char *)zMalloc(comprLen+1);
//	if ((comprLen = base64decode(ptr,compr,comprLen+1))==-1)
//	{
//		zFree(ptr);
//		zFree(compr);
//		setError(SigHandle, BASE64_ERROR);
//		return S_FALSE;
//	}
//	zFree(ptr);
//
//	bufferHead = (BufferLinkedList *)zMalloc(sizeof(BufferLinkedList));
//	bufferHead->bufferPtr = (Byte *) zMalloc(GUNZIP_BLOCK_SIZE);
//	bufferHead->bufferSize = GUNZIP_BLOCK_SIZE;
//	bufferHead->next = NULL;
//	bufferCur = bufferHead;
//
//	d_stream.zalloc = (alloc_func)0;
//    d_stream.zfree = (free_func)0;
//    d_stream.opaque = (voidpf)0;
//
//    d_stream.next_in  = compr;
//    d_stream.avail_in = (uInt)comprLen;
//
//    err = inflateInit(&d_stream);
//
//    for (;;) {
//        d_stream.next_out = bufferCur->bufferPtr;
//		d_stream.avail_out = (uInt)bufferCur->bufferSize;
//        err = inflate(&d_stream, Z_NO_FLUSH);
//        if (err == Z_STREAM_END) break;
//		bufferPrev = bufferCur;
//		bufferCur = (BufferLinkedList *)zMalloc(sizeof(BufferLinkedList));
//		bufferPrev->next = bufferCur;
//		bufferCur->bufferSize = GUNZIP_BLOCK_SIZE;
//		bufferCur->bufferPtr = (Byte *) zMalloc(GUNZIP_BLOCK_SIZE);
//		bufferCur->next = NULL;
//    }
//
//    err = inflateEnd(&d_stream);
//
//	uncompressedLength = d_stream.total_out;
//	uncompressedData = (unsigned char *)zMalloc(uncompressedLength);
//
//	// Now lets copy all uncompressed data into this contiguous buffer
//	memcpy((void *)uncompressedData, (const void *)bufferHead->bufferPtr, bufferHead->bufferSize);
//	ptr = uncompressedData + bufferHead->bufferSize;
//	bufferCur = bufferHead->next;
//
//	while (bufferCur)
//	{
//		memcpy(ptr, bufferCur->bufferPtr, bufferCur->bufferSize);
//		ptr += bufferCur->bufferSize;
//		bufferCur = bufferCur->next;
//	}
//	bufferCur = bufferHead;
//	FreeBufferLinkedList(bufferCur);
//
//	srcSize = uncompressedLength;
//	cbData = base64encodeSize(srcSize+1);
//
//	if(!(pbData = (BYTE *)zMalloc(cbData+1)))
//	{
//		zFree(uncompressedData);
//		setError(SigHandle, MEMORY_FAULT);
//		return FALSE;
//	}
//	if ((cbData  = base64encode(uncompressedData,srcSize,(unsigned char*)pbData,cbData+1))==-1) 
//	{
//		setError(SigHandle, BASE64_ERROR);
//		zFree(uncompressedData);
//		zFree(pbData);
//		return FALSE;
//	}
//	*(pbData+cbData)='\0';
//	zFree(uncompressedData);
//	*b64GunZippedStr = A2WBSTR((LPCSTR)pbData);
//
//	return S_OK;
//}

STDMETHODIMP CSignature::GunZipFile(BSTR gZippedFile, BSTR gUnZippedFile, BSTR* gUnZippedFilePath)
{
    Byte *uncompr;
    uLong uncomprLen=GUNZIP_BLOCK_SIZE;
	gzFile file;
	FILE *outFHandle;
	CComBSTR ccBstrFileName;
	char TempPath[MAX_PATH];
	TEMP_FILE_INFO *tmpFilePath = NULL;

	USES_CONVERSION;
	EnterObjectLog;
	if (!LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (!LicObj.getVerifyAllowed()) {
		setError(SigHandle, NO_VERIFICATION_LIC);
		return S_FALSE;
	}

	char *agZippedFile = (char *)HeapW2A(gZippedFile);
	file = gzopen(agZippedFile, "rb");
	zFree(agZippedFile);
    if (file == NULL)
	{
		setError(SigHandle, IO_ERROR);
		return S_FALSE;
	}

	ccBstrFileName = gUnZippedFile;

	if (ccBstrFileName.Length() == 0)
	{
		// Create temporary file for saving decoded data
		GetTempPath((DWORD)MAX_PATH, TempPath); 
		GetTempFileName(TempPath, // dir. for temp. files 
			"INF",                // temp. file name prefix 
			0,                    // create unique name 
			szTempName);          // buffer for name 
		tmpFilePath = new (TEMP_FILE_INFO);
		strcpy((char *)tmpFilePath->fileName, szTempName);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
	}
	else
	{
		char *agUnZippedFile = (char *)HeapW2A(gUnZippedFile);
		strcpy((char *)szTempName, agUnZippedFile);
		zFree(agUnZippedFile);
	}

	outFHandle = fopen((const char*)szTempName, "wb");
	if (outFHandle == NULL)
	{
		setError(SigHandle, IO_ERROR);
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}
	uncompr = (Byte *)zMalloc(GUNZIP_BLOCK_SIZE);
	while (1)
	{
		uncomprLen = gzread(file, uncompr, (unsigned)uncomprLen);
		if (uncomprLen > 0) {
			fwrite(uncompr, 1, uncomprLen,outFHandle);
		}
		else
			break;
	}
	zFree(uncompr);
	fclose(outFHandle);
	gzclose(file);
	*gUnZippedFilePath = A2WBSTR((LPCSTR)szTempName);
	ExitObjectLog;
	return S_OK;
}

void CSignature::FreeBufferLinkedList(BufferLinkedList * listHeadPtr)
{
	BufferLinkedList *cur;
	cur = listHeadPtr;
	if (cur->next == NULL)
	{
		zFree(cur->bufferPtr);
		zFree(cur);
	}
	else
	{
		FreeBufferLinkedList(cur->next);
		cur->next = NULL;
		zFree(cur->bufferPtr);
		zFree(cur);
	}
}
STDMETHODIMP CSignature::get_CertSerialNumberFormat(LONG *pVal)
{
	HRESULT hResult=S_OK;
	EnterObjectLog;
	*pVal = CertSerialNumberFormat;
	ExitObjectLog;
	return hResult;
}

STDMETHODIMP CSignature::put_CertSerialNumberFormat(LONG newVal)
{
	HRESULT hResult=S_OK;
	EnterObjectLog;
	CertSerialNumberFormat = newVal;
	ExitObjectLog;
	return hResult;
}
unsigned char *CSignature::Base64BinToPlainHex(unsigned char *base64Bin)
{
	DWORD dwSizeBuf=0;
	BYTE *buff=NULL;
	char s[30];
	unsigned char *d;
	
	EnterObjectLog;
	if (base64Bin == NULL)
		return NULL;

	dwSizeBuf = base64decodeSize(strlen((const char *)base64Bin));
	buff = (unsigned char *) zMalloc (dwSizeBuf);
	memset(buff,0,dwSizeBuf);
	if ((dwSizeBuf = base64decode(base64Bin,buff,dwSizeBuf))==-1) 
	{	
		if (buff) zFree (buff);		
	}
	
	d = (unsigned char *)zMalloc(256);
	memset(d,0,256);
	for(int j=dwSizeBuf;j>0;j--){
		sprintf(s,"%02x",(int)buff[j-1]);
		strcat((char *)d,s);
		strcat((char *)d," ");
	}
	zFree (buff);
	ExitObjectLog;
	return d;
}

unsigned char HexToUnsignedChar(unsigned char inputVal)
{
	switch (inputVal)
	{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'a': return 10;
		case 'A': return 10;
		case 'b': return 11;
		case 'B': return 11;
		case 'c': return 12;
		case 'C': return 12;
		case 'd': return 13;
		case 'D': return 13;
		case 'e': return 14;
		case 'E': return 14;
		case 'f': return 15;
		case 'F': return 15;
		default: return 0;
	}
}

unsigned char HexStrToUnsignedChar(unsigned char *hexStr)
{
	unsigned char outNum;
	unsigned char unitsVal;
	unsigned char tensVal;

	unitsVal = HexToUnsignedChar(hexStr[1]);
	tensVal = HexToUnsignedChar(hexStr[0]);
	outNum = 16 * tensVal + unitsVal;
	return outNum;
}

unsigned char *CSignature::PlainHexToBase64Bin(unsigned char *plainHex)
{
	DWORD dwSizeBuf=0;
	BYTE *buff=NULL;
	unsigned char s[4];
	unsigned char *d=NULL;
	unsigned int plainHexLen=0, binLen=0;

	EnterObjectLog;
	if (plainHex == NULL)
		return NULL;

	if ((plainHexLen = strlen((const char *)plainHex)) == 0)
		return NULL;

	binLen = (plainHexLen + 1) / 3;

	buff = (BYTE *)zMalloc(binLen);

	for (unsigned int i=0; i<binLen; i++)
	{
		memset(s,0,4);
		memcpy(s, (const void *)(plainHex + (i*3)),2);
		buff[binLen - i -1] = (BYTE)HexStrToUnsignedChar(s);
	}

	dwSizeBuf = base64encodeSize(binLen);
	d = (unsigned char *) zMalloc (dwSizeBuf+1);
	memset(d,0,dwSizeBuf+1);
	if ((dwSizeBuf = base64encode(buff,binLen, d,dwSizeBuf+1))==-1) 
	{	
		if (buff) zFree (buff);
		if (d) zFree (d);
		return NULL;
	}
	zFree (buff);
	ExitObjectLog;
	return d;
}

STDMETHODIMP CSignature::SecureXMLVerifyFileToBuffer(BSTR signedXMLFile, BSTR* verificationResponse)
{
	BSTR signedXML=NULL;
	EnterObjectLog;
	ReadAll(signedXMLFile, &signedXML);
	if (signedXML != NULL)
	{
		SecureXMLVerify(signedXML, verificationResponse);
		SysFreeString(signedXML);
	}
	ExitObjectLog;
	return S_OK;
}
STDMETHODIMP CSignature::SecureXMLVerifyFileToFile(BSTR signedXMLFile, BSTR outFilePath, BSTR* verificationResponseFilePath)
{
	BSTR signedXML=NULL, verificationResponse=NULL;
	EnterObjectLog;
	ReadAll(signedXMLFile, &signedXML);
	if (signedXML != NULL)
	{
		SecureXMLVerify(signedXML, &verificationResponse);
		SysFreeString(signedXML);
		if (verificationResponse != NULL)
		{
			SaveXMLStr(verificationResponse, outFilePath, verificationResponseFilePath);
            SysFreeString(verificationResponse);
		}
	}
	ExitObjectLog;
	return S_OK;
}
STDMETHODIMP CSignature::DeleteSignatureFromXMLStr(BSTR xmlStr, BSTR sigId, BSTR *newSigXMLStr)
{
	xmlDocPtr doc =NULL;
	xmlNodePtr cur=NULL, rootNode=NULL, parent=NULL;
	xmlChar *mem=NULL;
	int iSize;
	xmlXPathContextPtr xpathPtr=NULL;
	xmlXPathObjectPtr xpathResultPtr=NULL;
	unsigned char *ptr, *newPtr=NULL, *curPtr=NULL; 
	unsigned int *szPtr;
	unsigned int sizeM;
	char *charSigId;

	USES_CONVERSION;
	EnterObjectLog;
	BOOL freeNewPtr=FALSE;
	if (Base64DecodeXML == FALSE)
	{
		ptr = (unsigned char *)xmlStr;
		szPtr = (unsigned int *)(ptr - sizeof(int));
		sizeM = (*szPtr);

		if (((*ptr == 0xff) && (*(ptr + 1) == 0xfe)) ||
			((*ptr == 0xfe) && (*(ptr + 1) == 0xff)))
		{
			// There is no need to put the UTF 16 header since the data is already in utf-16 format
			newPtr = ptr;
		}
		else
		{
			newPtr = (unsigned char *)zMalloc(sizeM + 4);
			freeNewPtr = TRUE;

			FileEncoding(newPtr);
//			*newPtr = 0xFF;
//			*(newPtr + 1) = 0xFE;

			memcpy(newPtr+2, ptr, sizeM + 2);
			sizeM += 4;
		}
	}
	else
	{
		ptr = HeapW2A(xmlStr);
		sizeM = strlen((const char *)ptr);
		sizeM = base64decodeSize(sizeM);
		newPtr = (unsigned char *)zMalloc(sizeM+1);
		freeNewPtr = TRUE;
		if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
		{
			zFree(ptr);
			zFree(newPtr);
			setError(SigHandle, BASE64_ERROR);
			return S_FALSE;
		}
		zFree(ptr);
	}

	// original document
	doc = xmlParseMemory((const char *)newPtr,sizeM);
	if (freeNewPtr)
		zFree(newPtr);

	rootNode = xmlDocGetRootElement(doc);
	charSigId = (char *)HeapW2A(sigId);
	xmlNodePtr sigNode = xsSigNodeById((const xmlNodePtr) rootNode, (const xmlChar *)charSigId);
	zFree(charSigId);
	if (sigNode != NULL)
	{
		xmlUnlinkNode(sigNode);
		xmlFreeNode(sigNode);
	}

	xmlChar *newXMLStr;
	xmlDocDumpMemory(doc,&newXMLStr,&iSize);
	xmlFreeDoc(doc);

	if (Base64DecodeXML == TRUE)
	{
	// Base64 encode
		unsigned int cbData;
		unsigned char *pbData;
		cbData = base64encodeSize(iSize+1);

		if(!(pbData = (BYTE *)zMalloc(cbData+1)))
		{
			xmlFree(newXMLStr);
			setError(SigHandle, MEMORY_FAULT);
			return FALSE;
		}
		if ((cbData  = base64encode(newXMLStr,iSize,(unsigned char*)pbData,cbData+1))==-1) 
		{
			setError(SigHandle, BASE64_ERROR);
			xmlFree(newXMLStr);
			zFree(pbData);
			return FALSE;
		}
		*(pbData+cbData)='\0';
		xmlFree(newXMLStr);
		*newSigXMLStr = A2WBSTR((LPCSTR)pbData, (int)cbData);
		zFree(pbData);
	}
	else
	{
		unsigned char *dataPtr = newXMLStr;

		if (((*dataPtr == 0xff) && (*(dataPtr +1) == 0xfe)) ||
			((*dataPtr == 0xfe) && (*(dataPtr +1) == 0xff)))
		{
			// This is a UTF-16 file, so no need to do a char * to BSTR conversion
			// Just allocate memory and copy data and put the size information in front
			*newSigXMLStr = ::SysAllocStringByteLen((LPCSTR)dataPtr, (UINT)iSize);
			xmlFree(dataPtr);
		}
		else
		{
			*newSigXMLStr = A2WBSTR((LPCSTR)dataPtr, iSize);
			xmlFree(dataPtr);
		}
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::DeleteSignatureFromFile(BSTR signedXMLFile, BSTR sigId, BSTR outFilePath, BSTR* newSigFilePath)
{
	BSTR signedXML=NULL, newSigXMLStr=NULL;
	EnterObjectLog;
	ReadAll(signedXMLFile, &signedXML);
	if (signedXML != NULL)
	{
		DeleteSignatureFromXMLStr(signedXML, sigId, &newSigXMLStr);
		SysFreeString(signedXML);
		if (newSigXMLStr != NULL)
		{
			SaveXMLStr(newSigXMLStr, outFilePath, newSigFilePath);
            SysFreeString(newSigXMLStr);
		}
	}
	ExitObjectLog;
	return S_OK;
}
STDMETHODIMP CSignature::put_AllowedCertIssuerNames(VARIANT newVal)
{
	UINT elementCount=0;
	UINT itemCount=0;
	BSTR	*bstrList=NULL;
//	unsigned char  *charIssuerNamePtr;

USES_CONVERSION;
	EnterObjectLog;
	if ((newVal.vt != VT_BSTR) &&
		(newVal.vt != VT_DISPATCH) &&
		!(newVal.vt & VT_ARRAY) && 
		!(newVal.vt & VT_BYREF))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	if (allowedCertIssuerCount != 0)
	{
		for (unsigned int i=0; i < allowedCertIssuerCount; i++)
			SysFreeString(allowedCertIssuerNames[i]);
		zFree(allowedCertIssuerNames);
		allowedCertIssuerCount = 0;
	}

	bstrList = GetBstrArrayFromVariant(newVal, &itemCount);

	if ((bstrList == NULL) || (itemCount == 0))
	{
		allowedCertIssuerNames = NULL;
		allowedCertIssuerCount = 0;
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	allowedCertIssuerCount = itemCount;
	allowedCertIssuerNames = bstrList;

	//free cV and SigHandle
	//if ((UsingNetscape == FALSE) || (allowedCertIssuerCount != 0))
		if (cV != NULL)
		{
			for (int i=0; i<CertificateCount; i++)
			{
				if (cV[i]->certificate != NULL)
					zFree(cV[i]->certificate);
				zFree(cV[i]);
			}
			zFree(cV);
			cV = NULL;
		}
#ifdef WIN32
	//free showselect cert obj
	if (CertificateCount != 0)
		delete dlg;
#endif
	//do all initialization
	int numCerts;
	PCERT_DESCR *certPtr;

	sgArr=NULL;
	err=0;
	signum=0;
	uriArr=NULL;
	failedUriArr=NULL;
	failedUriCount=0;
	totalUriCount = 0;

	CertificateCount = 0;
	CurrentCertificate = NOT_INITIALIZED;

	unsigned char * tmpCharPtr = HeapW2A(StoreName.m_str);
	if (strcmp((const char *)tmpCharPtr, NETSCAPESTORE))
	{
#ifdef WIN32
		// Store name is not Netscape
		if ((UsingNetscape == TRUE) && (nsCertStoreObj != NULL))
		{
			nsCertStoreObj->Release();
			CoUninitialize();
		}
#endif
		UsingNetscape = FALSE;

#ifdef NSS
		if ((certPtr = axGetCertificateList(tmpCharPtr, &numCerts, SigHandle )) != NULL)
#else
		if ((certPtr = axGetCertificateList(tmpCharPtr, &numCerts )) != NULL)
#endif
		{
			CertificateCount = (long) numCerts;
			if (numCerts > 0)
				cVSigner = certPtr;
			else
			{
				cVSigner = NULL;
			}
		}
	}
	else // The store name is Netscape hence do the netscape cert processing
	{
		IUnknown *pUnknown;
#ifdef WIN32
		if ((UsingNetscape == TRUE) && (nsCertStoreObj != NULL))
		{
			nsCertStoreObj->Release();
			CoUninitialize();
		}

		CoInitialize(NULL);
		HRESULT hr = CoCreateInstance(__uuidof(CCertStore), NULL, CLSCTX_LOCAL_SERVER, 
							IID_IUnknown, (void **) &pUnknown);
		if (FAILED(hr))
		{
			UsingNetscape = FALSE;
			return S_FALSE;
		}

		hr = pUnknown->QueryInterface(__uuidof(ICertStore), (void **) &nsCertStoreObj);
		if (FAILED(hr))
		{
			pUnknown->Release();
			UsingNetscape = FALSE;
			return S_FALSE;
		}
		pUnknown->Release();
		nsCertStoreObj->NetscapeStorePassword = nsStorePassword;
		BSTR bstrCertListXml = (BSTR) nsCertStoreObj->GetCertificateList((unsigned long *)&numCerts);
		CertificateCount = (long) numCerts;
		if (numCerts > 0)
		{
			//CBufferVariant m_binaryData;
			UsingNetscape = TRUE;
			PCERT_DESCR *certList = (PCERT_DESCR *)zMalloc(CertificateCount * sizeof(PCERT_DESCR));
			unsigned char *certListXml = HeapW2A(bstrCertListXml);
			xmlDocPtr doc = xmlParseMemory((const char *)certListXml, strlen((const char *)certListXml));
			xmlNodePtr root = xmlDocGetRootElement(doc);
			xmlNodePtr cur = root->xmlChildrenNode;
			xmlNodePtr parent = cur;
			int certIndex = 0;
			while ((cur) && (certIndex < CertificateCount))
			{
				if (!(xmlStrcmp(cur->name, (const xmlChar *) "Certificate"))) {
					PCERT_DESCR certDescPtr = (PCERT_DESCR)zMalloc(sizeof(CERT_DESCR));
					certList[certIndex++] = certDescPtr;
					// content
					parent = cur;
					cur = cur->children;
					for (;cur != NULL; cur = cur->next)
					{
						if (!(xmlStrcmp(cur->name, (const xmlChar *)"SerialNumber")))
						{
							char *serialNumber = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
							strcpy((char *)certDescPtr->serialNumber, (const char *)serialNumber);
							xmlFree(serialNumber);
						}
						if (!(xmlStrcmp(cur->name, (const xmlChar *)"Issuer")))
						{
							char *issuer = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
							BSTR bstrIssuer = (BSTR)zMalloc(512*2);
							memset(bstrIssuer, 0, 512*2);
							MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)issuer, strlen((const char *)issuer), bstrIssuer, 512);
							StringCbCopyW(certDescPtr->issuer, 512, bstrIssuer);
							xmlFree(issuer);
							zFree(bstrIssuer);
						}
						if (!(xmlStrcmp(cur->name, (const xmlChar *)"Subject")))
						{
							char *subject = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
							BSTR bstrSubject = (BSTR)zMalloc(512*2);
							memset(bstrSubject, 0, 512*2);
							MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)subject, strlen((const char *)subject), bstrSubject, 512);
							StringCbCopyW(certDescPtr->subject, 512, bstrSubject);
							xmlFree(subject);
							zFree(bstrSubject);
						}
						if (!(xmlStrcmp(cur->name, (const xmlChar *)"ShortSubject")))
						{
							char *shortSubject = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
							BSTR bstrShortSubject = (BSTR)zMalloc(512*2);
							memset(bstrShortSubject, 0, 512*2);
							MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)shortSubject, strlen((const char *)shortSubject), bstrShortSubject, 512);
							StringCbCopyW(certDescPtr->shortSubject, 512, bstrShortSubject);
							xmlFree(shortSubject);
							zFree(bstrShortSubject);
						}
						if (!(xmlStrcmp(cur->name, (const xmlChar *)"NotAfter")))
						{
							char *notAfter = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
							strcpy((char *)certDescPtr->notAfter, (const char *)notAfter);
							xmlFree(notAfter);
						}
						if (!(xmlStrcmp(cur->name, (const xmlChar *)"X509Certificate")))
						{
							char *x509Certificate = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
							certDescPtr->certificate = (unsigned char *)zMalloc(strlen((const char *)x509Certificate) + 1);
							strcpy((char *)certDescPtr->certificate, (const char *)x509Certificate);
							xmlFree(x509Certificate);
						}
					}
				}
				cur = parent->next;
				parent = cur;
			}
			cVSigner = (PCERT_DESCR *)certList;
		}
		else
		{
			UsingNetscape = FALSE;
			cVSigner = NULL;
			nsCertStoreObj->Release();
			CoUninitialize();
		}
#endif
	}
	if ((allowedCertIssuerCount != 0) && (CertificateCount != 0))
	{
		int *indexArray = (int *)zMalloc(sizeof(int) * CertificateCount);
		int allowedCertCount = 0;

		for (unsigned int i=0; i < allowedCertIssuerCount; i++)
		{
			for(int j=0; j < CertificateCount; j++)
			{
				if (!wcscmp((const WCHAR *)allowedCertIssuerNames[i], (const WCHAR *)cVSigner[j]->issuer))
				{
					indexArray[allowedCertCount] = j;
					allowedCertCount++;
				}
			}
		}
		for (int i=0; i<CertificateCount; i++)
		{
			BOOL certificateAllowed = FALSE;
			for (int j=0; j<allowedCertCount; j++)
			{
				if (indexArray[j] == i)
				{
					certificateAllowed = TRUE;
					break;
				}
			}
//			if ((certificateAllowed == FALSE) && (UsingNetscape == FALSE))
			if (certificateAllowed == FALSE) // && (UsingNetscape == FALSE))
			{
				if (cVSigner[i]->certificate != NULL)
					zFree(cVSigner[i]->certificate);
				zFree(cVSigner[i]);
			}
		}
		CertificateCount = allowedCertCount;
		cV = (PCERT_DESCR *)zMalloc(sizeof(PCERT_DESCR *) * CertificateCount);
		for (int i=0; i<CertificateCount; i++)
			cV[i] = cVSigner[indexArray[i]];
//		if (UsingNetscape == FALSE)
			zFree(cVSigner);
		zFree(indexArray);
	}
	else
		cV = cVSigner;
#ifdef WIN32
	// initialise SelectCert
	if (CertificateCount != 0)
	{
		dlg = new CShowSelectCert(/*this,*/ tmpCharPtr, cV, CertificateCount);	
//		dlg->Create(NULL);
	}
#endif
	zFree(tmpCharPtr);
	ExitObjectLog;
	return S_OK;
}
STDMETHODIMP CSignature::get_CRLCacheDbConnectionString(BSTR* pVal)
{
	EnterObjectLog;
#ifdef WIN32
	*pVal = CRLCacheDbConnectionString.Copy();
#endif
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_CRLCacheDbConnectionString(BSTR newVal)
{
	EnterObjectLog;
#ifdef WIN32
	CRLCacheDbConnectionString = newVal;
#endif
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_UseCRLCache(BOOL* pVal)
{
	EnterObjectLog;
#ifdef WIN32
	if (CertVerifyParams.pCrlCache != NULL)
		*pVal = TRUE;
	else
		*pVal = FALSE;
#endif
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_UseCRLCache(BOOL newVal)
{
	EnterObjectLog;
#ifdef WIN32
	if (CertVerifyParams.pCrlCache != NULL)
	{
		delete CertVerifyParams.pCrlCache;
		if (newVal == FALSE)
		{
			CertVerifyParams.pCrlCache = NULL;
		}
		else
		{
			CertVerifyParams.pCrlCache = new CRLCache(CRLCacheDbConnectionString.m_str, SigHandle);
			CertVerifyParams.pCrlCache->SetCRLTimeOut(crlCacheTimeoutInMinutes);
		}
	}
	else
		if (newVal != FALSE)
		{
			CertVerifyParams.pCrlCache = new CRLCache(CRLCacheDbConnectionString.m_str, SigHandle);
			CertVerifyParams.pCrlCache->SetCRLTimeOut(crlCacheTimeoutInMinutes);
		}
#endif
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_CRLCacheTimeoutInMinutes(long newVal)
{
#ifdef WIN32
	crlCacheTimeoutInMinutes = newVal;
	EnterObjectLog;
	if (CertVerifyParams.pCrlCache != NULL)
		CertVerifyParams.pCrlCache->SetCRLTimeOut(newVal);
	ExitObjectLog;
#endif
	return S_OK;
}

STDMETHODIMP CSignature::put_CanonicalizationMethod(long newVal)
{
	EnterObjectLog;
	CanonicalizationMethod = newVal;
	if (newVal>1) {
		SigHandle->useFastC14N = 0;
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_NetscapeStorePassword(BSTR* pVal)
{
	EnterObjectLog;
	*pVal = SysAllocString(nsStorePassword);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_NetscapeStorePassword(BSTR newVal)
{
	EnterObjectLog;
	nsStorePassword = SysAllocString(newVal);
#ifdef NSS
	unsigned char *nsp = (unsigned char *)HeapW2A(nsStorePassword);
	if (!nsp) {
		nsp = (unsigned char *)zMalloc(sizeof(char));
		*nsp = '\0';
	}
	if (SigHandle->certStorePassword) {
		zFree(SigHandle->certStorePassword);
	}
	SigHandle->certStorePassword = nsp;
#endif
	ExitObjectLog;
	return S_OK;
}

#ifdef WIN32
STDMETHODIMP CSignature::SetActivePEMFileCert(BSTR pemFileName, BSTR pemPassword, BSTR* pemX509Cert)
{
	IUnknown *pUnknown;
	IPemObject *pemObject;
	BSTR bstrPfxFileName;

	USES_CONVERSION;
	EnterObjectLog;
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(__uuidof(CPemObject), NULL, CLSCTX_INPROC_SERVER, 
						IID_IUnknown, (void **) &pUnknown);
	if (FAILED(hr))
	{
		CoUninitialize();
		return S_FALSE;
	}

	hr = pUnknown->QueryInterface(__uuidof(IPemObject), (void **) &pemObject);
	if (FAILED(hr))
	{
		pUnknown->Release();
		CoUninitialize();
		return S_FALSE;
	}
	pUnknown->Release();

	bstrPfxFileName = pemObject->CovertToPFX(pemFileName, pemPassword);
	pemObject->Release();
	CoUninitialize();

	if (bstrPfxFileName == NULL)
	{
		setError(SigHandle, PFX_BAD_PASSWORD);
		return S_FALSE;
	}
	SetActivePFXFileCert(bstrPfxFileName, pemPassword, pemX509Cert);
	unsigned char *abstrPfxFileName = HeapW2A(bstrPfxFileName);
#ifdef WIN32
	DeleteFile((LPCTSTR)(abstrPfxFileName));
#else
	unlink(abstrPfxFileName);
#endif
	zFree(abstrPfxFileName);
	ExitObjectLog;
	return S_OK;
}
#endif

STDMETHODIMP CSignature::get_SecureXMLPath(BSTR* pVal)
{
	EnterObjectLog;
	*pVal = SecureXMLPath.Copy();
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_SignedDocumentCount(LONG sigIndex, LONG* pVal)
{
	*pVal = 0;
	EnterObjectLog;
	if (sgArr==NULL)
	{
		setError(SigHandle, NO_SIGNATURE_DATA);
		return S_FALSE;
	}
	if ((sigIndex >= signum) || (sigIndex < 0))
	{
		setError(SigHandle, SIG_INDEX_ERROR);
		return S_FALSE;
	}
	*pVal = sgArr[sigIndex]->refNumber;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::SignXMLByteArray(VARIANT xmlByteArray, BSTR signatureId, VARIANT* signedXmlByteArray)
{
	char *charSigId=NULL, *curCharSigId=NULL;
	unsigned char *charSignedXMLStr=NULL;
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL, parent=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlChar *mem=NULL;
	int iSize=0;
	CComBSTR	sigId;
	CComBSTR tmpXmlStr;
	unsigned char *newPtr=NULL;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	BOOL templateFound=FALSE;
	CBufferVariant m_binaryData;
	VARIANT *inputByteArray;
#ifdef LOGGING
	char buffer[200];
#endif

	EnterObjectLog;
	if (xmlByteArray.vt == (VT_VARIANT | VT_BYREF))
	{
		inputByteArray = xmlByteArray.pvarVal;
	}
	else
		inputByteArray = &xmlByteArray;

	if (inputByteArray->vt != (VT_ARRAY | VT_UI1))
	{
		setError(SigHandle, INVALID_VARIANT);
		m_binaryData.SetLength(0);
		*signedXmlByteArray = m_binaryData.Copy();
		return S_FALSE;
	}
	//if (! LicObj.checkLicense()) {
	//	setError(SigHandle, INVALID_SECUREXML_LIC);
	//	m_binaryData.SetLength(0);
	//	*signedXmlByteArray = m_binaryData.Copy();
	//	return S_FALSE;
	//}
#ifdef LOGGING
	sprintf((char *)buffer, "Variant type = %x", xmlByteArray.vt);
	DebugLog((const char *)buffer);
#endif

	m_binaryData = xmlByteArray;

#ifdef LOGGING
	sprintf((char *)buffer, "CBufferVariant size = %d", m_binaryData.GetLength());
	DebugLog((const char *)buffer);
#endif

	if (! LicObj.getSignAllowed()) 
	{
		if (!LicObj.getFormSignAllowed((unsigned char *)((void *)m_binaryData), m_binaryData.GetLength(), SigHandle))
		{
			setError(SigHandle, NO_SIGNING_LIC);
			m_binaryData.SetLength(0);
			*signedXmlByteArray = m_binaryData.Copy();
			return S_FALSE;
		}
	}
	// original document
	doc = xmlParseMemory((const char *)((void *)m_binaryData), m_binaryData.GetLength());
	if (!doc) 
	{
		setError(SigHandle, XML_PARSER_ERROR);
		m_binaryData.SetLength(0);
		*signedXmlByteArray = m_binaryData.Copy();
		return S_FALSE;
	}

	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	USES_CONVERSION;


	BOOL freeCharSigId = FALSE;
	sigId = signatureId;
	if (sigId.Length() == 0)
		charSigId = NULL;
	else
	{
		charSigId = (char *)HeapW2A(signatureId);
		freeCharSigId = TRUE;
	}

	if (charSigId == NULL)
		if (SignatureID.Length() == 0)
		{
//#ifdef WIN32
//			CoCreateGuid(&sigGuid);
//			GuidToString(&sigGuid, guidStr);
//#else
//			uuid_generate(sigGuid);
//			uuid_unparse(sigGuid, guidStr);
//#endif
//			charSigId = guidStr;
		}
		else
		{
			charSigId = (char *)HeapW2A(SignatureID.m_str);
			freeCharSigId = TRUE;
		}

	root = xmlDocGetRootElement(doc);
	if (charSigId != NULL)
		sigNode = xsSigNodeById((const xmlNodePtr) root, (const xmlChar *)charSigId);
	else
		sigNode = xsSigNodeWithNoIdNoSigValue((const xmlNodePtr) root);
	if (sigNode != NULL)
	{
		templateFound = TRUE;
		cur = sigNode->xmlChildrenNode;
		while (cur)
		{
				if (!(xmlStrcmp(cur->name, (const xmlChar *) "SignedInfo")))
				{
					signedInfoNode = cur;
					break;
				}
				cur = cur->next;
		}  // end while cur != NULL
	}
	  if (templateFound == FALSE) // A Signature element with matching Id was not found
	  {
		  // Add a new Signature element

		/*
		* Signature
		*/

		cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
		sigNode = cur;
		if (charSigId != NULL)
			xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
		cur = xmlAddChild(root,cur);

		xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
		parent = cur;

		/*
		* SignedInfo
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
		signedInfoNode = cur;
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		 * Canonicalization Method
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
		switch(CanonicalizationMethod)
		{
			case WITH_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
				break;
			case WITHOUT_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
				break;
			case EXC_WITH_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
				break;
			case EXC_WITHOUT_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
				break;
			default:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
		}
		cur = xmlAddChild(parent,cur);
		/*
		* Reference
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
		cur = xmlAddChild(parent,cur);
		xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)"");
		parent = cur;

		/*
		* Transforms
		*/
	
		cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		* Transform
		*/
		if ((CanonicalizationMethod == EXC_WITH_COMMENTS) ||
			(CanonicalizationMethod == EXC_WITHOUT_COMMENTS))
		{
			cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			}
			cur = xmlAddChild(parent,cur);
			parent = cur;
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_WITH_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_NO_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			cur = xmlAddChild(parent,cur);
			parent = parent->parent;
		}
		/*
		* Transform
		*/

		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_ENVELOPED_SIG);
		cur = xmlAddChild(parent,cur);		
	  }

#ifdef WIN32
	  if (AddWindowImageFlag == TRUE)
		  AddWindowImage(sigNode, signedInfoNode, charSigId);

	  if (PhysicalSigUsage != NO_PHYSICAL_SIG)		  
		  AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif
	/*
	 * init Signature. crBlob contains XML - envelope document
	 */
	short tmpEnvFlag = EnvelopingFlag;
	EnvelopingFlag = ENVELOPED;

	if (!(CreateSigFromTmplBlob(
								doc,
								charSigId, &charSignedXMLStr, &iSize)))
	{
		if (charSignedXMLStr != NULL)
		{
			xmlFree(charSignedXMLStr);
		}
		EnvelopingFlag = tmpEnvFlag;
		m_binaryData.SetLength(0);
		*signedXmlByteArray = m_binaryData.Copy();
		if (freeCharSigId)
			zFree(charSigId);
		return S_FALSE;
	}
	else
	{
		if (charSignedXMLStr != NULL)
		{
#ifdef WIN32
			m_binaryData.AssignData((const void *)charSignedXMLStr, (long) iSize);
			*signedXmlByteArray = m_binaryData.Copy();
#else		
			VARIANT v;
			VariantInit(&v);
			*signedXmlByteArray = v;
			VariantFromByteArray(signedXmlByteArray,(const char *)charSignedXMLStr, (long) iSize);
#endif
			if (Base64EncodeXML == TRUE)
				zFree(charSignedXMLStr);
			else
				xmlFree(charSignedXMLStr);
		}
	}
	EnvelopingFlag = tmpEnvFlag;
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::SaveXMLByteArray(VARIANT inputXmlByteArray, BSTR fileName, BSTR* path)
{
	FILE *hInFile; 
	BOOL writeResult;
	CComBSTR ccBstrFileName;
	BSTR bstrFileName;
	char TempPath[MAX_PATH];
	CComBSTR tmpXmlStr;
	BOOL freeMemory=FALSE;
	CBufferVariant m_binaryData;
	VARIANT *inputByteArray;
	TEMP_FILE_INFO *tmpFilePath = NULL;
#ifdef LOGGING
	char buffer[200];
#endif

	EnterObjectLog;
	*path = A2WBSTR((const char *) NULL);

	if (inputXmlByteArray.vt == (VT_VARIANT | VT_BYREF))
	{
		inputByteArray = inputXmlByteArray.pvarVal;
	}
	else
		inputByteArray = &inputXmlByteArray;

	if (inputByteArray->vt != (VT_ARRAY | VT_UI1))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}
	m_binaryData = inputXmlByteArray;
#ifdef LOGGING
	sprintf((char *)buffer, "Variant type = %x", inputXmlByteArray.vt);
	DebugLog((const char *)buffer);
#endif

	USES_CONVERSION;
	ccBstrFileName = fileName;

	if ((ccBstrFileName.Length() == 0) || (FileAccessRestricted == TRUE))
	{
		// Create temporary file for saving input XML String
		GetTempPath((DWORD)MAX_PATH, TempPath); 
		GetTempFileName(TempPath, // dir. for temp. files 
			"INF",                // temp. file name prefix 
			0,                    // create unique name 
			szTempName);          // buffer for name 
		bstrFileName = A2WBSTR(szTempName);
		tmpFilePath = new (TEMP_FILE_INFO);
		strcpy((char *)tmpFilePath->fileName, szTempName);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
	}
	else
		bstrFileName = SysAllocString(fileName);

	// open file in write mode 
#ifdef WIN32
	if ((hInFile = _wfopen(bstrFileName,L"wb"))==NULL) {
#elif UNIX
	unsigned char *utf8FileName = HeapW2A(bstrFileName);
	if ((hInFile = fopen((const char *)utf8FileName, "wb")) == NULL) {
			zFree(utf8FileName);
#endif
			setError(SigHandle, IO_ERROR);
			SysFreeString(bstrFileName);
			DebugLog("Could not create file");
			if (tmpFilePath != NULL)
			{
				tmpFileList->remove(tmpFilePath);
			}
			return S_FALSE;
	}
#ifdef UNIX
	zFree(utf8FileName);
#endif
#ifdef LOGGING
	sprintf((char *)buffer, "file %ws file size = %d", fileName, m_binaryData.GetLength());
	DebugLog((const char *)buffer);
#endif
	if ((writeResult = fwrite((const void *)m_binaryData, m_binaryData.GetLength(), 1, hInFile)) == 0)
	{
		setError(SigHandle, IO_ERROR);
		DebugLog("Could not write to file");
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}
	if (ferror(hInFile))
	{
		setError(SigHandle, IO_ERROR);
		DebugLog("Could not write to file");
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}

	fclose(hInFile);
	//tmpXmlStr = bstrFileName;
	//*path = tmpXmlStr.Copy();
	*path = bstrFileName;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::ReadAllByteArray(BSTR fileName, VARIANT* fileDataByteArray)
{
	unsigned char *dataPtr;
	CBufferVariant m_binaryData;
	DWORD	dwFileSize;
#ifdef LOGGING
	char buffer[200];
#endif

	USES_CONVERSION;
	EnterObjectLog;

	//charFileName = HeapW2A(fileName);
	//if ((charFileName == NULL) || (strlen((const char *)charFileName) == 0))
	//{
	//	setError(SigHandle, DEREF_URI_ERROR);
	//	zFree(charFileName);
	//	return S_FALSE;
	//}

	//dataPtr = xsDereferenceURI((URI)charFileName, &dwFileSize);
	if (ReadAllBin(fileName, &dataPtr, &dwFileSize) == S_FALSE)
	{
		setError(SigHandle, FILE_NOT_FOUND);
		m_binaryData.SetLength(0);
		*fileDataByteArray = m_binaryData.Copy();
//		zFree(charFileName);
		return S_FALSE;
	}
#ifdef LOGGING
	sprintf((char *)buffer, "file %ws file size = %d", fileName, dwFileSize);
	DebugLog((const char *)buffer);
#endif

#ifdef WIN32
	m_binaryData.AssignData((const void *)dataPtr, (long) dwFileSize);
	*fileDataByteArray = m_binaryData.Copy();
#else		
	VARIANT v;
	VariantInit(&v);
	*fileDataByteArray = v;
	VariantFromByteArray(fileDataByteArray,(const char *)dataPtr, (long) dwFileSize);
#endif

#ifdef LOGGING
	sprintf((char *)buffer, "Variant type = %x", fileDataByteArray->vt);
	DebugLog((const char *)buffer);
#endif
	zFree(dataPtr);
//	zFree(charFileName);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::VerifyXMLByteArray(VARIANT signedXmlByteArray, BOOL * sigStatus)
{
	CBufferVariant m_binaryData;
	VARIANT *inputByteArray;
	long certStatus=FALSE;
#ifdef LOGGING
	char buffer[200];
#endif

	EnterObjectLog;
	if (signedXmlByteArray.vt == (VT_VARIANT | VT_BYREF))
	{
		inputByteArray = signedXmlByteArray.pvarVal;
	}
	else
		inputByteArray = &signedXmlByteArray;

	if (inputByteArray->vt != (VT_ARRAY | VT_UI1))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}
#ifdef LOGGING
	sprintf((char *)buffer, "Variant type = %x", signedXmlByteArray.vt);
	DebugLog((const char *)buffer);
#endif
	m_binaryData = signedXmlByteArray;
	*sigStatus = TRUE;

	if (uriArr != NULL)
	{
		SigHandle->locArray = uriArr;
		SigHandle->locNumber = totalUriCount;
	}

	if (HMACKey.Length() == 0)
		*sigStatus = (BOOL) axVerify((const unsigned char *)m_binaryData, m_binaryData.GetLength(), NULL, IgnoreIncompleteSignature, SigIndexToVerify, DetailedVerificationReportFlag, SigHandle);
	else
	{
		/*
		 * This might not work on Windows 95/98
		 */
		xsCoreSetCSP((unsigned char *)"Microsoft Enhanced Cryptographic Provider v1.0",SigHandle);
		*sigStatus = (BOOL) axVerify((const unsigned char *)m_binaryData, m_binaryData.GetLength(), &HMACPassword, IgnoreIncompleteSignature, SigIndexToVerify, DetailedVerificationReportFlag, SigHandle);
	}

	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	//if (DetailedVerificationReportFlag)
	//	FetchSignatureStatus(*sigStatus);
	//else
	//	sgArr = axGetSignature(&signum, SigHandle); // Get the full signature stats
	FetchSignatureStatus(*sigStatus, DetailedVerificationReportFlag);

	if ((*sigStatus != FALSE)&&(CertVerifyParams.verificationOptions))
	{
		for (int i=0; i<signum; i++) // For each signature in the document
		{
			// certificate is present in the signature, validate it
			if (sgArr[i]->certificatesCount != 0)
			{
				get_SigCertStatus(i, NULL, 0, &certStatus);
				if (certStatus != 0)
				{
					// Add signature status value of failed
					*sigStatus = FALSE;
					sgArr[i]->status = FALSE;
					break;
				}
			}
		}
	}

	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::SecureXMLVerifyByteArray(VARIANT signedXmlByteArray, VARIANT* verificationResponseByteArray)
{
	CBufferVariant m_binaryData;
	VARIANT *inputByteArray;
	long certStatus=FALSE;
	int i,j,refNum=0, totalLocNum=0, failedLocNum=0;
	PURI_STATUS *refArr=NULL;
	PURI_PATH uriPath=NULL;
	long sigStatus;
	xmlDocPtr doc= NULL;
	xmlNodePtr cur=NULL, rootNode=NULL, parent=NULL, commNode=NULL;
	xmlNsPtr curNs=NULL;
	xmlChar *mem=NULL;
	xmlDtdPtr dtd=NULL;
	int iSize=0;
	char buffer[200];
	unsigned char *pbData=NULL, *pbDocument=NULL, *plainTextHex=NULL;

	USES_CONVERSION;

	EnterObjectLog;
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		m_binaryData = "<?xml version=\"1.0\" ?>\n<Error>Invalid SecureXML License</Error>";
		*verificationResponseByteArray = m_binaryData.Copy();
		return S_FALSE;
	}
	if (!LicObj.getVerifyAllowed()) {
		setError(SigHandle, NO_VERIFICATION_LIC);
		m_binaryData = "<?xml version=\"1.0\" ?>\n<Error>No SecureXML Verification License</Error>";
		*verificationResponseByteArray = m_binaryData.Copy();
		return S_FALSE;
	}

	if (signedXmlByteArray.vt == (VT_VARIANT | VT_BYREF))
	{
		inputByteArray = signedXmlByteArray.pvarVal;
	}
	else
		inputByteArray = &signedXmlByteArray;

	if (inputByteArray->vt != (VT_ARRAY | VT_UI1))
	{
		setError(SigHandle, INVALID_VARIANT);
		m_binaryData.SetLength(0);
		*verificationResponseByteArray = m_binaryData.Copy();
		return S_FALSE;
	}
#ifdef LOGGING
	sprintf((char *)buffer, "Variant type = %x", signedXmlByteArray.vt);
	DebugLog((const char *)buffer);
#endif
	m_binaryData = signedXmlByteArray;
	sigStatus = TRUE;

	SigHandle->locArray = uriArr;
	SigHandle->locNumber = totalUriCount;


	if (HMACKey.Length() == 0)
		sigStatus = (BOOL) axVerify((const unsigned char *)m_binaryData, m_binaryData.GetLength(), NULL, IgnoreIncompleteSignature, SigIndexToVerify, DetailedVerificationReportFlag, SigHandle);
	else
	{
		/*
		 * This might not work on Windows 95/98
		 */
		xsCoreSetCSP((unsigned char *)"Microsoft Enhanced Cryptographic Provider v1.0",SigHandle);
		sigStatus = (BOOL) axVerify((const unsigned char *)m_binaryData, m_binaryData.GetLength(), &HMACPassword, IgnoreIncompleteSignature, SigIndexToVerify, DetailedVerificationReportFlag, SigHandle);
	}

	//if (DetailedVerificationReportFlag == TRUE)
	//	FetchSignatureStatus(sigStatus);
	//else
	//	sgArr = axGetSignature(&signum, SigHandle); // Get the full signature stats
	FetchSignatureStatus(sigStatus, DetailedVerificationReportFlag);

	doc = xmlNewDoc((const unsigned char *)"1.0");
	// document, namespace, element name, element content
	cur = xmlNewDocNode(doc,NULL,(const unsigned char *)"XMLSignatureVerificationResponse",NULL);

	// if you want any namespace definition here
	curNs = xmlNewNs(cur,(const unsigned char *)"http://www.infomosaic.net/XMLSign/VerifyResponse/DTD.htm",NULL/*(const unsigned char *)"infomosaic"*/);
	//xmlSetNs(cur,curNs);

	// add root element
	xmlDocSetRootElement(doc,cur);
	rootNode = cur;

	// add some comment
	commNode = xmlNewDocComment(doc,(const unsigned char *)"1.2 Verified by Infomosaic SecureXML http://www.infomosaic.net");
	cur = xmlAddChild(rootNode,commNode);
	/*
	 * SignatureCount
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"SignatureCount"); // Using the parent element's name space
	cur = xmlAddChild(rootNode,cur);
	itoa(signum, (char *)buffer, 10);
	xmlNodeSetContent(cur,(const unsigned char *)buffer);

	if (signum == 0) // No signature was found or XML error
	{
		/*
		* SignatureStatus
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"SignatureStatus"); // Using the parent element's name space
		cur = xmlAddChild(rootNode,cur);

		/*
		* subnodes of SignatureStatus
		*/
		parent = cur;
		cur = xmlNewNode(NULL,(const unsigned char *)"SignatureId");
		cur = xmlAddChild(parent,cur);
		cur = xmlNewNode(NULL,(const unsigned char *)"SignatureAlgorithm");
		cur = xmlAddChild(parent,cur);	
		cur = xmlNewNode(NULL,(const unsigned char *)"Status");
		// Add signature status value of failed
		itoa(FALSE, (char *)buffer, 10);
		xmlNodeSetContent(cur,(const unsigned char *)buffer);
		cur = xmlAddChild(parent,cur);

		cur = xmlNewNode(NULL,(const unsigned char *)"LastError");
		// Add last error code
		itoa(axGetLastError(SigHandle), (char *)buffer, 10);
		xmlNodeSetContent(cur,(const unsigned char *)buffer);
		cur = xmlAddChild(parent,cur);

		if (axGetLastError(SigHandle) != 0)
		{
			unsigned char *tmpErr=axGetError(SigHandle);
			// add comment with additional errors
			commNode = xmlNewDocComment(doc,(const unsigned char *)tmpErr);
			cur = xmlAddChild(parent,commNode);
			zFree(tmpErr);
		}

		
		cur = xmlNewNode(NULL,(const unsigned char *)"ReferenceCount");
		// Set reference count to zero
		xmlNodeSetContent(cur,(const unsigned char *)"0");
		cur = xmlAddChild(parent,cur);
		cur = xmlNewNode(NULL,(const unsigned char *)"Reference");
		cur = xmlAddChild(parent,cur);
	}
	else // There was at least one signature in the document
	{
		for (i=0; i<signum; i++) // For each signature in the document
		{
			refNum = sgArr[i]->refNumber; // Number of URI in this signature
			refArr = sgArr[i]->refArray;  // The URI Array itself

		    /*
			 * SignatureStatus
			 */
			cur = xmlNewNode(NULL,(const unsigned char *)"SignatureStatus"); // Using the parent element's name space
			cur = xmlAddChild(rootNode,cur);

			/*
			* subnodes of SignatureStatus
			*/
			parent = cur;
			cur = xmlNewNode(NULL,(const unsigned char *)"SignatureId");

			if (sgArr[i]->sigId != NULL)
			{
				xmlNodeSetContent(cur,(const unsigned char *)sgArr[i]->sigId);
			}
			cur = xmlAddChild(parent,cur);
				
			cur = xmlNewNode(NULL,(const unsigned char *)"SignatureAlgorithm");
			if (sgArr[i]->sigMethod != NULL)
			{
				xmlNodeSetContent(cur,(const unsigned char *)sgArr[i]->sigMethod);
			}
			cur = xmlAddChild(parent,cur);
			
			cur = xmlNewNode(NULL,(const unsigned char *)"Status");
			long certStatus=0;

			if ((CertVerifyParams.verificationOptions & (~VERIFY_CRL_REC)) &&
				(sgArr[i]->status != FALSE) && (sgArr[i]->certificatesCount != 0))
			{
				sigStatus = 0;
				get_SigCertStatus(i, NULL, 0, &certStatus);
				if (certStatus != 0)
				{
					// Add signature status value of failed
					itoa(FALSE, (char *)buffer, 10);
					sgArr[i]->status = FALSE;
				}
				else
					itoa(TRUE, (char *)buffer, 10);
			}
			else
				itoa(sgArr[i]->status, (char *)buffer, 10);

			xmlNodeSetContent(cur,(const unsigned char *)buffer);
			cur = xmlAddChild(parent,cur);

			cur = xmlNewNode(NULL,(const unsigned char *)"LastError");
			if ((CertVerifyParams.verificationOptions & (~VERIFY_CRL_REC)) &&
				(certStatus != 0))
			{
				itoa(certStatus, (char *)buffer, 10);
			}
			else
				itoa(sgArr[i]->lasterror, (char *)buffer, 10);

			xmlNodeSetContent(cur,(const unsigned char *)buffer);
			cur = xmlAddChild(parent,cur);	

			if ((axGetLastError(SigHandle) != 0) && (CertVerifyParams.verificationOptions & (~VERIFY_CRL_REC)) &&
				(certStatus != 0))
			{
				// add comment with additional errors
				unsigned char * errStr = axGetError(SigHandle);
				commNode = xmlNewDocComment(doc,(const unsigned char *)errStr);
				zFree(errStr);
				cur = xmlAddChild(parent,commNode);
			}
			else
				if (sgArr[i]->lasterror != 0)
				{
					commNode = xmlNewDocComment(doc,(const unsigned char *)errorMsgTable[sgArr[i]->lasterror]);
					cur = xmlAddChild(parent,commNode);
				}
					
			cur = xmlNewNode(NULL,(const unsigned char *)"ReferenceCount");
			itoa(refNum, (char *)buffer, 10);
			xmlNodeSetContent(cur,(const unsigned char *)buffer);
			cur = xmlAddChild(parent,cur);

			if (sgArr[i]->signerCert != NULL)
			{
				unsigned char *utf8CharStr=NULL;
				int	utf8CharStrLen=0, utf16CharStrLen=0, utf16StrByteLen=0;

				cur = xmlNewNode(NULL,(const unsigned char *)"CertificateInfo");
				cur = xmlAddChild(parent,cur);
				// Adding subnodes of CertificateInfo
				parent = cur;
				cur = xmlNewNode(NULL,(const unsigned char *)"Subject");
				if (sgArr[i]->certificatesCount != 0)
					if ((utf16CharStrLen = wcslen(sgArr[i]->signerCert->subject)) != 0)
					{
						utf16StrByteLen = utf16CharStrLen * 2;
						utf8CharStrLen = utf16StrByteLen * 2;
						utf8CharStr = (unsigned char *)zMalloc(utf8CharStrLen);
						memset(utf8CharStr, 0, utf8CharStrLen);
						UTF16LEToUTF8(utf8CharStr, &utf8CharStrLen, (const unsigned char *)sgArr[i]->signerCert->subject, &utf16StrByteLen);
						xmlNodeSetContent(cur,(const unsigned char *)utf8CharStr);
						zFree(utf8CharStr);
					}
				cur = xmlAddChild(parent,cur);

				cur = xmlNewNode(NULL,(const unsigned char *)"ShortSubject");
				if (sgArr[i]->certificatesCount != 0)
					if ((utf16CharStrLen = wcslen(sgArr[i]->signerCert->shortSubject)) != 0)
					{
						utf16StrByteLen = utf16CharStrLen * 2;
						utf8CharStrLen = utf16StrByteLen * 2;
						utf8CharStr = (unsigned char *)zMalloc(utf8CharStrLen);
						memset(utf8CharStr, 0, utf8CharStrLen);
						UTF16LEToUTF8(utf8CharStr, &utf8CharStrLen, (const unsigned char *)sgArr[i]->signerCert->shortSubject, &utf16StrByteLen);
						xmlNodeSetContent(cur,(const unsigned char *)utf8CharStr);
						zFree(utf8CharStr);
					}
				cur = xmlAddChild(parent,cur);

				cur = xmlNewNode(NULL,(const unsigned char *)"CertificateIssuer");
				if (sgArr[i]->certificatesCount != 0)
					if ((utf16CharStrLen = wcslen(sgArr[i]->signerCert->issuer)) != 0)
					{
						utf16StrByteLen = utf16CharStrLen * 2;
						utf8CharStrLen = utf16StrByteLen * 2;
						utf8CharStr = (unsigned char *)zMalloc(utf8CharStrLen);
						memset(utf8CharStr, 0, utf8CharStrLen);
						UTF16LEToUTF8(utf8CharStr, &utf8CharStrLen, (const unsigned char *)sgArr[i]->signerCert->issuer, &utf16StrByteLen);
						xmlNodeSetContent(cur,(const unsigned char *)utf8CharStr);
						zFree(utf8CharStr);
					}
				cur = xmlAddChild(parent,cur);
				
				cur = xmlNewNode(NULL,(const unsigned char *)"CertificateSerialNumber");
				if (sgArr[i]->certificatesCount != 0)
					if (sgArr[i]->signerCert->serialNumber != NULL)
					{
						if (CertSerialNumberFormat == CERT_SERIAL_PLAIN_HEX)
						{
							plainTextHex = Base64BinToPlainHex(sgArr[i]->signerCert->serialNumber);
							xmlNodeSetContent(cur,(const unsigned char *)plainTextHex);
							zFree(plainTextHex);
						}
						else
							xmlNodeSetContent(cur,(const unsigned char *)sgArr[i]->signerCert->serialNumber);
					}
				cur = xmlAddChild(parent,cur);
				
				cur = xmlNewNode(NULL,(const unsigned char *)"CertificateExpiration");
				if (sgArr[i]->certificatesCount != 0)
					if (sgArr[i]->signerCert->notAfter != NULL)
						xmlNodeSetContent(cur,(const unsigned char *)sgArr[i]->signerCert->notAfter);
				cur = xmlAddChild(parent,cur);
				parent = parent->parent;
			}


			for (j=0; j<refNum; j++) // for each reference that was signed
			{

				cur = xmlNewNode(NULL,(const unsigned char *)"Reference");
				cur = xmlAddChild(parent,cur);

				// Add subnodes of Reference
				parent = cur;

				cur = xmlNewNode(NULL,(const unsigned char *)"URI");
				if (refArr[j]->URI != NULL)
				{
					xmlNodeSetContent(cur,(const unsigned char *)refArr[j]->URI);
				}
				cur = xmlAddChild(parent,cur);

				cur = xmlNewNode(NULL,(const unsigned char *)"DigestMethod");
				if (refArr[j]->digestMethod != NULL)
				{
					xmlNodeSetContent(cur,(const unsigned char *)refArr[j]->digestMethod);
				}
				cur = xmlAddChild(parent,cur);
				
				cur = xmlNewNode(NULL,(const unsigned char *)"DigestStatus");
				itoa(refArr[j]->status, (char *)buffer, 10);
				xmlNodeSetContent(cur,(const unsigned char *)buffer);
				cur = xmlAddChild(parent,cur);

				
				cur = xmlNewNode(NULL,(const unsigned char *)"SignedObject");
				if (refArr[j]->refObject != NULL)
				{
					if (refArr[j]->refObject->encoding != NULL)
						xmlNewProp(cur, (const unsigned char *)"Encoding", (const unsigned char *)refArr[j]->refObject->encoding);
					if (refArr[j]->refObject->encodedData != NULL)
					{
						xmlNodeSetContent(cur,(const unsigned char *)refArr[j]->refObject->encodedData);
					}
				}
				cur = xmlAddChild(parent,cur);
				parent = parent->parent;
			} // end for each reference

			cur = xmlNewNode(NULL,(const unsigned char *)"PropertyCount");
			itoa(sgArr[i]->propNumber, (char *)buffer, 10);
			xmlNodeSetContent(cur,(const unsigned char *)buffer);
			cur = xmlAddChild(parent,cur);

			cur = xmlNewNode(NULL,(const unsigned char *)"SignatureProperties");
			cur = xmlAddChild(parent,cur);

			// Add subnodes of SignatureProperties
			parent = cur;

			char *charTsProp;
			char *equalPtr;

			for (j = 0; j < sgArr[i]->propNumber;  j++)
			{
				// Adding Signature properties
				cur = xmlNewNode(NULL,(const unsigned char *)"Property");
				cur = xmlAddChild(parent,cur);

				// Adding subnodes of Property
				parent = cur;
				charTsProp = (char *)sgArr[i]->propArray[j];

				equalPtr = StrChr(charTsProp, '=');
				*equalPtr = '\0';

				cur = xmlNewNode(NULL,(const unsigned char *)"Name");
				xmlNodeSetContent(cur,(const unsigned char *)charTsProp);
				cur = xmlAddChild(parent,cur);

				cur = xmlNewNode(NULL,(const unsigned char *)"Value");
				xmlNodeSetContent(cur,(const unsigned char *)(equalPtr+1));
				*equalPtr = '='; //Restore the value

				cur = xmlAddChild(parent,cur);
				parent = parent->parent;
			}

		} /* end for each signature in the document loop */
	}
	xmlDocDumpMemoryEnc(doc,&mem,&iSize, "UTF-16");
#ifdef WIN32
	m_binaryData.AssignData((const void *)mem, (long) iSize);
	*verificationResponseByteArray = m_binaryData.Copy();
#else		
	VARIANT v;
	VariantInit(&v);
	*verificationResponseByteArray = v;
	VariantFromByteArray(verificationResponseByteArray,(const char *)mem, (long) iSize);
#endif

	xmlFree(mem);
	xmlFreeDoc(doc);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::SignXMLXpathByteArray(VARIANT inputXmlByteArray, BSTR xpathExp, BSTR signatureId, VARIANT* signedXmlByteArray)
{
	char *charSigId=NULL, *curCharSigId=NULL;
	unsigned char *charSignedXMLStr=NULL;
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL, parent=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlChar *mem=NULL;
	int iSize=0;
	CComBSTR	sigId;
	CComBSTR tmpXmlStr;
	unsigned char *newPtr=NULL;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	BOOL templateFound=FALSE;
	CBufferVariant m_binaryData;
	VARIANT *inputByteArray;
	char *equalPtr;
	CComBSTR tmpXpathStr;
	char *charTest;
#ifdef LOGGING
	char buffer[200];
#endif

	USES_CONVERSION;

	EnterObjectLog;
	if (inputXmlByteArray.vt == (VT_VARIANT | VT_BYREF))
	{
		inputByteArray = inputXmlByteArray.pvarVal;
	}
	else
		inputByteArray = &inputXmlByteArray;

	if (inputByteArray->vt != (VT_ARRAY | VT_UI1))
	{
		setError(SigHandle, INVALID_VARIANT);
		m_binaryData.SetLength(0);
		*signedXmlByteArray = m_binaryData.Copy();
		return S_FALSE;
	}

	//if (! LicObj.checkLicense()) {
	//	setError(SigHandle, INVALID_SECUREXML_LIC);
	//	m_binaryData.SetLength(0);
	//	*signedXmlByteArray = m_binaryData.Copy();
	//	return S_FALSE;
	//}
	//if (! LicObj.getSignAllowed()) 
	//{
	//	setError(SigHandle, NO_SIGNING_LIC);
	//	m_binaryData.SetLength(0);
	//	*signedXmlByteArray = m_binaryData.Copy();
	//	return S_FALSE;
	//}

	BOOL freeCharSigId = FALSE;
	sigId = signatureId;
	if (sigId.Length() == 0)
		charSigId = NULL;
	else
	{
		charSigId = (char *)HeapW2A(signatureId);
		freeCharSigId = TRUE;
	}
#ifdef LOGGING
	sprintf((char *)buffer, "Variant type = %x", inputXmlByteArray.vt);
	DebugLog((const char *)buffer);
#endif
	// original document
	m_binaryData = inputXmlByteArray;
	if (! LicObj.getSignAllowed()) 
	{
		if (!LicObj.getFormSignAllowed((unsigned char *)((void *)m_binaryData), m_binaryData.GetLength(), SigHandle))
		{
			setError(SigHandle, NO_SIGNING_LIC);
			m_binaryData.SetLength(0);
			*signedXmlByteArray = m_binaryData.Copy();
			if (freeCharSigId)
				zFree(charSigId);
			return S_FALSE;
		}
	}
	doc = xmlParseMemory((const char *)((void *)m_binaryData), m_binaryData.GetLength());
	if (!doc) 
	{
		setError(SigHandle, XML_PARSER_ERROR);
		m_binaryData.SetLength(0);
		*signedXmlByteArray = m_binaryData.Copy();
		if (freeCharSigId)
			zFree(charSigId);
		return S_FALSE;
	}
	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	if (charSigId == NULL)
		if (SignatureID.Length() == 0)
		{
//#ifdef WIN32
//			CoCreateGuid(&sigGuid);
//			GuidToString(&sigGuid, guidStr);
//#else
//			uuid_generate(sigGuid);
//			uuid_unparse(sigGuid, guidStr);
//#endif
//			charSigId = guidStr;
		}
		else
		{
			charSigId = (char *)HeapW2A(SignatureID.m_str);
			freeCharSigId = TRUE;
		}

	root = xmlDocGetRootElement(doc);
	if (charSigId != NULL)
		sigNode = xsSigNodeById((const xmlNodePtr) root, (const xmlChar *)charSigId);
	else
		sigNode = xsSigNodeWithNoIdNoSigValue((const xmlNodePtr) root);
	if (sigNode != NULL)
	{
		templateFound = TRUE;
		cur = sigNode->xmlChildrenNode;
		while (cur)
		{
				if (!(xmlStrcmp(cur->name, (const xmlChar *) "SignedInfo")))
				{
					signedInfoNode = cur;
					break;
				}
				cur = cur->next;
		}  // end while cur != NULL
	}
	  
	  if (templateFound == FALSE) // A Signature element with matching Id was not found
	  {
		  // Add a new Signature element
		/*
		* Signature
		*/

		cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
		sigNode = cur;
		if (charSigId != NULL)
			xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
		cur = xmlAddChild(root,cur);
		//xmlNewNs(cur,(const unsigned char *)"http://www.w3.org/2000/09/xmldsig#",(const unsigned char *)NULL);

		xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
		parent = cur;

	
		/*
		* SignedInfo
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
		signedInfoNode = cur;
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		 * Canonicalization Method
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
		switch(CanonicalizationMethod)
		{
			case WITH_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
				break;
			case WITHOUT_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
				break;
			case EXC_WITH_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
				break;
			case EXC_WITHOUT_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
				break;
			default:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
		}
		cur = xmlAddChild(parent,cur);
		/*
		* Reference
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
		cur = xmlAddChild(parent,cur);
		xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)"");
		parent = cur;

		/*
		* Transforms
		*/
	
		cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		* Transform
		*/
	
		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_ENVELOPED_SIG);
		cur = xmlAddChild(parent,cur);

		/*
		* Transform
		*/
		
		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_XPATH);
		cur = xmlAddChild(parent,cur);
		parent = cur;

		cur = xmlNewNode(NULL,(const unsigned char *)"XPath");
		if (XpathNamespaceCount != 0)
		{
			for (UINT i=0; i < XpathNamespaceCount; i++)
			{
				equalPtr = StrChr(XpathNamespaceList[i], '=');
				if (equalPtr == NULL)
				{
					xmlNewNs(cur, (const unsigned char *)XpathNamespaceList[i], (const unsigned char *)NULL);
				}
				else
				{
					*equalPtr = '\0';
					xmlNewNs(cur, (const unsigned char *)equalPtr+1, (const unsigned char *)XpathNamespaceList[i]);
					*equalPtr = '=';
				}
			}
		}
		cur = xmlAddChild(parent,cur);
		tmpXpathStr = xpathExp;
		if (tmpXpathStr.Length() == 0)
		{
			setError(SigHandle, XML_PARSER_ERROR);
			if (freeCharSigId)
				zFree(charSigId);
			return S_FALSE;
		}

		charTest = (char *)HeapW2A(xpathExp);
		xmlNodeSetContent(cur,(const unsigned char *)charTest);
		zFree(charTest);
	  }
	  else // A Signature element with matching Id was found
	  {
		parent = signedInfoNode;
		/*
		* Reference
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
		cur = xmlAddChild(parent,cur);
		xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)"");
		parent = cur;

		/*
		* Transforms
		*/
	
		cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		* Transform
		*/
		if ((CanonicalizationMethod == EXC_WITH_COMMENTS) ||
			(CanonicalizationMethod == EXC_WITHOUT_COMMENTS))
		{
			cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			}
			cur = xmlAddChild(parent,cur);
			parent = cur;
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_WITH_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_NO_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			cur = xmlAddChild(parent,cur);
			parent = parent->parent;
		}

		/*
		* Transform
		*/
	
		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_ENVELOPED_SIG);
		cur = xmlAddChild(parent,cur);

		/*
		* Transform
		*/
		
		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_XPATH);
		cur = xmlAddChild(parent,cur);
		parent = cur;

		cur = xmlNewNode(NULL,(const unsigned char *)"XPath");
		if (XpathNamespaceCount != 0)
		{
			for (UINT i=0; i < XpathNamespaceCount; i++)
			{
				equalPtr = StrChr(XpathNamespaceList[i], '=');
				if (equalPtr == NULL)
				{
					xmlNewNs(cur, (const unsigned char *)XpathNamespaceList[i], (const unsigned char *)NULL);
				}
				else
				{
					*equalPtr = '\0';
					xmlNewNs(cur, (const unsigned char *)equalPtr+1, (const unsigned char *)XpathNamespaceList[i]);
					*equalPtr = '=';
				}
			}
		}
		cur = xmlAddChild(parent,cur);
		tmpXpathStr = xpathExp;
		if (tmpXpathStr.Length() == 0)
		{
			setError(SigHandle, XML_PARSER_ERROR);
			if (freeCharSigId)
				zFree(charSigId);
			return S_FALSE;
		}

		charTest = (char *)HeapW2A(xpathExp);
		xmlNodeSetContent(cur,(const unsigned char *)charTest);
		zFree(charTest);
	  }

#ifdef WIN32
	  if (AddWindowImageFlag == TRUE)
		  AddWindowImage(sigNode, signedInfoNode, charSigId);

	  if (PhysicalSigUsage != NO_PHYSICAL_SIG)		  
		  AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif
	/*
	 * init Signature. crBlob contains XML - envelope document
	 */
	short tmpEnvFlag = EnvelopingFlag;
	EnvelopingFlag = ENVELOPED;

	if (!(CreateSigFromTmplBlob(doc,charSigId, &charSignedXMLStr, &iSize)))
	{
		if (charSignedXMLStr != NULL)
			xmlFree(charSignedXMLStr);
		EnvelopingFlag = tmpEnvFlag;
		m_binaryData.SetLength(0);
		*signedXmlByteArray = m_binaryData.Copy();
		if (freeCharSigId)
			zFree(charSigId);
		return S_FALSE;
	}
	else
	{
		if (charSignedXMLStr != NULL)
		{
#ifdef WIN32
			m_binaryData.AssignData((const void *)charSignedXMLStr, (long) iSize);
			*signedXmlByteArray = m_binaryData.Copy();
#else		
			VARIANT v;
			VariantInit(&v);
			*signedXmlByteArray = v;
			VariantFromByteArray(signedXmlByteArray,(const char *)charSignedXMLStr, (long) iSize);
#endif
			if (Base64EncodeXML == TRUE)
				zFree(charSignedXMLStr);
			else
				xmlFree(charSignedXMLStr);
		}
	}
	EnvelopingFlag = tmpEnvFlag;
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::SignXMLEnvelopedByteArray(VARIANT inputXmlByteArray, BSTR sigId, VARIANT* signedXmlByteArray)
{
	DS_DATA_BLOB crBlob;
	unsigned char *certData=NULL;
	keyinfo *ki=NULL;
	unsigned char *charSignedXML;
	char *charSigId;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	CBufferVariant m_binaryData;
	VARIANT *inputByteArray;
#ifdef LOGGING
	char buffer[200];
#endif

	USES_CONVERSION;
	
	EnterObjectLog;
	//if (! LicObj.checkLicense()) {
	//	setError(SigHandle, INVALID_SECUREXML_LIC);
	//	m_binaryData.SetLength(0);
	//	*signedXmlByteArray = m_binaryData.Copy();
	//	return S_FALSE;
	//}
	//if (!LicObj.getSignAllowed()) {
	//	setError(SigHandle, NO_SIGNING_LIC);
	//	m_binaryData.SetLength(0);
	//	*signedXmlByteArray = m_binaryData.Copy();
	//	return S_FALSE;
	//}
	if (inputXmlByteArray.vt == (VT_VARIANT | VT_BYREF))
	{
		inputByteArray = inputXmlByteArray.pvarVal;
	}
	else
		inputByteArray = &inputXmlByteArray;

	if (inputByteArray->vt != (VT_ARRAY | VT_UI1))
	{
		setError(SigHandle, INVALID_VARIANT);
		m_binaryData.SetLength(0);
		*signedXmlByteArray = m_binaryData.Copy();
		return S_FALSE;
	}

	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	xmlDocPtr doc= NULL;
	xmlNodePtr cur=NULL, rootNode=NULL, parent=NULL, commNode=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlNsPtr curNs=NULL;
	xmlChar *mem=NULL;
	int iSize=0;
	crBlob.cbData = 0;
	crBlob.pbData = NULL;
	CComBSTR tmpInputXML;
#ifdef LOGGING
	sprintf((char *)buffer, "Variant type = %x", inputXmlByteArray.vt);
	DebugLog((const char *)buffer);
#endif
	// original document
	m_binaryData = inputXmlByteArray;

	if (! LicObj.getSignAllowed()) 
	{
		if (!LicObj.getFormSignAllowed((unsigned char *)((void *)m_binaryData), m_binaryData.GetLength(), SigHandle))
		{
			setError(SigHandle, NO_SIGNING_LIC);
			m_binaryData.SetLength(0);
			*signedXmlByteArray = m_binaryData.Copy();
			return S_FALSE;
		}
	}

	doc = xmlParseMemory((const char *)((void *)m_binaryData), m_binaryData.GetLength());
	if (!doc) {
		setError(SigHandle,XML_PARSER_ERROR);
		m_binaryData.SetLength(0);
		*signedXmlByteArray = m_binaryData.Copy();
		return S_FALSE;
	}
	rootNode = xmlDocGetRootElement(doc);

	/*
	 * Signature
	*/

	tmpInputXML = sigId;
	BOOL freeCharSigId = FALSE;
	if (tmpInputXML.Length() == 0)
		charSigId = NULL;
	else
	{
		charSigId = (char *)HeapW2A(sigId);
		freeCharSigId = TRUE;
	}

	if (charSigId == NULL)
		if (SignatureID.Length() == 0)
		{
#ifdef WIN32
			CoCreateGuid(&sigGuid);
			GuidToString(&sigGuid, guidStr);
#else
			uuid_generate(sigGuid);
			uuid_unparse(sigGuid, guidStr);
#endif
			charSigId = guidStr;
		}
		else
		{
			charSigId = (char *)HeapW2A(SignatureID.m_str);
			freeCharSigId = TRUE;
		}


	cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
	sigNode = cur;
	xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
	cur = xmlAddChild(rootNode,cur);
	xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
	parent = cur;

	/*
	 * SignedInfo
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
	signedInfoNode = cur;
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	 * Canonicalization Method
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
	switch(CanonicalizationMethod)
	{
		case WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
			break;
		case WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
			break;
		case EXC_WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			break;
		case EXC_WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			break;
		default:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
	}
	cur = xmlAddChild(parent,cur);
	/*
	 * Reference
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
	cur = xmlAddChild(parent,cur);
	xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)"");
	parent = cur;

	/*
	 * Transforms
	 */
	
	cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
	* Transform
	*/
	if ((CanonicalizationMethod == EXC_WITH_COMMENTS) ||
		(CanonicalizationMethod == EXC_WITHOUT_COMMENTS))
	{
		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		if (CanonicalizationMethod == EXC_WITH_COMMENTS)
		{
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
		}
		else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
		{
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
		}
		cur = xmlAddChild(parent,cur);
		parent = cur;
		if (CanonicalizationMethod == EXC_WITH_COMMENTS)
		{
			cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
			xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_WITH_COMM,(const unsigned char *)"ec");
			xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
		}
		else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
		{
			cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
			xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_NO_COMM,(const unsigned char *)"ec");
			xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
		}
		cur = xmlAddChild(parent,cur);
		parent = parent->parent;
	}

	/*
	 * Transform
	 */
	
	cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
	xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_ENVELOPED_SIG);
	cur = xmlAddChild(parent,cur);
#ifdef WIN32
	if (AddWindowImageFlag == TRUE)
		AddWindowImage(sigNode, signedInfoNode, charSigId);

	if (PhysicalSigUsage != NO_PHYSICAL_SIG)
		AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif
	short tmpEnvFlag = EnvelopingFlag;
	EnvelopingFlag = ENVELOPED;

	if (!(CreateSigFromTmplBlob(doc, (char *)charSigId, &charSignedXML, &iSize)))
	{
		if (charSignedXML != NULL)
			xmlFree(charSignedXML);
		EnvelopingFlag = tmpEnvFlag;
		m_binaryData.SetLength(0);
		*signedXmlByteArray = m_binaryData.Copy();
		if (freeCharSigId)
			zFree(charSigId);
		return S_FALSE;
	}
	else
	{
		if (charSignedXML != NULL)
		{
#ifdef WIN32
			m_binaryData.AssignData((const void *)charSignedXML, (long) iSize);
			*signedXmlByteArray = m_binaryData.Copy();
#else		
			VARIANT v;
			VariantInit(&v);
			*signedXmlByteArray = v;
			VariantFromByteArray(signedXmlByteArray,(const char *)charSignedXML, (long) iSize);
#endif

			if (Base64EncodeXML == TRUE)
				zFree(charSignedXML);
			else
				xmlFree(charSignedXML);
		}
	}
	EnvelopingFlag = tmpEnvFlag;
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::Base64DecodeByteArrayToFile(VARIANT encodedBuffer, BSTR outFilePath, BSTR* decodedFilePath)
{
	unsigned char *newPtr;
	DWORD sizeM;
	CComBSTR ccBstrFileName;
	char TempPath[MAX_PATH];
	FILE *hFile;
	CBufferVariant m_binaryData;
	VARIANT *inputByteArray;
	TEMP_FILE_INFO *tmpFilePath = NULL;
	BSTR bstrFileName=NULL;

	USES_CONVERSION;

	EnterObjectLog;
	if (encodedBuffer.vt == (VT_VARIANT | VT_BYREF))
	{
		inputByteArray = encodedBuffer.pvarVal;
	}
	else
		inputByteArray = &encodedBuffer;

	if (inputByteArray->vt != (VT_ARRAY | VT_UI1))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	m_binaryData = encodedBuffer;
	if (m_binaryData.GetLength() == 0)
	{
		setError(SigHandle, BASE64_ERROR);
		return S_FALSE;
	}
	sizeM = base64decodeSize(m_binaryData.GetLength());
	newPtr = (unsigned char *)zMalloc(sizeM+1);
	if ((sizeM = base64decode((unsigned char*)m_binaryData,newPtr,sizeM+1))==-1)
	{
		zFree(newPtr);
		setError(SigHandle, BASE64_ERROR);
		return S_FALSE;
	}

	ccBstrFileName = outFilePath;

	if ((ccBstrFileName.Length() == 0) || (FileAccessRestricted == TRUE))
	{
		// Create temporary file for saving decoded data
		GetTempPath((DWORD)MAX_PATH, TempPath); 
		GetTempFileName(TempPath, // dir. for temp. files 
			"INF",                // temp. file name prefix 
			0,                    // create unique name 
			szTempName);          // buffer for name 
		bstrFileName = A2WBSTR((LPCSTR)szTempName);
		tmpFilePath = new (TEMP_FILE_INFO);
		strcpy((char *)tmpFilePath->fileName, szTempName);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
	}
	else
		bstrFileName = SysAllocString(outFilePath);
//		strcpy((char *)szTempName,(const char *)W2A(outFilePath));
	// open file in write mode 
#ifdef WIN32
	if ((hFile = _wfopen(bstrFileName,L"wb"))==NULL) {
#elif UNIX
	unsigned char *utf8FileName = HeapW2A(bstrFileName);
	if ((hFile = fopen((const char *)utf8FileName, "wb")) == NULL) {
			zFree(utf8FileName);
#endif
			setError(SigHandle, IO_ERROR);
			zFree(newPtr);
			SysFreeString(bstrFileName);
			if (tmpFilePath != NULL)
			{
				tmpFileList->remove(tmpFilePath);
			}
			return S_FALSE;
	}
#ifdef UNIX
	zFree(utf8FileName);
#endif

	if (fwrite(newPtr, 1, sizeM, hFile) == 0)
	{
		setError(SigHandle, IO_ERROR);
		zFree(newPtr);
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}
	if (ferror(hFile))
	{
		setError(SigHandle, IO_ERROR);
		zFree(newPtr);
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}
	fclose(hFile);
	zFree(newPtr);
	*decodedFilePath = bstrFileName;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::Base64DecodeByteArrayToByteArray(VARIANT encodedBuffer, VARIANT* decodedBuffer)
{
	unsigned char *newPtr;
	DWORD sizeM;
	CBufferVariant m_binaryData;
	VARIANT *inputByteArray;

	USES_CONVERSION;

	EnterObjectLog;
	if (encodedBuffer.vt == (VT_VARIANT | VT_BYREF))
	{
		inputByteArray = encodedBuffer.pvarVal;
	}
	else
		inputByteArray = &encodedBuffer;

	if (inputByteArray->vt != (VT_ARRAY | VT_UI1))
	{
		setError(SigHandle, INVALID_VARIANT);
		m_binaryData.SetLength(0);
		*decodedBuffer = m_binaryData.Copy();
		return S_FALSE;
	}

	m_binaryData = encodedBuffer;
	if (m_binaryData.GetLength() == 0)
	{
		setError(SigHandle, BASE64_ERROR);
		return S_FALSE;
	}

	sizeM = base64decodeSize(m_binaryData.GetLength());
	newPtr = (unsigned char *)zMalloc(sizeM+1);
	if ((sizeM = base64decode((unsigned char*)m_binaryData,newPtr,sizeM+1))==-1)
	{
		zFree(newPtr);
		setError(SigHandle, BASE64_ERROR);
		m_binaryData.SetLength(0);
		*decodedBuffer = m_binaryData.Copy();
		return S_FALSE;
	}
#ifdef WIN32
	m_binaryData.AssignData((const void *)newPtr, (long)sizeM);
	*decodedBuffer = m_binaryData.Copy();
#else		
	VARIANT v;
	VariantInit(&v);
	*decodedBuffer = v;
	VariantFromByteArray(decodedBuffer,(const char *)newPtr, (long) sizeM);
#endif

	zFree(newPtr);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::Base64EncodeByteArrayToByteArray(VARIANT inputBinary, VARIANT* encodedBuffer)
{
	unsigned char *newPtr;
	DWORD sizeM;
	CBufferVariant m_binaryData;
	VARIANT *inputByteArray;

	USES_CONVERSION;

	EnterObjectLog;
	if (inputBinary.vt == (VT_VARIANT | VT_BYREF))
	{
		inputByteArray = inputBinary.pvarVal;
	}
	else
		inputByteArray = &inputBinary;

	if (inputByteArray->vt != (VT_ARRAY | VT_UI1))
	{
		setError(SigHandle, INVALID_VARIANT);
		m_binaryData.SetLength(0);
		*encodedBuffer = m_binaryData.Copy();
		return S_FALSE;
	}

	m_binaryData = inputBinary;
	if (m_binaryData.GetLength() == 0)
	{
		setError(SigHandle, BASE64_ERROR);
		return S_FALSE;
	}
	sizeM = base64encodeSize(m_binaryData.GetLength());
	newPtr = (unsigned char *)zMalloc(sizeM+1);
	if ((sizeM = base64encode((unsigned char*)m_binaryData,m_binaryData.GetLength(),newPtr,sizeM+1))==-1)
	{
		zFree(newPtr);
		setError(SigHandle, BASE64_ERROR);
		m_binaryData.SetLength(0);
		*encodedBuffer = m_binaryData.Copy();
		return S_FALSE;
	}
#ifdef WIN32
	m_binaryData.AssignData((const void *)newPtr, (long)sizeM);
	*encodedBuffer = m_binaryData.Copy();
#else		
	VARIANT v;
	VariantInit(&v);
	*encodedBuffer = v;
	VariantFromByteArray(encodedBuffer,(const char *)newPtr, (long) sizeM);
#endif

	zFree(newPtr);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::Base64EncodeByteArrayToFile(VARIANT inputBinary, BSTR outFilePath, BSTR* encodedFilePath)
{
	HRESULT hr;
	VARIANT encodedBuffer;
	CComBSTR ccBstrFileName;
	char TempPath[MAX_PATH];
	FILE *hFile;
	CBufferVariant m_binaryData;
	TEMP_FILE_INFO	*tmpFilePath = NULL;
	BSTR bstrFileName=NULL;
	USES_CONVERSION;

	::VariantInit(&encodedBuffer);

	hr = Base64EncodeByteArrayToByteArray(inputBinary, &encodedBuffer);
	if (hr != S_OK)
		return S_FALSE;
	m_binaryData = encodedBuffer;
	if (m_binaryData.GetLength() == 0)
	{
		setError(SigHandle, BASE64_ERROR);
		return S_FALSE;
	}

	ccBstrFileName = outFilePath;

	if ((ccBstrFileName.Length() == 0) || (FileAccessRestricted == TRUE))
	{
		// Create temporary file for saving decoded data
		GetTempPath((DWORD)MAX_PATH, TempPath); 
		GetTempFileName(TempPath, // dir. for temp. files 
			"INF",                // temp. file name prefix 
			0,                    // create unique name 
			szTempName);          // buffer for name 
		bstrFileName = A2WBSTR((LPCSTR)szTempName);
		tmpFilePath = new (TEMP_FILE_INFO);
		strcpy((char *)tmpFilePath->fileName, szTempName);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
	}
	else
		bstrFileName = SysAllocString(outFilePath);
//		strcpy((char *)szTempName,(const char *)W2A(outFilePath));
	// open file in write mode 
#ifdef WIN32
	if ((hFile = _wfopen(bstrFileName,L"wb"))==NULL) {
#elif UNIX
	unsigned char *utf8FileName = HeapW2A(bstrFileName);
	if ((hFile = fopen((const char *)utf8FileName, "wb")) == NULL) {
			zFree(utf8FileName);
#endif
			setError(SigHandle, IO_ERROR);
			SysFreeString(bstrFileName);
			if (tmpFilePath != NULL)
			{
				tmpFileList->remove(tmpFilePath);
			}
			return S_FALSE;
	}
#ifdef UNIX
	zFree(utf8FileName);
#endif

	if (fwrite((const void *)m_binaryData, 1, m_binaryData.GetLength(), hFile) == 0)
	{
		setError(SigHandle, IO_ERROR);
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}
	if (ferror(hFile))
	{
		setError(SigHandle, IO_ERROR);
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}
	fclose(hFile);
	*encodedFilePath = bstrFileName;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::Base64EncodeStrToFile(BSTR inputStr, BSTR outFilePath, BSTR *encodedFilePath)
{
	CComBSTR ccBstrFileName, tmpXmlStr;
	char TempPath[MAX_PATH];
	FILE *hFile;
	char *charInputStr=NULL;
	BOOL freeMemory=FALSE;
	TEMP_FILE_INFO	*tmpFilePath = NULL;
	BSTR bstrFileName;

	USES_CONVERSION;

	EnterObjectLog;

	tmpXmlStr = inputStr;
	if (tmpXmlStr.Length() == 0)
	{
		setError(SigHandle, BASE64_ERROR);
		DebugLog("Input XML String is empty");
		return S_FALSE;
	}

	unsigned char *ptr = (unsigned char *)inputStr;
	unsigned int *szPtr = (unsigned int *)(ptr - sizeof(int));
	unsigned int inputSize = (*szPtr);

	if (((*ptr == 0xff) && (*(ptr +1) == 0xfe)) ||
		((*ptr == 0xfe) && (*(ptr +1) == 0xff)))
	{
		// The data is in utf-16 format so do not convert to char *
		charInputStr = (char *)ptr;
	}
	else
	{
		charInputStr = (char *)HeapW2A(inputStr);
		if (charInputStr == NULL)
		{
			setError(SigHandle, MEMORY_FAULT);
			return S_FALSE;
		}
		inputSize = strlen(charInputStr);
		freeMemory = TRUE;
	}

	int outputSize = base64encodeSize(inputSize);
	unsigned char *outputBuffer = (unsigned char *) zMalloc(outputSize + 1);
	if (outputBuffer == NULL)
	{
		if (freeMemory)
			zFree(charInputStr);
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}

	if ((outputSize = base64encode((unsigned char *)charInputStr, inputSize, outputBuffer, outputSize + 1)) == -1)
	{
		if (freeMemory)
			zFree(charInputStr);
		zFree(outputBuffer);
		setError(SigHandle, BASE64_ERROR);
		return S_FALSE;
	}
	if (freeMemory)
		zFree(charInputStr);

	ccBstrFileName = outFilePath;

	if ((ccBstrFileName.Length() == 0) || (FileAccessRestricted == TRUE))
	{
		// Create temporary file for saving decoded data
		GetTempPath((DWORD)MAX_PATH, TempPath); 
		GetTempFileName(TempPath, // dir. for temp. files 
			"INF",                // temp. file name prefix 
			0,                    // create unique name 
			szTempName);          // buffer for name 
		bstrFileName = A2WBSTR((LPCSTR)szTempName);
		tmpFilePath = new (TEMP_FILE_INFO);
		strcpy((char *)tmpFilePath->fileName, szTempName);
		tmpFileList->insert(tmpFileList->begin(), tmpFilePath);
	}
	else
		bstrFileName = SysAllocString(outFilePath);
//		strcpy((char *)szTempName,(const char *)W2A(outFilePath));
	// open file in write mode 
#ifdef WIN32
	if ((hFile = _wfopen(bstrFileName,L"wb"))==NULL) {
#elif UNIX
	unsigned char *utf8FileName = HeapW2A(bstrFileName);
	if ((hFile = fopen((const char *)utf8FileName, "wb")) == NULL) {
			zFree(utf8FileName);
#endif
			zFree(outputBuffer);
			setError(SigHandle, IO_ERROR);
			SysFreeString(bstrFileName);
			if (tmpFilePath != NULL)
			{
				tmpFileList->remove(tmpFilePath);
			}
			return S_FALSE;
	}
#ifdef UNIX
	zFree(utf8FileName);
#endif

	if (fwrite((const void *)outputBuffer, 1, outputSize, hFile) == 0)
	{
		zFree(outputBuffer);
		setError(SigHandle, IO_ERROR);
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}
	if (ferror(hFile))
	{
		zFree(outputBuffer);
		setError(SigHandle, IO_ERROR);
		if (tmpFilePath != NULL)
		{
			tmpFileList->remove(tmpFilePath);
		}
		return S_FALSE;
	}
	fclose(hFile);
	zFree(outputBuffer);
	*encodedFilePath = bstrFileName;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::Base64EncodeStrToStr(BSTR inputStr, BSTR* encodedStr)
{
	CComBSTR tmpXmlStr;
	char *charInputStr=NULL;
	BOOL freeMemory=FALSE;

	USES_CONVERSION;

	EnterObjectLog;

	tmpXmlStr = inputStr;
	if (tmpXmlStr.Length() == 0)
	{
		setError(SigHandle, BASE64_ERROR);
		DebugLog("Input XML String is empty");
		return S_FALSE;
	}

	unsigned char *ptr = (unsigned char *)inputStr;
	unsigned int *szPtr = (unsigned int *)(ptr - sizeof(int));
	unsigned int inputSize = (*szPtr);

	if (((*ptr == 0xff) && (*(ptr +1) == 0xfe)) ||
		((*ptr == 0xfe) && (*(ptr +1) == 0xff)))
	{
		// The data is in utf-16 format so do not convert to char *
		charInputStr = (char *)ptr;
	}
	else
	{
		charInputStr = (char *)HeapW2A(inputStr);
		if (charInputStr == NULL)
		{
			setError(SigHandle, MEMORY_FAULT);
			return S_FALSE;
		}
		inputSize = strlen(charInputStr);
		freeMemory = TRUE;
	}

	int outputSize = base64encodeSize(inputSize);
	unsigned char *outputBuffer = (unsigned char *) zMalloc(outputSize + 1);
	if (outputBuffer == NULL)
	{
		if (freeMemory)
			zFree(charInputStr);
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}

	if ((outputSize = base64encode((unsigned char *)charInputStr, inputSize, outputBuffer, outputSize + 1)) == -1)
	{
		if (freeMemory)
			zFree(charInputStr);
		zFree(outputBuffer);
		setError(SigHandle, BASE64_ERROR);
		return S_FALSE;
	}
	if (freeMemory)
		zFree(charInputStr);
	*encodedStr = A2WBSTR((LPCSTR)outputBuffer);
	zFree(outputBuffer);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::SetActivePFXB64Data(BSTR b64PfxData, BSTR pfxPassword, BSTR* pfxX509Cert)
{
	DWORD fileSize;
	char *certData=NULL;
	unsigned char *binFileData=NULL;
	unsigned char *charPfxB64Data=NULL;
	unsigned int sizeM;

USES_CONVERSION;
	EnterObjectLog;
	CComBSTR	tmpCcBstr;

	tmpCcBstr = b64PfxData;
	if (tmpCcBstr.Length() == 0)
	{
		setError(SigHandle, PFX_INVALID_CERTIFICATE);
		return S_FALSE;
	}

	unsigned char *ptr = (unsigned char *)b64PfxData;
	unsigned int *szPtr = (unsigned int *)(ptr - sizeof(int));
	unsigned int inputSize = (*szPtr);

	if (((*ptr == 0xff) && (*(ptr +1) == 0xfe)) ||
		((*ptr == 0xfe) && (*(ptr +1) == 0xff)))
	{
		// The data is in utf-16 format so do not convert to char *
		charPfxB64Data = (unsigned char *)zMalloc(inputSize);
		if (charPfxB64Data == NULL)
		{
			setError(SigHandle, MEMORY_FAULT);
			return S_FALSE;
		}
		memcpy(charPfxB64Data, (const char *)ptr, inputSize);
	}
	else
	{
		charPfxB64Data = HeapW2A(b64PfxData);
		if (charPfxB64Data == NULL)
		{
			setError(SigHandle, MEMORY_FAULT);
			return S_FALSE;
		}
		inputSize = strlen((const char *)charPfxB64Data);
	}

	fileSize = base64decodeSize(inputSize);

	binFileData = (unsigned char *)zMalloc(fileSize+1);
	if (binFileData == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		zFree(charPfxB64Data);
		return S_FALSE;
	}

	if ((fileSize = base64decode(charPfxB64Data, binFileData, fileSize+1)) == -1)
	{
		setError(SigHandle, BASE64_ERROR);
		zFree(charPfxB64Data);
		zFree(binFileData);
		return S_FALSE;
	}

	if (PfxPassword.pbData != NULL)
	{
		zFree(PfxPassword.pbData);
		PfxPassword.pbData = NULL;
	}

	ptr = (unsigned char *)pfxPassword;

	if (ptr != NULL)
	{
		szPtr = (unsigned int *)(ptr - sizeof(int));
		sizeM = *szPtr;

		if (sizeM == 0) {
			PfxPassword.pbData = NULL;
			PfxPassword.cbData = 0;
		}
		else
		{
			sizeM += 2; // BSTR size does not include the terminating null so add 2 to the size
			PfxPassword.pbData		= (unsigned char *) zMalloc(sizeM);
			memcpy(PfxPassword.pbData, ptr, sizeM);
			PfxPassword.cbData = sizeM;
		}
	}

	if (B64PfxDataPtr != NULL)
		zFree(B64PfxDataPtr);

	B64PfxDataPtr = charPfxB64Data;
	
	PfxCertDataBlob.cbData = fileSize;
	
	if (PfxCertDataBlob.pbData != NULL)
		zFree(PfxCertDataBlob.pbData);
	
	PfxCertDataBlob.pbData = binFileData; // Remember to free this memory in Empty()

	if (PfxX509Cert != NULL)
		zFree(PfxX509Cert);

	if (PfxCertInfo != NULL)
	{
		// Since PfxX509Cert and PfxCertInfo->certificate point to the same memory location
		// and we just freed PfxX509Cert above, we can't free PfxCertInfo->certificate as well
		zFree(PfxCertInfo);
		PfxCertInfo = NULL;
	}
#ifdef NSS
	SECItem spwd;
	spwd.data = PfxPassword.pbData;
	spwd.len = PfxPassword.cbData;
	PfxX509Cert	= crPFX2X509(&PfxCertDataBlob, &spwd, &PfxCertInfo, SigHandle);
#else
	PfxX509Cert	= crPFX2X509(&PfxCertDataBlob, (LPCWSTR) PfxPassword.pbData, &PfxCertInfo, SigHandle);
#endif

	if (PfxX509Cert != NULL)
	{
		*pfxX509Cert	= A2WBSTR((LPCSTR) PfxX509Cert);
		CurrentCertificate = USE_PFX_CERT;
	}

	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::put_FloatingLicense(BSTR signedXML)
{
	unsigned char *ptr, *newPtr=NULL;
	unsigned int sizeM;
	CComBSTR ccBstr;

	long osType;

	osType = CLicense::getHostOsType();

	if ((osType != 0) && (osType != VER_NT_WORKSTATION))
		 // It is not a client machine as it is some sort of windows server product
		 // Floating license is not allowed on a server class machine
	{
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}

	ccBstr = signedXML;
	if (ccBstr.Length() == 0)
		return S_FALSE;

	ptr = HeapW2A(signedXML);
	sizeM = strlen((const char *)ptr);
	sizeM = base64decodeSize(sizeM);
	if(!(newPtr = (BYTE *)zMalloc(sizeM+1)))
	{
		zFree(ptr);
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}
	if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
	{
		zFree(ptr);
		zFree(newPtr);
		setError(SigHandle, BASE64_ERROR);
		return S_FALSE;
	}
	zFree(ptr);
	LicObj.verifyFloatingLicense(newPtr, sizeM, SigHandle);
	zFree(newPtr);
	return S_OK;
}

STDMETHODIMP CSignature::get_FloatingLicense(BSTR *floatingLicenseStr)
{
//	DebugBreak();
	if (LicObj.getLicensedUserCount() == -1)
		*floatingLicenseStr = createSgts();
	return S_OK;
}

LPSYSTEMTIME localTimeToUtcTime(LPSYSTEMTIME localTime)
{
	TIME_ZONE_INFORMATION timeZoneInformation;
	CTime vbTime(*localTime);

	DWORD timeZoneId =  GetTimeZoneInformation(&timeZoneInformation);
	/*
	typedef struct _TIME_ZONE_INFORMATION { 
		LONG       Bias; 
		WCHAR      StandardName[ 32 ]; 
		SYSTEMTIME StandardDate; 
		LONG       StandardBias; 
		WCHAR      DaylightName[ 32 ]; 
		SYSTEMTIME DaylightDate; 
		LONG       DaylightBias; 
	} TIME_ZONE_INFORMATION, *PTIME_ZONE_INFORMATION;

	Members
	Bias 
	Current bias for local time translation on this computer, in minutes. The bias is the difference, 
	in minutes, between Coordinated Universal Time (UTC) and local time. All translations between UTC 
	and local time are based on the following formula: 

	UTC = local time + bias 
	This member is required. 

	StandardName 
	Pointer to a null-terminated string associated with standard time on this operating system. 
	For example, this member could contain "EST" to indicate Eastern Standard Time. This string 
	is not used by the operating system, so anything stored there using the SetTimeZoneInformation 
	function is returned unchanged by the GetTimeZoneInformation function. This string can be empty. 

	StandardDate 
	A SYSTEMTIME structure that contains a date and local time when the transition from daylight 
	saving time to standard time occurs on this operating system. If this date is not specified, 
	the wMonth member in the SYSTEMTIME structure must be zero. If this date is specified, the 
	DaylightDate value in the TIME_ZONE_INFORMATION structure must also be specified.
	To select the correct day in the month, set the wYear member to zero, the wDayOfWeek member 
	to an appropriate weekday, and the wDay member to a value in the range 1 through 5. Using this 
	notation, the first Sunday in April can be specified, as can the last Thursday in October 
	(5 is equal to "the last"). 

	StandardBias 
	Bias value to be used during local time translations that occur during standard time. This 
	member is ignored if a value for the StandardDate member is not supplied. 
	This value is added to the value of the Bias member to form the bias used during standard 
	time. In most time zones, the value of this member is zero. 

	DaylightName 
	Pointer to a null-terminated string associated with daylight saving time on this operating 
	system. For example, this member could contain "PDT" to indicate Pacific Daylight Time. This 
	string is not used by the operating system, so anything stored there by using the 
	SetTimeZoneInformation function is returned unchanged by the GetTimeZoneInformation function. 
	This string can be empty. 

	DaylightDate 
	A SYSTEMTIME structure that contains a date and local time when the transition from standard 
	time to daylight saving time occurs on this operating system. If this date is not specified, 
	the wMonth member in the SYSTEMTIME structure must be zero. If this date is specified, the 
	StandardDate value in the TIME_ZONE_INFORMATION structure must also be specified. 
	To select the correct day in the month, set the wYear member to zero, the wDayOfWeek member 
	to an appropriate weekday, and the wDay member to a value in the range 1 through 5. Using 
	this notation, the first Sunday in April can be specified, as can the last Thursday in 
	October (5 is equal to "the last"). 

	DaylightBias 
	Bias value to be used during local time translations that occur during daylight saving time. 
	This member is ignored if a value for the DaylightDate member is not supplied. 
	This value is added to the value of the Bias member to form the bias used during daylight 
	saving time. In most time zones, the value of this member is – 60. 


	*/

		switch(timeZoneId)
		{
			case TIME_ZONE_ID_UNKNOWN: 
		/* The system cannot determine the current time zone. 
		* This error is also returned if you call the SetTimeZoneInformation 
		* function and supply the bias values but no transition dates.
		* Windows NT/2000/XP: This value is returned if daylight saving time 
		* is not used in the current time zone, because there are no transition dates. 
		*/
				break;
			case TIME_ZONE_ID_STANDARD:
		/* The system is operating in the range covered by the StandardDate member of 
		* the TIME_ZONE_INFORMATION structure.
		* Windows 95/98/Me: This value is returned if daylight saving time is not 
		* used in the current time zone, because there are no transition dates.
		*/
				{
					CTimeSpan standardBias(0,0, timeZoneInformation.Bias, 0);
					vbTime = vbTime + standardBias;
					break;
				}

			case TIME_ZONE_ID_DAYLIGHT:
		/* The system is operating in the range covered by the DaylightDate member of 
		* the TIME_ZONE_INFORMATION structure.
		*/
				{
					CTimeSpan bias(0,0, timeZoneInformation.Bias, 0);
					CTimeSpan dayLightAdjustment(0,0, timeZoneInformation.DaylightBias, 0);
					vbTime = vbTime + bias + dayLightAdjustment;
					break;
				}
			default:
				break;
		}

		if (localTime) {
			vbTime.GetAsSystemTime(*localTime);
		}
		return localTime;
}

STDMETHODIMP CSignature::get_LicensedUserCount(LONG* pVal)
{
	*pVal = LicObj.getLicensedUserCount();
	return S_OK;
}

STDMETHODIMP CSignature::put_IncludeCRLInSignature(BOOL newVal)
{
	IncludeCRLInSignature = newVal;
	return S_OK;
}

STDMETHODIMP CSignature::get_UsedCRLList(VARIANT* pVal)
{
	VARIANT *outVariant;
	SAFEARRAY *outArray;
	SAFEARRAYBOUND rgsabound[1];
	HRESULT hr;
	
USES_CONVERSION;
	EnterObjectLog;
	outVariant = (VARIANT *)zMalloc(sizeof(VARIANT));
//	outArray = (SAFEARRAY *)zMalloc(sizeof(SAFEARRAY *));

	VariantInit(outVariant);

	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = CertVerifyParams.usedCrlCount;

	outArray = SafeArrayCreate(VT_BSTR, 
								1,
								rgsabound);
	if (outArray == NULL)
	{
		setError(SigHandle, MEMORY_FAULT);
		return S_FALSE;
	}
	for (long i=0; i<(long)CertVerifyParams.usedCrlCount; i++)
	{
		BSTR arrElement;
		arrElement = A2WBSTR(CertVerifyParams.usedCrlList[i]);
		hr = SafeArrayPutElement(outArray, &i, arrElement);
		if (hr != S_OK)
		{
			setError(SigHandle, MEMORY_FAULT);
			return S_FALSE;
		}
	}
	(*outVariant).vt = (VT_ARRAY | VT_BSTR);
	(*outVariant).parray = outArray;
	*pVal = *outVariant;
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::GetErrorDetail(LONG errorNum, BSTR* errorDesc)
{
	USES_CONVERSION;
	*errorDesc = A2WBSTR((LPCSTR)errorMsgTable[errorNum]);
	return S_OK;
}

STDMETHODIMP CSignature::put_PhysicalSignatureB64Str(BSTR newVal)
{
	if (PhysicalSignatureB64Str != NULL)
	{
		zFree(PhysicalSignatureB64Str);
		PhysicalSignatureB64Str = NULL;
	}
	if ((newVal != NULL) && (SysStringByteLen(newVal) != 0))
		PhysicalSignatureB64Str = HeapW2A(newVal);
	return S_OK;
}

STDMETHODIMP CSignature::GetSignedInfoDigest(BSTR xmlStr, BSTR signatureId, BSTR* signedInfoDigest)
{
	char *charXMLStr=NULL, *charSigId=NULL, *curCharSigId=NULL;
	unsigned char *charSignedInfoDigest=NULL;
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL, parent=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlChar *mem=NULL;
	int iSize=0;
	CComBSTR	sigId;
	unsigned char *ptr, *newPtr=NULL, *curPtr=NULL; 
	unsigned int *szPtr;
	unsigned int sizeM;

	xmlXPathContextPtr xpathPtr=NULL;
	xmlXPathObjectPtr xpathResultPtr=NULL;
	char *ptemp=NULL;
	BOOL freeNewPtr = FALSE;

#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	BOOL templateFound=FALSE;

	EnterObjectLog;

	*signedInfoDigest = A2WBSTR((LPCSTR)NULL);
	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		return S_FALSE;
	}
	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	USES_CONVERSION;

	BOOL freeCharSigId = FALSE;
	sigId = signatureId;
	if (sigId.Length() == 0)
		charSigId = NULL;
	else
	{
		charSigId = (char *)HeapW2A(signatureId);
		freeCharSigId = TRUE;
	}

	if (charSigId == NULL)
		if (SignatureID.Length() == 0)
		{
//#ifdef WIN32
//			CoCreateGuid(&sigGuid);
//			GuidToString(&sigGuid, guidStr);
//#else
//			uuid_generate(sigGuid);
//			uuid_unparse(sigGuid, guidStr);
//#endif
//			charSigId = guidStr;
		}
		else
		{
			charSigId = (char *)HeapW2A(SignatureID.m_str);
			freeCharSigId = TRUE;
		}

	if ((xmlStr != 0) && (SysStringByteLen(xmlStr) != 0))
	{
		if (Base64DecodeXML == FALSE)
		{
			ptr = (unsigned char *)xmlStr;
			szPtr = (unsigned int *)(ptr - sizeof(int));
			sizeM = (*szPtr);

			if (((*ptr == 0xff) && (*(ptr + 1) == 0xfe)) ||
				((*ptr == 0xfe) && (*(ptr + 1) == 0xff)))
			{
				// There is no need to put the UTF 16 header since the data is already in utf-16 format
				newPtr = ptr;
			}
			else
			{
				newPtr = (unsigned char *)zMalloc(sizeM + 4);
				freeNewPtr = TRUE;
				FileEncoding(newPtr);
				memcpy(newPtr+2, ptr, sizeM + 2);
				sizeM += 4;
			}
		}
		else
		{
			ptr = HeapW2A(xmlStr);
			sizeM = strlen((const char *)ptr);
			sizeM = base64decodeSize(sizeM);
			newPtr = (unsigned char *)zMalloc(sizeM+1);
			freeNewPtr = TRUE;
			if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
			{
				zFree(ptr);
				zFree(newPtr);
				setError(SigHandle, BASE64_ERROR);
				return S_FALSE;
			}
			zFree(ptr);
		}

		if (! LicObj.getSignAllowed()) 
		{
			if (!LicObj.getFormSignAllowed(newPtr, sizeM, SigHandle))
			{
				setError(SigHandle, NO_SIGNING_LIC);
				if (freeCharSigId)
					zFree(charSigId);
				if (freeNewPtr)
					zFree(newPtr);
				return S_FALSE;
			}
		}

		// original document
		doc = xmlParseMemory((const char *)newPtr,sizeM);
		if (freeNewPtr)
			zFree(newPtr);

		if (!doc) 
		{
			setError(SigHandle, XML_PARSER_ERROR);
			return S_FALSE;
		}

		root = xmlDocGetRootElement(doc);
	//	  cur = root->xmlChildrenNode;

		if (charSigId != NULL)
			sigNode = xsSigNodeById((const xmlNodePtr) root, (const xmlChar *)charSigId);
		else
			sigNode = xsSigNodeWithNoIdNoSigValue((const xmlNodePtr) root);
		if (sigNode != NULL)
		{
			templateFound = TRUE;
			cur = sigNode->xmlChildrenNode;
			while (cur)
			{
					if (!(xmlStrcmp(cur->name, (const xmlChar *) "SignedInfo")))
					{
						signedInfoNode = cur;
						break;
					}
					cur = cur->next;
			}  // end while cur != NULL
		}
		cur = root->xmlChildrenNode;
		if (templateFound == FALSE) // A Signature element with matching Id was not found
		{
			// Add a new Signature element

			/*
			* Signature
			*/

			cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
			sigNode = cur;
			if (charSigId != NULL)
				xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
			cur = xmlAddChild(root,cur);
			//xmlNewNs(cur,(const unsigned char *)"http://www.w3.org/2000/09/xmldsig#",(const unsigned char *)NULL);

			xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
			parent = cur;

			/*
			* SignedInfo
			*/
			cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
			signedInfoNode = cur;
			cur = xmlAddChild(parent,cur);
			parent = cur;

			/*
			* Canonicalization Method
			*/
			cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
			switch(CanonicalizationMethod)
			{
				case WITH_COMMENTS:
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
					break;
				case WITHOUT_COMMENTS:
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
					break;
				case EXC_WITH_COMMENTS:
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
					break;
				case EXC_WITHOUT_COMMENTS:
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
					break;
				default:
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
			}
			cur = xmlAddChild(parent,cur);
			if (signerCertChain == NULL)
			{//We assume RSA Algorithm will be used if no signer certificate info is provided
				cur = xmlNewNode(NULL, (const unsigned char *)"SignatureMethod");
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_RSAWITHSHA1);
				cur = xmlAddChild(parent, cur);
			}
			/*
			* Reference
			*/
			cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
			cur = xmlAddChild(parent,cur);
			xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)"");
			parent = cur;

			/*
			* Transforms
			*/
		
			cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
			cur = xmlAddChild(parent,cur);
			parent = cur;

			/*
			* Transform
			*/
			if ((CanonicalizationMethod == EXC_WITH_COMMENTS) ||
				(CanonicalizationMethod == EXC_WITHOUT_COMMENTS))
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
				if (CanonicalizationMethod == EXC_WITH_COMMENTS)
				{
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
				}
				else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
				{
					xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
				}
				cur = xmlAddChild(parent,cur);
				parent = cur;
				if (CanonicalizationMethod == EXC_WITH_COMMENTS)
				{
					cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
					xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_WITH_COMM,(const unsigned char *)"ec");
					xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
				}
				else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
				{
					cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
					xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_NO_COMM,(const unsigned char *)"ec");
					xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
				}
				cur = xmlAddChild(parent,cur);
				parent = parent->parent;
			}
			/*
			* Transform
			*/

			cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_ENVELOPED_SIG);
			cur = xmlAddChild(parent,cur);		
		}
	}
	else
	{
		if ((AttachedObjectCount != 0) || (DetachedObjectCount !=0))
		{
			doc = PrepareSignatureEnvelopeFromObjects(charSigId, &sigNode, &signedInfoNode);
			if (doc == NULL)
			{
				if (freeCharSigId)
					zFree(charSigId);
				return S_FALSE;
			}
		}
		else
		{
			if (freeCharSigId)
				zFree(charSigId);
			setError(SigHandle, XML_PARSER_ERROR);
			return S_FALSE;
		}
	}
#ifdef WIN32
	  if (PhysicalSigUsage != NO_PHYSICAL_SIG)		  
		  AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif
	/*
	 * init Signature. crBlob contains XML - envelope document
	 */
	short tmpEnvFlag = EnvelopingFlag;
	EnvelopingFlag = ENVELOPED;
//DebugBreak();
	calculateDigestOnly = TRUE;
	if (!(CreateSigFromTmplBlob(doc, charSigId, &charSignedInfoDigest, &iSize)))
	{
		if (charSignedInfoDigest != NULL)
		{
			zFree(charSignedInfoDigest);
		}
		EnvelopingFlag = tmpEnvFlag;
		*signedInfoDigest = NULL;
		calculateDigestOnly = FALSE;
		if (freeCharSigId)
			zFree(charSigId);
		return S_FALSE;
	}
	else
	{
		if (charSignedInfoDigest != NULL)
		{
			unsigned int cbData;
			unsigned char *pbData;
			cbData = base64encodeSize(iSize);
			pbData = (unsigned char *)zMalloc(cbData+1);
			if ((cbData = base64encode(charSignedInfoDigest, iSize, pbData, cbData+1)) == -1)
			{
				setError(SigHandle, BASE64_ERROR);
				zFree(pbData);
				zFree(charSignedInfoDigest);
				calculateDigestOnly = FALSE;
				if (freeCharSigId)
					zFree(charSigId);
				return S_FALSE;
			}
			zFree(charSignedInfoDigest);
			*signedInfoDigest = A2WBSTR((LPCSTR) pbData, cbData);
			zFree(pbData);
		}
	}
	EnvelopingFlag = tmpEnvFlag;
	calculateDigestOnly = FALSE;
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::GetX509CertificateChain(BSTR certID, BSTR* certChainAsB64XmlStr)
{
	CComBSTR tmpCertId;
	unsigned char *base64CertId=NULL, *certData=NULL;
	BOOL certificateFound = FALSE;
	unsigned char **certificateList=NULL;
	UINT certificateListCount=0;
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL, rootNode=NULL, parent=NULL;
	xmlChar *mem=NULL;
	int iSize=0;
	char buffer[20];
	unsigned int cbData=0;
	unsigned char *pbData=NULL;

	EnterObjectLog;
	tmpCertId = certID;

	*certChainAsB64XmlStr = A2WBSTR((LPCSTR) NULL);

	if (tmpCertId.Length() == 0)
	{
		setError(SigHandle, CERT_NOT_FOUND);
		return S_FALSE;
	}

USES_CONVERSION;
	if (CertSerialNumberFormat == CERT_SERIAL_PLAIN_HEX)
	{
		unsigned char *wCertID = HeapW2A(certID);
		base64CertId = PlainHexToBase64Bin(wCertID);
		zFree(wCertID);
	}
	else
		base64CertId = HeapW2A(certID);

	for (int i=0;i<CertificateCount;i++)
	{
		if (!(StrCmp((const char *)cV[i]->serialNumber, (const char *)base64CertId)))
		{
			certData = cV[i]->certificate;
			certificateFound = TRUE;
			break;
		}
	}
	if (base64CertId)
	{
		zFree(base64CertId);
		base64CertId = NULL;
	}
	if (certificateFound == FALSE)
	{
		setError(SigHandle, CERT_NOT_FOUND);
		return S_FALSE;
	}
#ifdef NSS
	SECItem si;
	si.data = PfxPassword.pbData;
	si.len = PfxPassword.cbData;
	certificateList = crGetSignerCertChain(	certData,
										&si,
										&certificateListCount,
										SigHandle);
#else
	certificateList = crGetSignerCertChain(	certData,
										(LPWSTR)PfxPassword.pbData,
										&certificateListCount,
										SigHandle);
#endif
	if ((certificateList == NULL) || (certificateListCount == 0))
		return S_FALSE;

	doc = xmlNewDoc((const unsigned char *)"1.0");
	// document, namespace, element name, element content
	cur = xmlNewDocNode(doc,NULL,(const unsigned char *)"CertificateChain",NULL);
	sprintf((char *)buffer, "%d", certificateListCount);
	xmlNewProp(cur, (const unsigned char *)"CertificateCount", (const unsigned char *)buffer);

	// add root element
	xmlDocSetRootElement(doc,cur);
	rootNode = cur;
	for (UINT i=0; i<certificateListCount; i++)
	{
		cur = xmlNewNode(NULL,(const unsigned char *)"X509Certificate");
		xmlNodeSetContent(cur,(const unsigned char *)certificateList[i]);
		cur = xmlAddChild(rootNode, cur);
	}
	for (UINT i=0; i<certificateListCount; i++)
		zFree(certificateList[i]);
	zFree(certificateList);
	xmlDocDumpMemory(doc,&mem,(int *)&iSize);
	xmlFreeDoc(doc);

	cbData = base64encodeSize(iSize);
	if(!(pbData = (BYTE *)zMalloc(cbData+1)))
	{
		xmlFree(mem);
		setError(SigHandle, MEMORY_FAULT);
		return FALSE;
	}
	if ((cbData  = base64encode(mem,iSize,(unsigned char*)pbData,cbData+1))==-1) 
	{
		setError(SigHandle, BASE64_ERROR);
		xmlFree(mem);
		zFree(pbData);
		return FALSE;
	}
	*(pbData+cbData)='\0';
	*certChainAsB64XmlStr = A2WBSTR((LPCSTR)pbData, cbData);
	zFree(pbData);
	xmlFree(mem);
	ExitObjectLog;
	return S_OK;
}

BYTE ** CSignature::getSignerCertChain(UINT * certificateCount)
{
	xmlDocPtr doc;
	xmlNodePtr cur=NULL, root=NULL;
	unsigned char *tmpCharPtr=NULL;
	BYTE **certList=NULL;
	UINT i=0;
	EnterObjectLog;
	*certificateCount = 0;

	if (signerCertChain == NULL)
	{
		ExitObjectLog;
		return NULL;
	}
	if ((doc = xmlParseMemory((const char *)signerCertChain, signerCertChainSize)) == NULL)
	{
		ExitObjectLog;
		return NULL;
	}

	root = xmlDocGetRootElement(doc);
	if ((tmpCharPtr = xmlGetProp(root, (const xmlChar *) "CertificateCount")) == NULL)
	{
		xmlFreeDoc(doc);
		ExitObjectLog;
		return NULL;
	}
	*certificateCount = (UINT)atoi((const char *)tmpCharPtr);
	xmlFree(tmpCharPtr);
	certList = (BYTE **)zMalloc(sizeof(BYTE *) * (*certificateCount));
	memset(certList, 0, sizeof(BYTE *) * (*certificateCount));

	cur = root->xmlChildrenNode;
	for (i=0; i< *certificateCount; i++)
	{
		if (cur == NULL)
			break;
		while (xmlStrcmp(cur->name, (const unsigned char *)"X509Certificate"))
		{
			cur = cur->next;
			if (cur == NULL)
				break;
		}
		if (cur == NULL)
			break;
		tmpCharPtr = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		certList[i] = (BYTE *)zMalloc(strlen((const char *)tmpCharPtr) + 1);
		strcpy((char *)certList[i], (const char *)tmpCharPtr);
		xmlFree(tmpCharPtr);
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	if (i != *certificateCount) // Something was wrong
	{
		for (UINT j=0; j<*certificateCount; j++)
		{
			if (certList[j] != NULL)
				zFree(certList[j]);
		}
		zFree(certList);
		certList = NULL;
		setError(SigHandle, CERT_PARTIAL_CHAIN);
	}
	ExitObjectLog;
	return certList;
}

STDMETHODIMP CSignature::put_SignerCertificateChain(BSTR newVal)
{
	unsigned char *ptr=NULL, *newPtr=NULL; 
	unsigned int sizeM;
	EnterObjectLog;
	if (signerCertChain != NULL)
	{
		zFree(signerCertChain);
		signerCertChain = NULL;
		signerCertChainSize = 0;
	}
	if ((newVal != NULL) && (SysStringByteLen(newVal) != 0))
	{
		ptr = HeapW2A(newVal);
		sizeM = strlen((const char *)ptr);
		sizeM = base64decodeSize(sizeM);
		newPtr = (unsigned char *)zMalloc(sizeM+1);
		if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
		{
			zFree(ptr);
			zFree(newPtr);
			setError(SigHandle, BASE64_ERROR);
			ExitObjectLog;
			return S_FALSE;
		}
		zFree(ptr);
		signerCertChain = newPtr;
		signerCertChainSize = sizeM;
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_SignatureImageId(BSTR* pVal)
{
	*pVal = A2WBSTR((LPCSTR)SigImageGuid.c_str());
	return S_OK;
}

STDMETHODIMP CSignature::put_SignatureImageId(BSTR newVal)
{
	char *charGuid=NULL;

	charGuid = (char *)HeapW2A(newVal);
	SigImageGuid = charGuid;
	zFree(charGuid);
	return S_OK;
}

STDMETHODIMP CSignature::SignSignedInfoDigest(BSTR b64CertData, BSTR b64SignedInfoDigest, BSTR* b64SigValXml)
{
	PDS_DATA_BLOB pcrBlob=NULL;	// <SignedInfo> data
	BYTE *pbHash;				// SHA1 hash
	DWORD dwHashLen=20;			// 
	PBYTE pbSignature=NULL;		// signature BLOB
	DWORD dwSigLen=0;			// signature BLOB
	PBYTE pbPublicKey=NULL;		// (out) pub key BLOB
	DWORD dwKeyLen=0;			// (out) pub key BLOB
	DWORD sigalgtype=0;
	unsigned char *certData=NULL;	// base64 encoded certData
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL, rootNode=NULL, parent=NULL;
	xmlChar *mem=NULL;
	int iSize=0;
	unsigned char *b64Pubkey=NULL, *b64SigVal=NULL, *b64Hash=NULL;
	unsigned char *pbData=NULL;
	unsigned int cbData=0;
	char buffer[20];
	HRESULT result = S_FALSE;
	unsigned char **certificateList=NULL;
	UINT certificateListCount=0;
	BOOL freeSigningCert=FALSE;

	*b64SigValXml = NULL;
	EnterObjectLog;

	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		ExitObjectLog;
		return S_FALSE;
	}

	if (!LicObj.getSignAllowed()) {
		setError(SigHandle, NO_SIGNING_LIC);
		ExitObjectLog;
		return S_FALSE;
	}

	if ((b64SignedInfoDigest == 0) ||
		(SysStringByteLen(b64SignedInfoDigest) == 0))
	{
		setError(SigHandle, NULL_DATA_STRING);
		ExitObjectLog;
		return S_FALSE;
	}

	if ((b64CertData == NULL) || 
		(SysStringByteLen(b64CertData) == 0))
	{
		if ((CurrentCertificate == NOT_INITIALIZED)	&& (CertificateCount != 0))
		{
#ifdef WIN32
			certData = (unsigned char *)dlg->selectCertificate();
#endif
			if (certData != NULL)
			{
				for (int i=0;i<CertificateCount;i++)
				{
					if (!(StrCmp((const char *)cV[i]->certificate, (const char *)certData)))
					{
						CurrentCertificate = i;
						break;
					}
				}
#ifdef WIN32
				if ((UsingNetscape) && (nsCertStoreObj != NULL))
				{
					BSTR pfxX509Cert;
					_bstr_t pfxFilePath = nsCertStoreObj->ExportNetscapeCert(_bstr_t(cV[CurrentCertificate]->serialNumber));
					SetActivePFXFileCert(pfxFilePath, nsStorePassword, &pfxX509Cert);
					certData = B64PfxDataPtr;
					DeleteFile((LPCTSTR)(char *)pfxFilePath);
				}
#endif
			}
		}
		else
			if (CurrentCertificate == USE_PFX_CERT)
				certData = B64PfxDataPtr;
			else
				if (CurrentCertificate == USE_BASE64_CERT)
				{
					freeSigningCert = TRUE;
					certData = (unsigned char *)HeapW2A(SignerCertificate.m_str);
				}
				else
					if ((CurrentCertificate >= 0) && (cV != NULL) && (cV[CurrentCertificate] != NULL))
						certData = cV[CurrentCertificate]->certificate;
	}
	else
	{
		certData	= HeapW2A(b64CertData);
		if (certData != NULL)
			freeSigningCert = TRUE;
	}


	if (certData == NULL)
	{
		setError(SigHandle, NO_CERTIFICATE);
		ExitObjectLog;
		return FALSE;
	}

	b64Hash		= HeapW2A(b64SignedInfoDigest);

	// Base64 decode b64Hash
	unsigned int b64HashSize = strlen((const char *)b64Hash);
	cbData = base64decodeSize(b64HashSize);
	pbHash = (unsigned char *)zMalloc(cbData+1);
	if ((cbData = base64decode(b64Hash, pbHash, cbData+1)) == -1)
	{
		setError(SigHandle, BASE64_ERROR);
		if (freeSigningCert == TRUE)
			zFree(certData);
		zFree(b64Hash);
		zFree(pbHash);
		ExitObjectLog;
		return S_FALSE;
	}
	zFree(b64Hash);

#ifdef NSS
	SECItem si;
	si.data = PfxPassword.pbData;
	si.len = PfxPassword.cbData;
	certificateList = crGetSignerCertChain(	certData,
										&si,
										&certificateListCount,
										SigHandle);
#else
	certificateList = crGetSignerCertChain(	certData,
										(LPWSTR)PfxPassword.pbData,
										&certificateListCount,
										SigHandle);
#endif
	if ((certificateList == NULL) || (certificateListCount == 0))
	{
		setError(SigHandle, CERT_CHAIN_ERROR);
		if (freeSigningCert == TRUE)
			zFree(certData);
		zFree(pbHash);
		ExitObjectLog;
		return S_FALSE;
	}

    /*
	 * Two steps Sign-On-Client. First call must return FALSE.
	 */
	xsSignOnClient(
		(const char *)certData,		// certificate to sign
		pbHash,				// <SignedInfo> hash
		pbSignature,		// (out) signature BLOB
		&dwSigLen,			// (out) signature BLOB
		pbPublicKey,		// (out) pub key BLOB
		&dwKeyLen,			// (out) pub key BLOB
		&PfxPassword,		// if signingCert is NULL, it is HMAC key, if certData is Pfx it is the password
		&sigalgtype,
		SigHandle
		);
	cleanupError(SigHandle);
	// allocate memory for signature and key
	pbSignature = (PBYTE)zMalloc(dwSigLen);
	pbPublicKey = (PBYTE)zMalloc(dwKeyLen);

	if (!xsSignOnClient(
		(const char *)certData,		// certificate to sign
		pbHash,				// <SignedInfo> hash
		pbSignature,		// (out) signature BLOB
		&dwSigLen,			// (out) signature BLOB
		pbPublicKey,		// (out) pub key BLOB
		&dwKeyLen,			// (out) pub key BLOB
		&PfxPassword,		// if signingCert is NULL, it is HMAC key, if certData is Pfx it is the password
		&sigalgtype,
		SigHandle
		))
	{
		if (freeSigningCert == TRUE)
			zFree(certData);
		zFree(pbHash);
		zFree(pbSignature);
		zFree(pbPublicKey);
		ExitObjectLog;
		return S_FALSE;
	}

	zFree(pbHash);

	// Lets base64 encode the signature value and public key values
	cbData = base64encodeSize(dwSigLen);
	b64SigVal = (unsigned char *)zMalloc(cbData+1);
	if ((cbData = base64encode(pbSignature, dwSigLen, b64SigVal, cbData+1)) == -1)
	{
		setError(SigHandle, BASE64_ERROR);
		zFree(pbSignature);
		zFree(pbPublicKey);
		zFree(b64SigVal);
		ExitObjectLog;
		return S_FALSE;
	}
	*(b64SigVal + cbData) = '\0';
	zFree(pbSignature);

	cbData = base64encodeSize(dwKeyLen);
	b64Pubkey = (unsigned char *)zMalloc(cbData+1);
	if ((cbData = base64encode(pbPublicKey, dwKeyLen, b64Pubkey, cbData+1)) == -1)
	{
		setError(SigHandle, BASE64_ERROR);
		zFree(pbSignature);
		zFree(pbPublicKey);
		zFree(b64Pubkey);
		zFree(b64SigVal);
		ExitObjectLog;
		return S_FALSE;
	}
	*(b64Pubkey + cbData) = '\0';
	zFree(pbPublicKey);

	doc = xmlNewDoc((const unsigned char *)"1.0");
	// document, namespace, element name, element content
	cur = xmlNewDocNode(doc,NULL,(const unsigned char *)"SignedInfoSignature",NULL);

	// add root element
	xmlDocSetRootElement(doc,cur);
	rootNode = cur;
	cur = xmlNewNode(NULL,(const unsigned char *)"SignatureValue");
	xmlNodeSetContent(cur,(const unsigned char *)b64SigVal);
	cur = xmlAddChild(rootNode, cur);

	cur = xmlNewNode(NULL,(const unsigned char *)"PublicKeyValue");
	xmlNodeSetContent(cur,(const unsigned char *)b64Pubkey);
	cur = xmlAddChild(rootNode, cur);

	cur = xmlNewNode(NULL,(const unsigned char *)"AlgorithmType");
	sprintf((char *)buffer, "%d", sigalgtype);
	xmlNodeSetContent(cur,(const unsigned char *)buffer);
	cur = xmlAddChild(rootNode, cur);

	cur = xmlNewNode(NULL,(const unsigned char *)"CertificateChainLength");
	sprintf((char *)buffer, "%d", certificateListCount);
	xmlNodeSetContent(cur,(const unsigned char *)buffer);
	cur = xmlAddChild(rootNode, cur);

	for (UINT i=0; i<certificateListCount; i++)
	{
		if (certificateList[i] != NULL)
		{
			cur = xmlNewNode(NULL,(const unsigned char *)"X509Certificate");
			xmlNodeSetContent(cur,(const unsigned char *)certificateList[i]);
			cur = xmlAddChild(rootNode, cur);
			zFree(certificateList[i]);
		}
	}
	zFree(certificateList);

	xmlDocDumpMemory(doc,&mem,(int *)&iSize);
	xmlFreeDoc(doc);

	zFree(b64Pubkey);
	zFree(b64SigVal);
	if (freeSigningCert == TRUE)
		zFree(certData);

	cbData = base64encodeSize(iSize);
	if(!(pbData = (BYTE *)zMalloc(cbData+1)))
	{
		xmlFree(mem);
		setError(SigHandle, MEMORY_FAULT);
		ExitObjectLog;
		return FALSE;
	}
	if ((cbData  = base64encode(mem,iSize,(unsigned char*)pbData,cbData+1))==-1) 
	{
		setError(SigHandle, BASE64_ERROR);
		xmlFree(mem);
		zFree(pbData);
		ExitObjectLog;
		return FALSE;
	}
	*(pbData+cbData)='\0';
	*b64SigValXml = A2WBSTR((LPCSTR)pbData, cbData);
	zFree(pbData);
	xmlFree(mem);

	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::ApplySignatureValue(BSTR b64SigValXml, BSTR* signedXML)
{
	xmlDocPtr doc;
	xmlNodePtr cur=NULL, root=NULL;
	unsigned char *tmpCharPtr=NULL;
	BYTE **certificateList=NULL, **oldCertificateList=NULL;
	UINT i=0;
	unsigned char *ptr=NULL, *newPtr=NULL; 
	unsigned int sizeM;
	int iSize;
	PBYTE pbSignature=NULL;		// signature BLOB
	DWORD dwSigLen=0;			// signature BLOB
	PBYTE pbPublicKey=NULL;		// (out) pub key BLOB
	DWORD dwKeyLen=0;			// (out) pub key BLOB
	DWORD sigalgtype=0;
//	unsigned char *certData=NULL;	// base64 encoded certData
	unsigned int cbData=0;
	unsigned char *pbData=NULL;
	int certListIndex=0, certificateListCount=0, oldCertificateListCount=0;
	BOOL result=0;
	keyinfo *ki = NULL;
	x509data *curX509Data = NULL;
	x509group *curX509Group = NULL;
	*signedXML = NULL;

	EnterObjectLog;

	if ((b64SigValXml == NULL) || 
		(SysStringByteLen(b64SigValXml) == 0))
	{
		setError(SigHandle, NULL_DATA_STRING);
		ExitObjectLog;
		return S_FALSE;
	}

	// Base64 decode b64SigValXml
	ptr = HeapW2A(b64SigValXml);
	sizeM = strlen((const char *)ptr);
	sizeM = base64decodeSize(sizeM);
	newPtr = (unsigned char *)zMalloc(sizeM+1);
	if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
	{
		zFree(ptr);
		zFree(newPtr);
		setError(SigHandle, BASE64_ERROR);
		ExitObjectLog;
		return S_FALSE;
	}
	zFree(ptr);

	if ((doc = xmlParseMemory((const char *)newPtr, sizeM)) == NULL)
	{
		zFree(newPtr);
		ExitObjectLog;
		return S_FALSE;
	}
	zFree(newPtr);

	root = xmlDocGetRootElement(doc);
	cur = root->xmlChildrenNode;
	if (cur == NULL)
	{
		xmlFreeDoc(doc);
		ExitObjectLog;
		return S_FALSE;
	}
	while (cur)
	{
		if (!xmlStrcmp(cur->name, (const unsigned char *)"SignatureValue"))
		{
			tmpCharPtr = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			sizeM = strlen((const char *)tmpCharPtr);
			sizeM  = base64decodeSize(sizeM);
			pbSignature = (PBYTE)zMalloc(sizeM+1);
			if ((dwSigLen = base64decode(tmpCharPtr, pbSignature, sizeM+1)) == -1)
			{
				setError(SigHandle, BASE64_ERROR);
				zFree(pbSignature);
				xmlFree(tmpCharPtr);
				ExitObjectLog;
				return S_FALSE;
			}
			xmlFree(tmpCharPtr);
		}
		if (!xmlStrcmp(cur->name, (const unsigned char *)"PublicKeyValue"))
		{
			tmpCharPtr = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			sizeM = strlen((const char *)tmpCharPtr);
			sizeM  = base64decodeSize(sizeM);
			pbPublicKey = (PBYTE)zMalloc(sizeM+1);
			if ((dwKeyLen = base64decode(tmpCharPtr, pbPublicKey, sizeM+1)) == -1)
			{
				setError(SigHandle, BASE64_ERROR);
				zFree(pbPublicKey);
				xmlFree(tmpCharPtr);
				ExitObjectLog;
				return S_FALSE;
			}
			xmlFree(tmpCharPtr);
		}
		if (!xmlStrcmp(cur->name, (const unsigned char *)"AlgorithmType"))
		{
			tmpCharPtr = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			sigalgtype = (DWORD)atoi((const char *)tmpCharPtr);
			xmlFree(tmpCharPtr);
		}
		if (!xmlStrcmp(cur->name, (const unsigned char *)"CertificateChainLength"))
		{
			tmpCharPtr = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			certificateListCount = (DWORD)atoi((const char *)tmpCharPtr);
			xmlFree(tmpCharPtr);
			certificateList = (BYTE **)zMalloc(sizeof(BYTE *) * certificateListCount);
			memset(certificateList, 0, certificateListCount * sizeof(BYTE *));
			certListIndex = 0;
		}
		if (!xmlStrcmp(cur->name, (const unsigned char *)"X509Certificate"))
		{
			tmpCharPtr = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			certificateList[certListIndex++] = tmpCharPtr;
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	oldCertificateList = getSignerCertChain((UINT *)&oldCertificateListCount);
	if ((oldCertificateList != NULL) && (oldCertificateListCount != 0))
	{ // Make sure that the certificates used during signing are the same as the ones provided during digest calculation
		if  (oldCertificateListCount == certificateListCount)
		{
			for (int i=0; i<certificateListCount; i++)
			{
				if (strcmp((const char *)oldCertificateList[i], (const char *)certificateList[i]))
				{// The chain provided during digest calculation != chain captured during signing
					for (int j=0; j<certificateListCount; j++)
						if (certificateList[j]) xmlFree(certificateList[j]);
					zFree(certificateList);
					for (int j=0; j<oldCertificateListCount; j++)
						if (oldCertificateList[j]) xmlFree(oldCertificateList[j]);
					zFree(oldCertificateList);
					setError(SigHandle, CERT_INVALID_CHAIN);
					if (pbSignature) zFree(pbSignature);
					if (pbPublicKey) zFree(pbPublicKey);
					ExitObjectLog;
					return S_FALSE;
				}
			}
			// The chain is identical to the one provided during digest calculation so there is no need to process it again
			for (int j=0; j<oldCertificateListCount; j++)
				if (oldCertificateList[j]) xmlFree(oldCertificateList[j]);
			zFree(oldCertificateList);
		}
		else
		{// The chain does not have the same number of cretificates as provided during digest calculation.
			for (int i=0; i<certificateListCount; i++)
				if (certificateList[i]) xmlFree(certificateList[i]);
			zFree(certificateList);
			for (int i=0; i<oldCertificateListCount; i++)
				if (oldCertificateList[i]) xmlFree(oldCertificateList[i]);
			zFree(oldCertificateList);
			setError(SigHandle, CERT_INVALID_CHAIN);
			if (pbSignature) zFree(pbSignature);
			if (pbPublicKey) zFree(pbPublicKey);
			ExitObjectLog;
			return S_FALSE;
		}
	}
	else
	{// There was no Certificate Chain provided during digest calculation so lets process them here now.
		if ((CertVerifyParams.usedCrlCount != 0) &&
			(CertVerifyParams.usedCrlList != NULL))
		{
			for (UINT i=0; i < CertVerifyParams.usedCrlCount; i++)
			{
				if (CertVerifyParams.usedCrlList[i] != NULL)
					zFree(CertVerifyParams.usedCrlList[i]);
			}
			zFree(CertVerifyParams.usedCrlList);
			CertVerifyParams.usedCrlList = NULL;
			CertVerifyParams.usedCrlCount = 0;
		}

		if (((CertVerifyParams.verificationOptions & (~VERIFY_CRL_REC)) || (useCam) || (useOcsp)) &&
			(certificateList != NULL))
		{
			SYSTEMTIME	tsSysTime;
#ifdef WIN32
			GetSystemTime(&tsSysTime);
#else
			GetSystemTimeLinux(&tsSysTime);
#endif
			if (useCam)
				result = crVerifyCertificateUsingCam(certificateList,
									certificateListCount,
									&tsSysTime, 
									(LPWSTR)PfxPassword.pbData, 
									&CertVerifyParams,
									SigHandle);
			else
				if (useOcsp)
					result = crVerifyCertificateUsingOcsp(certificateList,
										certificateListCount,
										&tsSysTime, 
										(LPWSTR)PfxPassword.pbData, 
										&CertVerifyParams,
										SigHandle);
				else {
#ifdef NSS
					SECItem s;
					s.data = PfxPassword.pbData;
					s.len  = PfxPassword.cbData;
					result = crVerifyCertificate(certificateList,
										certificateListCount,
										&tsSysTime, 
										&s, 
										&CertVerifyParams,
										SigHandle);
#else
					result = crVerifyCertificate(certificateList,
										certificateListCount,
										&tsSysTime, 
										(LPWSTR)PfxPassword.pbData, 
										&CertVerifyParams,
										SigHandle);
#endif
				}
			if (result == FALSE)
			{
				for (i=0; i < (UINT) certificateListCount; i++)
				{
					xmlFree(certificateList[i]);
				}
				zFree(certificateList);
				if (pbSignature) zFree(pbSignature);
				if (pbPublicKey) zFree(pbPublicKey);
				ExitObjectLog;
				return S_FALSE;
			}
		}

		/*
		* set <X509Data> certificate
		*/
		if (ExcludeSignerCertificateFlag != 1)// Either include the whole chain or just the end certificate
		{
			ki = xsCoreAddKeyInfo(SigHandle);
			curX509Data = xsCoreAddX509Data(ki, SigHandle);

			if (ExcludeSignerCertificateFlag == 0)// Include the whole chain of certificates
			{
				for (i=0; i < (UINT) certificateListCount; i++)
				{
					char *crlData = NULL;

					curX509Group = xsCoreAddX509Group(curX509Data, SigHandle);
					if ((IncludeCRLInSignature == TRUE) && (CertVerifyParams.usedCrlCount != 0))
					{
						crlData = CertVerifyParams.usedCrlList[i];
					}

					if (xsCoreSetX509Group(curX509Group,NULL,NULL,(char *)certificateList[i],crlData, NULL, NULL, SigHandle)!=TRUE)
					{
						for (int j=0; j < certificateListCount; j++)
						{
							xmlFree(certificateList[j]);
						}
						zFree(certificateList);
						if (pbSignature) zFree(pbSignature);
						if (pbPublicKey) zFree(pbPublicKey);
						ExitObjectLog;
						return FALSE;
					}
				}
			}
			if (ExcludeSignerCertificateFlag == 2) //Just include the signer end certificate
			{
				char *crlData = NULL;
				curX509Group = xsCoreAddX509Group(curX509Data, SigHandle);
				if ((IncludeCRLInSignature == TRUE) && (CertVerifyParams.usedCrlCount != 0))
				{
					crlData = CertVerifyParams.usedCrlList[0];
				}
				if (xsCoreSetX509Group(curX509Group,NULL,NULL,(char *)certificateList[0],crlData, NULL, NULL, SigHandle)!=TRUE)
				{
					for (int j=0; j < certificateListCount; j++)
					{
						xmlFree(certificateList[j]);
					}
					zFree(certificateList);
					if (pbSignature) zFree(pbSignature);
					if (pbPublicKey) zFree(pbPublicKey);
					ExitObjectLog;
					return FALSE;
				}
			}
		} // ExcludeSignerCertificateFlag != 1
	}

	/*
	 * Generate other XML sections
	 */
	if (!xsAcceptSignature(
		(const char *)certificateList[0],
		pbSignature,			// signature
		dwSigLen,				// signature size
		pbPublicKey,			// public key
		dwKeyLen,				// public key size
		sigalgtype,
		SigHandle
		))
	{
		if (certificateList != NULL)
		{
			for (int i=0; i<certificateListCount; i++)
				if (certificateList[i]) xmlFree(certificateList[i]);
			zFree(certificateList);
		}
		if (pbSignature) zFree(pbSignature);
		if (pbPublicKey) zFree(pbPublicKey);
		ExitObjectLog;
		return S_FALSE;
	}
	if (certificateList != NULL)
	{
		for (int i=0; i<certificateListCount; i++)
			if (certificateList[i]) xmlFree(certificateList[i]);
		zFree(certificateList);
	}

	if (pbSignature) zFree(pbSignature);
	if (pbPublicKey) zFree(pbPublicKey);

	/*
	 * get result XML as string and save it
	 */
	char *xsignature = (char *)xsCoreGenerateXMLSec(SigHandle, &iSize);
	if (Base64EncodeXML == FALSE)
		*signedXML = A2WBSTR((LPCSTR)xsignature, iSize);
	else
	{
		int srcSize;
		unsigned int cbData;
		unsigned char *pbData;
		srcSize = iSize;
		cbData = base64encodeSize(srcSize);

		if(!(pbData = (BYTE *)zMalloc(cbData+1)))
		{
			xmlFree(xsignature);
			setError(SigHandle, MEMORY_FAULT);
			ExitObjectLog;
			return S_FALSE;
		}
		if ((cbData  = base64encode((unsigned char *)xsignature,srcSize,(unsigned char*)pbData,cbData+1))==-1) 
		{
			setError(SigHandle, BASE64_ERROR);
			xmlFree(xsignature);
			zFree(pbData);
			ExitObjectLog;
			return S_FALSE;
		}
		*signedXML = A2WBSTR((LPCSTR)pbData,cbData);
		zFree(pbData);
	}
	xmlFree(xsignature);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::GetSignedInfoDigestFromByteArray(VARIANT xmlByteArray, 
														  BSTR signatureId, 
														  BSTR* signedInfoDigest)
{
	char *charXMLStr=NULL, *charSigId=NULL, *curCharSigId=NULL;
	unsigned char *charSignedInfoDigest=NULL;
	xmlDocPtr doc =NULL;
	xmlNodePtr root=NULL, cur=NULL, parent=NULL, sigNode=NULL, signedInfoNode=NULL;
	xmlChar *mem=NULL;
	int iSize=0;
	CComBSTR	sigId;
	char *ptemp=NULL;
#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char guidStr[50];
	BOOL templateFound=FALSE;

	CBufferVariant m_binaryData;
	VARIANT *inputByteArray;
	EnterObjectLog;

	if (! LicObj.checkLicense()) {
		setError(SigHandle, INVALID_SECUREXML_LIC);
		ExitObjectLog;
		return S_FALSE;
	}

	if (xmlByteArray.vt == (VT_VARIANT | VT_BYREF))
	{
		inputByteArray = xmlByteArray.pvarVal;
	}
	else
		inputByteArray = &xmlByteArray;

	if (inputByteArray->vt != (VT_ARRAY | VT_UI1))
	{
		setError(SigHandle, INVALID_VARIANT);
		*signedInfoDigest = NULL;
		ExitObjectLog;
		return S_FALSE;
	}

	m_binaryData = xmlByteArray;

	char *dataPtr = (char *)m_binaryData;
	UINT dwFileSize = (UINT) m_binaryData.GetLength();
	if (! LicObj.getSignAllowed()) 
	{
		if (!LicObj.getFormSignAllowed((unsigned char *)dataPtr, dwFileSize, SigHandle))
		{
			setError(SigHandle, NO_SIGNING_LIC);
			ExitObjectLog;
			return S_FALSE;
		}
	}

	// original document
	doc = xmlParseMemory((const char *)dataPtr,dwFileSize);
	if (!doc) 
	{
		setError(SigHandle, XML_PARSER_ERROR);
		ExitObjectLog;
		return S_FALSE;
	}

	if (sgArr != NULL)
	{
		if (uriArr != NULL)
			FreeUriArr();
		sgArr = NULL;
		signum = 0;
	}

	USES_CONVERSION;

	BOOL freeCharSigId = FALSE;
	sigId = signatureId;
	if (sigId.Length() == 0)
		charSigId = NULL;
	else
	{
		charSigId = (char *)HeapW2A(signatureId);
		freeCharSigId = TRUE;
	}

	if (charSigId == NULL)
		if (SignatureID.Length() == 0)
		{
//#ifdef WIN32
//			CoCreateGuid(&sigGuid);
//			GuidToString(&sigGuid, guidStr);
//#else
//			uuid_generate(sigGuid);
//			uuid_unparse(sigGuid, guidStr);
//#endif
//			charSigId = guidStr;
		}
		else
		{
			charSigId = (char *)HeapW2A(SignatureID.m_str);
			freeCharSigId = TRUE;
		}

	  root = xmlDocGetRootElement(doc);
//	  cur = root->xmlChildrenNode;

	if (charSigId != NULL)
		sigNode = xsSigNodeById((const xmlNodePtr) root, (const xmlChar *)charSigId);
	else
		sigNode = xsSigNodeWithNoIdNoSigValue((const xmlNodePtr) root);
	if (sigNode != NULL)
	{
		templateFound = TRUE;
		cur = sigNode->xmlChildrenNode;
		while (cur)
		{
				if (!(xmlStrcmp(cur->name, (const xmlChar *) "SignedInfo")))
				{
					signedInfoNode = cur;
					break;
				}
				cur = cur->next;
		}  // end while cur != NULL
	}
	cur = root->xmlChildrenNode;

	  if (templateFound == FALSE) // A Signature element with matching Id was not found
	  {
		  // Add a new Signature element

		/*
		* Signature
		*/

		cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
		sigNode = cur;
		if (charSigId != NULL)
			xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
		cur = xmlAddChild(root,cur);
		//xmlNewNs(cur,(const unsigned char *)"http://www.w3.org/2000/09/xmldsig#",(const unsigned char *)NULL);

		xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)NULL);
		parent = cur;

		/*
		* SignedInfo
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
		signedInfoNode = cur;
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		 * Canonicalization Method
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
		switch(CanonicalizationMethod)
		{
			case WITH_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
				break;
			case WITHOUT_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
				break;
			case EXC_WITH_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
				break;
			case EXC_WITHOUT_COMMENTS:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
				break;
			default:
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
		}
		cur = xmlAddChild(parent,cur);
		if (signerCertChain == NULL)
		{//We assume RSA Algorithm will be used if no signer certificate info is provided
			cur = xmlNewNode(NULL, (const unsigned char *)"SignatureMethod");
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_RSAWITHSHA1);
			cur = xmlAddChild(parent, cur);
		}
		/*
		* Reference
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
		cur = xmlAddChild(parent,cur);
		xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)"");
		parent = cur;

		/*
		* Transforms
		*/
	
		cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		* Transform
		*/
		if ((CanonicalizationMethod == EXC_WITH_COMMENTS) ||
			(CanonicalizationMethod == EXC_WITHOUT_COMMENTS))
		{
			cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			}
			cur = xmlAddChild(parent,cur);
			parent = cur;
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_WITH_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_NO_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			cur = xmlAddChild(parent,cur);
			parent = parent->parent;
		}

		/*
		* Transform
		*/

		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_ENVELOPED_SIG);
		cur = xmlAddChild(parent,cur);		
	  }
#ifdef WIN32
	  if (PhysicalSigUsage != NO_PHYSICAL_SIG)		  
		  AddPhysicalSignature(sigNode, signedInfoNode, charSigId);
#endif
	/*
	 * init Signature. crBlob contains XML - envelope document
	 */
	short tmpEnvFlag = EnvelopingFlag;
	EnvelopingFlag = ENVELOPED;

	calculateDigestOnly = TRUE;
	if (!(CreateSigFromTmplBlob(doc, charSigId, &charSignedInfoDigest, &iSize)))
	{
		if (charSignedInfoDigest != NULL)
		{
			zFree(charSignedInfoDigest);
		}
		EnvelopingFlag = tmpEnvFlag;
		*signedInfoDigest = NULL;
		calculateDigestOnly = FALSE;
		if (freeCharSigId)
			zFree(charSigId);
		ExitObjectLog;
		return S_FALSE;
	}
	else
	{
		if (charSignedInfoDigest != NULL)
		{
			unsigned int cbData;
			unsigned char *pbData;
			cbData = base64encodeSize(iSize);
			pbData = (unsigned char *)zMalloc(cbData+1);
			if ((cbData = base64encode(charSignedInfoDigest, iSize, pbData, cbData+1)) == -1)
			{
				setError(SigHandle, BASE64_ERROR);
				zFree(pbData);
				zFree(charSignedInfoDigest);
				calculateDigestOnly = FALSE;
				if (freeCharSigId)
					zFree(charSigId);
				ExitObjectLog;
				return S_FALSE;
			}
			zFree(charSignedInfoDigest);
			*signedInfoDigest = A2WBSTR((LPCSTR) pbData, cbData);
			zFree(pbData);
		}
	}
	EnvelopingFlag = tmpEnvFlag;
	calculateDigestOnly = FALSE;
	if (freeCharSigId)
		zFree(charSigId);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::ApplySignatureValueGetByteArray(BSTR b64SigValXml, VARIANT* signedXmlByteArray)
{
	xmlDocPtr doc;
	xmlNodePtr cur=NULL, root=NULL;
	unsigned char *tmpCharPtr=NULL;
	BYTE **certList=NULL;
	UINT i=0;
	unsigned char *ptr=NULL, *newPtr=NULL; 
	unsigned int sizeM;
	int iSize;
	PBYTE pbSignature=NULL;		// signature BLOB
	DWORD dwSigLen=0;			// signature BLOB
	PBYTE pbPublicKey=NULL;		// (out) pub key BLOB
	DWORD dwKeyLen=0;			// (out) pub key BLOB
	DWORD sigalgtype=0;
//	unsigned char *certData=NULL;	// base64 encoded certData
	unsigned int cbData=0;
	unsigned char *pbData=NULL;
	CBufferVariant m_binaryData;
	BYTE **certificateList=NULL, **oldCertificateList=NULL;
	int certListIndex=0, certificateListCount=0, oldCertificateListCount=0;
	BOOL result=0;
	keyinfo *ki = NULL;
	x509data *curX509Data = NULL;
	x509group *curX509Group = NULL;

	EnterObjectLog;

	m_binaryData.SetLength(0);
	*signedXmlByteArray = m_binaryData.Copy();

	if ((b64SigValXml == NULL) || 
		(SysStringByteLen(b64SigValXml) == 0))
	{
		setError(SigHandle, NULL_DATA_STRING);
		ExitObjectLog;
		return S_FALSE;
	}

	// Base64 decode b64SigValXml
	ptr = HeapW2A(b64SigValXml);
	sizeM = strlen((const char *)ptr);
	sizeM = base64decodeSize(sizeM);
	newPtr = (unsigned char *)zMalloc(sizeM+1);
	if ((sizeM = base64decode(ptr,newPtr,sizeM+1))==-1)
	{
		zFree(ptr);
		zFree(newPtr);
		setError(SigHandle, BASE64_ERROR);
		ExitObjectLog;
		return S_FALSE;
	}
	zFree(ptr);

	if ((doc = xmlParseMemory((const char *)newPtr, sizeM)) == NULL)
	{
		zFree(newPtr);
		ExitObjectLog;
		return S_FALSE;
	}
	zFree(newPtr);

	root = xmlDocGetRootElement(doc);
	cur = root->xmlChildrenNode;
	if (cur == NULL)
	{
		xmlFreeDoc(doc);
		ExitObjectLog;
		return S_FALSE;
	}

	while (cur)
	{
		if (!xmlStrcmp(cur->name, (const unsigned char *)"SignatureValue"))
		{
			tmpCharPtr = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			sizeM = strlen((const char *)tmpCharPtr);
			sizeM  = base64decodeSize(sizeM);
			pbSignature = (PBYTE)zMalloc(sizeM+1);
			if ((dwSigLen = base64decode(tmpCharPtr, pbSignature, sizeM+1)) == -1)
			{
				setError(SigHandle, BASE64_ERROR);
				zFree(pbSignature);
				xmlFree(tmpCharPtr);
				ExitObjectLog;
				return S_FALSE;
			}
			xmlFree(tmpCharPtr);
		}
		if (!xmlStrcmp(cur->name, (const unsigned char *)"PublicKeyValue"))
		{
			tmpCharPtr = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			sizeM = strlen((const char *)tmpCharPtr);
			sizeM  = base64decodeSize(sizeM);
			pbPublicKey = (PBYTE)zMalloc(sizeM+1);
			if ((dwKeyLen = base64decode(tmpCharPtr, pbPublicKey, sizeM+1)) == -1)
			{
				setError(SigHandle, BASE64_ERROR);
				zFree(pbPublicKey);
				xmlFree(tmpCharPtr);
				ExitObjectLog;
				return S_FALSE;
			}
			xmlFree(tmpCharPtr);
		}
		if (!xmlStrcmp(cur->name, (const unsigned char *)"AlgorithmType"))
		{
			tmpCharPtr = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			sigalgtype = (DWORD)atoi((const char *)tmpCharPtr);
			xmlFree(tmpCharPtr);
		}
		if (!xmlStrcmp(cur->name, (const unsigned char *)"CertificateChainLength"))
		{
			tmpCharPtr = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			certificateListCount = (DWORD)atoi((const char *)tmpCharPtr);
			xmlFree(tmpCharPtr);
			certificateList = (BYTE **)zMalloc(sizeof(BYTE *) * certificateListCount);
			memset(certificateList, 0, certificateListCount * sizeof(BYTE *));
			certListIndex = 0;
		}
		if (!xmlStrcmp(cur->name, (const unsigned char *)"X509Certificate"))
		{
			tmpCharPtr = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			certificateList[certListIndex++] = tmpCharPtr;
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	oldCertificateList = getSignerCertChain((UINT *)&oldCertificateListCount);

	if ((oldCertificateList != NULL) && (oldCertificateListCount != 0))
	{ // Make sure that the certificates used during signing are the same as the ones provided during digest calculation
		if  (oldCertificateListCount == certificateListCount)
		{
			for (int i=0; i<certificateListCount; i++)
			{
				if (strcmp((const char *)oldCertificateList[i], (const char *)certificateList[i]))
				{// The chain provided during digest calculation != chain captured during signing
					for (int j=0; j<certificateListCount; j++)
						if (certificateList[j]) xmlFree(certificateList[j]);
					zFree(certificateList);
					for (int j=0; j<oldCertificateListCount; j++)
						if (oldCertificateList[j]) xmlFree(oldCertificateList[j]);
					zFree(oldCertificateList);
					setError(SigHandle, CERT_INVALID_CHAIN);
					if (pbSignature) zFree(pbSignature);
					if (pbPublicKey) zFree(pbPublicKey);
					ExitObjectLog;
					return S_FALSE;
				}
			}
			// The chain is identical to the one provided during digest calculation so there is no need to process it again
			for (int j=0; j<oldCertificateListCount; j++)
				if (oldCertificateList[j]) xmlFree(oldCertificateList[j]);
			zFree(oldCertificateList);
		}
		else
		{// The chain does not have the same number of cretificates as provided during digest calculation.
			for (int i=0; i<certificateListCount; i++)
				if (certificateList[i]) xmlFree(certificateList[i]);
			zFree(certificateList);
			for (int i=0; i<oldCertificateListCount; i++)
				if (oldCertificateList[i]) xmlFree(oldCertificateList[i]);
			zFree(oldCertificateList);
			setError(SigHandle, CERT_INVALID_CHAIN);
			if (pbSignature) zFree(pbSignature);
			if (pbPublicKey) zFree(pbPublicKey);
			ExitObjectLog;
			return S_FALSE;
		}
	}
	else
	{// There was no Certificate Chain provided during digest calculation so lets process them here now.
		if ((CertVerifyParams.usedCrlCount != 0) &&
			(CertVerifyParams.usedCrlList != NULL))
		{
			for (UINT i=0; i < CertVerifyParams.usedCrlCount; i++)
			{
				if (CertVerifyParams.usedCrlList[i] != NULL)
					zFree(CertVerifyParams.usedCrlList[i]);
			}
			zFree(CertVerifyParams.usedCrlList);
			CertVerifyParams.usedCrlList = NULL;
			CertVerifyParams.usedCrlCount = 0;
		}

		if (((CertVerifyParams.verificationOptions & (~VERIFY_CRL_REC)) || (useCam) || (useOcsp)) &&
			(certificateList != NULL))
		{
			SYSTEMTIME	tsSysTime;
#ifdef WIN32
			GetSystemTime(&tsSysTime);
#else
			GetSystemTimeLinux(&tsSysTime);
#endif
			if (useCam)
				result = crVerifyCertificateUsingCam(certificateList,
									certificateListCount,
									&tsSysTime, 
									(LPWSTR)PfxPassword.pbData, 
									&CertVerifyParams,
									SigHandle);
			else
				if (useOcsp)
					result = crVerifyCertificateUsingOcsp(certificateList,
										certificateListCount,
										&tsSysTime, 
										(LPWSTR)PfxPassword.pbData, 
										&CertVerifyParams,
										SigHandle);
				else {
#ifdef NSS
					SECItem s;
					s.data = PfxPassword.pbData;
					s.len  = PfxPassword.cbData;
					result = crVerifyCertificate(certificateList,
										certificateListCount,
										&tsSysTime, 
										&s, 
										&CertVerifyParams,
										SigHandle);
#else
					result = crVerifyCertificate(certificateList,
										certificateListCount,
										&tsSysTime, 
										(LPWSTR)PfxPassword.pbData, 
										&CertVerifyParams,
										SigHandle);
#endif
				}
			if (result == FALSE)
			{
				for (i=0; i < (UINT) certificateListCount; i++)
				{
					xmlFree(certificateList[i]);
				}
				zFree(certificateList);
				if (pbSignature) zFree(pbSignature);
				if (pbPublicKey) zFree(pbPublicKey);
				ExitObjectLog;
				return S_FALSE;
			}
		}

		/*
		* set <X509Data> certificate
		*/
		if (ExcludeSignerCertificateFlag != 1)// Either include the whole chain or just the end certificate
		{
			ki = xsCoreAddKeyInfo(SigHandle);
			curX509Data = xsCoreAddX509Data(ki, SigHandle);

			if (ExcludeSignerCertificateFlag == 0)// Include the whole chain of certificates
			{
				for (i=0; i < (UINT) certificateListCount; i++)
				{
					char *crlData = NULL;

					curX509Group = xsCoreAddX509Group(curX509Data, SigHandle);
					if ((IncludeCRLInSignature == TRUE) && (CertVerifyParams.usedCrlCount != 0))
					{
						crlData = CertVerifyParams.usedCrlList[i];
					}

					if (xsCoreSetX509Group(curX509Group,NULL,NULL,(char *)certificateList[i],crlData, NULL, NULL, SigHandle)!=TRUE)
					{
						for (int j=0; j < certificateListCount; j++)
						{
							xmlFree(certificateList[j]);
						}
						zFree(certificateList);
						if (pbSignature) zFree(pbSignature);
						if (pbPublicKey) zFree(pbPublicKey);
						ExitObjectLog;
						return FALSE;
					}
				}
			}
			if (ExcludeSignerCertificateFlag == 2) //Just include the signer end certificate
			{
				char *crlData = NULL;
				curX509Group = xsCoreAddX509Group(curX509Data, SigHandle);
				if ((IncludeCRLInSignature == TRUE) && (CertVerifyParams.usedCrlCount != 0))
				{
					crlData = CertVerifyParams.usedCrlList[0];
				}
				if (xsCoreSetX509Group(curX509Group,NULL,NULL,(char *)certificateList[0],crlData, NULL, NULL, SigHandle)!=TRUE)
				{
					for (int j=0; j < certificateListCount; j++)
					{
						xmlFree(certificateList[j]);
					}
					zFree(certificateList);
					if (pbSignature) zFree(pbSignature);
					if (pbPublicKey) zFree(pbPublicKey);
					ExitObjectLog;
					return FALSE;
				}
			}
		} // ExcludeSignerCertificateFlag != 1
	}

	/*
	 * Generate other XML sections
	 */
	if (!xsAcceptSignature(
		(const char *)certificateList[0],
		pbSignature,			// signature
		dwSigLen,				// signature size
		/*pbPublicKey*/ NULL,			// public key
		dwKeyLen,				// public key size
		sigalgtype,
		SigHandle
		))
	{
		for (i=0; i < (UINT) certificateListCount; i++)
		{
			xmlFree(certificateList[i]);
		}
		zFree(certificateList);
		if (pbSignature) zFree(pbSignature);
		if (pbPublicKey) zFree(pbPublicKey);
		ExitObjectLog;
		return S_FALSE;
	}

	for (i=0; i < (UINT) certificateListCount; i++)
	{
		xmlFree(certificateList[i]);
	}
	zFree(certificateList);
	if (pbSignature) zFree(pbSignature);
	if (pbPublicKey) zFree(pbPublicKey);

	/*
	 * get result XML as string and save it
	 */
	char *xsignature = (char *)xsCoreGenerateXMLSec(SigHandle, &iSize);
#ifdef WIN32
	m_binaryData.AssignData((const void *)xsignature, iSize);
	*signedXmlByteArray = m_binaryData.Copy();
#else		
	VARIANT v;
	VariantInit(&v);
	*signedXmlByteArray = v;
	VariantFromByteArray(signedXmlByteArray,(const char *)xsignature, (long) iSize);
#endif

	xmlFree(xsignature);
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::GetSignedDocumentB64Str(LONG sigIndex, LONG uriIndex, BSTR* signedDocB64Str)
{
	int maxUri=0;

	*signedDocB64Str = NULL;

	EnterObjectLog;

	if (DetailedVerificationReportFlag != NO_SIGNED_OBJ_ACCESS)
	{
		if (sgArr==NULL)
		{
			setError(SigHandle, NO_SIGNATURE_DATA);
			return S_FALSE;
		}
		if ((sigIndex >= signum) || (sigIndex < 0))
		{
			setError(SigHandle, SIG_INDEX_ERROR);
			return S_FALSE;
		}

		maxUri = sgArr[sigIndex]->refNumber;

		if ((uriIndex >= maxUri) || (uriIndex < 0))
		{
			setError(SigHandle, URI_INDEX_ERROR);
			return S_FALSE;
		}

USES_CONVERSION;
		*signedDocB64Str = A2WBSTR((LPCSTR) sgArr[sigIndex]->refArray[uriIndex]->refObject->encodedData);
	}
	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::GetSignedDocumentByteArray(LONG sigIndex, LONG uriIndex, VARIANT* signedDocumentByteArray)
{
	int maxUri=0;
	CBufferVariant m_binaryData;
	unsigned long cbData=0;
	unsigned char *pbData=NULL;

	EnterObjectLog;
	m_binaryData.SetLength(0);
	*signedDocumentByteArray = m_binaryData.Copy();

	if (DetailedVerificationReportFlag != NO_SIGNED_OBJ_ACCESS)
	{
		if (sgArr==NULL)
		{
			setError(SigHandle, NO_SIGNATURE_DATA);
			return S_FALSE;
		}
		if ((sigIndex >= signum) || (sigIndex < 0))
		{
			setError(SigHandle, SIG_INDEX_ERROR);
			return S_FALSE;
		}

		maxUri = sgArr[sigIndex]->refNumber;

		if ((uriIndex >= maxUri) || (uriIndex < 0))
		{
			setError(SigHandle, URI_INDEX_ERROR);
			return S_FALSE;
		}

		if (sgArr[sigIndex]->refArray[uriIndex]->refObject->encodedData != NULL)
		{
			cbData = strlen((const char *)sgArr[sigIndex]->refArray[uriIndex]->refObject->encodedData);
			cbData = base64decodeSize(cbData);
			pbData = (unsigned char *) zMalloc(cbData+1);
			if ((cbData = base64decode(sgArr[sigIndex]->refArray[uriIndex]->refObject->encodedData, pbData, cbData+1)) == -1)
			{
				if (pbData)
					zFree(pbData);
				setError(SigHandle, BASE64_ERROR);
				return S_FALSE;
			}
#ifdef WIN32
			m_binaryData.AssignData((const void *)pbData, cbData);
			*signedDocumentByteArray = m_binaryData.Copy();
#else		
			VARIANT v;
			VariantInit(&v);
			*signedDocumentByteArray = v;
			VariantFromByteArray(signedDocumentByteArray,(const char *)pbData, (long) cbData);
#endif
			if (pbData)
				zFree(pbData);
		}
	}

	ExitObjectLog;
	return S_OK;
}

STDMETHODIMP CSignature::get_CertValidationTransactionId(BSTR* pVal)
{
	if (useCam == 1)
		*pVal = A2WBSTR((LPCSTR) CamResponseTransactionId);
	else
	{
#ifdef USE_OCSP
		if ((useOcsp == TRUE) && (pOcspClient != NULL))
		{
			*pVal = ocspOutputNonce.Copy();
		}
		else
#endif
			*pVal = NULL;
	}

	return S_OK;
}

STDMETHODIMP CSignature::put_CertValidationTransactionId(BSTR newVal)
{
#ifdef USE_OCSP
	if ((useOcsp == TRUE) && (pOcspClient != NULL))
	{
		UINT numChar = 0;
		numChar = SysStringLen(newVal);

		if (numChar % 2 != 0) // It is odd
		{
			WCHAR * newTransactionId = (WCHAR *)zMalloc((numChar + 2) *2);
			WCHAR zero = L'0';
			memcpy(newTransactionId, (const void *)&zero, 2);
			wcscpy(newTransactionId + 1, newVal);
			ocspInputNonce = newTransactionId;
			zFree(newTransactionId);
		}
		else
			ocspInputNonce = newVal;
	}
#endif
	return S_OK;
}

STDMETHODIMP CSignature::get_IgnoreIncompleteSignature(BOOL* pVal)
{
	*pVal = IgnoreIncompleteSignature;
	return S_OK;
}

STDMETHODIMP CSignature::put_IgnoreIncompleteSignature(BOOL newVal)
{
	IgnoreIncompleteSignature = newVal;
	return S_OK;
}

STDMETHODIMP CSignature::get_SignatureIndexToVerify(LONG* pVal)
{
	*pVal = SigIndexToVerify;
	return S_OK;
}

STDMETHODIMP CSignature::put_SignatureIndexToVerify(LONG newVal)
{
	SigIndexToVerify = newVal;
	return S_OK;
}

STDMETHODIMP CSignature::get_UseOcsp(BOOL* pVal)
{
	*pVal = useOcsp;
	return S_OK;
}

STDMETHODIMP CSignature::put_UseOcsp(BOOL newVal)
{
	IUnknown *pUnknown;

#ifdef USE_OCSP
	if (useOcsp == TRUE)
	{
		if (newVal == FALSE)
		{
			useOcsp = FALSE;
			if (pOcspClient != NULL)
			{
#ifdef WIN32
				pOcspClient->Release();
#endif
				pOcspClient = NULL;
			}
#ifdef WIN32
			CoUninitialize();
#endif
			return S_OK;
		}
		else
			return S_OK;
	}
	useOcsp = newVal;

	if (useOcsp == TRUE)
	{
		put_UseCam(FALSE); // Disable CAM based validation
#ifdef WIN32
		CoInitialize(NULL);
		HRESULT hr = CoCreateInstance(__uuidof(OcspClient), NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void **) &pUnknown);
		if (FAILED(hr))
		{
			useOcsp = FALSE;
			pOcspClient = NULL;
			setError(SigHandle, OCSP_ERROR);
			CoUninitialize();
			return S_FALSE;
		}

		hr = pUnknown->QueryInterface(__uuidof(IOcspClient), (void **) &pOcspClient);
		if (FAILED(hr))
		{
			pUnknown->Release();
			pOcspClient = NULL;
			useOcsp = FALSE;
			setError(SigHandle, OCSP_ERROR);
			CoUninitialize();
			return S_FALSE;
		}
		pUnknown->Release();
#elif UNIX
		nsresult rv;
		pOcspClient = do_CreateInstance("@infomosaic.com/OcspClientL;1", &rv);
		if (NS_FAILED(rv))
		{
			pOcspClient = NULL;
			useOcsp = FALSE;
			setError(SigHandle, OCSP_ERROR);
			return S_FALSE;
		}
#endif
	}
#endif
	return S_OK;
}

STDMETHODIMP CSignature::get_OcspTrustedRespSignerCertPath(BSTR* pVal)
{
	*pVal = ocspResponseCACertPath.Copy();
	return S_OK;
}

STDMETHODIMP CSignature::put_OcspTrustedRespSignerCertPath(BSTR newVal)
{
	ocspResponseCACertPath = newVal;
	return S_OK;
}

STDMETHODIMP CSignature::get_OcspReqSignerPFXCertPath(BSTR* pVal)
{
	*pVal = ocspRequestSignerB64PfxCertPath.Copy();
	return S_OK;
}

STDMETHODIMP CSignature::put_OcspReqSignerPFXCertPath(BSTR newVal)
{
	BSTR tmpBstr=NULL;
	HRESULT result;

	ocspRequestSignerB64PfxCertPath = newVal;
	result = ReadAllBase64(newVal, &tmpBstr);
	if (tmpBstr != NULL)
		ocspRequestSignerB64PfxCert = tmpBstr;
	else
		return S_FALSE;
	SysFreeString(tmpBstr);
	return S_OK;
}

STDMETHODIMP CSignature::get_OcspReqSignerPFXCertPassword(BSTR* pVal)
{
	*pVal = ocspRequestSignerB64PfxCertPassword.Copy();
	return S_OK;
}

STDMETHODIMP CSignature::put_OcspReqSignerPFXCertPassword(BSTR newVal)
{
	ocspRequestSignerB64PfxCertPassword = newVal;
	return S_OK;
}

STDMETHODIMP CSignature::get_OcspResponderURL(BSTR* pVal)
{
	*pVal = ocspOutputResponderUrl.Copy();
	return S_OK;
}

STDMETHODIMP CSignature::put_OcspResponderURL(BSTR newVal)
{
	ocspResponderUrl = newVal;
	return S_OK;
}

STDMETHODIMP CSignature::get_OcspTextResponse(BSTR* pVal)
{
	*pVal = ocspTextResponse.Copy();
	return S_OK;
}

STDMETHODIMP CSignature::get_OcspB64Response(BSTR* pVal)
{
	*pVal = ocspB64Response.Copy();
	return S_OK;
}

STDMETHODIMP CSignature::get_CertRevocationDate(BSTR* pVal)
{
	*pVal = ocspRevocationTime.Copy();
	return S_OK;
}

STDMETHODIMP CSignature::get_IncludeOcspResponse(LONG* pVal)
{
	*pVal = IncludeOcspResponse;
	return S_OK;
}

STDMETHODIMP CSignature::put_IncludeOcspResponse(LONG newVal)
{
	IncludeOcspResponse = newVal;
	return S_OK;
}

#ifdef WIN32
HRESULT	CSignature::ShowFileSignature(char *filePathBuf, char *outFilePathBuf, BOOL sigCapturedOnce, RECT *windowDim, char *guidStr)
{
	IUnknown *pUnknown;
	ICaptureImage *captureImageObject;
	BSTR bstrFilePath;
	char *charFilePath;
	HRESULT result = S_FALSE;

	USES_CONVERSION;
	EnterObjectLog;
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(__uuidof(CCaptureImage), NULL, CLSCTX_INPROC_SERVER, 
						IID_IUnknown, (void **) &pUnknown);
	if (FAILED(hr))
	{
		CoUninitialize();
		return S_FALSE;
	}

	hr = pUnknown->QueryInterface(__uuidof(ICaptureImage), (void **) &captureImageObject);
	if (FAILED(hr))
	{
		pUnknown->Release();
		CoUninitialize();
		return S_FALSE;
	}
	pUnknown->Release();

	captureImageObject->PhysicalSignatureFile = _bstr_t(filePathBuf);

	bstrFilePath = captureImageObject->ShowFileSignature(_bstr_t(guidStr));
	captureImageObject->Release();
	CoUninitialize();
	if (bstrFilePath != NULL)
	{
		result = S_OK;
		charFilePath = (char *)HeapW2A(bstrFilePath);
		strcpy(outFilePathBuf, charFilePath);
		zFree(charFilePath);
	}
	ExitObjectLog;
	return result;
}

BOOL CSignature::CaptureCurrentWindowImage (char *imageFilePath, char *guidStr)
{
	IUnknown *pUnknown;
	ICaptureImage *captureImageObject;
	BSTR bstrFilePath;
	char *charFilePath;
	BOOL result = FALSE;

	USES_CONVERSION;
	EnterObjectLog;
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(__uuidof(CCaptureImage), NULL, CLSCTX_INPROC_SERVER, 
						IID_IUnknown, (void **) &pUnknown);
	if (FAILED(hr))
	{
		CoUninitialize();
		return S_FALSE;
	}

	hr = pUnknown->QueryInterface(__uuidof(ICaptureImage), (void **) &captureImageObject);
	if (FAILED(hr))
	{
		pUnknown->Release();
		CoUninitialize();
		return S_FALSE;
	}
	pUnknown->Release();

	bstrFilePath = captureImageObject->CaptureCurrentWindowImage();
	captureImageObject->Release();
	CoUninitialize();
	if (bstrFilePath != NULL)
	{
		result = TRUE;
		charFilePath = (char *)HeapW2A(bstrFilePath);
		strcpy(imageFilePath, charFilePath);
		zFree(charFilePath);
	}
	ExitObjectLog;
	return result;
}
#endif

STDMETHODIMP CSignature::put_ProxyHost(BSTR newVal)
{
	proxyHost = newVal;
	return S_OK;
}

STDMETHODIMP CSignature::put_ProxyPort(USHORT newVal)
{
	proxyPort = newVal;
	return S_OK;
}

STDMETHODIMP CSignature::put_ProxyUserName(BSTR newVal)
{
	proxyUserName = newVal;
	return S_OK;
}

STDMETHODIMP CSignature::put_ProxyPassword(BSTR newVal)
{
	proxyPassword = newVal;
	return S_OK;
}

STDMETHODIMP CSignature::put_InclusiveNamespacePrefixList(VARIANT newVal)
{
	UINT elementCount=0;
	UINT itemCount=0;
	BSTR	*bstrList=NULL;
	string namespaceList;
	char *tmpPtr=NULL;

	EnterObjectLog;
	if ((newVal.vt != VT_BSTR) &&
		(newVal.vt != VT_DISPATCH) &&
		!(newVal.vt & VT_ARRAY) && 
		!(newVal.vt & VT_BYREF))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	if (InclusiveNamespaceList != NULL)
		zFree(InclusiveNamespaceList);
	InclusiveNamespaceList = NULL;

	bstrList = GetBstrArrayFromVariant(newVal, &itemCount);

	if ((bstrList == NULL) || (itemCount == 0))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	for (elementCount =0; elementCount < itemCount; elementCount++)
	{
		tmpPtr = (char *)HeapW2A(bstrList[elementCount]);
		namespaceList += tmpPtr;
		namespaceList += " ";
		SysFreeString(bstrList[elementCount]);
		zFree(tmpPtr);
	}
	zFree(bstrList);
	InclusiveNamespaceList = (LPSTR) zMalloc(namespaceList.length() + 1);
	memcpy(InclusiveNamespaceList, namespaceList.c_str(), (namespaceList.length() + 1));
	ExitObjectLog;
	return S_OK;
}

xmlDocPtr CSignature::PrepareSignatureEnvelopeFromObjects(char *charSigId, xmlNodePtr * sigNode, xmlNodePtr * signedInfoNode)
{
	xmlDocPtr doc=NULL;
	xmlNodePtr rootNode=NULL, cur=NULL, parent=NULL;
	xmlNsPtr curNs=NULL, sigNs=NULL;
	BYTE *pbData=NULL, *pbDocument=NULL;
	DWORD cbData = 0, cbDocument = 0;
	char *varprop[1];
	BSTR bstrPropName, bstrPropValue;
	unsigned char *bareFileName=NULL;
	xmlValidCtxtPtr ctxt=NULL;
	xmlDtdPtr dtd=NULL;

#ifdef WIN32
	GUID sigGuid;
#else
	uuid_t sigGuid;
#endif
	char objectId[128];

	if ((AttachedObjectCount == 0) && (DetachedObjectCount == 0))
		return NULL;

	doc = xmlNewDoc((const unsigned char *)"1.0");

	// DTD
    dtd = xmlNewDtd(doc, BAD_CAST "SignatureEnvelope",NULL,NULL);
	// create DTD validation context
    ctxt = xmlNewValidCtxt();
	// add ATTLIST
	xmlAddAttributeDecl(ctxt, dtd, BAD_CAST "ifmc:SignedObject",
                    BAD_CAST "Id", NULL, 
					XML_ATTRIBUTE_ID, XML_ATTRIBUTE_IMPLIED, 
					NULL, NULL);		    
	
    xmlAddChild((xmlNodePtr) doc, (xmlNodePtr) dtd);
	xmlFreeValidCtxt(ctxt);

	// document, namespace, element name, element content
	cur = xmlNewDocNode(doc,NULL,(const unsigned char *)"SignatureEnvelope",NULL);

	// if you want any namespace definition here
	curNs = xmlNewNs(cur,(const unsigned char *)"http://www.infomosaic.net/",(const unsigned char *)"ifmc");
	xmlSetNs(cur,curNs);

	// add root element
	xmlDocSetRootElement(doc,cur);
	rootNode = cur;

	/*
	* Signature
	*/

	cur = xmlNewNode(NULL,(const unsigned char *)"Signature"); // Using the parent element's name space
	*sigNode = cur;
	if (charSigId != NULL)
		xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)charSigId);
	sigNs = xmlNewNs(cur,(const unsigned char *)SIGNATURE_URI,(const unsigned char *)"ds");
	xmlSetNs(cur,sigNs);
	parent = cur;

	/*
	* SignedInfo
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"SignedInfo"); // Using the parent element's name space
	*signedInfoNode = cur;
	cur = xmlAddChild(parent,cur);
	parent = cur;

	/*
		* Canonicalization Method
	*/
	cur = xmlNewNode(NULL,(const unsigned char *)"CanonicalizationMethod");
	switch(CanonicalizationMethod)
	{
		case WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
			break;
		case WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_NO_COMM);
			break;
		case EXC_WITH_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			break;
		case EXC_WITHOUT_COMMENTS:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			break;
		default:
			xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_XML_WITH_COMM);
	}
	cur = xmlAddChild(parent,cur);
	if (signerCertChain == NULL)
	{//We assume RSA Algorithm will be used if no signer certificate info is provided
		cur = xmlNewNode(NULL, (const unsigned char *)"SignatureMethod");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_RSAWITHSHA1);
		cur = xmlAddChild(parent, cur);
	}
	for (UINT i=0; i < AttachedObjectCount; i++)
	{
		if ((i < SignedObjectIdCount) && (SignedObjectIdList[i] != NULL))
		{
			unsigned char *signedObjectId = HeapW2A(SignedObjectIdList[i]);
			strcpy(&objectId[1], (const char *)signedObjectId);
			zFree(signedObjectId);
		}
		else
		{
#ifdef WIN32
		CoCreateGuid(&sigGuid);
		GuidToString(&sigGuid, &objectId[1]);
#else
		uuid_generate(sigGuid);
		uuid_unparse(sigGuid, &objectId[1]);
#endif
		}
		objectId[0] = '#';

		if ((pbDocument = xsDereferenceBstrURI(
			AttachedObjectList[i],
			&cbDocument))==NULL) // (in/out) size of data
		{
				setError(SigHandle, DEREF_URI_ERROR);
				xmlFreeDoc(doc);
				return NULL;
		}
		// Base64 encode
		cbData = base64encodeSize(cbDocument);
		// allocate memory
		if (pbData) zFree (pbData);
		pbData = NULL;
		if(!(pbData = (BYTE *)zMalloc(cbData+1)))
		{
			zFree(pbDocument);
			setError(SigHandle, MEMORY_FAULT);
			xmlFreeDoc(doc);
			return NULL;
		}
		if (base64encode(pbDocument,cbDocument,(unsigned char*)pbData,cbData)==-1) 
		{
			setError(SigHandle, BASE64_ERROR);
			zFree(pbDocument);
			zFree(pbData);
			xmlFreeDoc(doc);
			return NULL;
		}
		*(pbData+cbData)='\0';
		zFree(pbDocument);
		varprop[0] = NULL;
		varprop[0] = (char *)zMalloc(MAX_PATH*2);
		memset(varprop[0],0,MAX_PATH*2);
		sprintf(varprop[0], "URI_%s",&objectId[1]);
//		bareFileName = (unsigned char *)xsRemovePath((const char *)AttachedObjectList[i]);
		bstrPropName = A2WBSTR((LPCSTR)varprop[0]);
//		bstrPropValue = A2WBSTR((LPCSTR)bareFileName);
		unsigned char *tmpCharPtr = xsRemoveBstrPath(AttachedObjectList[i]);
		bstrPropValue = A2WBSTR((LPCSTR)tmpCharPtr);
		zFree(tmpCharPtr);
		ChangeOrAddProperty(bstrPropName, bstrPropValue);
		SysFreeString(bstrPropName);
		SysFreeString(bstrPropValue);

		/*
		* SignedObject
		*/

		cur = xmlNewNode(curNs,(const unsigned char *)"SignedObject"); // Using the parent element's name space
		cur = xmlAddChild(rootNode,cur);
		xmlNewProp(cur, (const unsigned char *)"Encoding", (const unsigned char *)ALG_BASE64);
		xmlNewProp(cur, (const unsigned char *)"Id", (const unsigned char *)&objectId[1]);
		//xmlNewProp(cur, (const unsigned char *)"FileName", (const unsigned char *)bareFileName);
		xmlNodeSetContent(cur,(const unsigned char *)pbData);
		zFree(pbData);
		pbData = NULL;

		/*
		* Add Reference
		*/
		cur = xmlNewNode(NULL,(const unsigned char *)"Reference"); // Using the parent element's name space
		cur = xmlAddChild(*signedInfoNode,cur);

		xmlNewProp(cur, (const unsigned char *)"URI", (const unsigned char *)objectId);
		parent = cur;

		/*
		* Transforms
		*/

		cur = xmlNewNode(NULL,(const unsigned char *)"Transforms");
		cur = xmlAddChild(parent,cur);
		parent = cur;

		/*
		* Transform
		*/

		if ((CanonicalizationMethod == EXC_WITH_COMMENTS) ||
			(CanonicalizationMethod == EXC_WITHOUT_COMMENTS))
		{
			cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_WITH_COMM);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_CANON_EXC_NO_COMM);
			}
			cur = xmlAddChild(parent,cur);
			parent = cur;
			if (CanonicalizationMethod == EXC_WITH_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_WITH_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			else if (CanonicalizationMethod == EXC_WITHOUT_COMMENTS)
			{
				cur = xmlNewNode(NULL,(const unsigned char *)"InclusiveNamespaces");
				xmlNewNs(cur,(const unsigned char *)ALG_CANON_EXC_NO_COMM,(const unsigned char *)"ec");
				xmlNewProp(cur, (const unsigned char *)"PrefixList", (const unsigned char *)InclusiveNamespaceList);
			}
			cur = xmlAddChild(parent,cur);
			parent = parent->parent;
		}

		cur = xmlNewNode(NULL,(const unsigned char *)"Transform");
		xmlNewProp(cur, (const unsigned char *)"Algorithm", (const unsigned char *)ALG_BASE64);
		cur = xmlAddChild(parent,cur);		


		if (varprop[0]) zFree(varprop[0]);
		varprop[0] = NULL;
	}
	xmlAddChild(rootNode,*sigNode);
	for (UINT i=0; i < AttachedObjectCount; i++)
	{
		if (AttachedObjectList[i] != NULL)
			SysFreeString(AttachedObjectList[i]);

	}
	zFree(AttachedObjectList);
	AttachedObjectCount = 0;
	AttachedObjectList = NULL;
	return doc;
}

BSTR CSignature::createSgts()
{
	BOOL tmpBase64EncodeXML, tmpExcludeSignerCertificateFlag, tmpCurrentCertificate;
	SYSTEMTIME t;
	char buffer[BUFSIZ];
	CComBSTR propName, propValue;
//DebugBreak();
#ifdef WIN32
	GetSystemTime(&t);
#else
	GetSystemTimeLinux(&t);
#endif
	char *ampm;
	if (t.wHour >= 12)
		ampm = "pm";
	else
		ampm = "am";
	sprintf((char *)buffer, "%02d/%02d/%04d %02d:%02d:%02d %s", t.wMonth, t.wDay, t.wYear, t.wHour, t.wMinute, t.wSecond, ampm);

	tmpBase64EncodeXML = Base64EncodeXML;
	tmpExcludeSignerCertificateFlag = ExcludeSignerCertificateFlag;
	tmpCurrentCertificate = CurrentCertificate;

	string flLic = FL_LIC1 + FL_LIC2 + FL_LIC3 + FL_LIC4 + FL_LIC5 + FL_LIC6;
	string junk =  FL_LIC7 + FL_LIC9;
	junk += FL_LIC8 + FL_LIC10;
	string date = (char *)buffer; //timeStr.GetString();
	unsigned char *junkValue = (unsigned char *)"SW5mb21vc2FpY1NlY3VyZVdlYnNpZ25QYXNzd29yZA==";

	unsigned int iSize = strlen((const char *)junkValue);
	int oSize = base64decodeSize(iSize);
	unsigned char *charPfxPassword = (unsigned char *)zMalloc(oSize + 1);
	memset(charPfxPassword, 0, oSize +1);
	base64decode(junkValue, charPfxPassword, oSize + 1);
	Base64EncodeXML = 1;
	ExcludeSignerCertificateFlag = 2;
	BSTR pfxDataBuffer = A2WBSTR((LPCSTR)flLic.c_str());
	BSTR pfxPassword = A2WBSTR((LPCSTR) charPfxPassword);
	zFree(charPfxPassword);
	BSTR pfxX509Cert=NULL;
	SetActivePFXB64Data(pfxDataBuffer, pfxPassword, &pfxX509Cert);
	SysFreeString(pfxX509Cert);
	SysFreeString(pfxDataBuffer);
	SysFreeString(pfxPassword);

	for (int i=0; i<PropertyCount; i++)
	{
		if (Properties[i] != NULL)
		{
			zFree(Properties[i]);
			Properties[i] = NULL;
		}
	}
	PropertyCount = 0;

	sprintf((char *)buffer, "%d", LicObj.getMaintExpiryYear());
	propName = (const char *)"MaintExpiryYear";
	propValue = (const char *)buffer;
	ChangeOrAddProperty(propName, propValue);

	sprintf((char *)buffer, "%d", LicObj.getMaintExpiryMonth());
	propName = (const char *)"MaintExpiryMonth";
	propValue = (const char *)buffer;
	ChangeOrAddProperty(propName, propValue);

	sprintf((char *)buffer, "%d", LicObj.getMaintExpiryDay());
	propName = (const char *)"MaintExpiryDay";
	propValue = (const char *)buffer;
	ChangeOrAddProperty(propName, propValue);

	sprintf((char *)buffer, "%d", LicObj.isClientLinux());
	propName = (const char *)"LinuxClient";
	propValue = (const char *)buffer;
	ChangeOrAddProperty(propName, propValue);

	sprintf((char *)buffer, "%d", LicObj.isClientWindows());
	propName = (const char *)"WindowsClient";
	propValue = (const char *)buffer;
	ChangeOrAddProperty(propName, propValue);

	sprintf((char *)buffer, "%d", LicObj.isClientSolaris());
	propName = (const char *)"SolarisClient";
	propValue = (const char *)buffer;
	ChangeOrAddProperty(propName, propValue);

	sprintf((char *)buffer, "%d", LicObj.isClientMac());
	propName = (const char *)"MacClient";
	propValue = (const char *)buffer;
	ChangeOrAddProperty(propName, propValue);


	BSTR floatingLicenseStr=NULL;
	BSTR dateStr = A2WBSTR((LPCSTR) date.c_str());
	SignDataStr(dateStr, &floatingLicenseStr);
	SysFreeString(dateStr);
	Base64EncodeXML = tmpBase64EncodeXML;
	ExcludeSignerCertificateFlag = tmpExcludeSignerCertificateFlag;
	CurrentCertificate = tmpCurrentCertificate;

	for (int i=0; i<PropertyCount; i++)
	{
		if (Properties[i] != NULL)
		{
			zFree(Properties[i]);
			Properties[i] = NULL;
		}
	}
	PropertyCount = 0;

	return floatingLicenseStr;
}

STDMETHODIMP CSignature::get_TimeStampFormat(LONG* pVal)
{
	*pVal = TimeStampFormat;
	return S_OK;
}

STDMETHODIMP CSignature::put_TimeStampFormat(LONG newVal)
{
	TimeStampFormat = newVal;
	return S_OK;
}

STDMETHODIMP CSignature::get_TimeStampCritical(LONG* pVal)
{
	*pVal = TimeStampCritical;
	return S_OK;
}

STDMETHODIMP CSignature::put_TimeStampCritical(LONG newVal)
{
	TimeStampCritical = newVal;
	return S_OK;
}

STDMETHODIMP CSignature::put_SignedObjectId(VARIANT newVal)
{
	UINT elementCount=0;
	UINT itemCount=0;
	BSTR	*bstrList=NULL;

	EnterObjectLog;
	if ((newVal.vt != VT_BSTR) &&
		(newVal.vt != VT_DISPATCH) &&
		!(newVal.vt & VT_ARRAY) && 
		!(newVal.vt & VT_BYREF))
	{
		setError(SigHandle, INVALID_VARIANT);
		return S_FALSE;
	}

	if (SignedObjectIdCount != 0)
	{
		for (unsigned int i=0; i < SignedObjectIdCount; i++)
			SysFreeString(SignedObjectIdList[i]);
		zFree(SignedObjectIdList);
		SignedObjectIdCount = 0;
	}
	SignedObjectIdList = GetBstrArrayFromVariant(newVal, &SignedObjectIdCount);
	ExitObjectLog;
	return S_OK;
}
