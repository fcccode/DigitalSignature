#include "StdAfx.h"
#include "resource.h"
#include <fstream>

using namespace Gdiplus;

// Global Variables:
extern "C" {
extern HINSTANCE hInst;
}

static HWND hwnd, hwnd_dialogbar; 
static HWND hwndTB;


static TCHAR szTitle[MAX_PATH];			// The title bar text
static TCHAR szWindowClass[MAX_PATH];		// The title bar text
static char *FilePathBuffer;
static char *BmpFilePathBuffer;
static char TmpBmpFilePathBuffer[MAX_PATH+1];
static RECT *imageWindowDim;

static char *SigFileLabel = "File Signature";
static char *GuidStr = NULL;

extern INT GetEncoderClsid(const WCHAR* format, CLSID* pClsid);  // helper function
extern INT ConvertBmpToPng(char *bmpFilePath, char *pngFilePath);

extern PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
extern void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);

// CreateAToolBar creates a toolbar and adds a set of buttons to it.
// The function returns the handle to the toolbar if successful, 
// or NULL otherwise. 
// hwndParent is the handle to the toolbar's parent window. 
HWND CreateOKToolBar(HWND hwndParent) 
{ 
   TBBUTTON tbb[3]; 
   char szBuf[16]; 
   int iOK;
   INITCOMMONCONTROLSEX icex;

// Ensure that the common control DLL is loaded. 
   icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
   icex.dwICC  = ICC_BAR_CLASSES;
   InitCommonControlsEx(&icex);

// Create a toolbar. 
   hwndTB = CreateWindowEx(0, TOOLBARCLASSNAME, (LPSTR) NULL, 
        WS_CHILD | CCS_ADJUSTABLE | CCS_BOTTOM, 0, 0, 0, 0, hwndParent, 
        (HMENU) NULL, hInst, NULL); 

// Send the TB_BUTTONSTRUCTSIZE message, which is required for 
// backward compatibility. 
   SendMessage(hwndTB, TB_BUTTONSTRUCTSIZE, (WPARAM) sizeof(TBBUTTON), 0); 

// Add the button strings to the toolbar's internal string list. 
   LoadString(hInst, IDC_SIGOK, szBuf, 15); 
//Save room for second null terminator.
   iOK = strlen((const char *)szBuf);
   szBuf[iOK+2] = 0;
   iOK = SendMessage(hwndTB, TB_ADDSTRING, 0, (LPARAM) (LPSTR) szBuf); 

   // Fill the TBBUTTON array with button information, and add the 
// buttons to the toolbar. The buttons on this toolbar have text 
// but do not have bitmap images. 
   tbb[0].iBitmap = I_IMAGENONE; 
   tbb[0].idCommand = IDC_SIGOK; 
   tbb[0].fsState = TBSTATE_ENABLED; 
   tbb[0].fsStyle = BTNS_BUTTON; 
   tbb[0].dwData = 0; 
   tbb[0].iString = iOK; 
 
   SendMessage(hwndTB, TB_ADDBUTTONS, (WPARAM) 1, 
        (LPARAM) (LPTBBUTTON) &tbb); 


   SendMessage(hwndTB, TB_AUTOSIZE, 0, 0); 

   ShowWindow(hwndTB, SW_SHOW); 
   return hwndTB; 
}


//
//  FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//


LRESULT CALLBACK SigFileWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT psPaint;
	RECT window_rect;

	HDC hDC;

	PBITMAPINFO	pbmi;
	HBITMAP	bitmap;
	HDC		hdcCompatible;
	int Width, Height;

    RECT rcClient, tmpRect;                 // client area rectangle 

	char TempPath[MAX_PATH+1];
	static int labelWidth;
//	static GdiplusStartupInput gdiplusStartupInput;
//	static ULONG_PTR gdiplusToken;
	BSTR bstrFilePath;

