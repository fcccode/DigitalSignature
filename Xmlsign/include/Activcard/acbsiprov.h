/* ---------------------------------------------------------------------------
   (c) Copyright 1998, 2001 ActivCard
   All Rights Reserved.

   This program is an unpublished copyrighted work which is proprietary
   to ActivCard. This computer program includes Confidential,
   Proprietary Information and is a Trade Secret of ActivCard.
   Any use, disclosure, modification and/or reproduction is prohibited
   unless authorized in writing by ActivCard.

   WARNING:  Unauthorized reproduction of this program as well as
   unauthorized preparation of derivative works based upon the
   program or distribution of copies by sale, rental, lease or
   lending are violations of federal copyright laws and state trade
   secret laws, punishable by civil and criminal penalties.
   --------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------
   Disclaimer

   ActivCard makes no representations or warranties with respect to the
   contents or use of this software, and specifically disclaims any express
   or implied warranties of merchantability or fitness for any particular
   purpose. Further, ActivCard reserves the right to revise this software
   and to make changes to its content, at any time, without obligation to
   notify any person or entity of such revisions or changes.
   Further, ActivCard makes no representations or warranties with respect to
   any software, and specifically disclaims any express or implied warranties
   of merchantability or fitness for any particular purpose.
   --------------------------------------------------------------------------- */


#ifndef __ACBSIPROV_H__
#define __ACBSIPROV_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Parameters */
#define IN
#define OUT
#define INOUT

#if defined(WIN32) || defined(WIN16)
/* Windows standard files and definitions */
#include <windows.h>
#else
/* Unix standard files and definitions */
#include <stdio.h>
#define CALLBACK
#define TRUE 1
#define FALSE 0
#endif

/*@{*/ /* The comments are formatted for doc++ */
/* public accessors to retrieve the various parts of the version */

/************/
/** MACROS **/
/************/

#define BSI_MAJOR_VERSION(x)		((int)(((unsigned int)(x)>>24)&0xFF))
#define BSI_MINOR_VERSION(x)		((int)(((unsigned int)(x)>>16)&0xFF))
#define BSI_BUILD_VERSION(x)		((int)(((unsigned int)(x)>>8)&0xFF))

/***************/
/** CONSTANTS **/
/***************/


/**
* BSI_AUTHENTICATOR_MAX_LEN
* Maximum access right authenticator length 
*/
#define BSI_AUTHENTICATOR_MAX_LEN	255

/**
* BSI_KEY_LENGTH
* Authentication key length 
*/
#define BSI_KEY_LENGTH	16


/** 
*	Access Control Rules 
*
**/

/* Uninitialized Access Control Rule  */
#define BSI_ACR_UNDEF			-1

/* No Access Control Rule required */
#define BSI_ACR_ALWAYS			0

/* Operation is never possible */
#define BSI_ACR_NEVER			1

/* External Authentication, performed as a challenge/response is required  */
#define BSI_ACR_XAUTH			2

/* Object method can be accessed either after an External Authentication or a successful CHV verification */
#define BSI_ACR_XAUTH_OR_PIN	3

/* secure channel */
#define BSI_SECURE_CHANNEL_OP 	4

/* PIN code is required */ 
#define BSI_ACR_PIN				6

/* External Authentication followed by a PIN presentation */
#define BSI_ACR_XAUTH_THEN_PIN	7


#define BSI_SECURE_CHANNEL_DIN 	31

#define BSI_SECURE_CHANNEL_ISO	32

/* Access control rules  */
#define XSI_ACR_XAUTH_READ		20
#define XSI_ACR_XAUTH_UPDATE	21



/* Invalid card connection handle */
#define BSI_INVALID_CARD_HANDLE		-1


#define BSI_RSA_NO_PAD			10	
#define BSI_DES3_ECB			20

#define BSI_GCJ8 0x00000001
#define BSI_GCJ8X 0x00000002
#define BSI_SKI 0x00000004
#define BSI_PKI 0x00000008

