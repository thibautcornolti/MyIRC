/*
** EPITECH PROJECT, 2018
** Project
** File description:
** read_all_client.c
*/

#include <zconf.h>
#include <server.h>
#include "server.h"

static void p_cmd(server_t *serv, client_t *cli, char *cmd)
{
	cmd_t *c = parse_cmd(cmd);

	if (!c)
		return;
	exec_cmd(serv, cli, c);
	free_cmd(c);
}

static int read_cli(server_t *serv, client_t **tmp_cli)
{
	client_t *tmp;
	int status = read_cmd(*tmp_cli);

	if (status == 2)
		p_cmd(serv, *tmp_cli, (*tmp_cli)->buf);
	else if (status == 0) {
		tmp = (*tmp_cli)->next;
		poll_rm(&serv->poll, (*tmp_cli)->fd);
		client_rm(&serv->clients, *tmp_cli);
		printf("Client disconnected\n");
		*tmp_cli = tmp;
		return (0);
	}
	return (1);
}

void read_all_cli(server_t *s)
{
	client_t *tmp_cli = s->clients;

	while (tmp_cli) {
		if (poll_canread(s->poll, tmp_cli->fd) &&
		!read_cli(s, &tmp_cli))
			continue;
		tmp_cli = tmp_cli->next;
	}
}