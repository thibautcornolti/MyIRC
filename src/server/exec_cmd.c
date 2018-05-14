/*
** EPITECH PROJECT, 2018
** Project
** File description:
** exec_cmd.c
*/

#include <server.h>
#include "server.h"

static const cmd_list_t list[] = {
	{"nick", &nick_cmd},
	{"user", &user_cmd},
//	{"join", &join_cmd},
	{NULL, NULL}
};

int exec_cmd(server_t *serv, client_t *cli, cmd_t *cmd)
{
	for (int i = 0; list[i].name; i++)
		if (strcmp(list[i].name, cmd->cmd) == 0) {
			list[i].fnt(serv, cli, cmd);
			return (1);
		}
	if (cli->log_state == 0x11)
		msg_sendf(&cli->to_send, "%s %s %s %s\n", "421", cli->nickname,
		cmd->cmd, ":Unknown command");
	return (0);
}