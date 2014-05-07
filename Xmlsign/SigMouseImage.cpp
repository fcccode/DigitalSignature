#include "StdAfx.h"
#include "resource.h"
#include <list>
#include <fstream>
#include <securexml/DebugLog.h>

using namespace std ;

typedef list<POINT> POINTLIST;

using namespace Gdiplus;

// Global Variables:
extern "C" {
extern HINSTANCE hInst;
}
HWND hwnd, hwnd_dialogbar; 
HWND hwndTB;

POINTLIST *lst;
POINT csr;
unsigned prev_pkButtons;


TCHAR szTitle[MAX_PATH];			// The title bar text
TCHAR szWindowClass[MAX_PATH];		// The title bar text
char *FilePathBuffer;
char BmpFilePathBuffer[MAX_PATH+1];

char *MouseLabel = "Mouse Signature";
char *GuidStr = NULL;

INT GetEncoderClsid(const WCHAR* format, CLSID* pClsid);  // helper function

INT ConvertBmpToPng(char *bmpFilePath, char *pngFilePath)
{
   CLSID   encoderClsid;
   Status  stat;
   BSTR bstrBmpFilePath, bstrPngFilePath;



USES_CONVERSION;

	bstrBmpFilePath = A2WBSTR(bmpFilePath);
	bstrPngFilePath = A2WBSTR(pngFilePath);

   Image*   image = new Image(bstrBmpFilePath);

   //if (GuidStr)
   //{
		 // // Set the image title.
	  // PropertyItem* propItem = new PropertyItem;
	  // propItem->id = PropertyTagImageDescription;
	  // propItem->length = 18;  //  includes null terminator
	  // propItem->type = PropertyTagTypeASCII;
	  // propItem->value = GuidStr;
	  // image->SetPropertyItem(propItem);
   //}


   // Get the CLSID of the Png encoder.
   GetEncoderClsid(L"image/png", &encoderClsid);

   stat = image->Save(bstrPngFilePath, &encoderClsid, NULL);


   SysFreeString(bstrBmpFilePath);
   SysFreeString(bstrPngFilePath);

   delete image;

   return 0;
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)zMalloc(size);
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         zFree(pImageCodecInfo);
         return j;  // Success
      }    
   }

   zFree(pImageCodecInfo);
   return -1;  // Failure
}

PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp)
{ 
    BITMAP bmp; 
    PBITMAPINFO pbmi; 
    WORD    cClrBits; 

    // Retrieve the bitmap color format, width, and height. 
    if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) 
	{
		MessageBox(hwnd, "GetObject Failed", ":CreateBitmapInfoStruct", 1);
        return NULL;
	}

    // Convert the color format to a count of bits. 
    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
    if (cClrBits == 1) 
        cClrBits = 1; 
    else if (cClrBits <= 4) 
        cClrBits = 4; 
    else if (cClrBits <= 8) 
        cClrBits = 8; 
    else if (cClrBits <= 16) 
        cClrBits = 16; 
    else if (cClrBits <= 24) 
        cClrBits = 24; 
    else cClrBits = 32; 

    // Allocate memory for the BITMAPINFO structure. (This structure 
    // contains a BITMAPINFOHEADER structure and an array of RGBQUAD 
    // data structures.) 

     if (cClrBits != 24) 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER) + 
                    sizeof(RGBQUAD) * (1<< cClrBits)); 

     // There is no RGBQUAD array for the 24-bit-per-pixel format. 

     else 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER)); 

    // Initialize the fields in the BITMAPINFO structure. 

    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmi->bmiHeader.biWidth = bmp.bmWidth; 
    pbmi->bmiHeader.biHeight = bmp.bmHeight; 
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
    if (cClrBits < 24) 
        pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 

    // If the bitmap is not compressed, set the BI_RGB flag. 
    pbmi->bmiHeader.biCompression = BI_RGB; 

    // Compute the number of bytes in the array of color 
    // indices and store the result in biSizeImage. 
    // For Windows NT, the width must be DWORD aligned unless 
    // the bitmap is RLE compressed. This example shows this. 
    // For Windows 95/98/Me, the width must be WORD aligned unless the 
    // bitmap is RLE compressed.
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8
                                  * pbmi->bmiHeader.biHeight; 
    // Set biClrImportant to 0, indicating that all of the 
    // device colors are important. 
     pbmi->bmiHeader.biClrImportant = 0; 
     return pbmi; 
 } 


