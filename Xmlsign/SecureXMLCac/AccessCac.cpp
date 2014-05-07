#include "infomosaic_securexml_SmartcardImpl.h"
#include "windows.h"
#include <wincrypt.h>
#include "SecureXMLSmartCard.h"
#define GSC_2_0
#include "Litronic/bsi.h"
//#ifdef LITRONIC
//#define GSC_2_0
//#include "Litronic/bsi.h"
//#define gscBsiPkiReadCertificate(a, b, c, d, e) gscBsiPkiGetCertificate(a, b, c, d, (unsigned long *)e)
//#define gscBsiGcReadValue(a, b, c, d, e, f)     gscBsiGcReadValue(a, b, c, d, e, (unsigned long *)f)
//#define BSI_INVALID_CARD_HANDLE BSI_BAD_HANDLE
#define MAX_RDRS_TEXT_LEN 8192
//#else
//#include "Activcard/acbsiprov.h"
//#endif

typedef BSI_RETURN (CALLBACK * __AC_XSI_UtilConnect)( 
	OUT UTILCardHandle*,
	IN unsigned char*,				
	IN BSI_INT				
); 

typedef BSI_RETURN (CALLBACK * __AC_XSI_UtilDisconnect)( 
	IN UTILCardHandle					
); 

typedef BSI_RETURN (CALLBACK * __gscOldBsiUtilAcquireContext)( 
	IN UTILCardHandle,					
	IN unsigned char*,				
	IN unsigned int,				
	IN BSIAuthenticator*,	
	IN unsigned int					
); 

typedef BSI_RETURN (CALLBACK * __gscOldBsiUtilReleaseContext)( 
	IN UTILCardHandle,					
	IN unsigned char*,				
	IN BSI_INT				
); 


typedef BSI_RETURN (CALLBACK * __gscOldBsiGcReadValue)( 
	IN UTILCardHandle,				
	IN unsigned char*, 			
	IN BSI_INT, 			
	IN BSI_GCT, 				
	IN OUT unsigned char*, 			
	IN OUT BSI_UINT*		
); 
 
typedef BSI_RETURN (CALLBACK * __gscOldBsiPkiReadCertificate)( 
	IN UTILCardHandle,					
	IN unsigned char*, 				
	IN BSI_INT, 				
	OUT unsigned char*, 		
	IN OUT BSI_INT* 		
); 
 
__gscBsiUtilConnect gscBsiUtilConnect;
__gscBsiUtilDisconnect gscBsiUtilDisconnect;
__gscBsiUtilAcquireContext gscBsiUtilAcquireContext;
__gscBsiGcReadValue gscBsiGcReadValue;
__gscBsiPkiGetCertificate gscBsiPkiGetCertificate;
__gscBsiUtilGetReaderList gscBsiUtilGetReaderList;

__AC_XSI_UtilConnect AC_XSI_UtilConnect;
__AC_XSI_UtilDisconnect AC_XSI_UtilDisconnect;
__gscOldBsiUtilAcquireContext gscOldBsiUtilAcquireContext;
__gscOldBsiGcReadValue gscOldBsiGcReadValue;
__gscOldBsiPkiReadCertificate gscOldBsiPkiReadCertificate;


BOOL smCardMiddlewareOld=FALSE;


#define BUFSIZ	512
#define CHAR_HEX(c) (((c)>='0' && (c)<='9') ? ((c) - '0') : ( ((c)>='a' && (c)<='f') ? ((c)-'a'+0x0a) : ((c)-'A'+0x0a) ))
#define HEX_CHAR(c) (((c)>=0 && (c)<=9) ? ((c) + '0') : ((c)+'A'-0x0a) )

extern char PersonInstanceFileAID[512];
extern char BenefitsInfoFileAID[512];
extern char OtherBenefitsFileAID[512];
extern char PersonnelFileAID[512];
extern char PKICertFileAID_0[512];
extern char PKICertFileAID_1[512];
extern char PKICertFileAID_2[512];


