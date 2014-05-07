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
#include "StdAfx.h"
#ifdef WIN32
#include <windows.h>
#include <wincrypt.h>
#include <winldap.h>
#include <winber.h>
#endif
#include <math.h>
#include <cstdlib>
#include <list>

#include <vector>
using namespace std;

typedef list <unsigned char *> CrlList;

extern "C" {
#include <securexml/ax.h>
#include <securexml/cr.h>
#include <securexml/xs.h>
#include <securexml/utils.h>
#include <securexml/coresig.h>
#include <securexml/errors.h>
}
#include <securexml/base64.h>
#include "CertVerify.h"
#include <securexml/DebugLog.h>

#if defined LINUX && !defined SOLARIS
#include <securexml/wincryptLinux.h>
#endif
#ifdef NSS
static void FileTimeToT64(FILETIME *pft,int64 *pt);
static void SystemTimeToT64(SYSTEMTIME *pst,int64 *pt);
static int64 FindTimeTBase(void);
static int CompareCRLTime(SECItem *cTime, int64 pTime);
static PRBool CompareCerts(CERTCertificate *c1, CERTCertificate *c2);
static BOOL checkCertificate(CERTCertificate *pCertContext, 
							 CERTCertDBHandle *hStoreHandle,
							 int64 pTime, 
							 VERIFICATION_PARAMS *certVerParams,
							 PGLOBAL_SIG pg_sig);

static int check_CRL(CERTCertDBHandle *hStoreHandle,
					 CERTCertificate *pCertContext, 
					 CERTCertificate *pIssuerCertContext, 
					 int64 pTime, 
					 LPSTR *crlAltUrl,
					 UINT	altCrlCount,
					 BOOL	crlUrlIsCrlData,
					 BOOL	*crlFound,
					 CrlList *usedCrlList,
					 PGLOBAL_SIG pg_sig);

#else
static BOOL checkCertificate(PCCERT_CONTEXT pCertContext, 
							 HCERTSTORE hStoreHandle,
							 LPFILETIME pTime, 
							 VERIFICATION_PARAMS *certVerParams,
							 PGLOBAL_SIG pg_sig);
static int check_CRL(HCERTSTORE hStoreHandle,
					 PCCERT_CONTEXT pCertContext, 
					 PCCERT_CONTEXT pIssuerCertContext,
					 LPFILETIME pTime, 
					 CRLCache *pCrlCache,
					 LPSTR *crlAltUrl,
					 UINT	altCrlCount,
					 BOOL	crlUrlIsCrlData,
					 BOOL	*crlFound,
					 CrlList *usedCrlList,
					 PGLOBAL_SIG pg_sig);
#endif
/**
 * crVerifyCertificate
 * @certData: (in) array of base64 encoded PFX or X509 DER/ASN certificate
 * @certNum: (in) number certificates in array
 * @pSysTime:	(in) Time to use for certificate chain verification (optional, if NULL will use system time)
 * @hKey:	(in) PFX password
 * @pg_sig: (in) PGLOBAL_SIG
 *
 * Checks certificate chain, including revocation checking if pg_sig->doCRLCheck = true 
 *
 * Returns: TRUE/FALSE
 */
#ifdef NSS
BOOL crVerifyCertificate(BYTE **certData, 
						 UINT certNum,
						 LPSYSTEMTIME pSysTime, 
						 SECItem *password, 
						 VERIFICATION_PARAMS *certVerParams,
						 PGLOBAL_SIG pg_sig) 
#else
BOOL crVerifyCertificate(BYTE **certData, 
						 UINT certNum,
						 LPSYSTEMTIME pSysTime, 
						 LPWSTR password, 
						 VERIFICATION_PARAMS *certVerParams,
						 PGLOBAL_SIG pg_sig) 
#endif
{
BYTE *pbCert=NULL;
DWORD cbCert=0;
int err=0;
UINT i=0;

#ifdef NSS
SECItem pfxBlob;
CERTCertificate *pct=NULL;
CERTCertificate *endPct=NULL;
CERTCertDBHandle *hStoreHandle=NULL;
CERTCertificate **certs = NULL;
SECItem **derCerts = NULL;
int64 pTime=0;
SECStatus rv;
#else
HCRYPTPROV hProv;
CRYPT_KEY_PROV_INFO *provInfo;
CRYPT_DATA_BLOB pfxBlob;
PCCERT_CONTEXT pct=NULL;
PCCERT_CONTEXT endPct=NULL;
HCERTSTORE hStoreHandle=NULL;
FILETIME pfTime;
LPFILETIME pTime;
#endif

int optFlag =0;
BOOL sysTimeStatus=FALSE;
int res=0;
DWORD cbData=0;
DS_DATA_BLOB pwdBlob;

if (password!=NULL) {
#ifdef NSS
	pwdBlob.cbData= password->len;
	pwdBlob.pbData= password->data;
#else
	pwdBlob.cbData= 0;
	pwdBlob.pbData= (unsigned char *) password;
#endif
}else{
	pwdBlob.cbData= 0;
	pwdBlob.pbData= NULL;
}

//DebugBreak();

if (!certData) {
	setError(pg_sig, NO_CERTIFICATE);
	return FALSE;
}
#ifdef NSS
	hStoreHandle = CERT_GetDefaultCertDB();
		//(CERTCertDBHandle *)217865; // any non-0 number
#endif


if ((certVerParams->userPolicySetCountOut != 0) && 
	(certVerParams->userPolicySetOut != NULL))
{
	for (i=0; i < certVerParams->userPolicySetCountOut; i++)
	{
		if (certVerParams->userPolicySetOut[i] != NULL)
		{
			zFree(certVerParams->userPolicySetOut[i]);
			certVerParams->userPolicySetOut[i] = NULL;
		}
	}
	zFree(certVerParams->userPolicySetOut);
	certVerParams->userPolicySetCountOut = 0;
	certVerParams->userPolicySetOut = NULL;
}

if ((certVerParams->authPolicySetCountOut != 0) && 
	(certVerParams->authPolicySetOut != NULL))
{
	for (i=0; i < certVerParams->authPolicySetCountOut; i++)
	{
		if (certVerParams->authPolicySetOut[i] != NULL)
		{
			zFree(certVerParams->authPolicySetOut[i]);
			certVerParams->authPolicySetOut[i] = NULL;
		}
	}
	zFree(certVerParams->authPolicySetOut);
	certVerParams->authPolicySetCountOut = 0;
	certVerParams->authPolicySetOut = NULL;
}
//DebugBreak();
if ((certVerParams->usedCrlCount != 0) &&
	(certVerParams->usedCrlList != NULL))
{
	for (i=0; i < certVerParams->usedCrlCount; i++)
	{
		if (certVerParams->usedCrlList[i] != NULL)
		{
			zFree(certVerParams->usedCrlList[i]);
			certVerParams->usedCrlList[i] = NULL;
		}
	}
	zFree(certVerParams->usedCrlList);
	certVerParams->usedCrlList = NULL;
	certVerParams->usedCrlCount = 0;
}

if (pSysTime!=NULL) {
#ifdef NSS
SystemTimeToT64(pSysTime,&pTime);
#else
pTime = &pfTime;
sysTimeStatus = SystemTimeToFileTime(pSysTime, pTime);
#endif
} else {
#ifdef NSS
pTime=0;
#else
pTime=NULL;
#endif
}

#ifdef NSS
	derCerts = (SECItem **) zMalloc (sizeof(SECItem *) * certNum);
#endif

for (i=0;i<certNum;i++) {
	int realLen=0;
#ifdef NSS	
	pfxBlob.len = base64decodeSize(strlen((const char *)certData[i]));
	pfxBlob.data = (BYTE *)zMalloc (pfxBlob.len+1);
	if ((realLen= base64decode(certData[i],pfxBlob.data,pfxBlob.len))==-1) {
		setError(pg_sig, BASE64_ERROR);
		err=TRUE; goto retLabel;
	}
	pfxBlob.len = realLen;
	derCerts[i] = (SECItem *) zMalloc(sizeof(SECItem));
	derCerts[i]->len = pfxBlob.len;
	derCerts[i]->data = (BYTE *) zMalloc(pfxBlob.len);
	memcpy(derCerts[i]->data,pfxBlob.data,pfxBlob.len);
	
#else
	pfxBlob.cbData = base64decodeSize(strlen((const char *)certData[i]));
	pfxBlob.pbData = (BYTE *)zMalloc (pfxBlob.cbData+1);
	if ((realLen= base64decode(certData[i],pfxBlob.pbData,pfxBlob.cbData))==-1) {
		setError(pg_sig, BASE64_ERROR);
		err=TRUE; goto retLabel;
	}
	pfxBlob.cbData = realLen;
#endif

// special case: if certNum =1 it may be PFX
	if (certNum==1 
		&& crIsPFX(certData[i], &pwdBlob, pg_sig)) {
		//&& PFXIsPFXBlob(&pfxBlob)) {		
#ifdef NSS
		if (!(pct = NSS_ImportPKCS12Object(&pfxBlob, password, pg_sig))) {
			setError(pg_sig, PFX_BAD_PASSWORD);
			err=TRUE; goto retLabel;
		}
#else
		// check if we have password. For NSS it's already done by crIsPFX.
		if (!PFXVerifyPassword(&pfxBlob, password, CRYPT_MACHINE_KEYSET))
		{
			setError(pg_sig,PFX_BAD_PASSWORD);
			err=TRUE; goto retLabel;
		}

		if ((hStoreHandle =  PFXImportCertStore(
										&pfxBlob, 
										password, 
										CRYPT_MACHINE_KEYSET | CRYPT_EXPORTABLE
										)) == NULL)
		{
			setError(pg_sig,PFX_IMPORT_FAILED);
			err=TRUE; goto retLabel;
		}

		// we need CERT_CONTEXT
		while(pct = CertEnumCertificatesInStore(
			 hStoreHandle,
			pct))
		{			
				int optFlag=0;
				if (crFilterCerts(pct,&optFlag,NULL,pg_sig)) 
				{
					cleanupError(pg_sig);
					break;
				}
		}
#endif
		if (pct == NULL) {
			setError(pg_sig, PFX_INVALID_CERTIFICATE);
			err=TRUE; goto retLabel;
		}

		if (!checkCertificate(	pct, 
								hStoreHandle, 
								pTime,
								certVerParams,
								pg_sig)) {
			err=TRUE;
		}

// cleanup store
#ifdef NSS
	if (pfxBlob.data) zFree (pfxBlob.data);
	pfxBlob.data = NULL;
	
	// remove certificate from database
	SECStatus rv = SEC_DeletePermCertificate(pct);
    if (rv != SECSuccess) {
		setError(pg_sig, PFX_IMPORT_FAILED);
    }
#else
	res = CertGetCertificateContextProperty(pct,CERT_KEY_PROV_INFO_PROP_ID,NULL,&cbData);
	if (!res) goto retLabel;
	provInfo = (CRYPT_KEY_PROV_INFO *) zMalloc(cbData);
	if (!provInfo) goto retLabel;
	res = CertGetCertificateContextProperty(pct,CERT_KEY_PROV_INFO_PROP_ID,provInfo,&cbData);
	if (!res) goto retLabel;
	res = CryptAcquireContextW(&hProv, 
						 provInfo->pwszContainerName, 
						 provInfo->pwszProvName, 
						 provInfo->dwProvType, 
						 CRYPT_DELETEKEYSET |(provInfo->dwFlags  & CRYPT_MACHINE_KEYSET));
	zFree(provInfo);
#endif
	goto retLabel;
  }
#ifndef NSS
  else {

	// have to add certificate to the store
		if (hStoreHandle == NULL) {
			if(!(hStoreHandle = CertOpenStore(
			CERT_STORE_PROV_MEMORY,   // The memory provider type
			0,                        // The encoding type is not needed
			(HCRYPTPROV) NULL,                     // Use the default HCRYPTPROV
			0,                        // Accept the default dwFlags
			NULL                      // pvPara is not used
			))) {
				setError(pg_sig, CAPI_OPEN_STORE);
				err=TRUE; goto retLabel;
			}
		}

	if(!(CertAddEncodedCertificateToStore(
		hStoreHandle,
		MY_ENCODING_TYPE, // The encoding type
		(const BYTE*) pfxBlob.pbData,   // The encoded data from the certificate retrieved
		pfxBlob.cbData,
		CERT_STORE_ADD_REPLACE_EXISTING,
		&pct	)))  // The length of the encoded data
		{
			setError(pg_sig, CAPI_ADD_CERT);
			err=TRUE; goto retLabel;
		}
	
	if (i==0) endPct = pct;	// end certificate is always the first in array
	else{
		CertFreeCertificateContext(pct);
	}
  } // PFX?
#endif

#ifdef NSS
	if (pfxBlob.data) zFree (pfxBlob.data);
	pfxBlob.data = NULL;
#else
	if (pfxBlob.pbData) zFree (pfxBlob.pbData);
	pfxBlob.pbData = NULL;
#endif

} // for

#ifdef NSS
	// for NSS, no need in loop - all certificates are imported at once
	// add certificate to the store and CERTList
	pct = NULL;
	rv = CERT_ImportCerts(
			hStoreHandle, 
			certUsageObjectSigner,
			certNum, 
			derCerts,
			&certs, 
			PR_FALSE,
			PR_FALSE, 
			NULL);
	if (rv != SECSuccess) {		
		setError(pg_sig, CAPI_ADD_CERT);
		err=TRUE; goto retLabel;
	}

	endPct = certs[0];

#endif

	// certificates now in temp store. Take the end certificate and check it.
	if (!checkCertificate(	endPct, 
		hStoreHandle, 
		pTime,
		certVerParams,
		pg_sig)) {
		err=TRUE;
	}

retLabel:
#ifdef NSS
// cleanup DER list
for (i=0;i<certNum;i++) {
	zFree(derCerts[i]->data);
	zFree(derCerts[i]);
}
zFree(derCerts);

// go through cert array and delete all certificates
if (certs != NULL) CERT_DestroyCertArray(certs, certNum);
if (pct) CERT_DestroyCertificate(pct);

#else
// cleanup store
if (endPct) CertFreeCertificateContext(endPct);
if (hStoreHandle) {
	CertCloseStore(hStoreHandle,CERT_CLOSE_STORE_FORCE_FLAG);
}
#endif

#ifdef NSS
if (pfxBlob.data) zFree (pfxBlob.data);
#else
if (pfxBlob.pbData) zFree (pfxBlob.pbData);
#endif
if (err) 
	return FALSE;
else 
	return TRUE;

}