void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, 
                  HBITMAP hBMP, HDC hDC) 
 { 
     HANDLE hf;                 // file handle 
    BITMAPFILEHEADER hdr;       // bitmap file-header 
    PBITMAPINFOHEADER pbih;     // bitmap info-header 
    LPBYTE lpBits;              // memory pointer 
    DWORD dwTotal;              // total count of bytes 
    DWORD cb;                   // incremental count of bytes 
    BYTE *hp;                   // byte pointer 
    DWORD dwTmp; 

    pbih = (PBITMAPINFOHEADER) pbi; 
    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

    if (!lpBits)
	{
		MessageBox(hwnd, "GlobalAlloc Failed", ":CreateBMPFile", 1);
		return;
	}

    // Retrieve the color table (RGBQUAD array) and the bits 
    // (array of palette indices) from the DIB. 
    if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, 
        DIB_RGB_COLORS)) 
    {
		MessageBox(hwnd, "GetDIBits Failed", ":CreateBMPFile", 1);
		return;
    }

    // Create the .BMP file. 
    hf = CreateFile(pszFile, 
                   GENERIC_READ | GENERIC_WRITE, 
                   (DWORD) 0, 
                    NULL, 
                   CREATE_ALWAYS, 
                   FILE_ATTRIBUTE_NORMAL, 
                   (HANDLE) NULL); 
    if (hf == INVALID_HANDLE_VALUE)
	{		
		MessageBox(hwnd, "CreateFile Failed", ":CreateBMPFile", 1);
		return;
	}
    hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
    // Compute the size of the entire file. 
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
                 pbih->biSize + pbih->biClrUsed 
                 * sizeof(RGBQUAD) + pbih->biSizeImage); 
    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 

    // Compute the offset to the array of color indices. 
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
                    pbih->biSize + pbih->biClrUsed 
                    * sizeof (RGBQUAD); 

    // Copy the BITMAPFILEHEADER into the .BMP file. 
    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
        (LPDWORD) &dwTmp,  NULL)) 
    {
		MessageBox(hwnd, "WriteFile Failed", ":CreateBMPFile", 1);
		return;
    }

    // Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
                  + pbih->biClrUsed * sizeof (RGBQUAD), 
                  (LPDWORD) &dwTmp, ( NULL)))
	{
		MessageBox(hwnd, "WriteFile Failed", ":CreateBMPFile", 1);
		return;
	}

    // Copy the array of color indices into the .BMP file. 
    dwTotal = cb = pbih->biSizeImage; 
    hp = lpBits; 
    if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL))
	{
		MessageBox(hwnd, "WriteFile Failed", ":CreateBMPFile", 1);
		return;
	}
		

    // Close the .BMP file. 
     if (!CloseHandle(hf)) 
	{
		MessageBox(hwnd, "CloseHandle Failed", ":CreateBMPFile", 1);
		return;
	}

    // Free memory. 
    GlobalFree((HGLOBAL)lpBits);
}

