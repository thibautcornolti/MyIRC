/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"
#include "common.h"

static void run()
{
	ui_t *ui = create_ui();

	ui->init(ui);
	set_master_ui(ui);
	while (ui->getEvent(ui))
		ui->update(ui);
	ui->stop(ui);
}

int main()
{
	run();
	return (EXIT_SUCCESS);
}