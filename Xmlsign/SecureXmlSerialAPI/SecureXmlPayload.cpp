#include "stdafx.h"

#include "Signature.h"
#include "SecureXmlPayload.h"
#include "BufferVariant.h"
#include <securexml/base64.h>

#ifndef WIN32
#include <securexml/CharConversion.h>
#include <unistd.h>
#else
#include <process.h>
#define getpid _getpid
#endif
#include <securexml/DebugLog.h>

extern unsigned char * HeapW2A(BSTR bstrStr);
extern void s_log(const char* format, ...);

BSTR * GetBstrArrayFromVariant(VARIANT fileList, UINT *itemCount)
{
	VARIANT **vA;
	UINT arrayDim, elementSize;
	long lBound, uBound;
	VARTYPE arrayType;
	long elementCount;
	BSTR	*bstrList = NULL;
	BSTR	tmpBstr;
	VARIANT *fList;
	BSTR tmpCcBstr;
	UINT numElements=0;

//USES_CONVERSION;
	EnterLog;
	fList = &fileList;
	*itemCount = 0;

	if (fileList.vt == 0x400c)
	{
		fList = fileList.pvarVal;
	}

	if (fList->vt == VT_BSTR) // This is just a BSTR so there is just one file being signed
	{
		tmpCcBstr = fList->bstrVal;
		if (SysStringLen(tmpCcBstr) == 0)
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
						if (SysStringLen(tmpCcBstr) == 0)
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
						if (SysStringLen(tmpCcBstr) == 0)
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
							if (SysStringLen(tmpCcBstr) == 0)
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
	}
getBstrArrayExit:
	ExitLog;
	return bstrList;
}


SecureXmlPayload::SecureXmlPayload(void)
: ApiName(NULL)
, SourceProcessId(0)
, Nonce(NULL)
, SignatureObjectId(0)
, ParamCount(0)
{
	EnterLog;
	doc = NULL;
	charXmlDocPtr = NULL;
	memset(ValueArray, 0, sizeof(char *)*MAXPARAMCOUNT*MAXVALUECOUNT);
	ParamIsArrayArray = NULL;
	ParamArraySizeArray = NULL;
	ParamTypeArray = NULL;
	for (int i=0; i < MAXPARAMCOUNT; i++)
		VariantInit(&VariantParamValue[i]);
	oPayload = NULL;
	ExitLog;
}

SecureXmlPayload::SecureXmlPayload(const char *apiName, long sourceProcessId, const char *nonce,
					unsigned long signatureObjectId, int paramCount)
{
	EnterLog;
	SetApiName(apiName);
	SetSourceProcessId(sourceProcessId);
	SetNonce(nonce);
	SetSignatureObjectId(signatureObjectId);
	SetParamCount(paramCount);
	ExitLog;
}

SecureXmlPayload::~SecureXmlPayload(void)
{
	EnterLog;
	Reset();
	ExitLog;
}


// Valid input for dataType are String, Integer, ShortInteger and Byte. isArray must be true and arraySize must be 1 if dataType is Byte.
int SecureXmlPayload::SetParamType(int paramIndex, char * dataType, bool isArray, int arraySize)
{
	EnterLog;
	if (paramIndex < ParamCount)
	{
		strcpy(ParamTypeArray[paramIndex].paramType, (const char *)dataType);
		ParamIsArrayArray[paramIndex] = isArray;
		if (!isArray)
			ParamArraySizeArray[paramIndex] = 1;
		else
			ParamArraySizeArray[paramIndex] = arraySize;

	}
	ExitLog;
	return 0;
}

int SecureXmlPayload::SetParamValue(int paramIndex, int valueIndex, char * paramValue)
{
	EnterLog;
	if (paramIndex < ParamCount)
	{
		if (valueIndex < ParamArraySizeArray[paramIndex])
		{
			if (paramValue != NULL)
			{
				ValueArray[paramIndex][valueIndex] = (char *)zMalloc(strlen(paramValue) + 1);
				strcpy(ValueArray[paramIndex][valueIndex], paramValue);
				if (valueIndex == (ParamArraySizeArray[paramIndex] - 1))
				{
					if (!(strcmp((const char *)ParamTypeArray[paramIndex].paramType, (const char *)"StringArray")))
					{
						VARIANT *outVariant;
						SAFEARRAY *outArray;
						SAFEARRAYBOUND rgsabound[1];
						HRESULT hr;
						
						outVariant = (VARIANT *)&VariantParamValue[paramIndex];

						VariantInit(outVariant);
						rgsabound[0].lLbound = 0;
						rgsabound[0].cElements = ParamArraySizeArray[paramIndex];

						outArray = SafeArrayCreate(VT_BSTR, 
													1,
													rgsabound);
						if (outArray == NULL)
						{
							return false;
						}
						for (long i=0; i<(long)ParamArraySizeArray[paramIndex]; i++)
						{
							BSTR arrElement;
							arrElement = A2WBSTR((LPCSTR)GetParamValue(paramIndex, i));
							hr = SafeArrayPutElement(outArray, &i, arrElement);
							if (hr != S_OK)
							{
								return false;
							}
						}
						(*outVariant).vt = (VT_ARRAY | VT_BSTR);
						(*outVariant).parray = outArray;
					}
					else
					{
						if ((!strcmp((const char *)ParamTypeArray[paramIndex].paramType, (const char *)"ByteArray")))
						{
							CBufferVariant m_binaryData;
							DWORD dwBytesToWrite = base64decodeSize((DWORD)strlen((const char *)paramValue));
							char *decodedDataPtr = (char *)zMalloc (dwBytesToWrite+1);
							memset(decodedDataPtr,0,dwBytesToWrite+1);
							dwBytesToWrite = base64decode((unsigned char *)paramValue,(unsigned char *)decodedDataPtr,dwBytesToWrite);
							m_binaryData.AssignData(decodedDataPtr, dwBytesToWrite);
							VariantParamValue[paramIndex] = m_binaryData.Copy();
							zFree(decodedDataPtr);
						}
					}
				}
			}
		}
	}
	ExitLog;
	return 0;
}

int SecureXmlPayload::SetParamValue(int paramIndex, VARIANT paramValue)
{
	UINT itemCount=0;
	BSTR	*bstrList=NULL;

	EnterLog;
	if (paramIndex < ParamCount)
	{
		VariantClear(&VariantParamValue[paramIndex]);
		VariantCopy(&VariantParamValue[paramIndex],&paramValue);
		if (!(strcmp((const char *)ParamTypeArray[paramIndex].paramType, (const char *)"StringArray")))
		{
			bstrList = GetBstrArrayFromVariant(paramValue, &itemCount);
			ParamArraySizeArray[paramIndex] = itemCount;
			for (int itemIndex=0; itemIndex < itemCount; itemIndex++)
			{
				ValueArray[paramIndex][itemIndex] = (char *)HeapW2A(bstrList[itemIndex]);
				SysFreeString(bstrList[itemIndex]);
			}
			zFree(bstrList);
		}
		else
		{ // It must be ByteArray but let's make sure
			if (!(strcmp((const char *)ParamTypeArray[paramIndex].paramType, (const char *)"ByteArray")))
			{
				CBufferVariant m_bufVariant(paramValue);
				DWORD dataSize = m_bufVariant.GetLength();
				DWORD cbData = base64encodeSize(dataSize);
				// allocate memory
				unsigned char *pbData = (unsigned char *)zMalloc(cbData +1);
				base64encode((unsigned char *)(char *)m_bufVariant,dataSize,(unsigned char*)pbData,cbData+1);
				*(pbData+cbData)='\0';
				ParamArraySizeArray[paramIndex] = 1;
				ValueArray[paramIndex][0] = (char *)pbData;
			}
		}
	}
	ExitLog;
	return 0;
}

