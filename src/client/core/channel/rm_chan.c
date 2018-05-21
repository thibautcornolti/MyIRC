/*
** EPITECH PROJECT, 2018
** Project
** File description:
** rm_chan.c
*/

#include <client.h>

static void free_maillon(chan_t *chan)
{
	free(chan->name);
//	free_logger(chan->logger); //TODO ask tibo why this function is not defined
	free(chan);
}

int rm_chan(chan_t **c, char *name)
{
	chan_t *tmp;
	chan_t *cpy = *c;

	if (!cpy)
		return (0);
	if (!strcmp(cpy->name, name)) {
		*c = cpy->next;
		free_maillon(cpy);
		return (1);
	}
	while (cpy->next) {
		if (!strcmp(cpy->next->name, name)) {
			tmp = cpy->next;
			cpy->next = cpy->next->next;
			free_maillon(tmp);
			return (1);
		}
		cpy = cpy->next;
	}
	return (0);
}