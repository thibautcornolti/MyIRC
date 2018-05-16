/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static char *get_nick(char *line)
{
	char *res;
	int len = -1;

	while (line[++len] == ' ')
		;
	res = strdup(line + len);
	len = 0;
	for (; res[len] && res[len] != ' '; len++)
		;
	res[len] = 0;
	return (res);
}

bool cmd_nick(sess_t *sess, char *line)
{
	char *new_nickname = get_nick(line);

	free(sess->nickname);
	if (new_nickname && strlen(new_nickname))
		sess->nickname = strdup(new_nickname);
	else
		sess->nickname = strdup(getlogin());
	free(new_nickname);
	if (sess->serv->connected)
		dprintf(sess->serv->fd, "NICK %s\r\n", sess->nickname);
	return (true);
}
