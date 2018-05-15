/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

ui_t *set_master_ui(ui_t *ui)
{
	static ui_t *save = NULL;

	if (ui)
		save = ui;
	return (save);
}

void sig_handler(int sig)
{
	ui_t *ui = get_master_ui();

	ui->stop(ui);
	(void) sig;
}
