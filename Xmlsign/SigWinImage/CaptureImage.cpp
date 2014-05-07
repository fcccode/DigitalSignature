// CaptureImage.cpp : Implementation of CCaptureImage

#include "stdafx.h"
#include "CaptureImage.h"
#include ".\captureimage.h"
#include <securexml/DebugLog.h>

using namespace Gdiplus;
using namespace ATL;
extern CComModule _Module;

// Global Variables:
extern "C" {
extern HINSTANCE hInst;
}

extern INT GetEncoderClsid(const WCHAR* format, CLSID* pClsid);  // helper function
extern INT ConvertBmpToPng(char *bmpFilePath, char *pngFilePath);

extern PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
extern void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
extern HRESULT	ShowFileSignature(char *filePathBuf, char *outFilePathBuf, BOOL sigCapturedOnce, RECT *windowDim, char *guidStr);
extern HRESULT	CaptureMouseSignature(char *filePathBuf, BOOL sigCapturedOnce, RECT *windowDim, char *guidStr);


HWND	ieWindowHandle=NULL;

unsigned char * HeapW2A(BSTR bstrStr)
{
	unsigned char *ptr, *newPtr=NULL, *curPtr=NULL; 
	unsigned int *szPtr;
	unsigned int sizeM;
	
	EnterLog;
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
	ExitLog;
	return(newPtr);
}

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

BOOL CaptureCurrentWindowImage (char *imageFilePath)
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

// CCaptureImage

CCaptureImage::CCaptureImage()
{
	HWND desktopHwnd;

	EnterLog;
	hInst  = ::_Module.m_hInst;
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	desktopHwnd = GetDesktopWindow();	
	GetClientRect(desktopHwnd, &SignatureCaptureWindowDim);		
	SignatureCaptureWindowDim.left = (SignatureCaptureWindowDim.right / 2) - 135; // UpperX		
	SignatureCaptureWindowDim.top = (SignatureCaptureWindowDim.bottom / 2) - 100; // UpperY		
	SignatureCaptureWindowDim.bottom = 200; // Height
	SignatureCaptureWindowDim.right = 270;  // Width
	ExitLog;
}

CCaptureImage::~CCaptureImage()
{
	EnterLog;
	GdiplusShutdown(gdiplusToken);
	ExitLog;
}


STDMETHODIMP CCaptureImage::CaptureCurrentWindowImage(BSTR* WindowImageFileName)
{
	char imageFilePath[MAX_PATH+1];
	BOOL imageCaptureResult = FALSE;

	imageCaptureResult = ::CaptureCurrentWindowImage((char *)imageFilePath);
	if (imageCaptureResult == TRUE)
	{
		*WindowImageFileName = A2WBSTR((LPCSTR)imageFilePath);
		return S_OK;
	}
	else
		return S_FALSE;
}

STDMETHODIMP CCaptureImage::put_PhysicalSignatureFile(BSTR newVal)
{
	HRESULT hResult=S_OK;
	EnterLog;

	USES_CONVERSION;

	PhysicalSignatureFileName = newVal;

	if (PhysicalSignatureFileName.Length() == 0)
	{
		return S_FALSE;
	}
	Image image(newVal);
	SignatureCaptureWindowDim.bottom = image.GetHeight(); // Height
	SignatureCaptureWindowDim.right = image.GetWidth();  // Width
	
	ExitLog;
	return hResult;
}

STDMETHODIMP CCaptureImage::put_UpperX(LONG newVal)
{
	SignatureCaptureWindowDim.left = newVal;
	return S_OK;
}

STDMETHODIMP CCaptureImage::put_UpperY(LONG newVal)
{
	SignatureCaptureWindowDim.top = newVal;
	return S_OK;
}

STDMETHODIMP CCaptureImage::put_Width(LONG newVal)
{
	SignatureCaptureWindowDim.right = newVal;
	return S_OK;
}

STDMETHODIMP CCaptureImage::put_Height(LONG newVal)
{
	SignatureCaptureWindowDim.bottom = newVal;
	return S_OK;
}

STDMETHODIMP CCaptureImage::ShowFileSignature(BSTR guidStr, BSTR* outPngFilePath)
{
	char outFilePath[MAX_PATH+1];

	if (PhysicalSignatureFileName.Length() == 0)
		return S_FALSE;

	char *charPhysicalSigFileName = (char *)HeapW2A(PhysicalSignatureFileName.m_str);
	char *charGuidStr = (char *)HeapW2A(guidStr);

	HRESULT hr = ::ShowFileSignature(charPhysicalSigFileName, (char *)outFilePath, FALSE, &SignatureCaptureWindowDim, charGuidStr);

	*outPngFilePath = A2WBSTR((LPCSTR)outFilePath);
	
	zFree(charPhysicalSigFileName);
	zFree(charGuidStr);
	return S_OK;
}

STDMETHODIMP CCaptureImage::CaptureMouseSignature(BSTR guidStr, BSTR* outPngFilePath)
{
	char outFilePath[MAX_PATH+1];

	char *charGuidStr = (char *)HeapW2A(guidStr);

	HRESULT hr = ::CaptureMouseSignature((char *)outFilePath, FALSE, &SignatureCaptureWindowDim, charGuidStr);

	*outPngFilePath = A2WBSTR((LPCSTR)outFilePath);
	
	zFree(charGuidStr);
	return S_OK;
}
