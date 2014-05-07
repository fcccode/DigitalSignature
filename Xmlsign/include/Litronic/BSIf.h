/*
 *BSIf.h
 */

/******************************************************************
 
            Title  : 
            Package: BSI
            Author : Del Putnam (dputnam@sympagic.com)
            Date   : 08/09/2002
            License: Proprietary

			Copyright © 2002 The MITRE Corporation

            Purpose: Provides function prototypes for all required
					 BSI functions as specified in the GSC-IS
					 through version 2.0
 
********************************************************************/

#ifndef __BSIF_H__
#define __BSIF_H__

#ifdef __cplusplus
extern "C" {
#endif

#define IN
#define OUT
#define INOUT

/*
Standard includes and definitions
*/
/*
Windows
*/
#if defined(WIN32) || defined(WIN16)
#include <windows.h>
/*
Unix
*/
#else
#include <stdio.h>
#define CALLBACK
#define TRUE 1
#define FALSE 0
#endif

/*
 *
 * gscBsiUtilAcquireContext()
 *
 * Purpose: This function shall establish a session with the smart card by submitting
 *			the appropriate Authenticator in the BSIAuthenticator structure.  For ACRs 
 *			requiring external authentication (XAUTH), the uszAuthValue field of the 
 *			BSIAuthenticator structure must contain a cryptogram calculated by encrypting 
 *			a random challenge. 
 *
 * Returns:	BSI_OK
 *			BSI_BAD_HANDLE 
 *			BSI_BAD_AID 
 *			BSI_ACR_NOT_AVAILABLE 
 *			BSI_BAD_AUTH 
 *			BSI_CARD_REMOVED 
 *			BSI_PIN_LOCKED 
 *			BSI_UNKNOWN_ERROR
 *
 */
BSI_RETURN gscBsiUtilAcquireContext( 
	IN UTILCardHandle	hCard,					/* Card connection handle from gscBsiUtilConnect()			*/
	IN unsigned char	*uszAID,				/* Target container AID value.								*/
	IN unsigned int		unAIDLen,				/* AID value length in bytes								*/
	IN BSIAuthenticator *strctAuthenticator,	/* An array of structures containing the authenticator(s) 
													specified by the ACR									*/
	IN unsigned int unAuthNb					/* Number of authenticator structures contained in 
													strctAuthenticator.										*/
); 


/*
 * gscBsiUtilConnect()
 *
 * Purpose: Establish a logical connection with the card in a specified reader. 
 *
 * Returns: BSI_OK
 *			BSI_BAD_PARAM 
 *			BSI_UNKNOWN_READER 
 *			BSI_CARD_ABSENT 
 *			BSI_UNKNOWN_ERROR   
 *
 */
#ifdef GSC_2_0
BSI_RETURN gscBsiUtilConnect(
	IN char				*uszReaderName,			/* Name of the reader that the card is inserted into.		*/
	IN BSI_INT			unReaderNameLen,		/* Length of the reader name in bytes						*/
	OUT UTILCardHandle	*hCard					/* Card connection handle.									*/
);
#else
BSI_RETURN gscBsiUtilConnect(
	OUT UTILCardHandle*		phCard				/* Card connection handle									*/
);
#endif


/*
 * gscBsiUtilDisconnect() 
 *
 * Purpose: Terminate a logical connection to a card. 
 *
 * Returns: BSI_OK 
 *			BSI_BAD_HANDLE 
 *			BSI_CARD_REMOVED 
 *			BSI_UNKNOWN_ERROR
 */
BSI_RETURN gscBsiUtilDisconnect( 
	IN UTILCardHandle	hCard					/* Card connection handle from gscBsiUtilConnect()			*/
); 


/*
 * gscBsiUtilBeginTransaction()
 *
 * Purpose: This function starts an exclusive transaction with the smart card
 *			referenced by hCard. When the transaction starts, all other
 *			applications are precluded from accessing the smart card while the
 *			transaction is in progress.
 *
 * Returns: BSI_OK
 *			BSI_BAD_HANDLE
 *			BSI_UNKNOWN_ERROR
 *			BSI_SC_LOCKED
 *			BSI_NOT_TRANSACTED
 *			BSI_NO_SPSERVICE
 */
#ifdef GSC_2_1
BSI_RETURN gscBsiUtilBeginTransaction(
	IN UTILCardHandle	hCard,
	IN BOOL				blType
);
#endif


/*
 * gscBsiUtilEndTransaction()
 *
 * Purpose: This function ends a previously started transaction, allowing other
 *			blocked applications to begin or resume interactions with the card.
 *
 * Returns: BSI_OK
 *			BSI_BAD_HANDLE
 *			BSI_UNKNOWN_ERROR
 *			BSI_NOT_TRANSACTED
 *			BSI_NO_SPSERVICE
 */
#ifdef GSC_2_1
BSI_RETURN gscBsiUtilEndTransaction(
	IN UTILCardHandle	hCard
);
#endif


/*
 * gscBsiUtilGetVersion() 
 * 
 * Purpose: Returns the BSI implementation version. 
 *
 * Returns: BSI_OK 
 *			BSI_BAD_PARAM 
 *			BSI_INSUFFICIENT_BUFFER 
 *			BSI_UNKNOWN_ERROR
 */
BSI_RETURN gscBsiUtilGetVersion (
	OUT unsigned char	*uszVersion,			/* The BSI and SCSPM version formatted as .major,minor,
													revision, build_number									*/
	IN OUT BSI_INT		*unVersionLen			/* Length of the version string								*/
); 
 

/*
 * gscBsiUtilGetCardProperties() 
 *
 * Purpose: Retrieves version and capability information for the card.
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_CARD_REMOVED 
 *          BSI_BAD_PARAM 
 *          BSI_INSUFFICIENT_BUFFER 
 *          BSI_NO_CARDSERVICE 
 *          BSI_UNKNOWN_ERROR 
 */
BSI_RETURN gscBsiUtilGetCardProperties( 
	IN UTILCardHandle	hCard,					/* Card connection handle from gscBsiUtilConnect().			*/
	OUT unsigned char	*uszCCCUniqueID,		/* Buffer for the Card Capability Container version			*/
	IN OUT BSI_INT		*unUniqueIDLen,			/* Length of the CCC Unique ID string (input).  Length of 
													the returned Card Unique ID string including the 
													null terminator (output).								*/
	OUT BSI_INT			*unCardCapability		/* Bit mask value defining the providers supported by the 
													card.													*/
); 


/*
 * gscBsiUtilGetCardStatus() 
 * Purpose: Checks whether a given card handle is associated with a card 
 *			that is inserted into a powered up reader.
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_CARD_REMOVED 
 *          BSI_UNKNOWN_ERROR 
 */
BSI_RETURN gscBsiUtilGetCardStatus( 
	IN UTILCardHandle	hCard					/* Card connection handle from gscBsiUtilConnect().			*/
); 
 

/*
 * gscBsiUtilGetExtendedErrorText() 
 *
 * Purpose: When a BSI function call returns an error, an application can 
 *			make a subsequent call to this function to receive additional 
 *			implementation specific error information, if available. 
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_PARAM 
 *          BSI_NO_TEXT_AVAILABLE 
 *          BSI_UNKNOWN_ERROR 
 */
BSI_RETURN gscBsiUtilGetExtendedErrorText( 
	IN UTILCardHandle	hCard,					/* Card connection handle gscBsiUtilConnect()				*/
	OUT char			uszErrorText[BSI_ERROR_TEXT_LEN]
												/* buffer containing an implementation specific error text 
													string													*/
); 
 

/*
 * gscBsiUtilGetReaderList() 
 *
 * Purpose: Retrieves the list of available readers. 
 *
 * Returns: BSI_OK 
 *          BSI_BAD_PARAM 
 *          BSI_INSUFFICIENT_BUFFER 
 *          BSI_UNKNOWN_ERROR 
 */
BSI_RETURN gscBsiUtilGetReaderList( 
	IN OUT unsigned char	*uszReaderList,		/* Reader list buffer.  The reader list is returned as a 
													multi-string, each reader name terminated by a .\0..  
													The list itself is terminated by an additional trailing 
													.\0. character.											*/
	IN OUT BSI_INT			*unReaderListLen	/* Reader list length in bytes including all terminating 
													.\0. characters											*/
); 


/*
 * gscBsiUtilPassthru() 
 *
 * Purpose: Allows a client application to send a .raw. APDU through the 
 *			BSI directly to the card and receive the APDU-level response. 
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_PARAM 
 *          BSI_INSUFFICIENT_BUFFER 
 *          BSI_CARD_REMOVED 
 *          BSI_UNKNOWN_ERROR 
 */
BSI_RETURN gscBsiUtilPassthru( 
	IN UTILCardHandle		hCard,				/* Card connection handle from gscBsiUtilConnect().			*/
	IN unsigned char		*uszCardCommand,	/* The APDU to be sent to the card							*/
	IN BSI_INT				unCardCommandLen,	/* Length of the APDU string to be sent						*/
	IN OUT unsigned char	*uszCardResponse,	/* Pre-allocated buffer for the APDU response from the card. 
													The response must include the status bytes SW1 and SW2 
													returned by the card.  If the size of the buffer is 
													insufficient, the SPS shall return truncated response 
													data and the return code BSI_INSUFFICIENT_BUFFER.		*/
	IN OUT BSI_INT *unCardResponseLen			/* Length of the APDU response.  If the size of the 
													uszCardResponse buffer is insufficient, the SPS shall 
													return the correct size in this field.					*/
); 
 

/*
 * gscBsiUtilReleaseContext() 
 *
 * Purpose: Terminate a session with the card. 
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_AID 
 *          BSI_BAD_PARAM 
 *          BSI_CARD_REMOVED 
 *          BSI_UNKNOWN_ERROR 
 */
BSI_RETURN gscBsiUtilReleaseContext( 
	IN UTILCardHandle	hCard,					/* Card connection handle from gscBsiUtilConnect()			*/
	IN unsigned char	*uszAID,				/* Target  container AID value								*/
	IN BSI_INT			unAIDLen				/* AID value length in bytes								*/
); 


/*
 * gscBsiGcDataCreate() 
 *
 * Purpose: Create a new data item in {Tag, Length, Value} format in the selected container. 
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_AID 
 *          BSI_BAD_PARAM 
 *          BSI_CARD_REMOVED 
 *          BSI_NO_CARDSERVICE 
 *          BSI_ACCESS_DENIED 
 *          BSI_NO_MORE_SPACE 
 *          BSI_TAG_EXISTS 
 *          BSI_CREATE_ERROR 
 *          BSI_UNKNOWN_ERROR 
 */
BSI_RETURN gscBsiGcDataCreate( 
	IN UTILCardHandle	hCard,					/* Card connection handle from gscBsiUtilConnect()			*/
 	IN unsigned char	*uszAID,				/* Target container AID value								*/
	IN BSI_INT			unAIDLen,				/* AID value length in bytes								*/
	IN BSI_GCT			ucTag,					/* Tag of data item to store								*/
 	IN unsigned char	*uszValue,				/* Data value to store										*/
	IN BSI_INT			unValueLen				/* Data value length in bytes								*/
); 
 

/* gscBsiGcDataDelete() 
 *
 * Purpose: Delete the data item associated with the tag value in the specified container. 
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_AID 
 *          BSI_BAD_PARAM 
 *          BSI_BAD_TAG 
 *          BSI_CARD_REMOVED 
 *          BSI_NO_CARDSERVICE 
 *          BSI_ACCESS_DENIED 
 *          BSI_DELETE_ERROR 
 *          BSI_UNKNOWN_ERROR 
 */
BSI_RETURN gscBsiGcDataDelete( 
	IN UTILCardHandle	hCard,					/* Card connection handle from gscBsiUtilConnect()			*/
	IN unsigned char	*uszAID, 				/* Target container AID value								*/
	IN BSI_INT			unAIDLen, 				/* AID value length in bytes								*/
	IN BSI_GCT			ucTag 					/* Tag of data item to delete								*/
); 


/*
 * gscBsiGcGetContainerProperties() 
 *
 * Purpose: Retrieves the properties of the specified container.  Access Control
 *		Rules are common to all data items managed by the selected container. 
 *
 * Returns: BSI_OK 
 *			BSI_BAD_HANDLE 
 *			BSI_BAD_AID 
 *			BSI_BAD_PARAM 
 *			BSI_CARD_REMOVED 
 *			BSI_NO_CARDSERVICE 
 *			BSI_UNKNOWN_ERROR 
 */
#ifdef GSC_2_0
BSI_RETURN gscBsiGcGetContainerProperties( 
	IN UTILCardHandle	hCard,					/* Card connection handle from gscBsiUtilConnect()			*/
	IN unsigned char	*uszAID, 				/* Target container AID value								*/
	IN BSI_INT			unAIDLen, 				/* AID value length in bytes								*/
	OUT BSI_GC_ACR		*strctGCacr, 			/* Structure indicating access control conditions for all 
													operations.												*/
	OUT GCContainerSize *pstrContainerSizes,	/* For Virtual Machine cards, the size(in bytes) of the 
													container specified by uszAID.  unMaxNbDataItems is the 
													size of the T-Buffer, and unMaxValueStorageSize is the 
													size of the V-Buffer.  For file system cards that cannot 
													calculate these values, both fields of this structure 
													will be set to 0.										*/
	OUT unsigned char *uszContainerVersion 		/* Version of the container.  The format of this value is 
													application dependent.  In cases where the card cannot 
													return a container version, this string will contain 
													only the NULL terminator .\0..							*/
); 
#else
int gscBsiGcGetContainerProperties(
	IN  UTILCardHandle		hCard,				
	IN  unsigned char		*usAID,						
	IN  unsigned int		unAIDLen,				
	OUT BSI_GC_ACR			*pstrACR,					
	OUT GCContainerSize		*pstrContainerSize,			
	OUT unsigned char		*pusContainerVersion,		
	IN OUT unsigned int		*punContainerVersionlength	/* Container Version length value in bytes			*/
	);
#endif
 

/*
 * gscBsiGcReadTagList() 
 *
 * Purpose: Return the list of tags in the selected container. 
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_AID 
 *          BSI_BAD_PARAM 
 *          BSI_CARD_REMOVED 
 *          BSI_NO_CARDSERVICE 
 *          BSI_ACCESS_DENIED 
 *          BSI_INSUFFICIENT_BUFFER 
 *          BSI_UNKNOWN_ERROR 
 */
BSI_RETURN gscBsiGcReadTagList( 
	IN UTILCardHandle	hCard,					/* Card connection handle from gscBsiUtilConnect().			*/
	IN unsigned char	*uszAID,				/* Target container AID value.								*/
	IN BSI_INT			unAIDLen,				/* AID value length in bytes								*/
	IN OUT BSI_GCT		*TagArray,				/* An array containing the list of tags for the selected 
													container												*/
	IN OUT BSI_UINT		*unNbTags 				/* Number of tags in TagArray								*/
); 


/*
 * gscBsiGcReadValue() 
 *
 * Purpose: Returns the Value associated with the specified Tag. 
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_AID 
 *          BSI_BAD_PARAM 
 *          BSI_BAD_TAG 
 *          BSI_CARD_REMOVED 
 *          BSI_NO_CARDSERVICE 
 *          BSI_ACCESS_DENIED 
 *          BSI_INSUFFICIENT_BUFFER 
 *          BSI_READ_ERROR 
 *          BSI_UNKNOWN_ERROR
 */
BSI_RETURN gscBsiGcReadValue( 
	IN UTILCardHandle		hCard,				/* Card connection handle from gscBsiUtilConnect().			*/
	IN unsigned char		*uszAID, 			/* Target container AID value								*/
	IN BSI_INT				unAIDLen, 			/* AID value length in bytes								*/
	IN BSI_GCT				ucTag, 				/* Tag value of data item to read							*/
	IN OUT unsigned char	*uszValue, 			/* Value associated with the specified tag.  The caller must
													allocate the buffer.									*/
	IN OUT BSI_UINT			*unValueLen 		/* Size of the buffer allocated by the caller to hold the 
													returned Value (input).  Size of the Value returned 
													(output).												*/
); 
 

/*
 * gscBsiGcUpdateValue() 
 *
 * Purpose: Updates the Value associated with the specified Tag. 
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_AID 
 *          BSI_BAD_PARAM 
 *          BSI_BAD_TAG 
 *          BSI_CARD_REMOVED 
 *          BSI_NO_CARDSERVICE 
 *          BSI_ACCESS_DENIED 
 *          BSI_NO_MORE_SPACE 
 *          BSI_UPDATE_ERROR 
 *          BSI_UNKNOWN_ERROR 
 */
BSI_RETURN gscBsiGcUpdateValue( 
	IN UTILCardHandle	hCard,					/* Card connection handle from gscBsiUtilConnect().			*/
	IN unsigned char	*uszAID, 				/* Target container AID value.								*/
	IN BSI_INT			unAIDLen, 				/* AID value length in bytes.								*/
	IN BSI_GCT			ucTag, 					/* Tag of data item to update.								*/
	IN unsigned char	*uszValue, 				/* New Value of the data item.								*/
	IN BSI_INT			unValueLen 				/* Length in bytes of the new Value.						*/
); 
 

/*
 * gscBsiGetChallenge() 
 *
 * Purpose: Retrieves a randomly generated challenge from the card as the 
 *			first step of a challenge-response authentication protocol between
 *			the client application and the card.  The client subsequently 
 *			encrypts the challenge using a symmetric key and returns the 
 *			encrypted random challenge to the card through a call to 
 *			gscBsiUtilAcquireContext() in the uszAuthValue field of a 
 *			BSIAuthenticator structure.   
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_AID 
 *          BSI_BAD_PARAM 
 *          BSI_CARD_REMOVED 
 *          BSI_NO_CARDSERVICE 
 *          BSI_INSUFFICIENT_BUFFER 
 *          BSI_UNKNOWN_ERROR 
 */
BSI_RETURN gscBsiGetChallenge( 
	IN UTILCardHandle		hCard,				/* Card connection handle from gscBsiUtilConnect()			*/
	IN unsigned char		*uszAID, 			/* Target container AID value								*/
	IN BSI_INT				unAIDLen, 			/* AID value length in bytes								*/
	IN OUT unsigned char	*uszChallenge, 		/* Random challenge returned from the card					*/
	IN OUT BSI_INT			*unChallengeLen		/* Length of random challenge in bytes						*/
); 
 

/*
 * gscBsiSkiInternalAuthenticate() 
 *
 * Purpose: Computes a symmetric key cryptogram in response to a challenge. 
 *			In cases where the card reader authenticates the card, this 
 *			function does not return a cryptogram.  In these cases a 
 *			BSI_TERMINAL_AUTH will be returned if the card reader successfully 
 * 			authenticates the card.  BSI_ACCESS_DENIED is returned if the card 
 *			reader fails to authenticate the card. 
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_AID 
 *          BSI_BAD_PARAM 
 *          BSI_BAD_ALGO_ID 
 *          BSI_CARD_REMOVED 
 *          BSI_NO_CARDSERVICE 
 *          BSI_ACCESS_DENIED 
 *          BSI_TERMINAL_AUTH 
 *          BSI_INSUFFICIENT_BUFFER 
 *          BSI_UNKNOWN_ERROR
 */
BSI_RETURN gscBsiSkiInternalAuthenticate( 
	IN UTILCardHandle	hCard,					/* Card connection handle from gscBsiUtilConnect().			*/
 	IN unsigned char	*uszAID, 				/* SKI provider module AID value.							*/
	IN BSI_INT			unAIDLen, 				/* AID value length in bytes								*/
	IN unsigned char	ucAlgoID,				/* Identifies the cryptographic algorithm that the card must
													use to encrypt the challenge.  All conformant 
													implementations shall, at a minimum, support DES3-ECB 
													(Algorithm Identifier 0x81) and DES3-CBC (Algorithm 
													Identifier 0x82).  Implementations may optionally 
													support other cryptographic algorithms.					*/
 	IN unsigned char	*uszChallenge, 			/* Challenge generated by the client application and 
													submitted to the card									*/
	IN BSI_INT			unChallengeLen, 		/* Length of the challenge in bytes.						*/
	OUT unsigned char	*uszCryptogram,			/* The cryptogram computed by the card.						*/
 	IN OUT BSI_INT		*unCryptogramLen 		/* Length of the cryptogram computed by the card in bytes.  */
); 
 

/*
 * gscBsiPkiCompute() 
 *
 * Purpose: Performs a private key computation on the message digest using the 
 *			private key associated with the specified AID. 
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_AID 
 *          BSI_BAD_PARAM 
 *          BSI_BAD_ALGO_ID 
 *          BSI_CARD_REMOVED 
 *          BSI_ACCESS_DENIED 
 *          BSI_NO_CARDSERVICE 
 *          BSI_INSUFFICIENT_BUFFER 
 *          BSI_UNKNOWN_ERROR
 */
BSI_RETURN gscBsiPkiCompute( 
	IN UTILCardHandle		hCard,				/* Card connection handle from gscBsiUtilConnect().			*/
	IN unsigned char		*uszAID, 			/* PKI provider module AID value.							*/
	IN BSI_INT				unAIDLen, 			/* AID value length in bytes								*/
	IN unsigned char		ucAlgoID, 			/* Identifies the cryptographic algorithm that will be used 
													to generate the signature.  All conformant 
													implementations shall, at a minimum, support RSA_NO_PAD 
													(Algorithm Identifier 0xA3).  Implementations may 
													optionally support other algorithms.					*/
	IN unsigned char		*uszMessage,		/* The hash of the message to be signed						*/
	IN BSI_INT				unMessageLen, 		/* Length of hashed message to be signed, in bytes.			*/
	IN OUT unsigned char	*uszResult, 		/* Buffer containing the signature.							*/
	IN OUT BSI_INT			*unResultLen 		/* Length of the signature buffer in bytes					*/
);


/*
 * gscBsiPkiGetCertificate() 
 *
 * Purpose: Reads the certificate from the card.   
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_AID 
 *          BSI_BAD_PARAM 
 *          BSI_CARD_REMOVED 
 *          BSI_NO_CARDSERVICE 
 *          BSI_ACCESS_DENIED 
 *          BSI_READ_ERROR 
 *          BSI_INSUFFICIENT_BUFFER 
 *          BSI_UNKNOWN_ERROR
 */
BSI_RETURN gscBsiPkiGetCertificate( 
	IN UTILCardHandle	hCard,					/* Card connection handle from gscBsiUtilConnect().			*/
	IN unsigned char	*uszAID, 				/* PKI provider module AID value.							*/
	IN BSI_INT			unAIDLen, 				/* AID value length in bytes.								*/
	OUT unsigned char	*uszCertificate, 		/* Buffer containing the certificate.						*/
	IN OUT BSI_INT		*unCertificateLen 		/* Length of the certificate buffer in bytes.				*/
); 
 

/*
 * gscBsiGetCryptoProperties() 
 *
 * Purpose: Retrieves the Access Control Rules and private cryptographic 
 *			key length managed by the PKI provider module. 
 *
 * Returns: BSI_OK 
 *          BSI_BAD_HANDLE 
 *          BSI_BAD_AID 
 *          BSI_BAD_PARAM 
 *          BSI_CARD_REMOVED 
 *          BSI_NO_CARDSERVICE 
 *          BSI_UNKNOWN_ERROR 
 */
BSI_RETURN gscBsiGetCryptoProperties( 
	IN UTILCardHandle	hCard,					/* Card connection handle from gscBsiUtilConnect().			*/
	IN unsigned char	*uszAID, 				/* AID of the PKI provider.									*/
	IN BSI_INT			unAIDLen, 				/* Length of the AID of the PKI provider, in bytes.			*/
	OUT BSI_CRYPTO_ACR	*strctCRYPTOacr,		/* Structure indicating access control conditions for all 
													operations.  The range of possible values for the 
													members of this structure are defined in Table 3.1 
													(Section 3.1), and the allowable ACRs for each 
													function in Table 3.3 (Section 3.2):					*/
	OUT BSI_INT			*unKeyLen				/* Length of the private key managed by the PKI provider.	*/
); 
 
#ifdef __cplusplus
}
#endif

#endif /*__BSIF_H__*/

