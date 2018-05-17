/*
** EPITECH PROJECT, 2018
** Project
** File description:
** channel_exist.c
*/

#include "server.h"

int channel_exist(channel_t *channel, char *name)
{
	while (channel) {
		if (!strcmp(channel->name, name))
			return (1);
		channel = channel->next;
	}
	return (0);
}