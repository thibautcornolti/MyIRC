/*
** EPITECH PROJECT, 2018
** Project
** File description:
** accept_client.c
*/

#include <sys/socket.h>
#include <zconf.h>
#include "server.h"

int accept_client(int sock_serv, client_t **cli, poll_t **p)
{
	client_t to_push;
	int sock = accept(sock_serv, NULL, 0);

	if (sock == -1)
		return (0);
	to_push.fd = sock;
	to_push.log_state = 0;
	to_push.nickname = NULL;
	to_push.to_send = NULL;
	msg_sendf(&to_push.to_send, "%s %s :%s\n", "020", "*", "Please wait "
	"while we process your connection.");
	if (!client_add(cli, &to_push) || !poll_add(p, sock, POLLIN)) {
		close(sock);
		return (0);
	}
	return (1);
}