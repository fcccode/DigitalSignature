#include "stdafx.h"

#include "Signature.h"
#include "SecureXmlPayload.h"

#ifndef WIN32
#include <securexml/CharConversion.h>
#endif
#include <securexml/DebugLog.h>

extern unsigned char * HeapW2A(BSTR bstrStr);


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

char * SecureXmlPayload::GetParamType(int paramIndex, bool *isArray, int *arraySize)
{
	EnterLog;
	*isArray = ParamIsArrayArray[paramIndex];
	*arraySize = ParamArraySizeArray[paramIndex];
	ExitLog;
	return ParamTypeArray[paramIndex].paramType;
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
	}
	ExitLog;
	return 0;
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

int SecureXmlPayload::SetParamValue(int paramIndex, VARIANT paramValue)
{
	UINT itemCount=0;
	BSTR	*bstrList=NULL;

	EnterLog;
	if (paramIndex < ParamCount)
	{
		VariantParamValue[paramIndex] = paramValue;
		bstrList = GetBstrArrayFromVariant(paramValue, &itemCount);
		ParamArraySizeArray[paramIndex] = itemCount;
		for (int itemIndex=0; itemIndex < itemCount; itemIndex++)
		{
			ValueArray[paramIndex][itemIndex] = (char *)HeapW2A(bstrList[itemIndex]);
			SysFreeString(bstrList[itemIndex]);
		}
		zFree(bstrList);
	}
	ExitLog;
	return 0;
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
					int arraySize = 0;
					bool isArray = false;
					if (charArraySize != NULL)
					{
						arraySize = atoi((const char *)charArraySize);
						if (arraySize != 0)
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
					VARIANT *outVariant;
					SAFEARRAY *outArray;
					SAFEARRAYBOUND rgsabound[1];
					HRESULT hr;
					
					outVariant = (VARIANT *)&VariantParamValue[paramIndex];

					VariantInit(outVariant);
					rgsabound[0].lLbound = 0;
					rgsabound[0].cElements = arraySize;

					outArray = SafeArrayCreate(VT_BSTR, 
												1,
												rgsabound);
					if (outArray == NULL)
					{
						return false;
					}
					for (long i=0; i<(long)arraySize; i++)
					{
						BSTR arrElement;
						arrElement = ::A2WBSTR((LPCSTR)GetParamValue(paramIndex, i));
						hr = SafeArrayPutElement(outArray, &i, arrElement);
						if (hr != S_OK)
						{
							return false;
						}
					}
					(*outVariant).vt = (VT_ARRAY | VT_BSTR);
					(*outVariant).parray = outArray;
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

int SecureXmlPayload::SetParamValue(int paramIndex, int valueIndex, int paramValue)
{
	ExitLog;
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

int SecureXmlPayload::GetParamIntegerValue(int paramIndex, int valueIndex)
{
	return (atoi((const char *)GetParamValue(paramIndex, valueIndex)));
}

int SecureXmlPayload::SetParamValue(int paramIndex, int valueIndex, BSTR paramValue)
{
	unsigned char *charParamValue = NULL;
	charParamValue = HeapW2A(paramValue);
	SetParamValue(paramIndex, valueIndex, (char *)charParamValue);
	zFree(charParamValue);
	return 0;
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
	oPayload->SetSourceProcessId(GetCurrentProcessId());

	sigObj = (CSignature *)iPayload->GetSignatureObjectId();
	if (!(strcmp((const char *)apiName, (const char *)"createSignatureObject")))
	{
		sigObj = new CSignature();
		oPayload->SetParamCount(1);
		oPayload->SetParamType(0, "Integer" , false, 1);
		oPayload->SetParamValue(0,0,(int) sigObj);
		oPayload->SetSignatureObjectId((unsigned long)sigObj);
		return oPayload;
	}
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
			oPayload->SetParamCount(1);
			oPayload->SetParamType(0, "String", false, 1);
			oPayload->SetParamValue(0,0,pVal);
			SysFreeString(pVal);
			SysFreeString(newVal1);
			return oPayload;
		}
		if (!(strcmp((const char *)apiName, (const char *)"getCertificateInfo")))
		{
			BSTR pVal=FALSE;
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
	}
#if 0
/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsignHTML
 * Signature: (ILjava/lang/Object;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CsignHTML
  (JNIEnv *, jobject, jint, jobject);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsecureXMLVerify
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CsecureXMLVerify
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCSP
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCSP
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetSignedHTML
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetSignedHTML
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsignFile
 * Signature: (ILjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsignFile
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetSignedFileObject
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetSignedFileObject
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsignXMLEnveloped
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CsignXMLEnveloped
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetVersion
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetVersion
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetLicenseStatus
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetLicenseStatus
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetPropertyCount
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetPropertyCount
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CviewAnyCertificate
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CviewAnyCertificate
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CverifyXMLStr
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CverifyXMLStr
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetActivePFXFileCert
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CsetActivePFXFileCert
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CpFXExportActiveCertificate
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CpFXExportActiveCertificate
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetHostName
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetHostName
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetTimeStampURL
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetTimeStampURL
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetTimeStampURL
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetTimeStampURL
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetTimeStamping
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetTimeStamping
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetTimeStamping
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetTimeStamping
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetTimeStampFormat
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetTimeStampFormat
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetTimeStampFormat
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetTimeStampFormat
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetTimeStampCritical
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetTimeStampCritical
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetTimeStampCritical
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetTimeStampCritical
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetHostOsType
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetHostOsType
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetCrlChecking
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetCrlChecking
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCrlChecking
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCrlChecking
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetSigCertStatus
 * Signature: (IILjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetSigCertStatus
  (JNIEnv *, jobject, jint, jint, jstring, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CverifyX509CertCRL
 * Signature: (ILjava/lang/String;Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CverifyX509CertCRL
  (JNIEnv *, jobject, jint, jstring, jstring, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CverifyPFXCertCRL
 * Signature: (ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CverifyPFXCertCRL
  (JNIEnv *, jobject, jint, jstring, jstring, jstring, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetAddWindowImage
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetAddWindowImage
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetAddWindowImage
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetAddWindowImage
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCRLLocation
 * Signature: (I[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCRLLocation
  (JNIEnv *, jobject, jint, jobjectArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CverifyActiveCertificate
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CverifyActiveCertificate
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCertificatePolicy
 * Signature: (I[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCertificatePolicy
  (JNIEnv *, jobject, jint, jobjectArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetAuthorityConstrainedPolicy
 * Signature: (I)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_infomosaic_securexml_SignatureImpl_CgetAuthorityConstrainedPolicy
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetUserConstrainedPolicy
 * Signature: (I)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_infomosaic_securexml_SignatureImpl_CgetUserConstrainedPolicy
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCertificatePolicyChecking
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCertificatePolicyChecking
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCertificateChainValidation
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCertificateChainValidation
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCertificatePathLengthChecking
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCertificatePathLengthChecking
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetConfigFileName
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetConfigFileName
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetDoDCompliance
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetDoDCompliance
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetCertificatePolicyExplicit
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetCertificatePolicyExplicit
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCertificatePolicyExplicit
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCertificatePolicyExplicit
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCertificateTrustExplicit
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCertificateTrustExplicit
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsignXMLXpathStr
 * Signature: (ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CsignXMLXpathStr
  (JNIEnv *, jobject, jint, jstring, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetUseHMAC
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetUseHMAC
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetUseHMAC
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetUseHMAC
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetHMACPassword
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetHMACPassword
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetHMACPassword
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetHMACPassword
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CchangeOrAddProperty
 * Signature: (ILjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CchangeOrAddProperty
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetDetailedVerificationFlag
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetDetailedVerificationFlag
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CcaptureLiveSignature
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CcaptureLiveSignature
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetExcludeSignerCertificate
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetExcludeSignerCertificate
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CcoSignXMLStr
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CcoSignXMLStr
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CcoSignFile
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CcoSignFile
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsignFiles
 * Signature: (I[Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CsignFiles
  (JNIEnv *, jobject, jint, jobjectArray, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetRecipientCertificates
 * Signature: (I[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetRecipientCertificates
  (JNIEnv *, jobject, jint, jobjectArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CencryptStr
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CencryptStr
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CdecryptStr
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CdecryptStr
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CencryptFile
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CencryptFile
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CdecryptFile
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CdecryptFile
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetTrustedRoots
 * Signature: (I[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetTrustedRoots
  (JNIEnv *, jobject, jint, jobjectArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetRecipientCertificateFiles
 * Signature: (I[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetRecipientCertificateFiles
  (JNIEnv *, jobject, jint, jobjectArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetDetachedObjects
 * Signature: (I[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetDetachedObjects
  (JNIEnv *, jobject, jint, jobjectArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetAttachedObjects
 * Signature: (I[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetAttachedObjects
  (JNIEnv *, jobject, jint, jobjectArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CreadAllBase64
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CreadAllBase64
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetDecryptionPFXCertFile
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetDecryptionPFXCertFile
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetDecryptUsingPFXFileCert
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetDecryptUsingPFXFileCert
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetDecryptionPFXPassword
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetDecryptionPFXPassword
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetXpathNamespace
 * Signature: (I[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetXpathNamespace
  (JNIEnv *, jobject, jint, jobjectArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetCamServerHost
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetCamServerHost
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCamServerHost
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCamServerHost
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetCamServerPort
 * Signature: (I)S
 */
JNIEXPORT jshort JNICALL Java_infomosaic_securexml_SignatureImpl_CgetCamServerPort
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCamServerPort
 * Signature: (IS)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCamServerPort
  (JNIEnv *, jobject, jint, jshort);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetUseCam
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetUseCam
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetUseCam
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetUseCam
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetAgencyId
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetAgencyId
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetAgencyId
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetAgencyId
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetCamValidationResponse
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetCamValidationResponse
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetSigPropValueByName
 * Signature: (IILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetSigPropValueByName
  (JNIEnv *, jobject, jint, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    Cbase64DecodeBufferToFile
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_Cbase64DecodeBufferToFile
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    Cbase64DecodeFileToFile
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_Cbase64DecodeFileToFile
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgunZipFile
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgunZipFile
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetCertSerialNumberFormat
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetCertSerialNumberFormat
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCertSerialNumberFormat
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCertSerialNumberFormat
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsecureXMLVerifyFileToBuffer
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CsecureXMLVerifyFileToBuffer
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsecureXMLVerifyFileToFile
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CsecureXMLVerifyFileToFile
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CdeleteSignatureFromXMLStr
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CdeleteSignatureFromXMLStr
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CdeleteSignatureFromFile
 * Signature: (ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CdeleteSignatureFromFile
  (JNIEnv *, jobject, jint, jstring, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetAllowedCertIssuerNames
 * Signature: (I[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetAllowedCertIssuerNames
  (JNIEnv *, jobject, jint, jobjectArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetCRLCacheDbConnectionString
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetCRLCacheDbConnectionString
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCRLCacheDbConnectionString
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCRLCacheDbConnectionString
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetUseCRLCache
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetUseCRLCache
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetUseCRLCache
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetUseCRLCache
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCRLCacheTimeoutInMinutes
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCRLCacheTimeoutInMinutes
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCanonicalizationMethod
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCanonicalizationMethod
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetActivePEMFileCert
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CsetActivePEMFileCert
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetSecureXMLPath
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetSecureXMLPath
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetSignedDocumentCount
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetSignedDocumentCount
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsignXMLByteArray
 * Signature: (I[BLjava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_SignatureImpl_CsignXMLByteArray
  (JNIEnv *, jobject, jint, jbyteArray, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsaveXMLByteArray
 * Signature: (I[BLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CsaveXMLByteArray
  (JNIEnv *, jobject, jint, jbyteArray, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CreadAllByteArray
 * Signature: (ILjava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_SignatureImpl_CreadAllByteArray
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CverifyXMLByteArray
 * Signature: (I[B)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CverifyXMLByteArray
  (JNIEnv *, jobject, jint, jbyteArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsecureXMLVerifyByteArray
 * Signature: (I[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_SignatureImpl_CsecureXMLVerifyByteArray
  (JNIEnv *, jobject, jint, jbyteArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsignXMLXpathByteArray
 * Signature: (I[BLjava/lang/String;Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_SignatureImpl_CsignXMLXpathByteArray
  (JNIEnv *, jobject, jint, jbyteArray, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsignXMLEnvelopedByteArray
 * Signature: (I[BLjava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_SignatureImpl_CsignXMLEnvelopedByteArray
  (JNIEnv *, jobject, jint, jbyteArray, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    Cbase64DecodeByteArrayToFile
 * Signature: (I[BLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_Cbase64DecodeByteArrayToFile
  (JNIEnv *, jobject, jint, jbyteArray, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    Cbase64DecodeByteArrayToByteArray
 * Signature: (I[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_SignatureImpl_Cbase64DecodeByteArrayToByteArray
  (JNIEnv *, jobject, jint, jbyteArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    Cbase64EncodeByteArrayToByteArray
 * Signature: (I[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_SignatureImpl_Cbase64EncodeByteArrayToByteArray
  (JNIEnv *, jobject, jint, jbyteArray);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    Cbase64EncodeByteArrayToFile
 * Signature: (I[BLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_Cbase64EncodeByteArrayToFile
  (JNIEnv *, jobject, jint, jbyteArray, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    Cbase64EncodeStrToFile
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_Cbase64EncodeStrToFile
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    Cbase64EncodeStrToStr
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_Cbase64EncodeStrToStr
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetActivePFXB64Data
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CsetActivePFXB64Data
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetFloatingLicense
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetFloatingLicense
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetFloatingLicense
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetFloatingLicense
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetLicensedUserCount
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetLicensedUserCount
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetIncludeCRLInSignature
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetIncludeCRLInSignature
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetUsedCRLList
 * Signature: (I)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_infomosaic_securexml_SignatureImpl_CgetUsedCRLList
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetErrorDetail
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetErrorDetail
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetPhysicalSignatureB64Str
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetPhysicalSignatureB64Str
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetSignedInfoDigest
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetSignedInfoDigest
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetX509CertificateChain
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetX509CertificateChain
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetSignerCertificateChain
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetSignerCertificateChain
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetSignatureImageId
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetSignatureImageId
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetSignatureImageId
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetSignatureImageId
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsignSignedInfoDigest
 * Signature: (ILjava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CsignSignedInfoDigest
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CapplySignatureValue
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CapplySignatureValue
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetSignedInfoDigestFromByteArray
 * Signature: (I[BLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetSignedInfoDigestFromByteArray
  (JNIEnv *, jobject, jint, jbyteArray, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CapplySignatureValueGetByteArray
 * Signature: (ILjava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_SignatureImpl_CapplySignatureValueGetByteArray
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetSignedDocumentB64Str
 * Signature: (III)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetSignedDocumentB64Str
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetSignedDocumentByteArray
 * Signature: (III)[B
 */
JNIEXPORT jbyteArray JNICALL Java_infomosaic_securexml_SignatureImpl_CgetSignedDocumentByteArray
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetCertValidationTransactionId
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetCertValidationTransactionId
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetCertValidationTransactionId
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetCertValidationTransactionId
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetIgnoreIncompleteSignature
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetIgnoreIncompleteSignature
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetIgnoreIncompleteSignature
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetIgnoreIncompleteSignature
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetSignatureIndexToVerify
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetSignatureIndexToVerify
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetSignatureIndexToVerify
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetSignatureIndexToVerify
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetUseOcsp
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetUseOcsp
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetUseOcsp
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetUseOcsp
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetOcspTrustedRespSignerCertPath
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetOcspTrustedRespSignerCertPath
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetOcspTrustedRespSignerCertPath
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetOcspTrustedRespSignerCertPath
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetOcspReqSignerPFXCertPath
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetOcspReqSignerPFXCertPath
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetOcspReqSignerPFXCertPath
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetOcspReqSignerPFXCertPath
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetOcspReqSignerPFXCertPassword
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetOcspReqSignerPFXCertPassword
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetOcspReqSignerPFXCertPassword
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetOcspReqSignerPFXCertPassword
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetOcspResponderURL
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetOcspResponderURL
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetOcspResponderURL
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetOcspResponderURL
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetOcspTextResponse
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetOcspTextResponse
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetOcspB64Response
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetOcspB64Response
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetCertRevocationDate
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_infomosaic_securexml_SignatureImpl_CgetCertRevocationDate
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CgetIncludeOcspResponse
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_infomosaic_securexml_SignatureImpl_CgetIncludeOcspResponse
  (JNIEnv *, jobject, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetIncludeOcspResponse
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetIncludeOcspResponse
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetProxyHost
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetProxyHost
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetProxyPort
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetProxyPort
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetProxyUserName
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetProxyUserName
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetProxyPassword
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetProxyPassword
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     infomosaic_securexml_SignatureImpl
 * Method:    CsetInclusiveNamespacePrefixList
 * Signature: (I[Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_infomosaic_securexml_SignatureImpl_CsetInclusiveNamespacePrefixList
  (JNIEnv *, jobject, jint, jobjectArray);
#endif
	return NULL;
}
