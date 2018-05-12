/*
** EPITECH PROJECT, 2018
** Project
** File description:
** write_all_client.c
*/

#include "server.h"

static void send_msg(client_t *cli, data_send_t *msg)
{
	if (msg->data)
		send_sock(cli, msg->data);
	if (msg->next)
		send_msg(cli, msg->next);
}

void write_all_cli(client_t *cli, poll_t *p)
{
	while (cli) {
		if (poll_canwrite(p, cli->fd)) {
			send_msg(cli, cli->to_send);
			data_send_clear(&cli->to_send);
			poll_update(p, cli->fd, POLLIN | POLLHUP);
		}
		cli = cli->next;
	}
}