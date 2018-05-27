/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** open_connection.c
*/

#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
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

int create_client(char *serv, uint16_t port)
{
	int ret;
	struct sockaddr_in addr;

	if (!create_sock(&ret))
		return (-1);
	memset(&addr, 0, sizeof(addr));
	if (inet_pton(AF_INET, serv, &addr.sin_addr) != 1) {
		perror("inet_pton");
		close(ret);
		return (-1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (connect(ret, (const struct sockaddr *) &addr,
	sizeof(addr)) == -1) {
		perror("connect");
		close(ret);
		return (-1);
	}
	return (ret);
}