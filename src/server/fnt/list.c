/*
** EPITECH PROJECT, 2018
** Project
** File description:
** list.c
*/

#include <server.h>
#include "server.h"

void list_cmd(server_t *server, client_t *client, cmd_t *cmd)
{
	channel_t *all_chan = server->channel;

	while (all_chan) {
		if (cmd->ac == 0 || (cmd->ac > 0 &&
		strstr(all_chan->name, cmd->args[0]))) {
			msg_sendf(&client->to_send, ":%s 322 %s %s %d :\r\n",
			"localhost", client->nickname, all_chan->name,
			size_channel(server->clients, all_chan->name));
		}
		all_chan = all_chan->next;
	}
	msg_sendf(&client->to_send, ":%s 323 %s :%s\r\n", "localhost",
	client->nickname, "End of LIST");
}

//:irc.knoepflin.tk 353 test = #lol :@Arthur
//:irc.knoepflin.tk 366 test #lol :End of NAMES list.