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

#ifndef __CORESIG_H__
#define __CORESIG_H__

#ifndef LIBXML_STATIC
#define LIBXML_STATIC
#endif


#ifdef WIN32
#include <windows.h>
#include <wincrypt.h>
#else
#include <stdio.h>
#include <wtypes.h>
#include <windef.h>
//#include <winbase.h>
//#include <winnls.h>
#include <winerror.h>
//#include <oleauto.h>
//#include <objbase.h>

#endif

//#ifdef LINUX
//#include <securexml/wincryptLinux.h>
//#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if __cplusplus
extern "C" {
#endif

#if defined(NSS)
#include <mozilla-all.h>
#endif

#include <securexml/parser.h>
/*
 *	External (global) variables, macros and structs
*/

#define MAXBUFFERSIZE 2048
#define MALLOCSIZE (1024 * 50)
#define MAX_CERT_COUNT 256

#define ENVELOPED	2
#define ENVELOPING	1
#define DETACHED	0

#define sigAlgDSA		1
#define sigAlgRSA		2
#define sigAlgHMAC		3

#define SECURE_XML_LOGO "XML Signature produced by Infomosaic SecureXML, http://www.infomosaic.net"

// return values
#define FALSE	0
#define TRUE	1

#define SIGNATURE_URI "http://www.w3.org/2000/09/xmldsig#"
#define NS_PREFIX "idsig"
#define SIG_LOOKUP "(//. | //@* | //namespace::*) [self::idsig:Signature]"
#define XPATH_ENVELOPED_EXPR "count(ancestor-or-self::idsig:Signature | here()/ancestor::idsig:Signature[1]) > count(ancestor-or-self::idsig:Signature)"

#define uriDSAKeyValue	"http//www.w3.org/2000/09/xmldsig#DSAKeyValue"
#define uriRSAKeyValue	"http//www.w3.org/2000/09/xmldsig#RSAKeyValue"
#define uriX509Data	"http://www.w3.org/2000/09/xmldsig#X509Data"
#define uriPGPData		"http://www.w3.org/2000/09/xmldsig#PGPData"
#define uriSPKIData	"http://www.w3.org/2000/09/xmldsig#SPKIData"
#define uriMgmtData	"http://www.w3.org/2000/09/xmldsig#MgmtData"
#define uriX509Raw	"http://www.w3.org/2000/09/xmldsig#rawX509Certificate"
#define uriRefTypeSignatureProperties "http://www.w3.org/2000/09/xmldsig#SignatureProperties"
#define uriXmlSignatureDTD "http://www.w3.org/TR/xmldsig-core/xmldsig-core-schema.dtd"
#define defaultTimeServiceUrl "http://time-b.timefreq.bldrdoc.gov:13"
//algorithm URIs

#define ALG_SHA1				"http://www.w3.org/2000/09/xmldsig#sha1"
#define ALG_BASE64				"http://www.w3.org/2000/09/xmldsig#base64"
#define ALG_HMACSHA1			"http://www.w3.org/2000/09/xmldsig#hmac-sha1"
#define ALG_DSAWITHSHA1			"http://www.w3.org/2000/09/xmldsig#dsa-sha1"
#define ALG_RSAWITHSHA1			"http://www.w3.org/2000/09/xmldsig#rsa-sha1"
#define ALG_CANON_XML_WITH_COMM	"http://www.w3.org/TR/2001/REC-xml-c14n-20010315#WithComments"
#define ALG_CANON_XML_NO_COMM	"http://www.w3.org/TR/2001/REC-xml-c14n-20010315"
#define ALG_CANON_XML_WITH_COMM1  "http://www.w3.org/TR/2000/CR-xml-c14n-20001026#WithComments"
#define ALG_CANON_XML_NO_COMM1	"http://www.w3.org/TR/2000/CR-xml-c14n-20001026"
#define ALG_CANON_XML_WITH_COMM2  "http://www.w3.org/TR/2000/WD-xml-c14n-20000907#WithComments"
#define ALG_CANON_XML_NO_COMM2	"http://www.w3.org/TR/2000/WD-xml-c14n-20000907"
#define ALG_XSLT				"http://www.w3.org/TR/1999/REC-xslt-19991116"
#define ALG_XPATH				"http://www.w3.org/TR/1999/REC-xpath-19991116"
#define ALG_ENVELOPED_SIG		"http://www.w3.org/2000/09/xmldsig#enveloped-signature"
#define ALG_ASN1_DER_X509_CERT	"http://www.w3.org/2000/09/xmldsig#rawX509Certificate"
#define ALG_ZERO_SPACE			"http://www.infomosaic.net/xmldsig#zero-space"

#define ALG_CANON_EXC_WITH_COMM   "http://www.w3.org/2001/10/xml-exc-c14n#WithComments"
#define ALG_CANON_EXC_NO_COMM   "http://www.w3.org/2001/10/xml-exc-c14n#"
#define CANON_EXC_WITH_COMM		33		// 0x0021
#define CANON_EXC_NO_COMM		65		// 0x0041

// which algorithms to use

#define IFM_SHA1				1		// 0x0001
#define BASE64					2		// 0x0002
#define HMACSHA1				4		// 0x0004
#define DSAWITHSHA1				8		// 0x0008
#define RSAWITHSHA1				16		// 0x0010
#define CANON_XML_WITH_COMM		32
#define CANON_XML_NO_COMM		64
#define TRANS_XSLT					128		// 0x0080
#define TRANS_XPATH					256		// 0x0100
#define TRANS_ENVELOPED_SIG			512		// 0x0200
#define ASN1_DER_X509_CERT		1024	// 0x0400
#define TRANS_ZERO_SPACE		2048	// 0x0800

// reference type
#define REF_OBJECT			1
#define REF_MANIFEST		2
#define REF_ENVELOPED		3
#define REF_DETACHED		4
#define REF_REFERENCE		5
#define REF_XPOINTER		6
#define REF_XPOINTER_BY_ID	7

// default properties

#define DEF_CANON_ALG				ALG_CANON_XML_NO_COMM
#define DEF_SIGNMETHOD_ALG			ALG_DSAWITHSHA1
#define DEF_DIGMETH_ALG				ALG_SHA1
#define DEF_TRANSF_ALG				ALG_ENVELOPED_SIG
#define DEF_SIGNATURE_URI			SIGNATURE_URI

#define OCTET_STREAM 1
#define XPATH_NODE_SET 2


/*
 **********************************************************************
 *						SignedInfo structs
 **********************************************************************
*/

/**
 * xpath
 *
 * Describes <XPath> element as child of <Transform>
 */

typedef struct _xpath xpath;
struct _xpath
{
	char param_ns_prefix[MAXBUFFERSIZE];	/* NS prefix */
	char param_ns_href[MAXBUFFERSIZE];		/* NS URL */
	unsigned char *data;					/* XPath expression */
	xmlNodePtr here;						/* node that bears XPath expression, for function here() */
	xpath *next;						/* next XPath */
};


/**
 * transform
 *
 * The <Transform> element
 */

typedef struct _transform st_transform;
struct _transform
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	char param_algorithm[MAXBUFFERSIZE];
	char param_uri[MAXBUFFERSIZE];
	unsigned char *data;		/* The current transform data */
	xpath *vxpath;			/* an xpath structure can be included */
	xmlNodePtr node;		/* pointer to the xml node */
	st_transform *next; /* pointer to next transform (this is a linked list) */
	unsigned char *prefixList; /* for Exclusive C14N namespace prefix list */
};

