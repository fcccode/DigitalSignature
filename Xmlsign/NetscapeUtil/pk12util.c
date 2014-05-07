
#include <windows.h>

#include "nspr.h"
#include "secutil.h"
#include "pk11func.h"
#include "pkcs12.h"
#include "p12plcy.h"
#include "pk12util.h"
#include "nss.h"
#include "secport.h"
#include "certdb.h"


static SECStatus p12u_SwapUnicodeBytes(SECItem *uniItem)
{
    unsigned int i;
    unsigned char a;

	if((uniItem == NULL) || (uniItem->len % 2))
		return SECFailure;

	for(i = 0; i < uniItem->len; i += 2)
	{
		a = uniItem->data[i];
		uniItem->data[i] = uniItem->data[i+1];
		uniItem->data[i+1] = a;
    }

    return SECSuccess;
}

static PRBool p12u_ucs2_ascii_conversion_function(
					PRBool toUnicode,
					unsigned char *inBuf,
					unsigned int inBufLen,
					unsigned char *outBuf,
					unsigned int maxOutBufLen,
					unsigned int *outBufLen,
					PRBool swapBytes)
{
    SECItem it = { 0 };
    SECItem *dup = NULL;
    PRBool ret;
    /* If converting Unicode to ASCII, swap bytes before conversion
     * as neccessary.
     */
 //   if (pk12_debugging)
	//{
	//	int i;
	//	printf("Converted from:\n");
	//	for (i = 0; i < inBufLen; i++)
	//		printf("%2x ", inBuf[i]);
	//		/*if (i%60 == 0) printf("\n");*/
	//	printf("\n");
 //   }
    it.data = inBuf;
    it.len = inBufLen;
    dup = SECITEM_DupItem(&it);
    if (!toUnicode && swapBytes)
	{
		if (p12u_SwapUnicodeBytes(dup) != SECSuccess)
		{
			SECITEM_ZfreeItem(dup, PR_TRUE);
			return PR_FALSE;
		}
    }
    /* Perform the conversion. */
    ret = PORT_UCS2_UTF8Conversion(toUnicode, dup->data, dup->len,
								   outBuf, maxOutBufLen, outBufLen);
    if (dup)
		SECITEM_ZfreeItem(dup, PR_TRUE);
    /* If converting ASCII to Unicode, swap bytes before returning
     * as neccessary.
     */
 //   if (pk12_debugging)
	//{
	//	int i;
	//	printf("Converted to:\n");
	//	for (i=0; i<*outBufLen; i++)
	//		printf("%2x ", outBuf[i]);
	//		/*if (i%60 == 0) printf("\n");*/
	//	printf("\n");
 //   }

	return ret;
}

static void p12u_EnableAllCiphers()
{
    SEC_PKCS12EnableCipher(PKCS12_RC4_40, 1);
    SEC_PKCS12EnableCipher(PKCS12_RC4_128, 1);
    SEC_PKCS12EnableCipher(PKCS12_RC2_CBC_40, 1);
    SEC_PKCS12EnableCipher(PKCS12_RC2_CBC_128, 1);
    SEC_PKCS12EnableCipher(PKCS12_DES_56, 1);
    SEC_PKCS12EnableCipher(PKCS12_DES_EDE3_168, 1);
    SEC_PKCS12SetPreferredCipher(PKCS12_DES_EDE3_168, 1);
}

PRUintn P12U_Init(char *dir, char *dbprefix)
{
    SECStatus rv;
    PK11_SetPasswordFunc(SECU_GetModulePassword);

    PR_Init(PR_SYSTEM_THREAD, PR_PRIORITY_NORMAL, 1);
    rv = NSS_Initialize(dir, dbprefix, dbprefix, "secmod.db", 0);
    if (rv != SECSuccess)
		return -1;

    /* setup unicode callback functions */
    PORT_SetUCS2_ASCIIConversionFunction(p12u_ucs2_ascii_conversion_function);
    /* use the defaults for UCS4-UTF8 and UCS2-UTF8 */

    p12u_EnableAllCiphers();

    return 0;
}

