// NetscapeUtilTest.cpp : Defines the entry point for the console application.
//

#include "NetscapeUtil.h"

int main()
{
	int size = 0;
	PCERT_DESCR *list = NULL;
	int i;
	char filename[100];
	HRESULT res = S_FALSE;
	char *tempNetDir = NULL;

	res = NetscapeUtilStart(&tempNetDir);
	if (res != S_OK)
		return 1;

	list = axGetNetscapeCertList(&size, tempNetDir, "SecureXML");

	for (i = 0; i < size; i++)
	{
		printf("%s\n", list[i]->subject);
		printf("%s\n", list[i]->notAfter);
		sprintf(filename, "C:\\Temp\\ExportCert%d.pfx", i);
		res = axExportNetscapeCert(filename, list[i]->serialNumber, "infomosaic", tempNetDir, "SecureXML");
		if (res != S_OK)
			printf("Export %s Failed\n\n", filename);
		else
			printf("Exported %s successfully\n\n", filename);
	}


	// Cleanup
	if (list)
	{
		for (i = 0; i < size; i++)
		{
			free(list[i]->certificate);
			free(list[i]);
		}
		free(list);
	}

	res = NetscapeUtilStop(tempNetDir);
	if (res != S_OK)
		return 1;

	return 0;
}

