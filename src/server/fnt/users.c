/*
** EPITECH PROJECT, 2018
** Project
** File description:
** users.c
*/

#include "server.h"

static char *append_char(char *in, char *to)
{
	size_t size = (in) ? strlen(in) : 0;
	char *ret = realloc(in, sizeof(char) * (size + strlen(to) + 1));

	if (!ret)
		return (NULL);
	memcpy(ret + size, to, strlen(to) + 1);
	return (ret);
}

static char *get_user_list(server_t *server, client_t *cli)
{
	client_t *list = server->clients;
	int i = 0;
	char *ret = NULL;

	while (list) {
		if (list->nickname &&
		strcmp(list->nickname, cli->nickname) != 0) {
			if (i != 0)
				ret = append_char(ret, " ");
			ret = append_char(ret, list->nickname);
			i += 1;
		}
		list = list->next;
	}
	return (ret);
}

void users_cmd(server_t *server, client_t *cli, cmd_t *cmd)
{
	char *users = get_user_list(server, cli);

	(void) cmd;
	msg_sendf(&cli->to_send, ":%s 265 %s :%s\r\n", "localhost",
	cli->nickname, users);
	free(users);
}