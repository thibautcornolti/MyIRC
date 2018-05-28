/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool get_event_serv(ui_t *this)
{
	serv_t *serv = this->session->serv;
	char c = 0;
	int r = 0;

	if (!serv->connected)
		return (false);
	while ((r = read(serv->fd, &c, 1)) > 0 && c != '\n' && c != '\r') {
		serv->buffer[serv->buffer_idx % serv->buffer_size] = c;
		serv->buffer_idx++;
	}
	serv->buffer_last = c;
	serv->buffer_last_nb = r;
	return (true);
}

void process_event_serv(ui_t *this)
{
	serv_t *serv = this->session->serv;
	char c = serv->buffer_last;

	if ((c == 13 || c == 10) && strlen(serv->buffer) && do_srv(this)) {
		serv->buffer_idx = 0;
		memset(serv->buffer, 0, serv->buffer_size);
	}
	if (serv->buffer_last_nb == 0) {
		serv->connected = false;
		this->session->printChan(
			this->session, "master", "Connection reset by peer!");
		serv->commander->push(serv->commander,
			"USER %s 127.0.0.1 server %s", getlogin(), getlogin());
		serv->commander->push(
			serv->commander, "NICK %s", this->session->nickname);
	}
	this->w_info->update(this->w_info);
	this->w_logs->update(this->w_logs);
	this->w_chan->update(this->w_chan);
}

void send_event_serv(ui_t *this)
{
	serv_t *serv = this->session->serv;

	dprintf(serv->fd, "%s\r\n", serv->commander->pop(serv->commander));
	this->w_info->update(this->w_info);
	this->w_logs->update(this->w_logs);
}
