// ShowSelectCert.h : Declaration of the CShowSelectCert

#ifndef __SHOWSELECTCERT_H_
#define __SHOWSELECTCERT_H_

#include "stdafx.h"
#include "resource.h"       // main symbols
#include <atlhost.h>
#include <winuser.h>

#if __cplusplus
extern "C" {
#endif

#include <libxml/parser.h>
#include <securexml/ax.h>
#include <securexml/errors.h>
#include <securexml/utils.h>
#include <securexml/coresig.h>
#include <securexml/DebugLog.h>

#if __cplusplus
}
#endif

#include <securexml/base64.h>

extern unsigned char * HeapW2A(BSTR bstrStr);
/////////////////////////////////////////////////////////////////////////////
// CShowSelectCert
class CShowSelectCert : 
	public CAxDialogImpl<CShowSelectCert>
{
public:
//	class CSignature *curSig;
	PCERT_DESCR *cV;
	unsigned char* serialNo;
	WCHAR **issuer;
	WCHAR **subject;
	char **notAfter;
	char **decodedDataPtr;
	char * certificate;
	int count;
	short nCurrentRow;
	char* getCertificateData(int);
	BOOL certSelected;
	char StoreName[MAX_PATH];
	
	CShowSelectCert()
	{
		EnableWindow();
	}
	CShowSelectCert(/*CSignature *curSig,*/ unsigned char *storeName, PCERT_DESCR *cV, long certCount);
	
	virtual ~CShowSelectCert();

	enum { IDD = IDD_SHOWSELECTCERT };

BEGIN_MSG_MAP(CShowSelectCert)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)		
	NOTIFY_HANDLER(IDC_LIST2, NM_CLICK, OnClickList)
	COMMAND_HANDLER(IDC_BUTTON1, BN_CLICKED, OnClickedButton1)		
END_MSG_MAP()

	LRESULT CShowSelectCert::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CComBSTR caption;

		caption.LoadString(IDS_CAPTION);
		if (count != 0)
		{
			::SetWindowTextW(m_hWnd,caption);
			//Insert header		
			CreateHeader();
			
			// Inserts first Row with four columns .		

			for(int i=0;i<count;i++){		
				SetCell((LPWSTR)subject[i],i,0);
				SetCell((LPWSTR)issuer[i],i,1);
				BSTR tmpBstr;
				tmpBstr = A2WBSTR((LPCSTR)notAfter[i]);
				SetCell((LPWSTR)tmpBstr,i,2);
				SysFreeString(tmpBstr);
				tmpBstr = A2WBSTR((LPCSTR)decodedDataPtr[i]);
				SetCell((LPWSTR)tmpBstr,i,3);
				SysFreeString(tmpBstr);
			}
			CenterWindow();
			nCurrentRow = 0;
			setSelection();

		}
				
		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (nCurrentRow != -1)
			certSelected = TRUE;
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		certSelected = FALSE;
		EndDialog(wID);
		return 0;
	}
	void CShowSelectCert::CreateHeader()
	{
		CWindow listControl(GetDlgItem(IDC_LIST2));
		CComBSTR cstr;
		
		listControl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

		LVCOLUMNW list1;
		list1.mask =  LVCF_TEXT |LVCF_WIDTH| 
        LVCF_FMT |LVCF_SUBITEM;
		list1.fmt = LVCFMT_LEFT;
		
		cstr.LoadString(IDS_SERIALNO);
		list1.cx = 100;
		list1.pszText   = (LPWSTR) cstr;
			//L"Serial No";
		list1.iSubItem = 0;		
//		listControl.SendMessage(LVM_INSERTCOLUMN, (WPARAM)0,(WPARAM)&list1);
		::SendMessageW(listControl.m_hWnd, LVM_INSERTCOLUMNW, 0, (LPARAM)(const LV_ITEMW *)(&list1));
		
		cstr.LoadString(IDS_EXPDATE);
		list1.cx = 100;
		list1.pszText   = (LPWSTR) cstr;
			//L"Expiration Date";
		list1.iSubItem = 1;
//		listControl.SendMessage(LVM_INSERTCOLUMN, (WPARAM)0,(WPARAM)&list1);	
		SNDMSG(listControl.m_hWnd, LVM_INSERTCOLUMNW, 0, (LPARAM)(const LV_ITEMW *)(&list1));

		cstr.LoadString(IDS_ISSUEDBY);
		list1.cx = 100;
		list1.pszText   = (LPWSTR) cstr;
			//L"Issued by";
		list1.iSubItem = 2;
//		listControl.SendMessage(LVM_INSERTCOLUMN, (WPARAM)0,(WPARAM)&list1);
		SNDMSG(listControl.m_hWnd, LVM_INSERTCOLUMNW, 0, (LPARAM)(const LV_ITEMW *)(&list1));
		
		cstr.LoadString(IDS_ISSUEDTO);
		list1.cx = 100;
		list1.pszText   = (LPWSTR) cstr;
			//L"Issued To";
		list1.iSubItem = 3;
//		listControl.SendMessage(LVM_INSERTCOLUMN, (WPARAM)0,(WPARAM)&list1);
		SNDMSG(listControl.m_hWnd, LVM_INSERTCOLUMNW, 0, (LPARAM)(const LV_ITEMW *)(&list1));
	}
	void CShowSelectCert::SetCell(LPWSTR value, int nRow, int nCol)
	{
    
	CWindow listControl(GetDlgItem(IDC_LIST2));

    //Fill the LVITEM structure with the 
    //values given as parameters.
	
    LVITEMW lvItem;
    lvItem.mask = LVIF_TEXT;
    lvItem.iItem = nRow;
    lvItem.pszText = value;
    lvItem.iSubItem = nCol;
	lvItem.lParam = (LPARAM) value;
    if(nCol >0)
        
//		ListView_SetItem(listControl.m_hWnd,&lvItem);
		SNDMSG(listControl.m_hWnd, LVM_SETITEMW, 0, (LPARAM)(const LV_ITEMW *)(&lvItem));
		
    else
        //Insert the value into List
//        ListView_InsertItem(listControl.m_hWnd,&lvItem);
		  SNDMSG((listControl.m_hWnd), LVM_INSERTITEMW, 0, (LPARAM)(const LV_ITEMW *)(&lvItem));
	}

	LRESULT OnClickList(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{		
	
		LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pnmh;
		
		nCurrentRow = temp->iItem;	
		
		return 0;
	}
	char *CShowSelectCert::selectCertificate()
	{
//		DebugBreak();
		CComBSTR cstr;
		BYTE *msg1=NULL, *msg2=NULL;

		cstr.LoadString(IDS_MSGINSTALL);
		msg1 = HeapW2A(cstr);
		cstr.LoadString(IDS_MSGNOCERT);
		msg2 = HeapW2A(cstr);
		if (count != 0)
			DoModal();
		else
			MessageBox((LPCTSTR) msg1, (LPCTSTR) msg2, MB_OK);

		zFree(msg1);
		zFree(msg2);

		if(certSelected)
			return getCertificateData(nCurrentRow);
		else 
			return NULL;
	}

	void CShowSelectCert::setSelection()
	{
	CWindow listControl(GetDlgItem(IDC_LIST2));
	ListView_SetItemState(listControl, nCurrentRow, LVIS_SELECTED| LVIS_FOCUSED, LVIS_SELECTED| LVIS_FOCUSED); 
	}

	LRESULT OnClickedButton1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};
#endif //__SHOWSELECTCERT_H_