int SecureXmlPayload::SetParamValue(int paramIndex, int valueIndex, int paramValue)
{
	EnterLog;
	if (paramIndex < ParamCount)
	{
		if (valueIndex < ParamArraySizeArray[paramIndex])
		{
			ValueArray[paramIndex][valueIndex] = (char *)zMalloc(32);
			memset(ValueArray[paramIndex][valueIndex], 0, 32);
			sprintf(ValueArray[paramIndex][valueIndex],"%d", paramValue);
			if (valueIndex == (ParamArraySizeArray[paramIndex] - 1))
			{
				VARIANT *outVariant;
				SAFEARRAY *outArray;
				SAFEARRAYBOUND rgsabound[1];
				HRESULT hr;
				
				outVariant = (VARIANT *)&VariantParamValue[paramIndex];

				VariantInit(outVariant);
				rgsabound[0].lLbound = 0;
				rgsabound[0].cElements = ParamArraySizeArray[paramIndex];

				outArray = SafeArrayCreate(VT_BSTR, 
											1,
											rgsabound);
				if (outArray == NULL)
				{
					return false;
				}
				for (long i=0; i<(long)ParamArraySizeArray[paramIndex]; i++)
				{
					BSTR arrElement;
					arrElement = A2WBSTR((LPCSTR)GetParamValue(paramIndex, i));
					hr = SafeArrayPutElement(outArray, &i, arrElement);
					if (hr != S_OK)
					{
						return false;
					}
				}
				(*outVariant).vt = (VT_ARRAY | VT_BSTR);
				(*outVariant).parray = outArray;
			}
		}
	}
	ExitLog;
	return 0;
}

int SecureXmlPayload::SetParamValue(int paramIndex, int valueIndex, BSTR paramValue)
{
	unsigned char *charParamValue = NULL;
	charParamValue = HeapW2A(paramValue);
	SetParamValue(paramIndex, valueIndex, (char *)charParamValue);
	zFree(charParamValue);
	return 0;
}

char * SecureXmlPayload::GetParamType(int paramIndex, bool *isArray, int *arraySize)
{
	EnterLog;
	*isArray = ParamIsArrayArray[paramIndex];
	*arraySize = ParamArraySizeArray[paramIndex];
	ExitLog;
	return ParamTypeArray[paramIndex].paramType;
}


char *SecureXmlPayload::GetParamValue(int paramIndex, int valueIndex)
{
	EnterLog;
	if (paramIndex < ParamCount)
	{
		if (valueIndex < ParamArraySizeArray[paramIndex])
		{
			ExitLog;
			return ValueArray[paramIndex][valueIndex];
		}
	}
	ExitLog;
	return NULL;
}

VARIANT SecureXmlPayload::GetParamValue(int paramIndex)
{
	VARIANT v;
	VariantInit(&v);
	EnterLog;
	if (paramIndex < ParamCount)
	{
		ExitLog;
		return VariantParamValue[paramIndex];
	}
	ExitLog;
	return v;
}

int SecureXmlPayload::GetParamIntegerValue(int paramIndex, int valueIndex)
{
	return (atoi((const char *)GetParamValue(paramIndex, valueIndex)));
}

void SecureXmlPayload::SetApiName(const char * apiName)
{
	EnterLog;
	if (ApiName != NULL)
		zFree(ApiName);
	ApiName = (char *)zMalloc(strlen(apiName) + 1);
	strcpy(ApiName, apiName);
	ExitLog;
}

void SecureXmlPayload::SetSourceProcessId(long sourceProcessId)
{
	EnterLog;
	SourceProcessId = sourceProcessId;
	ExitLog;
}

void SecureXmlPayload::SetNonce(const char * nonce)
{
	EnterLog;
	if (Nonce != NULL)
		zFree(Nonce);
	Nonce = (char *)zMalloc(strlen(nonce) + 1);
	strcpy(Nonce, nonce);
	ExitLog;
}

void SecureXmlPayload::SetSignatureObjectId(unsigned long sigObjId)
{
	EnterLog;
	SignatureObjectId = sigObjId;
	ExitLog;
}

void SecureXmlPayload::SetParamCount(int paramCount)
{
	EnterLog;
	for (int i=0; i<ParamCount; i++)
	{
		if (ParamArraySizeArray != NULL)
			for (int j=0; j<ParamArraySizeArray[i]; j++)
			{
				if (ValueArray[i][j] != NULL)
					zFree(ValueArray[i][j]);
				ValueArray[i][j] = NULL;
			}
	}

	ParamCount = paramCount;

	if (ParamArraySizeArray != NULL)
		zFree(ParamArraySizeArray);
	ParamArraySizeArray = (int *)zMalloc(sizeof(int) * paramCount);
	memset(ParamArraySizeArray, 0, sizeof(int) * paramCount);

	if (ParamIsArrayArray != NULL)
		zFree(ParamIsArrayArray);
	ParamIsArrayArray = (bool *)zMalloc(sizeof(bool) * paramCount);
	memset(ParamIsArrayArray, 0, sizeof(bool) * paramCount);

	if (ParamTypeArray != NULL)
		zFree(ParamTypeArray);
	ParamTypeArray = (ParamTypeNamePtr)zMalloc(sizeof(ParamTypeName) * paramCount);
	memset(ParamTypeArray, 0, sizeof(ParamTypeName) * paramCount);
	ExitLog;
}

