/*
 * BSIt.h
 */

/******************************************************************
 
            Title  : BSIt.h
            Package: BSI
            Author : Del Putnam (dputnam@sympagic.com)
            Date   : 08/09/2002
            License: Proprietary

			Copyright © 2002 The MITRE Corporation

            Purpose: Provides type definitions for BSI modules
			         based on the GSC-IS through version 2.0
 
********************************************************************/

/* 
 * BSI Types 
 */

#ifndef __BSIT_H__
#define __BSIT_H__


/*
 * BSI Implementation Dependent type definitions
 *
 * Note: Since there are differences between the GSC-IS 1.8
 *		 and the GSC-IS 2.0 specs for this structure, applications
 *		 should use the identifier BSI_GCT defined here
 *		 to ensure compatibility.
 */
#ifdef GSC_2_0
typedef long			UTILCardHandle;
typedef unsigned char	GCtag;	/* GSC-IS v2.0 */
#define BSI_GCT			GCtag
#else
typedef int				UTILCardHandle;
typedef unsigned char	GCTag;
#define BSI_GCT			GCTag
#endif
typedef unsigned char	gcTag;	/* for backward compatibility */

/*
 * Macros to provide consistency between BSI Types that 
 * differ between GSC-IS v1.8 and v2.0.  To ensure compatibility,
 * applications should use the identifiers defined here
 * rather than the equivalent C/C++ keywords.
 */
#ifdef GSC_2_0
#define BSI_RETURN	unsigned long
#define BSI_INT		unsigned long
#define BSI_UINT	unsigned long
#else
#define BSI_RETURN	int
#define BSI_INT		int
#define BSI_UINT	unsigned int
#endif


/*
 * Auhenticator structure
 */
#ifdef GSC_2_0
typedef struct { 
	unsigned int	unACRtype; 
	unsigned char	usAuthValue [BSI_AUTHENTICATOR_MAX_LEN]; 
	unsigned int	unAuthValueLen; 
	unsigned char	usKeyValue[BSI_KEY_LENGTH]; 
	bool			bWriteKey; 
} BSIAuthenticator;
#else
typedef struct {
	unsigned int	unACRType;
	unsigned char	usAuthValue[BSI_AUTHENTICATOR_MAX_LEN];
	unsigned int	unAuthLen;
	unsigned char	usKeyValue[BSI_KEY_LENGTH];
} BSIAuthenticator;
#endif

/*
 * Auhenticator structure
 */
#ifdef GSC_2_0
typedef struct strctContainerSizes
{ 
	unsigned long	unMaxNbDataItems; 
	unsigned long	unMaxValueStorageSize; 
} GCContainerSize;
#else
typedef struct strGC_ContainerSize
{
	unsigned int	unMaxNbDataItems;
	unsigned int	unMaxValuesStorageSize;
} GCContainerSize;
#endif

/*
 * GC access right structure
 *
 * Note: Since there are differences between the GSC-IS 1.8
 *		 and the GSC-IS 2.0 specs for this structure, applications
 *		 should use the identifier BSI_GC_ACR defined here
 *		 to ensure compatibility.
 */
#ifdef GSC_2_0
typedef struct strctGCacr
{ 
	unsigned long	unCreateACR; 
	unsigned long	unDeleteACR; 
	unsigned long	unReadTagListACR; 
	unsigned long	unReadValueACR; 
	unsigned long	unUpdateValueACR; 
} GCacr;
#define BSI_GC_ACR GCacr
#else
typedef struct strGC_ACR
{
	unsigned int	unCreateACR;
	unsigned int	unDeleteACR;
	unsigned int	unReadTagListACR;
	unsigned int	unReadValueACR;
	unsigned int	unUpdateValueACR;
} GCAcr;
typedef GCAcr	GCacr;	/* for backward compatibility */
#define BSI_GC_ACR GCAcr
#endif


/*
 * Crypto access right structure
 *
 * Note: Since there are differences between the GSC-IS 1.8
 *		 the GSC-IS 2.0 specs for this structure, applications
 *		 should use the identifier BSI_CRYPTO_ACR defined
 *		 here to ensure compatibility.
 */
#ifdef GSC_2_0
typedef struct strctCRYPTOacr
{ 
	unsigned long	unGetChallengeACR; 
	unsigned long	unInternalAuthenticateACR; 
	unsigned long	unPkiComputeACR; 
	unsigned long	unReadCertificateACR; 
} CRYPTOacr;
#define BSI_CRYPTO_ACR CRYPTOacr
#else
typedef struct strCRYPTO_ACR
{
	unsigned int	unGetChallengeACR;
	unsigned int	unInternalAuthACR;
	unsigned int	unPKIComputeACR;
	unsigned int	unReadCertificateACR;
} CRYPTOAcr;
#define BSI_CRYPTO_ACR CRYPTOAcr
#endif

/*
 * Function pointer type definitions for BSI dlls
 *
 * Applications which explicitly load a BSI DLL should use
 * the function pointer types defined here to declare the
 * pointers to BSI functions.
 *
 * Example: 
 *
 * #include "BSI.h"								// include the function definition	
 * __gscBsiUtilConnect gscBsiUtilConnect;		// declare a pointer to a function
 * HINSTANCE hInst = LoadLibrary( "BSI.dll" );	// load the BSI DLL
 * gscBsiUtilConnect =							// initialize the function pointer
 *			(__gscBsiUtilConnect)GetProcAddress(m_hBSIDLL, "gscBsiUtilConnect");
 */
typedef BSI_RETURN (__cdecl * __gscBsiUtilAcquireContext)( 
	IN UTILCardHandle,					
	IN unsigned char*,				
	IN unsigned int,				
	IN BSIAuthenticator*,	
	IN unsigned int					
); 