/* type for pStrProperty in AC_XSI_GetProperties */
#define XSI_PROPERTY_MAX_LEN	255

/* LSB */
#define XSI_PPRTYPE_GC_BUFTAG_SIZE__	0x14
/* LSB */
#define XSI_PPRTYPE_GC_BUFVALUE_SIZE_	0x15
/* Applet version */
#define XSI_PPRTYPE_VERSION	0x01
/* Xtented/BSI */
#define XSI_PPRTYPE_TAG_TYPE	0x10 
/* type : SKI(Async/sync) or PKI */
#define XSI_PPRTYPE_CRYPTO_	0x11
/* RSA or DES key length */
#define XSI_PPRTYPE_CRYPTO_KEY_LEN_	0x12
/* SKI counter value */
#define XSI_PPRTYPE_SKI_SYNC_CNT_	0x13
#define XSI_PPRTYPE_CUID         0x20
#define XSI_PPRTYPE_CAPABILITIES 0x21

/* Possible value of type for pStrProperty are: */
#define XSI_TAG_DEFAULT	0x01
#define XSI_TAG_EXTENDED	0x02
#define XSI_CRYPTO_PKI	0x01
#define XSI_CRYPTO_SKI_SYNC	0x02
#define XSI_CRYPTO_SKI_ASYNC	0x03
/* (64 bytes RSA-512 bits) */
#define XSI_CRYPTO_KEY_LEN_512	0x40 
/* (128 bytes RSA-1024 bits) */
#define XSI_CRYPTO_KEY_LEN_1024	0x80 
/* (8bytes DES) */
#define XSI_CRYPTO_KEY_LEN_64	0x08 
/* (16 bytes DES3) */
#define XSI_CRYPTO_KEY_LEN_128	0x10 
/* (96 bytes RSA-768 bits) */
#define XSI_CRYPTO_KEY_LEN_768	0x60

/* number of item (each item=TLV) in a category */
#define NB_CARD_PROPERTIES	2
#define NB_PKI_PROPERTIES	3
#define NB_SKI_PROPERTIES	4
#define NB_STATIC_PROPERTIES	4

/**
* Return codes
* Return codes and error codes
*/
enum
{

	BSI_OK						=0,			/* Execution completed successfully */
	BSI_ACCESS_DENIED			= -30001, 	/* Access conditions are not fulfilled */
	BSI_BAD_AID					= -30002, 	/* The card application of the given AID cannot be found on the card */
	BSI_BAD_ALGO_ID				= -30003, 	/* The algorithm ID provided to the cryptographic Provider is not supported. */
	BSI_BAD_AUTH				= -30004, 	/* Authenticator value or type is not correct  */
	BSI_BAD_HANDLE				= -30005, 	/* Unknown card handle */
	BSI_BAD_PARAM				= -30006, 	/* Incorrect parameter value */
	BSI_BAD_TAG					= -30007, 	/* Incorrect parameter value */
	BSI_CARD_ABSENT				= -30008, 	/* There is no card in the reader */
	BSI_CARD_NOT_INIT			= -30009, 	/* The smart card is not yet initialized */
	BSI_CARD_PRESENT			= -30010, 	/* There is a card in the reader */
	BSI_CARD_REMOVED			= -30011, 	/* The connected smart card has been removed */
	BSI_CARD_RESET				= -30012, 	/* The communication with the card was reset */
	BSI_COMM_ERROR				= -30013, 	/* Error during communication with the card */
	BSI_CREATE_ERROR			= -30014, 	/* Error creating data in Generic Container  */
	BSI_DATA_CORRUPTED			= -30015, 	/* The provider has detected that the data read from the smart card is corrupted. */
	BSI_DELETE_ERROR			= -30016, 	/* Error deleting data in Generic Container  */
	BSI_INSUFFICIENT_BUFFER		= -30017, 	/* The buffer provided to retrieve data is too small */
	BSI_LOAD_LIB_FAILED			= -30018, 	/* Loading of card communication library failed */
	BSI_NO_MORE_DATA			= -30019, 	/* No space available for data creation in container */
	BSI_NOT_IMPLEMENTED			= -30020, 	/* The service is not implemented in the API  version */
	BSI_PIN_LOCKED				= -30021, 	/* The card is locked because too many wrong PIN have been entered */
	BSI_READ_ERROR				= -30022, 	/* Error reading data in Generic Container or getting a Certificate */
	BSI_SERVICE_NOT_AVAILABLE	= -30023, 	/* The card does not implement a BSI service required by the Application. */
	BSI_UNKNOWN_ERROR			= -30024, 	/* An error occurred but the cause is unknown  */
	BSI_UNKNOWN_READER			= -30025, 	/* Unknown reader */
	BSI_UPDATE_ERROR			= -30026, 	/* Error updating data in Generic Container  */
	BSI_ACR_NOT_AVAILABLE		= -30027, 	/* The card or applet does not support the access control rule for which the application was attempting to establish a security context. */
	XSI_WEAK_PIN				= -30028,   /* The PIN does not follow weak PIN policy */
	XSI_INVALID_PIN_LENGTH		= -30029,    /* The PIN length does not follow Min/Max PIN length requirements */
	XSI_NO_KEY					= -30030,    /* No private key */
	XSI_NO_CERTIFICATE			= -30031	 /* No certificate */
};




