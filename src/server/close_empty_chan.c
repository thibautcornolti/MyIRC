/*
** EPITECH PROJECT, 2018
** Project
** File description:
** close_empty_chan.c
*/

#include <server.h>
#include "server.h"

void close_empty_chan(server_t *s)
{
	size_t i = 0;
	channel_t *tmp;
	channel_t *channel = s->channel;

	while (channel) {
		if (size_channel(s->clients, channel->name) == 0) {
			tmp = channel->next;
			free(channel->name);
			free(channel);
			if (i == 0)
				s->channel = tmp;
			else
				i += 1;
			channel = tmp;
			i += 1;
		} else
			channel = channel->next;
	}
}