// CreateAToolBar creates a toolbar and adds a set of buttons to it.
// The function returns the handle to the toolbar if successful, 
// or NULL otherwise. 
// hwndParent is the handle to the toolbar's parent window. 
HWND CreateAToolBar(HWND hwndParent) 
{ 
   TBBUTTON tbb[3]; 
   char szBuf[16]; 
   int iOK, iStartOver;
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

// Add the button strings to the toolbar's internal string list. 
   LoadString(hInst, IDS_SIGNEW, szBuf, 15); 
//Save room for second null terminator.
   iStartOver = strlen((const char *)szBuf);
   szBuf[iStartOver+2] = 0;
   iStartOver = SendMessage(hwndTB, TB_ADDSTRING, 0, (LPARAM) (LPSTR) szBuf); 

   // Fill the TBBUTTON array with button information, and add the 
// buttons to the toolbar. The buttons on this toolbar have text 
// but do not have bitmap images. 
   tbb[0].iBitmap = I_IMAGENONE; 
   tbb[0].idCommand = IDC_SIGOK; 
   tbb[0].fsState = TBSTATE_ENABLED; 
   tbb[0].fsStyle = BTNS_BUTTON; 
   tbb[0].dwData = 0; 
   tbb[0].iString = iOK; 
 
   tbb[1].iBitmap = I_IMAGENONE; 
   tbb[1].idCommand = IDS_SIGNEW; 
   tbb[1].fsState = TBSTATE_ENABLED; 
   tbb[1].fsStyle = BTNS_BUTTON; 
   tbb[1].dwData = 0; 
   tbb[1].iString = iStartOver; 

   SendMessage(hwndTB, TB_ADDBUTTONS, (WPARAM) 2, 
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


LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT psPaint;
	RECT window_rect;

	HDC hDC, hdc;

	PBITMAPINFO	pbmi;
	HBITMAP	bitmap;
	HDC		hdcCompatible;
	int Width, Height;

    RECT rcClient, tmpRect;                 // client area rectangle 
    POINT ptClientUL;              // client upper left corner 
    POINT ptClientLR;              // client lower right corner 
    static POINTS ptsBegin;        // beginning point 
    static POINTS ptsEnd;          // new endpoint 
    static POINTS ptsPrevEnd;      // previous endpoint 
    static BOOL fPrevLine = FALSE; // previous line flag 

	char TempPath[MAX_PATH+1];
	static HPEN hPen;
	HPEN hPenOld;
	LOGBRUSH lb;
	static int labelWidth;
//	static GdiplusStartupInput gdiplusStartupInput;
//	static ULONG_PTR gdiplusToken;



	
	switch (message) 
	{
       case WM_LBUTTONDOWN: 
 
            // Capture mouse input. 
 
            SetCapture(hWnd); 
 
            // Retrieve the screen coordinates of the client area, 
            // and convert them into client coordinates. 
 
            GetClientRect(hWnd, &rcClient);
			GetClientRect(hwndTB, &tmpRect);
            ptClientUL.x = rcClient.left; 
            ptClientUL.y = rcClient.top; 
 
            // Add one to the right and bottom sides, because the 
            // coordinates retrieved by GetClientRect do not 
            // include the far left and lowermost pixels. 
 
            ptClientLR.x = rcClient.right + 1; 
            ptClientLR.y = rcClient.bottom - labelWidth; 
            ClientToScreen(hWnd, &ptClientUL); 
            ClientToScreen(hWnd, &ptClientLR); 
 
            // Copy the client coordinates of the client area 
            // to the rcClient structure. Confine the mouse cursor 
            // to the client area by passing the rcClient structure 
            // to the ClipCursor function. 
 
            SetRect(&rcClient, ptClientUL.x, ptClientUL.y, 
                ptClientLR.x, ptClientLR.y); 
            ClipCursor(&rcClient); 
 
            // Convert the cursor coordinates into a POINTS 
            // structure, which defines the beginning point of the 
            // line drawn during a WM_MOUSEMOVE message. 
 
            ptsBegin = MAKEPOINTS(lParam); 
            break; 
 
        case WM_MOUSEMOVE: 
 
            // When moving the mouse, the user must hold down 
            // the left mouse button to draw lines. 
 
            if (wParam & MK_LBUTTON) 
            { 
 
                // Retrieve a device context (DC) for the client area. 
 
                hdc = GetDC(hWnd); 
 				hPenOld = (HPEN)SelectObject(hdc, hPen);

                // Convert the current cursor coordinates to a 
                // POINTS structure, and then draw a new line. 
 
                ptsEnd = MAKEPOINTS(lParam); 
                MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT) NULL); 
                LineTo(hdc, ptsEnd.x, ptsEnd.y); 
 
                // Set the previous line flag, save the ending 
                // point of the new line, and then release the DC. 
 
                ptsBegin = ptsEnd;
				SelectObject(hdc, hPenOld);
                ReleaseDC(hWnd, hdc); 
            } 
            break; 
 
        case WM_LBUTTONUP: 
 
            // The user has finished drawing the line. Reset the 
            // previous line flag, release the mouse cursor, and 
            // release the mouse capture. 
 
            ClipCursor(NULL); 
            ReleaseCapture(); 
            break;

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
									BmpFilePathBuffer);          // buffer for name 


					CreateBMPFile(hWnd, BmpFilePathBuffer, pbmi, bitmap, hdcCompatible);
					GetTempFileName(TempPath, // dir. for temp. files 
									"IMG",                // temp. file name prefix 
									0,                    // create unique name 
									FilePathBuffer);          // buffer for name 
					ConvertBmpToPng(BmpFilePathBuffer, FilePathBuffer);
					DeleteFile(BmpFilePathBuffer);

					ReleaseDC(hWnd, hDC);
					ReleaseDC(hWnd, hdcCompatible);
					DestroyWindow(hWnd);
					break;
				case IDS_SIGNEW:
					InvalidateRect(hWnd, NULL, TRUE);
					return DefWindowProc(hWnd, message, wParam, lParam);
					
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}


		case WM_DESTROY:
			DeleteObject(hPen);