void SecureXmlPayload::Reset(void)
{
	EnterLog;
	for (int i=0; i<ParamCount; i++)
	{
		if (ParamArraySizeArray != NULL)
			for (int j=0; j<ParamArraySizeArray[i]; j++)
			{
				if (ValueArray[i][j] != NULL)
					zFree(ValueArray[i][j]);
				ValueArray[i][j] = NULL;
			}
		VariantClear(&VariantParamValue[i]);
		VariantInit(&VariantParamValue[i]);
	}

	if (ApiName != NULL)
		zFree(ApiName);
	ApiName = NULL;

	SourceProcessId = 0;

	if (Nonce != NULL)
		zFree(Nonce);
	Nonce = NULL;

	SignatureObjectId = 0;
	ParamCount = 0;

	if (doc != NULL)
		xmlFreeDoc(doc);
	doc = NULL;

	if (charXmlDocPtr != NULL)
		xmlFree(charXmlDocPtr);
	charXmlDocPtr = NULL;

	if (ParamArraySizeArray != NULL)
		zFree(ParamArraySizeArray);
	ParamArraySizeArray = NULL;

	if (ParamIsArrayArray != NULL)
		zFree(ParamIsArrayArray);
	ParamIsArrayArray = NULL;

	if (ParamTypeArray != NULL)
		zFree(ParamTypeArray);
	ParamTypeArray = NULL;
	if (oPayload != NULL)
		delete oPayload;
	oPayload = NULL;
	ExitLog;
}

char * SecureXmlPayload::GetPayloadXml(unsigned long * xmlByteSize)
{
	EnterLog;
	bool result = CreatePayloadXml();
	if ((result) && (doc != NULL))
	{
		if (charXmlDocPtr != NULL)
			xmlFree(charXmlDocPtr);
		xmlDocDumpMemory(doc,&charXmlDocPtr,&charXmlDocSize);
		*xmlByteSize = charXmlDocSize;
		ExitLog;
		return (char *) charXmlDocPtr;
	}
	else
	{
		ExitLog;
		return NULL;
	}
}

bool SecureXmlPayload::SetPayloadXml(const char * payloadXml)
{
	EnterLog;
	bool result = ParsePayloadXml(payloadXml);
	ExitLog;
	return result;
}

bool SecureXmlPayload::ParsePayloadXml(const char *secureXML_Payload)
{
	EnterLog;
	if (doc != NULL)
		xmlFreeDoc(doc);
	doc = xmlParseMemory((const char *)secureXML_Payload,(int) strlen((const char *)secureXML_Payload));
	xmlNodePtr root = xmlDocGetRootElement(doc);
	xmlNodePtr cur = root->xmlChildrenNode;
	xmlNodePtr parent = cur;
	xmlNodePtr cur1=NULL, cur2=NULL;
	for (; cur != NULL; cur = cur->next)
	{
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "SourceProcess_Id"))) 
		{
			char *sourceProcessId = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			SetSourceProcessId(atoi(sourceProcessId));
			xmlFree(sourceProcessId);
		}
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "Nonce"))) 
		{
			char *nonce = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			SetNonce((const char *)nonce);
			xmlFree(nonce);
		}
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "SignatureObject_Id"))) 
		{
			char *signatureObjectId = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			SetSignatureObjectId((unsigned long)atoi(signatureObjectId));
			xmlFree(signatureObjectId);
		}
		if (!(xmlStrcmp(cur->name, (const xmlChar *) "API"))) 
		{
			parent = cur;
			cur1 = cur->children;
			int paramIndex = 0;
			for (; cur1 != NULL; cur1 = cur1->next)
			{
				if (!(xmlStrcmp(cur1->name, (const xmlChar *)"API_Name")))
				{
					char *apiName = (char *)xmlNodeListGetString(doc, cur1->xmlChildrenNode, 1);
					SetApiName((const char *)apiName);
					xmlFree(apiName);
				}
				if (!(xmlStrcmp(cur1->name, (const xmlChar *)"Param_Count")))
				{
					char *paramCount = (char *)xmlNodeListGetString(doc, cur1->xmlChildrenNode, 1);
					SetParamCount(atoi((const char *)paramCount));
					xmlFree(paramCount);
				}
				if (!(xmlStrcmp(cur1->name, (const xmlChar *)"Param")))
				{
					char *paramType = (char *)xmlGetProp(cur1, (const xmlChar *)"Type");
					char *charArraySize = (char *)xmlGetProp(cur1, (const xmlChar *)"ArraySize");
					int arraySize = 1;
					bool isArray = false;
					if (charArraySize != NULL)
					{
						arraySize = atoi((const char *)charArraySize);
						if (arraySize > 1)
							isArray = true;
					}
					SetParamType(paramIndex, paramType, isArray, arraySize);

					xmlFree(paramType);
					xmlFree(charArraySize);
					int valueIndex = 0;
					cur2 = cur1->children;
					for (; (cur2 != NULL) && (valueIndex < arraySize); cur2 = cur2->next)
					{
						if (!(xmlStrcmp(cur2->name, (const xmlChar *)"Value")))
						{
							char *value = (char *)xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
							SetParamValue(paramIndex, valueIndex, value);
							xmlFree(value);
							valueIndex++;
						}
					}
					//VARIANT *outVariant;
					//SAFEARRAY *outArray;
					//SAFEARRAYBOUND rgsabound[1];
					//HRESULT hr;
					//
					//outVariant = (VARIANT *)&VariantParamValue[paramIndex];

					//VariantInit(outVariant);
					//rgsabound[0].lLbound = 0;
					//rgsabound[0].cElements = arraySize;

					//outArray = SafeArrayCreate(VT_BSTR, 
					//							1,
					//							rgsabound);
					//if (outArray == NULL)
					//{
					//	return false;
					//}
					//for (long i=0; i<(long)arraySize; i++)
					//{
					//	BSTR arrElement;
					//	arrElement = ::A2WBSTR((LPCSTR)GetParamValue(paramIndex, i));
					//	hr = SafeArrayPutElement(outArray, &i, arrElement);
					//	if (hr != S_OK)
					//	{
					//		return false;
					//	}
					//}
					//(*outVariant).vt = (VT_ARRAY | VT_BSTR);
					//(*outVariant).parray = outArray;
					paramIndex++;
				}
			}
			break;
		}
		//cur = parent->next;
		//parent = cur;
	}
	ExitLog;
	return true;
}
bool SecureXmlPayload::CreatePayloadXml()
{
	char buffer[64];
	xmlNodePtr cur=NULL, parent1=NULL, parent=NULL, rootNode=NULL;

	EnterLog;
	memset(buffer, 0, 64);

	if (doc != NULL)
		xmlFreeDoc(doc);
	doc = NULL;
	if (charXmlDocPtr != NULL)
		xmlFree(charXmlDocPtr);
	charXmlDocSize = 0;
	charXmlDocPtr = NULL;

	doc = xmlNewDoc((const unsigned char *)"1.0");

	// document, namespace, element name, element content
	cur = xmlNewDocNode(doc,NULL,(const unsigned char *)"SecureXML_Payload",NULL);

	// add root element
	xmlDocSetRootElement(doc,cur);
	rootNode = cur;

	cur = xmlNewNode(NULL,(const unsigned char *)"SourceProcess_Id"); 
	sprintf(buffer, (const char *)"%d", SourceProcessId);
	xmlNodeSetContent(cur,(const unsigned char *)buffer);
	cur = xmlAddChild(rootNode,cur);

	cur = xmlNewNode(NULL,(const unsigned char *)"Nonce"); 
	xmlNodeSetContent(cur,(const unsigned char *)Nonce);
	cur = xmlAddChild(rootNode,cur);

	cur = xmlNewNode(NULL,(const unsigned char *)"SignatureObject_Id"); 
	sprintf(buffer, (const char *)"%d", SignatureObjectId);
	xmlNodeSetContent(cur,(const unsigned char *)buffer);
	cur = xmlAddChild(rootNode,cur);

	cur = xmlNewNode(NULL,(const unsigned char *)"API"); 
	cur = xmlAddChild(rootNode,cur);
	parent = cur;

	cur = xmlNewNode(NULL,(const unsigned char *)"API_Name");
	xmlNodeSetContent(cur,(const unsigned char *)ApiName);
	cur = xmlAddChild(parent,cur);

	cur = xmlNewNode(NULL,(const unsigned char *)"Param_Count");
	sprintf(buffer, (const char *)"%d", ParamCount);
	xmlNodeSetContent(cur,(const unsigned char *)buffer);
	cur = xmlAddChild(parent,cur);

	for (int i=0; i < ParamCount; i++)
	{
		cur = xmlNewNode(NULL,(const unsigned char *)"Param");
		xmlNewProp(cur, (const unsigned char *)"Type", (const unsigned char *)ParamTypeArray[i].paramType);
		if ((ParamIsArrayArray[i] == true) && (ParamArraySizeArray[i] > 0))
		{
			sprintf(buffer, (const char *)"%d", ParamArraySizeArray[i]);
			xmlNewProp(cur, (const unsigned char *)"ArraySize", (const unsigned char *)buffer);
		}
		parent1 = cur;
		cur = xmlAddChild(parent, cur);
		for (int j=0; j < ParamArraySizeArray[i]; j++)
		{
			cur = xmlNewNode(NULL, (const unsigned char *)"Value");
			xmlNodeSetContent(cur,(const unsigned char *)ValueArray[i][j]);
			xmlAddChild(parent1,cur);
		}
	}
	ExitLog;
	return true;
}