/**********************/
/** TYPE DEFINITIONS **/
/**********************/

/**
* @type UTILCardHandle
* @name UTILCardHandle
*
* Connection handle
* Card communication handle
*/
typedef int UTILCardHandle;


/**
* @type GCTag
* @name GCTag
*
* Container Data identification Tag
* Container Data identification Tag
*/
typedef unsigned char GCTag;

/* Auhenticator structure */
typedef struct strBSI_AUthenticator
{
	unsigned int	unACRType;
	unsigned char	usAuthValue[BSI_AUTHENTICATOR_MAX_LEN];
	unsigned int	unAuthLen;
	unsigned char	usKeyValue[BSI_KEY_LENGTH];
} BSIAuthenticator;

/* Auhenticator structure */
typedef struct strGC_ContainerSize
{
	unsigned int	unMaxNbDataItems;
	unsigned int	unMaxValuesStorageSize;
} GCContainerSize;

/* GC access right structure */
typedef struct strGC_ACR
{
	unsigned int	unCreateACR;
	unsigned int	unDeleteACR;
	unsigned int	unReadTagListACR;
	unsigned int	unReadValueACR;
	unsigned int	unUpdateValueACR;
} GCAcr;

/* GC access right structure */
typedef struct strCRYPTO_ACR
{
	unsigned int	unGetChallengeACR;
	unsigned int	unInternalAuthACR;
	unsigned int	unPKIComputeACR;
	unsigned int	unReadCertificateACR;
} CRYPTOAcr;

/* extented version to get properties */
typedef struct strXSI_Property
{
	unsigned char pusPropertyType;
	unsigned char pusPropertyValue[XSI_PROPERTY_MAX_LEN];
	unsigned int unPropertyValueLen;
} XSIProperty;

#define AC_XSI_Connect(x,y,z) AC_XSI_UtilConnect(x,y,z)
#define AC_XSI_Disconnect(x)  AC_XSI_UtilDisconnect(x)
#define AC_XSI_GetCuid(x,y,z) AC_XSI_UtilGetCuid(x,y,z)


/***************/
/** FUNCTIONS **/
/***************/


/* --------------------    Utility provider API    -------------------- */


/**
* AC_XSI_UtilConnect.
*
* Retrieve a card communication handle
*
*@return ...
*
*@param phCard				Retrieved card communication handle
*@param usReaderName		Reader where connection should be established
*@param nReaderNameLen		Length of the reader name
*
*/
int CALLBACK AC_XSI_UtilConnect(
	OUT UTILCardHandle*		phCard,				/* Retrieved card communication handle */
	IN  unsigned char*		usReaderName,		/* Reader where connection should be established */
	IN  unsigned int		nReaderNameLen		/* Length of the reader name */
	);

