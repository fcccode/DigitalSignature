#include "StdAfx.h"
#include <mshtml.h>


using namespace Gdiplus;

// Global Variables:
extern "C" {
extern HINSTANCE hInst;
}

extern INT GetEncoderClsid(const WCHAR* format, CLSID* pClsid);  // helper function
extern INT ConvertBmpToPng(char *bmpFilePath, char *pngFilePath);

extern PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
extern void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);


HWND	ieWindowHandle=NULL;

BOOL CALLBACK EnumChildProc(HWND hwnd,    LPARAM lParam)
{
	char buffer[MAX_PATH];

	unsigned int result = GetClassName(hwnd,(LPTSTR) buffer, MAX_PATH);
	
	if (!strcmp((const char *)"Internet Explorer_Server", (const char *)buffer))
	{
		ieWindowHandle = hwnd;
		return false;
	}


	return true;

}

BOOL CaptureCurrentWindowImage (char *imageFilePath, char *guidStr)
{
	HWND hWnd;
	RECT window_rect;
	HDC hDC, hdcCompatible;
	HRESULT hr=S_OK;
	int Width, Height;
	PBITMAPINFO	pbmi;
	HBITMAP	bitmap;
	static char TempPath[MAX_PATH+1];
	static char BmpFilePathBuffer[MAX_PATH+1];
	int result;


	
	hWnd = GetForegroundWindow();

	result =  EnumChildWindows(hWnd,  EnumChildProc,  0);
	
	if (ieWindowHandle != NULL)
		hWnd = ieWindowHandle;

	hDC = GetDC(hWnd);
	hdcCompatible = CreateCompatibleDC(hDC);
	GetClientRect(hWnd, &window_rect);

	Width = window_rect.right;
	Height = window_rect.bottom;

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
					imageFilePath);          // buffer for name 
	ConvertBmpToPng(BmpFilePathBuffer, imageFilePath);
	DeleteFile(BmpFilePathBuffer);

	ReleaseDC(hWnd, hDC);
	ReleaseDC(hWnd, hdcCompatible);

	ieWindowHandle = NULL;

	return TRUE;

}