#ifdef NSS
static BOOL checkCertificate(CERTCertificate *pCertContext, 
							 CERTCertDBHandle *handle,
							 int64 pTime, 
							 VERIFICATION_PARAMS *certVerParams,
							 PGLOBAL_SIG pg_sig)
{
CERTCertificateList *chain=NULL;
CERTCertificate *rootCertificate=NULL;
CERTCertificate *pct = NULL;
DWORD dwFlag = 0;
int err=0;
UINT certIndex, issuerIndex;
BOOL checkCRLFailed;
UINT crlCount;
LPSTR *crlList;
BYTE *crlCertUrl=NULL;
LPSTR *authConstPolSet=NULL;
UINT	authConstPolCount=0;
LPSTR *userConstPolSet=NULL;
UINT	userConstPolCount=0;
UINT	explicitPolicyCount;
int i;
BOOL trustedRootFound=FALSE;
BOOL crlFound = FALSE;
BOOL result = FALSE;
SECStatus res;
CERTCertificate *c = NULL;

	
    chain = CERT_CertChainFromCert(pCertContext, certUsageObjectSigner, PR_TRUE);
    if (!chain) {
		return FALSE;
    }

	rootCertificate = DecodeDERCertificate(&chain->certs[chain->len-1]);
	if (!rootCertificate) {
		err=TRUE;
		goto exitCheckCertificate;
	}

	CERTVerifyLog log;
	log.arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
	c = NULL;
	SECCertificateUsage returnedUsages;
	res = SECFailure;

	for (i=chain->len-1; i>=0; i--) {		
		c = DecodeDERCertificate(&chain->certs[i]);
		if (!c) {
			err=TRUE;
			break;
		}
		// do basic check
		log.count = 0;
		log.head = NULL;
		log.tail = NULL;		

		SECCertUsage certUsage = certUsageObjectSigner;
		if (pTime==0) {
			pTime = PR_Now();
		}
		res = CERT_VerifyCertificate(handle,c,PR_TRUE,0,pTime,pg_sig,&log,&returnedUsages);
		if (log.head) {
			CERTVerifyLogNode *node;
			node = log.head;
			while ( node ) {
				switch (node->error) {
						case SEC_ERROR_EXPIRED_CERTIFICATE:
							setError(pg_sig, CERT_TIME_INVALID);
							err = TRUE;
							break;
						case SEC_ERROR_REVOKED_CERTIFICATE:
							//err = TRUE;
							break;
						case SEC_ERROR_BAD_SIGNATURE:
							setError(pg_sig, CERT_SIGNATURE_INVALID);
							err = TRUE;
							break;
						case SEC_ERROR_UNTRUSTED_ISSUER:
							//setError(pg_sig, CERT_UNTRUSTED_ROOT);
							//err = TRUE;
							break;
						default:
							//err = TRUE;
							break;
				}
				CERT_DestroyCertificate(node->cert);
				if (err) {
					break;
				}
				node = node->next;
			}
		}
		if (!err && res!=SECSuccess){
			setError (pg_sig, CAPI_GET_CERT_CHAIN);
			err = TRUE;
		}
		CERT_DestroyCertificate(c);	
		c=NULL;
		if (err) {
			break;
		}
	}

	if (err) {
		if (c) CERT_DestroyCertificate(c);		
		goto exitCheckCertificate;
	}

	if (certVerParams->verificationOptions & EXPLICIT_TRUST)
	{
		if ((certVerParams->trustRootCertCount == 0) ||
			(certVerParams->trustRootCerts == NULL))
		{
			setError(pg_sig, CERT_UNTRUSTED_ROOT);
			err=TRUE;
			goto exitCheckCertificate;
		}			
		for (i=0; i < (int)certVerParams->trustRootCertCount; i++)
		{
			SECItem derCert;
			derCert.len = base64decodeSize(strlen(certVerParams->trustRootCerts[i]));
			derCert.data = (unsigned char *) zMalloc (derCert.len+1);
			if (derCert.data == NULL)
			{
				setError(pg_sig, MEMORY_FAULT);
				err=TRUE; goto exitCheckCertificate;
			}
			memset(derCert.data,0x00,derCert.len);
			derCert.len = base64decode(	(unsigned char *)certVerParams->trustRootCerts[i],
				derCert.data,
				derCert.len);
			if (derCert.len == -1) 
			{
				setError(pg_sig, BASE64_ERROR);
				zFree(derCert.data);
				err=TRUE; goto exitCheckCertificate;
			}
			if (!(pct = DecodeDERCertificate(&derCert)))
			{
				setError(pg_sig, CAPI_CREATE_CERT_CNTX);
				zFree(derCert.data);
				err=TRUE; goto exitCheckCertificate;
			}

			if (CompareCerts(pct, rootCertificate))
			{
				trustedRootFound = TRUE;
				if (pct) CERT_DestroyCertificate(pct);
				pct = NULL;
				zFree(derCert.data);
				break;
			}
			if (pct) CERT_DestroyCertificate(pct);
			pct = NULL;
			zFree(derCert.data);
		}
		if (trustedRootFound == FALSE)
		{
			setError(pg_sig, CERT_UNTRUSTED_ROOT);
			err=TRUE;
			goto exitCheckCertificate;
		}
	}

	if (certVerParams->verificationOptions & VERIFY_CHAIN)
	{
		if (!certIsBasicExtensionConstraintOK(chain, handle, pg_sig))
		{
			setError(pg_sig, BASIC_CONSTRAINT_ERR);
			err = TRUE;
			goto exitCheckCertificate;
		}

		if (!certIsKeyUsageOK(chain,handle, pg_sig))
		{
			setError(pg_sig, CERT_KEY_USAGE_ERR);
			err = TRUE;
			goto exitCheckCertificate;
		}

		if (!certIsNameChainOK(chain, handle))
		{
			setError(pg_sig, CERT_INVALID_CHAIN);
			err = TRUE;
			goto exitCheckCertificate;
		}
	} // Verify chain

	if (certVerParams->verificationOptions & VERIFY_PATH_LENGTH)
	{
		if (!certIsPathLengthConstraintOK(chain, handle, pg_sig))
		{
			setError(pg_sig, CERT_PATHLEN_ERR);
			err = TRUE;
			goto exitCheckCertificate;
		}
	}

	if (certVerParams->verificationOptions & VERIFY_POLICY)
	{
		if (certVerParams->verificationOptions & POLICY_EXPLICIT)
			explicitPolicyCount = 0;
		else
			explicitPolicyCount = chain->len + 1;

		certVerParams->authPolicySetOut = getAuthConstrainedPolicySet(chain,
			handle,
			explicitPolicyCount,
			&certVerParams->explicitPolicyInd,// out
			&certVerParams->authPolicySetCountOut);
		if (certVerParams->verificationOptions & POLICY_EXPLICIT)
		{
			if (certVerParams->authPolicySetCountOut == 0)
			{
				certVerParams->userPolicySetCountOut=0;
				setError(pg_sig, CERT_POLICY_ERROR);
				err = TRUE;
				goto exitCheckCertificate;
			}
		}
		// this function returns Auth Constraint policy set if user policy is ANY
		certVerParams->userPolicySetOut = getUserConstrainedPolicySet(chain,
			handle,
			certVerParams->userPolicySet,
			certVerParams->userPolicyCount,
			explicitPolicyCount,
			&certVerParams->explicitPolicyInd,		// out
			&certVerParams->userPolicySetCountOut);			

		if ((certVerParams->verificationOptions & POLICY_EXPLICIT) && 
			(certVerParams->userPolicySetCountOut == 0))
		{
			if (certVerParams->userPolicySetCountOut == 0)
			{
				setError(pg_sig, CERT_POLICY_ERROR);
				err = TRUE;
				goto exitCheckCertificate;
			}
		}
		if ((certVerParams->explicitPolicyInd == 0) &&
			(certVerParams->userPolicySetCountOut == 0))
		{
			setError(pg_sig, CERT_POLICY_ERROR);
			err = TRUE;
			goto exitCheckCertificate;
		}

	} // VerifyPolicy


	if (certVerParams->verificationOptions & VERIFY_CRL)
	{
		CrlList *usedCrlList = new CrlList();

		checkCRLFailed = FALSE;
		for (certIndex=0; certIndex < (UINT) chain->len; certIndex++)
		{
			if (certIndex == chain->len - 1)
				issuerIndex = certIndex;
			else
				issuerIndex = certIndex+1;

			if ((certVerParams->altCrlCount != 0) &&
				(certVerParams->crlAltUrl != NULL))//Local CRL Location is given, so use that first
			{
				crlCount = certVerParams->altCrlCount;
				crlList = certVerParams->crlAltUrl;
				CERTCertificate *v_cert= DecodeDERCertificate(&chain->certs[certIndex]);
				CERTCertificate *v_issuer= DecodeDERCertificate(&chain->certs[issuerIndex]);
				if (!v_cert || !v_issuer) {
					checkCRLFailed = TRUE;
					break; // At least one of the certificates in the chain has a problem
				}
				result = check_CRL (handle, 
					v_cert, 
					v_issuer,
					pTime,
					crlList,
					crlCount,
					FALSE,
					&crlFound,
					usedCrlList,
					pg_sig);
				CERT_DestroyCertificate(v_cert);
				CERT_DestroyCertificate(v_issuer);
				if (crlFound == TRUE)
				{
					if (result == FALSE) //CRL validation failed for some reason
					{
						checkCRLFailed = TRUE;
						break; // At least one of the certificates in the chain has a problem
					}
					else // CRL validation was successful
					{
						crlFound = FALSE; // reset this boolean for the next certificate in the chain
						checkCRLFailed = FALSE;
						continue; // check the next certificate in the chain
					}
				}
			}
			if ((crlFound == TRUE) && (checkCRLFailed == FALSE)) // The whole chain validated successfully
				break;
			else
			{// CRL was not found in the given CRL Location list. Try certificate CRL DP
				CERTCertificate *v_cert= DecodeDERCertificate(&chain->certs[certIndex]);
				if (!v_cert) {
					checkCRLFailed = TRUE;
					break; 
				}
				crlCertUrl = getCRLDist(v_cert);					
				if (crlCertUrl == NULL)
				{
					if ( certIndex != 0)
					{
						// If this is the root certificate, then the CRL may be
						// available from the first intermediate certificate
						// since the issuers for both are the root CA
						if (certIndex == chain->len - 1)
						{
							CERTCertificate *v_cert0= DecodeDERCertificate(&chain->certs[certIndex-1]);
							if (!v_cert0) {
								checkCRLFailed = TRUE;
								break; 
							}
							crlCertUrl = getCRLDist(v_cert0);
							CERT_DestroyCertificate(v_cert0);
							if (crlCertUrl == NULL)
							{//No CRL DP present and none of the given CRL Locations, if any, matched
								crlFound = FALSE;
								checkCRLFailed = TRUE;
								setError(pg_sig, CRL_NOT_FOUND);
								CERT_DestroyCertificate(v_cert);
								break;
							}
							else
							{// CRL Location Found
								crlCount = 1;
								crlList = (LPSTR *)zMalloc(sizeof (char *));
								crlList[0] = (LPSTR)crlCertUrl;
							}
						}
						else
						{//No CRL DP present and none of the given CRL Locations, if any, matched
							crlFound = FALSE;
							checkCRLFailed = TRUE;
							setError(pg_sig, CRL_NOT_FOUND);
							CERT_DestroyCertificate(v_cert);
							break;
						}
					}
					else
					{//No CRL DP present and none of the given CRL Locations, if any, matched
						crlFound = FALSE;
						checkCRLFailed = TRUE;
						setError(pg_sig, CRL_NOT_FOUND);
						CERT_DestroyCertificate(v_cert);
						break;
					}
				}
				else
				{// CRL Location Found
					crlCount = 1;
					crlList = (LPSTR *)zMalloc(sizeof (char *));
					crlList[0] = (LPSTR)crlCertUrl;
				}
				CERTCertificate *v_issuer= DecodeDERCertificate(&chain->certs[issuerIndex]);

				if (!v_issuer) {
					checkCRLFailed = TRUE;
					if (crlCertUrl) zFree(crlCertUrl);
					if (crlList) zFree (crlList);
					break; 
				}
				result = check_CRL (handle,
					v_cert, 
					v_issuer,
					pTime,
					crlList,
					crlCount,
					FALSE,
					&crlFound,
					usedCrlList,
					pg_sig);
				CERT_DestroyCertificate(v_cert);
				CERT_DestroyCertificate(v_issuer);
				if (crlFound == TRUE)
				{
					if (result == FALSE) //CRL validation failed for some reason
					{
						checkCRLFailed = TRUE;
						zFree(crlCertUrl);
						zFree (crlList);
						break; // At least one of the certificates in the chain has a problem
					}
					else // CRL validation was successful
					{
						crlFound = FALSE; // reset this boolean for the next certificate in the chain
						zFree(crlCertUrl);
						zFree (crlList);
						continue; // check the next certificate in the chain
					}
				}
				else
				{	//No CRL DP present and none of the given CRL Locations, if any, matched
					crlFound = FALSE;
					checkCRLFailed = TRUE;
					zFree(crlCertUrl);
					zFree (crlList);
					break;
				}
			}
		}
		if (checkCRLFailed == FALSE)
			err = FALSE;
		else
			err = TRUE;
		//if (err == FALSE)
		//{
		unsigned int listSize = usedCrlList->size();
		if (listSize != 0)
		{
			certVerParams->usedCrlCount = listSize;
			certVerParams->usedCrlList = (LPSTR *) zMalloc(listSize * sizeof(LPSTR *));
			memset(certVerParams->usedCrlList, 0, listSize * sizeof(LPSTR *));
			CrlList::iterator iList;
			unsigned int crlIndex=0;
			for (iList = usedCrlList->end(), iList--; crlIndex < listSize; iList--, crlIndex++)
			{
				certVerParams->usedCrlList[crlIndex] = (LPSTR) zMalloc(strlen((const char *)*iList)+1);
				strcpy((char *)certVerParams->usedCrlList[crlIndex], (const char *)*iList);
				zFree(*iList);
			}
		}
		//}
		delete usedCrlList;
	} // VerifyCRL
	else
	{
		if (certVerParams->verificationOptions & VERIFY_CRL_REC)
		{
			CrlList *usedCrlList = new CrlList();
			checkCRLFailed = FALSE;
			if ((certVerParams->recCrlCount != 0) &&
				(certVerParams->recCrlList != NULL)) // Recorded CRL data is available
			{
				crlCount = certVerParams->recCrlCount;
				crlList = certVerParams->recCrlList;
				for (certIndex=0; certIndex < (UINT) chain->len; certIndex++)
				{
					if (certIndex == chain->len - 1)
						issuerIndex = certIndex;
					else
						issuerIndex = certIndex+1;
					CERTCertificate *v_cert= DecodeDERCertificate(&chain->certs[certIndex]);
					CERTCertificate *v_issuer= DecodeDERCertificate(&chain->certs[issuerIndex]);

					if (!v_cert || !v_issuer) {
						checkCRLFailed = TRUE;
						break;
					}
					result = check_CRL(	handle, 
						v_cert, 
						v_issuer,
						pTime, 
						crlList, 
						crlCount,
						TRUE,
						&crlFound,
						usedCrlList, 
						pg_sig);
					CERT_DestroyCertificate(v_cert);
					CERT_DestroyCertificate(v_issuer);

					if (crlFound == TRUE)
					{
						if (result == FALSE) //CRL validation failed for some reason
						{
							checkCRLFailed = TRUE;
							break; // At least one of the certificates in the chain has a problem
						}
						else // CRL validation was successful
						{
							crlFound = FALSE; // reset this boolean for the next certificate in the chain
							checkCRLFailed = FALSE;
							continue; // check the next certificate in the chain
						}
					}
					else
					{
						checkCRLFailed = TRUE;
						break;
					}
				}// for
				if (checkCRLFailed == FALSE)
					err = FALSE;
				else
					err = TRUE;
				//if (err == FALSE)
				//{
				unsigned int listSize = usedCrlList->size();
				if (listSize != 0)
				{
					certVerParams->usedCrlCount = listSize;
					certVerParams->usedCrlList = (LPSTR *) zMalloc(listSize * sizeof(LPSTR *));
					memset(certVerParams->usedCrlList, 0, listSize * sizeof(LPSTR *));
					CrlList::iterator iList;
					unsigned int crlIndex=0;
					for (iList = usedCrlList->end(), iList--; crlIndex < listSize; iList--, crlIndex++)
					{
						certVerParams->usedCrlList[crlIndex] = (LPSTR) zMalloc(strlen((const char *)*iList)+1);
						strcpy((char *)certVerParams->usedCrlList[crlIndex], (const char *)*iList);
						zFree(*iList);
					}
				}
				//}
			}// if Recorded CRL Data is available
			delete usedCrlList;
		} // if VERIFY_CRL_REC enabled
	}
    
exitCheckCertificate:
	if (rootCertificate) CERT_DestroyCertificate(rootCertificate);
	CERT_DestroyCertificateList(chain);
	if (err) {
		return FALSE;
	} else {
		return TRUE;
	}
}
#else
/**
 * Check certificate chain - trust and CRL check
 */
