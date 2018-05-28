/*
** EPITECH PROJECT, 2018
** Project
** File description:
** free_chan.c
*/

#include "client.h"

void free_chan(struct sess_s *this)
{
	chan_t *chan = this->chan;
	chan_t *cpy;

	while (chan) {
		cpy = chan->next;
		chan->logger->free(chan->logger);
		free(chan->name);
		free(chan);
		chan = cpy;
	}
	this->chan = NULL;
}

void clean_chans(struct sess_s *this)
{
	chan_t *chan = this->chan->next;
	chan_t *next;

	this->cur_chan = this->chan;
	while (chan) {
		next = chan->next;
		this->rmChan(this, chan->name);
		chan = next;
	}
}
