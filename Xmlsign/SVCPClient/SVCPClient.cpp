// SVCPClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/* scvp_clt.c */
/* Written by Yann Busnel <Yann.Busnel@enst-bretagne.fr> */
/* for the RSM group of projects - July 2003 */
/* ================================================================ */

//#include <sys/param.h>
//#include <error.h>
#include <fcntl.h>
#include <stdio.h>
#include <io.h>
#include <string.h>
#include <time.h>
//#include <unistd.h>
//#include <curl/curl.h>
//#include <curl/types.h>
//#include <curl/easy.h>
extern "C" {
#include "openssl/err.h"
#include "openssl/rand.h"
#include "openssl/scvp.h"
}
#include <winhttp.h>
#include "TConvert.h"

#define NONCE_SIZE	4

#define errx(a, b, c) {printf(b, __FUNCTION__); exit(a);}
#define warnx		printf
#define bzero(a, b)		memset(a, b, 1);
#define MAXHOSTNAMELEN	1023

typedef struct MemoryStruct_st {
	char *memory;
	size_t size;
} MemoryStruct;

void errx0(int res, char *msg, void *param);
int scvp_cert_verify(X509 *cert, char *url);
int scvp_build_request(SCVP_REQUEST *req, X509 *cert);
int scvp_check_response(SCVP_RESPONSE *resp, SCVP_REQUEST *req, X509 *cert,
			unsigned char *sbuf, int len);
int scvp_cmp_request(SCVP_REQUEST *req, unsigned char *sbuf, int slen);
size_t WriteMemory_cb(void *ptr, size_t size, size_t nmemb, void *data);
//char ebuf[CURL_ERROR_SIZE];

