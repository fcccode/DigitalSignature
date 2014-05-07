/*****************************************************************************************
 * Copyright: (c) 2000-2003 Infomosaic Corporation.
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
// Validation.cpp : Implementation of CValidation

#include "stdafx.h"
#include "Validation.h"
#include ".\validation.h"
#include <securexml/DebugLog.h>

extern "C" {
BOOL LogEnabled = FALSE;
}

unsigned char * HeapW2A(BSTR bstrStr)
{
	unsigned char *ptr, *newPtr=NULL, *curPtr=NULL; 
	unsigned int *szPtr;
	unsigned int sizeM;
	

	ptr = (unsigned char *)bstrStr;
	if (ptr == NULL)
		return NULL;
	szPtr = (unsigned int *)(ptr - sizeof(int));
	sizeM = (*szPtr)/2;
	newPtr = (unsigned char *)zMalloc(sizeM+1);
	curPtr=newPtr;

	for (unsigned int i=0; i<sizeM; i++)
	{
		*curPtr = *(unsigned char *)(bstrStr + i);
		curPtr++;
	}
	*curPtr = '\0';
	
	return(newPtr);
}

// CValidation
CValidation::CValidation()
{
	SigHandle = axInit();
	licenseObj = new CLicense();
}
CValidation::~CValidation()
{
	axFree(SigHandle);
	delete licenseObj;
}


STDMETHODIMP CValidation::ValidateXmlWithSchema(BSTR instanceXMLStr, BSTR schemaXmlStr, ULONG* validationStatus)
{
	unsigned char *charSchemaXmlStr, *charInstanceXmlStr;
	unsigned int instanceXmlStrSize;
	xmlDocPtr doc;

//DebugBreak();

	charSchemaXmlStr = (xmlChar *)HeapW2A(schemaXmlStr);
	if (charSchemaXmlStr == NULL)
	{
		*validationStatus = FALSE;
		return S_FALSE;
	}

	charInstanceXmlStr = (xmlChar *)HeapW2A(instanceXMLStr);
	if (charSchemaXmlStr == NULL)
	{
		*validationStatus = FALSE;
		zFree(charSchemaXmlStr);
		return S_FALSE;
	}
	instanceXmlStrSize = strlen((const char *)charInstanceXmlStr);
	doc = xmlParseMemory((const char *)charInstanceXmlStr, instanceXmlStrSize);
	zFree(charInstanceXmlStr);

	*validationStatus = licenseObj->validateXmlWithSchema(	charSchemaXmlStr, 
														doc, 
														SigHandle);
	xmlFreeDoc(doc);
	zFree(charSchemaXmlStr);

	return S_OK;
}

STDMETHODIMP CValidation::ValidateFormLicense(BSTR formXmlStr, ULONG* validationStatus)
{
	unsigned char *charFormXmlStr;
	unsigned int formXmlStrSize;
	xmlXPathContextPtr xpathPtr=NULL;
	xmlXPathObjectPtr xpathResultPtr=NULL;

	charFormXmlStr = HeapW2A(formXmlStr);
	if (charFormXmlStr == NULL)
	{
		*validationStatus = FALSE;
		return S_FALSE;
	}

	formXmlStrSize = strlen((const char *)charFormXmlStr);
//DebugBreak();
	*validationStatus = licenseObj->verifyTemplateSignature(charFormXmlStr, formXmlStrSize,
															SigHandle);
	if (*validationStatus != 0)
	{
		*validationStatus = licenseObj->verifyTemplateSchema(charFormXmlStr, SigHandle);
	}
	zFree(charFormXmlStr);
	return S_OK;
}
