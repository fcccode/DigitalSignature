// CertStore.h : Declaration of the CCertStore

#pragma once
#include "resource.h"       // main symbols
#include "NetscapeUtil.h"


// ICertStore
[
	object,
	uuid("0D61AA35-48D5-47F5-8249-F685F75250FD"),
	dual,	helpstring("ICertStore Interface"),
	pointer_default(unique)
]
__interface ICertStore : IDispatch
{
	[id(1), helpstring("method GetCertificateList")] HRESULT GetCertificateList([out] ULONG* certCount, [out,retval] BSTR *certArray);
	[propput, id(2), helpstring("property NetscapeStorePassword")] HRESULT NetscapeStorePassword([in] BSTR newVal);
	[id(3), helpstring("method ExportNetscapeCert")] HRESULT ExportNetscapeCert([in] BSTR certSerialNumber, [out,retval] BSTR* pfxFilePath);
};



// CCertStore

[
	coclass,
	threading("apartment"),
	vi_progid("NetscapeCert.CertStore"),
	progid("NetscapeCert.CertStore.1"),
	version(1.0),
	uuid("0A06154B-8FF9-48B2-A819-B68C327FC773"),
	helpstring("CertStore Class")
]
class ATL_NO_VTABLE CCertStore : 
	public ICertStore
{
public:
	CCertStore();
	~CCertStore();


	char *nsStoreHandle;
	char nsStorePassword[MAX_PATH];
	PCERT_DESCR *certList;
	int certListSize;


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

	STDMETHOD(GetCertificateList)(ULONG* certCount, BSTR* certArray);
	STDMETHOD(put_NetscapeStorePassword)(BSTR newVal);
	STDMETHOD(ExportNetscapeCert)(BSTR certSerialNumber, BSTR* pfxFilePath);
};

