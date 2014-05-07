#include "infomosaic_securexml_SmartcardImpl.h"
#include "windows.h"
#include <wincrypt.h>
#include "SecureXMLSmartCard.h"

extern jstring bstr2jstring(JNIEnv *env, BSTR bstr);
extern BSTR jstring2bstr(JNIEnv *env, jstring str);
extern VARIANT jbytearray2variant(JNIEnv *env, jbyteArray arr);
extern jbyteArray variant2jbytearray(JNIEnv *env, VARIANT arr);
extern VARIANT jstringarray2variant(JNIEnv *env, jobjectArray arr);


char PersonInstanceFileAID[512];
char BenefitsInfoFileAID[512];
char OtherBenefitsFileAID[512];
char PersonnelFileAID[512];
char PKICertFileAID_0[512];
char PKICertFileAID_1[512];
char PKICertFileAID_2[512];

long lastError=0;

/***************/
/** CONSTANTS **/
/***************/
/* Macros, defines, constants, ... */
#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    CsetRID
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_infomosaic_securexml_SmartcardImpl_CsetRID
  (JNIEnv *env, jobject _this, jstring rId)
{
	const char *c1 =  env->GetStringUTFChars(rId, 0);
	setRID(c1);
	env->ReleaseStringUTFChars(rId, c1);
	return 0;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    CgetCN
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetCN
  (JNIEnv *env, jobject _this, jint cardHandle, jint certIndex)
{
	jstring str=NULL;
	unsigned char *binCertData = NULL;
	unsigned int dataSize = 0;
	long result = 0;
	unsigned char *aidString=NULL;
	PCCERT_CONTEXT pct = NULL;
	WCHAR shortSubject[256];

	switch(certIndex)
	{
		case 0: aidString = (unsigned char *)PKICertFileAID_0;
				break;
		case 1: aidString = (unsigned char *)PKICertFileAID_1;
				break;
		case 2: aidString = (unsigned char *)PKICertFileAID_2;
				break;
		default:aidString = (unsigned char *)PKICertFileAID_0;
	}

	result = bsiPkiReadCertificate(/*inp*/ cardHandle, 
						/*inp*/ aidString, 
						/*out*/ &binCertData, 
						/*out*/ &dataSize);
	if ((binCertData != NULL) && (dataSize >0))
	{
		pct = CertCreateCertificateContext(MY_ENCODING_TYPE,binCertData,dataSize);
		if (binCertData) free (binCertData);
		if (!pct) 
		{		
//			printf("%s : %d : %s\n", __FILE__, __LINE__, __FUNCTION__);
			return str;
		}
		// get Short Subject name - call
		if(!(result = CertGetNameStringW(
			pct,
			CERT_NAME_SIMPLE_DISPLAY_TYPE,
			(unsigned long)NULL,
			NULL,
			(LPWSTR)shortSubject,
			256))) 
		{
			CertFreeCertificateContext(pct);
//			printf("%s : %d : %s\n", __FILE__, __LINE__, __FUNCTION__);
			return str;
		}
		str = env->NewString((const jchar *)shortSubject, result-1);
		CertFreeCertificateContext(pct);
	}
//	printf("%s : %d : %s\n", __FILE__, __LINE__, __FUNCTION__);
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    CgetEmailAdress
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetEmailAddress
  (JNIEnv *env, jobject _this, jint cardHandle, jint certIndex)
{
	jstring str=NULL;
	unsigned char *binCertData = NULL;
	unsigned int dataSize = 0;
	long result = 0;
	unsigned char *aidString=NULL;
	PCCERT_CONTEXT pct = NULL;
    PCERT_EXTENSION  pCertExtInfo = NULL;
	DWORD cBufferSize = 0;
	PCERT_ALT_NAME_INFO pCertAltNameInfo = NULL;

	switch(certIndex)
	{
		case 0: aidString = (unsigned char *)PKICertFileAID_0;
				break;
		case 1: aidString = (unsigned char *)PKICertFileAID_1;
				break;
		case 2: aidString = (unsigned char *)PKICertFileAID_2;
				break;
		default:aidString = (unsigned char *)PKICertFileAID_0;
	}

	result = bsiPkiReadCertificate(/*inp*/ cardHandle, 
						/*inp*/ aidString, 
						/*out*/ &binCertData, 
						/*out*/ &dataSize);
	if ((binCertData != NULL) && (dataSize >0))
	{
		pct = CertCreateCertificateContext(MY_ENCODING_TYPE,binCertData,dataSize);
		if (binCertData) free (binCertData);
		if (!pct) 
		{
//			printf("%s : %d : %s\n", __FILE__, __LINE__, __FUNCTION__);
			return str;
		}

		// search for the subject alternate name extension
		pCertExtInfo = CertFindExtension(szOID_SUBJECT_ALT_NAME2	/* your OID here */, 
					pct->pCertInfo->cExtension,
					pct->pCertInfo->rgExtension);

		if (NULL != pCertExtInfo)
		{
			// convert the BLOB info into something useful for decoding
			const BYTE* ptemp = pCertExtInfo->Value.pbData;
			DWORD cbCount = pCertExtInfo->Value.cbData;

			if(!CryptDecodeObject(
					MY_ENCODING_TYPE,
					X509_ALTERNATE_NAME, // your OID goes here
					ptemp ,     // The buffer to be decoded.
					cbCount,
					CRYPT_DECODE_NOCOPY_FLAG,
					NULL,
					&cBufferSize))
			{
				CertFreeCertificateContext(pct);
//				printf("%s : %d : %s\n", __FILE__, __LINE__, __FUNCTION__);
				return str;
			}

			// Allocate memory for the decoded information
			if(!(pCertAltNameInfo =  (PCERT_ALT_NAME_INFO) malloc (cBufferSize*2)))
			{
				CertFreeCertificateContext(pct);
//				printf("%s : %d : %s\n", __FILE__, __LINE__, __FUNCTION__);
				return str;
			}

			if(CryptDecodeObject(
					MY_ENCODING_TYPE,
					X509_ALTERNATE_NAME,  // your OID goes here
					ptemp,     // The buffer to be decoded.
					cbCount,
					CRYPT_DECODE_NOCOPY_FLAG,
					pCertAltNameInfo,
					&cBufferSize)) 
			{
					LPWSTR altName;
					DWORD altNameSize=0;
					for (unsigned int i=0; i<pCertAltNameInfo->cAltEntry; i++)
					{
						if (pCertAltNameInfo->rgAltEntry[i].dwAltNameChoice == CERT_ALT_NAME_RFC822_NAME)
						{
							altName = pCertAltNameInfo->rgAltEntry[i].pwszRfc822Name;
							altNameSize = wcslen(altName);
							str = env->NewString((const jchar *)altName, altNameSize);
							break;
						}
					}
					free(pCertAltNameInfo);
			}
			else
			{
				free(pCertAltNameInfo);
				CertFreeCertificateContext(pct);
//				printf("%s : %d : %s\n", __FILE__, __LINE__, __FUNCTION__);
				return str;
			}
		}
		else
		{
			CertFreeCertificateContext(pct);
//			printf("%s : %d : %s\n", __FILE__, __LINE__, __FUNCTION__);
			return str;
		}
		CertFreeCertificateContext(pct);
	}
//	printf("%s : %d : %s\n", __FILE__, __LINE__, __FUNCTION__);
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    connectToCard
 * Signature: (Ljava/lang/String;J)J
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SmartcardImpl_CconnectToCard
  (JNIEnv *env, jobject _this, jint cardHandle, jstring readerName) 
{
	return (jint)connectToCard(cardHandle);
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    disconnectFromCard
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_infomosaic_securexml_SmartcardImpl_CdisconnectFromCard
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	return (jlong)disconnectFromCard(cardHandle);
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getBloodTypeCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetBloodTypeCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *bloodTypeCode = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, BLOOD_TYPE_CODE_TAG, &bloodTypeCode);
	if (bloodTypeCode != NULL)
	{
		str = env->NewStringUTF((const char *)bloodTypeCode);
		free(bloodTypeCode);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getBranchOfServiceCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetBranchOfServiceCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *branchOfServiceCode = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonnelFileAID, BRANCH_SERVICE_CODE_TAG, &branchOfServiceCode);
	if (branchOfServiceCode != NULL)
	{
		str = env->NewStringUTF((const char *)branchOfServiceCode);
		free(branchOfServiceCode);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getCHCCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetCHCCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *chcCode = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)BenefitsInfoFileAID, CIVIL_HCARE_TYPE_CODE_TAG, &chcCode);
	if (chcCode != NULL)
	{
		str = env->NewStringUTF((const char *)chcCode);
		free(chcCode);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getCHCEndDate
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetCHCEndDate
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)BenefitsInfoFileAID, CIVIL_HCARE_END_DATE_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getCadency
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetCadency
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, CADENCY_NAME_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getCardExpireDate
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetCardExpiryDate
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, ID_CARD_EXPIRY_DATE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getCardIssueDate
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetCardIssueDate
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, ID_CARD_ISSUE_DATE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getCommissaryCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetCommissaryCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)BenefitsInfoFileAID, COMMISSARY_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getDateCacDataExpires
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetDateCacDataExpires
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, DEMOGRAPHIC_DATA_EXPIRY_DATE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getDateCacDataLoaded
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetDateCacDataLoaded
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, DEMOGRAPHIC_DATA_LOAD_DATE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getDateOfBirth
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetDateOfBirth
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, DATE_OF_BIRTH_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getDirectCareCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetDirectCareCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)BenefitsInfoFileAID, DIRECT_CARE_TYPE_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getDirectCareEndDate
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetDirectCareEndDate
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)BenefitsInfoFileAID, DIRECT_CARE_END_DATE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getDoDContractorFunctionCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetDoDContractorFunctionCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonnelFileAID, DOD_CONTR_FUNC_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getErrorMessage
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetErrorMessage
  (JNIEnv *env, jobject _this, jint cardHandle, jlong inpJlong) 
{
	jstring str=NULL;
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getExchangeCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetExchangeCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)BenefitsInfoFileAID, EXCHANGE_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getFirstName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetFirstName
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	long	lResp = 0;
	unsigned char	ucTag=0;
	unsigned int	unTag=1;
	unsigned char*	usDataReadValue=NULL; 
	unsigned int 	unDataReadValueLen=0; 
	jstring str=NULL;

	if (cardHandle != -1)
	{
		lResp = getTagValueFromContainer(	cardHandle, 
											(unsigned char *)PersonInstanceFileAID, 
											FIRST_NAME_TAG, 
											&usDataReadValue);
		if (usDataReadValue != NULL)
		{
			str = env->NewStringUTF((const char *)usDataReadValue);
			free(usDataReadValue);
		}
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getGenderCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetGenderCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, SEX_CATEGORY_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getLastName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetLastName
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, LAST_NAME_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getMWRCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetMWRCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)BenefitsInfoFileAID, MWR_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getMealPlanCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetMealPlanCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)OtherBenefitsFileAID, MEAL_PLAN_TYPE_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getMiddleName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetMiddleName
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, MIDDLE_NAME_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getNonMedicalBenefitsEndDate
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetNonMedicalBenefitsEndDate
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)BenefitsInfoFileAID, NON_MED_BEN_END_DATE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getNonUSGovernmentAgencyCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetNonUSGovernmentAgencyCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonnelFileAID, NON_USGOVT_AGENCY_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getOrganDonorCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetOrganDonorCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, ORGAN_DONOR_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getPayGrade
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetPayGrade
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonnelFileAID, PAY_GRADE_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getPayPlan
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetPayPlan
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonnelFileAID, PAY_PLAN_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getPersonDoDEDI
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetPersonDoDEDI
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, DOD_EDI_PERSON_ID_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getPersonIdentifier
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetPersonIdentifier
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, PERSON_IDENTIFIER_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getPersonIdentifierTypeCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetPersonIdentifierTypeCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonInstanceFileAID, PERSON_ID_TYPE_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getPersonnelCategoryCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetPersonnelCategoryCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonnelFileAID, PERSONNEL_CATEGORY_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}