/**
* gscBsiUtilConnect.
*
* Retrieve a card communication handle
*
*@return ...
*
*@param phCard				Retrieved card communication handle
*
*/
int CALLBACK gscBsiUtilConnect(
	OUT UTILCardHandle*		phCard				/* Retrieved card communication handle */
	);

/**
* AC_XSI_UtilDisconnect.
*
* Close communication to the card
*
*@return ...
*
*@param hCard				Handle of the connection to be closed
*
*/
int CALLBACK AC_XSI_UtilDisconnect(
	IN  UTILCardHandle		hCard				/* Card communication handle */
	);

/**
* gscBsiUtilDisconnect.
*
* Close communication to the card
*
*@return ...
*
*@param hCard				Handle of the connection to be closed
*
*/
int CALLBACK gscBsiUtilDisconnect(
	IN  UTILCardHandle		hCard				/* Card communication handle */
	);

/**
* AC_XSI_UtilGetCuid.
*
* Get card serial number 
*
*@return ...
*
*@param phCard			Retrieved communication handle
*@param pSerialNumber		Card Serial Number
*@param punSerialNumberLen	Serial Number length
*
*
*@see 
*
*@author ddo
*
*@version 1.0
*
*
*/
int CALLBACK AC_XSI_UtilGetCuid(
	OUT UTILCardHandle		hCard,				/* Retrieved communication handle */
	OUT unsigned char		*pSerialNumber,		/* Card Serial Number */
	OUT unsigned int		*punSerialNumberLen	/* Serial Number length */
	);

/**
* AC_XSI_GetProperties.
*
* Retrieve Card and Applets properties 
*
*@return ...
*
*@param hCard				Card communication handle
*@param usAID				GC AID value 
*@param unAIDLen			Length of GC AID value 
*@param pstrProperty		Card and Applets properties
*@param punPropertNb		Number of Applets or Card Properties
*/
int CALLBACK AC_XSI_GetProperties(	
	IN  UTILCardHandle		hCard,				/* Card communication handle */
   	IN	unsigned char*		usAID,
	IN	unsigned int		unAIDLen,
	OUT	XSIProperty*		pstrProperty,
	INOUT unsigned int*		punPropertNb
	);


/**
* gscBsiUtilGetCardProperties.
*
* Get card presence status in reader or for a connected card 
*
*@return ...
*
*@param hCard				Card communication handle
*@param pusCardUniqueID		Card unique identifier computed from Chip Identifiers	
*@param punUniqueIDLength	Card unique identifier length
*@param punCardCapability	Card capabilirties (GCA, PKI, SKI)
*/
int CALLBACK gscBsiUtilGetCardProperties(	
	IN  UTILCardHandle		hCard,				/* Card communication handle */
   	OUT unsigned char*	    pusCardUniqueID,
	INOUT unsigned int*		punUniqueIDLength,
	OUT unsigned int*  	    punCardCapability
	);



/**
* AC_XSI_UtilGetCardStatus.
*
* Get card presence status in reader or for a connected card 
*
*@return ...
*
*@param hCard				Card communication handle
*@param usReaderName		Reader name for status 	
*@param unReaderNameLen		Reader name length 
*/
int CALLBACK AC_XSI_UtilGetCardStatus(	
	IN  UTILCardHandle		hCard,				/* Card communication handle */
	IN unsigned char*		usReaderName,		/* Reader name for status 	 */
	IN unsigned int			unReaderNameLen		/* Reader name length */
	);


/**
* AC_XSI_UtilGetReaderList.
*
* Retrieve the list of configured readers
*
*@return ...
*
*@param pusReadersList		Readers list multi-string buffer  	
*@param punReadersListLen	Readers list buffer length 
*/
int CALLBACK AC_XSI_UtilGetReaderList(
	OUT		unsigned char	*puszReadersList,	/* Readers list multi-string buffer */
    INOUT	unsigned int	*punReadersListLen	/* Readers list buffer length  */
	);