MemoryStruct *makeHttpRequest(char *CVRequest, int reqLen, char *url)
{
  DWORD dwSize = 0;
  DWORD dwDownloaded = 0;
  LPSTR pszOutBuffer;
  BOOL  bResults = FALSE;
  HINTERNET  hSession = NULL, 
             hConnect = NULL,
             hRequest = NULL;
  DWORD dwStatusCode = 0;
  MemoryStruct *chunk = NULL;
  URL_COMPONENTS urlComp;
  DWORD dwUrlLen = 0;

  if (!CVRequest || !url) return NULL;
  
  _towchar wUrl(url);

      // Initialize the URL_COMPONENTS structure.
  ZeroMemory(&urlComp, sizeof(urlComp));
  urlComp.dwStructSize = sizeof(urlComp);

  // Set required component lengths to non-zero so that they are cracked.
  urlComp.dwSchemeLength    = -1;
  urlComp.dwHostNameLength  = -1;
  urlComp.dwUrlPathLength   = -1;
  urlComp.dwExtraInfoLength = -1;

  // Crack the URL.
  if (!WinHttpCrackUrl( wUrl, wcslen(wUrl), 0, &urlComp))
  {
      printf("Error %u in WinHttpCrackUrl.\n", GetLastError());
      return NULL;
  }


  // Use WinHttpOpen to obtain a session handle.
  hSession = WinHttpOpen( L"Infomosaic SCVP Client",  
                          WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                          WINHTTP_NO_PROXY_NAME, 
                          WINHTTP_NO_PROXY_BYPASS, 0 );

  // Specify an HTTP server from
  // urlComp.dwHostNameLength
  // urlComp.lpszHostName
  dwSize = 256;
  LPWSTR wOutBuffer = new WCHAR[dwSize+1];  
  ZeroMemory(wOutBuffer, dwSize);
  memcpy((void *)wOutBuffer,(void *)urlComp.lpszHostName, urlComp.dwHostNameLength*2);
  
  if( hSession )
	  hConnect = WinHttpConnect( hSession,  wOutBuffer,
								urlComp.nPort, 0 );

  delete [] wOutBuffer;
  // Create an HTTP request handle.
  if( hConnect )
	  hRequest = WinHttpOpenRequest( hConnect, L"POST", urlComp.lpszUrlPath,
                                   NULL, WINHTTP_NO_REFERER, 
                                   WINHTTP_DEFAULT_ACCEPT_TYPES, 
                                   0 );

  // Add a request header.
  if( hRequest )
    bResults = WinHttpAddRequestHeaders( hRequest, 
                 L"Content-Type: application/scvp-request\r\n",
                                         -1,
                                         WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE );

    if( hRequest )
    bResults = WinHttpAddRequestHeaders( hRequest, 
                 L"Accept: application/scvp-response\r\n",
                                         -1,
                                         WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE );

  // Send a request.
  if( hRequest )
    bResults = WinHttpSendRequest( hRequest,
                                   WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                                   CVRequest, reqLen, 
                                   reqLen, 0 );


  // End the request.
  if( bResults )
    bResults = WinHttpReceiveResponse( hRequest, NULL );

  // Use WinHttpQueryHeaders to obtain the header buffer.
  dwSize = 256;
  wOutBuffer = new WCHAR[dwSize / sizeof(WCHAR)];

  if( bResults )
    bResults = WinHttpQueryHeaders( hRequest, 
									WINHTTP_QUERY_STATUS_CODE ,
                                    NULL, 
                                    wOutBuffer,
                                    &dwSize,
                                    WINHTTP_NO_HEADER_INDEX );
  if (bResults) 
  {
	_tochar tc(wOutBuffer, TRUE);
	dwStatusCode = atoi((LPSTR)tc);
	delete [] wOutBuffer;
  }

  // get content-type header
  if( dwStatusCode == 200)
  {
		dwSize =0;
		WinHttpQueryHeaders( hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF,
                             WINHTTP_HEADER_NAME_BY_INDEX, NULL, &dwSize,
                             WINHTTP_NO_HEADER_INDEX);
	
        // Allocate memory for the buffer.
        wOutBuffer = new WCHAR[dwSize/sizeof(WCHAR)];

        // Use HttpQueryInfo to obtain the header Content-Type.
        bResults = WinHttpQueryHeaders( hRequest, 
                                        WINHTTP_QUERY_CONTENT_TYPE,
                                        WINHTTP_HEADER_NAME_BY_INDEX, 
                                        wOutBuffer, &dwSize, 
                                        WINHTTP_NO_HEADER_INDEX);
	    if (!bResults) goto lend;

		_tochar tc(wOutBuffer, TRUE);
		// Must be specific type
		if (strncmp((LPSTR)tc,"application/scvp-response",strlen("application/scvp-response"))!=0){
			goto lend;
		}

	// Keep checking for data until there is nothing left.
	do 
		{
		// Check for available data.
		dwSize = 0;
		if( !WinHttpQueryDataAvailable( hRequest, &dwSize ) )
				break;

		if (dwSize==0) break;
		// Allocate space for the buffer.
		pszOutBuffer = new char[dwSize+1];
		if( !pszOutBuffer )
		{
			dwSize=0;
		}
		else
		{
			// Read the data.
			ZeroMemory( pszOutBuffer, dwSize+1 );

			if( !WinHttpReadData( hRequest, (LPVOID)pszOutBuffer, 
				dwSize, &dwDownloaded ) ) {
					delete [] pszOutBuffer;
					break;
				}
	          

			if (dwDownloaded>0) {
				if (!chunk) {
					chunk = new MemoryStruct;
					ZeroMemory( chunk, sizeof(MemoryStruct) );
				}
				if (chunk->size>0) {
					char *oldMem = (char *) malloc(chunk->size);
					memcpy((void *)oldMem, (void *) chunk->memory, chunk->size);
					chunk->memory = (char *)realloc(chunk->memory, chunk->size + dwDownloaded);
					memcpy((void *)chunk->memory, (void *)oldMem, chunk->size);
					memcpy((void *)(chunk->memory + chunk->size), (void *)pszOutBuffer, dwDownloaded);
				}else{
					chunk->memory = (char *)malloc(dwDownloaded);
					memcpy((void *)chunk->memory, (void *)pszOutBuffer, dwDownloaded);
				}					
			}

			delete [] pszOutBuffer;
		}
	} while( dwSize > 0 );
  } // if status == 200

lend:
  // Close any open handles.
  if( hRequest ) WinHttpCloseHandle( hRequest );
  if( hConnect ) WinHttpCloseHandle( hConnect );
  if( hSession ) WinHttpCloseHandle( hSession );
  return chunk;
}

