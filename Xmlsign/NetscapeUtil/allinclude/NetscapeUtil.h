#pragma once
#if __cplusplus
extern "C"
{
#endif

#include "resource.h"
#include <stdio.h>
#include <windows.h>
#include <string.h>

#if defined(WIN32)
#include "fcntl.h"
#include "io.h"
#endif

#include "secutil.h"

#if defined(XP_UNIX)
#include <unistd.h>
#endif

#include "nspr.h"
#include "prtypes.h"
#include "prtime.h"
#include "prlong.h"

#include "pk11func.h"
#include "secasn1.h"
#include "cert.h"
#include "cryptohi.h"
#include "secoid.h"
#include "certdb.h"
#include "nss.h"

#include "secutil.h"
#include "pkcs12.h"
#include "p12plcy.h"
#include "pk12util.h"
#include "secport.h"

#include <strsafe.h>


/**
 * CERT_DESCR
 *
 * describes X509 certificate
 */
//#if !__cplusplus
typedef struct _CERT_DESCR CERT_DESCR;
typedef CERT_DESCR *PCERT_DESCR;
struct _CERT_DESCR{
	unsigned char serialNumber[256];
	WCHAR issuer[256];
	WCHAR subject[256];
	WCHAR shortSubject[256];
	unsigned char notAfter[256];
	unsigned char *certificate;
};
//#endif
PCERT_DESCR *axGetNetscapeCertList(int *, char *, char *);
HRESULT axExportNetscapeCert(char *fileName, char *serialNum, char *passwd, char *tempNetDir, char *dbPass);

PRUintn P12U_Init(char *, char *);
HRESULT P12U_ExportPKCS12Object(CERTCertificate *, char *, PK11SlotInfo *,
								secuPWData *, secuPWData *);
HRESULT NetscapeUtilStart(char **tempNetDir);
HRESULT NetscapeUtilStop(char *tempNetDir);

#if __cplusplus
}
#endif