static BOOL checkCertificate(PCCERT_CONTEXT pCertContext,
							 HCERTSTORE hStoreHandle,
							 LPFILETIME pTime, 
							 VERIFICATION_PARAMS *certVerParams,
							 PGLOBAL_SIG pg_sig) {
// chain parameters
CERT_CHAIN_PARA ChainPara;
CERT_ENHKEY_USAGE EnhkeyUsage;
CERT_USAGE_MATCH  CertUsage;  
PCCERT_CHAIN_CONTEXT     pChainContext=NULL;
DWORD dwFlag = 0;
int err=0;
UINT certIndex, issuerIndex;
BOOL checkCRLFailed;
UINT crlCount;
LPSTR *crlList;
BYTE *crlCertUrl=NULL;
LPSTR *authConstPolSet=NULL;
UINT	authConstPolCount=0;
LPSTR *userConstPolSet=NULL;
UINT	userConstPolCount=0;
UINT	explicitPolicyCount;
UINT i;
BOOL trustedRootFound=FALSE;
unsigned char *pbData;
UINT	cbData;
CERT_CONTEXT *pct;
DWORD rootCertIndex;
BOOL crlFound = FALSE;
BOOL result = FALSE;

// create chain 
		EnhkeyUsage.cUsageIdentifier = 0;
		EnhkeyUsage.rgpszUsageIdentifier=NULL;
		CertUsage.dwType = USAGE_MATCH_TYPE_AND;
		CertUsage.Usage  = EnhkeyUsage;
		ChainPara.cbSize = sizeof(CERT_CHAIN_PARA);
		ChainPara.RequestedUsage=CertUsage;

		//if ((certVerParams->verificationOptions & VERIFY_CRL) &&
		//	(certVerParams->altCrlCount == 0))
		//	dwFlag = CERT_CHAIN_REVOCATION_CHECK_CHAIN;

		if(!CertGetCertificateChain(
			NULL,                  // Use the default chain engine.
			pCertContext,          // Pointer to the end certificate.
			pTime,                 // Use the default time (NULL) or specified
			hStoreHandle,          // Search the temporary store for PFX files.
			&ChainPara,            // Use AND logic, and enhanced key usage 
								   // as indicated in the ChainPara 
								   // data structure.
			dwFlag,
			NULL,                  // Currently reserved.
			&pChainContext))       // Return a pointer to the chain created.
		{
			setError (pg_sig, CAPI_GET_CERT_CHAIN);
			return FALSE;
		}

//DebugBreak();
		if (certVerParams->verificationOptions & EXPLICIT_TRUST)
		{
			if ((certVerParams->trustRootCertCount == 0) ||
				(certVerParams->trustRootCerts == NULL))
			{
				setError(pg_sig, CERT_UNTRUSTED_ROOT);
				err=TRUE;
				goto exitCheckCertificate;
			}
			rootCertIndex = pChainContext->rgpChain[0]->cElement - 1;
			for (i=0; i < certVerParams->trustRootCertCount; i++)
			{
				cbData = base64decodeSize(strlen(certVerParams->trustRootCerts[i]));
				pbData = (unsigned char *) zMalloc (cbData+1);
				if (pbData == NULL)
				{
					setError(pg_sig, MEMORY_FAULT);
					err=TRUE; goto exitCheckCertificate;
				}
				memset(pbData,0x00,cbData);
				cbData = base64decode(	(unsigned char *)certVerParams->trustRootCerts[i],
									pbData,
									cbData);
				if (cbData == -1) 
				{
					setError(pg_sig, BASE64_ERROR);
					zFree(pbData);
					err=TRUE; goto exitCheckCertificate;
				}
				if(!(pct = (CERT_CONTEXT *) CertCreateCertificateContext(
					MY_ENCODING_TYPE  ,            // The encoding type
					pbData,   // The encoded data from the certificate retrieved
					cbData)))  // The length of the encoded data
				{
					setError(pg_sig, CAPI_CREATE_CERT_CNTX);
					zFree(pbData);
					err=TRUE; goto exitCheckCertificate;
				}
				if (CertCompareCertificate(	MY_ENCODING_TYPE,
											pct->pCertInfo,
											pChainContext->rgpChain[0]->rgpElement[rootCertIndex]->pCertContext->pCertInfo
											))
				{
					trustedRootFound = TRUE;
					CertFreeCertificateContext(pct);
					zFree(pbData);
					break;
				}
				CertFreeCertificateContext(pct);
				zFree(pbData);
			}
			if (trustedRootFound == FALSE)
			{
				setError(pg_sig, CERT_UNTRUSTED_ROOT);
				err=TRUE;
				goto exitCheckCertificate;
			}
		}

		if (certVerParams->verificationOptions & VERIFY_CHAIN)
		{
			if (!certIsBasicExtensionConstraintOK(pChainContext, pg_sig))
			{
				setError(pg_sig, BASIC_CONSTRAINT_ERR);
				err = TRUE;
				goto exitCheckCertificate;
			}

			if (!certIsKeyUsageOK(pChainContext, pg_sig))
			{
				setError(pg_sig, CERT_KEY_USAGE_ERR);
				err = TRUE;
				goto exitCheckCertificate;
			}

			if (!certIsNameChainOK(pChainContext))
			{
				setError(pg_sig, CERT_INVALID_CHAIN);
				err = TRUE;
				goto exitCheckCertificate;
			}

			if (pChainContext->TrustStatus.dwErrorStatus & CERT_TRUST_IS_NOT_TIME_VALID)
			{
				setError(pg_sig, CERT_TIME_INVALID);
				err = TRUE;
				goto exitCheckCertificate;
			}

			if (pChainContext->TrustStatus.dwErrorStatus & CERT_TRUST_IS_NOT_TIME_NESTED)
			{
				setError(pg_sig, CERT_TIME_NOT_NESTED);
				err = TRUE;
				goto exitCheckCertificate;
			}

			if (pChainContext->TrustStatus.dwErrorStatus & CERT_TRUST_IS_NOT_SIGNATURE_VALID)
			{
				setError(pg_sig, CERT_SIGNATURE_INVALID);
				err = TRUE;
				goto exitCheckCertificate;
			}

			if (pChainContext->TrustStatus.dwErrorStatus & CERT_TRUST_IS_NOT_VALID_FOR_USAGE)
			{
				setError(pg_sig, CERT_INVALID_USAGE);
				err = TRUE;
				goto exitCheckCertificate;
			}

			if (pChainContext->TrustStatus.dwErrorStatus & CERT_TRUST_IS_UNTRUSTED_ROOT)
			{
				setError(pg_sig, CERT_UNTRUSTED_ROOT);
				err = TRUE;
				goto exitCheckCertificate;
			}

			if (pChainContext->TrustStatus.dwErrorStatus & CERT_TRUST_IS_CYCLIC)
			{
				setError(pg_sig, CERT_TRUST_CYCLIC);
				err = TRUE;
				goto exitCheckCertificate;
			}

			if (pChainContext->TrustStatus.dwErrorStatus & CERT_TRUST_IS_PARTIAL_CHAIN)
			{
				setError(pg_sig, CERT_PARTIAL_CHAIN);
				err = TRUE;
				goto exitCheckCertificate;
			}

			if (pChainContext->TrustStatus.dwErrorStatus & CERT_TRUST_CTL_IS_NOT_TIME_VALID)
			{
				setError(pg_sig, CERT_TIME_INVALID);
				err = TRUE;
				goto exitCheckCertificate;
			}

			if (pChainContext->TrustStatus.dwErrorStatus & CERT_TRUST_CTL_IS_NOT_SIGNATURE_VALID)
			{
				setError(pg_sig, CERT_SIGNATURE_INVALID);
				err = TRUE;
				goto exitCheckCertificate;
			}

			if (pChainContext->TrustStatus.dwErrorStatus & CERT_TRUST_CTL_IS_NOT_VALID_FOR_USAGE)
			{
				setError(pg_sig, CERT_INVALID_USAGE);
				err = TRUE;
				goto exitCheckCertificate;
			}
		}

		if (certVerParams->verificationOptions & VERIFY_PATH_LENGTH)
		{
			if (!certIsPathLengthConstraintOK(pChainContext, pg_sig))
			{
				setError(pg_sig, CERT_PATHLEN_ERR);
				err = TRUE;
				goto exitCheckCertificate;
			}
		}

		if (certVerParams->verificationOptions & VERIFY_POLICY)
		{
//DebugBreak();			
			if (certVerParams->verificationOptions & POLICY_EXPLICIT)
				explicitPolicyCount = 0;
			else
				explicitPolicyCount = pChainContext->rgpChain[0]->cElement + 1;

			certVerParams->authPolicySetOut = getAuthConstrainedPolicySet(pChainContext,
															explicitPolicyCount,
															&certVerParams->explicitPolicyInd,// out
															&certVerParams->authPolicySetCountOut);
			if (certVerParams->verificationOptions & POLICY_EXPLICIT)
			{
				if (certVerParams->authPolicySetCountOut == 0)
				{
					certVerParams->userPolicySetCountOut=0;
					setError(pg_sig, CERT_POLICY_ERROR);
					err = TRUE;
					goto exitCheckCertificate;
				}
			}
			// this function returns Auth Constraint policy set if user policy is ANY
			certVerParams->userPolicySetOut = getUserConstrainedPolicySet(pChainContext,
															certVerParams->userPolicySet,
															certVerParams->userPolicyCount,
															explicitPolicyCount,
															&certVerParams->explicitPolicyInd,		// out
															&certVerParams->userPolicySetCountOut);			

			if ((certVerParams->verificationOptions & POLICY_EXPLICIT) && 
				(certVerParams->userPolicySetCountOut == 0))
			{
				if (certVerParams->userPolicySetCountOut == 0)
				{
					setError(pg_sig, CERT_POLICY_ERROR);
					err = TRUE;
					goto exitCheckCertificate;
				}
			}
			if ((certVerParams->explicitPolicyInd == 0) &&
				(certVerParams->userPolicySetCountOut == 0))
			{
				setError(pg_sig, CERT_POLICY_ERROR);
				err = TRUE;
				goto exitCheckCertificate;
			}
											 
		}

		err=TRUE;

		switch(pChainContext->TrustStatus.dwErrorStatus)
		{
		case CERT_TRUST_NO_ERROR :
			err=FALSE;
			break;
		case CERT_TRUST_IS_NOT_TIME_VALID: 
			break;
		case CERT_TRUST_IS_NOT_TIME_NESTED: 
			break;
		case CERT_TRUST_IS_REVOKED:
			err=TRUE; // Don't pay attention to CAPI. We will validate CRL ourselves
			break;
		case CERT_TRUST_IS_NOT_SIGNATURE_VALID:
			setError(pg_sig,CRL_BAD_SIGNATURE);
			break;
		case CERT_TRUST_IS_NOT_VALID_FOR_USAGE:
			break;
		case CERT_TRUST_IS_UNTRUSTED_ROOT:
			break;
		case CERT_TRUST_REVOCATION_STATUS_UNKNOWN:
			break;
		case CERT_TRUST_IS_CYCLIC :
			break;
		case CERT_TRUST_IS_PARTIAL_CHAIN: 
			break;
		case CERT_TRUST_CTL_IS_NOT_TIME_VALID: 
			break;
		case CERT_TRUST_CTL_IS_NOT_SIGNATURE_VALID: 
			break;
		case CERT_TRUST_CTL_IS_NOT_VALID_FOR_USAGE: 
			break;
		case CERT_TRUST_IS_OFFLINE_REVOCATION:
			break;
		default:
			err=TRUE;
			break;
		} // End switch


		if (certVerParams->verificationOptions & VERIFY_CRL)
		{
//DebugBreak();
			//if (pChainContext->TrustStatus.dwErrorStatus & CERT_TRUST_IS_REVOKED)
			//{
			//	setError(pg_sig, CRL_CERT_REVOKED);
			//	err = TRUE;
			//	goto exitCheckCertificate;
			//}

			CrlList *usedCrlList = new CrlList();

			checkCRLFailed = FALSE;
			for (certIndex=0; certIndex < pChainContext->rgpChain[0]->cElement; certIndex++)
			{
				//DebugBreak();
				if (certIndex == pChainContext->rgpChain[0]->cElement - 1)
					issuerIndex = certIndex;
				else
					issuerIndex = certIndex+1;

				if ((certVerParams->altCrlCount != 0) &&
					(certVerParams->crlAltUrl != NULL))//Local CRL Location is given, so use that first
				{
					crlCount = certVerParams->altCrlCount;
					crlList = certVerParams->crlAltUrl;
					result = check_CRL (	hStoreHandle, 
											pChainContext->rgpChain[0]->rgpElement[certIndex]->pCertContext, 
									pChainContext->rgpChain[0]->rgpElement[issuerIndex]->pCertContext,
									pTime,
									certVerParams->pCrlCache,
									crlList,
									crlCount,
									FALSE,
									&crlFound,
									usedCrlList,
									pg_sig);
					if (crlFound == TRUE)
					{
						if (result == FALSE) //CRL validation failed for some reason
						{
							checkCRLFailed = TRUE;
							break; // At least one of the certificates in the chain has a problem
						}
						else // CRL validation was successful
						{
							crlFound = FALSE; // reset this boolean for the next certificate in the chain
							checkCRLFailed = FALSE;
							continue; // check the next certificate in the chain
						}
					}
				}
				if ((crlFound == TRUE) && (checkCRLFailed == FALSE)) // The whole chain validated successfully
					break;
				else
				{// CRL was not found in the given CRL Location list. Try certificate CRL DP
//DebugBreak();
					crlCertUrl = getCRLDist(pChainContext->rgpChain[0]->rgpElement[certIndex]->pCertContext);
					if (crlCertUrl == NULL)
					{
						if ( certIndex != 0)
						{
							// If this is the root certificate, then the CRL may be
							// available from the first intermediate certificate
							// since the issuers for both are the root CA
							if (certIndex == pChainContext->rgpChain[0]->cElement - 1)
							{
								crlCertUrl = getCRLDist(pChainContext->rgpChain[0]->rgpElement[certIndex -1]->pCertContext);
								if (crlCertUrl == NULL)
								{//No CRL DP present and none of the given CRL Locations, if any, matched
									crlFound = FALSE;
									checkCRLFailed = TRUE;
									setError(pg_sig, CRL_NOT_FOUND);
									break;
								}
								else
								{// CRL Location Found
									crlCount = 1;
									crlList = (LPSTR *)zMalloc(sizeof (char *));
									crlList[0] = (LPSTR)crlCertUrl;
								}
							}
							else
							{//No CRL DP present and none of the given CRL Locations, if any, matched
								crlFound = FALSE;
								checkCRLFailed = TRUE;
								setError(pg_sig, CRL_NOT_FOUND);
								break;
							}
						}
						else
						{//No CRL DP present and none of the given CRL Locations, if any, matched
							crlFound = FALSE;
							checkCRLFailed = TRUE;
							setError(pg_sig, CRL_NOT_FOUND);
							break;
						}
					}
					else
					{// CRL Location Found
						crlCount = 1;
						crlList = (LPSTR *)zMalloc(sizeof (char *));
						crlList[0] = (LPSTR)crlCertUrl;
					}

					result = check_CRL (hStoreHandle,
										pChainContext->rgpChain[0]->rgpElement[certIndex]->pCertContext, 
									pChainContext->rgpChain[0]->rgpElement[issuerIndex]->pCertContext,
									pTime,
									certVerParams->pCrlCache,
									crlList,
									crlCount,
									FALSE,
									&crlFound,
									usedCrlList,
									pg_sig);
					if (crlFound == TRUE)
					{
						if (result == FALSE) //CRL validation failed for some reason
						{
							checkCRLFailed = TRUE;
							zFree(crlCertUrl);
							zFree (crlList);
							break; // At least one of the certificates in the chain has a problem
						}
						else // CRL validation was successful
						{
							crlFound = FALSE; // reset this boolean for the next certificate in the chain
							zFree(crlCertUrl);
							zFree (crlList);
							continue; // check the next certificate in the chain
						}
					}
					else
					{	//No CRL DP present and none of the given CRL Locations, if any, matched
						if ( certIndex != 0)
						{
							// If this is the root certificate, then the CRL may be
							// available from the first intermediate certificate
							// since the issuers for both are the root CA
							if (certIndex == pChainContext->rgpChain[0]->cElement - 1)
							{
								cleanupError(pg_sig); // Remove all previous errors from the error stack
								crlCertUrl = getCRLDist(pChainContext->rgpChain[0]->rgpElement[certIndex -1]->pCertContext);
								if (crlCertUrl == NULL)
								{//No CRL DP present and none of the given CRL Locations, if any, matched
									crlFound = FALSE;
									checkCRLFailed = TRUE;
									setError(pg_sig, CRL_NOT_FOUND);
									break;
								}
								else
								{// CRL Location Found
									crlCount = 1;
									crlList = (LPSTR *)zMalloc(sizeof (char *));
									crlList[0] = (LPSTR)crlCertUrl;
									result = check_CRL (hStoreHandle,
														pChainContext->rgpChain[0]->rgpElement[certIndex]->pCertContext, 
													pChainContext->rgpChain[0]->rgpElement[issuerIndex]->pCertContext,
													pTime,
													certVerParams->pCrlCache,
													crlList,
													crlCount,
													FALSE,
													&crlFound,
													usedCrlList,
													pg_sig);
									if (crlFound == TRUE)
									{
										if (result == FALSE) //CRL validation failed for some reason
										{
											checkCRLFailed = TRUE;
											zFree(crlCertUrl);
											zFree (crlList);
											break; // At least one of the certificates in the chain has a problem
										}
										else // CRL validation was successful
										{
											crlFound = FALSE; // reset this boolean for the next certificate in the chain
											zFree(crlCertUrl);
											zFree (crlList);
											break; // We are done since this was the root certificate
										}
									}
									else
									{
										crlFound = FALSE;
										checkCRLFailed = TRUE;
										zFree(crlCertUrl);
										zFree (crlList);
										break;
									}
								}
							}
							else
							{//No CRL DP present and none of the given CRL Locations, if any, matched
								crlFound = FALSE;
								checkCRLFailed = TRUE;
								setError(pg_sig, CRL_NOT_FOUND);
								break;
							}
						}
						else
						{
							crlFound = FALSE;
							checkCRLFailed = TRUE;
							zFree(crlCertUrl);
							zFree (crlList);
							break;
						}
					}
				}
			}
			if (checkCRLFailed == FALSE)
				err = FALSE;
			else
				err = TRUE;
			//if (err == FALSE)
			//{
				unsigned int listSize = usedCrlList->size();
				if (listSize != 0)
				{
					certVerParams->usedCrlCount = listSize;
					certVerParams->usedCrlList = (LPSTR *) zMalloc(listSize * sizeof(LPSTR *));
					memset(certVerParams->usedCrlList, 0, listSize * sizeof(LPSTR *));
					CrlList::iterator iList;
					unsigned int crlIndex=0;
					for (iList = usedCrlList->end(), iList--; crlIndex < listSize; iList--, crlIndex++)
					{
						certVerParams->usedCrlList[crlIndex] = (LPSTR) zMalloc(strlen((const char *)*iList)+1);
						strcpy((char *)certVerParams->usedCrlList[crlIndex], (const char *)*iList);
						zFree(*iList);
					}
				}
			//}
			delete usedCrlList;
		}
		else
		{
			if (certVerParams->verificationOptions & VERIFY_CRL_REC)
			{
//				DebugBreak();
				//if (pChainContext->TrustStatus.dwErrorStatus & CERT_TRUST_IS_REVOKED)
				//{
				//	setError(pg_sig, CRL_CERT_REVOKED);
				//	err = TRUE;
				//	goto exitCheckCertificate;
				//}

				CrlList *usedCrlList = new CrlList();
				checkCRLFailed = FALSE;
				if ((certVerParams->recCrlCount != 0) &&
					(certVerParams->recCrlList != NULL)) // Recorded CRL data is available
				{
					crlCount = certVerParams->recCrlCount;
					crlList = certVerParams->recCrlList;
					for (certIndex=0; certIndex < pChainContext->rgpChain[0]->cElement; certIndex++)
					{
						if (certIndex == pChainContext->rgpChain[0]->cElement - 1)
							issuerIndex = certIndex;
						else
							issuerIndex = certIndex+1;

						result = check_CRL(	hStoreHandle, 
											pChainContext->rgpChain[0]->rgpElement[certIndex]->pCertContext, 
										pChainContext->rgpChain[0]->rgpElement[issuerIndex]->pCertContext,
										pTime, 
										NULL, // Don't use CrlCache
										crlList, 
										crlCount,
										TRUE,
										&crlFound,
										usedCrlList, 
										pg_sig);
						if (crlFound == TRUE)
						{
							if (result == FALSE) //CRL validation failed for some reason
							{
								checkCRLFailed = TRUE;
								break; // At least one of the certificates in the chain has a problem
							}
							else // CRL validation was successful
							{
								crlFound = FALSE; // reset this boolean for the next certificate in the chain
								checkCRLFailed = FALSE;
								continue; // check the next certificate in the chain
							}
						}
						else
						{
							checkCRLFailed = TRUE;
							break;
						}
					}// for
					if (checkCRLFailed == FALSE)
						err = FALSE;
					else
						err = TRUE;
					//if (err == FALSE)
					//{
						unsigned int listSize = usedCrlList->size();
						if (listSize != 0)
						{
							certVerParams->usedCrlCount = listSize;
							certVerParams->usedCrlList = (LPSTR *) zMalloc(listSize * sizeof(LPSTR *));
							memset(certVerParams->usedCrlList, 0, listSize * sizeof(LPSTR *));
							CrlList::iterator iList;
							unsigned int crlIndex=0;
							for (iList = usedCrlList->end(), iList--; crlIndex < listSize; iList--, crlIndex++)
							{
								certVerParams->usedCrlList[crlIndex] = (LPSTR) zMalloc(strlen((const char *)*iList)+1);
								strcpy((char *)certVerParams->usedCrlList[crlIndex], (const char *)*iList);
								zFree(*iList);
							}
						}
					//}
				}// if Recorded CRL Data is available
				delete usedCrlList;
			} // if VERIFY_CRL_REC enabled
		}


exitCheckCertificate:
		CertFreeCertificateChain(pChainContext);

		if (err) {
//			setError(pg_sig,CERT_TRUST_ERROR);
			return FALSE;
		} else {
			return TRUE;
		}
}