int
scvp_cert_verify(X509 *cert, char *url)
{
	SCVP_REQUEST *CVRequest = NULL;
	SCVP_RESPONSE *CVResponse = NULL;
//	CURL *curl = NULL;
	MemoryStruct *chunk = NULL;
	unsigned char *p, *sbuf = NULL;
	struct curl_slist *hlist = NULL;
	long httpcode;
	char *ct;
	int len, cr;

	CVRequest = SCVP_REQUEST_new();
	if (CVRequest == NULL)
		errx(1, "can't allocate request: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	if (scvp_build_request(CVRequest, cert) != 0)
		errx(1, "can't build request", NULL);
	len = i2d_SCVP_REQUEST(CVRequest, NULL);
	if (len <= 0)
		errx(1, "request encoding failed (get length): %s",
		     ERR_error_string(ERR_get_error(), NULL));
	sbuf = (unsigned char *) malloc(len + 1);
	if (sbuf == NULL)
		errx(1, "send buffer allocation failed: %s", strerror(errno));
	bzero(sbuf, len + 1);
	p = sbuf;
	if (i2d_SCVP_REQUEST(CVRequest, &p) <= 0)
		errx(1, "request encoding failed (real encoding): %s",
		     ERR_error_string(ERR_get_error(), NULL));
	chunk = (MemoryStruct *) malloc(sizeof(MemoryStruct));
	if (chunk == NULL)
		errx(1, "can't allocate receive memory: %s", strerror(errno));
	bzero(chunk, sizeof(MemoryStruct));

	/* debug */
	{
		int fd = open("req", O_WRONLY|O_CREAT|O_TRUNC, 0644);

		(void) write(fd, (char *) sbuf, len);
		(void) close(fd);
	}

	chunk = makeHttpRequest((char *) sbuf, len, url);
	if (!chunk) {
		// request failed
		errx(1, "HTTP Request Failed: %s", strerror(errno));
	}

	//curl = curl_easy_init();
	//if (curl == NULL)
	//	errx(1, "curl init failed");
	//if (curl_easy_setopt(curl, CURLOPT_URL, url) != CURLE_OK)
	//	errx(1, "curl setopt failed (URL)", NULL);
	//if (curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
	//		     (char *) sbuf) != CURLE_OK)
	//	errx(1, "curl setopt failed (POST)", NULL);
	//if (curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, len) != CURLE_OK)
	//	errx(1, "curl setopt failed (SIZE)", NULL);
	//hlist = curl_slist_append(hlist,
	//			  "Content-Type: application/scvp-request");
	//if (hlist == NULL)
	//	errx(1, "curl header append failed (CT)", NULL);
	//hlist = curl_slist_append(hlist,
	//			  "Accept: application/scvp-response");
	//if (hlist == NULL)
	//	errx(1, "curl header append failed (A)", NULL);
	//if (curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hlist) != CURLE_OK)
	//	errx(1, "curl setopt failed (HEADER)", NULL);
	//if (curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
	//		     &WriteMemory_cb) != CURLE_OK)
	//	errx(1, "curl setopt failed (WRITECB)", NULL);
	//if (curl_easy_setopt(curl, CURLOPT_FILE, (void *) chunk) != CURLE_OK)
	//	errx(1, "curl setopt failed (WRITE)", NULL);
	//if (curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, ebuf) != CURLE_OK)
	//	errx(1, "curl setopt failed (ERROR)", NULL);
	//if (curl_easy_perform(curl) != CURLE_OK)
	//	errx(1, "curl perform failed: %s", ebuf);
	//httpcode = 0;
	//if (curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &httpcode) != CURLE_OK)
	//	errx(1, "curl getinfo failed (HTTPCODE)", NULL);
	//if (httpcode != 200L)
	//	errx(1, "HTTP error (status = %ld)", httpcode);
	//ct = NULL;
	//if (curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct) != CURLE_OK)
	//	errx(1, "curl getinfo failed (CONTENTTYPE)", NULL);
	//if (ct == NULL)
	//	warnx("can't get Content-Type");
	//else if (strcmp(ct, "application/scvp-response") != 0)
	//	errx(1, "bad Content-Type %s", ct);

	//ERR_clear_error();
	p = (unsigned char *) chunk->memory;
	CVResponse = d2i_SCVP_RESPONSE(NULL, &p, chunk->size);
	if (CVResponse == NULL) {
		printf("Returned response: %s\n", chunk->memory);
		errx(1, "response decoding failed: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	}
	cr = scvp_check_response(CVResponse, CVRequest, cert, sbuf, len);

	if (CVRequest)
		SCVP_REQUEST_free(CVRequest);
	if (CVResponse)
		SCVP_RESPONSE_free(CVResponse);
	if (sbuf)
		free(sbuf);
	//if (curl)
	//	curl_global_cleanup();
	//if (hlist)
	//	curl_slist_free_all(hlist);
	if (chunk && chunk->memory)
		free(chunk->memory);
	if (chunk)
		free(chunk);
	ERR_clear_error();

	return cr;
}

int
scvp_build_request(SCVP_REQUEST *req, X509 *cert)
{
	SCVP_CERTREF *certRef;
	ASN1_OBJECT *obj;
	SCVP_PKCREF *pkc;
	char *hostname;
	unsigned char nonce[NONCE_SIZE];

	if ((req->scvpVersion == NULL) ||
	    (req->query == NULL))
		errx(1, "build request: allocation failed (global)", NULL);
	if (!ASN1_INTEGER_set(req->scvpVersion, 1L))
		errx(1, "build request: can't set version: %s",
		     ERR_error_string(ERR_get_error(), NULL));

	/* Query */

	/* Query -> queryCerts */
	pkc = SCVP_PKCREF_new();
	certRef = SCVP_CERTREF_new();
	if ((req->query->queriedCerts == NULL) ||
	    (req->query->checks == NULL) ||
	    (req->query->wantBack == NULL) ||
	    (req->query->valPolicy == NULL) ||
	    (pkc == NULL) ||
	    (certRef == NULL))
		errx(1, "build request: allocation failed (query): %s",
		     ERR_error_string(ERR_get_error(), NULL));
	pkc->type = V_SCVP_PKCREF_CERT;
	pkc->value.cert = X509_dup(cert);
	if (pkc->value.cert == NULL)
		errx(1, "build request: allocation failed (cert): %s",
		     ERR_error_string(ERR_get_error(), NULL));
	certRef->type = V_SCVP_CERTREF_PKC;
	certRef->value.pkc = pkc;
	if (sk_SCVP_CERTREF_push(req->query->queriedCerts, certRef) <= 0)
		errx(1, "build request: allocation failed (certRef): %s",
		     ERR_error_string(ERR_get_error(), NULL));

	/* Query -> Checks */
	obj = OBJ_nid2obj(NID_id_stc_build_status_checked_pkc_path);
	if (obj == NULL)
		errx(1, "build request: can't get check OID: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	if (sk_ASN1_OBJECT_push(req->query->checks, obj) <= 0)
		errx(1, "build request: allocation failed (check): %s",
		     ERR_error_string(ERR_get_error(), NULL));

        /* Query -> WantBacks */
	obj = OBJ_nid2obj(NID_id_swb_pkc_cert_status);
	if (obj == NULL)
		errx(1, "build request: can't get wantback OID: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	if (sk_ASN1_OBJECT_push(req->query->wantBack, obj) <= 0)
		errx(1, "build request: allocation failed (wantback): %s",
		     ERR_error_string(ERR_get_error(), NULL));

	/* Query -> ValPolicy */
	obj = OBJ_nid2obj(NID_id_svp_defaultValPolicy);
	if (obj == NULL)
		errx(1, "build request: can't get policy OID: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	req->query->valPolicy->valPolicyId = obj;

	/* Requestor */
	req->requestor = ASN1_OCTET_STRING_new();
	if (req->requestor == NULL)
		errx(1, "build request: allocation failed (requestor): %s",
		     ERR_error_string(ERR_get_error(), NULL));
	hostname = (char *)malloc(MAXHOSTNAMELEN + 1);
	if (hostname == NULL)
		errx(1, "build request: allocation failed (hostname)", NULL);
	bzero(hostname, MAXHOSTNAMELEN + 1);

	unsigned long lpnSize=MAXHOSTNAMELEN;	
	
	if (GetComputerName(hostname,&lpnSize) < 0)
		errx(1, "build request: gethostname: %s", strerror(errno));
	if (!ASN1_OCTET_STRING_set(req->requestor,
				   (unsigned char *)hostname,
				   strlen(hostname)))
		errx(1, "build request: can't set requestor: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	
	/* RequestNonce */
	req->requestNonce = ASN1_OCTET_STRING_new();
	if (req->requestNonce == NULL)
		errx(1, "build request: allocation failed (requestNonce): %s",
		     ERR_error_string(ERR_get_error(), NULL));
	if (RAND_pseudo_bytes(nonce, NONCE_SIZE) <= 0)
		errx(1, "build request: can't get nonce: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	if (!ASN1_OCTET_STRING_set(req->requestNonce, nonce, NONCE_SIZE))
		errx(1, "build request: can't set nonce: %s",
		     ERR_error_string(ERR_get_error(), NULL));

	/* ReqExtensions */

	return 0;
}

int
scvp_check_response(SCVP_RESPONSE *resp, SCVP_REQUEST *req, X509 *cert,
		    unsigned char *sbuf, int slen)
{
	SCVP_CERTREPLY *crep;
	SCVP_HASHVALUE *hv;
	ASN1_OCTET_STRING *ostr;
	EVP_MD_CTX mdctx;
	unsigned char md_value[EVP_MAX_MD_SIZE];
	long nid, status;
	int md_len, i;

	/* scvpVersion */
	if ((resp->scvpVersion == NULL) ||
	    ASN1_INTEGER_cmp(resp->scvpVersion, req->scvpVersion))
		errx(1, "check response: bad version", NULL);

	/* producedAt */

	/* responseStatus */
	if ((resp->responseStatus == NULL) ||
	    (resp->responseStatus->statusCode == NULL))
		errx(1, "check response: bad status", NULL);
	status = ASN1_ENUMERATED_get(resp->responseStatus->statusCode);
	if (status != SCVP_STATUS_CODE_OKAY) {
		warnx("check response: status = %ld", status);
		return (int) -status * 1000000;
	}

	/* requestRef */
	if (resp->requestRef == NULL)
		errx(1, "check response: bad requestRef", NULL);
	switch (resp->requestRef->type) {
	case V_SCVP_REQUEST_REFERENCE_REQUESTHASH:
		hv = resp->requestRef->value.requestHash;
		if ((hv == NULL) ||
		    (hv->algorithm == NULL) ||
		    (hv->algorithm->algorithm == NULL) ||
		    (hv->value == NULL))
			errx(1, "check response: no hash in requestRef", NULL);
		nid = OBJ_obj2nid(hv->algorithm->algorithm);
		if (nid != NID_sha1)
			errx(1, "check response: not a sha-1 hash", NULL);
		ostr = hv->value;
		EVP_MD_CTX_init(&mdctx);
		EVP_DigestInit_ex(&mdctx, EVP_sha1(), NULL);
		EVP_DigestUpdate(&mdctx, sbuf, slen);
		EVP_DigestFinal_ex(&mdctx, md_value, (unsigned int *)&md_len);
		EVP_MD_CTX_cleanup(&mdctx);
		if ((md_len != ostr->length) ||
		    memcmp((const void *)md_value, (const void *)ostr->data, md_len)) {
			warnx("check response: hash mismatch");
			return -1;
		}
		break;

	case V_SCVP_REQUEST_REFERENCE_FULLREQUEST:
		if (resp->requestRef->value.fullRequest == NULL)
			errx(1, "check response: void requestRef", NULL);
		if (scvp_cmp_request(resp->requestRef->value.fullRequest,
				     sbuf, slen)) {
			warnx("check response: requestRef mismatch");
			return -1;
		}
		break;

	default:
		errx(1, "check response: unknown requestRef", NULL);
	}

	/* requestor */
	if (resp->requestor == NULL)
		errx(1, "check response: no requestor", NULL);
	if (ASN1_OCTET_STRING_cmp(resp->requestor, req->requestor))
		errx(1, "check response: requestor mismatch", NULL);

	/* responder */

	/* requestNonce */
	if (resp->requestNonce == NULL)
		errx(1, "check response: no requestNonce", NULL);
	if (ASN1_OCTET_STRING_cmp(resp->requestNonce, req->requestNonce))
		errx(1, "check response: requestNonce mismatch", NULL);

	/* replyObjects */
	if ((resp->replyObjects == NULL) ||
	    (sk_SCVP_CERTREPLY_num(resp->replyObjects) != 1))
		errx(1, "check response: bad replyObjects", NULL);
	crep = sk_SCVP_CERTREPLY_value(resp->replyObjects, 0);
	if (crep == NULL)
		errx(1, "check response: bad CertReply", NULL);

	/* CertReply -> cert */
	if ((crep->cert == NULL) ||
	    (crep->cert->type != V_SCVP_CERTREF_PKC) ||
	    (crep->cert->value.pkc == NULL) ||
	    (crep->cert->value.pkc->type != V_SCVP_PKCREF_CERT) ||
	    (crep->cert->value.pkc->value.cert == NULL) ||
	    X509_cmp(crep->cert->value.pkc->value.cert, cert))
		errx(1, "check reply: bad cert", NULL);

	/* CertReply -> replyStatus */
	if (crep->replyStatus == NULL)
		errx(1, "check reply: bad status", NULL);
	status = ASN1_ENUMERATED_get(crep->replyStatus);
	if (status != SCVP_REPLY_STATUS_SUCCESS) {
		warnx("check reply: status = %ld", status);
		return (int) -status * 1000;
	}

	/* CertReply -> replyValTime */
	if (crep->replyValTime == NULL)
		errx(1, "check reply: bad valtime", NULL);
	/* should do more checks */

	/* CertReply -> replyChecks */
	if (crep->replyChecks == NULL)
		errx(1, "check reply: no checks", NULL);
	for (i = 0; i < sk_SCVP_REPLYCHECK_num(crep->replyChecks); i++) {
		SCVP_REPLYCHECK *rcheck;

		rcheck = sk_SCVP_REPLYCHECK_value(crep->replyChecks, i);
		if ((rcheck == NULL) ||
		    (rcheck->check == NULL) ||
		    (rcheck->status == NULL)) {
			warnx("check reply: empty check %d", i);
			continue;
		}
		nid = OBJ_obj2nid(rcheck->check);
		if (nid != NID_id_stc_build_status_checked_pkc_path)
			warnx("check reply: bad check OID");
		status = ASN1_INTEGER_get(rcheck->status);
		if (status != 0L) {
			warnx("check reply: bad status %ld in check %d",
			      status, i);
			return (int) -status * 10;
		}
	}

	/* CertReply -> replyWantBacks */
	if (crep->replyWantBacks == NULL)
		errx(1, "check reply: bad wantbacks", NULL);
	for (i = 0; i < sk_SCVP_REPLYWANTBACK_num(crep->replyWantBacks); i++) {
		SCVP_REPLYWANTBACK *rwback;
		unsigned char *p;

		rwback = sk_SCVP_REPLYWANTBACK_value(crep->replyWantBacks, i);
		if ((rwback == NULL) ||
		    (rwback->wb == NULL) ||
		    (rwback->value == NULL)) {
			warnx("check reply: empty wantback %d", i);
			continue;
		}
		nid = OBJ_obj2nid(rwback->wb);
		if (nid != NID_id_swb_pkc_cert_status) {
			warnx("check reply: bad wantback OID");
			continue;
		}
		p = rwback->value->data;
		rwback->d.status =
			d2i_ASN1_BOOLEAN(NULL, &p, rwback->value->length);
		if (rwback->d.status < 0)
			errx(1, "check reply: can't get wantback value", NULL);
		if (rwback->d.status == 0) {
			warnx("check reply: wantback said cert is not valid");
			return -1;
		}
	}

	/* CertReply -> valPolicy */
	if ((crep->valPolicy == NULL) ||
	    (crep->valPolicy->valPolicyId == NULL))
		errx(1, "check reply: bad valPolicy", NULL);
	nid = OBJ_obj2nid(crep->valPolicy->valPolicyId);
	if (nid != NID_id_svp_defaultValPolicy)
		warnx("check response: bad policy OID");

	/* serverContextInfo */

	/* respExtensions */

	return 0;
}

int
scvp_cmp_request(SCVP_REQUEST *req, unsigned char *sbuf, int slen)
{
	unsigned char *buf, *p;
	int len, ret;

	len = i2d_SCVP_REQUEST(req, NULL);
	if (len <= 0) {
		warnx("cmp request: %s",
		      ERR_error_string(ERR_get_error(), NULL));
		return -1;
	}
	if (len != slen)
		return len - slen;
	buf = (unsigned char *) malloc(len + 1);
	if (buf == NULL)
		return -1;
	p = buf;
	if (i2d_SCVP_REQUEST(req, &p) <= 0) {
		warnx("cmp request: %s",
		      ERR_error_string(ERR_get_error(), NULL));
		free(buf);
		return -1;
	}
	ret = memcmp((const void *)buf, (const void *)sbuf, len);
	free(buf);
	return ret;
}

size_t
WriteMemory_cb(void *ptr, size_t size, size_t nmemb, void *data)
{
	register int realsize = size * nmemb;
	MemoryStruct *mem = (MemoryStruct *) data;
	
	mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy((void *)ptr, (const void *)&(mem->memory[mem->size]), realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	} else
		errx(1, "realloc failed: %s", strerror(errno));
	return realsize;
}

int main(int argc, _TCHAR* *argv[])
{
	BIO *in = NULL;
	X509 *cert = NULL;
	int cr;

	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();

	if (argc != 3)
		errx(1, "usage: %s certfile URL", argv[0]);
	in = BIO_new_file((const char *)argv[1], "r");
	if (in == NULL)
		errx(1, "can't open %s:", argv[1]);
	cert = d2i_X509_bio(in, NULL);
	if (cert == NULL)
		errx(1, "can't decode cert: %s",
		     ERR_error_string(ERR_get_error(), NULL));
	cr = scvp_cert_verify(cert, (char *)argv[2]);
	printf("cr = %d\n", cr);

	if (in)
		BIO_free_all(in);
	if (cert)
		X509_free(cert);
	EVP_cleanup();
	ERR_free_strings();
	exit(0);
	return 0;
}

void errx0(int res, char *msg, void *param) {
	printf(msg,param);
	exit(res);
}