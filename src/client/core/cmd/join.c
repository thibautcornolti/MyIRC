/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool cmd_join(sess_t *sess, char *line)
{
	sess->serv->commander->push(sess->serv->commander, "JOIN %s", line);
	return (true);
}