HINSTANCE m_hInstCacDll;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  dwReason, 
                       LPVOID lpReserved
					 )
{

    if (dwReason == DLL_PROCESS_ATTACH)
    {
		m_hInstCacDll = LoadLibrary((LPCTSTR)"sspbsi.dll");
		if (m_hInstCacDll == NULL)
		{
			//MessageBox(NULL, "Could not load sspbsi.dll", "Failure", MB_OK);
			//m_hInstCacDll = LoadLibrary((LPCTSTR)"acbsi20.dll");
			//if (m_hInstCacDll == NULL)
			//{
			//	MessageBox(NULL, "Could not load acbsi20.dll", "Failure", MB_OK);
				m_hInstCacDll = LoadLibrary((LPCTSTR)"acbsiprov.dll");
				if (m_hInstCacDll == NULL)
				{
					//MessageBox(NULL, "Could not load acbsiprov.dll", "Failure", MB_OK);
				}
				else
				{
					//MessageBox(NULL, "acbsiprov.dll loaded successfully", "Success", MB_OK);
					smCardMiddlewareOld = TRUE;
				}
			//}
			//else
			//{
			//	MessageBox(NULL, "acbsi20.dll loaded successfully", "Success", MB_OK);
			//}
		}
		else
		{
			//MessageBox(NULL, "sspbsi.dll loaded successfully", "Success", MB_OK);
		}
    }

    return TRUE;
}

int ConvAsciiToBin (	const char *pszDataIn,	/* String buffer to convert (size must be multiple of 2)*/
                        char *pszDataOut,		/* Binary buffer*/
                        int *nDataOutSize)		/* size of output buffer*/
{
  int nInLength;
  int i;

/* ----- Control the parameters -------- */

  if( !pszDataIn || 
      !pszDataOut )
      return -1;

  nInLength = strlen (pszDataIn);

  /* data len must be even */
  if (nInLength % 2)
      return -1;

  /* must fit in the pszDataOut buffer */
  if ( *nDataOutSize < (nInLength / 2) )
      return -1;

/* ------------------------------------ */
  
  for (i = 0; i < nInLength; i += 2)
    pszDataOut[i / 2] = CHAR_HEX (pszDataIn[i + 1]) | (CHAR_HEX (pszDataIn[i]) << 4);
  
  *nDataOutSize = nInLength / 2;

  return 0;
}

void GetContainerAID ( unsigned char *asciiHexString, unsigned char *pusAID, unsigned int *punAIDLen)
{
	unsigned int i=0;
	unsigned int length=0;

	if (asciiHexString != NULL)
		length = strlen((const char *)asciiHexString);

	if (length > *punAIDLen*2)
	{
		memset (pusAID, 0, *punAIDLen);
		*punAIDLen = 0;
		return;
	}
	for (i =0; i < length; i++)
	{
		if (!isxdigit(asciiHexString[i]))
		{
			memset (pusAID, 0, *punAIDLen);
			*punAIDLen = 0;
			return;
		}
	}

	if ( ConvAsciiToBin ((const char *)asciiHexString, (char *)pusAID, (int *)punAIDLen ) == -1)
	{
		memset (pusAID, 0, *punAIDLen);
		*punAIDLen = 0;
		return;
	}
}

