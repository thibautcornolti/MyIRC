/*
** EPITECH PROJECT, 2018
** Project
** File description:
** free_channel.c
*/

#include "server.h"

void free_channel(channel_t *channel)
{
	channel_t *tmp;

	while (channel) {
		tmp = channel->next;
		free(channel->name);
		free(channel);
		channel = tmp;
	}
}