/**
 * transforms
 *
 * The Transforms element consists of a linked list of <Transform>
 */

typedef struct _transforms transforms;
struct _transforms
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	st_transform *vtransform;
};

/**
 * digestmethod
 *
 * <DigestMethod> element
 */

typedef struct _digestmethod digestmethod;
struct _digestmethod
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	char param_algorithm[MAXBUFFERSIZE];
	unsigned char *data;
};

/**
 * digestvalue
 *
 * <DigestValue> element
 */

typedef struct _digestvalue digestvalue;
struct _digestvalue
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	unsigned char *data;
};

/**
 * reference
 *
 * <Reference> element
 */

typedef struct _reference reference;
struct _reference
{
	char param_ns[MAXBUFFERSIZE];	/* not used */
	char param_id[MAXBUFFERSIZE];	/* Reference ID */
	char param_uri[MAXBUFFERSIZE];  /* Reference URI */
	char param_type[MAXBUFFERSIZE]; /* Reference type */
	transforms *vtransforms;			/* <Transforms> */
	digestmethod *vdigestmethod;		/* <DigestMethod> */
	digestvalue *vdigestvalue;		/* <DigestValue> */
	xmlNodePtr refNode;				/* xml node that bears this reference */
	reference *next;				/* possible next Reference */
};

