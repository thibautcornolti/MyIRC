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
	channel_t *tmp;
	channel_t *channel = s->channel;

	if (channel && size_channel(s->clients, channel->name) == 0) {
		s->channel = channel->next;
		free(channel);
		channel = s->channel;
	}
	while (channel && channel->next) {
		if (size_channel(s->clients, channel->next->name) == 0) {
			tmp = channel->next;
			channel->next = channel->next->next;
			free(tmp->name);
			free(tmp);
		} else
			channel = channel->next;
	}
}