SecureXmlPayload * SecureXmlPayload::InvokeAPI(void)
{
	SecureXmlPayload *iPayload = this;
	
	if (oPayload != NULL)
		delete oPayload;

	oPayload = new SecureXmlPayload();
	CSignature *sigObj=NULL;

	char *apiName = iPayload->GetApiName();
	oPayload->SetApiName((const char *)apiName);
	oPayload->SetNonce((const char *)iPayload->GetNonce());
	oPayload->SetSourceProcessId(getpid());

	if (!(strcmp((const char *)apiName, (const char *)"createSignatureObject")))
	{
		sigObj = new CSignature();
		oPayload->SetParamCount(1);
		oPayload->SetParamType(0, "Integer" , false, 1);
		oPayload->SetParamValue(0,0,(int) sigObj);
		oPayload->SetSignatureObjectId((unsigned long)sigObj);
		return oPayload;
	}
	sigObj = (CSignature *)iPayload->GetSignatureObjectId();
	if (sigObj == NULL)
	{
		return NULL;
	}
	else
	{
		oPayload->SetSignatureObjectId((unsigned long)sigObj);
		if (!(strcmp((const char *)apiName, (const char *)"destroySignatureObject")))
		{
			delete sigObj;
			sigObj = NULL;
			oPayload->SetParamCount(0);
			oPayload->SetSignatureObjectId(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getEnvelopingFlag")))
		{
			short pVal=0;
			sigObj->get_EnvelopingFlag(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "ShortInteger", false, 1);
			oPayload->SetParamValue(0,0, (int)pVal);
			return oPayload;
		}

		if (!(strcmp((const char *)apiName, (const char *)"setEnvelopingFlag")))
		{
			short pVal=0;
			sigObj->put_EnvelopingFlag((short)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getHostName")))
		{
			BSTR pVal=NULL;
			sigObj->get_HostName(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getRecipientCertificateStore")))
		{
			BSTR pVal=NULL;
			sigObj->get_RecipientCertificateStore(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setRecipientCertificateStore")))
		{
			BSTR newVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_RecipientCertificateStore(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignerCertificate")))
		{
			BSTR pVal=NULL;
			long sigIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			sigObj->get_SignerCertificate(sigIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setSignerCertificate")))
		{
			BSTR newVal=NULL;
			long sigIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->put_SignerCertificate(sigIndex, newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignatureID")))
		{
			BSTR pVal=NULL;
			long sigIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			sigObj->get_SignatureID(sigIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setSignatureID")))
		{
			BSTR newVal=NULL;
			long sigIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->put_SignatureID(sigIndex, newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getProperties")))
		{
			BSTR pVal=NULL;
			long sigIndex=0, propIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			propIndex = iPayload->GetParamIntegerValue(1,0);
			sigObj->get_Properties(sigIndex, propIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setProperties")))
		{
			BSTR newVal=NULL;
			long sigIndex=0, propIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			propIndex = iPayload->GetParamIntegerValue(1,0);
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(2,0));
			sigObj->put_Properties(sigIndex, propIndex, newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getBase64EncodeXML")))
		{
			BOOL pVal=0;
			sigObj->get_Base64EncodeXML(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0, (int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setBase64EncodeXML")))
		{
			sigObj->put_Base64EncodeXML((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getBase64DecodeXML")))
		{
			BOOL pVal=0;
			sigObj->get_Base64DecodeXML(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0, (int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setBase64DecodeXML")))
		{
			sigObj->put_Base64DecodeXML((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getDocumentURI")))
		{
			BSTR pVal=NULL;
			long sigIndex=0, uriIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			uriIndex = iPayload->GetParamIntegerValue(1,0);
			sigObj->get_DocumentURI(sigIndex, uriIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getDigestObjectStatus")))
		{
			BOOL pVal=FALSE;
			long sigIndex=0, uriIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			uriIndex = iPayload->GetParamIntegerValue(1,0);
			sigObj->get_DigestObjectStatus(sigIndex, uriIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getLanguage")))
		{
			BSTR pVal=NULL;
			sigObj->get_Language(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setLanguage")))
		{
			BSTR newVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_Language(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignatureStatus")))
		{
			BOOL pVal=FALSE;
			long sigIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			sigObj->get_SignatureStatus(sigIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getPhysicalSignatureUsage")))
		{
			long pVal=0;
			sigObj->get_PhysicalSignatureUsage(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0, (int)pVal);
			return oPayload;
		}

		if (!(strcmp((const char *)apiName, (const char *)"setPhysicalSignatureUsage")))
		{
			sigObj->put_PhysicalSignatureUsage((long)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setActiveCertificate")))
		{
			BSTR newVal=NULL;
			BOOL pVal=FALSE;
//s_log("Set active cert [%s]\n",iPayload->GetParamValue(0,0));
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->SetActiveCertificate(newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0, (int)pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getNetscapeStorePassword")))
		{
			BSTR pVal=NULL;
			sigObj->get_NetscapeStorePassword(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setNetscapeStorePassword")))
		{
			BSTR newVal=NULL;
			BOOL pVal=FALSE;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_NetscapeStorePassword(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getStoreName")))
		{
			BSTR pVal=NULL;
			sigObj->GetStoreName(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setStoreName")))
		{
			BSTR newVal=NULL;
			BOOL pVal=FALSE;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->SetStoreName(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"signXMLStr")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SignXMLStr(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"signDataStr")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->SignDataStr(newVal1, &pVal);
//BSTR err;
//sigObj->GetError(&err);
//s_log("Sign errors: %s\n", HeapW2A(err));
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCertificateInfo")))
		{
			BSTR pVal=NULL;
			long sigIndex=0, valIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			valIndex = iPayload->GetParamIntegerValue(1,0);
			sigObj->GetCertificateInfo(sigIndex, valIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"selectActiveCertificate")))
		{
			BSTR pVal=NULL;
			sigObj->SelectActiveCertificate(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getError")))
		{
			BSTR pVal=NULL;
			sigObj->GetError(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"readAll")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->ReadAll(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"saveXMLStr")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SaveXMLStr(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getPhysicalSignatureFile")))
		{
			BSTR pVal=NULL;
			sigObj->get_PhysicalSignatureFile(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setPhysicalSignatureFile")))
		{
			BSTR newVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_PhysicalSignatureFile(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCapturedSignatureFile")))
		{
			BSTR pVal=NULL;
			sigObj->get_CapturedSignatureFile(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"sign")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->Sign(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getIncludeCamResponse")))
		{
			BOOL pVal=0;
			sigObj->get_IncludeCamResponse(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0, (int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setIncludeCamResponse")))
		{
			sigObj->put_IncludeCamResponse((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"saveXMLSignature")))
		{
			BSTR newVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->SaveXMLSignature(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"verify")))
		{
			BSTR newVal=NULL;
			BOOL pVal=FALSE;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->Verify(newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0, (int)pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setOverwriteFile")))
		{
			sigObj->put_OverwriteFile((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"pFXExportCertificate")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->PFXExportCertificate(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"verifyDetached")))
		{
			BSTR newVal=NULL;
			BOOL pVal=FALSE;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->VerifyDetached(newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0, (int)pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getLastError")))
		{
			long pVal=0;
			sigObj->GetLastError(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0, (int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getX509Certificate")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->GetX509Certificate(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"viewCertificate")))
		{
			BSTR newVal=NULL;
			BOOL pVal=FALSE;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->ViewCertificate(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCertificateCount")))
		{
			long pVal=0;
			sigObj->get_CertificateCount(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0, (int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignedDocumentPath")))
		{
			BSTR pVal=FALSE;
			long sigIndex=0, uriIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			uriIndex = iPayload->GetParamIntegerValue(1,0);
			sigObj->get_SignedDocumentPath(sigIndex, uriIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignerSubject")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->get_SignerSubject(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCertIssuer")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->get_CertIssuer(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCertExpiry")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->get_CertExpiry(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCertSerialNumber")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->get_CertSerialNumber(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"fileExists")))
		{
			BSTR newVal=NULL;
			BOOL pVal=FALSE;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->FileExists(newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0, (int)pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getFailedUriCount")))
		{
			long pVal=FALSE;
			sigObj->get_FailedUriCount(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getTotalUriCount")))
		{
			long pVal=FALSE;
			sigObj->get_TotalUriCount(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getFailedUriFullPath")))
		{
			BSTR pVal=FALSE;
			long uriIndex=0;
			uriIndex = iPayload->GetParamIntegerValue(0,0);
			sigObj->get_FailedUriFullPath(uriIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setFailedUriFullPath")))
		{
			BSTR newVal=NULL;
			long uriIndex=0;
			uriIndex = iPayload->GetParamIntegerValue(0,0);
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->put_FailedUriFullPath(uriIndex, newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getFailedUri")))
		{
			BSTR pVal=FALSE;
			long uriIndex=0;
			uriIndex = iPayload->GetParamIntegerValue(0,0);
			sigObj->get_FailedUri(uriIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignatureCount")))
		{
			long pVal=FALSE;
			sigObj->get_SignatureCount(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"signHTML")))
		{
#ifdef WIN32
			BSTR pVal=FALSE;
			DWORD_PTR htmlDocument=0;
			htmlDocument = iPayload->GetParamIntegerValue(0,0);
			sigObj->SignHTML((IDispatch *)htmlDocument, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
#endif
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"secureXMLVerify")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->SecureXMLVerify(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCSP")))
		{
			BSTR newVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->SetCSP(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignedHTML")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->GetSignedHTML(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"signFile")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SignFile(newVal1, newVal2);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignedFileObject")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->GetSignedFileObject(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"signXMLEnveloped")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SignXMLEnveloped(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getVersion")))
		{
			BSTR pVal=NULL;
			sigObj->GetVersion(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getLicenseStatus")))
		{
			long pVal=NULL;
			sigObj->GetLicenseStatus(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getPropertyCount")))
		{
			long pVal=NULL;
			long sigIndex = iPayload->GetParamIntegerValue(0,0);
			sigObj->GetPropertyCount(sigIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"viewAnyCertificate")))
		{
			BSTR newVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->ViewAnyCertificate(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"verifyXMLStr")))
		{
			BSTR newVal=NULL;
			BOOL pVal=FALSE;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->VerifyXMLStr(newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0, (int)pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setActivePFXFileCert")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SetActivePFXFileCert(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"pFXExportActiveCertificate")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->PFXExportActiveCertificate(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getHostName")))
		{
			BSTR pVal=NULL;
			sigObj->get_HostName(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getTimeStampURL")))
		{
			BSTR pVal=NULL;
			sigObj->get_TimeStampURL(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setTimeStampURL")))
		{
			BSTR newVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_TimeStampURL(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getTimeStamping")))
		{
			BOOL pVal=NULL;
			sigObj->get_TimeStamping(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setTimeStamping")))
		{
			BOOL pVal=0;
			sigObj->put_TimeStamping((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setTimeStampFormat")))
		{
			LONG pVal=0;
			sigObj->put_TimeStampFormat((LONG)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getTimeStampFormat")))
		{
			long pVal=NULL;
			sigObj->get_TimeStampFormat(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getTimeStampCritical")))
		{
			long pVal=NULL;
			sigObj->get_TimeStampCritical(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setTimeStampCritical")))
		{
			LONG pVal=0;
			sigObj->put_TimeStampCritical((LONG)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getHostOsType")))
		{
			long pVal=NULL;
			sigObj->get_HostOsType(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCrlChecking")))
		{
			BOOL pVal=NULL;
			sigObj->get_CrlChecking(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCrlChecking")))
		{
			BOOL pVal=0;
			sigObj->put_CrlChecking((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSigCertStatus")))
		{
			long pVal=NULL;
			long sigIndex = iPayload->GetParamIntegerValue(0,0);
			BSTR atTime = A2WBSTR((LPCSTR)iPayload->GetParamValue(1, 0));
			long timeFormat = iPayload->GetParamIntegerValue(2,0);
			sigObj->get_SigCertStatus(sigIndex, atTime, timeFormat, &pVal);
			SysFreeString(atTime);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"verifyX509CertCRL")))
		{
			BOOL pVal=NULL;
			BSTR certData = A2WBSTR((LPCSTR)iPayload->GetParamValue(0, 0));
			BSTR atTime = A2WBSTR((LPCSTR)iPayload->GetParamValue(1, 0));
			long timeFormat = iPayload->GetParamIntegerValue(2,0);
			sigObj->VerifyX509CertCRL(certData, atTime, timeFormat, &pVal);
			SysFreeString(certData);
			SysFreeString(atTime);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"verifyPFXCertCRL")))
		{
			BOOL pVal=NULL;
			BSTR pfxFileName = A2WBSTR((LPCSTR)iPayload->GetParamValue(0, 0));
			BSTR pfxPassword = A2WBSTR((LPCSTR)iPayload->GetParamValue(1, 0));
			BSTR atTime = A2WBSTR((LPCSTR)iPayload->GetParamValue(2, 0));
			long timeFormat = iPayload->GetParamIntegerValue(3,0);
			sigObj->VerifyPFXCertCRL(pfxFileName, pfxPassword, atTime, timeFormat, &pVal);
			SysFreeString(pfxFileName);
			SysFreeString(pfxPassword);
			SysFreeString(atTime);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCRLLocation")))
		{
			VARIANT crlLocation = iPayload->GetParamValue(0);
			sigObj->put_CRLLocation(crlLocation);
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"verifyActiveCertificate")))
		{
			BOOL pVal=NULL;
			sigObj->VerifyActiveCertificate(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCertificatePolicy")))
		{
			VARIANT crlLocation = iPayload->GetParamValue(0);
			sigObj->put_CertificatePolicy(crlLocation);
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getAuthorityConstrainedPolicy")))
		{
			VARIANT pVal;
			sigObj->get_AuthorityConstrainedPolicy(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "StringArray", true, 1);
			oPayload->SetParamValue(0,pVal);
			VariantClear(&pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getUserConstrainedPolicy")))
		{
			VARIANT pVal;
			sigObj->get_UserConstrainedPolicy(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "StringArray", true, 1);
			oPayload->SetParamValue(0,pVal);
			VariantClear(&pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCertificatePolicyChecking")))
		{
			BOOL pVal=0;
			sigObj->put_CertificatePolicyChecking((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCertificateChainValidation")))
		{
			BOOL pVal=0;
			sigObj->put_CertificateChainValidation((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCertificatePathLengthChecking")))
		{
			BOOL pVal=0;
			sigObj->put_CertificatePathLengthChecking((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setConfigFileName")))
		{
			BSTR newVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_ConfigFileName(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setDoDCompliance")))
		{
			BOOL pVal=0;
			sigObj->put_DoDCompliance((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCertificatePolicyExplicit")))
		{
			BOOL pVal=NULL;
			sigObj->get_CertificatePolicyExplicit(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCertificatePolicyExplicit")))
		{
			BOOL pVal=0;
			sigObj->put_CertificatePolicyExplicit((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCertificateTrustExplicit")))
		{
			BOOL pVal=0;
			sigObj->put_CertificateTrustExplicit((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"signXMLXpathStr")))
		{
			BSTR pVal=NULL;
			BSTR xmlStr = A2WBSTR((LPCSTR)iPayload->GetParamValue(0, 0));
			BSTR xPathExp = A2WBSTR((LPCSTR)iPayload->GetParamValue(1, 0));
			BSTR signatureId = A2WBSTR((LPCSTR)iPayload->GetParamValue(2, 0));
			sigObj->SignXMLXpathStr(xmlStr, xPathExp, signatureId, &pVal);
			SysFreeString(xmlStr);
			SysFreeString(xPathExp);
			SysFreeString(signatureId);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getUseHMAC")))
		{
			BOOL pVal=NULL;
			sigObj->get_UseHMAC(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setUseHMAC")))
		{
			BOOL pVal=0;
			sigObj->put_UseHMAC((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"changeOrAddProperty")))
		{
			BSTR propertyName = A2WBSTR((LPCSTR)iPayload->GetParamValue(0, 0));
			BSTR propertyValue = A2WBSTR((LPCSTR)iPayload->GetParamValue(1, 0));
			sigObj->ChangeOrAddProperty(propertyName, propertyValue);
			SysFreeString(propertyValue);
			SysFreeString(propertyName);
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setDetailedVerificationFlag")))
		{
			BOOL pVal=0;
			sigObj->put_DetailedVerificationFlag((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"captureLiveSignature")))
		{
			BSTR pVal=NULL;
			sigObj->CaptureLiveSignature(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setExcludeSignerCertificate")))
		{
			BOOL pVal=0;
			sigObj->put_ExcludeSignerCertificate((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"coSignXMLStr")))
		{
			BSTR newVal=NULL;
			BSTR pVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->CoSignXMLStr(newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"coSignFile")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->CoSignFile(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"signFiles")))
		{
			BSTR pVal=NULL;
			VARIANT fileList = iPayload->GetParamValue(0);
			BSTR outFileName = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SignFiles(fileList, outFileName, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setRecipientCertificates")))
		{
			VARIANT newVal = iPayload->GetParamValue(0);
			sigObj->put_RecipientCertificates(newVal);
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"encryptStr")))
		{
			BSTR newVal=NULL;
			BSTR pVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->EncryptStr(newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"decryptStr")))
		{
			BSTR newVal=NULL;
			BSTR pVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->DecryptStr(newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"encryptFile")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->EncryptFile(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"decryptFile")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->DecryptFile(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setTrustedRoots")))
		{
			VARIANT newVal = iPayload->GetParamValue(0);
			sigObj->put_TrustedRoots(newVal);
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setRecipientCertificateFiles")))
		{
			VARIANT newVal = iPayload->GetParamValue(0);
			sigObj->put_RecipientCertificateFiles(newVal);
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setDetachedObjects")))
		{
			VARIANT newVal = iPayload->GetParamValue(0);
			sigObj->put_DetachedObjects(newVal);
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setAttachedObjects")))
		{
			VARIANT newVal = iPayload->GetParamValue(0);
			sigObj->put_AttachedObjects(newVal);
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"readAllBase64")))
		{
			BSTR newVal=NULL;
			BSTR pVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->ReadAllBase64(newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setDecryptionPFXCertFile")))
		{
			BSTR newVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_DecryptionPFXCertFile(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setDecryptUsingPFXFileCert")))
		{
			BOOL pVal=0;
			sigObj->put_DecryptUsingPFXFileCert((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setDecryptionPFXPassword")))
		{
			BSTR newVal= A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_DecryptionPFXPassword(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setXpathNamespace")))
		{
			VARIANT newVal = iPayload->GetParamValue(0);
			sigObj->put_XpathNamespace(newVal);
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCamServerHost")))
		{
			BSTR pVal=NULL;
			sigObj->get_CamServerHost(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCamServerHost")))
		{
			BSTR newVal= A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_CamServerHost(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getAgencyId")))
		{
			BSTR pVal=NULL;
			sigObj->get_AgencyId(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setAgencyId")))
		{
			BSTR newVal= A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_AgencyId(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCamServerPort")))
		{
			USHORT pVal=NULL;
			sigObj->get_CamServerPort(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "ShortInteger", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCamServerPort")))
		{
			sigObj->put_CamServerPort((USHORT)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getUseCam")))
		{
			BOOL pVal=NULL;
			sigObj->get_UseCam(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setUseCam")))
		{
			sigObj->put_UseCam((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCamValidationResponse")))
		{
			BSTR pVal=NULL;
			sigObj->get_CamValidationResponse(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSigPropValueByName")))
		{
			BSTR pVal=FALSE;
			long sigIndex = iPayload->GetParamIntegerValue(0,0);
			BSTR propName = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->GetSigPropValueByName(sigIndex, propName, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"base64DecodeBufferToFile")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->Base64DecodeBufferToFile(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"base64DecodeFileToFile")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->Base64DecodeFileToFile(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"gunZipFile")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->GunZipFile(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCertSerialNumberFormat")))
		{
			LONG pVal=NULL;
			sigObj->get_CertSerialNumberFormat(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCertSerialNumberFormat")))
		{
			sigObj->put_CertSerialNumberFormat((LONG)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"secureXMLVerifyFileToBuffer")))
		{
			BSTR newVal=NULL;
			BSTR pVal=NULL;
			newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->SecureXMLVerifyFileToBuffer(newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"secureXMLVerifyFileToFile")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SecureXMLVerifyFileToFile(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"deleteSignatureFromXMLStr")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->DeleteSignatureFromXMLStr(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"deleteSignatureFromFile")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			BSTR newVal3 = A2WBSTR((LPCSTR)iPayload->GetParamValue(2,0));
			sigObj->DeleteSignatureFromFile(newVal1, newVal2, newVal3, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			SysFreeString(newVal3);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setAllowedCertIssuerNames")))
		{
			VARIANT newVal = iPayload->GetParamValue(0);
			sigObj->put_AllowedCertIssuerNames(newVal);
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCRLCacheDbConnectionString")))
		{
			BSTR pVal=NULL;
			sigObj->get_CRLCacheDbConnectionString(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCRLCacheDbConnectionString")))
		{
			BSTR newVal= A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_CRLCacheDbConnectionString(newVal);
			oPayload->SetParamCount(0);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getUseCRLCache")))
		{
			BOOL pVal=NULL;
			sigObj->get_UseCRLCache(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setUseCRLCache")))
		{
			sigObj->put_UseCRLCache((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCRLCacheTimeoutInMinutes")))
		{
			sigObj->put_CRLCacheTimeoutInMinutes((ULONG)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCanonicalizationMethod")))
		{
			sigObj->put_CanonicalizationMethod((ULONG)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
#ifdef WIN32
		if (!(strcmp((const char *)apiName, (const char *)"setActivePEMFileCert")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SetActivePEMFileCert(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
#endif
		if (!(strcmp((const char *)apiName, (const char *)"getSecureXMLPath")))
		{
			BSTR pVal=NULL;
			sigObj->get_SecureXMLPath(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignedDocumentCount")))
		{
			LONG pVal=NULL;
			sigObj->get_SignedDocumentCount((LONG)iPayload->GetParamIntegerValue(0,0),&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"signXMLByteArray")))
		{
			VARIANT pVal;
			VARIANT xmlByteArray = iPayload->GetParamValue(0);
			BSTR	newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SignXMLByteArray(xmlByteArray, newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "ByteArray", false, 1);
			oPayload->SetParamValue(0,pVal);
			VariantClear(&pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"saveXMLByteArray")))
		{
			BSTR pVal;
			VARIANT xmlByteArray = iPayload->GetParamValue(0);
			BSTR	newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SaveXMLByteArray(xmlByteArray, newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"readAllByteArray")))
		{
			VARIANT pVal;
			BSTR	newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->ReadAllByteArray(newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "ByteArray", false, 1);
			oPayload->SetParamValue(0,pVal);
			VariantClear(&pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"verifyXMLByteArray")))
		{
			BOOL pVal;
			VARIANT xmlByteArray = iPayload->GetParamValue(0);
			sigObj->VerifyXMLByteArray(xmlByteArray, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"secureXMLVerifyByteArray")))
		{
			VARIANT pVal;
			VARIANT xmlByteArray = iPayload->GetParamValue(0);
			sigObj->SecureXMLVerifyByteArray(xmlByteArray, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "ByteArray", false, 1);
			oPayload->SetParamValue(0,pVal);
			VariantClear(&pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"signXMLXpathByteArray")))
		{
			VARIANT pVal;
			VARIANT xmlByteArray = iPayload->GetParamValue(0);
			BSTR	newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			BSTR	newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(2,0));
			sigObj->SignXMLXpathByteArray(xmlByteArray, newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "ByteArray", false, 1);
			oPayload->SetParamValue(0,pVal);
			VariantClear(&pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"signXMLEnvelopedByteArray")))
		{
			VARIANT pVal;
			VARIANT xmlByteArray = iPayload->GetParamValue(0);
			BSTR	newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SignXMLEnvelopedByteArray(xmlByteArray, newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "ByteArray", false, 1);
			oPayload->SetParamValue(0,pVal);
			VariantClear(&pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"base64DecodeByteArrayToFile")))
		{
			BSTR pVal;
			VARIANT xmlByteArray = iPayload->GetParamValue(0);
			BSTR	newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->Base64DecodeByteArrayToFile(xmlByteArray, newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(newVal1);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"base64DecodeByteArrayToByteArray")))
		{
			VARIANT pVal;
			VARIANT xmlByteArray = iPayload->GetParamValue(0);
			sigObj->Base64DecodeByteArrayToByteArray(xmlByteArray, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "ByteArray", false, 1);
			oPayload->SetParamValue(0,pVal);
			VariantClear(&pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"base64EncodeByteArrayToByteArray")))
		{
			VARIANT pVal;
			VARIANT xmlByteArray = iPayload->GetParamValue(0);
			sigObj->Base64EncodeByteArrayToByteArray(xmlByteArray, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "ByteArray", false, 1);
			oPayload->SetParamValue(0,pVal);
			VariantClear(&pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"base64EncodeByteArrayToFile")))
		{
			BSTR pVal;
			VARIANT xmlByteArray = iPayload->GetParamValue(0);
			BSTR	newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->Base64EncodeByteArrayToFile(xmlByteArray, newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(newVal1);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"base64EncodeStrToFile")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->Base64EncodeStrToFile(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"base64EncodeStrToStr")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->Base64EncodeStrToStr(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setActivePFXB64Data")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SetActivePFXB64Data(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getFloatingLicense")))
		{
			BSTR pVal=NULL;
			sigObj->get_FloatingLicense(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setFloatingLicense")))
		{
			BSTR newVal1=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_FloatingLicense(newVal1);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getLicensedUserCount")))
		{
			LONG pVal=0;
			sigObj->get_LicensedUserCount(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setIncludeCRLInSignature")))
		{
			sigObj->put_IncludeCRLInSignature((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getUsedCRLList")))
		{
			VARIANT pVal;
			sigObj->get_UsedCRLList(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "StringArray", true, 1);
			oPayload->SetParamValue(0,pVal);
			VariantClear(&pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getErrorDetail")))
		{
			BSTR pVal=NULL;
			sigObj->GetErrorDetail((LONG)iPayload->GetParamIntegerValue(0,0), &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setPhysicalSignatureB64Str")))
		{
			BSTR newVal1=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_PhysicalSignatureB64Str(newVal1);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignedInfoDigest")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->GetSignedInfoDigest(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getX509CertificateChain")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->GetX509CertificateChain(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setSignerCertificateChain")))
		{
			BSTR newVal1=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_SignerCertificateChain(newVal1);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setSignatureImageId")))
		{
			BSTR newVal1=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_SignatureImageId(newVal1);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignatureImageId")))
		{
			BSTR pVal=NULL;
			sigObj->get_SignatureImageId(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"signSignedInfoDigest")))
		{
			BSTR newVal1=NULL, newVal2=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			newVal2 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->SignSignedInfoDigest(newVal1, newVal2, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			SysFreeString(newVal2);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"applySignatureValue")))
		{
			BSTR newVal1=NULL;
			BSTR pVal=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->ApplySignatureValue(newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignedInfoDigestFromByteArray")))
		{
			BSTR pVal;
			VARIANT xmlByteArray = iPayload->GetParamValue(0);
			BSTR	newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(1,0));
			sigObj->GetSignedInfoDigestFromByteArray(xmlByteArray, newVal1, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(newVal1);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"applySignatureValueGetByteArray")))
		{
			VARIANT pVal;
			BSTR	newVal = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->ApplySignatureValueGetByteArray(newVal, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "ByteArray", false, 1);
			oPayload->SetParamValue(0,pVal);
			VariantClear(&pVal);
			SysFreeString(newVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignedDocumentB64Str")))
		{
			BSTR pVal=NULL;
			long sigIndex=0, uriIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			uriIndex = iPayload->GetParamIntegerValue(1,0);
			sigObj->GetSignedDocumentB64Str(sigIndex, uriIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignedDocumentByteArray")))
		{
			VARIANT pVal;
			long sigIndex=0, uriIndex=0;
			sigIndex = iPayload->GetParamIntegerValue(0,0);
			uriIndex = iPayload->GetParamIntegerValue(1,0);
			sigObj->GetSignedDocumentByteArray(sigIndex, uriIndex, &pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "ByteArray", false, 1);
			oPayload->SetParamValue(0,pVal);
			VariantClear(&pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCertValidationTransactionId")))
		{
			BSTR pVal=NULL;
			sigObj->get_CertValidationTransactionId(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setCertValidationTransactionId")))
		{
			BSTR newVal1=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_CertValidationTransactionId(newVal1);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getIgnoreIncompleteSignature")))
		{
			BOOL pVal=NULL;
			sigObj->get_IgnoreIncompleteSignature(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setIgnoreIncompleteSignature")))
		{
			sigObj->put_IgnoreIncompleteSignature((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getSignatureIndexToVerify")))
		{
			LONG pVal=NULL;
			sigObj->get_SignatureIndexToVerify(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setSignatureIndexToVerify")))
		{
			sigObj->put_SignatureIndexToVerify((LONG)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getUseOcsp")))
		{
			BOOL pVal=NULL;
			sigObj->get_UseOcsp(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setUseOcsp")))
		{
			sigObj->put_UseOcsp((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setOcspTrustedRespSignerCertPath")))
		{
			BSTR newVal1=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_OcspTrustedRespSignerCertPath(newVal1);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getOcspTrustedRespSignerCertPath")))
		{
			BSTR pVal=NULL;
			sigObj->get_OcspTrustedRespSignerCertPath(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setOcspReqSignerPFXCertPath")))
		{
			BSTR newVal1=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_OcspReqSignerPFXCertPath(newVal1);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getOcspReqSignerPFXCertPath")))
		{
			BSTR pVal=NULL;
			sigObj->get_OcspReqSignerPFXCertPath(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setOcspReqSignerPFXCertPassword")))
		{
			BSTR newVal1=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_OcspReqSignerPFXCertPassword(newVal1);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getOcspReqSignerPFXCertPassword")))
		{
			BSTR pVal=NULL;
			sigObj->get_OcspReqSignerPFXCertPassword(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setOcspResponderURL")))
		{
			BSTR newVal1=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_OcspResponderURL(newVal1);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getOcspResponderURL")))
		{
			BSTR pVal=NULL;
			sigObj->get_OcspResponderURL(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getOcspTextResponse")))
		{
			BSTR pVal=NULL;
			sigObj->get_OcspTextResponse(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getOcspB64Response")))
		{
			BSTR pVal=NULL;
			sigObj->get_OcspB64Response(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCertRevocationDate")))
		{
			BSTR pVal=NULL;
			sigObj->get_CertRevocationDate(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getIncludeOcspResponse")))
		{
			LONG pVal=NULL;
			sigObj->get_IncludeOcspResponse(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setIncludeOcspResponse")))
		{
			sigObj->put_IncludeOcspResponse((LONG)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setProxyHost")))
		{
			BSTR newVal1=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_ProxyHost(newVal1);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setProxyPort")))
		{
			sigObj->put_ProxyPort((USHORT)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setProxyUserName")))
		{
			BSTR newVal1=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_ProxyUserName(newVal1);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setProxyPassword")))
		{
			BSTR newVal1=NULL;
			newVal1 = A2WBSTR((LPCSTR)iPayload->GetParamValue(0,0));
			sigObj->put_ProxyPassword(newVal1);
			oPayload->SetParamCount(0);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getAddWindowImage")))
		{
			BOOL pVal=NULL;
			sigObj->get_AddWindowImage(&pVal);
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "Integer", false, 1);
			oPayload->SetParamValue(0,0,(int)pVal);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setAddWindowImage")))
		{
			sigObj->put_AddWindowImage((BOOL)iPayload->GetParamIntegerValue(0,0));
			oPayload->SetParamCount(0);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"setInclusiveNamespacePrefixList")))
		{
			VARIANT crlLocation = iPayload->GetParamValue(0);
			sigObj->put_InclusiveNamespacePrefixList(crlLocation);
			oPayload->SetParamCount(0);
			return oPayload;
		}
	}
	return NULL;
}
