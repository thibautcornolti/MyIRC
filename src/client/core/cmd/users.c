/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool cmd_users(sess_t *sess, char *line)
{
	sess->serv->commander->push(sess->serv->commander, "USERS %s", line);
	return (true);
}
