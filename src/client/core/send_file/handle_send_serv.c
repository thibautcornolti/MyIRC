/*
** EPITECH PROJECT, 2018
** Project
** File description:
** handle_send_serv.c
*/

#include <sys/stat.h>
#include "client.h"

static void handle_accept_client(sess_t *sess, size_t i)
{
	if (poll_canread(sess->pl, sess->send_serv[i].serv)) {
		sess->send_serv[i].client = accept(sess->send_serv[i]
		.serv, NULL, NULL);
		if (sess->send_serv[i].client == -1)
			return;
		poll_rm(&sess->pl, sess->send_serv[i].serv);
		poll_add(&sess->pl, sess->send_serv[i].client, POLLOUT |
		POLLHUP | POLLIN);
		close(sess->send_serv[i].serv);
	}
}

static bool handle_transfert(sess_t *sess, size_t i, bool state)
{
	sess->printfChan(sess, "master", "Transfer %s (\"%s\")",
	(state) ? "complete" : "failed", sess->send_serv[i].file);
	close(sess->send_serv[i].client);
	close(sess->send_serv[i].fd_file);
	free(sess->send_serv[i].file);
	if (i < sess->nb_send_serv)
		memmove(sess->send_serv + i, sess->send_serv +
		i + 1, sess->nb_send_serv - i - 1);
	sess->nb_send_serv -= 1;
	sess->send_serv = realloc(sess->send_serv,
	sizeof(send_file_t) * sess->nb_send_serv);
	return (false);
}

static bool handle_write_client(sess_t *sess, size_t i)
{
	char tmp[512];
	ssize_t size_read;
	ssize_t size_write;

	if (sess->send_serv[i].client > 0 && poll_canwrite(sess->pl,
	sess->send_serv[i].client)) {
		size_read = read(sess->send_serv[i].fd_file, tmp, 512);
		size_write = write(sess->send_serv[i].client, tmp, (size_t)
		size_read);
		if (size_write == 0 && size_read != 0)
			return (handle_transfert(sess, i, false));
	}
	return (true);
}

static bool handle_end_of_read(sess_t *sess, size_t i)
{
	struct stat s;
	uint32_t rsize;

	if (sess->send_serv[i].client > 0 && poll_canread(sess->pl,
		sess->send_serv[i].client)) {
		read(sess->send_serv[i].client, &rsize, 4);
		if (fstat(sess->send_serv[i].fd_file, &s) == -1)
			return (true);
		if (swap_endian(rsize) >= s.st_size)
			return (handle_transfert(sess, i, true));
	}
	return (true);
}

void handle_send_serv(ui_t *ui)
{
	size_t i = 0;

	while (i < ui->session->nb_send_serv) {
		handle_accept_client(ui->session, i);
		if (handle_write_client(ui->session, i) &&
		handle_end_of_read(ui->session, i))
			i += 1;
		else
			ui->w_logs->update(ui->w_logs);
	}
}