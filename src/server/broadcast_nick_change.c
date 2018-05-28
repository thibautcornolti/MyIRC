/*
** EPITECH PROJECT, 2018
** Project
** File description:
** broadcast_nick_change.c
*/

#include "server.h"

static int is_in(client_t **tab, client_t *to_test, int size)
{
	int i = 0;

	while (i < size && tab) {
		if (tab[i] == to_test)
			return (1);
		i += 1;
	}
	return (0);
}

static client_t **append_cli(client_t **in, client_t *to, int *size)
{
	in = realloc(in, sizeof(client_t *) * (*size + 1));

	if (!in) {
		*size = 0;
		return (NULL);
	}
	in[*size] = to;
	*size += 1;
	return (in);
}

static void broadcast(client_t **to_send, int size, char *msg)
{
	int i = 0;

	while (to_send && i < size) {
		msg_send(&to_send[i]->to_send, msg);
		i += 1;
	}
}

void broadcast_nick_change(server_t *server, client_t *cli, char *msg)
{
	int size = 0;
	client_t **ret = NULL;
	client_t *a_cli;
	channel_t *chan = cli->channel;

	while (chan) {
		a_cli = server->clients;
		while (a_cli) {
			if (a_cli != cli && channel_contain(a_cli->channel,
			chan->name) && !is_in(ret, a_cli, size))
				ret = append_cli(ret, a_cli, &size);
			a_cli = a_cli->next;
		}
		chan = chan->next;
	}
	broadcast(ret, size, msg);
}