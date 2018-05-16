/*
** EPITECH PROJECT, 2018
** Project
** File description:
** join.c
*/

#include <server.h>
#include "server.h"

static char *get_user_by_chan(client_t *all_cli, char *chan_name)
{
	size_t i = 0;
	size_t len;
	char *ret = strdup("");

	while (all_cli) {
		if (all_cli->log_state == 0x11 &&
		channel_contain(all_cli->channel, chan_name)) {
			len = strlen(ret);
			ret = realloc(ret, sizeof(char) * (len +
			strlen(all_cli->nickname) + (i != 0) + 1));
			if (i != 0)
				ret[len] = ' ';
			memcpy(ret + len + (i != 0), all_cli->nickname,
			strlen(all_cli->nickname));
			ret[len + strlen(all_cli->nickname) + (i != 0)] = '\0';
			i += 1;
		}
		all_cli = all_cli->next;
	}
	return (ret);
}

static void send_list_user(server_t *server, client_t *cli, cmd_t *cmd)
{
	char *list = get_user_by_chan(server->clients, cmd->args[0]);

	if (!list)
		return;
	msg_sendf(&cli->to_send, ":%s 353 %s = %s :%s\r\n",
	"localhost", cli->nickname, cmd->args[0], list);
	msg_sendf(&cli->to_send, ":%s 366 %s %s :%s\r\n", "localhost",
	cli->nickname, cmd->args[0], "End of NAMES list.");
	//BROADCAST    :test2!~d@163.5.141.157 JOIN :#lol
	broadcast_to_channel(server->clients, cli, cmd->args[0], ":");
	free(list);
}

void join_cmd(server_t *server, client_t *cli, cmd_t *cmd)
{
	int ret;

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
	ret = channel_add(&cli->channel, cmd->args[0]);
	if (ret == 1) {
//		msg_sendf(&cli->to_send, ":%s!~%s@localhost JOIN :%s\r\n",
//	cli->nickname, cli->nickname, cmd->args[0]); //TODO Change second nickname by username
		broadcast_channel(server->clients, cmd->args[0],
	":%s!~%s@localhost JOIN :%s\r\n", cli->nickname, cli->nickname,
	cmd->args[0]);
		send_list_user(server, cli, cmd);
	}
}