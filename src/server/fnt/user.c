/*
** EPITECH PROJECT, 2018
** Project
** File description:
** user.c
*/

#include "server.h"

void user_cmd(server_t *server, client_t *cli, cmd_t *cmd)
{
	(void) server;
	if (cmd->ac != 4) {
		msg_sendf(&cli->to_send, ":%s 461 %s USER :%s\r\n",
		"localhost", (cli->nickname) ? cli->nickname : "*",
		"Not enough paramters");
		return;
	}
	cli->log_state |= 0x10;
	if (cli->log_state == 0x11) {
		msg_sendf(&cli->to_send, ":%s 001 %s :Welcome to the Internet "
		"Relay Network %s!\r\n", "localhost", cli->nickname,
			  cli->nickname);
	}
}