#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <wincrypt.h>

#ifndef DWORD
#define DWORD unsigned long
#endif

extern void perror(char *msg);

#define CSP MS_ENHANCED_PROV

HCRYPTPROV hCryptProv;

int RAND_bytes(unsigned char *buf, int num){
	return CryptGenRandom(hCryptProv, num, buf);
}

void bn_to_le(BIGNUM *bn, unsigned char *out){

	int i;
	int size = BN_num_bytes(bn);
	char* in = malloc(size);

	BN_bn2bin(bn, in);
    /* change big endian to little endian */
    for(i=0; i<size; i++)
		out[i] = in[size-i-1];

	free(in);
}

int crypto_startup() {
    if(CryptAcquireContext(&hCryptProv, NULL, CSP, PROV_RSA_FULL,
			   CRYPT_NEWKEYSET) == FALSE) {
		//perror("CryptAcquireContext RSA");
		if(GetLastError() == NTE_EXISTS) {
			if(CryptAcquireContext(&hCryptProv, NULL, CSP, PROV_RSA_FULL, 0) == FALSE) {
					perror("Crypt AcquireContext CSP");
					return GetLastError(); /* failed to acquire context - probably
											* don't have high encryption installed! */
			}
		} 
		else {
			perror("Crypt AcquireContext !NTE_EXISTS");
			return GetLastError(); /* failed to acquire context - probably
									   * don't have high encryption installed! */
		}
	}

	return 0;
}

void crypto_shutdown() {
    if(hCryptProv)
	CryptReleaseContext(hCryptProv, 0);
    hCryptProv = 0;
}

int RSA_public_encrypt(int length, unsigned char *ptext, unsigned char *ctext, RSA *key, int pad){

    int i;
    unsigned char *pKeybuf;
    HCRYPTKEY hRsaKey;
    PUBLICKEYSTRUC *pBlob;
    RSAPUBKEY *pRPK;
    unsigned char *buf;
    DWORD dlen;
    DWORD bufsize;
	DWORD mod_size;

	if (pad != RSA_PKCS1_PADDING){
		perror("Only PKCS1_PADDING supported");
		return -1;
	}
	
	mod_size = BN_num_bytes(key->n);

    /* allocate buffer for public key blob */
    if((pBlob = malloc(sizeof(PUBLICKEYSTRUC) + sizeof(RSAPUBKEY) + mod_size)) == NULL){
		perror("Out of memory");
		return GetLastError();
	}

	memset(pBlob, 0, sizeof(PUBLICKEYSTRUC) + sizeof(RSAPUBKEY) + mod_size);

    /* allocate buffer for message encryption block */
	bufsize = (length + mod_size) << 1;
    if((buf = malloc(bufsize)) == NULL){
		perror("Out of memory");
		return GetLastError();
	}

    /* construct public key blob from host public key */
    pKeybuf = ((unsigned char*)pBlob) + sizeof(PUBLICKEYSTRUC) +
		sizeof(RSAPUBKEY);
    
	bn_to_le(key->n, pKeybuf);
	

    pBlob->bType = PUBLICKEYBLOB;
    pBlob->bVersion = 0x02;
    pBlob->reserved = 0;
    pBlob->aiKeyAlg = CALG_RSA_KEYX;
    pRPK = (RSAPUBKEY*)(((unsigned char*)pBlob) + sizeof(PUBLICKEYSTRUC));
    pRPK->magic = 0x31415352; /* "RSA1" */
    pRPK->bitlen = mod_size * 8;
    bn_to_le(key->e, &pRPK->pubexp);

    /* import public key blob into key container */
    if(CryptImportKey(hCryptProv, (void*)pBlob,
		      sizeof(PUBLICKEYSTRUC)+sizeof(RSAPUBKEY)+mod_size,
			  0, 0, &hRsaKey) == 0){
		perror("Error importing RSA key!");
		return GetLastError();
	}

    /* copy message into buffer */
    memcpy(buf, ptext, length);
    dlen = length;

    /* using host public key, encrypt the message */
    if(CryptEncrypt(hRsaKey, 0, TRUE, 0, buf, &dlen, bufsize) == FALSE){
		perror("Error encrypting using RSA key!");
		return GetLastError();
	}

    for(i = 0; i < (int)dlen; i++)
		ctext[i] = buf[dlen - i - 1]; /* make it big endian */

    CryptDestroyKey(hRsaKey);
    free(buf);
    free(pBlob);

	return dlen;
}

