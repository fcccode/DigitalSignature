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

#ifndef __XS_H__
#define __XS_H__
#if __cplusplus
extern "C" {
#endif

#include <securexml/parser.h>
#include <securexml/coresig.h>

typedef int XS_ALGORITHM;
typedef const char *URI;

// get HTTP/File context of URI
extern BYTE *xsDereferenceURI (
	URI ref,
	DWORD *cbRef);
// generate <Reference>
extern reference *xsGenerateReference(
    const char *referenceId,
	XS_ALGORITHM digestMethod,
	const char *digestValue,
	const char *documentURI,
	PGLOBAL_SIG pg_sig);
// generate <Object>
extern object *xsGenerateObject(
    const char *objectId,
	const char *objectValue,
	const char **proparray,
	const int numprop,
	PGLOBAL_SIG pg_sig);
// generate <Transform>
extern st_transform *xsGenerateTransform(
    XS_ALGORITHM trAlgorithm,
	reference *rfs, PGLOBAL_SIG pg_sig);
// init signature
extern int xsInitSignature(
	char *sigId,
	//PDS_DATA_BLOB envBlob,
	xmlDocPtr doc,
	PGLOBAL_SIG pg_sig);
// sign and populate <SignatureValue> etc.
extern PDS_DATA_BLOB xsGetSignedInfo(
	const char *certData,
	PDS_DATA_BLOB hKey, 
	PGLOBAL_SIG pg_sig);
extern int xsSign(
	const char *certData,
	PDS_DATA_BLOB hKey, 
	PGLOBAL_SIG pg_sig);
// Apply transformation
extern int xsTransform (
	TRS_DATA_BLOB *sourceObject,	
	int trAlgorithm,
	TRS_DATA_BLOB *destObject,
	PGLOBAL_SIG pg_sig);
// resolve reference as octet stream
extern int xsGetReferenceOctets(
		reference *pref,
		PDS_DATA_BLOB objectBlob, PGLOBAL_SIG pg_sig);
// verify single <Signature> 
extern int xsVerify (
	xmlDocPtr xmlSigDoc,
	xmlNodePtr xmlSigNode, PDS_DATA_BLOB pKey, BOOL	provideSignedObjectBlob, PGLOBAL_SIG pg_sig);
// URI to number decoder, see coresig.h for numbers descriptions
extern int xsDecodeAlg(char *alg);
// free global data associated with API
extern void xsFree(PGLOBAL_SIG pg_sig);
// get string with error stack
extern char *xsGetErrorDescription(PGLOBAL_SIG pg_sig);
// get last error
extern int xsGetErrorNumber(PGLOBAL_SIG pg_sig);
// convert absolute file path to the file name
extern char *xsRemovePath(const char *fileName) ;
// get HTTP content
extern unsigned char *xsHTTPFetch(const char *URL, int *size);
// get nodeset
extern xmlNodeSetPtr xsGetChildNodeSet(const xmlNodePtr parent, xmlNodeSetPtr nodeSet, int withComments);
extern xmlNodePtr xsSigNodeById(const xmlNodePtr parent, const xmlChar *id);
extern xmlNodePtr xsSigNodeWithNoIdNoSigValue(const xmlNodePtr parent);
extern xmlNodeSetPtr xsGetSigNodeSet(const xmlNodePtr parent, xmlNodeSetPtr nodeSet);
extern BOOL isSignatureComplete(xmlNodePtr nptr);

extern int xsSignOnClient(
	const char *certData,		// certificate to sign
	PBYTE pbHash,				// <SignedInfo> hash
	PBYTE pbSignature,			// (out) signature BLOB
	DWORD *dwSigLen,				// (out) signature BLOB
	PBYTE pbPublicKey,			// (out) pub key BLOB
	DWORD *dwKeyLen,				// (out) pub key BLOB
	PDS_DATA_BLOB pHMACKey,			// (optional) HMAC key
	DWORD *pkalgtype,			// signature alg. type
	PGLOBAL_SIG pg_sig
	);

extern int xsAcceptSignature(
	const char *certData,
	PBYTE pbSignature,			// signature
	DWORD dwSigLen,				// signature size
	PBYTE keyBlobData,			// public key
	DWORD keySize,				// public key size
	DWORD pkalgtype,			// signature alg. type, from xsSignOnClient
	PGLOBAL_SIG pg_sig
	);


#if __cplusplus
}
#endif

#endif
