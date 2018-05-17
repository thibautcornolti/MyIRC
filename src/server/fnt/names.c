/*
** EPITECH PROJECT, 2018
** Project
** File description:
** names.c
*/

#include <server.h>
#include "server.h"

static void send_list(server_t *server, client_t *client, cmd_t *cmd)
{
	char *list = get_user_by_chan(server->clients, client, cmd->args[0]);
	if (!list)
		return;
	msg_sendf(&client->to_send, ":%s 353 %s = %s :%s\r\n",
	"localhost", client->nickname, cmd->args[0], list);
	free(list);
}

void names_cmd(server_t *server, client_t *client, cmd_t *cmd)
{
	if (cmd->ac == 0) {
		msg_sendf(&client->to_send, ":%s 461 %s NAMES :%s\r\n",
		"localhost", client->nickname, "Not enough parameters");
		return;
	}
	if (channel_exist(server->channel, cmd->args[0]))
		send_list(server, client, cmd);
	msg_sendf(&client->to_send, ":%s 366 %s %s :%s\r\n", "localhost",
	client->nickname, cmd->args[0], "End of NAMES list.");
}