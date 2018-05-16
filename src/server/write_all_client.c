/*
** EPITECH PROJECT, 2018
** Project
** File description:
** write_all_client.c
*/

#include <server.h>
#include "server.h"

static void send_msg(client_t *cli, data_send_t *msg)
{
	if (msg->data)
		send_sock(cli, msg->data);
	if (msg->next)
		send_msg(cli, msg->next);
}

static void force_disconnect_client(server_t *server, client_t **cli)
{
	client_t *tmp;

	tmp = (*cli)->next;
	poll_rm(&server->poll, (*cli)->fd);
	close((*cli)->fd);
	client_rm(&server->clients, (*cli));
	*cli = tmp;
}

void write_all_cli(server_t *server)
{
	client_t *cli = server->clients;

	while (cli) {
		if (poll_canwrite(server->poll, cli->fd)) {
			send_msg(cli, cli->to_send);
			msg_send_clear(&cli->to_send);
			poll_update(server->poll, cli->fd, POLLIN | POLLHUP);
			if (cli->quit == 1) {
				force_disconnect_client(server, &cli);
				continue;
			}
		}
		cli = cli->next;
	}
}