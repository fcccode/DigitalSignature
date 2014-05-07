#include <fcntl.h>

#ifndef __RESOLV__DNSSEC__
#include <resolv_dnssec.h>
#endif //  __RESOLV__DNSSEC_
#include "getrrcertbyname.h"

/*
 * free the chain list of certificates
 */

void
free_certlist(struct certlist * certlist)
{
	struct certlist * cl, * nxt;
	cl = certlist;
	if (cl == NULL) {
		logger(LLV_DEBUG,
		       "Error in free_certlist: arument isn't valid");
		return;
	}

	while (cl != NULL) {
		if (cl->cert != NULL)
			free(cl->cert);
		nxt = cl->next;
		free(cl);
		cl = nxt;
	}
}

/*
 * Take a name , go search the CERT RR of the name.
 * return a chain list of structure with certificate and DNSsec status
 * of the CERT RR.
 * the chain list of structure was allocated, the user of the function
 * should free it.
 *
 * name should not be NULL
 * certlist should not be NULL
 *
 * return 1 if success
 * return 0 if controled error
 * return -1 if internal error
*/

int
getrrcertbyname(char *name, struct certlist **certlist)
{
	struct dns_response *resp;
	int ret;
	int validity; /* DNSsec validity of the RR */
	struct dns_rr *ans;
	char *buf;
	struct certlist *head, *curr, *cl;

	/* argument test */
	if ((name == NULL) || (certlist == NULL)) {
		logger(LLV_DEBUG,
		       "Error in getrrcertbyname: arument isn't valid");
		return(0);
	}

	/* call the DNS */
	ret = getrrsetbyname2(name, C_IN, dns_rdatatype_cert, 0, &resp);

	/* check the validity of the DNS response */
	if (ret != 0) {
		logger(LLV_DEBUG, "Error in getrrcertbyname 1");
		return(0);
	}

	if (resp->query == NULL) {
		logger(LLV_DEBUG, "Error in getrrcertbyname: query is NULL");
		free_dns_response(resp);
		return(0);
	}
	if ((resp->query->class != C_IN) ||
	    (resp->query->type != dns_rdatatype_cert)) {
		logger(LLV_DEBUG,
		       "Error in getrrcertbyname: "
		       "the response isn't right type or class");
		free_dns_response(resp);
		return(0);
	}
	if (resp->answer == NULL) {
		logger(LLV_DEBUG, "Error in getrrcertbyname:answer is NULL");
		free_dns_response(resp);
		return(0);
	}

	/* the DNSsec validity */
	ret = validator(name, resp->query->class, resp->query->type, resp);
	if (ret != 1) {
		logger(LLV_WARNING,
		       "In getrrcertbyname: "
		       "the DNSsec validity can't be verified");
		validity = 0;
	} else {
		logger(LLV_DEBUG,
		       "In getrrcertbyname: the DNSsec validity is verified");
		validity = 1;
	}

	/* construct the chain list of certificates */
	head = curr = NULL;
	ans = resp->answer;
	while (ans != NULL) {

		if ((ans->class != C_IN) ||
		    (ans->type != dns_rdatatype_cert)) {
			logger(LLV_DEBUG, "this is not a certificate");
			ans = ans->next;
			continue;
		}

		if (ans->size <= 5) {
			logger(LLV_DEBUG,
			       "Error in getrrcertbyname: "
			       "response is too short");
			free_dns_response(resp);
			return(0);
		}
		cl = (struct certlist *) malloc(sizeof(struct certlist));
		if (cl == NULL)	{
			logger(LLV_DEBUG, "Error in getrrcertbyname: malloc");
			free_dns_response(resp);
			free_certlist(head);
			return(-1);
		}
		bzero(cl, sizeof(struct certlist));

		cl->certlen = ans->size-5;
		cl->status = validity;

		buf = (char *) ans->rdata;
		cl->type = buffer_getuint16(buf);
		buf += 2;
		cl->keytag = buffer_getuint16(buf);
		buf += 2;
		cl->algorithm = buffer_getuint8(buf);
		buf += 1;

		cl->cert = (char *) malloc(cl->certlen);
		if (cl->cert == NULL) {
			logger(LLV_DEBUG, "Error in getrrcertbyname: malloc");
			free_dns_response(resp);
			return(-1);
		}

		bzero(cl->cert, cl->certlen);
		memcpy(cl->cert, buf, cl->certlen);

		if (head == NULL) {
			head = cl;
			curr = cl;
		} else {
			curr->next = cl;
			curr = curr->next;
		}
		ans = ans->next;
	}

	*certlist = head;
	return(1);
}

/* for test only */

#ifdef debug_getrrcertbyname
int
main(int argc, char *argv[])
{
	struct certlist *certlist, *curr;
	int ret;
	char *buffer;
	char *file_name;
	int fd;
	int len;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s dns_name_of_cert_owner\n", argv[0]);
		exit(0);
	}

	ret = getrrcertbyname(argv[1], &certlist);

	if (ret != 1) {
		fprintf(stderr, "Error in call getrrcertbyname\n");
		exit(0);
	}

	curr = certlist;

	while (curr != NULL) {
		buffer = (char *) malloc(curr->certlen * 2);
		bzero(buffer, curr->certlen * 2);
		len = b64_ntop2(curr->cert, curr->certlen,
				buffer, curr->certlen * 2);
		fprintf(stderr,
			"type:%d keytag:%d alg:%d status:%d "
			"certlen:%d cert_base64:%s\n",
			curr->type,
			curr->keytag,
			curr->algorithm,
			curr->status,
			curr->certlen,buffer);
		free(buffer);
		file_name = (char *) malloc(5 + strlen(argv[1]) + 6 + 4);
		bzero(file_name, strlen(argv[1]) + 6 + 4);
		sprintf(file_name, "/tmp/%s_%d.der", argv[1], curr->keytag);
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC);
		write(fd, curr->cert, curr->certlen);
		close(fd);
		free(file_name);
		curr = curr->next;
	}

	free_certlist(certlist);
	exit(0);
}
#endif