USES_CONVERSION;
	
	switch (message) 
	{

		case WM_SIZE:
			GetClientRect(hWnd, &window_rect);
			SendMessage(hwndTB, TB_AUTOSIZE, 0, 0); 
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDC_SIGOK:
					hDC = GetDC(hWnd);
					hdcCompatible = CreateCompatibleDC(hDC);
					GetClientRect(hWnd, &window_rect);
					GetClientRect(hwndTB, &rcClient);
					Width = window_rect.right - window_rect.left;
					Height = (window_rect.bottom - window_rect.top) - (rcClient.bottom - rcClient.top);

					bitmap = CreateCompatibleBitmap(hDC, 
													Width, 
													Height);
					SelectObject(hdcCompatible, bitmap);

					BitBlt(hdcCompatible, 0,0, Width, Height, hDC, 0,0, SRCCOPY);
					pbmi = CreateBitmapInfoStruct(hWnd, bitmap);

					// Create a temporary file. 
					GetTempPath((DWORD)MAX_PATH+1, TempPath); 
					GetTempFileName(TempPath, // dir. for temp. files 
									"IMG",                // temp. file name prefix 
									0,                    // create unique name 
									(char *)TmpBmpFilePathBuffer);          // buffer for name 


					CreateBMPFile(hWnd, (char *)TmpBmpFilePathBuffer, pbmi, bitmap, hdcCompatible);
					GetTempFileName(TempPath, // dir. for temp. files 
									"IMG",                // temp. file name prefix 
									0,                    // create unique name 
									FilePathBuffer);          // buffer for name 
					ConvertBmpToPng((char *)TmpBmpFilePathBuffer, FilePathBuffer);
					DeleteFile((const char *)TmpBmpFilePathBuffer);

					ReleaseDC(hWnd, hDC);
					ReleaseDC(hWnd, hdcCompatible);
					DestroyWindow(hWnd);
					break;
					
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}


		case WM_DESTROY:
//			GdiplusShutdown(gdiplusToken);
			PostQuitMessage(0);
			break;

		case WM_PAINT:
			RECT windowRectSize;
			if (hDC = BeginPaint(hWnd, &psPaint)) 
			{
				GetClientRect(hWnd, &tmpRect);
				GetClientRect(hwndTB, &rcClient);
				windowRectSize.left = imageWindowDim->left;
				windowRectSize.top = imageWindowDim->top;

				if ((tmpRect.bottom - tmpRect.top) < imageWindowDim->bottom)
					windowRectSize.bottom = windowRectSize.top + imageWindowDim->bottom + rcClient.bottom;
				else
					windowRectSize.bottom = windowRectSize.top + tmpRect.bottom + rcClient.bottom;

				if ((tmpRect.right - tmpRect.left) < imageWindowDim->right)
					windowRectSize.right = imageWindowDim->left + imageWindowDim->right;
				else
					windowRectSize.right = imageWindowDim->left + tmpRect.right;


				bstrFilePath = A2WBSTR((LPCSTR) BmpFilePathBuffer);
			   // Create a RectF object that specifies the destination of the image.
			   RectF destRect(0, 0, imageWindowDim->right, imageWindowDim->bottom);


				Graphics graphics(hDC);
				Image image(bstrFilePath);
				//SetWindowPos( hWnd,
				//			  HWND_TOP,
				//			  windowRectSize.left,
				//			  windowRectSize.top,
				//			  windowRectSize.right - windowRectSize.left,
				//			  windowRectSize.bottom - windowRectSize.top,
				//			  SWP_SHOWWINDOW);


				graphics.DrawImage(&image, destRect);
				SysFreeString(bstrFilePath);

				labelWidth = rcClient.bottom + 50;
				tmpRect.top = windowRectSize.bottom - windowRectSize.top - labelWidth - 16;
				tmpRect.left = 0;
				tmpRect.bottom = tmpRect.top + 16;

				labelWidth += 16;

				SetTextColor(hDC, RGB(0x00, 0x99, 0x99));

				DrawText(hDC, SigFileLabel, strlen(SigFileLabel), &tmpRect, DT_LEFT);
				
				tmpRect.top = tmpRect.top - 14;
				tmpRect.bottom = tmpRect.top + 14;
				labelWidth += 14;

				DrawText(hDC, GuidStr, strlen(GuidStr), &tmpRect, DT_LEFT);

				EndPaint(hWnd, &psPaint);
			}
			break;

		case WM_CREATE:
			CreateOKToolBar(hWnd);
			// Initialize GDI+.
