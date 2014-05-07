/*
 * BSId.h
 */

/******************************************************************
 
            Title  : BSId.h
            Package: BSI
            Author : Del Putnam (dputnam@sympagic.com)
            Date   : 08/09/2002
            License: Proprietary

			Copyright © 2002 The MITRE Corporation

            Purpose: Provides definitions for a BSI module based 
					 on the GSC-IS through version 2.0
 
********************************************************************/

#ifndef __BSID_H__
#define __BSID_H__

#define BSI_DLL_NAME "acbsiprov.dll"


/*
BSI Implementation Dependent Constants
*/
#define BSI_AUTHENTICATOR_MAX_LEN	255
#define BSI_KEY_LENGTH				16
#define BSI_ERROR_TEXT_LEN			255


/*
 * Access Control Rules 
 */

#define BSI_ACR_ALWAYS			0x00	/* No access control rule is required */
#define	BSI_ACR_NEVER			0x01	/* Operation is never possible */
#define	BSI_ACR_XAUTH			0x02	/* External Authentication.	*/
#define BSI_ACR_XAUTH_OR_PIN	0x03	/* The object method can be accessed either after an External Authentication or after a successful PIN presentation	*/
#define BSI_SECURE_CHANNEL_GP	0x04	/* Secure Channel (Global Platform)	*/
#define BSI_SECURE_CHANNEL_OP	0x04	/* Secure Channel (Global Platform)(GSC 1.8)*/
#define BSI_ACR_PIN_ALWAYS		0x05	/* PIN must be verified immediately prior to service request. */
#define BSI_ACR_PIN				0x06	/* PIN code is required	*/
#define BSI_ACR_XAUTH_THEN_PIN	0x07	/* External Authentication followed by a PIN presentation */
#define BSI_ACR_UPDATE_ONCE		0x08	/* The target object can only be updated once during its lifetime */
#define BSI_ACR_PIN_THEN_XAUTH	0x09	/* PIN presentation followed by External Authentication	*/
#define BSI_SECURE_CHANNEL_ISO	0x0B	/* Secure Channel (ISO 7816-4) */


/*
 * Card Capabilities Bitmask Definitions
 */
#define BSI_GCCDM		0x00000001  
#define BSI_SKI			0x00000002  
#define BSI_PKI			0x00000004  
#define BSI_GCCDM_EXT	0x00000008  
#define BSI_SKI_EXT		0x00000010  
#define BSI_PKI_EXT		0x00000020

#ifdef GSC_2_0
/*
 * GSC-IS v2.0 Return Codes
 */
#define BSI_OK					0x00		/* Execution completed successfully. */
#define BSI_ACCESS_DENIED		0x01		/* The applicable ACR was not fulfilled. */
#define BSI_ACR_NOT_AVAILABLE	0x02		/* The specified ACR is incorrect. */
#define BSI_BAD_AID				0x03		/* The specified Application Identifiers (AID) does not exist. */
#define BSI_BAD_ALGO_ID			0x04		/* The specified cryptographic algorithm is not available. */
#define BSI_BAD_AUTH			0x05		/* Invalid authentication data. */
#define BSI_BAD_HANDLE			0x06		/* The specified card handle is not available. */
#define BSI_BAD_PARAM			0x07		/* One or more of the specified parameters is incorrect. */
#define BSI_BAD_TAG				0x08		/* Invalid tag information. */
#define BSI_CARD_ABSENT			0x09		/* The card associated with the specified card handle is not present. */
#define BSI_CARD_REMOVED		0x0A		/* The card associated with the specified card handle has been removed. */
#define BSI_CREATE_ERROR		0x0B		/* Error encountered while trying to create the specified data. */
#define BSI_DELETE_ERROR		0x0D		/* Error encountered while trying to delete the specified data. */
#define BSI_INSUFFICIENT_BUFFER 0x0E		/* The buffer allocated by the calling application is too small. */
#define BSI_NO_CARDSERVICE		0x0F		/* The smart card associated with the specified card handle does not provide the requested service. */
#define BSI_NO_MORE_SPACE		0x10		/* There is insufficient space in the selected container to store the specified data. */
#define BSI_PIN_LOCKED			0x11		/* The PIN is locked. */
#define BSI_READ_ERROR			0x12		/* Error encountered while attempting to read the specified data. */
#define BSI_TAG_EXISTS			0x13		/* The tag specified for a create operation already exists in the target container. */
#define BSI_TIMEOUT_ERROR		0x14		/* A connection could not be established with the card before the timeout value expired. */
#define BSI_TERMINAL_AUTH		0X15		/* The card reader has performed a successful Internal Authentication with the card. */
#define BSI_NO_TEXT_AVAILABLE	0x16		/* No extended error text is available. */
#define BSI_UNKNOWN_ERROR		0x17		/* The requested operation has generated an unspecified error. */
#define BSI_UNKNOWN_READER		0x18		/* The specified reader does not exist. */
#define BSI_UPDATE_ERROR		0x19		/* Error encountered while attempting to update the specified data. */

