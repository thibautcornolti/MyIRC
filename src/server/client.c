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
	new_elem->to_send = to_add->to_send;
	new_elem->nickname = to_add->nickname;
	new_elem->log_state = to_add->log_state;
	new_elem->fd = to_add->fd;
	new_elem->next = NULL;
	if (!*cli)
		*cli = new_elem;
	else {
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
	return (1);
}

int client_rm(client_t **cli, client_t *to_rm)
{
	client_t *tmp;
	client_t *cpy = *cli;

	if (!cpy)
		return (0);
	if (cpy == to_rm) {
		*cli = cpy->next;
		free(cpy);
		return (1);
	}
	while (cpy->next) {
		if (cpy->next == to_rm) {
			tmp = cpy->next;
			cpy->next = cpy->next->next;
			free(tmp);
			return (1);
		}
		cpy = cpy->next;
	}
	return (0);
}