/**
* gscBsiUtilGetVersion.
*
* Retrieve GC provider API version information
*
*@return ...
*
*@param pusVersion			Printable API version
*@param pnVersionLen		Length of printable API version
*
*/
int CALLBACK gscBsiUtilGetVersion(
	OUT		unsigned char*	usVersion,			/* Printable API version */
	INOUT	int*			pnVersionLen		/* Length of printable API version */
	);


/**
* gscBsiUtilPassthru.
*
* 
*
*@return ...
*
*@param hCard				Card communication handle
*@param usCardCommand		APDU sent to the card
*@param uncardCommandLen	Length of APDU sent to the card
*@param pusCardResponse		Card response
*@param puncardCommandLen	Length of Card response
*
*/
int CALLBACK gscBsiUtilPassthru(
	IN		UTILCardHandle	hCard,				/* Card communication handle */
	IN		unsigned char*	usCardCommand,		/* APDU sent to the card */
	IN		unsigned int	uncardCommandLen,	/* Length of APDU sent to the card */
	OUT		unsigned char*	pusCardResponse,	/* Card response */
	OUT		unsigned int*	puncardResponseLen	/* Length of Card response */
	);


/**
* gscBsiUtilAcquireContext.
*
* Give access to a service providing the appropriate values to perform authentication
*
*@return ...
*
*@param hCard				Card communication handle
*@param usAID				GC AID value
*@param unAIDLen			Length of GC AID value
*@param pstrAuthenticator	Array of structures containing the authenticators
*@param unAuthenticatorNb	Number of authenticators in structure
*
*/
int CALLBACK gscBsiUtilAcquireContext(
	IN	UTILCardHandle		hCard,				/* Card communication handle */
	IN	unsigned char*		usAID,				/* GC AID value */
	IN	unsigned int		unAIDLen,			/* Length of GC AID value */
	IN  BSIAuthenticator*	pstrAuthenticator,	/* Array of structures containing the authenticators */
	IN  unsigned int		unAuthenticatorNb	/* Number of authenticators in structure */
	);


/**
* gscBsiUtilReleaseContext.
*
* Give up access to a card service
*
*@return ...
*
*@param hCard				Card communication handle
*@param usAID				GC AID value
*@param unAIDLen			Length of GC AID value
*
*/
int CALLBACK gscBsiUtilReleaseContext(
	IN  UTILCardHandle		hCard,				/* Card communication handle */
	IN	unsigned char*		usAID,				/* GC AID value */
	IN	unsigned int		unAIDLen			/* Length of GC AID value */
	);

/**
* AC_XSI_UtilChangePIN.
*
* Change PIN
*
*@return ...
*
*@param hCard				Card communication handle
*@param usAID				GC AID value
*@param unAIDLen			Length of GC AID value
*@param usOldPIN			Old PIN value 
*@param unOldPINLen			Old PIN value length 
*@param usNewPIN			New PIN value 		
*@param unNewPINLen			New PIN value length 
*
*/
int CALLBACK AC_XSI_UtilChangePIN(
	IN UTILCardHandle       hCard,				/* Card communication handle */
	IN unsigned char*		usAID,				/* GC AID value	*/
	IN unsigned int			unAIDLen,			/* Length of GC AID value */
	IN char*				usOldPIN,			/* Old PIN value */
	IN unsigned int			unOldPINLen,		/* Old PIN value length */
	IN char*				usNewPIN,			/* New PIN value */		
	IN unsigned int			unNewPINLen			/* New PIN value length */
	);

/**
* AC_XSI_UtilIsPINVerified.
*
* Retrieve PIN verification status
*
*@return BSI_OK				PIN is verified
*@return BSI_ACCESS_DENIED	PIN is not verified
*
*@param hCard				Card communication handle
*@param usAID				GC AID value
*@param unAIDLen			Length of GC AID value
*@param pnLeftPinTry		Remaining attempts before PIN is blocked 
*
*/
int CALLBACK AC_XSI_UtilIsPINVerified(
	IN UTILCardHandle       hCard,				/* Card communication handle */
	IN unsigned char*		usAID,				/* GC AID value	*/
	IN unsigned int			unAIDLen,			/* Length of GC AID value */
	OUT int*				pnLeftPinTry		/* Remaining attempts before PIN is blocked */
	);