/**
 * canonicalizationmethod
 *
 * <CanonicalizationMethod> element
 */

typedef struct _canonicalizationmethod canonicalizationmethod;
struct _canonicalizationmethod
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	char param_algorithm[MAXBUFFERSIZE];
	unsigned char *data;
};

/**
 * signaturemethod
 *
 * <SignatureMethod> element
 */

typedef struct _signaturemethod signaturemethod;
struct _signaturemethod
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	char param_algorithm[MAXBUFFERSIZE];
	int hmacOutputLength;
	unsigned char *data;
};

/**
 * signedinfo
 *
 * <SignedInfo> element
 */

typedef struct _signedinfo signedinfo;
struct _signedinfo
{
	char param_id[MAXBUFFERSIZE];
	canonicalizationmethod *vcanonicalizationmethod;
	signaturemethod *vsignaturemethod;
	reference *vreference;
};

/**
 * signaturevalue
 *
 * <SignatureValue> element
 */

typedef struct _signaturevalue signaturevalue;
struct _signaturevalue
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	char param_id[MAXBUFFERSIZE];
	unsigned char *data;
};


/**
 * dsakeyvalue
 *
 *
 */

typedef struct _dsakeyvalue dsakeyvalue;
struct _dsakeyvalue
{
	unsigned char P[MAXBUFFERSIZE];
	unsigned char Q[MAXBUFFERSIZE];
	unsigned char G[MAXBUFFERSIZE];
	unsigned char Y[MAXBUFFERSIZE];
	unsigned char J[MAXBUFFERSIZE];
	unsigned char seed[MAXBUFFERSIZE];
	unsigned char pGenCounter[MAXBUFFERSIZE];
};

/**
 * rsakeyvalue
 *
 *
 */

typedef struct _rsakeyvalue rsakeyvalue;
struct _rsakeyvalue
{
	unsigned char Modulus[MAXBUFFERSIZE];
	unsigned char Exponent[MAXBUFFERSIZE];
};

/**
 * retrievalmethod
 *
 *
 */

typedef struct _retrievalmethod retrievalmethod;
struct _retrievalmethod
{
	char URI[MAXBUFFERSIZE];
	char Type[MAXBUFFERSIZE];
	transforms *vtransforms;
	xmlNodePtr refNode;				/* xml node that bears this reference */
};


/**
 * x509group
 *
 *
 */

typedef struct _x509group x509group;
struct _x509group
{
	char X509IssuerSerial_Name[MAXBUFFERSIZE];
	char X509IssuerSerial_Number[MAXBUFFERSIZE];
	char X509SubjectName[MAXBUFFERSIZE];
	char X509SKI[MAXBUFFERSIZE];
	char *X509Certificate;
	char *X509CRL;
	x509group *next;
};

/**
 * x509data
 *
 *
 */

typedef struct _x509data x509data;
struct _x509data
{
	x509group *group;
	x509data *next;
};


/**
 * pgpdata
 *
 *
 */

typedef struct _pgpdata pgpdata;
struct _pgpdata
{
	unsigned char PGPKeyPacket[MAXBUFFERSIZE];
	unsigned char PGPKeyID[MAXBUFFERSIZE];
};

/**
 * spkidata
 *
 *
 */

typedef struct _spkidata spkidata;
struct _spkidata
{
	unsigned char SPKISexp[MAXBUFFERSIZE];
};

/**
 * keyname
 *
 *
 */

typedef struct _keyname keyname;
struct _keyname
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	unsigned char *data;
};


/**
 * keyvalueelements
 *
 *
 */

typedef struct _keyvalueelements keyvalueelements;
struct _keyvalueelements
{
	unsigned char param_ns[MAXBUFFERSIZE]; /* not used */
	dsakeyvalue *vdsakeyvalue;
	rsakeyvalue *vrsakeyvalue;
	unsigned char *data;
	keyvalueelements *next;
};

