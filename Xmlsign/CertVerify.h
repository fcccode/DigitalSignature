/*****************************************************************************************
 * Copyright: (c) 2000-2002 Infomosaic Corporation.
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
#ifndef __CERTVERIFY_H__
#define __CERTVERIFY_H__
#include "CRLCache.h"

// Bit map for various certificate validation options
#define VERIFY_CRL				0x01
#define VERIFY_POLICY			0x02
#define VERIFY_CHAIN			0x04
#define VERIFY_PATH_LENGTH		0x08
#define POLICY_EXPLICIT			0x10
#define EXPLICIT_TRUST			0x20
#define VERIFY_CRL_REC			0x40		// Verify certificate with the CRL data included in the signature

typedef struct _CERTVERIFICATIONPARAMS VERIFICATION_PARAMS;
typedef struct _CERTVERIFICATIONPARAMS * PVERIFICATION_PARAMS;
struct _CERTVERIFICATIONPARAMS {
							 CRLCache *pCrlCache;
							 LPSTR *crlAltUrl;
							 UINT  altCrlCount;
							 LPSTR *recCrlList;				// Crl list as included in the signature element
							 UINT  recCrlCount;				// Number of Crls included above
							 LPSTR *userPolicySet;
							 UINT  userPolicyCount;
							 UINT  verificationOptions;
							 LPSTR *trustRootCerts;
							 UINT  trustRootCertCount;
							 LPSTR *authPolicySetOut;		// out
							 UINT  authPolicySetCountOut;	// out
							 LPSTR *userPolicySetOut;		// out
							 UINT  userPolicySetCountOut;	// out
							 BOOL  explicitPolicyInd;		// out
							 UINT  usedCrlCount;			// out
							 LPSTR *usedCrlList;			// out
};
#ifdef NSS
extern BOOL crVerifyCertificate(BYTE **certData, 
								UINT certNum,
								LPSYSTEMTIME pSysTime, 
								SECItem *password,
								VERIFICATION_PARAMS *certVerParams,
								PGLOBAL_SIG pg_sig);
#else
extern BOOL crVerifyCertificate(BYTE **certData, 
								UINT certNum,
								LPSYSTEMTIME pSysTime, 
								LPWSTR hKey,
								VERIFICATION_PARAMS *certVerParams,
								PGLOBAL_SIG pg_sig);
#endif
#endif
