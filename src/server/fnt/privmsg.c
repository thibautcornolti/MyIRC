/*
** EPITECH PROJECT, 2018
** Project
** File description:
** privmsg.c
*/

#include <server.h>
#include "server.h"

static void send_to_nickname(client_t *all_cli, client_t *cli, cmd_t *cmd)
{
	while (all_cli) {
		if (all_cli->nickname && !strcmp(all_cli->nickname,
		cmd->args[0])) {
			msg_sendf(&all_cli->to_send, ":%s!~%s@localhost %s %s"
			" :%s\r\n", cli->nickname, cli->username,
			cmd->cmd, cmd->args[0], cmd->args[1]);
			return;
		}
		all_cli = all_cli->next;
	}
	msg_sendf(&cli->to_send, ":%s 401 %s %s :%s\r\n", "localhost",
	cli->nickname, cmd->args[0], "No such nick/channel");
}

static void send_to_channel(server_t *s, client_t *cli, cmd_t *cmd)
{
	client_t *all_cli = s->clients;

	if (!channel_contain(s->channel, cmd->args[0])) {
		msg_sendf(&cli->to_send, ":%s 401 %s %s :%s\r\n", "localhost",
		cli->nickname, cmd->args[0], "No such nick/channel");
		return;
	}
	while (all_cli) {
		if (all_cli != cli && channel_contain(all_cli->channel,
		cmd->args[0])) {
			msg_sendf(&all_cli->to_send, ":%s!~%s@localhost %s %s"
			" :%s\r\n", cli->nickname, cli->username, cmd->cmd,
			cmd->args[0], cmd->args[1]);
		}
		all_cli = all_cli->next;
	}
}

void privmsg_cmd(server_t *server, client_t *cli, cmd_t *cmd)
{
	if (cmd->ac != 2) {
		msg_sendf(&cli->to_send, ":%s 461 %s %s :%s", "localhost",
		cli->nickname, cmd->cmd, "Not enough parameters");
	}
	if (cmd->args[0][0] != '#')
		send_to_nickname(server->clients, cli, cmd);
	else
		send_to_channel(server, cli, cmd);
}