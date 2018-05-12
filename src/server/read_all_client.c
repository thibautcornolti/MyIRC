/*
** EPITECH PROJECT, 2018
** Project
** File description:
** read_all_client.c
*/

#include <zconf.h>
#include "server.h"

void read_all_cli(client_t **cli, poll_t **p)
{
	client_t *tmp;
	client_t *tmp_cli = *cli;

	while (tmp_cli) {
		if (poll_canread(*p, tmp_cli->fd)) {
			char *s = read_sock(tmp_cli);
			if (!s) {
				tmp = tmp_cli->next;
				poll_rm(p, tmp_cli->fd);
				client_rm(cli, tmp_cli);
				printf("Client disconnected\n");
				tmp_cli = tmp;
				continue;
			} else
				data_send_add(&tmp_cli->to_send, "Salut\n");
		}
		tmp_cli = tmp_cli->next;
	}
}