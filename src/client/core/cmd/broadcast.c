/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool cmd_broadcast(ui_t *ui, char *line)
{
	if (!strcmp(ui->session->cur_chan->name, "master")) {
		push_log_chanf(ui, "master", "You cannot speak here");
		return (true);
	}
	push_log_chanf(ui, ui->session->cur_chan->name, "%s: %s",
	ui->session->nickname, line);
	ui->session->serv->commander->push(ui->session->serv->commander,
	"PRIVMSG %s :%s", ui->session->cur_chan->name, line);
	return (true);
}
