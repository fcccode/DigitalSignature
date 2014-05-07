// This is the main DLL file.

#include "NetscapeUtil.h"

static CERTCertList *GetCerts(PK11SlotInfo *slot, secuPWData *pwdata)
{
	CERTCertList *list = NULL;

    if (slot == NULL)
		// If there is no slot, get the defaults, I guess
		list = PK11_ListCerts(PK11CertListUnique, pwdata);

	else
		// list = getSlotCerts(handle, name, slot, raw, ascii, pwdata);
		list = PK11_ListCertsInSlot(slot);

	return list;
}

// D300C133-A6F6-4FB4-A734-4865FBF5A3B1
//
//	typedef struct {
//		unsigned long  Data1;
//		unsigned short Data2;
//		unsigned short Data3;
//		byte           Data4[ 8 ];
//	} GUID;
void GuidToString(GUID *guid, char *guidStr)
{
	unsigned short data1, data2, data3, data4, data5, data6, data7, data8;
	data1 = *(unsigned char *)&guid->Data4[0];
	data2 = *(unsigned char *)&guid->Data4[1];
	data3 = *(unsigned char *)&guid->Data4[2];
	data4 = *(unsigned char *)&guid->Data4[3];
	data5 = *(unsigned char *)&guid->Data4[4];
	data6 = *(unsigned char *)&guid->Data4[5];
	data7 = *(unsigned char *)&guid->Data4[6];
	data8 = *(unsigned char *)&guid->Data4[7];

	sprintf(guidStr, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", 
			guid->Data1, 
			guid->Data2,
			guid->Data3,
			data1, data2, data3, data4,
			data5, data6, data7, data8);

}

BOOL copyNetscapeDatabase(char *netscapeDir, char *destDir, char *db)
{
	char origFile[MAX_PATH];
	char destFile[MAX_PATH];
	BOOL ret = FALSE;

	// Create original database file name
	sprintf(origFile, "%s\\%s", netscapeDir, db);

	// Create destination database file name
	sprintf(destFile, "%s\\%s", destDir, db);

	// Now copy the database file with replacement enforced
	ret = CopyFile(origFile, destFile, FALSE);
	return ret;
}

