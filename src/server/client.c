/*
** EPITECH PROJECT, 2018
** Project
** File description:
** client.cpp
*/

#include <stdlib.h>
#include "server.h"

size_t nb_client(client_t *cli)
{
	size_t ret = 0;

	while (cli) {
		ret += 1;
		cli = cli->next;
	}
	return ret;
}

int client_add(client_t **cli, client_t *to_add)
{
	client_t *tmp = *cli;
	client_t *new_elem = malloc(sizeof(client_t));

	if (!new_elem)
		return (0);
	to_add->next = NULL;
	memcpy(new_elem, to_add, sizeof(client_t));
	if (!*cli)
		*cli = new_elem;
	else {
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
	return (1);
}

static void free_client(client_t *cli)
{
	free(cli->username);
	free(cli->nickname);
	free(cli->buf);
	free_channel(cli->channel);
	free_data_msg(cli->to_send);
	cli->buf = NULL;
}

void client_rm(client_t **cli, client_t *to_rm)
{
	client_t *tmp;
	client_t *cpy = *cli;

	if (!cpy)
		return;
	if (cpy == to_rm) {
		*cli = cpy->next;
		free(cpy);
		return;
	}
	while (cpy->next) {
		if (cpy->next == to_rm) {
			tmp = cpy->next;
			free_client(tmp);
			cpy->next = cpy->next->next;
			free(tmp);
			return;
		}
		cpy = cpy->next;
	}
}