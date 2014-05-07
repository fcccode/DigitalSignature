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
 *****************************************************************************************
 */
 
/*
 * The example shows how to generate XPath transformation and produce  
 * enveloped signature from template
 */

#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <securexml/coresig.h>
#include <securexml/parser.h>
#include <securexml/xs.h>
#include <securexml/cr.h>
#include <securexml/ax.h>
#include <securexml/utils.h>
#include <securexml/base64.h>

void main() {
PCERT_DESCR *certs=NULL;
DS_DATA_BLOB crBlob;
char *certData;
char *cSigAlg=NULL;
char *xsignature;
int iSigMethod=0;
int dsize=0,i=0,j=0;
transform *ptrs=NULL;
reference *pref=NULL;
keyinfo *ki=NULL;
xpath *xpth=NULL;
FILE *hFile;
int refNum=0, signum=0;
PSIG_STATUS *sgArr=NULL;
PURI_STATUS *refArr=NULL;
PGLOBAL_SIG pg_sig = NULL; 
x509data *curX509Data=NULL;
x509group *curX509Group=NULL;

axFree(pg_sig); 
pg_sig = axInit(); 
 
certData = axSelectCertificate("MY",NULL,1);
/*
 * detect signature method from certificate
 */
	cSigAlg= (char *) malloc(512);
	memset(cSigAlg,0,512);

switch (crGetProviderType(certData)) {
case sigAlgRSA:
	iSigMethod = RSAWITHSHA1;
	strcpy(cSigAlg,ALG_RSAWITHSHA1);
	break;
case sigAlgDSA:
	iSigMethod = DSAWITHSHA1;
	strcpy(cSigAlg,ALG_DSAWITHSHA1);
	break;
default:
	printf("Invalid provider\n");
	exit(1);
}
 

	/*
	 * Read envelope. Use helper function for it.
	 */
	crBlob.pbData = xsDereferenceURI("signature.tmpl",&(crBlob.cbData));
	if (!crBlob.pbData) {
		printf ("Error: %d, %s\n",axGetLastError(pg_sig),axGetError(pg_sig));
		exit(1);
	}

	/*
	 * init Signature. crBlob contains XML - envelope document
	 */
	if (xsInitSignature(NULL,&crBlob, pg_sig)!=TRUE) {
		printf ("Error: %d, %s\n",axGetLastError(pg_sig), axGetError(pg_sig));
		exit(1);
	}

	/*
	 * set <X509Data> certificate
	 */
	ki = xsCoreAddKeyInfo(pg_sig);
	curX509Data = xsCoreAddX509Data(ki, pg_sig);
	curX509Group = xsCoreAddX509Group(curX509Data, pg_sig);
	if (xsCoreSetX509Group(curX509Group,NULL,NULL,(char *)certData,NULL, NULL, NULL, pg_sig)!=TRUE)
	{
		printf ("Error: %d, %s\n",axGetLastError(pg_sig), axGetError(pg_sig));
		exit(1);
	}

    /* 
	 * sign it and generate other XML sections
	 */
	if (!xsSign(
		certData,	// certificate with public key, base64 encoded
		NULL,		// HMAC key, not used
 		pg_sig)) {
		printf ("Error: %d, %s\n",axGetLastError(pg_sig), axGetError(pg_sig));
		exit(1);
	} 
	/*  
	 * get result XML as string and save it
	 */
	xsignature = xsCoreGenerateXMLSec(pg_sig);
	if (xsignature == NULL) {
		printf ("Error: %d, %s\n",axGetLastError(pg_sig), axGetError(pg_sig));
		exit(1);
	}

 
	if ((hFile = fopen("signature.xml","w"))==NULL) {
		printf("can't open file");
		exit(1);
	}
 	fprintf(hFile,"%s",xsignature);
	fclose(hFile);

	
	/*
	 * verify it
	 */
	if (!axVerify(xsignature, 0, pg_sig)) {
		printf ("Error: %d, %s\n",axGetLastError(pg_sig), axGetError(pg_sig));		
	} else {
		printf ("Signature OK!\n");
	}
/*
 * Display signature and reference status
 */

sgArr = axGetSignature(&signum, pg_sig);	// array of all signatures found in the file

for (i=0;i<signum;i++) {
printf("Signature id=%s status=%d error=%d\n",sgArr[i]->sigId,sgArr[i]->status,sgArr[i]->lasterror);
/*
 * display signer certificate
 */

printf("Certificate Issuer= %s\n",sgArr[i]->signerCert->issuer);
printf("Certificate Subject= %s\n",sgArr[i]->signerCert->subject);
printf("Certificate SerialNumber= %s\n",sgArr[i]->signerCert->serialNumber);
printf("Certificate Not after= %s\n",sgArr[i]->signerCert->notAfter);

/*
 * display references
 */
refNum = sgArr[i]->refNumber;
refArr = sgArr[i]->refArray;
for (j=0;j<refNum;j++) {
	printf ("URI = %s , status = %d\n", refArr[j]->URI, refArr[j]->status);
	printf ("Reference encoding: %s\n",refArr[j]->refObject->encoding);
	printf ("Reference data: \n%s\n",refArr[j]->refObject->encodedData);
} 
}


	axFree(pg_sig);

	exit(0);
}


