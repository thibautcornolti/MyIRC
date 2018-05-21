/*
** EPITECH PROJECT, 2018
** Project
** File description:
** push_log.c
*/

#include "client.h"

static int is_chan_exist(ui_t *this, char *name)
{
	chan_t *chan = this->session->chan;

	while (chan) {
		if (!strcmp(chan->name, name))
			return (1);
		chan = chan->next;
	}
	return (0);
}

void push_log_chanf(ui_t *this, char *name, char *model, ...)
{
	char *msg;
	chan_t *chan = this->session->chan;
	va_list list;

	va_start(list, model);
	msg = sendf(model, list);
	if (!is_chan_exist(this, name))
		add_chan(&this->session->chan, name);
	while (chan) {
		if (!strcmp(chan->name, name)) {
			chan->logger->log(chan->logger, msg);
			if (chan != this->session->cur_chan)
				chan->update = true;
			this->w_chan->update(this->w_chan);
			return;
		}
		chan = chan->next;
	}
	va_end(list);
}

void push_log_in_chan(ui_t *this, char *name, char *msg)
{
	chan_t *chan = this->session->chan;

	if (!is_chan_exist(this, name))
		add_chan(&this->session->chan, name);
	while (chan) {
		if (!strcmp(chan->name, name)) {
			chan->logger->log(chan->logger, msg);
			if (chan != this->session->cur_chan)
				chan->update = true;
			this->w_chan->update(this->w_chan);
			return;
		}
		chan = chan->next;
	}
}