//			GdiplusShutdown(gdiplusToken);
			PostQuitMessage(0);
			break;

		case WM_PAINT:
			if (hDC = BeginPaint(hWnd, &psPaint)) 
			{
				GetClientRect(hWnd, &tmpRect);
				GetClientRect(hwndTB, &rcClient);

				labelWidth = rcClient.bottom + 4;
				tmpRect.top = tmpRect.bottom - labelWidth - 16;
				tmpRect.left = 0;
				tmpRect.bottom = tmpRect.top + 16;

				labelWidth += 16;


				SetTextColor(hDC, RGB(0x00, 0x99, 0x99));

				DrawText(hDC, MouseLabel, strlen(MouseLabel), &tmpRect, DT_LEFT);
				
				tmpRect.top = tmpRect.top - 14;
				tmpRect.bottom = tmpRect.top + 14;
				labelWidth += 14;

				if (GuidStr)
					DrawText(hDC, GuidStr, strlen(GuidStr), &tmpRect, DT_LEFT);

				hPenOld = (HPEN)SelectObject(hDC, hPen);
				POINTLIST::iterator i = lst->begin();
				while( i != lst->end() ) 
				{
					if( i->x >= 0 )
						LineTo(hDC, i->x,i->y);
					else
						MoveToEx(hDC, abs(i->x),abs(i->y), NULL);
					i++;
				}

				SelectObject(hDC, hPenOld);
				EndPaint(hWnd, &psPaint);
			}
			break;

		case WM_CREATE:
			CreateAToolBar(hWnd);
            // Initialize the pen's brush.
            lb.lbStyle = BS_SOLID; 
            lb.lbColor = RGB(255,0,0); 
            lb.lbHatch = 0; 
 

			hPen =  ExtCreatePen(	PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_SQUARE | PS_JOIN_ROUND,// pen style
									(DWORD) 1,         // pen width
									&lb,  // brush attributes
									0,    // length of custom style array
									NULL   // custom style array
								);
			// Initialize GDI+.
//			GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}




BOOL InitApplication(HINSTANCE hinstance) 
{ 
    WNDCLASSEX wcx; 
 
    // Fill in the window class structure with parameters 
    // that describe the main window. 
 
    wcx.cbSize = sizeof(wcx);          // size of structure 
    wcx.style = CS_HREDRAW | 
        CS_VREDRAW;                    // redraw if size changes 
    wcx.lpfnWndProc = MainWndProc;     // points to window procedure 
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
    wcx.lpszClassName = "MainMouseClass";  // name of window class 
    wcx.hIconSm = (struct HICON__ *)LoadImage(hinstance, // small class icon 
        MAKEINTRESOURCE(5),
        IMAGE_ICON, 
        GetSystemMetrics(SM_CXSMICON), 
        GetSystemMetrics(SM_CYSMICON), 
        LR_DEFAULTCOLOR); 
 
    // Register the window class. 
 
    return RegisterClassEx(&wcx); 
} 

 
BOOL InitInstance(HINSTANCE hinstance, int nCmdShow, RECT *windowDim) 
{ 
	lst = new POINTLIST;
	char ErrorMsg[100];


    // Create the main window. 
 
    hwnd = CreateWindow( 
        "MainMouseClass",        // name of window class 
        "Create Mouse Signature", // title-bar string 
        WS_OVERLAPPEDWINDOW, // top-level window 
        windowDim->left,       // default horizontal position 
        windowDim->top,       // default vertical position 
        windowDim->right,       // default width 
        windowDim->bottom,       // default height 
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

HRESULT	CaptureMouseSignature(char *filePathBuf, BOOL sigCapturedOnce, RECT *windowDim, char *guidStr)
{
    MSG msg; 
//	HACCEL hAccelTable;

	FilePathBuffer = filePathBuf;
	GuidStr = guidStr;

//	if (!sigCapturedOnce)
 		if (!InitApplication(hInst)) 
	       return FALSE; 

    if (!InitInstance(hInst, SW_SHOWNORMAL, windowDim)) 
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
	UnregisterClass("MainMouseClass", hInst);

	if (strlen(FilePathBuffer) == 0)
		return FALSE;
	else
		return TRUE;
}