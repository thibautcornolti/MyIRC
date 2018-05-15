/*
** EPITECH PROJECT, 2018
** Project
** File description:
** nick.c
*/

#include "server.h"

void nick_cmd(server_t *server, client_t *cli, cmd_t *cmd)
{
	(void) server;

	if (cmd->ac == 0) {
		msg_send(&cli->to_send, "461 * NICK :Not enough "
					"parameters\n");
		return;
	}
	cli->nickname = strdup(cmd->args[0]);
	cli->log_state |= 0x1;
	if (cli->log_state == 0x11) {
		msg_send(&cli->to_send, "001 :Welcome to the Internet "
					"Relay Network <nick>!\n");
	}
}