/*
** EPITECH PROJECT, 2018
** Project
** File description:
** push_log.c
*/

#include "client.h"

static int is_chan_exist(sess_t *this, char *name)
{
	chan_t *chan = this->chan;

	while (chan) {
		if (!strcmp(chan->name, name))
			return (1);
		chan = chan->next;
	}
	return (0);
}

void printf_chan(sess_t *this, char *name, char *model, ...)
{
	char *msg;
	chan_t *chan = this->chan;
	va_list list;

	va_start(list, model);
	msg = sendf(model, list);
	if (!is_chan_exist(this, name))
		this->addChan(this, name);
	while (chan) {
		if (!strcmp(chan->name, name)) {
			chan->logger->log(chan->logger, msg);
			if (chan != this->cur_chan)
				chan->update = true;
			return;
		}
		chan = chan->next;
	}
	va_end(list);
}

void print_chan(sess_t *this, char *name, char *msg)
{
	chan_t *chan = this->chan;

	if (!is_chan_exist(this, name))
		this->addChan(this, name);
	while (chan) {
		if (!strcmp(chan->name, name)) {
			chan->logger->log(chan->logger, msg);
			if (chan != this->cur_chan)
				chan->update = true;
			return;
		}
		chan = chan->next;
	}
}