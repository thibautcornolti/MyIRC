/*
** EPITECH PROJECT, 2018
** Project
** File description:
** poll.cpp
*/

#include <malloc.h>
#include "common.h"

int poll_add(poll_t **p, int fd, short evt)
{
	poll_t *new_elem = malloc(sizeof(poll_t));
	poll_t *cpy = *p;

	if (!new_elem)
		return (0);
	new_elem->fd = fd;
	new_elem->evt = evt;
	new_elem->next = NULL;
	if (!*p)
		*p = new_elem;
	else {
		while (cpy->next)
			cpy = cpy->next;
		cpy->next = new_elem;
	}
	return (1);
}

int poll_rm(poll_t **p, int fd) //TODO Coding Style
{
	poll_t *tmp;
	poll_t *cpy = *p;
	size_t i = 0;

	if (!cpy)
		return (0);
	if (!cpy->next && cpy->fd == fd) {
		free(*p);
		*p = NULL;
		return (1);
	}
	while (cpy->next) {
		if (cpy->next->fd == fd) {
			tmp = cpy->next;
			cpy->next = cpy->next->next;
			if (i == 0)
				*p = tmp;
			free(tmp);
			return (1);
		}
		i++;
		cpy = cpy->next;
	}
	return (0);
}

int poll_update(poll_t *p, int fd, short evt)
{
	poll_t *cpy = p;

	if (!cpy)
		return (0);
	while (cpy->next) {
		if (cpy->fd == fd) {
			cpy->evt = evt;
			return (1);
		}
		cpy = cpy->next;
	}
	return (0);
}
