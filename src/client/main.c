/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static void run()
{
	ui_t *ui = create_ui();

	ui->init(ui);
	set_master_ui(ui);
	ui->update(ui);
	while (!ui->hasToQuit) {
		poll_wait(ui->session->pl, -1);
		if (poll_canread(ui->session->pl, 0)) {
			ui->getEvent(ui);
			ui->processEvent(ui);
		}
		if (ui->session->serv->connected &&
			poll_canread(ui->session->pl, ui->session->serv->fd)) {
			ui->getServerEvent(ui);
			ui->processServerEvent(ui);
		}
	}
	ui->stop(ui);
}

int main()
{
	run();
	return (EXIT_SUCCESS);
}