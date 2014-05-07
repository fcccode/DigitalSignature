
#include <cstdlib>
#include <stdarg.h>
#include <string>

#include <securexml/DebugLog.h>

//#ifdef LINUX
//#include <securexml/unicodeLinux.h>
//#endif

#include <time.h>
#include <sys/timeb.h>
#include <list>

using namespace std;

struct AllocInfo {
	      DWORD	address;
	      DWORD	size;
	      char	file[64];
		  char  func[64];
	      DWORD	line;
      };
typedef AllocInfo ALLOC_INFO;

typedef list <ALLOC_INFO*> AllocList;

AllocList *allocList=NULL;
#ifdef WIN32
char *LogFilePath= "C:\\temp\\SecureXML.log";
#elif LINUX
char *LogFilePath = "/tmp/SecureXML.log";
#endif
char *debugMutexName = "SecureXML-Debug";

const char *EnteringFunction = "Entering function";
const char *ExitingFunction = "Exiting function";

void * __cdecl myMalloc(unsigned int size,
                                    const char *file, int line, const char *func)
{
	void *ptr = (void *)malloc(size);
	AddTrack((DWORD)ptr, size, file, line, func);
	return(ptr);
}

void __cdecl myFree(void *p, const char *file, int line, const char *func)
{
	RemoveTrack((DWORD)p, file, line, func);
	free(p);
}

void __cdecl rFree(void *p)
{
	if (p) {
		free(p);
	}
};

void * __cdecl myRealloc(void *p, unsigned int size,
                                    const char *file, int line, const char *func)
{
	void *ptr = (void *)realloc(p, size);
	RemoveTrack((DWORD)p, file, line, func);
	AddTrack((DWORD)ptr, size, file, line, func);
	return(ptr);
}

void __cdecl AddTrack(DWORD addr,  DWORD asize,  const char *fname, DWORD lnum, const char *func)
{
	ALLOC_INFO *info;
	char buf[1024];

#ifdef LOGGING
	if (MemoryLogEnabled)
	{
#endif
		if(!allocList) {
			allocList = new(AllocList);
		}

		info = new(ALLOC_INFO);
		info->address = addr;
		strncpy(info->file, fname, 63);
		info->line = lnum;
		info->size = asize;
		strncpy(info->func, func, 63);
		allocList->insert(allocList->begin(), info);
		sprintf(buf, "%-20s:\tLINE %d,\tADDRESS %d\tFUNCTION %s\t%d Bytes Allocated",
			info->file, info->line, info->address, info->func, info->size);
		AddLog(buf);
#ifdef LOGGING
	}
#endif
};

void __cdecl RemoveTrack(DWORD addr, const char *fname, DWORD lnum, const char *func)
{
	char buf[1024];
	BOOL memoryFound=FALSE;

#ifdef LOGGING
	if (MemoryLogEnabled)
	{
#endif
		AllocList::iterator i;

		if(!allocList)
			return;
		for(i = allocList->begin(); i != allocList->end(); i++)
		{
			if((*i)->address == addr)
			{
				sprintf(buf, "%-20s:\tLINE %d,\tADDRESS %d\tFUNCTION %s\t%d Bytes Freed",
					(*i)->file, (*i)->line, (*i)->address, (*i)->func, (*i)->size);
				AddLog(buf);
				sprintf(buf, "%-20s:\tLINE %d,\tADDRESS %d\tFUNCTION %s\t%d Freed allocated memory.", 
					fname, lnum, addr, func, (*i)->size);
				AddLog(buf);
				allocList->remove((*i));
				memoryFound = TRUE;
				break;
			}
		}
		if (memoryFound == FALSE)
		{
			sprintf(buf, "%-20s:\tLINE %d,\tADDRESS %d\tFUNCTION %s\tTrying to free unallocated memory.", 
				fname, lnum, addr, func);
			AddLog(buf);
		}
#ifdef LOGGING
	}
#endif
};

void __cdecl DumpUnfreed()
{
	AllocList::iterator i;
	DWORD totalSize = 0;
	char buf[1024];

#ifdef LOGGING
	if (MemoryLogEnabled)
	{
#endif
		if(!allocList)
			return;

		for(i = allocList->begin(); i != allocList->end(); i++) {
			sprintf(buf, "%-20s:\tLINE %d,\tADDRESS %d\tFUNCTION %s\t%d Bytes Unfreed",
				(*i)->file, (*i)->line, (*i)->address, (*i)->func, (*i)->size);
			AddLog(buf);
			totalSize += (*i)->size;
		}
		sprintf(buf, "-----------------------------------------------------------");
		AddLog(buf);
		sprintf(buf, "Total Unfreed: %d bytes", totalSize);
		AddLog(buf);
#ifdef LOGGING
	}
#endif
};

#ifdef LINUX

void __cdecl AddLog(char *logStr)
{
	// TODO: Finish this function using pthread for Linux
}

void __cdecl AddLogDetail(const char *logStr, const char *func, char *module, DWORD line)
{
	// TODO: Finish this function using pthread for Linux
}

#elif WIN32

