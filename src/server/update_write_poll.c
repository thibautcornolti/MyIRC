/*
** EPITECH PROJECT, 2018
** Project
** File description:
** update_write_poll.c
*/

#include "server.h"

void update_write_poll(client_t *cli, poll_t *p)
{
	while (cli) {
		if (cli->to_send)
			poll_update(p, cli->fd, POLLIN | POLLHUP | POLLOUT);
		else
			poll_update(p, cli->fd, POLLIN | POLLHUP);
		cli = cli->next;
	}
}