#endif

#ifdef NSS
static int check_CRL(CERTCertDBHandle *hStoreHandle,
					 CERTCertificate *pCertContext, 
					 CERTCertificate *pIssuerCertContext, 
					 int64 pTime, 
					 LPSTR *crlAltUrl,
					 UINT	altCrlCount,
					 BOOL	crlUrlIsCrlData,
					 BOOL	*crlFound,
					 CrlList *usedCrlList,
					 PGLOBAL_SIG pg_sig) 
{
	//+++
	BYTE *crlUrl=NULL;
	CERTCrl *pCrlContext=NULL;
	CERTCrlEntry *pCrlEntry = NULL;
	int ret=TRUE;
	SECItem *crl=NULL;
	UINT crlCount=0;
	UINT crlIndex;
	BOOL validCrlFound = FALSE;
	SECStatus ss;
	vector <SECItem *> crlBlobList;

		for (crlIndex=0; crlIndex < altCrlCount; crlIndex++)
		{
			crlBlobList.clear();
			if (crlUrlIsCrlData)
			{
				crl = (SECItem *) zMalloc(sizeof(SECItem));
				crl->len = base64decodeSize(strlen((const char *)crlAltUrl[crlIndex]));
				crl->data = (unsigned char *) zMalloc(crl->len + 1);
				if ((crl->len = base64decode((unsigned char *)crlAltUrl[crlIndex], crl->data, crl->len+1)) == -1)
				{
					setError(pg_sig, BASE64_ERROR);
					continue;
				}
			}
			else
			{
				crlUrl = (BYTE *) crlAltUrl[crlIndex];
				if (!crlUrl) 
					continue;

				if (strncmp((const char *)crlUrl,"ldap:",5)==0) 
				{
					PDS_DATA_BLOB *pCrl = fetchLDAP_URL(crlUrl);
					int i=0;
					while (pCrl && pCrl[i]) {
						crl = (SECItem *) zMalloc(sizeof(SECItem));
						crl->data = pCrl[i]->pbData;
						crl->len = pCrl[i]->cbData;
						crlBlobList.push_back(crl);
						i++;
					}
					zFree (pCrl);
				}
				else
				{
					PDS_DATA_BLOB pds=NULL;
					pds = fetch_URL(crlUrl);
					if (pds) {
						crl = (SECItem *) zMalloc(sizeof(SECItem));
						crl->data = pds->pbData;
						crl->len = pds->cbData;
						crlBlobList.push_back(crl);
					}else{
						crl = NULL;
					}
				}
				if (crlBlobList.size()==0) {
					cleanupError(pg_sig); // Remove all previous errors from the error stack
					ret=FALSE;
					continue;
				}

				//if (crl==NULL) {
				//	cleanupError(pg_sig); // Remove all previous errors from the error stack
				//	ret=FALSE;
				//	continue;
				//}
			}
		// list of BLOBs
		for (UINT i=0; i<crlBlobList.size(); i++) 
		{
			crl = crlBlobList.at(i);
			// create CRL context
			CERTSignedCrl *sCrl =
				CERT_DecodeDERCrl(NULL,crl,SEC_CRL_TYPE);
			if (sCrl==NULL) 
			{
				cleanupError(pg_sig); // Remove all previous errors from the error stack
				setError(pg_sig,CRL_ERROR);
				ret=FALSE;
				if (crl->data) 
					zFree(crl->data);
				zFree (crl);
				crl = NULL;
				continue;
			}			

//			ss = CERT_CompleteCRLDecodeEntries(sCrl);

			pCrlContext = &(sCrl->crl);
			BYTE *cName = (BYTE *) CERT_NameToAscii(&pCrlContext->name);

			// Check to see if the CRL issuer and the certificate issuers are the same
			if (certIsNameEqual((BYTE *)pCertContext->issuerName, cName) 
					== TRUE) // certificate and CRL issuers match
			{
				PORT_Free(cName);
				validCrlFound = TRUE;
				ss = CERT_VerifySignedData(&(sCrl->signatureWrap),
				       pIssuerCertContext,
				       pTime,
				       pg_sig);

				
				if (ss!=SECSuccess)
				{
					cleanupError(pg_sig); // Remove all previous errors from the error stack
					setError(pg_sig,CRL_BAD_SIGNATURE);
					ret=FALSE;
					SEC_DestroyCrl(sCrl);
					pCrlContext = NULL;
					if (crl->data) 
						zFree(crl->data);
					zFree (crl);
					crl = NULL;
					continue;
				}
				else // CRL has a valid signature from the cert issuer
				{
					CERTCertExtension **extensions = pCrlContext->extensions;
					*crlFound = TRUE;
					SECItem oid1, oid2;
					SECItem encodedExt;
					oid1.data = (BYTE *) oid_delta_crl_idicator;
					oid1.len = 3;
					oid2.data = (BYTE *) oid_issuing_disp_point;
					oid2.len = 3;

					encodedExt.data = NULL;
					encodedExt.len =0;

					/*
					 * Check for some v2 extensions
					 */
					// delta CRL lookup
					ss = i_cert_FindExtensionByOID(extensions,&oid1,&encodedExt);
					if ((ss == SECSuccess) && (encodedExt.len>0))
					{
						SECITEM_FreeItem(&encodedExt,PR_FALSE);
						validCrlFound = FALSE; // Set CRL Found to false in order to force a CRL Fetch
						setError(pg_sig, CRL_ERROR);
						ret=FALSE;
						SEC_DestroyCrl(sCrl);
						pCrlContext = NULL;
						if (crl->data) 
							zFree(crl->data);
						zFree (crl);
						crl = NULL;
						break;
					}
				
					// issuing disp point lookup
					ss = i_cert_FindExtensionByOID(extensions,&oid2,&encodedExt);
					if ((ss == SECSuccess) && (encodedExt.len>0))
					{
						SECITEM_FreeItem(&encodedExt,PR_FALSE);
						validCrlFound = FALSE; // Set CRL Found to false in order to force a CRL Fetch
						setError(pg_sig, CRL_ERROR);
						ret=FALSE;
						SEC_DestroyCrl(sCrl);
						pCrlContext = NULL;
						if (crl->data) 
							zFree(crl->data);
						zFree (crl);
						crl = NULL;
						break;
					}

					// Lets add the base64 encoded CRL to the crl list
					int size = base64encodeSize(crl->len);
					unsigned char *b64Crl = (unsigned char *)zMalloc(size+1);
					if ((size = base64encode(crl->data, crl->len, b64Crl, size+1)) == -1)
					{
						setError(pg_sig, BASE64_ERROR);
						zFree(b64Crl);
						break;
					}
					*(b64Crl + size) = '\0';
					usedCrlList->insert(usedCrlList->begin(), b64Crl);
					CERTCrlEntry *entry = FindCertInCRL(pCertContext, pCrlContext);
					if (entry != NULL) {
						// CRL contains this certificate
						// Compare the revocation time with pTime
						if (CompareCRLTime(&entry->revocationDate, pTime) <= 0)
						{// The certificate was revoked before pTime
							cleanupError(pg_sig); // Remove all previous errors from the error stack
							setError(pg_sig,CRL_CERT_REVOKED);
							ret=FALSE;
							SEC_DestroyCrl(sCrl);
							pCrlContext = NULL;
							if (crl->data) 
								zFree(crl->data);
							zFree (crl);
							crl = NULL;
							break;
						}
					}
				}
				
				// -1 means comparision time is after NextUpdate, and CRL is old.
				if (CompareCRLTime(&(pCrlContext->nextUpdate),pTime)==-1)
				{
					cleanupError(pg_sig); // Remove all previous errors from the error stack
					setError(pg_sig,CRL_TOO_OLD);
					ret=FALSE;
					SEC_DestroyCrl(sCrl);
					pCrlContext = NULL;
					if (crl->data) 
						zFree(crl->data);
					zFree (crl);
					crl = NULL;
					break;
				}
				
				
				if (crl->data) 
					zFree(crl->data);
				zFree (crl);
				crl = NULL;
				SEC_DestroyCrl(sCrl);
				
				break;
			}
			else // This CRL is not relevant since it's issuer is not the same as the certificate issuer
			{
				PORT_Free(cName);
				SEC_DestroyCrl(sCrl);
				
				pCrlContext = NULL;
				if (crl->data) 
					zFree(crl->data);
				zFree (crl);
				crl = NULL;
				continue;
			}
		}
	}

				
	if (!(validCrlFound))
	{
		setError(pg_sig,CRL_NOT_FOUND);
		ret=FALSE;
	}
	return ret;
}
#else
/**
 * Alternative procedure to verify certificate against CRL.
 * CRL URL can be ldap, http or file. In file case it is simply file name, no prefixes.
 *
 * Returns: TRUE/FALSE, TRUE if CRL fetched, validated and doesn't contain certificate serial.
 *			FALSE if CRL cannot be fetched or CRL contains certificate serial.
 */
