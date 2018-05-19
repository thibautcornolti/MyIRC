/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static void wait_fd(ui_t *ui)
{
	if (ui->session->serv->connected &&
		ui->session->serv->commander->size(
			ui->session->serv->commander))
		poll_update(ui->session->pl, ui->session->serv->fd,
			POLLIN | POLLOUT);
	else if (ui->session->serv->connected)
		poll_update(ui->session->pl, ui->session->serv->fd, POLLIN);
	poll_wait(ui->session->pl, -1);
}

static void run() //TODO Coding style
{
	ui_t *ui = create_ui();

	ui->init(ui);
	set_master_ui(ui);
	ui->update(ui);
	while (!ui->hasToQuit) {
		wait_fd(ui);
		if (poll_canread(ui->session->pl, 0)) {
			ui->getEvent(ui);
			ui->processEvent(ui);
		}
		if (ui->session->serv->connected &&
			poll_canread(ui->session->pl, ui->session->serv->fd)) {
			ui->getServerEvent(ui);
			ui->processServerEvent(ui);
		}
		if (ui->session->serv->connected &&
			poll_canwrite(
				ui->session->pl, ui->session->serv->fd)) {
			ui->sendServerEvent(ui);
		}
	}
	ui->free(ui);
}

int main()
{
	run();
	return (EXIT_SUCCESS);
}