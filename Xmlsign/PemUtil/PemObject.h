// PemObject.h : Declaration of the CPemObject

#pragma once
#include "resource.h"       // main symbols


// IPemObject
[
	object,
	uuid("12F2BF07-DC45-4684-A4BC-8A5F44984777"),
	dual,	helpstring("IPemObject Interface"),
	pointer_default(unique)
]
__interface IPemObject : IDispatch
{
	[id(1), helpstring("method CovertToPFX")] HRESULT CovertToPFX([in] BSTR pemFileName,[in] BSTR pemPassword, [out,retval] BSTR* pfxFilePath);
};



// CPemObject

[
	coclass,
	threading("apartment"),
	vi_progid("PemUtil.PemObject"),
	progid("PemUtil.PemObject.1"),
	version(1.0),
	uuid("D8F3211F-302F-45DB-8187-CDF6B7677D90"),
	helpstring("PemObject Class")
]
class ATL_NO_VTABLE CPemObject : 
	public IPemObject
{
public:
	CPemObject()
	{
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

	STDMETHOD(CovertToPFX)(BSTR pemFileName, BSTR pemPassword, BSTR* pfxFilePath);
};

