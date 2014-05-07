// CaptureImage.h : Declaration of the CCaptureImage

#pragma once
#include "resource.h"       // main symbols
#include <gdiplus.h>
#include <wtypes.h>
#include <string>

using namespace Gdiplus;
using namespace std;

extern "C" {
extern HINSTANCE hInst;
}


// ICaptureImage
[
	object,
	uuid("0674A7D1-0A9C-4FE4-B914-96BCC6EDC4CF"),
	dual,	helpstring("ICaptureImage Interface"),
	pointer_default(unique)
]
__interface ICaptureImage : IDispatch
{
	[id(1), helpstring("method CaptureCurrentWindowImage")] HRESULT CaptureCurrentWindowImage([out,retval] BSTR* WindowImageFileName);
	[propput, id(2), helpstring("property PhysicalSignatureFile")] HRESULT PhysicalSignatureFile([in] BSTR newVal);
	[propput, id(3), helpstring("property UpperX")] HRESULT UpperX([in] LONG newVal);
	[propput, id(4), helpstring("property UpperY")] HRESULT UpperY([in] LONG newVal);
	[propput, id(5), helpstring("property Width")] HRESULT Width([in] LONG newVal);
	[propput, id(6), helpstring("property Height")] HRESULT Height([in] LONG newVal);
	[id(7), helpstring("method ShowFileSignature")] HRESULT ShowFileSignature([in] BSTR guidStr, [out,retval] BSTR* outPngFilePath);
	[id(8), helpstring("method CaptureMouseSignature")] HRESULT CaptureMouseSignature([in] BSTR guidStr, [out,retval] BSTR* outPngFilePath);
};



// CCaptureImage

[
	coclass,
	threading("apartment"),
	vi_progid("SigWinImage.CaptureImage"),
	progid("SigWinImage.CaptureImage.1"),
	version(1.0),
	uuid("F18805CC-5075-4D36-BB01-76A4CAF6EE31"),
	helpstring("CaptureImage Class")
]
class ATL_NO_VTABLE CCaptureImage : 
	public ICaptureImage
{
public:
	CComBSTR	PhysicalSignatureFileName;
	CComBSTR	CapturedSignatureFileName;
	CComBSTR	WindowImageFileName[MAX_PATH+1];
	RECT	SignatureCaptureWindowDim;
	string	SigImageGuid;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

public:
	CCaptureImage();
	~CCaptureImage();

BEGIN_CATEGORY_MAP(CCaptureImage)
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

	STDMETHOD(CaptureCurrentWindowImage)(BSTR* WindowImageFileName);
	STDMETHOD(put_PhysicalSignatureFile)(BSTR newVal);
	STDMETHOD(put_UpperX)(LONG newVal);
	STDMETHOD(put_UpperY)(LONG newVal);
	STDMETHOD(put_Width)(LONG newVal);
	STDMETHOD(put_Height)(LONG newVal);
	STDMETHOD(ShowFileSignature)(BSTR guidStr, BSTR* outPngFilePath);
	STDMETHOD(CaptureMouseSignature)(BSTR guidStr, BSTR* outPngFilePath);
};