void setRID(const char *rId)
{
	gscBsiUtilConnect = NULL;
	gscBsiUtilDisconnect = NULL;
	gscBsiUtilAcquireContext = NULL;
	gscBsiGcReadValue = NULL;
	gscBsiPkiGetCertificate = NULL;
	gscBsiUtilGetReaderList = NULL;

	gscOldBsiUtilAcquireContext = NULL;
	gscOldBsiGcReadValue = NULL;
	gscOldBsiPkiReadCertificate = NULL;
	gscOldBsiPkiReadCertificate = NULL;

	if (smCardMiddlewareOld == TRUE)
	{
		AC_XSI_UtilConnect =
			(__AC_XSI_UtilConnect)GetProcAddress(m_hInstCacDll, "AC_XSI_UtilConnect");
		//if (AC_XSI_UtilConnect == NULL)
		//	MessageBox(NULL, (LPCTSTR)"AC_XSI_UtilConnect == NULL", (LPCTSTR)__FUNCTION__, MB_OK);

		AC_XSI_UtilDisconnect =
			(__AC_XSI_UtilDisconnect)GetProcAddress(m_hInstCacDll, "AC_XSI_UtilDisconnect");
		//if (AC_XSI_UtilDisconnect == NULL)
		//	MessageBox(NULL, (LPCTSTR)"AC_XSI_UtilDisconnect == NULL", (LPCTSTR)__FUNCTION__, MB_OK);

		gscOldBsiPkiReadCertificate =
 				(__gscOldBsiPkiReadCertificate)GetProcAddress(m_hInstCacDll, "gscBsiPkiReadCertificate");
		//if (gscOldBsiPkiReadCertificate == NULL)
		//	MessageBox(NULL, (LPCTSTR)"gscBsiPkiReadCertificate == NULL", (LPCTSTR)__FUNCTION__, MB_OK);

		gscOldBsiUtilAcquireContext =
 				(__gscOldBsiUtilAcquireContext)GetProcAddress(m_hInstCacDll, "gscBsiUtilAcquireContext");
		//if (gscOldBsiUtilAcquireContext == NULL)
		//	MessageBox(NULL, (LPCTSTR)"gscBsiUtilAcquireContext == NULL", (LPCTSTR)__FUNCTION__, MB_OK);

		gscOldBsiGcReadValue =
 				(__gscOldBsiGcReadValue)GetProcAddress(m_hInstCacDll, "gscBsiGcReadValue");
		//if (gscOldBsiGcReadValue == NULL)
		//	MessageBox(NULL, (LPCTSTR)"gscBsiGcReadValue == NULL", (LPCTSTR)__FUNCTION__, MB_OK);
	}
	else
	{
		gscBsiUtilConnect =
 				(__gscBsiUtilConnect)GetProcAddress(m_hInstCacDll, "gscBsiUtilConnect");
		//if (gscBsiUtilConnect == NULL)
		//	MessageBox(NULL, (LPCTSTR)"gscBsiUtilConnect == NULL", (LPCTSTR)__FUNCTION__, MB_OK);

		gscBsiUtilDisconnect =
 				(__gscBsiUtilDisconnect)GetProcAddress(m_hInstCacDll, "gscBsiUtilDisconnect");
		//if (gscBsiUtilDisconnect == NULL)
		//	MessageBox(NULL, (LPCTSTR)"gscBsiUtilDisconnect == NULL", (LPCTSTR)__FUNCTION__, MB_OK);

		gscBsiUtilAcquireContext =
 				(__gscBsiUtilAcquireContext)GetProcAddress(m_hInstCacDll, "gscBsiUtilAcquireContext");
		//if (gscBsiUtilAcquireContext == NULL)
		//	MessageBox(NULL, (LPCTSTR)"gscBsiUtilAcquireContext == NULL", (LPCTSTR)__FUNCTION__, MB_OK);

		gscBsiGcReadValue =
 				(__gscBsiGcReadValue)GetProcAddress(m_hInstCacDll, "gscBsiGcReadValue");
		//if (gscBsiGcReadValue == NULL)
		//	MessageBox(NULL, (LPCTSTR)"gscBsiGcReadValue == NULL", (LPCTSTR)__FUNCTION__, MB_OK);

		gscBsiPkiGetCertificate =
 				(__gscBsiPkiGetCertificate)GetProcAddress(m_hInstCacDll, "gscBsiPkiGetCertificate");
		//if (gscBsiPkiGetCertificate == NULL)
		//	MessageBox(NULL, (LPCTSTR)"gscBsiPkiGetCertificate == NULL", (LPCTSTR)__FUNCTION__, MB_OK);

		gscBsiUtilGetReaderList =
 				(__gscBsiUtilGetReaderList)GetProcAddress(m_hInstCacDll, "gscBsiUtilGetReaderList");
		//if (gscBsiUtilGetReaderList == NULL)
		//	MessageBox(NULL, (LPCTSTR)"gscBsiUtilGetReaderList == NULL", (LPCTSTR)__FUNCTION__, MB_OK);
	}


	memset(PersonInstanceFileAID, 0, 512);
	memset(BenefitsInfoFileAID, 0, 512);
	memset(OtherBenefitsFileAID, 0, 512);
	memset(PersonnelFileAID, 0, 512);
	memset(PKICertFileAID_0, 0, 512);
	memset(PKICertFileAID_1, 0, 512);
	memset(PKICertFileAID_2, 0, 512);

	strcpy(PersonInstanceFileAID, rId);
	strcpy(BenefitsInfoFileAID, rId);
	strcpy(OtherBenefitsFileAID, rId);
	strcpy(PersonnelFileAID, rId);
	strcpy(PKICertFileAID_0, rId);
	strcpy(PKICertFileAID_1, rId);
	strcpy(PKICertFileAID_2, rId);

	strcat(PersonInstanceFileAID, "0200");
	strcat(BenefitsInfoFileAID, "0202");
	strcat(OtherBenefitsFileAID, "0203");
	strcat(PersonnelFileAID, "0201");
	strcat(PKICertFileAID_0, "0100");
	strcat(PKICertFileAID_1, "0101");
	strcat(PKICertFileAID_2, "0102");
}

