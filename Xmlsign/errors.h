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
#define CRYPT_API_ERROR			20		// CryptAPI error
#define DEREF_URI_ERROR			21		// Dereference for URI failed
#define DIGEST_ERROR			22		// digest validation or calculation failed
#define KEY_IMPORT_ERROR		23		// Key import failed
#define SIGN_FAILED				24		// Sign procedure failed
#define CERT_GET_PK_ERROR		25		// Get PK from certificate failed
#define NO_XML_OBJECT			26		// No object #OBJECT in XML
#define FILE_NOT_FOUND			27		// File not found
#define CERT_NOT_FOUND			28			// Certificate not found by ID
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