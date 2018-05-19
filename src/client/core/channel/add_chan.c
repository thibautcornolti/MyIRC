/*
** EPITECH PROJECT, 2018
** Project
** File description:
** add_chan.c
*/

#include "client.h"

int add_chan(chan_t **chan, char *name)
{
	chan_t *cpy = *chan;
	chan_t *new_elem = safe_malloc(sizeof(chan_t));

	new_elem->name = strdup(name);
	if (!new_elem->name) {
		free(new_elem);
		return (0);
	}
	new_elem->logger = create_logger();
	new_elem->update = false;
	new_elem->next = NULL;
	if (!*chan)
		*chan = new_elem;
	else {
		while (cpy->next)
			cpy = cpy->next;
		cpy->next = new_elem;
	}
	return (1);
}