HRESULT copyNetscapeDatabases(char *tempPath)
{
	char netscapeDir[MAX_PATH];
	char tempPath2[MAX_PATH];
	HRESULT res;
	HANDLE hd;
	WIN32_FIND_DATA FindFileData;
	BOOL fileCopyRet;
	GUID guid;
	char guidStr[50];

	// Get the Temp Path for the user
    GetTempPath((DWORD)MAX_PATH, tempPath);

	// Save the Temp Path to be able to use later.
	sprintf(tempPath2, "%s", tempPath);

	CoCreateGuid(&guid);
	GuidToString(&guid, guidStr);
	res = StringCbCat(tempPath, MAX_PATH, guidStr);
	if (res != S_OK)
		goto done;

	// Try to open the directory for read. If it doesn't exist, create it. If it exists, close the handle.
	hd = CreateFile(tempPath, 0, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (hd == INVALID_HANDLE_VALUE)
	{
		if (CreateDirectory(tempPath, NULL) == 0)
			goto done;
	}
	else
		CloseHandle(hd);

	// Get the original Temp Path
	res = StringCbCopy(netscapeDir, MAX_PATH, tempPath2);
	if (res != S_OK)
		goto done;

	// Move up the directory path and go into Application Data\Mozilla
	res = StringCbCat(netscapeDir, MAX_PATH, "..\\..\\Application Data\\Mozilla\\Profiles\\default\\");
	if (res != S_OK)
		goto done;

	sprintf(tempPath2, "%s*.slt", netscapeDir);

	// Search the directory for a ".slt" directory
	hd = FindFirstFile(tempPath2, &FindFileData);
	if (hd == INVALID_HANDLE_VALUE)
		goto done;
	else
		FindClose(hd);

	// Add the directory name to netscapeDir
	res = StringCbCat(netscapeDir, MAX_PATH, FindFileData.cFileName);
	if (res != S_OK)
		goto done;

	// Now, netscapeDir contains the netscape Directory
	//  Copy the database files from that directory into tempPath
	fileCopyRet = copyNetscapeDatabase(netscapeDir, tempPath, "cert8.db");
	if (fileCopyRet == FALSE)
		goto done;
	fileCopyRet = copyNetscapeDatabase(netscapeDir, tempPath, "key3.db");
	if (fileCopyRet == FALSE)
		goto done;
	fileCopyRet = copyNetscapeDatabase(netscapeDir, tempPath, "secmod.db");
	if (fileCopyRet == FALSE)
		goto done;

	return S_OK;

done:

	return S_FALSE;
}

HRESULT copySerialNumber(char *dest, SECItem *orig)
{
	HRESULT res;
	char *base64Data = BTOA_DataToAscii(orig->data, orig->len);

	// base64encode(orig->data, orig->len, dest, base64encodeSize(orig->len));

	res = StringCbCopy(dest, 256, base64Data);

	// Free up the space after copy
	PORT_Free(base64Data);

	return res;
}

SECStatus copyValidity(char *dest, SECItem *orig)
{
	int64 time;
	SECStatus rv;
    PRExplodedTime pTime;
	int mon;

	rv = DER_UTCTimeToTime(&time, orig);
	if (rv != SECSuccess)
		return rv;

	// Convert to UTC Time
    PR_ExplodeTime(time, PR_GMTParameters, &pTime);

	mon = pTime.tm_month + 1;
	sprintf(dest, "%02d/%02d/%d  %02d:%02d",
				  (pTime.tm_month + 1), pTime.tm_mday, pTime.tm_year,
				  pTime.tm_hour, pTime.tm_min);

	return rv;
}

void copyShortSubject(WCHAR *shortSub, WCHAR *subject)
{
	WCHAR *ptr = wcsstr(subject, L"CN=");
	WCHAR *ptr2;
	if (ptr)
	{
		ptr += 3;
		ptr2 = wcsstr(ptr, L",");
		if (ptr2 == NULL)
			ptr2 = subject + wcslen(subject);
		memcpy(shortSub, ptr, (ptr2 - ptr)*2);
		shortSub[ptr2 - ptr] = L'\0';
		return;
	}
    
	ptr = wcsstr(subject, L"E=");
	if (ptr)
	{
		ptr += 2;
		ptr2 = wcsstr(ptr, L",");
		if (ptr2 == NULL)
			ptr2 = subject + wcslen(subject);
		memcpy(shortSub, ptr, (ptr2 - ptr)*2);
		shortSub[ptr2 - ptr] = '\0';
		return;
	}

	ptr = wcsstr(subject, L"OU=");
	if (ptr)
	{
		ptr += 3;
		ptr2 = wcsstr(ptr, L",");
		if (ptr2 == NULL)
			ptr2 = subject + wcslen(subject);
		memcpy(shortSub, ptr, (ptr2 - ptr)*2);
		shortSub[ptr2 - ptr] = '\0';
		return;
	}
	ptr = wcsstr(subject, L"O=");
	if (ptr)
	{
		ptr += 2;
		ptr2 = wcsstr(ptr, L",");
		if (ptr2 == NULL)
			ptr2 = subject + wcslen(subject);
		memcpy(shortSub, ptr, (ptr2 - ptr)*2);
		shortSub[ptr2 - ptr] = '\0';
		return;
	}
}

/*
 * axGetNetscapeCertList
 * @asize:		(out) size of array
 * @tempNetDir:	(in) the temporary netscape directory returned by NetscapeUtilStart call
 * @dbPass:		(in) the password to access the Netscape database
 *
 * Returns list of available certificates in Netscape Certificate Store
 * array of pointers to #PCERT_DESCR, size of the array stored in @asize
 *
 * Returns: array of #PCERT_DESCR
 */

PCERT_DESCR *axGetNetscapeCertList(int *asize, char *tempNetDir, char *dbPass)
{
	PCERT_DESCR *retArray = NULL;
	PCERT_DESCR certInArray = NULL;
	SECStatus rv;
    CERTCertDBHandle *certHandle;
    char *slotname = "internal";
    PK11SlotInfo *slot = NULL;
    secuPWData pwdata = { PW_NONE, 0 };
    char *name = NULL;
	CERTCertList *certs = NULL;
    CERTCertListNode *node;
	int i = 0, count = 0;
	HRESULT res;
	BOOL err = TRUE;


	// Initialize the count to "ZERO"
	*asize = 0;

	// The databases are already copied in start function. Just check whether the string is not NULL
	if (tempNetDir == NULL)
		goto done;

    certHandle = CERT_GetDefaultCertDB();
    if (PL_strcmp(slotname, "internal") == 0)
		slot = PK11_GetInternalKeySlot();
    else if (slotname != NULL)
		slot = PK11_FindSlotByName(slotname);

	if (dbPass == NULL)
		pwdata.source = PW_NONE;
	else
		pwdata.source = PW_PLAINTEXT;
	pwdata.data = dbPass;

	certs = GetCerts(slot, &pwdata);
	// Just find the number of certificates here
	count = 0;
	for (node = CERT_LIST_HEAD(certs); !CERT_LIST_END(node, certs);
										node = CERT_LIST_NEXT(node))
	{
		SECKEYPrivateKey *privKey = PK11_FindKeyByAnyCert(node->cert, &pwdata);
		if (privKey == NULL)
			continue;
		SECKEY_DestroyPrivateKey(privKey);
		count++;
	}

	if (count == 0)
		goto done;

	retArray = (PCERT_DESCR *) malloc(sizeof(PCERT_DESCR) * count);
	for (i = 0; i < count; i++)
		retArray[i] = NULL;
	i = 0;
	for (node = CERT_LIST_HEAD(certs); !CERT_LIST_END(node, certs);
										node = CERT_LIST_NEXT(node))
	{
		char *temp;
		WCHAR issuer[256];
		char *asciiCertName=NULL;
		WCHAR bstrCertName[512];

		SECKEYPrivateKey *privKey = PK11_FindKeyByAnyCert(node->cert, &pwdata);
		if (privKey == NULL)
			continue;
		SECKEY_DestroyPrivateKey(privKey);

		// Go through each of the certificates and add them to retArray
		certInArray = (PCERT_DESCR) malloc(sizeof (CERT_DESCR));

		// Copy the subject into certificate's subject
		memset(bstrCertName, 0, 512 * sizeof(WCHAR));
		asciiCertName = CERT_NameToAscii(&node->cert->subject);
		MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)asciiCertName, strlen((const char *)asciiCertName), bstrCertName, 512);
		res = StringCbCopyW(certInArray->subject, 512, bstrCertName);
		PORT_Free(asciiCertName);
		memset(bstrCertName, 0, 512 * sizeof(WCHAR));

		if (res != S_OK)
			goto done;

		// Copy the Short Subject name from the subject name
		copyShortSubject(certInArray->shortSubject, certInArray->subject);

		// Copy the issuer into certificate's issuer
		asciiCertName = CERT_NameToAscii(&node->cert->issuer);
		MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)asciiCertName, strlen((const char *)asciiCertName), bstrCertName, 512);
		res = StringCbCopyW(issuer, 512, bstrCertName);
		PORT_Free(asciiCertName);
		if (res != S_OK)
			goto done;

		// Copy the Short Issuer name from the issuer name
		copyShortSubject(certInArray->issuer, issuer);

		// Copy the serialNumber into certificate's serialNumber
		res = copySerialNumber(certInArray->serialNumber, &node->cert->serialNumber);
		if (res != S_OK)
			goto done;

		// Copy the expiration date into certificate's expiration
		rv = copyValidity(certInArray->notAfter, &node->cert->validity.notAfter);
		if (rv != SECSuccess)
			goto done;

		// Copy the whole X509 data in base64 encoded format
		temp = BTOA_DataToAscii(node->cert->derCert.data, node->cert->derCert.len);
		certInArray->certificate = (char *)malloc((strlen(temp) + 1) * sizeof(char));
		sprintf(certInArray->certificate, "%s", temp);
		PORT_Free(temp);

		retArray[i] = certInArray;
		i++;
	}

	*asize = count;
	err = FALSE;

