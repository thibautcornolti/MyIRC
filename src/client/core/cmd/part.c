/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool cmd_part(sess_t *sess, char *line)
{
	char **cmd = split_cmd(line);

	if (!cmd)
		return (false);
	if (len_array((void **)cmd) == 1 && strlen(cmd[0]))
		sess->serv->commander->push(
			sess->serv->commander, "PART %s", cmd[0]);
	else if (len_array((void **)cmd) >= 2)
		sess->serv->commander->push(
			sess->serv->commander, "PART %s :%s", cmd[0], cmd[1]);
	else if (strcmp(sess->cur_chan->name, "master"))
		sess->serv->commander->push(sess->serv->commander, "PART %s",
			sess->cur_chan->name);
	else
		sess->printChan(sess, "master", "You cannot leave master");
	free_array((void **)cmd);
	return (true);
}