/**
 * keyinfo
 *
 *
 */

typedef struct _keyinfo keyinfo;
struct _keyinfo
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	char param_id[MAXBUFFERSIZE];
	keyname *vkeyname;
	keyvalueelements *vkeyvalueelements;
	retrievalmethod *vretrievalmethod;
	x509data *vx509data;
	pgpdata *vpgpdata;
	spkidata *vspkidata;
	unsigned char MgmtDta[MAXBUFFERSIZE];
};

/**
 * manifest
 *
 *
 */

typedef struct _manifest manifest;
struct _manifest
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	char param_id[MAXBUFFERSIZE];
	reference *vreference;
};

/**
 * signatureproperty
 *
 *
 */

typedef struct _signatureproperty signatureproperty;
struct _signatureproperty
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	char param_target[MAXBUFFERSIZE];
	char param_id[MAXBUFFERSIZE];
	unsigned char *data;
	signatureproperty *next;
};

/**
 * signatureproperties
 *
 *
 */

typedef struct _signatureproperties signatureproperties;
struct _signatureproperties
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	char param_id[MAXBUFFERSIZE];
	signatureproperty *vsignatureproperty;
};

/**
 * object
 *
 *
 */

typedef struct _object object;
struct _object
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	char param_id[MAXBUFFERSIZE];
	char mimetype[MAXBUFFERSIZE];
	char encoding[MAXBUFFERSIZE];
	unsigned char *data;
	signatureproperties *vsignatureproperties;
	manifest *vmanifest;
	object *next;
};

/**
 * signature
 *
 * The main structure - contains all information about signature currently has being processed
 */

typedef struct _signature signature;
struct _signature
{
	char param_ns[MAXBUFFERSIZE]; /* not used */
	char param_id[MAXBUFFERSIZE];
	char param_xmlns[MAXBUFFERSIZE];	/* xmlns="..." */
	signaturevalue *vsignaturevalue;
	signedinfo *vsignedinfo;
	keyinfo *vkeyinfo;
	object *objects;
};



/**
 * CERT_DESCR
 *
 * describes X509 certificate
 */

typedef struct _CERT_DESCR CERT_DESCR;
typedef CERT_DESCR *PCERT_DESCR;
struct _CERT_DESCR{
	unsigned char serialNumber[256];
	WCHAR issuer[256];
	WCHAR subject[256];
	WCHAR shortSubject[256];
	unsigned char notAfter[256];
	unsigned char *certificate;
};

/**
 * SIGNED_OBJECT
 *
 * object data for reference
 */

typedef struct _SIGNED_OBJECT SIGNED_OBJECT;
typedef SIGNED_OBJECT *PSIGNED_OBJECT;
struct _SIGNED_OBJECT{
	unsigned char encoding[256];	// object encoding
	unsigned char *encodedData;		// encoded data
};


/**
 * URI_PATH
 *
 * describes full path to detached file
 */

typedef struct _URI_PATH URI_PATH;
typedef URI_PATH *PURI_PATH;
struct _URI_PATH{
	unsigned char *sigId;		/* signature Id */
	unsigned char *URI;			/* reference URI */
	unsigned char *fullPath;	/* full path to the file if URI is file */
};


/**
 * URI_STATUS
 *
 * reference status after signature verification
 */

typedef struct _URI_STATUS URI_STATUS;
typedef URI_STATUS *PURI_STATUS;
struct _URI_STATUS{
	unsigned char *URI;				/* reference URI */
	unsigned char *digestMethod;	/* digest method */
	int status;						/* digest validated (1) or not (0)*/
	PSIGNED_OBJECT refObject;		/* object data */
};


/**
 * SIG_STATUS
 *
 * signature status after verification
 */

