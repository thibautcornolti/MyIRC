/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool get_event_ui(ui_t *this)
{
	char c = 0;

	while (read(0, &c, 1) > 0) {
		if (c >= 32 && c <= 126) {
			this->buffer[this->buffer_idx % this->buffer_size] = c;
			this->buffer_idx++;
		}
	}
	this->buffer_last = c;
	return (errno == EAGAIN);
}

static void process_event_spec(ui_t *this)
{
	if (this->buffer_last == 27) {
		this->hasToQuit = true;
	} else if (this->buffer_last == '\t') {
		this->session->cur_chan = this->session->cur_chan->next;
		if (!this->session->cur_chan)
			this->session->cur_chan = this->session->chan;
		this->w_chan->update(this->w_chan);
		this->w_logs->update(this->w_logs);
	}
}

void process_event_ui(ui_t *this)
{
	char c = this->buffer_last;

	if (c == 127) {
		if (this->buffer_idx > 0)
			this->buffer_idx--;
		this->buffer[this->buffer_idx % this->buffer_size] = 0;
	} else if ((c == 13 || c == 10) && strlen(this->buffer) &&
		do_cmd(this)) {
		this->buffer_idx = 0;
		memset(this->buffer, 0, this->buffer_size);
	} else
		process_event_spec(this);
	this->w_chat->update(this->w_chat);
}
