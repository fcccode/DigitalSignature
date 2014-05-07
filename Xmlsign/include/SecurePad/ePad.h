// ePad.h : Declaration of the CePad

#ifndef __EPAD_H_
#define __EPAD_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CePad
class ATL_NO_VTABLE CePad : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CePad, &CLSID_ePad>,
	public IDispatchImpl<IePad, &IID_IePad, &LIBID_SECUREPADLib>
{
public:
	CePad();

DECLARE_REGISTRY_RESOURCEID(IDR_EPAD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CePad)
	COM_INTERFACE_ENTRY(IePad)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IePad
public:
	STDMETHOD(SetPenColor)(/*[in]*/ long red, /*[in]*/ long green, /*[in]*/ long blue);
	STDMETHOD(get_Height)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Height)(/*[in]*/ long newVal);
	STDMETHOD(get_Width)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Width)(/*[in]*/ long newVal);
	STDMETHOD(get_UpperY)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_UpperY)(/*[in]*/ long newVal);
	STDMETHOD(get_UpperX)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_UpperX)(/*[in]*/ long newVal);
	STDMETHOD(GetEpadPropXML)(/*[out, retval]*/ BSTR *ePadPropXML);
	STDMETHOD(GetPhysicalSignature)(/*[in]*/ BSTR bstrGuidStr, /*[out, retval]*/ BSTR *sigFilePath);

	long UpperX, UpperY, Width, Height;
	long penColorRed, penColorGreen, penColorBlue;
};

#endif //__EPAD_H_