#ifdef GSC_2_0
typedef BSI_RETURN (__cdecl * __gscBsiUtilConnect)(
	IN unsigned char*,			
	IN BSI_INT,		
	OUT UTILCardHandle*					
);
#else
typedef BSI_RETURN (__cdecl * __gscBsiUtilConnect)(
	OUT UTILCardHandle*
);
#endif
 

typedef BSI_RETURN (__cdecl * __gscBsiUtilDisconnect)( 
	IN UTILCardHandle					
); 


typedef BSI_RETURN (__cdecl * __gscBsiUtilGetVersion )(
	OUT unsigned char*,			
	IN OUT BSI_INT*			
); 
 

typedef BSI_RETURN (__cdecl * __gscBsiUtilGetCardProperties)( 
	IN UTILCardHandle,					
	OUT unsigned char*,		
	IN OUT BSI_INT*,			
	OUT BSI_INT*		
); 


typedef BSI_RETURN (__cdecl * __gscBsiUtilGetCardStatus)( 
	IN UTILCardHandle					
); 
 

typedef BSI_RETURN (__cdecl * __gscBsiUtilGetExtendedErrorText)( 
	IN UTILCardHandle,					
	OUT char*
); 
 

typedef BSI_RETURN (__cdecl * __gscBsiUtilGetReaderList)( 
	IN OUT unsigned char*,		
	IN OUT BSI_INT*
); 


typedef BSI_RETURN (__cdecl * __gscBsiUtilPassthru)( 
	IN UTILCardHandle,				
	IN unsigned char*,	
	IN BSI_INT,	
	IN OUT unsigned char*,	
	IN OUT BSI_INT*		
); 
 
typedef BSI_RETURN (__cdecl * __gscBsiUtilReleaseContext)( 
	IN UTILCardHandle,					
	IN unsigned char*,				
	IN BSI_INT				
); 


typedef BSI_RETURN (__cdecl * __gscBsiGcDataCreate)( 
	IN UTILCardHandle,					
 	IN unsigned char*,				
	IN BSI_INT,				
	IN BSI_GCT,					
 	IN unsigned char*,				
	IN BSI_INT				
); 
 
typedef BSI_RETURN (__cdecl * __gscBsiGcDataDelete)( 
	IN UTILCardHandle,					
	IN unsigned char*, 				
	IN BSI_INT, 				
	IN BSI_GCT 					
); 

#ifdef GSC_2_0
typedef BSI_RETURN (__cdecl * __gscBsiGcGetContainerProperties)( 
	IN UTILCardHandle,					
	IN unsigned char*, 				
	IN BSI_INT, 				
	OUT BSI_GC_ACR*, 			
	OUT GCContainerSize,	
	OUT unsigned char*		
); 
#else
typedef BSI_RETURN (__cdecl * __gscBsiGcGetContainerProperties)(
	IN  UTILCardHandle,				
	IN  unsigned char*,						
	IN  unsigned int,				
	OUT BSI_GC_ACR*,					
	OUT GCContainerSize*,			
	OUT unsigned char*,		
	IN OUT unsigned int*
	);
#endif
 
typedef BSI_RETURN (__cdecl * __gscBsiGcReadTagList)( 
	IN UTILCardHandle,					
	IN unsigned char*,				
	IN BSI_INT,				
	IN OUT BSI_GCT*,				
	IN OUT BSI_UINT*
); 

typedef BSI_RETURN (__cdecl * __gscBsiGcReadValue)( 
	IN UTILCardHandle,				
	IN unsigned char*, 			
	IN BSI_INT, 			
	IN BSI_GCT, 				
	IN OUT unsigned char*, 			
	IN OUT BSI_UINT*		
); 
 
typedef BSI_RETURN (__cdecl * __gscBsiGcUpdateValue)( 
	IN UTILCardHandle,					
	IN unsigned char*, 				
	IN BSI_INT, 				
	IN BSI_GCT, 					
	IN unsigned char*, 				
	IN BSI_INT 				
); 
 
typedef BSI_RETURN (__cdecl * __gscBsiGetChallenge)( 
	IN UTILCardHandle,				
	IN unsigned char*, 			
	IN BSI_INT, 			
	IN OUT unsigned char*, 		
	IN OUT BSI_INT*		
); 
 
typedef BSI_RETURN (__cdecl * __gscBsiSkiInternalAuthenticate)( 
	IN UTILCardHandle,					
 	IN unsigned char*, 				
	IN BSI_INT, 				
	IN unsigned char,				
 	IN unsigned char*, 			
	IN BSI_INT, 		
	OUT unsigned char*,			
 	IN OUT BSI_INT* 		
); 
 
typedef BSI_RETURN (__cdecl * __gscBsiPkiCompute)( 
	IN UTILCardHandle,				
	IN unsigned char*, 			
	IN BSI_INT, 			
	IN unsigned char, 			
	IN unsigned char*,		
	IN BSI_INT, 		
	IN OUT unsigned char*, 		
	IN OUT BSI_INT*		
);

typedef BSI_RETURN (__cdecl * __gscBsiPkiGetCertificate)( 
	IN UTILCardHandle,					
	IN unsigned char*, 				
	IN BSI_INT, 				
	OUT unsigned char*, 		
	IN OUT BSI_INT* 		
); 
 
typedef BSI_RETURN (__cdecl * __gscBsiGetCryptoProperties)( 
	IN UTILCardHandle,					
	IN unsigned char*, 				
	IN BSI_INT, 				
	OUT BSI_CRYPTO_ACR*,		
	OUT BSI_INT*			
); 
 
#endif /*__BSIT_H__*/