static int check_CRL(HCERTSTORE hStoreHandle,
					 PCCERT_CONTEXT pCertContext, 
					 PCCERT_CONTEXT pIssuerCertContext, 
					 LPFILETIME pTime, 
					 CRLCache *pCrlCache,
					 LPSTR *crlAltUrl,
					 UINT	altCrlCount,
					 BOOL	crlUrlIsCrlData,
					 BOOL	*crlFound,
					 CrlList *usedCrlList,
					 PGLOBAL_SIG pg_sig) {
	BYTE *crlUrl=NULL;
	PCCRL_CONTEXT pCrlContext=NULL;
	PCRL_ENTRY pCrlEntry = NULL;//(PCRL_ENTRY) zMalloc(sizeof(CRL_ENTRY));
	PCRL_ENTRY *ppCrlEntry = &pCrlEntry;
	int ret=TRUE;
	PDS_DATA_BLOB crl=NULL;
	PDS_DATA_BLOB *crlDataList=NULL;
	UINT crlCount=0;
	UINT crlIndex;
	BOOL validCrlFound = FALSE;

	EnterPgSigLog;

//DebugBreak();
	if (pCrlCache != NULL)
	{
//		DebugBreak();
		crlDataList = pCrlCache->FetchCRLFromCRLCache(	&pCertContext->pCertInfo->Issuer,
														&crlCount,
														pg_sig);
		if ((crlCount != 0) && (crlDataList != NULL))
		{// A CRL was found in the CRL Cache
			for (crlIndex=0; crlIndex < crlCount; crlIndex++)
			{
				crl = crlDataList[crlIndex];
				// create CRL context
				pCrlContext = CertCreateCRLContext(MY_TYPE,crl->pbData,crl->cbData);
				if (pCrlContext==NULL) 
				{
					cleanupError(pg_sig); // Remove all previous errors from the error stack
					setError(pg_sig,CRL_ERROR);
					ret=FALSE;
					continue;
				}
				// Check to see if the CRL issuer and the certificate issuers are the same
				if (certIsNameEqual(&pCertContext->pCertInfo->Issuer, 	&pCrlContext->pCrlInfo->Issuer) 
						== TRUE) // certificate and CRL issuers match
				{
					validCrlFound = TRUE;
					if (!CryptVerifyCertificateSignature(
						(HCRYPTPROV) NULL,	// CSP
						MY_TYPE,
						pCrlContext->pbCrlEncoded,	
						pCrlContext->cbCrlEncoded,
						&pIssuerCertContext->pCertInfo->SubjectPublicKeyInfo))
					{
						cleanupError(pg_sig); // Remove all previous errors from the error stack
						setError(pg_sig,CRL_BAD_SIGNATURE);
						ret=FALSE;
						CertFreeCRLContext(pCrlContext);
						pCrlContext = NULL;
						continue;
					}
					else // CRL has a valid signature from the cert issuer
					{
						PCERT_EXTENSION  pCertExtInfo = NULL;
						*crlFound = TRUE;
						pCertExtInfo = CertFindExtension(	szOID_DELTA_CRL_INDICATOR,
															pCrlContext->pCrlInfo->cExtension,
															pCrlContext->pCrlInfo->rgExtension);
						if (pCertExtInfo != NULL)
						{
							validCrlFound = FALSE; // Set CRL Found to false in order to force a CRL Fetch
							pCrlCache->DeleteCRLFromCRLCache(&pCertContext->pCertInfo->Issuer, crl, pg_sig);

							setError(pg_sig, CRL_ERROR);
							ret=FALSE;
							CertFreeCRLContext(pCrlContext);
							pCrlContext = NULL;
							break;
						}
						
						pCertExtInfo = CertFindExtension(	szOID_ISSUING_DIST_POINT,
															pCrlContext->pCrlInfo->cExtension,
															pCrlContext->pCrlInfo->rgExtension);
						if (pCertExtInfo != NULL)
						{
							validCrlFound = FALSE; // Set CRL Found to false in order to force a CRL Fetch
							pCrlCache->DeleteCRLFromCRLCache(&pCertContext->pCertInfo->Issuer, crl, pg_sig);

							setError(pg_sig, CRL_ERROR);
							ret=FALSE;
							CertFreeCRLContext(pCrlContext);
							pCrlContext = NULL;
							break;
						}
						// Lets add the base64 encoded CRL to the crl list
						int size = base64encodeSize(crl->cbData);
						unsigned char *b64Crl = (unsigned char *)zMalloc(size+1);
						if ((size = base64encode(crl->pbData, crl->cbData, b64Crl, size+1)) == -1)
						{
							setError(pg_sig, BASE64_ERROR);
							zFree(b64Crl);
							break;
						}
						*(b64Crl + size) = '\0';
						usedCrlList->insert(usedCrlList->begin(), b64Crl);

						if (!CertFindCertificateInCRL(pCertContext,pCrlContext,0,0,ppCrlEntry)) 
						{
							// list wasn't searched
							cleanupError(pg_sig); // Remove all previous errors from the error stack
							setError(pg_sig,CRL_ERROR);
							ret=FALSE;
							CertFreeCRLContext(pCrlContext);
							pCrlContext = NULL;
							continue;
						}
						//Add this to the Store for faster validation in the future
						//CertAddCRLContextToStore(hStoreHandle, pCrlContext,CERT_STORE_ADD_NEWER,NULL);

						if (pCrlEntry!=NULL) {
							// CRL contains this certificate
							// Compare the revocation time with pTime
							if (CompareFileTime((const FILETIME *)&pCrlEntry->RevocationDate, pTime) <= 0)
							{// The certificate was revoked before pTime
								cleanupError(pg_sig); // Remove all previous errors from the error stack
								setError(pg_sig,CRL_CERT_REVOKED);
								ret=FALSE;
								CertFreeCRLContext(pCrlContext);
								pCrlContext = NULL;
								pCrlEntry=NULL;
								break;
							}
						}
					}// CRL has a valid signature from the cert issuer
					if (CertVerifyCRLTimeValidity(pTime, pCrlContext->pCrlInfo) == 1)
					{
						cleanupError(pg_sig); // Remove all previous errors from the error stack

						validCrlFound = FALSE; // Set CRL Found to false in order to force a CRL Fetch
						pCrlCache->DeleteCRLFromCRLCache(&pCertContext->pCertInfo->Issuer, crl, pg_sig);

						setError(pg_sig,CRL_TOO_OLD);
						ret=FALSE;
						CertFreeCRLContext(pCrlContext);
						pCrlContext = NULL;
						break;
					}
					//if (crl->pbData) 
					//	zFree(crl->pbData);
					//zFree (crl);
					CertFreeCRLContext(pCrlContext);
					break;
				}//CRL issuer and cert issuers are the same
				else // This CRL is not relevant since it's issuer is not the same as the certificate issuer
				{
					CertFreeCRLContext(pCrlContext);
					pCrlContext = NULL;
					//if (crl->pbData) 
					//	zFree(crl->pbData);
					//zFree (crl);
					//crl = NULL;
					continue;
				}
			}//for (crlIndex=0; crlIndex < crlCount; crlIndex++)
			for (unsigned int i=0; i<crlCount; i++)
			{
				if (crlDataList[i] != NULL)
				{
					if (crlDataList[i]->pbData != NULL)
						zFree(crlDataList[i]->pbData);
					zFree(crlDataList[i]);
				}
			}
			zFree(crlDataList);
		}//if ((crlCount != 0) && (crlDataList != NULL))
	}//pCrlCache!=NULL
//DebugBreak();
	if (validCrlFound == FALSE)
	{
		vector <PDS_DATA_BLOB> crlBlobList;

		for (crlIndex=0; crlIndex < altCrlCount; crlIndex++)
		{
			if (crlUrlIsCrlData)
			{
				crl = (PDS_DATA_BLOB) zMalloc(sizeof(DS_DATA_BLOB));
				crl->cbData = base64decodeSize(strlen((const char *)crlAltUrl[crlIndex]));
				crl->pbData = (unsigned char *) zMalloc(crl->cbData + 1);
				if ((crl->cbData = base64decode((unsigned char *)crlAltUrl[crlIndex], crl->pbData, crl->cbData+1)) == -1)
				{
					setError(pg_sig, BASE64_ERROR);
					continue;
				}
				crlBlobList.push_back(crl);
			}
			else
			{
				crlUrl = (BYTE *) crlAltUrl[crlIndex];
				if (!crlUrl) 
					continue;

				if (strncmp((const char *)crlUrl,"ldap:",5)==0) 
				{
					PDS_DATA_BLOB *pCrl = fetchLDAP_URL(crlUrl);
					int i=0;
					while (pCrl && pCrl[i]) {
						crlBlobList.push_back(pCrl[i]);
						i++;
					}
					zFree (pCrl);
				}
				else
				{
					crl = fetch_URL(crlUrl);
					crlBlobList.push_back(crl);
				}
				if (crlBlobList.size()==0) {
					cleanupError(pg_sig); // Remove all previous errors from the error stack
					ret=FALSE;
					continue;
				}
			}
		}

		// list of BLOBs
		for (UINT i=0; i<crlBlobList.size(); i++) 
		{
			crl = crlBlobList.at(i);
			if (crl != NULL)
			{
#ifdef DEBUG
				char crlFileName[MAX_PATH];
				sprintf(crlFileName, "c:\\temp\\fetchedCrl%02d_%02d.crl", crlIndex, i);
				FILE *fHandle = fopen((const char *)crlFileName, "wb");
				fwrite((const void *)crl->pbData, crl->cbData, 1, fHandle);
				fclose(fHandle);
#endif
				// create CRL context
				pCrlContext = CertCreateCRLContext(MY_TYPE,crl->pbData,crl->cbData);
				if (pCrlContext==NULL) 
				{
					cleanupError(pg_sig); // Remove all previous errors from the error stack
					setError(pg_sig,CRL_ERROR);
					ret=FALSE;
					if (crl->pbData) 
						zFree(crl->pbData);
					zFree (crl);
					crl = NULL;
					continue;
				}
				if (pCrlCache != NULL)
				{
					//Enter CRL into the CRL Cache
					pCrlCache->EnterCRLIntoCRLCache(&pCrlContext->pCrlInfo->Issuer,crl, pg_sig);
				}
				// Check to see if the CRL issuer and the certificate issuers are the same
				if (certIsNameEqual(&pCertContext->pCertInfo->Issuer, 	&pCrlContext->pCrlInfo->Issuer) 
						== TRUE) // certificate and CRL issuers match
				{
					validCrlFound = TRUE;
					if (!CryptVerifyCertificateSignature(
						(HCRYPTPROV) NULL,	// CSP
						MY_TYPE,
						pCrlContext->pbCrlEncoded,	
						pCrlContext->cbCrlEncoded,
						&pIssuerCertContext->pCertInfo->SubjectPublicKeyInfo))
					{
						cleanupError(pg_sig); // Remove all previous errors from the error stack
						setError(pg_sig,CRL_BAD_SIGNATURE);
						ret=FALSE;
						CertFreeCRLContext(pCrlContext);
						pCrlContext = NULL;
						if (crl->pbData) 
							zFree(crl->pbData);
						zFree (crl);
						crl = NULL;
						continue;
					}
					else // CRL has a valid signature from the cert issuer
					{
						PCERT_EXTENSION  pCertExtInfo = NULL;
						*crlFound = TRUE;
						pCertExtInfo = CertFindExtension(	szOID_DELTA_CRL_INDICATOR,
															pCrlContext->pCrlInfo->cExtension,
															pCrlContext->pCrlInfo->rgExtension);
						if (pCertExtInfo != NULL)
						{
							setError(pg_sig, CRL_ERROR);
							ret=FALSE;
							CertFreeCRLContext(pCrlContext);
							pCrlContext = NULL;
							if (crl->pbData) 
								zFree(crl->pbData);
							zFree (crl);
							crl = NULL;
							break;
						}
						
						pCertExtInfo = CertFindExtension(	szOID_ISSUING_DIST_POINT,
															pCrlContext->pCrlInfo->cExtension,
															pCrlContext->pCrlInfo->rgExtension);
						if (pCertExtInfo != NULL)
						{
							setError(pg_sig, CRL_ERROR);
							ret=FALSE;
							CertFreeCRLContext(pCrlContext);
							pCrlContext = NULL;
							if (crl->pbData) 
								zFree(crl->pbData);
							zFree (crl);
							crl = NULL;
							break;
						}
						// Lets add the base64 encoded CRL to the crl list
						int size = base64encodeSize(crl->cbData);
						unsigned char *b64Crl = (unsigned char *)zMalloc(size+1);
						if ((size = base64encode(crl->pbData, crl->cbData, b64Crl, size+1)) == -1)
						{
							setError(pg_sig, BASE64_ERROR);
							zFree(b64Crl);
							break;
						}
						*(b64Crl + size) = '\0';
						usedCrlList->insert(usedCrlList->begin(), b64Crl);

						if (!CertFindCertificateInCRL(pCertContext,pCrlContext,0,0,ppCrlEntry)) 
						{
							// list wasn't searched
							cleanupError(pg_sig); // Remove all previous errors from the error stack
							setError(pg_sig,CRL_ERROR);
							ret=FALSE;
							CertFreeCRLContext(pCrlContext);
							pCrlContext = NULL;
							if (crl->pbData) 
								zFree(crl->pbData);
							zFree (crl);
							crl = NULL;
							continue;
						}
						//Add this to the Store for faster validation in the future
						//CertAddCRLContextToStore(hStoreHandle, pCrlContext,CERT_STORE_ADD_NEWER,NULL);

						if (pCrlEntry!=NULL) {
							// CRL contains this certificate
							// Compare the revocation time with pTime
							if (CompareFileTime((const FILETIME *)&pCrlEntry->RevocationDate, pTime) <= 0)
							{// The certificate was revoked before pTime
								cleanupError(pg_sig); // Remove all previous errors from the error stack
								setError(pg_sig,CRL_CERT_REVOKED);
								ret=FALSE;
								CertFreeCRLContext(pCrlContext);
								pCrlContext = NULL;
								pCrlEntry=NULL;
								if (crl->pbData) 
									zFree(crl->pbData);
								zFree (crl);
								crl = NULL;
								break;
							}
						}
					}
					if (CertVerifyCRLTimeValidity(pTime, pCrlContext->pCrlInfo) == 1)
					{
						cleanupError(pg_sig); // Remove all previous errors from the error stack
						setError(pg_sig,CRL_TOO_OLD);
						ret=FALSE;
						CertFreeCRLContext(pCrlContext);
						pCrlContext = NULL;
						if (crl->pbData) 
							zFree(crl->pbData);
						zFree (crl);
						crl = NULL;
						break;
					}
					if (crl->pbData) 
						zFree(crl->pbData);
					zFree (crl);
					crl = NULL;
					CertFreeCRLContext(pCrlContext);
					break;
				}
				else // This CRL is not relevant since it's issuer is not the same as the certificate issuer
				{
					CertFreeCRLContext(pCrlContext);
					pCrlContext = NULL;
					if (crl->pbData) 
						zFree(crl->pbData);
					zFree (crl);
					crl = NULL;
					continue;
				}
			}//if (crl != NULL)
		}//for (UINT i=0; i<crlBlobList.size(); i++)
	}//if (validCrlFound == FALSE)
	if (!(validCrlFound))
	{
		setError(pg_sig,CRL_NOT_FOUND);
		ret=FALSE;
	}
	ExitPgSigLog;
	return ret;
}
#endif

