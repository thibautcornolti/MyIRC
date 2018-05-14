/*
** EPITECH PROJECT, 2018
** Project
** File description:
** user.c
*/

#include "server.h"

void user_cmd(server_t *server, client_t *cli, cmd_t *cmd)
{
	cli->log_state |= 0x10;
	if (cli->log_state == 0x11) {
		msg_sendf(&cli->to_send, "001 :Welcome to the Internet "
		"Relay Network %s!\n", cli->nickname);
//		msg_send(&cli->to_send, "001 :Welcome to the Internet "
//					"Relay Network <nick>!\n");
	}
}