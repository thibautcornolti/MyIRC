/*
** EPITECH PROJECT, 2018
** Project
** File description:
** join.c
*/

#include "server.h"

static void send_list_user(server_t *server, client_t *cli, cmd_t *cmd)
{
	char *list = get_user_by_chan(server->clients, cli, cmd->args[0]);

	if (!list)
		return;
	msg_sendf(&cli->to_send, ":%s 353 %s = %s :%s\r\n",
	"localhost", cli->nickname, cmd->args[0], list);
	msg_sendf(&cli->to_send, ":%s 366 %s %s :%s\r\n", "localhost",
	cli->nickname, cmd->args[0], "End of NAMES list.");
	free(list);
}

void join_cmd(server_t *server, client_t *cli, cmd_t *cmd)
{
	int ret_me = 0;
	int ret_serv = 0;

	if (cmd->ac == 0) {
		msg_sendf(&cli->to_send, ":%s 461 %s JOIN :%s\r\n",
		"localhost", cli->nickname, "Not enough parameters");
		return;
	}
	if (cmd->args[0][0] != '#') {
		msg_sendf(&cli->to_send, ":%s 403 %s %s :%s\r\n", "localhost",
		cli->nickname, cmd->args[0], "No such channel");
		return;
	}
	ret_me = channel_add(&cli->channel, cmd->args[0]);
	ret_serv = channel_add(&server->channel, cmd->args[0]);
	if (ret_me == 1 && ret_serv >= 1) {
		broadcast_channel(server->clients, cmd->args[0],
	":%s!~%s@localhost JOIN :%s\r\n", cli->nickname, cli->username,
	cmd->args[0]);
		send_list_user(server, cli, cmd);
	}
}