typedef struct _SIG_STATUS SIG_STATUS;
typedef SIG_STATUS *PSIG_STATUS;
struct _SIG_STATUS{
	unsigned char *sigId;			/* signature ID */
	unsigned char *sigMethod;		/* signature algorithm */
	int status;						/* validated or not */
	int lasterror;					/* last error if not validated */
	PURI_STATUS *refArray;			/* array of PURI_STATUS */
	int refNumber;					/* number of references */
	PCERT_DESCR signerCert;			/* signer certificate */
	unsigned char **propArray;		/* array of SignatureProperty, name=value */
	int propNumber;					/* sizeof of the properties array */
	unsigned char **certificates;	/* base64 encoded X509 certificate chain used in the current signature */
									/* the certificate at index 0 is the signer certificate */
	int certificatesCount;			/* The number of certificates in the chain */
	unsigned char **crlDataList;	/* base64 encoded CRL data included with the current signature */
	unsigned int	crlDataCount;	/* The number of CRLs included in the crlDataList */
};


/**
 * DS_DATA_BLOB
 *
 * Equivalent to CRYPT_DATA_BLOB of CryptoAPI
 */

typedef struct _DS_DATA_BLOB DS_DATA_BLOB;
typedef DS_DATA_BLOB *PDS_DATA_BLOB;
struct _DS_DATA_BLOB {
	unsigned char *pbData;		/* pointer to data */
	unsigned long cbData;		/* size of data */
};


/**
 * TRS_DATA_BLOB
 *
 * Input/output structure for transformations
 */

typedef struct _TRS_DATA_BLOB TRS_DATA_BLOB;
typedef TRS_DATA_BLOB *PTRS_DATA_BLOB;
struct _TRS_DATA_BLOB {
	unsigned char *pbData;		/* octet stream */
	unsigned long cbData;		/* size of octet stream */
	xmlNodeSetPtr nodeSet;		/* node-set */
	xmlXPathContextPtr ctx;		/* XPath context */
	st_transform *trf;				/* current transform */
	int inputType;				/* OCTET_STREAM or XPATH_NODE_SET */
	int outputType;				/* OCTET_STREAM or XPATH_NODE_SET */
	int c14mode;				/* with /without comments, TRUE/FALSE */
};

/**
 * lasterror
 *
 * Stack of errors
 */
typedef struct _lasterror lasterror;
struct _lasterror{
	int number;
	char description[512];
	lasterror *prev;
};

/**
 * GLOBAL_SIG
 *
 * Structure for all global variables
 */

typedef struct _GLOBAL_SIG GLOBAL_SIG;
typedef struct _GLOBAL_SIG *PGLOBAL_SIG;
struct _GLOBAL_SIG
{
	int verified;		// flag to set after Verify()
	PSIG_STATUS *sigArray;	// array of all found signatures
	int sigNumber;			// number of all found signatures
	PURI_PATH *locArray;	// array of locators
	int locNumber;			// number of URI_PATH passed to axVerifyDetachedFile

	xmlDocPtr pXmlDoc;			 // XML document with <Signature>
	xmlNodePtr pXmlSig;			 // current <Signature> XML node
	signature *sig;				 // pointer to main structure
	unsigned char *providerName; // CSP name, default NULL.
	unsigned char *dtdError;	 // DTD validation errors
	lasterror *lastError;		 // stack of errors
	int useFastC14N;
#ifdef NSS
	unsigned char *certStorePassword; // NSS certificate store password
	unsigned char *certStoreName; // Netscape or FireFox
	unsigned char *certStorePath; // NSS certificate store path to remove upon NSS shutdown
#endif
};


/*
 *	Core library functions
 */
