/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

size_t size_commander(commander_t *this)
{
	size_t res = -1;

	while (this->cmds[++res])
		;
	return (res);
}

bool push_commander(commander_t *this, char *cmd, ...)
{
	va_list ap;
	size_t len = this->size(this);
	char *final = NULL;
	bool res = true;

	va_start(ap, cmd);
	vasprintf(&final, cmd, ap);
	if (final && len < 512)
		this->cmds[len] = final;
	else
		res = false;
	va_end(ap);
	return (res);
}

char *pop_commander(commander_t *this)
{
	char *res = this->cmds[0];

	for (size_t i = 0; this->cmds[i]; ++i)
		this->cmds[i] = this->cmds[i + 1];
	return (res);
}
