/*
** EPITECH PROJECT, 2018
** Project
** File description:
** exec_cmd.c
*/

#include <server.h>
#include "server.h"

static const cmd_list_t list[] = {
	{"NICK", 0, &nick_cmd},
	{"USER", 0, &user_cmd},
	{"JOIN", 1, &join_cmd},
	{"PART", 1, &part_cmd},
	{"PRIVMSG", 1, &privmsg_cmd},
	{"QUIT", 0, &quit_cmd},
	{NULL, 0, NULL}
};

static int exec_cmd_with_perm(server_t *serv, client_t *cli, cmd_t *cmd, int i)
{
	if (list[i].need_login == 1 && cli->log_state != 0x11) {
		msg_sendf(&cli->to_send, ":%s 451 * :%s\r\n", "localhost",
		"You have not registered");
		return (0);
	}
	list[i].fnt(serv, cli, cmd);
	return (1);
}

int exec_cmd(server_t *serv, client_t *cli, cmd_t *cmd)
{
	for (int i = 0; list[i].name; i++)
		if (strcmp(list[i].name, cmd->cmd) == 0)
			return (exec_cmd_with_perm(serv, cli, cmd, i));
	if (cli->log_state == 0x11)
		msg_sendf(&cli->to_send, ":%s 421 %s %s :%s\r\n",
		"localhost", cli->nickname, cmd->cmd, "Unknown command");
	return (0);
}