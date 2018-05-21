/*
** EPITECH PROJECT, 2018
** Project
** File description:
** join.c
*/

#include "client.h"

void resp_join(ui_t *ui, char **resp)
{
	char *nick = get_nickname(resp[0]);
	chan_t *chan_cpy = ui->session->chan;

	if (!nick)
		return;
	if (!strcmp(ui->session->nickname, nick))
		push_log_in_chan(ui, resp[2], "You have joined this channel");
	else
		push_log_chanf(ui, resp[2], "%s has joined this channel",
		nick);
	while (chan_cpy) {
		if (!strcmp(chan_cpy->name, resp[2])) {
			ui->session->cur_chan = chan_cpy;
			ui->w_logs->update(ui->w_logs);
			ui->w_chan->update(ui->w_chan);
		}
		chan_cpy = chan_cpy->next;
	}
}