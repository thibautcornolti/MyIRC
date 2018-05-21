/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool cmd_names(sess_t *sess, char *line)
{
	sess->serv->commander->push(sess->serv->commander, "NAMES %s", line);
	return (true);
}