done:
	// Need to clear out the certificates in all cases
	CERT_DestroyCertList(certs);

	if (slot)
		PK11_FreeSlot(slot);

	if (err)
	{
		*asize = 0;
		if (retArray)
			free(retArray);
		return NULL;
	}

	return retArray;
}


HRESULT axExportNetscapeCert(char *fileName, char *serialNum, char *passwd, char *tempNetDir, char *dbPass)
{
    char *slotname = "internal";
	char *dbprefix = "";
    PK11SlotInfo *slot = NULL;
	CERTCertList *certs = NULL;
	CERTCertListNode *node = NULL;
    secuPWData pwdata = { PW_NONE, 0 };
	secuPWData pwslot = { PW_NONE, 0 };
	BOOL err = TRUE;
	SECStatus rv;
	PRUintn initRet;
	char certSerial[256];
	HRESULT res = S_FALSE;

	// The databases are already copied in start function. Just check whether the string is not NULL
	if (tempNetDir == NULL)
		goto done;

	// Initialize the P12
	initRet = P12U_Init(tempNetDir, dbprefix);
	if (initRet != 0)
		goto done;

    if (PL_strcmp(slotname, "internal") == 0)
		slot = PK11_GetInternalKeySlot();
    else if (slotname != NULL)
		slot = PK11_FindSlotByName(slotname);

	if (!slot)
		goto done;

	certs = GetCerts(slot, &pwdata);

	// For exporting the certificate, use the given password
	pwdata.source = PW_PLAINTEXT;
	pwdata.data = passwd;

	// For accessing the database, use the following password
	if (dbPass == NULL)
		pwslot.source = PW_NONE;
	else
		pwslot.source = PW_PLAINTEXT;
	pwslot.data = dbPass;

	for (node = CERT_LIST_HEAD(certs); !CERT_LIST_END(node, certs);
										node = CERT_LIST_NEXT(node))
	{
		res = copySerialNumber(certSerial, &node->cert->serialNumber);
		if (res != S_OK)
			goto done;

		if (PL_strcmp(certSerial, serialNum) == 0)
		{
			res = P12U_ExportPKCS12Object(node->cert, fileName, node->cert->slot, &pwslot, &pwdata);
			if (res != S_OK)
				goto done;
			break;
		}
	}

	err = FALSE;

done:
	// Need to clear out the certificates in all cases
	CERT_DestroyCertList(certs);

	if (slot)
		PK11_FreeSlot(slot);

	if (err)
		return S_FALSE;

	return S_OK;
}

