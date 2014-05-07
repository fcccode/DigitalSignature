#include "StdAfx.h"
#include "CAMClient.h"
#include <stdio.h>

#if __cplusplus
extern "C" {
#endif

#include <securexml/utils.h>
#include <securexml/errors.h>

#if __cplusplus
}
#endif

#include <securexml/base64.h>
#include <securexml/DebugLog.h>



#define SEND_ERROR(stat,asc1,asc2) { *dest_status= stat; strcpy ((char*)dest_cert_ascii_bfr, (char*)asc1); strcat ((char*)dest_cert_ascii_bfr, (char*)asc2), strcpy ((char*)dest_ca_msg_bfr, ""); return S_OK; }
char *g_log_name= NULL;		// expected by libcore

CCAMClient::CCAMClient(void)
{
	// init internal state
	ca_ptr_count=0;
	tmpfile_count= 0;
	camServerPortNumber = 7777;
}

CCAMClient::~CCAMClient(void)
{
}

HRESULT CCAMClient::validate(unsigned char * cam_hostname,
									  unsigned char * cert_buffer,
									  int cert_buffer_size,
									  unsigned char * aa_id, 
									  int * dest_status, 
									  unsigned char **dest_cert_ascii_bfr,
									  int *destCertAsciiBufSize,
									  unsigned char **dest_ca_msg_bfr,
									  int *destCaMsgBufSize)
{
	int i;
	DWORD encodedDataSize;
	BYTE *encodedDataPtr;
	// ----------
	// construct the outgoing CAM request
//DebugBreak();
	AaCamValidate val;

	val.msg_type= AA_VALIDATE;
	val.aa_id.data= aa_id;
	val.aa_id.size= strlen((char*)aa_id);
	val.cert.data= (unsigned char*) cert_buffer;
	val.cert.size= cert_buffer_size;

	BinString *send_wrap= serialize(&val, sizeof(AaCamValidate), AaCamValidateBSC);


	// ----------
	// connect to CAM, send request

	SOCKET sock= my_connect((char*)cam_hostname);
	if (sock==INVALID_SOCKET)
	{
		*dest_status= CA_REQ_BAD; 
		delBinString (send_wrap);
		return S_OK;
	}

	i= send_header(sock, send_wrap->size);
	if (i<0) 
	if (sock==INVALID_SOCKET)
	{
		*dest_status= CA_REQ_BAD; 
		delBinString (send_wrap);
		return S_OK;
		//SEND_ERROR(10, "<> unable to send to specified CAM ", cam_hostname);
	}

	i= send_bs(sock, send_wrap);
	if (i<=0) 
	if (sock==INVALID_SOCKET)
	{
		*dest_status= CA_REQ_BAD; 
		delBinString (send_wrap);
		return S_OK;
		//SEND_ERROR(10, "<> unable to send request to specified CAM: ", cam_hostname);
	}

	// ----------
	// receive response and close socket

	BinString *resp_wrap= read_msg(sock);
	if (!resp_wrap) 
	{
		*dest_status= CA_REQ_BAD; 
		delBinString (send_wrap);
		return S_OK;
		//SEND_ERROR(10, "<> unable to read response from specified CAM: ", cam_hostname);
	}
//DebugBreak();
	CamAaValidate *ptr= (CamAaValidate*) deserialize(resp_wrap, sizeof(CamAaValidate), CamAaValidateBSC);

//	shutdown (sock, SD_BOTH);
	shutdown (sock, 0x02);
#ifdef WIN32
	closesocket (sock);
#else
	close(sock);
#endif

	// ----------
	// copy result to dest

	*dest_status= ptr->status;

	if (*dest_cert_ascii_bfr != NULL)
		zFree(*dest_cert_ascii_bfr);
	*destCertAsciiBufSize = ptr->cert_ascii.size;
	*dest_cert_ascii_bfr = (unsigned char *)zMalloc(ptr->cert_ascii.size);
	copy_mem_out(&ptr->cert_ascii, *dest_cert_ascii_bfr);

	if (*dest_ca_msg_bfr != NULL)
		zFree(*dest_ca_msg_bfr);

	// The data is binary, so lets base64 encode it
//#ifdef _DEBUG_
//	FILE *hFile;
//	char *szTempName = "C:\\temp\\CamRespBeforeEncode.bin";
//	hFile = fopen((const char*)szTempName,"wb");
//	fwrite(ptr->ca_signed_msg.data, 1, ptr->ca_signed_msg.size, hFile);
//	fclose(hFile);
//#endif
	//Lets find out the true size of the response data

	//char * contentLengthPtr = strstr((const char *)ptr->ca_signed_msg.data, "Content-length: ");
	//char * lengthPtr = NULL;
	char *respPtr= (char *)ptr->ca_signed_msg.data;
	int length= ptr->ca_signed_msg.size;
	//if (contentLengthPtr != NULL)
	//{
	//	lengthPtr = contentLengthPtr + strlen((const char *)"Content-length: ");
	//	sscanf((const char *)lengthPtr, "%d\r\n", &length);
	//	respPtr = strstr(lengthPtr, "\r\n\r\n");
	//	respPtr += 4;
	//}

	encodedDataSize = base64encodeSize(length);
	encodedDataPtr = (BYTE *)zMalloc(encodedDataSize + 1);
	encodedDataSize = base64encode((unsigned char *)respPtr, length, encodedDataPtr, encodedDataSize + 1);
	*dest_ca_msg_bfr = (unsigned char *)encodedDataPtr;
	*destCaMsgBufSize = encodedDataSize;

	//*destCaMsgBufSize = ptr->ca_signed_msg.size;
	//*dest_ca_msg_bfr = (unsigned char *)zMalloc(ptr->ca_signed_msg.size);
	//copy_mem_out(&ptr->ca_signed_msg, *dest_ca_msg_bfr);

	delBinString (send_wrap);
	delBinString (resp_wrap);

	return S_OK;
}


