/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static void send_msg_with_chan(sess_t *sess, char **cmd)
{
	if (!strcmp(cmd[0], "master")) {
		sess->printfChan(sess, "master", "You cannot speak here");
		return;
	}
	sess->printfChan(sess, cmd[0], "%s: %s", sess->nickname, cmd[1]);
	sess->serv->commander->push(sess->serv->commander,
	"PRIVMSG %s :%s", cmd[0], cmd[1]);
}

static void send_msg_without_channel(sess_t *sess, char **cmd)
{
	if (!strcmp(sess->cur_chan->name, "master")) {
		sess->printfChan(sess, "master", "You cannot speak here");
		return;
	}
	sess->printfChan(sess, sess->cur_chan->name, "%s: %s", sess->nickname,
	cmd[0]);
	sess->serv->commander->push(sess->serv->commander,
	"PRIVMSG %s :%s", sess->cur_chan->name, cmd[0]);
}

bool cmd_msg(sess_t *sess, char *line)
{
	char **cmd = split_cmd(line);

	if (!cmd)
		return (false);
	if (len_array((void **) cmd) == 1)
		send_msg_without_channel(sess, cmd);
	else if (len_array((void **) cmd) >= 2)
		send_msg_with_chan(sess, cmd);
	free_array((void **) cmd);
	return (true);
}