#ifdef NSS
extern PGLOBAL_SIG xsCoreInit(const unsigned char *certStorePassword, const unsigned char *certStoreName);
#else
extern PGLOBAL_SIG xsCoreInit();
#endif
extern int xsCoreInitSignature(PGLOBAL_SIG);
// free internal structures
extern int xsCoreFreeSignature(PGLOBAL_SIG);
// setup xml document for signature processing - must call before xsVerify()
extern int xsCoreInitXmlDocument(xmlDocPtr pdoc, PGLOBAL_SIG pg_sig);
// generate XML output to the file
extern int xsCoreGenerateXMLSecDoc(char *filename, PGLOBAL_SIG pg_sig);
// generate XML output in memory
extern unsigned char *xsCoreGenerateXMLSec(PGLOBAL_SIG pg_sig, int *iSize);
// get <SignedInfo> as octet stream, before canonicalization
extern unsigned char *xsCoreGetSignedInfoBlob(int verifyFlag, xmlNodePtr sigNode, PGLOBAL_SIG pg_sig);
// returns the last defined reference
extern reference *xsCoreGetReference(PGLOBAL_SIG pg_sig);
// adds new reference
extern reference *xsCoreAddReference(PGLOBAL_SIG pg_sig);
// get <Transforms> for <RetrievalMethod>
extern transforms *xsCoreGetRMTransforms(retrievalmethod *retmeth,PGLOBAL_SIG pg_sig);
// get the last <Transform> of the <Transforms>
extern st_transform *xsCoreGetTransform(transforms *transforms, PGLOBAL_SIG pg_sig);
// add new <Ttransform>
extern st_transform *xsCoreAddTransform(transforms *transforms, PGLOBAL_SIG pg_sig);
// get the last <KeyValue>
extern keyvalueelements *xsCoreGetKeyValueElements(PGLOBAL_SIG pg_sig);
// add <KeyValue>
extern keyvalueelements *xsCoreAddKeyValueElements(keyinfo *ki, PGLOBAL_SIG pg_sig);
// get X509Data
extern x509data *xsCoreGetX509Data(PGLOBAL_SIG pg_sig);
// add X509Data
extern x509data *xsCoreAddX509Data(keyinfo *ki,PGLOBAL_SIG pg_sig);
// get Object
extern object *xsCoreGetObject(PGLOBAL_SIG pg_sig);
// add new Object
extern object *xsCoreAddObject(PGLOBAL_SIG pg_sig);
// get <SignatureProperties>
extern signatureproperties *xsCoreGetSignatureProperties(object *object, PGLOBAL_SIG pg_sig);
// get <SignatureProperty>
extern signatureproperty *xsCoreGetSignatureProperty(signatureproperties *signatureproperties, PGLOBAL_SIG pg_sig);
// add <SignatureProperty>
extern signatureproperty *xsCoreAddSignatureProperty(signatureproperties *signatureproperties, PGLOBAL_SIG pg_sig);
// setters for XML elements
extern int xsCoreSetSignature(char *param_id, char *param_xmlns, PGLOBAL_SIG pg_sig);
extern int xsCoreSetSignedInfo(char *param_id, PGLOBAL_SIG pg_sig);
extern int xsCoreSetCanonicalizationMethod(char *param_ns, char *param_algorithm, unsigned char *data, PGLOBAL_SIG pg_sig);

extern int xsCoreSetSignatureMethod(char *param_ns, char *param_algorithm, int hmacOutputLength, unsigned char *data,PGLOBAL_SIG pg_sig);
extern int xsCoreSetReference(reference *ref, char *param_ns, char *param_id,
						   char *param_uri, char *param_type, xmlNodePtr param_node,PGLOBAL_SIG pg_sig );
extern int xsCoreSetDigestMethod(digestmethod *dig, char *param_ns,
							  char *param_algorithm, unsigned char *data, PGLOBAL_SIG pg_sig);
extern int xsCoreSetDigestValue(digestvalue *dig, char *param_ns, unsigned char *data,PGLOBAL_SIG pg_sig);
extern int xsCoreSetTransforms(transforms *transf, char *param_ns, PGLOBAL_SIG pg_sig);
extern int xsCoreSetTransform(st_transform *trf, char *param_ns, char *param_algorithm,
						   char *param_uri, unsigned char *data, xmlNodePtr node, PGLOBAL_SIG pg_sig );
extern int xsCoreSetSignatureValue(char *param_ns, char *param_id, unsigned char *data, PGLOBAL_SIG pg_sig);
extern int xsCoreSetKeyInfo(keyinfo *ki,char *param_ns, char *param_id, PGLOBAL_SIG pg_sig);
extern int xsCoreSetKeyName(keyname *kn,char *param_ns, unsigned char *data, PGLOBAL_SIG pg_sig);

extern int xsCoreSetKeyValueElements(keyvalueelements *keyvalels, char *param_ns,
								  unsigned char *data, PGLOBAL_SIG pg_sig);
extern int xsCoreSetDSAKeyValue(dsakeyvalue *dsa, char *P, char *Q,
						   char *G, char *Y, char *J, char *seed, char *pGenCounter, PGLOBAL_SIG pg_sig);
extern int xsCoreSetRSAKeyValue(rsakeyvalue *rsa, char *Modulus,
							 char *Exponent, PGLOBAL_SIG pg_sig);
