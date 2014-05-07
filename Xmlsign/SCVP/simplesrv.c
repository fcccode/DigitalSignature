/* simple server */

#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <err.h>
#include <stdio.h>
#include <unistd.h>

short port = 8000;
struct sockaddr_in srv, from;
int flen;

main(int argc, char *argv[])
{
	int s, c, i;

	s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s < 0)
		err(1, "socket");
	i = 1;
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i)) < 0)
		err(1, "setsockopt(SO_REUSEADDR)");
	srv.sin_family = AF_INET;
#ifndef linux
	srv.sin_len = sizeof(srv);
#endif
	srv.sin_port = htons(port);
	if (bind(s, (struct sockaddr *)&srv, sizeof(srv)) < 0)
		err(2, "bind");
	if (listen(s, 1) < 0)
		err(3, "listen");
	flen = sizeof(from);
	c = accept(s, (struct sockaddr *)&from, &flen);
	if (c < 0)
		err(4, "accept");
	for (i = 3; i < 20; i++) {
		if (i == c)
			continue;
		(void) close(i);
	}
	if (dup2(c, 0) < 0)
		err(5, "dup2");
	if (dup2(c, 1) < 0)
		err(6, "dup2");
	if (close(c) < 0)
		err(7, "close");
	if (execvp(argv[1], &argv[1]) < 0)
		err(8, "execvp");
	exit(1);
}
