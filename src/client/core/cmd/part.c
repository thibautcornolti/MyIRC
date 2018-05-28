/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static void cmd_part_internal(sess_t *sess, commander_t *cmder)
{
	if (strcmp(sess->cur_chan->name, "master"))
		cmder->push(cmder, "PART %s", sess->cur_chan->name);
	else
		sess->printChan(sess, "master", "You cannot leave master");
}

bool cmd_part(sess_t *sess, char *line)
{
	commander_t *cmder = sess->serv->commander;
	char **cmd = split_cmd(line);

	if (!cmd)
		return (false);
	if (len_array((void **)cmd) == 1 && strlen(cmd[0]))
		cmder->push(cmder, "PART %s", cmd[0]);
	else if (len_array((void **)cmd) >= 2)
		cmder->push(cmder, "PART %s :%s", cmd[0], cmd[1]);
	else
		cmd_part_internal(sess, cmder);
	free_array((void **)cmd);
	return (true);
}
