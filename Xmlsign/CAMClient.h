
#ifdef WIN32
#pragma once
#endif

#ifdef UNIX
#include <securexml/DebugLog.h>
#include <winsock.h>
#endif

// local types
#include "CamCom/aa_cam.h"

typedef struct {
	__int32		header_proto_ver;
	__int32		header_msg_len;	    // not including this header
} xmit_header;

#define BSCHAR(X) (char*)X.data
#define BSPCHAR(X) (char*)X->data

class CCAMClient
{
public:
	CCAMClient(void);
	~CCAMClient(void);
	HRESULT validate(	unsigned char * cam_hostname, 
						unsigned char * cert_buffer, 
						int cert_buf_len, 
						unsigned char * aa_id, 
						int * dest_status, 
						unsigned char **dest_cert_ascii_bfr, 
						int *destCertAsciiBufSize, 
						unsigned char **dest_ca_msg_bfr,
						int *destCaMsgBufSize);
	USHORT	camServerPortNumber;

private:
//	char cert_store[65535];

	// -------------------------
	// internal object state

	BinString *ca_ptr_store[512];
	int ca_ptr_count;

	BinString *tmpfile_store[512];
	int tmpfile_count;



	// -------------------------
	// helper routines

	int full_recv(SOCKET sock, char *dest, int size);

	BinString* newBinString(int size, char *name);
	void delBinString(BinString *me);

	BinString* serialize(void *source, int size_struct, int num_binstrings);
	char* deserialize(BinString *source, int size_struct, int num_binstrings);

	SOCKET my_connect(char *hostname);				// returns INVALID_SOCKET on failure

	int send_header(SOCKET sock, int size);		// returns -1 on failure
	int read_header(SOCKET sock);				// returns # bytes to read
	BinString* read_msg(SOCKET sock);			// returns NULL on error
	int send_bs(SOCKET socket, BinString *s);	// returns -1 on failure

	int read_file(char *fname, char *bfr, int maxsize);	// returns actual size or -1

	void copy_str_out(BinString *src, unsigned char *dest);
	void copy_mem_out(BinString *src, unsigned char *dest);
};