/* 
From MSDN, Private Key blob:
PUBLICKEYSTRUC  publickeystruc ;
RSAPUBKEY rsapubkey; 
BYTE modulus[rsapubkey.bitlen/8]; (n)
BYTE prime1[rsapubkey.bitlen/16]; (p)
BYTE prime2[rsapubkey.bitlen/16]; (q)
BYTE exponent1[rsapubkey.bitlen/16]; (dmp1)
BYTE exponent2[rsapubkey.bitlen/16]; (dmq1)
BYTE coefficient[rsapubkey.bitlen/16]; (iqmp)
BYTE privateExponent[rsapubkey.bitlen/8]; (d)

other:
public exponent (e)
*/

int RSA_private_decrypt(int length, unsigned char *ctext, unsigned char *ptext, RSA *key, int pad){

    int i;
    unsigned char *pKeybuf;
    HCRYPTKEY hRsaKey;
    PUBLICKEYSTRUC *pBlob;
    RSAPUBKEY *pRPK;
    unsigned char *buf;
    DWORD dlen;
    DWORD bufsize;
	DWORD mod_size;
	int temp;

	if (pad != RSA_PKCS1_PADDING){
		perror("Only PKCS1_PADDING supported");
		return -1;
	}
	
	mod_size = BN_num_bytes(key->n);

    /* allocate buffer for public key blob */
    if((pBlob = malloc(sizeof(PUBLICKEYSTRUC) + sizeof(RSAPUBKEY) +
		mod_size  + (mod_size/2 * 7))) == NULL){
		perror("Out of memory");
		return -1;
	}
	memset(pBlob, 0, sizeof(PUBLICKEYSTRUC) + sizeof(RSAPUBKEY) + mod_size + (mod_size/2 * 7));

    /* allocate buffer for message decryption block */
    bufsize = length;
    if((buf = malloc(bufsize)) == NULL){
		perror("Out of memory");
		return -1;
	}

    /* construct public key blob from host public key */
    pKeybuf = ((unsigned char*)pBlob) + sizeof(PUBLICKEYSTRUC) + sizeof(RSAPUBKEY);    

    bn_to_le(key->n, pKeybuf);
	pKeybuf += BN_num_bytes(key->n);
    
	bn_to_le(key->p, pKeybuf);
	pKeybuf += BN_num_bytes(key->p);

	bn_to_le(key->q, pKeybuf);
	pKeybuf += BN_num_bytes(key->q);
	
	bn_to_le(key->dmp1, pKeybuf);
	pKeybuf += BN_num_bytes(key->dmp1);
	
	bn_to_le(key->dmq1, pKeybuf);
	pKeybuf += BN_num_bytes(key->dmq1);
	
	bn_to_le(key->iqmp, pKeybuf);
	pKeybuf += BN_num_bytes(key->iqmp);
	
	bn_to_le(key->d, pKeybuf);
	pKeybuf += BN_num_bytes(key->d);
	
    pBlob->bType = PRIVATEKEYBLOB;
    pBlob->bVersion = 0x02;
    pBlob->reserved = 0;
    pBlob->aiKeyAlg = CALG_RSA_KEYX;
    pRPK = (RSAPUBKEY*)(((unsigned char*)pBlob) + sizeof(PUBLICKEYSTRUC));
    pRPK->magic = 0x32415352; /* "RSA2" */
    pRPK->bitlen = mod_size * 8;
    bn_to_le(key->e, &pRPK->pubexp);

    /* import public key blob into key container */
    if(CryptImportKey(hCryptProv, (void*)pBlob,
		      sizeof(PUBLICKEYSTRUC)+sizeof(RSAPUBKEY)+mod_size+(mod_size/2 * 7),
			  0, CRYPT_EXPORTABLE, &hRsaKey) == FALSE){
		perror("Error importing RSA key!");
		return GetLastError();
	}

	dlen = length;
    for(i = 0; i < (int)dlen; i++)
		buf[i] = ctext[dlen - i - 1]; /* make it little endian */

    /* using host private key, decrypt the message */
    if(CryptDecrypt(hRsaKey, 0, TRUE, 0, buf, &dlen) == FALSE){
		perror("Error decrypting using RSA key!");
		return GetLastError();
	}

	memcpy(ptext, buf, dlen);

    CryptDestroyKey(hRsaKey);
    free(buf);
    free(pBlob);

	return dlen;
}

