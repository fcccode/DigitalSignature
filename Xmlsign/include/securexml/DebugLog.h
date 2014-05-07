
#ifndef __DEBUGLOG_H__
#define __DEBUGLOG_H__

#ifdef WIN32
#pragma once
#include <windows.h>
#endif

#ifndef WIN32
#include <wtypes.h>
#include <windef.h>
#include <winerror.h>
#endif

//#include <securexml/coresig.h>

#if __cplusplus
extern "C" {
#endif

void __cdecl AddTrack(DWORD addr,  DWORD asize,  const char *fname, DWORD lnum, const char *func);
void __cdecl RemoveTrack(DWORD addr, const char *fname, DWORD lnum, const char *func);
void __cdecl DumpUnfreed();
void __cdecl AddLog(char *logStr);
//void __cdecl AddLogDetail(const char *logStr, const char *fname, DWORD lnum, const char *func);
void __cdecl AddLogDetailWithMutex(const char *module, DWORD lnum, const char *func, unsigned int objectAddress,
						  unsigned int memoryAddress, const char *operation, const char *logStr);
void __cdecl AddLogDetail(const char *module, DWORD lnum, const char *func, unsigned int objectAddress,
						  unsigned int memoryAddress, const char *operation, const char *logStr);
//void __cdecl AddLogDetailWithInstance(const void *objectPtr, const char *logStr, const char *fname, DWORD lnum, const char *func);
void __cdecl LogMemoryStatus(const char *fname, DWORD lnum, const char *func);

extern const char *EnteringFunction;
extern const char *ExitingFunction;

extern BOOL DebugLogEnabled;

extern BOOL MemoryLogEnabled;

#define zMalloc(x)	myMalloc(x, __FILE__, __LINE__, __FUNCTION__)

#ifdef LOGGING
#define zFree(x)	myFree(x, __FILE__, __LINE__, __FUNCTION__)
#define zFree(x)	myFree(x, __FILE__, __LINE__, __FUNCTION__)
#define zRealloc(x,y)	myRealloc(x, y, __FILE__, __LINE__, __FUNCTION__)

//#define xmlMalloc(x)	myMalloc(x, __FILE__, __LINE__, __FUNCTION__)
//#define xmlFree(x)	myFree(x, __FILE__, __LINE__, __FUNCTION__)
//#define xmlRealloc(x,y)	myRealloc(x, y, __FILE__, __LINE__, __FUNCTION__)


#define DebugLog(x)				AddLogDetailWithMutex(__FILE__, __LINE__, __FUNCTION__, 0, 0, "Debug Log", x)
#define DebugLogInstance(x)		AddLogDetailWithMutex(__FILE__, __LINE__, __FUNCTION__, (unsigned int)SigHandle, 0, "Debug Log", x)
#define DebugLogPgSig(x)		AddLogDetailWithMutex(__FILE__, __LINE__, __FUNCTION__, (unsigned int)pg_sig, 0, "Debug Log", x)
#define EnterLog				DebugLog(EnteringFunction)
#define ExitLog					DebugLog(ExitingFunction)
#define EnterObjectLog			DebugLogInstance(EnteringFunction)
#define ExitObjectLog			DebugLogInstance(ExitingFunction)
#define EnterPgSigLog			DebugLogPgSig(EnteringFunction)
#define ExitPgSigLog			DebugLogPgSig(ExitingFunction)
#define LogMemory		LogMemoryStatus(__FILE__, __LINE__, __FUNCTION__)
#else
//#define zMalloc(x)		malloc(x)
#define zFree(x)		rFree(x)
#define zRealloc(x,y)	realloc(x, y)
#define DebugLog(x)		
#define EnterLog		
#define ExitLog
#define LogMemory
#define EnterObjectLog
#define ExitObjectLog
#define EnterPgSigLog
#define ExitPgSigLog
#define DebugLogInstance(x)
#define DebugLogPgSig(x)
#endif

void * __cdecl myMalloc(unsigned int size,
                                    const char *file, int line, const char *func);
void __cdecl myFree(void *p, const char *file, int line, const char *func);
void __cdecl rFree(void *p);
void * __cdecl myRealloc(void *p, unsigned int size,
                                    const char *file, int line, const char *func);

#if __cplusplus
}
#endif

#endif		// __DEBUGLOG_H__