// ==================================================================
// INTERNAL SUPPORT
// ==================================================================

int CCAMClient::full_recv(SOCKET sock, char *dest, int size)
{
	int have=0, got=1;

	while ( (have<size) && (got>0) ) {
		got= recv(sock, dest+have, (size-have), 0);
		have+= got;
	}

	return have;
}

// --------------

BinString* CCAMClient::newBinString(int size, char *name)
{
  if (size==0) return NULL;

  // given the size of the data string, return a BinString structure with sufficient memory allocated
  BinString *me = (BinString*)zMalloc(sizeof(BinString));

  // extern memory_object g_mem; is included at bottom of memory.hpp
  me->size = size;
  me->data = (unsigned char*)zMalloc(size);
  return(me);
}

void CCAMClient::delBinString(BinString *me)
{
  if (me == NULL) return;
  zFree(me->data);
  zFree(me);
}

// --------------

BinString* CCAMClient::serialize(void *source, int size_struct, int num_binstrings)
{
	int i, ttl_size;
	BinString *base, *answer;
	unsigned char *output_ptr;

	// set pointer to base of array of BinStrings within the user struct
	base= (BinString*) ((char*)source + size_struct - num_binstrings*sizeof(BinString));

	// calculate the total size needed in output structure
	ttl_size= size_struct;
	for (i=0; i<num_binstrings; i++) ttl_size+= base[i].size;

	// allocate output and copy over existing flat structure
	answer= newBinString(ttl_size, "serialize flat allocation");
	memcpy (answer->data, source, size_struct);

	// now append the attached BinString data
	output_ptr= answer->data + size_struct;
	for (i=0; i<num_binstrings; i++) {
		if ((base[i].size==0)||(!base[i].data)) continue;

		memcpy (output_ptr, base[i].data, base[i].size);
		output_ptr+= base[i].size;
	}

	// finally, "null-out" the useless data pointers in the serialized struct
	// (make sure local memory pointers do not make it into the serialized data)
	base= (BinString*) ((char*)answer->data + size_struct - num_binstrings*sizeof(BinString));
	for (i=0; i<num_binstrings; i++) base[i].data= NULL;

	return answer;
}


