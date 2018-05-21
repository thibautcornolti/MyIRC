/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool cmd_list(sess_t *sess, char *line)
{
	(void) sess;
	(void) line;
	sess->serv->commander->push(sess->serv->commander, "LIST %s", line);
	return (true);
}
