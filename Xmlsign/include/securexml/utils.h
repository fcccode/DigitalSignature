/*****************************************************************************************
 * Copyright: (c) 2001 Infomosaic Corporation.
 * All rights reserved.
 * It is violation of international law to use this code without proper written authorization
 * and license agreement from Infomosaic Corporation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL INFOMOSAIC CORPORATION  OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * Author:
 * Date:
 * Change history:
 *
 * Date		|	Modified By		|	Brief description of the modification
 *
 *
 *****************************************************************************************
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#if __cplusplus
extern "C" {
#endif

#include <time.h>

#include <securexml/coresig.h>

/***************** for internal use ********************/
// set last error
extern void setError(PGLOBAL_SIG pg_sig,int errnum);
extern void setErrorWithDescr(PGLOBAL_SIG pg_sig,int errnum, unsigned char *errDescr);

// trim white spaces (leading and trailing)
extern char *trim(char *src);
// free current signature data
extern void freeThisSignature(PGLOBAL_SIG pg_sig);
// debug
extern void printStatus(char *s);
// simple sort of strings, bubble algorithm
extern void simpleSort(char *x[], int n);
// decode BASE64 string to BYTE *
// with conversion little-endian -> big-endian
extern int decodeBigEndian(const BYTE *src, BYTE *dst, DWORD *retsize);
// trim white spaces through whole object
extern int zeroSpace(BYTE *pSrcObject, DWORD sizeSrcObject,BYTE *dstObject, DWORD *objSize);

extern void xsCheckError(PGLOBAL_SIG pg_sig,int err);

//#ifdef WIN32
extern LPSYSTEMTIME rfcTimeToSystem(BYTE *rfcTime);
extern LPSYSTEMTIME vbNowTimeToSystem(BYTE *vbNowTime);
extern LPSYSTEMTIME jsUtcTimeToSystem(BYTE *jsUtcTime);
extern LPSYSTEMTIME localTimeToUtcTime(LPSYSTEMTIME localTime);
extern char * systemTimeToJsUtcTime(SYSTEMTIME &systemTime);
extern char * systemTimeToVbNowTime(SYSTEMTIME &systemTime);
extern char * systemTimeToRfcTime(SYSTEMTIME &tsSysTime);
//#else
//extern struct tm *rfcTimeToSystem(BYTE *rfcTime);
//extern struct tm *vbNowTimeToSystem(BYTE *vbNowTime);
//extern struct tm *jsUtcTimeToSystem(BYTE *jsUtcTime);
//extern struct tm *localTimeToUtcTime(struct tm *localTime);
//#endif
extern unsigned char * getSystemTimeAsRfcTime();
extern char *stolower(char *src);
void s_log(const char* format, ...);
extern char * insertLineBreak(const char *inputString, int lineWrapLimit);
#if __cplusplus
}
#endif

#endif