HRESULT NetscapeUtilStart(char **tempNetDir)
{
	HRESULT res;
	SECStatus rv;

	*tempNetDir = (char *)malloc(MAX_PATH * sizeof(char));

	res = copyNetscapeDatabases(*tempNetDir);

	// Initialize the password function to NULL
	PK11_SetPasswordFunc(SECU_GetModulePassword);

	//  Initialize NSPR and NSS
    //PR_Init(PR_SYSTEM_THREAD, PR_PRIORITY_NORMAL, 1);
    rv = NSS_Initialize(*tempNetDir, "", "", "secmod.db", NSS_INIT_NOMODDB | NSS_INIT_READONLY);
	if (rv != SECSuccess)
		res = S_FALSE;

	return res;
}


HRESULT NetscapeUtilStop(char *tempNetDir)
{
	HANDLE hd;
	BOOL delRet;
	char fileName[MAX_PATH];

	if (tempNetDir == NULL)
		return S_OK;

	// Remove the temporary netscape directory, if it exists
	// Try to open the directory for read. If it exists, close the handle.
	hd = CreateFile(tempNetDir, 0, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (hd == INVALID_HANDLE_VALUE)
		goto done;
	else
		CloseHandle(hd);

	// We will come here only if the directory exists
	// Delete the files in the directory
	sprintf(fileName, "%s\\cert8.db", tempNetDir);
	delRet = DeleteFile(fileName);
	sprintf(fileName, "%s\\key3.db", tempNetDir);
	delRet = DeleteFile(fileName);
	sprintf(fileName, "%s\\secmod.db", tempNetDir);
	delRet = DeleteFile(fileName);

	// Now finally delete the empty directory
	delRet = RemoveDirectory(tempNetDir);

done:

	if (tempNetDir != NULL)
		free(tempNetDir);

	if (NSS_Shutdown() != SECSuccess)
		return S_FALSE;

	return S_OK;
}