/* ------------------------ GC provider API Prototypes ---------------------- */



/* tagged data management */

/**
* gscBsiGcGetContainerProperties.
*
* Retrieve Access Rights configuration for data label and value
* in container
*
*@return ...
*
*@param hCard						Card communication handle 
*@param usAID						Container AID  
*@param unAIDLen					Container AID length  
*@param pstrACR						GC Services access right structure table  
*@param pstrContainerSize			Size of container storage  
*@param pusContainerVersion			Container version  
*@param punContainerVersionlength	Length of container version  
*
*/
int CALLBACK gscBsiGcGetContainerProperties(
	IN  UTILCardHandle		hCard,						/* Card communication handle */
	IN  unsigned char*		usAID,						/* Container AID */ 
	IN  unsigned int		unAIDLen,					/* Container AID length */
	OUT GCAcr*				pstrACR,					/* GC Services access right structure table */
	OUT GCContainerSize*	pstrContainerSize,			/* Size of container storage */
	OUT unsigned char*		pusContainerVersion,		/* Container version */
	IN OUT unsigned int*	punContainerVersionlength	/* Length of container version */
	);



/**
* gscBsiGcDataCreate.
*
* Create a new data in  container
*
*@return ...
*
*@param hCard				Card communication handle
*@param usAID				Container AID
*@param unAIDLen			Container AID length
*@param ucTag				Data Identification Tag
*@param usValue				Data value
*@param unValueLen			Data value length
*
*/
int CALLBACK gscBsiGcDataCreate(
	IN  UTILCardHandle		hCard,				/* Card communication handle */
	IN  unsigned char*		usAID,				/* Container AID */ 
	IN  unsigned int		unAIDLen,			/* Container AID length */
	IN	GCTag				ucTag,				/* Data identification tag */
	IN  unsigned char*		usValue,			/* Data value */		
	IN  unsigned int		unValueLen			/* Data value length */		
	);



/**
* gscBsiGcDataDelete.
*
* Delete a data from a container 
*
*@return ...
*
*@param hCard				Card communication handle
*@param usAID				Container AID
*@param unAIDLen			Container AID length
*@param pstrAR,				Autenticator structure table
*@param unARNb,				Number of structures in table
*@param unTag				Data container identification tag
*
*/
int CALLBACK gscBsiGcDataDelete(
	IN	UTILCardHandle		hCard,				/* Card communication handle */
	IN	unsigned char*		usAID,				/* Container AID */ 
	IN	unsigned int		unAIDLen,			/* Container AID length */
	IN	GCTag				ucTag				/* Data container identification tag */
	);



/**
* gscBsiGcReadTagList
*
* Get the list of existing tags within a container
*
*@return ...
*
*@param hCard				Card communication handle
*@param usAID				Container AID
*@param unAIDLen			Container AID length
*@param pTagArray			Array of tags
*@param pnTagNb				Number of tags in array
*
*/
int CALLBACK gscBsiGcReadTagList(
	IN     UTILCardHandle	hCard,				/* Card communication handle */
	IN     unsigned char*	usAID,				/* Container AID */ 
	IN     unsigned int		unAIDLen,			/* Container AID length */
	OUT	   GCTag*			pTagArray,			/* Array of tags */
	INOUT  unsigned int*	pnTagNb				/* Number of tags in array */		
	);