void __cdecl AddLog(char *logStr)
{
	FILE *fh;
#ifdef WIN32
	__time64_t ltime;
#elif LINUX
	time_t ltime;
#endif
	HANDLE hMutex=NULL;
	DWORD dwWaitResult; 

#ifdef WIN32
	_time64( &ltime );
#elif LINUX
	time(&ltime);
#endif
	hMutex = CreateMutex(NULL, FALSE, debugMutexName);

	while (1)
	{
		// Request ownership of mutex.
		dwWaitResult = WaitForSingleObject( 
			hMutex,   // handle to mutex
			5000L);   // five-second time-out interval

		if ((dwWaitResult == WAIT_OBJECT_0) || (dwWaitResult == WAIT_ABANDONED))
		{
							try
							{
								fh = fopen((const char *)LogFilePath, "a");
								if (fh != NULL)
								{
#ifdef WIN32
									fprintf(fh, "%s: %s", logStr, _ctime64( &ltime ));
#elif LINUX
									fprintf(fh, "%s: %s", logStr, ctime( &ltime ));
#endif
									fclose(fh);
								}
							}
							catch(char *)
							{}
							catch (int)
							{}
							ReleaseMutex(hMutex);
							break;
		}
	}
	CloseHandle(hMutex);
}

void __cdecl AddLogDetail(const char *logStr, const char *func, char *module, DWORD line)
{
	FILE *fh;
#ifdef WIN32
	__time64_t ltime;
#elif LINUX
	time_t ltime;
#endif
	HANDLE hMutex=NULL;
	DWORD dwWaitResult; 

	if (DebugLogEnabled)
	{
		hMutex = CreateMutex(NULL, FALSE, debugMutexName);
		while (1)
		{
			// Request ownership of mutex.
			dwWaitResult = WaitForSingleObject( 
				hMutex,   // handle to mutex
				5000L);   // five-second time-out interval

			if ((dwWaitResult == WAIT_OBJECT_0) || (dwWaitResult == WAIT_ABANDONED))
			{
#ifdef WIN32
				_time64( &ltime );
#elif LINUX
				time(&ltime);
#endif
				try
				{
					fh = fopen((const char *)LogFilePath, "a");
					if (fh != NULL)
					{
#ifdef WIN32
						fprintf(fh, "%-20s:\tLINE %d,\tFUNCTION %s\t\t %s\t\t%s", module, line, func, logStr, _ctime64( &ltime ));
#elif LINUX
						fprintf(fh, "%-20s:\tLINE %d,\tFUNCTION %s\t\t %s\t\t%s", module, line, func, logStr, ctime( &ltime ));
#endif
						fclose(fh);
					}
				}
				catch (char *)
				{}
				catch (int)
				{}
				ReleaseMutex(hMutex);
				break;
			}
		}
		CloseHandle(hMutex);
	}
}

#endif

#define DIV 1024
// #define DIV 1

char *divisor = "K";
// char *divisor = "";

// Handle the width of the field in which to print numbers this way to
// make changes easier. The asterisk in the print format specifier
// "%*I64d" takes an int from the argument list, and uses it to pad 
// and right-justify the number being formatted.
#define WIDTH 7


#ifdef WIN32

void __cdecl LogMemoryStatus(const char *fileName, const char *funcName, int lineNumber)
{
  MEMORYSTATUSEX statex;
  char buffer[200];

  statex.dwLength = sizeof (statex);

  GlobalMemoryStatusEx (&statex);

  sprintf((char *)buffer, "File: %s, Function: %s, Line: %d", fileName, funcName, lineNumber);
  AddLog(buffer);

  //sprintf((char *)buffer, "%ld percent of memory is in use.",
  //        statex.dwMemoryLoad);
  //AddLog(buffer);

  //sprintf ((char *)buffer, "There are %*I64d total %sbytes of physical memory.",
  //        WIDTH, statex.ullTotalPhys/DIV, divisor);
  //AddLog(buffer);

  //sprintf ((char *)buffer, "There are %*I64d free %sbytes of physical memory.",
  //        WIDTH, statex.ullAvailPhys/DIV, divisor);
  //AddLog(buffer);

  sprintf ((char *)buffer, "There are %*I64d total %sbytes of paging file used.",
          WIDTH, (statex.ullTotalPageFile/DIV) - (statex.ullAvailPageFile/DIV), divisor);
  AddLog(buffer);

  //sprintf ((char *)buffer, "There are %*I64d free %sbytes of paging file.",
  //        WIDTH, statex.ullAvailPageFile/DIV, divisor);
  //AddLog(buffer);

  //sprintf ((char *)buffer, "There are %*I64x total %sbytes of virtual memory.",
  //        WIDTH, statex.ullTotalVirtual/DIV, divisor);
  //AddLog(buffer);

  //sprintf ((char *)buffer, "There are %*I64x free %sbytes of virtual memory.",
  //        WIDTH, statex.ullAvailVirtual/DIV, divisor);
  //AddLog(buffer);

  //// Show the amount of extended memory available.

  //sprintf ((char *)buffer, "There are %*I64x free %sbytes of extended memory.",
  //        WIDTH, statex.ullAvailExtendedVirtual/DIV, divisor);
  //AddLog(buffer);
}

#endif


