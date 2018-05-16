/*
** EPITECH PROJECT, 2018
** Project
** File description:
** broadcast_channel.c
*/

#include "server.h"

void broadcast_to_channel(client_t *all_cli, client_t *cli, char *chan_name,
char *msg)
{
	while (all_cli) {
		if (all_cli != cli &&
		channel_contain(all_cli->channel, chan_name)) {
			msg_send(&all_cli->to_send, msg);
		}
		all_cli = all_cli->next;
	}
}