/**
* gscBsiGcReadValue.
*
* Retrieve value of a data container
*
*@return ...
*
*@param hCard				Card communication handle
*@param usAID				Container AID
*@param unAIDLen			Container AID length
*@param ucTag				Data identification tag
*@param usDataValue			Retrieved data value 
*@param punDataValueLen		Retrieved data value length
*
*/
int CALLBACK gscBsiGcReadValue(
	IN	  UTILCardHandle	hCard,				/* Card communication handle */
	IN    unsigned char*	usAID,				/* Container AID */ 
	IN    unsigned int		unAIDLen,			/* Container AID length */
 	IN	  GCTag				ucTag,				/* Data identification tag */
	OUT   unsigned char*	usDataValue,		/* Data value */ 
	INOUT unsigned int*		punDataValueLen		/* Data value length */
	);


/**
* gscBsiGcUpdateValue.
*
* Change the value for an existing data in a container 
*
*@return .
*
*@param hCard				Card communication handle
*@param usAID				Container AID
*@param unAIDLen			Container AID length
*@param ucTag				Data identification tag
*@param usDataValue			Updated data value
*@param unDataValueLen		Data value length
*
*/
int CALLBACK gscBsiGcUpdateValue(
	IN	UTILCardHandle		hCard,				/* Card communication handle */
	IN  unsigned char*		usAID,				/* Container AID */ 
	IN  unsigned int		unAIDLen,			/* Container AID length */
 	IN	GCTag				ucTag,				/* Data identification tag */
	IN	unsigned char*		usDataValue,		/* Updated data value */		
	IN	unsigned int		unDataValueLen		/* Data value length */		
	);

/**
* AC_XSI_GetBuffer.
*
* Get buffer from container 
*
*@return .
*
*@param hCard				Card communication handle
*@param usAID				Container AID
*@param unAIDLen			Container AID length
*@param punVBufferLength	Value buffer length
*@param pVBuffer			Value buffer
*@param punTBufferLength	Tag buffer length
*@param pTBuffer			Tag buffer
*
*/
int CALLBACK AC_XSI_GetBuffer(
	IN		UTILCardHandle		hCard,				/* Card communication handle */
	IN		unsigned char*		usAID,				/* Container AID */ 
	IN		unsigned int		unAIDLen,			/* Container AID length */
 	INOUT	unsigned int*		punTBufferLength,	/* Tag buffer length */
	OUT		unsigned char*		pTBuffer,			/* Tag buffer */
	INOUT	unsigned int*		punVBufferLength,	/* Value buffer length */
	OUT		unsigned char*		pVBuffer			/* Value buffer	*/
	);

/**
* AC_XSI_SetBuffer.
*
* Set buffer in container 
*
*@return .
*
*@param hCard				Card communication handle
*@param usAID				Container AID
*@param unAIDLen			Container AID length
*@param punVBufferLength	Value buffer length
*@param pVBuffer			Value buffer
*@param punTBufferLength	Tag buffer length
*@param pTBuffer			Tag buffer
*
*/
int CALLBACK AC_XSI_SetBuffer(
	IN	UTILCardHandle		hCard,				/* Card communication handle */
	IN	unsigned char*		usAID,				/* Container AID */ 
	IN	unsigned int		unAIDLen,			/* Container AID length */
	IN	unsigned int		unTBufferLength,	/* Tag buffer length */
	IN	unsigned char*		pTBuffer,			/* Tag buffer */
 	IN	unsigned int		unVBufferLength,	/* Value buffer length */
	IN	unsigned char*		pVBuffer			/* Value buffer	*/
	);


/* ------------------------ Cryptographic provider API Prototypes ---------------------- */


/**
* gscBsiGetCryptoProperties.
*
* Retrieve cryptographic services properties 
*
*@return .
*
*@param hCard				Card communication handle
*@param usAID				Container AID
*@param unAIDLen			Container AID length
*@param pstrAcr				Crypto services access rights 
*@param unKeyLength			RSA key length
*
*/
int CALLBACK gscBsiGetCryptoProperties(
	IN	UTILCardHandle		hCard,				/* Card communication handle */
	IN  unsigned char*		usAID,				/* Container AID */ 
	IN	unsigned int		unAIDLen,			/* Container AID length */
 	OUT	CRYPTOAcr*			pstrAcr,			/* Crypto services access rights */
	OUT	unsigned int*		unKeyLength			/* RSA key length */		
	);

