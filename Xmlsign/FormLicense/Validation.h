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
// Validation.h : Declaration of the CValidation

#pragma once
#include "resource.h"       // main symbols
#include "License.h"
#include <objsafe.h>


// IValidation
[
	object,
	uuid("9C2C7A7E-E901-43F4-91F5-869B20DC6A1A"),
	dual,	helpstring("IValidation Interface"),
	pointer_default(unique)
]
__interface IValidation : IDispatch
{
	[id(1), helpstring("method ValidateXmlWithSchema")] HRESULT ValidateXmlWithSchema([in] BSTR instanceXMLStr, [in] BSTR schemaXmlStr, [out,retval] ULONG* validationStatus);
	[id(2), helpstring("method ValidateFormLicense")] HRESULT ValidateFormLicense([in] BSTR formXmlStr, [out,retval] ULONG* validationStatus);
};



// CValidation

[
	coclass,
	threading("apartment"),
	vi_progid("FormLicense.Validation"),
	progid("FormLicense.Validation.1"),
	version(1.0),
	uuid("667A9827-D2EF-42D5-A9A7-4B6209ECBD04"),
	helpstring("Validation Class")
]
class ATL_NO_VTABLE CValidation : 
	public IValidation
{
public:
	CValidation();
	~CValidation();
BEGIN_CATEGORY_MAP(CValidation)
	IMPLEMENTED_CATEGORY(CATID_SafeForScripting)
	IMPLEMENTED_CATEGORY(CATID_SafeForInitializing)
END_CATEGORY_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	PGLOBAL_SIG	SigHandle;
	CLicense *licenseObj;

	STDMETHOD(ValidateXmlWithSchema)(BSTR instanceXMLStr, BSTR schemaXmlStr, ULONG* validationStatus);
	STDMETHOD(ValidateFormLicense)(BSTR formXmlStr, ULONG* validationStatus);
};

