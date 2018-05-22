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
	signal(SIGWINCH, sig_handler);
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
		ui->fileEvent(ui);
	}
	ui->free(ui);
}

int main()
{
//	char hostname[500]; //TODO rm debug
//
//	gethostname(hostname, 500);
//	struct hostent *t = gethostbyname(hostname);
//	int i = 0;
//	printf("Name: %s\n", t->h_name);
//	printf("Type: %d\n", t->h_addrtype);
//	printf("Len: %d\n", t->h_length);
//	while (t->h_addr_list[i]) {
//		printf("[%d] : %d.%d.%d.%d\n", i, t->h_addr_list[i][0],
//		t->h_addr_list[i][1], t->h_addr_list[i][2],
//		       t->h_addr_list[i][3]);
//		i ++;
//	}
//	return (0);
	run();
	return (EXIT_SUCCESS);
}