/**
* gscBsiGetChallenge.
*
* Retrieve challenge for external authentication 
*
*@return .
*
*@param hCard				Card communication handle
*@param usAID				Container AID
*@param unAIDLen			Container AID length
*@param pusChallenge		Retrieved challenge 
*@param punChallengeLen		Length of retrieved challenge
*
*/
int CALLBACK gscBsiGetChallenge(
	IN	UTILCardHandle		hCard,				/* Card communication handle */
	IN  unsigned char*		usAID,				/* Container AID */ 
	IN  unsigned int		unAIDLen,			/* Container AID length */
 	OUT	unsigned char*		pusChallenge,		/* Retrieved challenge */
	INOUT unsigned int*		punChallengeLen		/* Length of retrieved challenge */		
	);


/**
* gscBsiPkiCompute
*
* Perform data signature
*
*@return .
*
*@param hCard				Card communication handle
*@param usAID				Container AID
*@param unAIDLen			Container AID length
*@param ucAlgoId			Algorithm Id 
*@param usMessage			Message to be signed 
*@param unMessageLen		Length of message to be signed  
*@param pusResult			Resulting signature 
*@param punResultLen		Length of resulting signature
*
*/
int CALLBACK gscBsiPkiCompute(
	IN		UTILCardHandle	hCard,				/* Card communication handle */
	IN		unsigned char*	usAID,				/* Container AID */ 
	IN		unsigned int	unAIDLen,			/* Container AID length */
	IN		unsigned char	ucAlgoId,			/* Algorithm Id */
	IN		unsigned char*	usMessage,			/* Message to be signed */ 
	IN		unsigned int	unMessageLen,		/* Length of message to be signed */
	OUT		unsigned char*	pusResult,			/* Resulting signature */ 
	INOUT	unsigned int*	punResultLen		/* Length of resulting signature */
	);


/**
* gscBsiPkiReadCertificate
*
* Read certificate from card
*
*@return .
*
*@param hCard				Card communication handle
*@param usAID				Container AID
*@param unAIDLen			Container AID length
*@param pusCertificate		Message to be signed 
*@param punCertificateLen	Length of message to be signed  
*
*/
int CALLBACK gscBsiPkiReadCertificate(
	IN		UTILCardHandle	hCard,				/* Card communication handle */
	IN		unsigned char*	usAID,				/* Container AID */ 
	IN		unsigned int	unAIDLen,			/* Container AID length */
	OUT		unsigned char*	pusCertificate,		/* Certificate buffer */
	INOUT	unsigned int*	punCertificateLen	/* Length of certificate buffer */ 
	);


/**
* gscBsiSkiInternalAuthenticate
*
* Read certificate from card
*
*@return .
*
*@param hCard				Card communication handle
*@param usAID				Container AID
*@param unAIDLen			Container AID length
*@param ucAlgoId			Algorithm Id 
*@param usChallenge			Message to be signed 
*@param unChallengeLen		Length of message to be signed  
*@param pusCryptogram		Computed cryptogram 
*@param punCryptogramLen	Length of computed cryptogram  
*
*/
int CALLBACK gscBsiSkiInternalAuthenticate(
	IN		UTILCardHandle	hCard,				/* Card communication handle */
	IN		unsigned char*	usAID,				/* Container AID */ 
	IN		unsigned int	unAIDLen,			/* Container AID length */
	IN		unsigned char	ucAlgoId,			/* Algorithm Id */
	IN		unsigned char*	usChallenge,		/* Challenge submitted to the card */ 
	IN		unsigned int	unChallengeLen,		/* Length of challenge */
	OUT		unsigned char*	pusCryptogram,		/* Computed cryptogram */ 
	INOUT	unsigned int*	punCryptogramLen	/* Length of computed cryptogram */
	);


/*@}*/ /* The comments are formatted for doc++ */

#ifdef __cplusplus
}
#endif

#endif /* __ACBSIPROV_H__ */