long bsiPkiReadCertificate(/*inp*/ int hCard, 
						/*inp*/ unsigned char *asciiHexString, 
						/*out*/ unsigned char **usCertificateValue, 
						/*out*/ unsigned int *unCertificateDataLen)
{
	long	lResp = BSI_OK;
	unsigned char	usAID[BUFSIZ];
	unsigned int	unAIDLen=0;
	*usCertificateValue= NULL;
	*unCertificateDataLen=0;	
	
	unAIDLen = BUFSIZ;
	GetContainerAID (asciiHexString, usAID, &unAIDLen);

	if (smCardMiddlewareOld == TRUE)
	{
		lResp = gscOldBsiPkiReadCertificate(
			hCard,				
			(unsigned char *)usAID,			
			unAIDLen,	
			NULL,
			(unsigned long *)unCertificateDataLen					
			);
		if (lResp != BSI_OK)
		{
//			printf("%s : %d : %s : lResp = %d\n", __FILE__, __LINE__, __FUNCTION__, lResp);
			return lResp;
		}
	}
	else
	{
		*unCertificateDataLen = 1024*8;
	}
	*usCertificateValue = (unsigned char *)malloc (*unCertificateDataLen*sizeof (unsigned char));
	if (*usCertificateValue != NULL)
	{
		/* retrieve data */
		if (smCardMiddlewareOld == TRUE)
		{
			lResp = gscOldBsiPkiReadCertificate(
				hCard,				
				usAID,			
				unAIDLen,	
				*usCertificateValue,	
				(unsigned long *)unCertificateDataLen	
				);
		}
		else
		{
			lResp = gscBsiPkiGetCertificate(
				hCard,				
				usAID,			
				unAIDLen,	
				*usCertificateValue,	
				(unsigned long *)unCertificateDataLen	
				);
		}
		if (lResp != BSI_OK)
		{
			free(*usCertificateValue);
//				printf("%s : %d : %s\n", __FILE__, __LINE__, __FUNCTION__);
			return lResp;
		}	
		else	
		{
//				printf("%s : %d : %s\n", __FILE__, __LINE__, __FUNCTION__);
			return BSI_OK;
		}
	}
	return lResp;
}