SECStatus P12U_InitSlot(PK11SlotInfo *slot, secuPWData *slotPw)
{
    SECStatus rv;

    /*	New databases, initialize keydb password. */
    if (PK11_NeedUserInit(slot))
	{
		rv = SECU_ChangePW(slot,
						(slotPw->source == PW_PLAINTEXT) ? slotPw->data : 0,
						(slotPw->source == PW_FROMFILE) ? slotPw->data : 0);
		if (rv != SECSuccess)
		    return SECFailure;
    }

    if (PK11_Authenticate(slot, PR_TRUE, slotPw) != SECSuccess)
	{
		PORT_SetError(SEC_ERROR_USER_CANCELLED);
		// pk12uErrno = PK12UERR_USER_CANCELLED;
		return SECFailure;
    }

    return SECSuccess;
}

/*
 *
 */
SECItem *P12U_GetP12FilePassword(PRBool confirmPw, secuPWData *p12FilePw)
{
    char *p0 = NULL, *p1 = NULL;
    SECItem *pwItem = NULL;

    if (p12FilePw == NULL || p12FilePw->source == PW_NONE)
	{
		for (;;)
		{
			p0 = SECU_GetPasswordString(NULL,
							"Enter password for PKCS12 file: ");
			if (!confirmPw)
				break;
			p1 = SECU_GetPasswordString(NULL, "Re-enter password: ");
			if (PL_strcmp(p0, p1) == 0)
				break;
		}
    }

	else if (p12FilePw->source == PW_FROMFILE)
		p0 = SECU_FilePasswd(NULL, PR_FALSE, p12FilePw->data);

	else			/* Plaintext */
		p0 = p12FilePw->data;

    pwItem = SECITEM_AllocItem(NULL, NULL, PL_strlen(p0) + 1);
    memcpy(pwItem->data, p0, pwItem->len);

	if (p12FilePw == NULL || p12FilePw->source == PW_NONE || p12FilePw->source == PW_FROMFILE)
	{
		PORT_Memset(p0, 0, PL_strlen(p0));
		PORT_Free(p0);

		PORT_Memset(p1, 0, PL_strlen(p1));
		PORT_Free(p1);
	}

    return pwItem;
}

static void p12u_WriteToExportFile(void *arg, const char *buf, unsigned long len)
{
    p12uContext *p12cxt = arg;
    int writeLen;

    if(!p12cxt || (p12cxt->error == PR_TRUE))
		return;

    if(p12cxt->file == NULL)
	{
		p12cxt->errorValue = SEC_ERROR_PKCS12_UNABLE_TO_WRITE;
		p12cxt->error = PR_TRUE;
		return;
    }

    writeLen = PR_Write(p12cxt->file, (unsigned char *)buf, (int32)len);

    if(writeLen != (int)len)
	{
		PR_Close(p12cxt->file);
		PR_Free(p12cxt->filename);
		p12cxt->filename = NULL;
		p12cxt->file = NULL;
		p12cxt->errorValue = SEC_ERROR_PKCS12_UNABLE_TO_WRITE;
		p12cxt->error = PR_TRUE;
    }
}

static void p12u_DestroyExportFileInfo(p12uContext **exp_ptr, PRBool removeFile)
{
    if(!exp_ptr || !(*exp_ptr))
		return;

    if((*exp_ptr)->file != NULL)
		PR_Close((*exp_ptr)->file);

    if((*exp_ptr)->filename != NULL)
	{
		if(removeFile)
		    PR_Delete((*exp_ptr)->filename);
		PR_Free((*exp_ptr)->filename);
    }

    PR_Free(*exp_ptr);
    *exp_ptr = NULL;
}