#ifdef NSS
static PRBool
CompareCerts(CERTCertificate *c1, CERTCertificate *c2)
{
    SECComparison comp;
    
    comp = SECITEM_CompareItem(&c1->derCert, &c2->derCert);
    if ( comp == SECEqual ) { /* certs are the same */
	return(PR_TRUE);
    } else {
	return(PR_FALSE);
    }
}

//#define SECS_TO_FT_MULT 10000000
#define SECS_TO_FT_MULT 10
static void SystemTimeToT64(SYSTEMTIME *pst,int64 *pt)
{
 FILETIME ft;
 SystemTimeToFileTime(pst, &ft);
 FileTimeToT64(&ft,pt);
 *pt-=FindTimeTBase();
}
static int64 FindTimeTBase(void)
{
 // Find 1st Jan 1970 as a FILETIME 
 int64 tbase;
 SYSTEMTIME st;
 FILETIME ft;
 memset(&st,0,sizeof(st));
 st.wYear=1970;
 st.wMonth=1;
 st.wDay=1;
 SystemTimeToFileTime(&st, &ft);
 FileTimeToT64(&ft,&tbase);
 return tbase;
}
static void FileTimeToT64(FILETIME *pft,int64 *pt)
{
 LARGE_INTEGER li;    
 li.LowPart = pft->dwLowDateTime;
 li.HighPart = pft->dwHighDateTime;
 *pt=li.QuadPart;
 *pt/=SECS_TO_FT_MULT;
}

// returns -1 if pTime is later then cTime, 0 if pTime is same as cTime, 1 if cTime is later then pTime
static int CompareCRLTime(SECItem *cTime, int64 pTime)
{
	// convert SECItem to int64 time and compare
	int64 utcTime;
	int rv = DER_UTCTimeToTime(&utcTime, cTime);
    if (rv) {
        return -100;
    }
	if (utcTime>pTime) {
		return 1;
	}else if (utcTime==pTime){
		return 0;
	}else{
		return -1;
	}
}
#endif
