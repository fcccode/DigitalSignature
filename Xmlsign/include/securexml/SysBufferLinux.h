
#ifndef _SYSBUFFERLINUX_H
#define _SYSBUFFERLINUX_H

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <windef.h>
#include <winbase.h>
#include <winnls.h>
#include <winerror.h>
#include <oleauto.h>
#include <objbase.h>
#include <wtypes.h>

#include <securexml/DebugLog.h>
#include <securexml/unicodeLinux.h>
#include <time.h>

/******************************************************************************
 *             SysStringLen
 *
 * Get the allocated length of a BSTR in wide characters.
 *
 * PARAMS
 *  str [I] BSTR to find the length of
 *
 * RETURNS
 *  The allocated length of str, or 0 if str is NULL.
 *
 * NOTES
 *  See BSTR.
 *  The returned length may be different from the length of the string as
 *  calculated by lstrlenW(), since it returns the length that was used to
 *  allocate the string by SysAllocStringLen().
 */
inline int SysStringLen(BSTR str)
{
    DWORD* bufferPointer;

     if (!str) return 0;
    /*
     * The length of the string (in bytes) is contained in a DWORD placed
     * just before the BSTR pointer
     */
    bufferPointer = (DWORD*)str;

    bufferPointer--;

    return (int)(*bufferPointer/sizeof(WCHAR));
}

/******************************************************************************
 *             SysStringByteLen
 *
 * Get the allocated length of a BSTR in bytes.
 *
 * PARAMS
 *  str [I] BSTR to find the length of
 *
 * RETURNS
 *  The allocated length of str, or 0 if str is NULL.
 *
 * NOTES
 *  See SysStringLen(), BSTR().
 */
inline int SysStringByteLen(BSTR str)
{
    DWORD* bufferPointer;

     if (!str) return 0;
    /*
     * The length of the string (in bytes) is contained in a DWORD placed
     * just before the BSTR pointer
     */
    bufferPointer = (DWORD*)str;

    bufferPointer--;

    return (int)(*bufferPointer);
}

/******************************************************************************
 *		SysAllocString
 *
 * Create a BSTR from an OLESTR.
 *
 * PARAMS
 *  str [I] Source to create BSTR from
 *
 * RETURNS
 *  Success: A BSTR allocated with SysAllocStringLen().
 *  Failure: NULL, if oleStr is NULL.
 *
 * NOTES
 *  See BSTR.
 *  MSDN (October 2001) incorrectly states that NULL is returned if oleStr has
 *  a length of 0. Native Win32 and this implementation both return a valid
 *  empty BSTR in this case.
 */
inline BSTR SysAllocString(LPCOLESTR str)
{
    if (!str) return 0;

    /* Delegate this to the SysAllocStringLen32 method. */
    return SysAllocStringLen(str, strlenW(str));
}

/******************************************************************************
 *		SysFreeString
 *
 * Free a BSTR.
 *
 * PARAMS
 *  str [I] BSTR to free.
 *
 * RETURNS
 *  Nothing.
 *
 * NOTES
 *  See BSTR.
 *  str may be NULL, in which case this function does nothing.
 */
inline void SysFreeString(BSTR str)
{
    DWORD* bufferPointer;

    /* NULL is a valid parameter */
    if(!str) return;

    /*
     * We have to be careful when we free a BSTR pointer, it points to
     * the beginning of the string but it skips the byte count contained
     * before the string.
     */
    bufferPointer = (DWORD*)str;

    bufferPointer--;

    /*
     * Free the memory from its "real" origin.
     */
    zFree(bufferPointer);
}

/******************************************************************************
 *             SysAllocStringLen
 *
 * Create a BSTR from an OLESTR of a given wide character length.
 *
 * PARAMS
 *  str [I] Source to create BSTR from
 *  len [I] Length of oleStr in wide characters
 *
 * RETURNS
 *  Success: A newly allocated BSTR from SysAllocStringByteLen()
 *  Failure: NULL, if len is >= 0x80000000, or memory allocation fails.
 *
 * NOTES
 *  See BSTR(), SysAllocStringByteLen().
 */
inline BSTR SysAllocStringLen(const OLECHAR *str, unsigned int len)
{
    DWORD  bufferSize;
    DWORD* newBuffer;
    WCHAR* stringBuffer;

    /*
     * Find the length of the buffer passed-in in bytes.
     */
    bufferSize = len * sizeof (WCHAR);

    /*
     * Allocate a new buffer to hold the string.
     * dont't forget to keep an empty spot at the beginning of the
     * buffer for the character count and an extra character at the
     * end for the NULL.
     */
    newBuffer = (DWORD*)zMalloc(bufferSize + sizeof(WCHAR) + sizeof(DWORD));

    /*
     * If the memory allocation failed, return a null pointer.
     */
    if (newBuffer==0)
      return 0;

    /*
     * Copy the length of the string in the placeholder.
     */
    *newBuffer = bufferSize;

    /*
     * Skip the byte count.
     */
    newBuffer++;

    /*
     * Copy the information in the buffer.
     * Since it is valid to pass a NULL pointer here, we'll initialize the
     * buffer to nul if it is the case.
     */
    if (str != 0)
      memcpy(newBuffer, str, bufferSize);
    else
      memset(newBuffer, 0, bufferSize);

    /*
     * Make sure that there is a nul character at the end of the
     * string.
     */
    stringBuffer = (WCHAR*)newBuffer;
    stringBuffer[len] = L'\0';

    return (LPWSTR)stringBuffer;
}