static PRBool p12u_OpenExportFile(p12uContext *p12cxt, PRBool fileRead)
{
    if(!p12cxt || !p12cxt->filename)
		return PR_FALSE;

    if(fileRead)
		p12cxt->file = PR_Open(p12cxt->filename,
								 PR_RDONLY, 0400);
    else
		p12cxt->file = PR_Open(p12cxt->filename,
								 PR_CREATE_FILE | PR_RDWR | PR_TRUNCATE,
								 0600);

    if(!p12cxt->file)
	{
		p12cxt->error = PR_TRUE;
		PR_SetError(SEC_ERROR_NO_MEMORY, 0);
		return PR_FALSE;
	}

    return PR_TRUE;
}

static p12uContext *p12u_InitFile(PRBool fileImport, char *filename)
{
    p12uContext *p12cxt;
    PRBool fileExist;

	if(fileImport)
		fileExist = PR_TRUE;
	else
		fileExist = PR_FALSE;

	p12cxt = (p12uContext *)PORT_ZAlloc(sizeof(p12uContext));
	if(!p12cxt)
	{
		PR_SetError(SEC_ERROR_NO_MEMORY, 0);
		return NULL;
	}

    p12cxt->error = PR_FALSE;
    p12cxt->errorValue = 0;
    // p12cxt->filename = strdup(filename);
	p12cxt->filename = PORT_Strdup(filename);
    if(!p12u_OpenExportFile(p12cxt, fileImport))
	{
		PR_SetError(p12cxt->errorValue, 0);
		p12u_DestroyExportFileInfo(&p12cxt, PR_FALSE);
		return NULL;
	}

    return p12cxt;
}


HRESULT P12U_ExportPKCS12Object(CERTCertificate *cert, char *outfile, PK11SlotInfo *inSlot,
												secuPWData *slotPw, secuPWData *p12FilePw)
{
    SEC_PKCS12ExportContext *p12ecx = NULL;
    SEC_PKCS12SafeInfo *keySafe = NULL, *certSafe = NULL;
    SECItem *pwitem = NULL;
    p12uContext *p12cxt = NULL;
    PK11SlotInfo* slot = NULL;
	HRESULT res = S_FALSE;
	
    if (P12U_InitSlot(inSlot, slotPw) != SECSuccess)
		goto done;

    /*	Password to use for PKCS12 file.  */
    pwitem = P12U_GetP12FilePassword(PR_TRUE, p12FilePw);
	if (!pwitem)
		goto done;

    p12cxt = p12u_InitFile(PR_FALSE, outfile); 
	if (!p12cxt)
		goto done;

	slot = cert->slot;
	if (!slot)
		goto done;

    p12ecx = SEC_PKCS12CreateExportContext(NULL, NULL, slot, slotPw);
    if(!p12ecx)
		goto done;

	if(SEC_PKCS12AddPasswordIntegrity(p12ecx, pwitem, SEC_OID_SHA1)
					       != SECSuccess)
		goto done;

	keySafe = SEC_PKCS12CreateUnencryptedSafe(p12ecx);
	if (PK11_IsFIPS())
		certSafe = keySafe;
	else
		certSafe = SEC_PKCS12CreatePasswordPrivSafe(p12ecx, pwitem,
							SEC_OID_PKCS12_V2_PBE_WITH_SHA1_AND_40_BIT_RC2_CBC);

	if(!certSafe || !keySafe)
		goto done;

	if(SEC_PKCS12AddCertAndKey(p12ecx, certSafe, NULL, cert,
							CERT_GetDefaultCertDB(), keySafe, NULL, PR_TRUE, pwitem,
							SEC_OID_PKCS12_V2_PBE_WITH_SHA1_AND_3KEY_TRIPLE_DES_CBC)
							!= SECSuccess)
		goto done;

	if(SEC_PKCS12Encode(p12ecx, p12u_WriteToExportFile, p12cxt)
							!= SECSuccess)
		goto done;


	res = S_OK;

done:
    SEC_PKCS12DestroyExportContext(p12ecx);

	if (res == S_OK)
	    p12u_DestroyExportFileInfo(&p12cxt, PR_FALSE);
	else
	    p12u_DestroyExportFileInfo(&p12cxt, PR_TRUE);

    if(pwitem)
        SECITEM_ZfreeItem(pwitem, PR_TRUE);

	return res;
}

