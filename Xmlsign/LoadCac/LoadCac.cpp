// LoadCac.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <string>
using namespace std;

char szModulePath[MAX_PATH];	// module path without terminating \ character
char szActivCardDll[MAX_PATH];
char szLitronicDll[MAX_PATH];

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  dwReason, 
                       LPVOID lpReserved
					 )
{
	HINSTANCE m_hInstCacDll;

    if (dwReason == DLL_PROCESS_ATTACH)
    {
		TCHAR ModulePath[MAX_PATH];

		// Find and store this DLL module path as OLECHAR array

		::GetModuleFileName((HMODULE)hModule, ModulePath, MAX_PATH);
		MessageBox(NULL, (LPCTSTR)ModulePath, "GetModulePath", MB_OK);
		int len = strlen((const char *)ModulePath);

		for ( int i = len; i > 0; i--)
			if ( ModulePath[i] == '\\')
			{
				ModulePath[i] = '\0';
				strcpy( szModulePath, (const char *)ModulePath);
				break;
			}
        DisableThreadLibraryCalls((HMODULE)hModule);

		MessageBox(NULL, (LPCTSTR)szModulePath, "szModulePath", MB_OK);

		strcpy(szActivCardDll, (const char *)szModulePath);
		strcpy(szLitronicDll, (const char *)szModulePath);
		strcat(szActivCardDll, (const char *)"\\SecureXMLCac.dll");
		strcat(szLitronicDll, (const char *)"\\SecureXMLCacL.dll");
		MessageBox(NULL, (LPCTSTR) szActivCardDll, "Loading ActiveCard Dll", MB_OK);
		m_hInstCacDll = LoadLibrary((LPCTSTR)szActivCardDll);
		if (m_hInstCacDll == NULL)
		{
			MessageBox(NULL, "Could not load SecureXMLCac.dll", "Failure", MB_OK);
			MessageBox(NULL, (LPCTSTR) szLitronicDll, "Loading Litronic Dll", MB_OK);
			m_hInstCacDll = LoadLibrary((LPCTSTR)szLitronicDll);
			if (m_hInstCacDll == NULL)
			{
				MessageBox(NULL, "Could not load SecureXMLCac.dll", "Failure", MB_OK);
			}
			else
			{
				MessageBox(NULL, "SecureXMLCacL.dll loaded successfully", "Success", MB_OK);
			}

		}
		else
		{
			MessageBox(NULL, "SecureXMLCac.dll loaded successfully", "Success", MB_OK);
		}
    }

    return TRUE;
}

