/*
** EPITECH PROJECT, 2018
** Project
** File description:
** nick.c
*/

#include <server.h>
#include "server.h"

static void first_nick(client_t *cli, cmd_t *cmd)
{
	cli->nickname = strdup(cmd->args[0]);
	if (!cli->nickname)
		return;
	cli->log_state |= 0x1;
	if (cli->log_state == 0x11) {
		msg_sendf(&cli->to_send, ":%s 001 :Welcome to the Internet "
		"Relay Network %s!\r\n", "localhost", cli->nickname);
	}
}

static void change_nick(server_t *serv, client_t *cli, cmd_t *cmd)
{
	char *new_nick = strdup(cmd->args[0]);
	char *msg = asendf(":%s!~@localhost NICK :%s\r\n",
			   cli->nickname, cmd->args[0]);

	(void) serv;
	if (!msg || !new_nick)
		return;
	broadcast_nick_change(serv, cli, msg);
	msg_send(&cli->to_send, msg);
	free(cli->nickname);
	cli->nickname = new_nick;
	free(msg);
}

static int already_taken(client_t *all_cli, char *nick)
{
	while (all_cli) {
		if (all_cli->nickname && !strcmp(all_cli->nickname, nick))
			return (1);
		all_cli = all_cli->next;
	}
	return (0);
}

void nick_cmd(server_t *server, client_t *cli, cmd_t *cmd)
{
	if (cmd->ac == 0) {
		msg_sendf(&cli->to_send, ":%s 461 * NICK :Not enough "
		"parameters\r\n", "localhost");
		return;
	}
	if (already_taken(server->clients, cmd->args[0])) {
		msg_sendf(&cli->to_send, ":%s 433 %s %s :%s\r\n",
		"localhost", (cli->nickname) ? cli->nickname : "*",
		cmd->args[0], "Nickname is already in use");
		return;
	}
	if (!cli->nickname)
		first_nick(cli, cmd);
	else
		change_nick(server, cli, cmd);
}