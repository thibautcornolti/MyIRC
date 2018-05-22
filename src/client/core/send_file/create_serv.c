/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** create_serv.c
*/

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <zconf.h>
#include <string.h>

static int create_sock(int *ret)
{
	int tmp = 1;

	*ret = socket(AF_INET, SOCK_STREAM, 0);
	if (*ret == -1) {
		perror("socket");
		return (0);
	}
	setsockopt(*ret, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int));
	return (1);
}

static int listen_sock(int ret)
{
	if (listen(ret, 1024) == -1) {
		perror("listen");
		close(ret);
		return (0);
	}
	return (1);
}

int create_random_serv(uint16_t *port)
{
	struct sockaddr_in s_in;
	socklen_t len = sizeof(s_in);
	int ret = -1;

	if (!create_sock(&ret))
		return (-1);
	memset(&s_in, 0, sizeof(s_in));
	s_in.sin_addr.s_addr = htonl(INADDR_ANY);
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(0);
	if (bind(ret, (const struct sockaddr *) &s_in, sizeof(s_in)) == -1) {
		perror("bind");
		close(ret);
		return (0);
	}
	getsockname(ret, (struct sockaddr *) &s_in, &len);
	if (!listen_sock(ret))
		return (-1);
	*port = ntohs(s_in.sin_port);
	return (ret);
}