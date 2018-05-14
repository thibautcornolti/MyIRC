/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool cmd_nick(sess_t *sess, char *line)
{
	free(sess->nickname);
	if (strlen(line))
		sess->nickname = strdup(line);
	else
		sess->nickname = strdup("iencli");
	return (true);
}
