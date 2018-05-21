/*
** EPITECH PROJECT, 2018
** Project
** File description:
** part.c
*/

#include "client.h"

void resp_part(ui_t *this, char **resp)
{
	char *nick = get_nickname(resp[0]);

	if (!nick)
		return;
	if (!strcmp(this->session->nickname, nick)) {
		if (!strcmp(this->session->cur_chan->name, resp[2]))
			this->session->cur_chan = this->session->chan;
		rm_chan(&this->session->chan->next, resp[2]);
		this->w_chan->update(this->w_chan);
		this->w_logs->update(this->w_logs);
	} else {
		push_log_chanf(this, resp[2], "%s leave this channel (\"%s\")",
		nick, (len_array((void **) resp) >= 4) ? resp[3] : "");
	}
}