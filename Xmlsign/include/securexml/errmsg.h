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

#ifndef __ERRMSG_H__
#define __ERRMSG_H__

#pragma once
#if __cplusplus
extern "C" {
#endif

unsigned char *errorMsgTable[] = {				(unsigned char *)" ",
/*#define CERT_CHAIN_ERROR		1	*/			(unsigned char *)"Certificate Chain Error",
/*#define BASE64_ERROR			2	*/			(unsigned char *)"Base 64 Error",
/*#define C14_ERROR				3	*/			(unsigned char *)"Canonicalization error",
/*#define PRIVATEKEY_ERROR		4	*/			(unsigned char *)"Cannot acquire private key",
/*#define XMLSIGLIB_ERROR		5	*/			(unsigned char *)"XML Signature library error",
/*#define INVALID_SIGMETHOD		6	*/			(unsigned char *)"Cannot detect signature method",
/*#define MEMORY_FAULT			7	*/			(unsigned char *)"Memory fault (malloc)",
/*#define INVALID_SIG_ALG		8	*/			(unsigned char *)"Unsupported signature algorithm",
/*#define INVALID_PROVIDER		9	*/			(unsigned char *)"Unsupported provider",
/*#define INVALID_TRANSFORM		10	*/			(unsigned char *)"Unsupported transformation",
/*#define INVALID_DIGEST_METHOD	11	*/			(unsigned char *)"Wrong algorithm for digest method",
/*#define IO_ERROR				12	*/			(unsigned char *)"IO error",
/*#define NO_CERTIFICATE		13	*/			(unsigned char *)"No certificate provided",
/*#define INVALID_XML_SIGNATURE	14	*/			(unsigned char *)"Invalid XML structure of <Signature>",
/*#define SIGNATURE_NTE_ERROR	15	*/			(unsigned char *)"Signature validation failed: NTE errors",
/*#define XML_PARSER_ERROR		16	*/			(unsigned char *)"XML parser error",
/*#define TRANSFORM_ERROR		17	*/			(unsigned char *)"Transformation error",
/*#define I2O_ERROR			 	18	*/			(unsigned char *)"Integer to Big-endian convertion failed",
/*#define NO_CERT_STORE			19	*/			(unsigned char *)"No specified store found for the current user",
/*#define CAPI_CREATE_HASH		20	*/			(unsigned char *)"CryptAPI error: Create Hash Failed",
/*#define DEREF_URI_ERROR		21	*/			(unsigned char *)"Dereference for URI failed",
/*#define DIGEST_ERROR			22	*/			(unsigned char *)"Digest validation or calculation failed",
/*#define KEY_IMPORT_ERROR		23	*/			(unsigned char *)"Key import failed",
/*#define SIGN_FAILED			24	*/			(unsigned char *)"Sign procedure failed",
/*#define CERT_GET_PK_ERROR		25	*/			(unsigned char *)"Get PK from certificate failed",
/*#define NO_XML_OBJECT				26		*/  (unsigned char *)"No object /*#OBJECT in XML",
/*#define FILE_NOT_FOUND			27		*/  (unsigned char *)"File not found",
/*#define CERT_NOT_FOUND			28		*/  (unsigned char *)"Certificate not found by ID",
/*#define NEWKEYSET_ERROR			29		*/  (unsigned char *)"CryptAcquireContext with new keyset failed",
/*#define CERT_GET_DETAILS_ERROR	30		*/  (unsigned char *)"Get issuer/subject from certificate failed",
/*#define PUBLIC_KEY_NOT_MATCH		31		*/  (unsigned char *)"public key from certificate is not the same as in XML",
/*#define INVALID_XML				32		*/  (unsigned char *)"given XML file is invalid",
/*#define XML_ERROR					33		*/  (unsigned char *)"XML/Xpath processor failed",
/*#define PK_SIZE_TOO_BIG			34		*/  (unsigned char *)"Must increase MAX_MODULUS_SIZE in cr.h",
/*#define DECODE_ERROR				35		*/  (unsigned char *)"BASE64 little-endian -> BYTE *big-endian decode failed",
/*#define XPOINTER_NOT_IMPLEMENTED	36		*/  (unsigned char *)"Xpointer not implemented",
/*#define XPATH_ERROR				37		*/  (unsigned char *)"XPath error",
/*#define RELATIVE_NS_FOUND			38		*/  (unsigned char *)"C14n error: found relative namespace",
/*#define XML_DOC_INIT_ERROR		39		*/  (unsigned char *)"Must free pXmlDoc before call xsCoreInitXmlDocument()",
/*#define HTTP_ERROR				40		*/  (unsigned char *)"URI cannot be fetched",
/*#define GENERATE_KEY_ERROR		41		*/  (unsigned char *)"Generate RC2 key for HMAC failed",
/*#define HMAC_KEY_SIZE_TOO_SMALL	42		*/  (unsigned char *)"Generate RC2 key for HMAC failed because of key length (password is too big for default key)",
/*#define NO_KEY					43		*/  (unsigned char *)"Unable to verify - no key or certificate found",
/*#define NO_VERIFICATION_LIC		44		*/  (unsigned char *)"Signature verification license for SecureXML not found",
/*#define NO_SIGNING_LIC			45		*/  (unsigned char *)"Signature creation license for SecureXML not found",
/*#define NO_SECUREXML_LIC			46		*/  (unsigned char *)"License for SecureXML not found",
/*#define INVALID_SECUREXML_LIC		47		*/  (unsigned char *)"License for SecureXML is not valid",
/*#define DLL_NOT_REGISTERED		48		*/  (unsigned char *)"SecureXML dll not registered",
/*#define NO_SIGNATURE_DATA			49		*/  (unsigned char *)"There is no signature verification data available",
/*#define SIG_INDEX_ERROR			50		*/  (unsigned char *)"Signature Index >= SignatureCount",
/*#define PROP_INDEX_ERROR			51		*/  (unsigned char *)"Property Index >= PropertyCount for the given Signature Index",
/*#define URI_INDEX_ERROR			52		*/  (unsigned char *)"URI Index >= UriCount or FailedUriCount for the given signature index",
/*#define CERT_INDEX_ERROR			53		*/  (unsigned char *)"Certificate Index >= Certificate Count",
/*#define CERT_VAL_INDEX_ERROR		54		*/  (unsigned char *)"Certificate Value Index can only be 1,2,3 or 4",
/*#define DOC_PATH_NOT_FOUND		55		*/  (unsigned char *)"No SignedDocumentPath info exists for the given sig/uri index",
/*#define SIG_NOT_FOUND				56		*/  (unsigned char *)"No signature with the matching signature Id was found",
/*#define PFX_BAD_PASSWORD			57		*/  (unsigned char *)"Invalid password provided for PFX file",
/*#define PFX_IMPORT_FAILED			58		*/  (unsigned char *)"Import failed for PFX certificate",
/*#define PFX_INVALID_CERTIFICATE	59		*/  (unsigned char *)"No private key found found in PFX certificate or other validation error",
/*#define PFX_EXPORT_FAILED			60		*/  (unsigned char *)"Export failed for PFX certificate",
/*#define CERT_TRUST_ERROR			61		*/  (unsigned char *)"Certificate trust/CRL check failed",
/*#define FILE_PATH_TOO_LONG		62		*/  (unsigned char *)"The file path is >= MAX_PATH",
/*#define FILE_PATH_NOT_SET			63		*/  (unsigned char *)"The file path hasn't been set yet",
/*#define LICENSE_EXPIRED			64		*/  (unsigned char *)"The license has expired",
/*#define INVALID_CSP				65		*/  (unsigned char *)"The given CSP value was invalid",
/*#define NO_SECUREXML_CONFIG		66		*/  (unsigned char *)"Config file for SecureXML not found",
/*#define NO_HMAC_PASSWORD			67		*/  (unsigned char *)"No Hmac password was provided & no physical signature used",
/*#define NULL_DATA_STRING			68		*/  (unsigned char *)"The data string provided is of zero length",
/*#define DUPLICATE_SIG_ID			69		*/  (unsigned char *)"There is already a signature with matching signature Id present",
/*#define INVALID_SDATA_NS			70		*/  (unsigned char *)"There is no XML element SignedObject in the infomosaic name space",
/*#define INVALID_VARIANT			71		*/  (unsigned char *)"The Variant contains unsupported data type",
/*#define CRL_BAD_SIGNATURE			72		*/  (unsigned char *)"CRL has invalid signature",
/*#define CRL_ERROR					73		*/  (unsigned char *)"Generic error on CRL validation",
/*#define CRL_NOT_FOUND				74		*/  (unsigned char *)"No CRL related data found for the certificate/chain",
/*#define CRL_CERT_REVOKED			75		*/  (unsigned char *)"Certificate revoked according to CRL",
/*#define CERT_TIME_INVALID			76		*/  (unsigned char *)"Certificate is expired or at least one of the certificates in the chain has invalid time",
/*#define CERT_TIME_NOT_NESTED		77		*/  (unsigned char *)"The time nesting of the certificate chain is invalid",
/*#define CERT_SIGNATURE_INVALID	78		*/  (unsigned char *)"At least one of the certificates in the chain has invalid signature",
/*#define CERT_INVALID_USAGE		79		*/	(unsigned char *)"Invalid certificate usage",
/*#define CERT_PARTIAL_CHAIN		80		*/  (unsigned char *)"Partial certificate chain",
/*#define CERT_UNTRUSTED_ROOT		81		*/	(unsigned char *)"Untrusted root certificate",
/*#define CERT_TRUST_CYCLIC			82		*/	(unsigned char *)"The trust is cyclical",
/*#define CERT_INVALID_CHAIN		83		*/  (unsigned char *)"Issuer name <> Subject name of issuer certificate",
/*#define BASIC_CONSTRAINT_ERR		84		*/  (unsigned char *)"Either the intermediate certificate does not have a basicConstraints extension or it is not marked critical or the cA is set to false",
/*#define CERT_KEY_USAGE_ERR		85		*/  (unsigned char *)"Certificate key usage error",
/*#define CERT_POLICY_ERROR			86		*/  (unsigned char *)"Certificate policy validation failed",
/*#define CRL_TOO_OLD				87		*/  (unsigned char *)"The nextUpdate time is earlier than current time",
/*#define INVALID_ENC_ALG			88		*/  (unsigned char *)"Unsupported encryption algorithm",
/*#define DECRYPTION_FAILED			89		*/  (unsigned char *)"Probably wrong certificate used for decryption",
/*#define CERT_PATHLEN_ERR			90		*/  (unsigned char *)"There is a violation of the path length constraint in the certificate chain",
/*#define NO_ENCRYPT_LIC			91		*/  (unsigned char *)"The license to create encrypted documents not present",
/*#define NO_DECRYPT_LIC			92		*/  (unsigned char *)"The license to decrypt encrypted documents not present",
/*#define CAM_CERT_REVOKED			93		*/  (unsigned char *)"Certificate is revoked as reported by the CAM server",
/*#define CAM_CERT_EXPIRED			94		*/  (unsigned char *)"Certificate is expired as reported by the CAM server",
/*#define CAM_CERT_SUSPENDED		95		*/  (unsigned char *)"Certificate is suspended as reported by the CAM server",
/*#define CAM_CERT_FAILED_VERIFICATION	96	*/  (unsigned char *)"Certificate failed verification for some reason as reported by the CAM server",
/*#define CAM_CERT_ISSUER_NOT_FOUND		97	*/  (unsigned char *)"Certificate issuer not found as reported by the CAM server",
/*#define CAM_CERT_NOT_PARSABLE			98	*/  (unsigned char *)"Certificate is not parsable as reported by the CAM server",
/*#define CAM_CA_SYSTEM_BUSY		99		*/  (unsigned char *)"CA is too busy to respond as reported by the CAM server",
/*#define CAM_CA_TIMEOUT			100		*/  (unsigned char *)"CA timed out during certification validation as reported by the CAM server",
/*#define CAM_CA_CERT_UNKNOWN		101		*/  (unsigned char *)"CA claims they did not issue this cert as reported by the CAM server",
/*#define CAM_CA_REQ_BAD			102		*/  (unsigned char *)"Comm or protocol problem between CAM and CA as reported by the CAM server",
/*#define CAM_CA_BAD_RESP_SIG		103		*/  (unsigned char *)"Invalid signature on CA response as reported by the CAM server",
/*#define CAM_INTERNAL_ERROR		104		*/  (unsigned char *)"CAM internal error",
/*#define CAPI_SET_HASH_PARAM		105		*/  (unsigned char *)"CryptAPI error: Set Hash Param Failed",
/*#define CAPI_HASH_DATA			106		*/  (unsigned char *)"CryptAPI error: CryptHashData Failed",
/*#define CAPI_GET_HASH_PARAM		107		*/  (unsigned char *)"CryptAPI error: CryptGetHashParam Failed",
/*#define CAPI_CREATE_CERT_CNTX		108		*/  (unsigned char *)"CryptAPI error: CertCreateCertificateContext Failed",
/*#define CAPI_GET_USER_KEY			109		*/  (unsigned char *)"CryptAPI error: CryptGetUserKey Failed",
/*#define CAPI_EXPORT_KEY			110		*/  (unsigned char *)"CryptAPI error: CryptExportKey Failed",
/*#define CAPI_SIGN_HASH			111		*/  (unsigned char *)"CryptAPI error: CryptSignHash Failed",
/*#define CAPI_OPEN_STORE			112		*/  (unsigned char *)"CryptAPI error: CertOpenStore Failed",
/*#define CAPI_ADD_CERT				113		*/  (unsigned char *)"CryptAPI error: CertAddEncodedCertificateToStore Failed",
/*#define CAPI_GET_CERT_CHAIN		114		*/  (unsigned char *)"CryptAPI error: CertGetCertificateChain Failed",
/*#define CAPI_DECODE_OBJ			115		*/  (unsigned char *)"CryptAPI error: CryptDecodeObject Failed",
/*#define CAPI_GET_CERT_CNTX_PROP	116		*/  (unsigned char *)"CryptAPI error: CertGetCertificateContextProperty Failed",
/*#define CAPI_ADD_CERT_CNTX		117		*/  (unsigned char *)"CryptAPI error: CertAddCertificateContextToStore Failed",
/*#define CRSIGN_FAILED				118		*/  (unsigned char *)"Internal method crSign Failed",
/*#define CAPI_ACQUIRE_CNTX			119		*/  (unsigned char *)"CryptAcquireContext Failed",
/*#define CAPI_DECRYPT_MSG			120		*/  (unsigned char *)"CryptDecryptMessage Failed",
/*#define CAPI_ENCRYPT_MSG			121		*/  (unsigned char *)"CryptEncryptMessage Failed",
/*#define ADO_ERROR					122		*/	(unsigned char *)"Problem accessing database",
/*#define OCSP_ERROR				123		*/  (unsigned char *)"Generic OCSP Error",
/*#define OCSP_CERT_UNKNOWN			124		*/	(unsigned char *)"Certificate issuer is not known to the OCSP responder",
/*#define OCSP_CERT_REVOKED			125		*/	(unsigned char *)"Certificate is revoked as per OCSP response",
/*#define OCSP_CA_UNTRUSTED			126		*/	(unsigned char *)"The OCSP Response is not signed by a trusted authority",
/*#define NSS_NOT_SUPPORTED			127		*/	(unsigned char *)"This call currently is not supported for NSS API",
/*#define TIME_STAMP_FAILED			128		*/  (unsigned char *)"Could not obtain time stamp from the time stamp server"
};
#if __cplusplus
}
#endif

#endif		// __ERRMSG_H__

