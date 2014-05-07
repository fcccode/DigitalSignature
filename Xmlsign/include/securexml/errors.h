
#ifndef __ERRORS_H__
#define __ERRORS_H__

/**
 * CERT_CHAIN_ERROR
 *
 * Certificate chain is not valid
 *
 */
#define CERT_CHAIN_ERROR		1
/**
 * BASE64_ERROR
 *
 * Base64 error
 *
 */
#define BASE64_ERROR			2
#define C14_ERROR				3		// Canonicalization error
#define PRIVATEKEY_ERROR		4		// Cannot acquire private key
#define XMLSIGLIB_ERROR			5		// XML Signature library error
#define INVALID_SIGMETHOD		6		// Cannot detect signature method
#define MEMORY_FAULT			7		// Memory fault (malloc)
#define INVALID_SIG_ALG			8		// Unsupported signature algorithm
#define INVALID_PROVIDER		9		// Unsupported provider
#define INVALID_TRANSFORM		10		// Unsupported transformation
#define INVALID_DIGEST_METHOD	11		// Wrong algorithm for digest method
#define IO_ERROR				12		// IO error
#define NO_CERTIFICATE			13		// no certificate provided
#define INVALID_XML_SIGNATURE	14		// Invalid XML structure of <Signature>
#define SIGNATURE_NTE_ERROR		15		// Signature validation failed: NTE errors
#define XML_PARSER_ERROR		16		// XML parser error
#define TRANSFORM_ERROR			17		// transformation error
#define I2O_ERROR			 	18		// Integer to Big-endian convertion failed
#define NO_CERT_STORE			19		// No specified store found for the current user
#define CAPI_CREATE_HASH		20		// CryptAPI error: Create Hash Failed
#define DEREF_URI_ERROR			21		// Dereference for URI failed
#define DIGEST_ERROR			22		// digest validation or calculation failed
#define KEY_IMPORT_ERROR		23		// Key import failed
#define SIGN_FAILED				24		// Sign procedure failed
#define CERT_GET_PK_ERROR		25		// Get PK from certificate failed
#define NO_XML_OBJECT			26		// No object #OBJECT in XML
#define FILE_NOT_FOUND			27		// File not found
#define CERT_NOT_FOUND			28		// Certificate not found by ID
#define NEWKEYSET_ERROR			29		// CryptAcquireContext with new keyset failed
#define CERT_GET_DETAILS_ERROR  30		// Get issuer/subject from certificate failed
#define PUBLIC_KEY_NOT_MATCH	31		// public key from certificate is not the same as in XML
#define INVALID_XML				32		// given XML file is invalid
#define XML_ERROR				33		// XML/Xpath processor failed
#define PK_SIZE_TOO_BIG			34		// Must increase MAX_MODULUS_SIZE in cr.h
#define DECODE_ERROR			35		// BASE64 little-endian -> BYTE *big-endian decode failed
#define XPOINTER_NOT_IMPLEMENTED 36		// Xpointer not implemented
#define XPATH_ERROR				37		// XPath error
#define RELATIVE_NS_FOUND       38		// c14n error: found relative namespace
#define XML_DOC_INIT_ERROR      39		// must free pXmlDoc before call xsCoreInitXmlDocument()
#define HTTP_ERROR				40		// URI cannot be fetched
#define GENERATE_KEY_ERROR		41		// Generate RC2 key for HMAC failed
#define HMAC_KEY_SIZE_TOO_SMALL 42		// Generate RC2 key for HMAC failed because of key length (password is too big for default key)
#define NO_KEY					43		// Unable to verify - no key or certificate found
#define NO_VERIFICATION_LIC		44		// Signature verification license for SecureXML not found
#define NO_SIGNING_LIC			45		// Signature creation license for SecureXML not found
#define NO_SECUREXML_LIC		46		// License for SecureXML not found
#define INVALID_SECUREXML_LIC	47		// License for SecureXML is not valid
#define DLL_NOT_REGISTERED		48		// SecureXML dll not registered
#define NO_SIGNATURE_DATA		49		// There is no signature verification data available
#define SIG_INDEX_ERROR			50		// Signature Index >= SignatureCount
#define PROP_INDEX_ERROR		51		// Property Index >= PropertyCount for the given Signature Index
#define URI_INDEX_ERROR			52		// URI Index >= UriCount or FailedUriCount for the given signature index
#define CERT_INDEX_ERROR		53		// Certificate Index >= Certificate Count
#define CERT_VAL_INDEX_ERROR	54		// Certificate Value Index can only be 1,2,3 or 4
#define DOC_PATH_NOT_FOUND		55		// No SignedDocumentPath info exists for the given sig/uri index
#define SIG_NOT_FOUND			56		// No signature with the matching signature Id was found
#define PFX_BAD_PASSWORD		57		// Invalid password provided for PFX file
#define PFX_IMPORT_FAILED		58		// Import failed for PFX certificate
#define PFX_INVALID_CERTIFICATE 59		// No private key found found in PFX certificate or other validation error
#define PFX_EXPORT_FAILED		60		// Export failed for PFX certificate
#define CERT_TRUST_ERROR		61		// Certificate trust/CRL check failed
#define FILE_PATH_TOO_LONG		62		// The file path is >= MAX_PATH
#define FILE_PATH_NOT_SET		63		// The file path hasn't been set yet
#define LICENSE_EXPIRED			64		// The license has expired
#define INVALID_CSP				65		// The given CSP value was invalid
#define NO_SECUREXML_CONFIG		66		// Config file for SecureXML not found
#define NO_HMAC_PASSWORD		67		// No Hmac password was provided & no physical signature used
#define NULL_DATA_STRING		68		// The data string provided is of zero length
#define DUPLICATE_SIG_ID		69		// There is already a signature with matching signature Id present
#define INVALID_SDATA_NS		70		// There is no XML element SignedObject in the infomosaic name space
#define INVALID_VARIANT			71		// The Variant contains unsupported data type
#define CRL_BAD_SIGNATURE		72		// CRL has invalid signature
#define CRL_ERROR				73		// generic error on CRL validation
#define CRL_NOT_FOUND			74		// no CRL related data found for the certificate/chain
#define CRL_CERT_REVOKED		75		// certificate revoked according to CRL

