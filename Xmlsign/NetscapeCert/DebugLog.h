
#ifndef __DEBUGLOG_H__
#define __DEBUGLOG_H__

#ifdef WIN32
#pragma once
#include <windows.h>
#endif

#include <securexml/coresig.h>

#if __cplusplus
extern "C" {
#endif

void __cdecl AddTrack(DWORD addr,  DWORD asize,  const char *fname, DWORD lnum, const char *func);
void __cdecl RemoveTrack(DWORD addr, const char *fname, DWORD lnum, const char *func);
void __cdecl DumpUnfreed();
void __cdecl AddLog(char *logStr);
void __cdecl AddLogDetail(const char *logStr, const char *func, char *module, DWORD line);
void __cdecl LogMemoryStatus(const char *fileName, const char *funcName, int lineNumber);

extern const char *EnteringFunction;
extern const char *ExitingFunction;

extern BOOL DebugLogEnabled;
extern BOOL MemoryLogEnabled;

#ifdef LOGGING
#define zMalloc(x)	myMalloc(x, __FILE__, __LINE__, __FUNCTION__)
#define zFree(x)	myFree(x, __FILE__, __LINE__, __FUNCTION__)
#define zFree(x)	myFree(x, __FILE__, __LINE__, __FUNCTION__)
#define zRealloc(x,y)	myRealloc(x, y, __FILE__, __LINE__, __FUNCTION__)

//#define xmlMalloc(x)	myMalloc(x, __FILE__, __LINE__, __FUNCTION__)
//#define xmlFree(x)	myFree(x, __FILE__, __LINE__, __FUNCTION__)
//#define xmlRealloc(x,y)	myRealloc(x, y, __FILE__, __LINE__, __FUNCTION__)


#define DebugLog(x)		AddLogDetail(x, __FUNCTION__, __FILE__, __LINE__)
#define EnterLog		DebugLog(EnteringFunction)
#define ExitLog			DebugLog(ExitingFunction)
#define LogMemory		LogMemoryStatus(__FILE__, __FUNCTION__, __LINE__)
#else
#define zMalloc(x)		malloc(x)
#define zFree(x)		rFree(x)
#define zRealloc(x,y)	realloc(x, y)
#define DebugLog(x)		
#define EnterLog		
#define ExitLog
#define LogMemory
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