#else
/*
 * GSC-IS v1.8 Return codes
 */
#define	BSI_OK						0x00000000	/* Execution completed successfully */
#define	BSI_ACCESS_DENIED			0xFFFF8ACF	/* Access conditions are not fulfilled */
#define	BSI_BAD_AID					0xFFFF8ACE 	/* The card application of the given AID cannot be found on the card */
#define BSI_BAD_ALGO_ID				0xFFFF8ACD 	/* The algorithm ID provided to the cryptographic Provider is not supported. */
#define	BSI_BAD_AUTH				0xFFFF8ACC 	/* Authenticator value or type is not correct  */
#define	BSI_BAD_HANDLE				0xFFFF8ACB  /* Unknown card handle */
#define	BSI_BAD_PARAM				0xFFFF8ACA 	/* Incorrect parameter value */
#define	BSI_BAD_TAG					0xFFFF8AC9 	/* Incorrect parameter value */
#define	BSI_CARD_ABSENT				0xFFFF8AC8	/* There is no card in the reader */
#define	BSI_CARD_NOT_INIT			0xFFFF8AC7 	/* The smart card is not yet initialized */
#define	BSI_CARD_PRESENT			0xFFFF8AC6	/* There is a card in the reader */
#define	BSI_CARD_REMOVED			0xFFFF8AC5	/* The connected smart card has been removed */
#define	BSI_CARD_RESET				0xFFFF8AC4	/* The communication with the card was reset */
#define	BSI_COMM_ERROR				0xFFFF8AC3 	/* Error during communication with the card */
#define	BSI_CREATE_ERROR			0xFFFF8AC2 	/* Error creating data in Generic Container  */
#define	BSI_DATA_CORRUPTED			0xFFFF8AC1 	/* The provider has detected that the data read from the smart card is corrupted. */
#define	BSI_DELETE_ERROR			0xFFFF8AC0 	/* Error deleting data in Generic Container  */
#define	BSI_INSUFFICIENT_BUFFER		0xFFFF8ABF 	/* The buffer provided to retrieve data is too small */
#define	BSI_LOAD_LIB_FAILED			0xFFFF8ABE 	/* Loading of card communication library failed */
#define	BSI_NO_MORE_DATA			0xFFFF8ABD	/* No space available for data creation in container */
#define	BSI_NOT_IMPLEMENTED			0xFFFF8ABC 	/* The service is not implemented in the API  version */
#define	BSI_PIN_LOCKED				0xFFFF8ABB 	/* The card is locked because too many wrong PIN have been entered */
#define	BSI_READ_ERROR				0xFFFF8ABA 	/* Error reading data in Generic Container or getting a Certificate */
#define	BSI_SERVICE_NOT_AVAILABLE	0xFFFF8AB9 	/* The card does not implement a BSI service required by the Application. */
#define	BSI_UNKNOWN_ERROR			0xFFFF8AB8 	/* An error occurred but the cause is unknown  */
#define	BSI_UNKNOWN_READER			0xFFFF8AB7 	/* Unknown reader */
#define	BSI_UPDATE_ERROR			0xFFFF8AB6 	/* Error updating data in Generic Container  */
#define	BSI_ACR_NOT_AVAILABLE		0xFFFF8AB5 	/* The card or applet does not support the access control rule for which the application was attempting to establish a security context. */

#endif /* GSC_2_0 */

#endif /*__BSID_H__*/
