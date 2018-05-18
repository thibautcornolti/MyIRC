/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

commander_t *create_commander()
{
	commander_t *commander;

	commander = safe_malloc(sizeof(commander_t));
	commander->size = &size_commander;
	commander->push = &push_commander;
	commander->pop = &pop_commander;
	commander->free = &free_commander;
	return (commander);
}

void free_commander(commander_t *this)
{
	for (size_t i = 0; this->cmds[i]; ++i)
		free(this->cmds[i]);
	free(this);
}
