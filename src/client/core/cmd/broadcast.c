/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool cmd_broadcast(sess_t *sess, char *line)
{
	if (!strcmp(sess->cur_chan->name, "master")) {
		sess->printfChan(sess, "master", "You cannot speak here");
		return (true);
	}
	sess->printfChan(
		sess, sess->cur_chan->name, "%s: %s", sess->nickname, line);
	sess->serv->commander->push(sess->serv->commander, "PRIVMSG %s :%s",
		sess->cur_chan->name, line);
	return (true);
}
