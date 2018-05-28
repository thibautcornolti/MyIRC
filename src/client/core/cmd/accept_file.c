/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static void accept_file(sess_t *sess, get_file_t *file)
{
	file->serv = create_client(file->ip, file->port);
	if (file->serv != -1)
		file->fd_file = open(file->name, O_WRONLY | O_CREAT |
		O_TRUNC, 0644);
	if (file->serv == -1 || file->fd_file == -1) {
		sess->printfChan(sess, file->nick, "Transfer failed (%s)",
		file->name);
		file->state = -1;
		return;
	}
	sess->printfChan(sess, file->nick, "Transfer start (%s)", file->name);
	file->state = 1;
}

bool cmd_accept_file(sess_t *sess, char *line)
{
	if (!strlen(line) && strcmp(sess->cur_chan->name, "master"))
		line = sess->cur_chan->name;
	for (size_t i = 0; i < sess->nb_get_file; i++)
		if (sess->get_file[i].state == 0 &&
		!strcmp(sess->get_file[i].nick, line)) {
			accept_file(sess, &sess->get_file[i]);
			poll_add(&sess->pl, sess->get_file[i].serv, POLLIN |
			POLLHUP);
		}
	return (true);
}
