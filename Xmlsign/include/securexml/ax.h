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

#ifndef __AX_H__
#define __AX_H__
#if __cplusplus
extern "C" {
#endif

#define MAX_PROP 100
#define MAX_REF 1000
#define MAX_SIG 1000
#define MAX_OBJ 40
#define NO_SIGNED_OBJ_ACCESS 2

#include <securexml/coresig.h>

/****************************************************************/
/* "ax" section: ActiveX interface                              */
/****************************************************************/


// returns String <SignedInfo>
extern unsigned char *axSign(
	const char *URIname,
	const char **proparray,
	const int numprop,
	const int sigModelFlag,
	const int Transform,
	const int digestMethod,
	const char *rawCertData,
	const char *sigId,
	PDS_DATA_BLOB hKey,
	PGLOBAL_SIG pg_sig);	

// init library context
#ifdef NSS
extern PGLOBAL_SIG axInit(const unsigned char *certStorePassword, const unsigned char *certStoreName);
#else
extern PGLOBAL_SIG axInit();
#endif
// verify all XML Signatures in the document: data
extern int axVerify(const unsigned char *pbSignature, DWORD dwSize, PDS_DATA_BLOB pKey, 
					BOOL ignoreIncomplete, long sigIndexToVerify, BOOL provideSignedObjectBlob, PGLOBAL_SIG pg_sig);
// verify all XML Signatures in the document: URI
extern int axVerifyFile(const unsigned char *fileName, PDS_DATA_BLOB pKey,
						BOOL ignoreIncomplete, long sigIndexToVerify, PGLOBAL_SIG pg_sig);
// verify all XML Signatures in the document
extern int axVerifyDetachedFile (
	const unsigned char *xmlFileName, 
	PURI_PATH *uriList,
	int locNum,PDS_DATA_BLOB pKey, BOOL ignoreIncomplete, long sigIndexToVerify, PGLOBAL_SIG pg_sig);
// returns last error number
extern int axGetLastError(PGLOBAL_SIG pg_sig);
// returns error description: corresponding Windows error code
extern unsigned char *axGetError(PGLOBAL_SIG pg_sig);
// free internal structures
extern void axFree(PGLOBAL_SIG);
// returns base64 encoded certificate
extern unsigned char *axSelectCertificate (
	unsigned char *storeName,
	unsigned char *rootIssuer,
	int flagGUI,
	PGLOBAL_SIG pg_sig);
// After VERIFY:
// get signatures status: sigNum will be set to number of signatures
extern PSIG_STATUS *axGetSignature(int *sigNum, PGLOBAL_SIG pg_sig);

// Before SIGN:
// returns list of available certificates:
// size of array is written to "asize"
#ifdef NSS
extern PCERT_DESCR *axGetCertificateList(unsigned char *storeName, int *asize, PGLOBAL_SIG pg_sig);
#else
extern PCERT_DESCR *axGetCertificateList(unsigned char *storeName, int *asize);
#endif
// Before Encrypt:
// returns list of available certificates without access to private key:
// size of array is written to "asize"
extern PCERT_DESCR *axGetRecipientCertificateList(unsigned char *storeName, int *asize);

// return Base64 encoded certificate
extern unsigned char *axGetCertificate(unsigned char *storeName, unsigned char *certId);
// display certificate details (must be in store on localhost)
extern void axViewCertificate(unsigned char *storeName, unsigned char *certId);
// display any certificate
extern void axViewAnyCertificate(unsigned char *pbData);
// return BLOB: certificate with private key (PFX)
extern PDS_DATA_BLOB axExportCertificate(unsigned char *storeName, unsigned char *certId, LPCWSTR password, PGLOBAL_SIG pg_sig);

#if __cplusplus
}
#endif

#endif
