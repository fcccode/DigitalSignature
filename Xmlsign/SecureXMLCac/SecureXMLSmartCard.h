#ifndef _Included_SecureXMLSmartCard
#define _Included_SecureXMLSmartCard
#ifdef __cplusplus
extern "C" {
#endif

#define PERSONAL_INSTANCE_FILE				"0200"
#define FIRST_NAME_TAG						0x01
#define FIRST_NAME_MAXLEN					40
#define MIDDLE_NAME_TAG						0x02
#define MIDDLE_NAME_MAXLEN					40
#define LAST_NAME_TAG						0x03
#define LAST_NAME_MAXLEN					52
#define CADENCY_NAME_TAG					0x04
#define CADENCY_NAME_MAXLEN					8
#define PERSON_IDENTIFIER_TAG				0x05
#define PERSON_IDENTIFIER_MAXLEN			30
#define DATE_OF_BIRTH_TAG					0x06
#define DATE_OF_BIRTH_MAXLEN				16
#define SEX_CATEGORY_CODE_TAG				0x07
#define SEX_CATEGORY_CODE_MAXLEN			2
#define PERSON_ID_TYPE_CODE_TAG				0x08
#define PERSON_ID_TYPE_CODE_MAXLEN			2
#define BLOOD_TYPE_CODE_TAG					0x11
#define BLLOD_TYPE_CODE_MAXLEN				4
#define DOD_EDI_PERSON_ID_TAG				0x17
#define DOD_EDI_PERSON_ID_MAXLEN			20
#define ORGAN_DONOR_TAG						0x18
#define ORGAN_DONOR_MAXLEN					2
#define ID_CARD_ISSUE_DATE_TAG				0x62
#define ID_CARD_ISSUE_DATE_MAXLEN			16
#define ID_CARD_EXPIRY_DATE_TAG				0x63
#define ID_CARD_EXPIRY_DATE_MAXLEN			16
#define DEMOGRAPHIC_DATA_LOAD_DATE_TAG		0x65
#define DEMOGRAPHIC_DATA_LOAD_DATE_MAXLEN	16
#define DEMOGRAPHIC_DATA_EXPIRY_DATE_TAG	0x66
#define DEMOGRAPHIC_DATA_EXPIRY_DATE_MAXLEN	16
#define CARD_INSTANCE_ID_TAG				0x67
#define CARD_INSTANCE_ID_MAXLEN				2


#define BENEFITS_INFO_FILE					"0202"
#define EXCHANGE_CODE_TAG					0x12
#define EXCHANGE_CODE_MAXLEN				2
#define COMMISSARY_CODE_TAG					0x13
#define COMMISSARY_CODE_MAXLEN				2
#define MWR_CODE_TAG						0x14
#define MWR_CODE_MAXLEN						2
#define NON_MED_BEN_END_DATE_TAG			0x1B
#define NON_MED_BEN_END_DATE_MAXLEN			16
#define DIRECT_CARE_END_DATE_TAG			0x1C
#define DIRECT_CARE_END_DATE_MAXLEN			16
#define CIVIL_HCARE_TYPE_CODE_TAG			0xd0
#define CIVIL_HCARE_TYPE_CODE_MAXLEN		2
#define DIRECT_CARE_TYPE_CODE_TAG			0xd1
#define DIRECT_CARE_TYPE_CODE_MAXLEN		2
#define CIVIL_HCARE_END_DATE_CODE_TAG		0xd2
#define CIVIL_HCARE_END_DATE_CODE_MAXLEN	16


#define OTHER_BENEFITS_FILE					"0203"
#define MEAL_PLAN_TYPE_CODE_TAG				0x1a
#define MEAL_PLAN_TYPE_CODE_MAXLEN			4


#define PERSONNEL_FILE						"0201"
#define DOD_CONTR_FUNC_CODE_TAG				0x19
#define DOD_CONTR_FUNC_CODE_MAXLEN			2
#define USGOVT_AGENCY_CODE_TAG				0x20
#define USGOVT_AGENCY_CODE_MAXLEN			8
#define BRANCH_SERVICE_CODE_TAG				0x24
#define BRANCH_SERVICE_CODE_MAXLEN			2
#define PAY_GRADE_CODE_TAG					0x25
#define PAY_GRADE_CODE_MAXLEN				4
#define RANK_CODE_TAG						0x26
#define RANK_CODE_TAG_MAXLEN				12
#define PERSONNEL_CATEGORY_CODE_TAG			0x34
#define PERSONNEL_CATEGORY_CODE_MAXLEN		2
#define NON_USGOVT_AGENCY_CODE_TAG			0x35
#define NON_USGOVT_AGENCY_CODE_MAXLEN		4
#define PAY_PLAN_CODE_TAG					0x36
#define PAY_PLAN_CODE_MAXLEN				4
#define PERSONNEL_ENTL_COND_CODE_TAG		0xd3
#define PERSONNEL_ENTL_COND_CODE_MAXLEN		4

#define CERTIFICATE_DATA_CODE				0x70
#define CERTIFICATE_DATA_CODE_MAXLEN		1100

/* Define additional error codes */
#define ZERO_DATA_LENGTH_ENTRY				-40001
#define OUT_OF_MEMORY						-40002

extern long getTagValueFromContainer(/*inp*/ int hCard, 
						/*inp*/ unsigned char *asciiHexString, 
						/*inp*/ char tag, 
						/*out*/ unsigned char **tagValue);
extern long logonToCard(int cardHandle, const char *pinStr);
extern void setRID(const char *rId);
extern int connectToCard(int cardHandle);
extern long disconnectFromCard(int cardHandle);
extern long bsiPkiReadCertificate(/*inp*/ int hCard, 
						/*inp*/ unsigned char *asciiHexString, 
						/*out*/ unsigned char **usCertificateValue, 
						/*out*/ unsigned int *unCertificateDataLen);
extern long getTagValueFromContainer(/*inp*/ int hCard, 
						/*inp*/ unsigned char *asciiHexString, 
						/*inp*/ char tag, 
						/*out*/ unsigned char **tagValue);
void setRID(const char *rId);

#ifdef __cplusplus
}
#endif

#endif