#define CERT_TIME_INVALID       76		// At least one of the certificates in the chain has invalid time
#define CERT_TIME_NOT_NESTED    77		// The time nesting of the certificate chain is invalid
#define CERT_SIGNATURE_INVALID  78		// At least one of the certificates in the chain has invalid signature
#define CERT_INVALID_USAGE      79
#define CERT_PARTIAL_CHAIN		80
#define CERT_UNTRUSTED_ROOT     81
#define CERT_TRUST_CYCLIC       82

#define CERT_INVALID_CHAIN		83		// Issuer name <> Subject name of issuer certificate


#define BASIC_CONSTRAINT_ERR	84		// Either the intermediate certificate does not
										// have a basicConstraints extension or it is
										// not marked critical or the cA is set to false

#define CERT_KEY_USAGE_ERR		85		// If the application encounters an intermediate certificate in the
										// certificate path that has the key usage extension present with the
										// keyCertSign bit set to true and the basic constraints extension
										// present, the application must ensure that the certificate has the cA
										// component of the basic constraints extension set to TRUE.

#define CERT_POLICY_ERROR		86		// Certificate policy validation failed
#define CRL_TOO_OLD				87		// The nextUpdate time is earlier than current time
#define INVALID_ENC_ALG			88		// Unsupported encryption algorithm
#define DECRYPTION_FAILED		89		// Probably wrong certificate used for decryption
#define CERT_PATHLEN_ERR		90		// There is a violation of the path length constraint in the certificate chain
#define NO_ENCRYPT_LIC			91		// The license to create encrypted documents not present
#define NO_DECRYPT_LIC			92		// The license to decrypt encrypted documents not present
#define CAM_CERT_REVOKED		93		// Certificate is revoked as reported by the CAM server
#define CAM_CERT_EXPIRED		94		// Certificate is expired as reported by the CAM server
#define CAM_CERT_SUSPENDED		95		// Certificate is suspended as reported by the CAM server
#define CAM_CERT_FAILED_VERIFICATION 96 // Certificate failed verification for some reason as reported by the CAM server
#define CAM_CERT_ISSUER_NOT_FOUND	97	// Certificate issuer not found as reported by the CAM server
#define CAM_CERT_NOT_PARSABLE		98	// Certificate is not parsable as reported by the CAM server
#define CAM_CA_SYSTEM_BUSY		99		// CA is too busy to respond as reported by the CAM server
#define CAM_CA_TIMEOUT			100		// CA timed out during certification validation as reported by the CAM server
#define CAM_CA_CERT_UNKNOWN		101		// CA claims they did not issue this cert as reported by the CAM server
#define CAM_CA_REQ_BAD			102		// comm or protocol problem between CAM and CA as reported by the CAM server
#define CAM_CA_BAD_RESP_SIG		103		// invalid signature on CA response as reported by the CAM server
#define CAM_INTERNAL_ERROR		104		// CAM internal error
#define CAPI_SET_HASH_PARAM		105		// CryptAPI error: Set Hash Param Failed
#define CAPI_HASH_DATA			106		// CryptAPI error: CryptHashData Failed
#define CAPI_GET_HASH_PARAM		107		// CryptAPI error: CryptGetHashParam Failed
#define CAPI_CREATE_CERT_CNTX	108		// CryptAPI error: CertCreateCertificateContext Failed
#define CAPI_GET_USER_KEY		109		// CryptAPI error: CryptGetUserKey Failed
#define CAPI_EXPORT_KEY			110		// CryptAPI error: CryptExportKey Failed
#define CAPI_SIGN_HASH			111		// CryptAPI error: CryptSignHash Failed
#define CAPI_OPEN_STORE			112		// CryptAPI error: CertOpenStore Failed
#define CAPI_ADD_CERT			113		// CryptAPI error: CertAddEncodedCertificateToStore Failed
#define CAPI_GET_CERT_CHAIN		114		// CryptAPI error: CertGetCertificateChain Failed
#define CAPI_DECODE_OBJ			115		// CryptAPI error: CryptDecodeObject Failed
#define CAPI_GET_CERT_CNTX_PROP	116		// CryptAPI error: CertGetCertificateContextProperty Failed
#define CAPI_ADD_CERT_CNTX		117		// CryptAPI error: CertAddCertificateContextToStore Failed
#define CRSIGN_FAILED			118		// crSign Failed
#define CAPI_ACQUIRE_CNTX		119		// CryptAcquireContext Failed
#define CAPI_DECRYPT_MSG		120		// CryptDecryptMessage Failed
#define CAPI_ENCRYPT_MSG		121		// CryptEncryptMessage Failed
#define ADO_ERROR				122		// Problem accessing database
#define OCSP_ERROR				123		// Generic OCSP Error
#define OCSP_CERT_UNKNOWN		124		// Certificate issuer is not known to the OCSP responder
#define OCSP_CERT_REVOKED		125		// Certificate is revoked as per OCSP response
#define	OCSP_CA_UNTRUSTED		126		// The OCSP Response is not signed by a trusted authority
#define NSS_NOT_SUPPORTED		127		// This call currently is not supported for NSS API
#define TIME_STAMP_FAILED		128		// Could not obtain time stamp from the time stamp server

#endif		// __ERRORS_H__