//			GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}




BOOL SigFileInitApplication(HINSTANCE hinstance) 
{ 
    WNDCLASSEX wcx; 
 
    // Fill in the window class structure with parameters 
    // that describe the main window. 
 
    wcx.cbSize = sizeof(wcx);          // size of structure 
    wcx.style = CS_HREDRAW | 
        CS_VREDRAW;                    // redraw if size changes 
    wcx.lpfnWndProc = SigFileWndProc;     // points to window procedure 
    wcx.cbClsExtra = 0;                // no extra class memory 
    wcx.cbWndExtra = 0;                // no extra window memory 
    wcx.hInstance = hinstance;         // handle to instance 
    wcx.hIcon = LoadIcon(NULL, 
        IDI_APPLICATION);              // predefined app. icon 
    wcx.hCursor = LoadCursor(NULL, 
        IDC_ARROW);                    // predefined arrow 
    wcx.hbrBackground = (struct HBRUSH__ *)GetStockObject( 
        WHITE_BRUSH);                  // white background brush 
    wcx.lpszMenuName =  (LPCSTR)NULL;// name of menu resource 
    wcx.lpszClassName = "MainFileImageClass";  // name of window class 
    wcx.hIconSm = (struct HICON__ *)LoadImage(hinstance, // small class icon 
        MAKEINTRESOURCE(5),
        IMAGE_ICON, 
        GetSystemMetrics(SM_CXSMICON), 
        GetSystemMetrics(SM_CYSMICON), 
        LR_DEFAULTCOLOR); 
 
    // Register the window class. 
 
    return RegisterClassEx(&wcx); 
} 

 
BOOL SigFileInitInstance(HINSTANCE hinstance, int nCmdShow, RECT *windowDim) 
{ 
	char ErrorMsg[100];


    // Create the main window. 
 
    hwnd = CreateWindow( 
        "MainFileImageClass",        // name of window class 
        "File Signature", // title-bar string 
        WS_OVERLAPPEDWINDOW, // top-level window 
        windowDim->left,       // default horizontal position 
        windowDim->top,       // default vertical position 
        windowDim->right + 60,       // default width 
        windowDim->bottom + 120,       // default height 
        (HWND) NULL,         // no owner window 
        (HMENU) NULL,        // use class menu 
        hinstance,           // handle to application instance 
        (LPVOID) NULL);      // no window-creation data 
 
    if (!hwnd) 
	{
		sprintf((char *)ErrorMsg, "%x", GetLastError());
		MessageBox(NULL, ErrorMsg, "Error", 1); 
        return FALSE;
	}

 
    // Show the window and send a WM_PAINT message to the window 
    // procedure. 
 
    ShowWindow(hwnd, nCmdShow); 
    UpdateWindow(hwnd);
    return TRUE; 
 
}

HRESULT	ShowFileSignature(char *filePathBuf, char *outFilePathBuf, BOOL sigCapturedOnce, RECT *windowDim, char *guidStr)
{
    MSG msg; 
//	HACCEL hAccelTable;

	memset(outFilePathBuf, 0, MAX_PATH);
	BmpFilePathBuffer = filePathBuf;
	FilePathBuffer = outFilePathBuf;
	GuidStr = guidStr;
	imageWindowDim = windowDim;

	//DebugBreak();

//	if (!sigCapturedOnce)
 		if (!SigFileInitApplication(hInst)) 
	       return FALSE; 

    if (!SigFileInitInstance(hInst, SW_SHOWNORMAL, windowDim)) 
        return FALSE;
	


	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
//		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
//		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
//		}
	}
	UnregisterClass("MainFileImageClass", hInst);

	return S_OK;
}