long getTagValueFromContainer(/*inp*/ int hCard, 
						/*inp*/ unsigned char *asciiHexString, 
						/*inp*/ char tag, 
						/*out*/ unsigned char **tagValue)
{
	long	lResp = BSI_OK;
	unsigned char	usAID[BUFSIZ];
	unsigned int	unAIDLen=BUFSIZ;
	unsigned char	ucTag=0;
	unsigned char*	usDataReadValue=NULL; 
	unsigned int 	unDataReadValueLen=0; 

	GetContainerAID (asciiHexString, usAID, &unAIDLen);

	ucTag = (char)tag;
	
	/* retrieve data length */
	if (smCardMiddlewareOld == TRUE)
	{
		lResp = gscOldBsiGcReadValue(
			hCard,				
			usAID,			
			unAIDLen,	
			ucTag,
			NULL,	
			(unsigned long *)&unDataReadValueLen	
			);
	}
	else
		lResp = gscBsiGcReadValue(
			hCard,				
			usAID,			
			unAIDLen,	
			ucTag,
			NULL,	
			(unsigned long *)&unDataReadValueLen	
			);
	if (lResp != BSI_OK)
	{
		return lResp;
	}	
	else	
	{
		if (unDataReadValueLen != 0)
		{	
			usDataReadValue = (unsigned char *)malloc (unDataReadValueLen*sizeof (unsigned char) + 1);
			if (usDataReadValue != NULL)
			{
				/* retrieve data */
				if (smCardMiddlewareOld == TRUE)
				{
					lResp = gscOldBsiGcReadValue(
						hCard,				
						usAID,			
						unAIDLen,	
						ucTag,
						usDataReadValue,	
						(unsigned long *)&unDataReadValueLen	
						);
				}
				else
					lResp = gscBsiGcReadValue(
						hCard,				
						usAID,			
						unAIDLen,	
						ucTag,
						usDataReadValue,	
						(unsigned long *)&unDataReadValueLen	
						);
				if (lResp != BSI_OK)
				{
					return lResp;
				}	
				else	
				{
					*(char *)(usDataReadValue+unDataReadValueLen) = '\0';
					*tagValue = usDataReadValue;
//					printf("Tag = %02x, value = %s\n", (int)tag, *tagValue);
					return unDataReadValueLen;
				}
			}
			else
				return OUT_OF_MEMORY;
		}
		else
			return ZERO_DATA_LENGTH_ENTRY;
	}
}
long logonToCard(int cardHandle, const char *pinStr)
{
	BSIAuthenticator pstrAuthent;
	unsigned int unAuthenticatorNb=1;
	long	lResp = -1;
	unsigned char	usAID[BUFSIZ];
	unsigned int	unAIDLen=BUFSIZ;

	//MessageBox(NULL, (LPCTSTR)"Setting BSIAuthenticator structure", (LPCTSTR)__FUNCTION__, MB_OK);
	if (pinStr != NULL)
	{
//#ifdef LITRONIC
		pstrAuthent.unACRtype = BSI_ACR_PIN;
		pstrAuthent.unAuthValueLen = strlen(pinStr);
		pstrAuthent.bWriteKey=				 false;			// We want to read
		memcpy ((char *)(pstrAuthent.usAuthValue), pinStr, pstrAuthent.unAuthValueLen);
//#else
//		pstrAuthent.unACRType = BSI_ACR_PIN;
//		pstrAuthent.unAuthLen = strlen(pinStr);
//		memcpy ((char *)(pstrAuthent.usAuthValue), pinStr, pstrAuthent.unAuthLen);
//#endif
		GetContainerAID ((unsigned char *)PersonInstanceFileAID, usAID, &unAIDLen);
	//MessageBox(NULL, (LPCTSTR)"Calling gscBsiUtilAcquireContext", (LPCTSTR)__FUNCTION__, MB_OK);
		if (smCardMiddlewareOld == TRUE)
		{
			lResp = gscOldBsiUtilAcquireContext(
				cardHandle,				
				(unsigned char *)usAID,				
				unAIDLen,
				&pstrAuthent,
				unAuthenticatorNb);
		}
		else
			lResp = gscBsiUtilAcquireContext(
				cardHandle,				
				(unsigned char *)usAID,				
				unAIDLen,
				&pstrAuthent,
				unAuthenticatorNb);
	}
//	printf("%s : lResp = %d\n",__FUNCTION__, lResp);
	return lResp;
}