/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getPersonnelEntitlementConditionTypeCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetPersonnelEntitlementConditionTypeCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonnelFileAID, PERSONNEL_ENTL_COND_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getRank
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetRank
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonnelFileAID, RANK_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    getUSGovernmentAgencyCode
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SmartcardImpl_CgetUSGovernmentAgencyCode
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	jstring str=NULL;
	unsigned char *valueString = NULL;
    if (cardHandle==-1) return str;

	getTagValueFromContainer(cardHandle, (unsigned char *)PersonnelFileAID, USGOVT_AGENCY_CODE_TAG, &valueString);
	if (valueString != NULL)
	{
		str = env->NewStringUTF((const char *)valueString);
		free(valueString);
	}
	return str;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    initialize
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_infomosaic_securexml_SmartcardImpl_Cinitialize
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	return 0;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    logoffFromCard
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_infomosaic_securexml_SmartcardImpl_ClogoffFromCard
  (JNIEnv *env, jobject _this, jint cardHandle) 
{
	return 0;
}

/*
 * Class:     infomosaic_securexml_SmartcardImpl
 * Method:    logonToCard
 * Signature: (Ljava/lang/String;J)J
 */
JNIEXPORT jlong JNICALL Java_infomosaic_securexml_SmartcardImpl_ClogonToCard
  (JNIEnv *env, jobject _this, jint cardHandle, jstring pin) 
{
	const char *c1 = env->GetStringUTFChars(pin, 0);
	logonToCard(cardHandle, c1);
	env->ReleaseStringUTFChars(pin, c1);
	return 0;
}

