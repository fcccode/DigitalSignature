// Pem2PfxUtilTest.c : Defines the entry point for the console application.
//

#include "pem2pfx.h"

#ifdef _DEBUG
int errno = 0;
#endif


int main()
{
	HRESULT res;
	char *pfxFile = Pem2Pfx("C:\\Temp\\Debug\\ExportCert0.pem", "info");

	free(pfxFile);
	return 0;
}