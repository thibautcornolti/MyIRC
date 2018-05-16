/*
** EPITECH PROJECT, 2018
** Project
** File description:
** channel.c
*/

#include "server.h"

static int find_duplicate(channel_t *t, char *chan_name)
{
	while (t) {
		if (!strcmp(t->name, chan_name))
			return (1);
		t = t->next;
	}
	return (0);
}

int channel_add(channel_t **chan, char *chan_name)
{
	channel_t *tmp = *chan;
	channel_t *new_elem = malloc(sizeof(channel_t));

	if (!new_elem)
		return (0);
	if (find_duplicate(*chan, chan_name)) {
		free(new_elem);
		return (2);
	}
	new_elem->name = strdup(chan_name);
	new_elem->next = NULL;
	if (!*chan)
		*chan = new_elem;
	else {
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
	return (1);
}

int channel_contain(channel_t *chan, char *chan_name)
{
	while (chan) {
		if (!strcmp(chan->name, chan_name))
			return (1);
		chan = chan->next;
	}
	return (0);
}

size_t size_channel(client_t *all_cli, char *chan)
{
	size_t ret = 0;

	while (all_cli) {
		if (channel_contain(all_cli->channel, chan))
			ret += 1;
		all_cli = all_cli->next;
	}
	return (ret);
}

int channel_rm(channel_t **chan, char *chan_name)
{
	channel_t *tmp;
	channel_t *cpy = *chan;

	if (!cpy)
		return (0);
	if (!strcmp(cpy->name, chan_name)) {
		*chan = cpy->next;
		free(cpy);
		return (1);
	}
	while (cpy->next) {
		if (!strcmp(cpy->next->name, chan_name)) {
			tmp = cpy->next;
			cpy->next = cpy->next->next;
			free(tmp);
			return (1);
		}
		cpy = cpy->next;
	}
	return (0);
}