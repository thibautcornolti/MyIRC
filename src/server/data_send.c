/*
** EPITECH PROJECT, 2018
** Project
** File description:
** data_send.c
*/

#include "server.h"

int data_send_add(data_send_t **ds, char *data)
{
	data_send_t *tmp = *ds;
	data_send_t *new_elem = malloc(sizeof(data_send_t));

	if (!new_elem)
		return (0);
	new_elem->data = strdup(data);
	new_elem->next = NULL;
	if (!*ds)
		*ds = new_elem;
	else {
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
	return (1);
}

void data_send_clear(data_send_t **ds)
{
	data_send_t *cpy = *ds;
	data_send_t *tmp;

	while (cpy) {
		tmp = cpy->next;
		free(cpy->data);
		free(cpy);
		cpy = tmp;
	}
	*ds = NULL;
}