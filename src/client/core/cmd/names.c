/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool cmd_names(sess_t *sess, char *line)
{
	commander_t *cmder = sess->serv->commander;

	if (strlen(line))
		cmder->push(cmder, "NAMES %s", line);
	else if (strcmp(sess->cur_chan->name, "master"))
		cmder->push(cmder, "NAMES %s", sess->cur_chan->name);
	else
		sess->printChan(
			sess, "master", "You cannot list master's users");
	return (true);
}