int connectToCard(int cardHandle)
{
	jint	lResp = BSI_OK;
	UTILCardHandle hCard=0;


	if (cardHandle != -1)
	{
		//MessageBox(NULL, (LPCTSTR)"Calling gscBsiUtilDisconnect", (LPCTSTR)__FUNCTION__, MB_OK);
		if (smCardMiddlewareOld == FALSE)
			lResp = gscBsiUtilDisconnect( cardHandle );
		else
			lResp = (jint)AC_XSI_UtilDisconnect(cardHandle);
	}
	
	if (smCardMiddlewareOld == FALSE)
	{
		char  ListOfReaders[MAX_RDRS_TEXT_LEN];

		BSI_INT	   unReaderListLen=MAX_RDRS_TEXT_LEN;
		//MessageBox(NULL, (LPCTSTR)"Calling gscBsiUtilGetReaderList", (LPCTSTR)__FUNCTION__, MB_OK);
		lResp= gscBsiUtilGetReaderList( (unsigned char *)ListOfReaders, &unReaderListLen );
		if ( BSI_OK != lResp ) {
			//MessageBox(NULL, (LPCTSTR)"BSI_OK != lResp", (LPCTSTR)__FUNCTION__, MB_OK);
			return( false );
		}	
		
		if ( MAX_RDRS_TEXT_LEN < unReaderListLen ) {
			//MessageBox(NULL, (LPCTSTR)"MAX_RDRS_TEXT_LEN < unReaderListLen", (LPCTSTR)__FUNCTION__, MB_OK);
			return( false );
		}

		if ( 0 == unReaderListLen ) {
			//MessageBox(NULL, (LPCTSTR)"0 == unReaderListLen", (LPCTSTR)__FUNCTION__, MB_OK);
			return( false );
		}


		// Display all the possible readers */
		int num_readers = 0;
		char *thereader= ListOfReaders;
		int n= 0;  // Choose the 0th
		
		// Show all the readers
		while ( 0 != *thereader ) {
			num_readers++;

			while ( 0 != *thereader++ );	// Skip to next possible reader
		}


		/* Connect to the Nth reader. */
		thereader= ListOfReaders;
		for ( int i=0; i< num_readers; i++ ) 
		{
			if ( i == n ) 
			{		

				// Now try to establish a context with a reader & card.
				// ( Will fail if there is no card in the reader )
				//MessageBox(NULL, (LPCTSTR)"Calling gscBsiUtilConnect", (LPCTSTR)__FUNCTION__, MB_OK);
				lResp= gscBsiUtilConnect( (unsigned char *)thereader, strlen(thereader), &hCard );
				if ( BSI_OK == lResp ) 
				{
					break;;
				} 
				else 
				{
					continue;
				}
			}

			while ( 0 != *thereader++ );
		}
	}
	else
		lResp = (jint)AC_XSI_UtilConnect(&hCard, NULL, 0);

	if (lResp != BSI_OK)
	{
		return (jlong)-1;
	}
	return (jint)hCard;
}
long disconnectFromCard(int cardHandle)
{
	jlong	lResp = BSI_OK;
	if (cardHandle != -1)
	{
		if (smCardMiddlewareOld == FALSE)
		{
			//MessageBox(NULL, (LPCTSTR)"Calling gscBsiUtilConnect", (LPCTSTR)__FUNCTION__, MB_OK);
			lResp = (jlong)gscBsiUtilDisconnect(cardHandle);
		}
		else
			lResp = (jlong)AC_XSI_UtilDisconnect(cardHandle);
	}
	return lResp;
}