/*
** EPITECH PROJECT, 2018
** Project
** File description:
** handle_get_file.c
*/

#include "client.h"

static void end_trans(get_file_t *get_file)
{
	close(get_file->fd_file);
	close(get_file->serv);
	get_file->state = 2;
}

static void handle_get_part_file(sess_t *this, get_file_t *get_file)
{
	char tmp[512];
	ssize_t size;

	size = read(get_file->serv, tmp, 512);
	if (size == 0) {
		this->printfChan(this, get_file->nick,
		"Transfer finished (%s)", get_file->name);
		end_trans(get_file);
		return;
	}
	write(get_file->fd_file, tmp, (size_t) size);
	get_file->size_dl += size;
}

static void send_size_dl(get_file_t *get_file)
{
	uint32_t to_send = swap_endian((uint32_t) get_file->size_dl);

	write(get_file->serv, &to_send, sizeof(uint32_t));
}

static void handle_end_transfer(ui_t *this, get_file_t *get_file)
{
	if (get_file->size_dl >= get_file->size_tot) {
		this->session->printfChan(this->session, get_file->nick,
		"Transfer finished (%s)", get_file->name);
		end_trans(get_file);
		this->w_logs->update(this->w_logs);
	}
}

void handle_get_file(ui_t *this)
{

	for (size_t i = 0; i < this->session->nb_get_file; i++) {
		if (this->session->get_file[i].state == 1 &&
		poll_canread(this->session->pl, this->session->get_file[i]
		.serv)) {
			handle_get_part_file(this->session, &this->session->
			get_file[i]);
			send_size_dl(&this->session->get_file[i]);
		}
		if (this->session->get_file[i].state == 1)
			handle_end_transfer(this, &this->session->get_file[i]);
	}
}