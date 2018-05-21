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
		ui->session->printfChan(
			ui->session, "master", "You cannot speak here");
		return (true);
	}
	ui->session->printfChan(ui->session, ui->session->cur_chan->name,
		"%s: %s", ui->session->nickname, line);
	ui->session->serv->commander->push(ui->session->serv->commander,
		"PRIVMSG %s :%s", ui->session->cur_chan->name, line);
	return (true);
}