char* CCAMClient::deserialize(BinString *source, int size_struct, int num_binstrings)
{
	int i;
	BinString *base;
	unsigned char *data_ptr;

	// set pointer to base of array of BinStrings within the user struct
	base= (BinString*) ((char*)source->data + size_struct - num_binstrings*sizeof(BinString));

	// walk through the BinStrings, updating their data pointers
	data_ptr= source->data + size_struct;
	for (i=0; i<num_binstrings; i++) {
		base[i].data= data_ptr;
		data_ptr+= base[i].size;
	}

	return (char*) source->data;
}

// --------------------------------
// QUERY IP NUMBER

unsigned long get_ip_from_hostname(char *hostname)
{
	unsigned long answer;
	char *x= (char*) &answer;
	hostent *lookup_response;
	int i;

	// handle NULL => use local loopback

	if (!hostname || !*hostname)
	{
		x[0]= 127; x[1]= x[2]= 0; x[3]= 1;
		return answer;
	}

  	// handle numeric IP

	if ( (*hostname>='0') && (*hostname<='9') )
	{
		int temp[4];
		i= sscanf (hostname, "%d.%d.%d.%d", &temp[0], &temp[1], &temp[2], &temp[3]);
		if (i!=4) return -1;
		for (i=0; i<4; i++) x[i]= temp[i];

		return answer;
	}

	// handle real hostname

	lookup_response=gethostbyname(hostname);
	if (!lookup_response) return -2;
	for (i=0; i<4; i++) x[i]=lookup_response->h_addr[i];

	return answer;
}


// -------------

SOCKET CCAMClient::my_connect(char *hostname)
{
	int i;

	// start up sockets
	
	WORD ver= MAKEWORD (2,0);
#ifdef WIN32
	WSAData d;
#else
	WSADATA d;
#endif
	WSAStartup(ver, &d);

	// resolve given hostname

	unsigned long dest_ip = ::get_ip_from_hostname(hostname);

    SOCKET sock;
#ifdef WIN32
    struct sockaddr_in addr;
#else
    SOCKADDR_IN addr;
#endif

    sock = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family= AF_INET;
    addr.sin_port= htons(camServerPortNumber);
    addr.sin_addr.S_un.S_addr= dest_ip;

    // connect
    i = connect(sock, (struct sockaddr*) &addr, sizeof(addr));
	if (i!=0) return INVALID_SOCKET;

    int timeout_ms=10000;
	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*) &timeout_ms, sizeof(timeout_ms));
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout_ms, sizeof(timeout_ms));

	return sock;
}


// -------------

int CCAMClient::send_header(SOCKET sock, int size)
{
	xmit_header header;

	header.header_proto_ver= 3;
	header.header_msg_len = size;

	int i= send(sock, (char*)&header, sizeof(header), 0);
	return (i<=0)? -1 : 0;
}


int CCAMClient::read_header(SOCKET sock)
{
	xmit_header header;

	int i= full_recv(sock, (char*)&header, sizeof(header));
	if (i<sizeof(header)) return -1;

	return header.header_msg_len;
}

BinString* CCAMClient::read_msg(SOCKET sock)
{
	int i,s= read_header(sock);
	if (s<=0) return NULL;

	BinString *answer= newBinString(s, "read bfr");
	i= full_recv(sock, (char*)answer->data, s);
	if (i!=s) { delBinString(answer); return NULL; }

	return answer;
}

int CCAMClient::send_bs(SOCKET sock, BinString *s)
{
	unsigned int i= send(sock, (char*)s->data, s->size, 0);
	return (i==s->size)? i : -1;
}

// -------------

int CCAMClient::read_file(char *fname, char *bfr, int maxsize)
{
	int got;
	FILE *fil= fopen(fname, "rb");
	if (!fil) return -1;

	got= fread(bfr, 1, maxsize, fil);
	fclose(fil);

	return got;
}

// --------------

void CCAMClient::copy_str_out(BinString *src, unsigned char *dest)
{
	if (!src || !src->data || !dest) return;
	int i;

	char *p= (char*)dest;

	for (i=0; i<(int)src->size; i++) {
		if (src->data[i] != 0x0a) *p++= src->data[i];
		else { *p++=13; *p++=10; }
	}
	*p++= 0;
}

void CCAMClient::copy_mem_out(BinString *src, unsigned char *dest)
{
	if (!src || !src->data || !dest) return;

	memcpy (dest, src->data, src->size);
}
