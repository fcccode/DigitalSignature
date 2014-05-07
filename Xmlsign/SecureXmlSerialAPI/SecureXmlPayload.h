#pragma once

#if __cplusplus
extern "C" {
#endif

#include <libxml/parser.h>
#include <libxml/xmlschemas.h>

#if __cplusplus
}
#endif

#define	MAXPARAMCOUNT	8
#define MAXVALUECOUNT	128

//#include <securexml/CharConversion.h>

typedef struct ParamTypeStruct
{
	char paramType[16];
} ParamTypeName, *ParamTypeNamePtr;

class SecureXmlPayload
{
public:
	SecureXmlPayload(void);
	SecureXmlPayload(const char *apiName, long sourceProcessId, const char *nonce,
					unsigned long signatureObjectId, int paramCount);
	virtual ~SecureXmlPayload(void);
private:
	xmlDocPtr doc;
	unsigned char *charXmlDocPtr;
	int charXmlDocSize;
	bool *ParamIsArrayArray;
	int *ParamArraySizeArray;
	ParamTypeNamePtr ParamTypeArray;
	char *ValueArray[MAXPARAMCOUNT][MAXVALUECOUNT];
	VARIANT VariantParamValue[MAXPARAMCOUNT];
	SecureXmlPayload *oPayload;
protected:
	char *ApiName;
	long SourceProcessId;
	char *Nonce;
	unsigned long SignatureObjectId;
	int ParamCount;
public:
	// Valid input for dataType are String, Integer, ShortInteger and Byte. isArray must be true and arraySize must be 1 if dataType is Byte.
	int SetParamType(int paramIndex, char * dataType, bool isArray, int arraySize);
	char *GetParamType(int paramIndex, bool *isArray, int *arraySize);

	int SetParamValue(int paramIndex, int valueIndex, char * paramValue);
	char *GetParamValue(int paramIndex, int valueIndex);

	int SetParamValue(int paramIndex, VARIANT paramValue);
	VARIANT GetParamValue(int paramIndex);

	void SetApiName(const char * apiName);
	char * GetApiName()
	{
		return ApiName;
	};

	void SetSourceProcessId(long sourceProcessId);
	long GetSourceProcessId()
	{
		return SourceProcessId;
	};

	void SetNonce(const char * nonce);
	char *GetNonce()
	{
		return Nonce;
	}

	void SetSignatureObjectId(unsigned long sigObjId);
	unsigned long GetSignatureObjectId()
	{
		return SignatureObjectId;
	}

	void SetParamCount(int paramCount);
	int GetParamCount()
	{
		return ParamCount;
	}

	void Reset(void);
	char * GetPayloadXml(unsigned long * xmlByteSize);
	bool SetPayloadXml(const char * payloadXml);
private:
	bool ParsePayloadXml(const char *secureXML_Payload);
	bool CreatePayloadXml();
public:
	int SetParamValue(int paramIndex, int valueIndex, int paramValue);
	int GetParamIntegerValue(int paramIndex, int valueIndex);
	int SetParamValue(int paramIndex, int valueIndex, BSTR paramValue);
	SecureXmlPayload * InvokeAPI(void);
};
extern BSTR * GetBstrArrayFromVariant(VARIANT fileList, UINT *itemCount);
