/*
** EPITECH PROJECT, 2018
** Project
** File description:
** join.c
*/

#include "client.h"

void resp_join(ui_t *ui, char **resp)
{
	chan_t *chan_cpy = ui->session->chan;

	push_log_in_chan(ui, resp[2], "Vous avez rejoint le channel");
	while (chan_cpy) {
		if (!strcmp(chan_cpy->name, resp[2])) {
			ui->session->cur_chan = chan_cpy;
			ui->w_logs->update(ui->w_logs);
			ui->w_chan->update(ui->w_chan);
		}
		chan_cpy = chan_cpy->next;
	}
}