/******************************************************************************
 *             SysAllocStringByteLen
 *
 * Create a BSTR from an OLESTR of a given byte length.
 *
 * PARAMS
 *  str [I] Source to create BSTR from
 *  len [I] Length of oleStr in bytes
 *
 * RETURNS
 *  Success: A newly allocated BSTR
 *  Failure: NULL, if len is >= 0x80000000, or memory allocation fails.
 *
 * NOTES
 *  -If len is 0 or oleStr is NULL the resulting string is empty ("").
 *  -This function always NUL terminates the resulting BSTR.
 *  -oleStr may be either an LPCSTR or LPCOLESTR, since it is copied
 *  without checking for a terminating NUL.
 *  See BSTR.
 */
inline BSTR SysAllocStringByteLen(LPCSTR str, UINT len)
{
    DWORD* newBuffer;
    char* stringBuffer;

    /*
     * Allocate a new buffer to hold the string.
     * dont't forget to keep an empty spot at the beginning of the
     * buffer for the character count and an extra character at the
     * end for the NULL.
     */
    newBuffer = (DWORD*)zMalloc(len + sizeof(WCHAR) + sizeof(DWORD));

    /*
     * If the memory allocation failed, return a null pointer.
     */
    if (newBuffer==0)
      return 0;

    /*
     * Copy the length of the string in the placeholder.
     */
    *newBuffer = len;

    /*
     * Skip the byte count.
     */
    newBuffer++;

    /*
     * Copy the information in the buffer.
     * Since it is valid to pass a NULL pointer here, we'll initialize the
     * buffer to nul if it is the case.
     */
    if (str != 0)
      memcpy(newBuffer, str, len);

    /*
     * Make sure that there is a nul character at the end of the
     * string.
     */
    stringBuffer = (char *)newBuffer;
    stringBuffer[len] = 0;
    stringBuffer[len+1] = 0;

    return (LPWSTR)stringBuffer;
}

/**********************************************************************
 * VarBstrCat
 *
 * Concatenate two BSTR values.
 *
 * PARAMS
 *  pbstrLeft  [I] Source
 *  pbstrRight [I] Value to concatenate
 *  pbstrOut   [O] Destination
 *
 * RETURNS
 *  Success: S_OK.
 *  Failure: E_INVALIDARG, if pbstrOut is invalid.
 *           E_OUTOFMEMORY, if memory allocation fails.
 */
inline HRESULT VarBstrCat(BSTR pbstrLeft, BSTR pbstrRight, BSTR *pbstrOut)
{
  unsigned int len;

  if (!pbstrOut)
    return E_INVALIDARG;

  len = pbstrLeft ? strlenW(pbstrLeft) : 0;
  if (pbstrRight)
    len += strlenW(pbstrRight);

  *pbstrOut = SysAllocStringLen(NULL, len);
  if (!*pbstrOut)
    return E_OUTOFMEMORY;

  **pbstrOut = L'\0';

  if (pbstrLeft)
    strcpyW(*pbstrOut, pbstrLeft);

  if (pbstrRight)
    strcatW(*pbstrOut, pbstrRight);

  return S_OK;
}


/**********************************************************************
 * VarBstrCmp
 *
 * Compare two BSTR values.
 *
 * PARAMS
 *  pbstrLeft  [I] Source
 *  pbstrRight [I] Value to compare
 *  lcid       [I] LCID for the comparason
 *  dwFlags    [I] Flags to pass directly to CompareStringW().
 *
 * RETURNS
 *  VARCMP_LT, VARCMP_EQ or VARCMP_GT indicating that pbstrLeft is less
 *  than, equal to or greater than pbstrRight respectively.
 *  VARCMP_NULL is returned if either string is NULL, unless both are NULL
 *  in which case VARCMP_EQ is returned.
 */
inline HRESULT VarBstrCmp(BSTR pbstrLeft, BSTR pbstrRight, LCID lcid, DWORD dwFlags)
{
	if (!pbstrLeft)
	{
		if (!pbstrRight || !*pbstrRight)
			return VARCMP_EQ;
		return VARCMP_NULL;
	}
	else if (!pbstrRight)
	{
		if (!*pbstrLeft)
			return VARCMP_EQ;
		return VARCMP_NULL;
	}

	return CompareStringW(lcid, dwFlags, pbstrLeft, -1, pbstrRight, -1) - 1;
}

#endif		// _SYSBUFFERLINUX_H
