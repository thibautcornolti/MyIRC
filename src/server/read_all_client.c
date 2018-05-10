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
	client_t *tmp_cli = *cli;

	while (tmp_cli) {
		if (poll_canread(*p, tmp_cli->fd)) {
			//TODO Read client
		}
		tmp_cli = tmp_cli->next;
	}
}