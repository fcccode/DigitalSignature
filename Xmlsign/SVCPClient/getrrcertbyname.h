
/* cf RFC2538  */
#define DNSSEC_TYPE_PKIX        1
#define DNSSEC_TYPE_SPKI        2
#define DNSSEC_TYPE_PGP         3
#define DNSSEC_TYPE_URI         4
#define DNSSEC_TYPE_OID         5

#define DNSSEC_ALG_RSAMD5       1
#define DNSSEC_ALG_DH           2
#define DNSSEC_ALG_DSA          3
#define DNSSEC_ALG_ECC          4
#define DNSSEC_ALG_PRIVATEDNS   5
#define DNSSEC_ALG_PRIVATEOID   6


struct certlist {
	u_int16_t type;
	u_int16_t keytag;
	u_int8_t algorithm;             
	u_int8_t status;	/* DNSsec validation  1:valid  0:uncertain*/
	u_int16_t certlen;       
	char *cert;  
	struct certlist *next;
};

extern int getrrcertbyname(char *name, struct certlist **certlistp);
extern void free_certlist(struct certlist *certlist);