extern int xsCoreSetRetrievalMethod(retrievalmethod *retmethod, char *URI,
								 char *type, xmlNodePtr rnode, PGLOBAL_SIG pg_sig);
extern int xsCoreSetRMTransforms(retrievalmethod *retmeth, char *param_ns, PGLOBAL_SIG pg_sig);
extern int xsCoreSetPGPData(pgpdata *pgp, unsigned char *PGPKeyPacket,
						 unsigned char *PGPKeyID, PGLOBAL_SIG pg_sig);
extern int xsCoreSetSPKIData(spkidata *spki, unsigned char *SPKISexp, PGLOBAL_SIG pg_sig);
extern int xsCoreSetMgmtData(unsigned char *data, PGLOBAL_SIG pg_sig);
extern int xsCoreSetObject(object *obj, char *param_ns, char *param_id, char *mimetype,
						char *encoding, unsigned char *data, PGLOBAL_SIG pg_sig);
extern int xsCoreSetSignatureProperties(signatureproperties *sps, char *param_ns, char *param_id, PGLOBAL_SIG pg_sig);
extern int xsCoreSetSignatureProperty(signatureproperty *sp, char *param_ns,
						 char *param_target, char *param_id, unsigned char* data, PGLOBAL_SIG pg_sig);
extern void xsCoreSetXPath(xpath *xpth,
		xmlChar *ns_prefix,
		xmlChar *ns_href,
		xmlChar *data,
		xmlNodePtr here);
extern xpath *xsCoreAddXPath(st_transform *trf, PGLOBAL_SIG pg_sig);
extern manifest *xsCoreAddManifest(object *obj, PGLOBAL_SIG pg_sig);
extern signatureproperties *xsCoreAddSignatureProperties(object *obj,PGLOBAL_SIG pg_sig);
extern dsakeyvalue *xsCoreAddDsaKeyValue(keyvalueelements *kel, PGLOBAL_SIG pg_sig);
extern rsakeyvalue *xsCoreAddRsaKeyValue(keyvalueelements *kel, PGLOBAL_SIG pg_sig);
extern keyinfo *xsCoreAddKeyInfo(PGLOBAL_SIG pg_sig);
extern keyname *xsCoreAddKeyName(keyinfo *ki, PGLOBAL_SIG pg_sig);
extern retrievalmethod *xsCoreAddRetrievalMethod(keyinfo *ki, PGLOBAL_SIG pg_sig);
extern pgpdata *xsCoreAddPGPData(keyinfo *ki, PGLOBAL_SIG pg_sig);
extern spkidata *xsCoreAddSPKIData(keyinfo *ki, PGLOBAL_SIG pg_sig);
// parse XML node <Signature>
extern int xsCoreParseSignature(xmlNodePtr sigNode, PGLOBAL_SIG pg_sig);
// check on well-formed XML
extern int xsCoreValidateXMLStructure(unsigned char *pdoc, int dwSize);
// set CSP
extern void xsCoreSetCSP(BYTE *cspName, PGLOBAL_SIG pg_sig);
// create new reference (helper for RetrievalMethod)
extern reference *xsCoreNewReference();
// create new x509data (helper for RetrievalMethod)
extern x509data *xsCoreNewX509Data();
extern reference *xsCoreAddTimestamp(PGLOBAL_SIG pg_sig,unsigned char *tsUrl);
extern int xsCoreSetManifest(manifest *mfs, char *param_id, PGLOBAL_SIG pg_sig);
extern reference *xsCoreManifestAddReference(manifest *mfs, PGLOBAL_SIG pg_sig);
extern x509group *xsCoreAddX509Group(x509data *dt, PGLOBAL_SIG pg_sig);
extern int xsCoreSetX509Group(x509group *x509grp,
						  char *X509SubjectName,
						  char *X509SKI,
						  char *X509Certificate,
						  char *X509CRL,
						  char *X509IssuerSerial_Name,
						  char *X509IssuerSerial_Number,
						  PGLOBAL_SIG pg_sig);
extern x509group *xsCoreNewX509Group();
extern int xsCoreSetSignatureNSPrefix(char *ns_prefix, PGLOBAL_SIG pg_sig);
#if __cplusplus
}
#endif

#endif


