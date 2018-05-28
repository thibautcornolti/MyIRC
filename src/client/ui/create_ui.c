/*
** EPITECH PROJECT, 2018
** Project
** File description:
** create_ui.c
*/

#include "client.h"

static void create_ui_2(ui_t *ui)
{
	ui->init = &init_ui;
	ui->free = &free_ui;
	ui->update = &update_ui;
	ui->getEvent = &get_event_ui;
	ui->processEvent = &process_event_ui;
	ui->initWindows = &init_windows;
	ui->freeWindows = &free_windows;
	ui->getServerEvent = &get_event_serv;
	ui->processServerEvent = &process_event_serv;
	ui->sendServerEvent = &send_event_serv;
	ui->fileEvent = &handle_transfer;
}

ui_t *create_ui(void)
{
	ui_t *ui;

	ui = safe_malloc(sizeof(ui_t));
	create_ui_2(ui);
	ui->framecap = 70000;
	ui->hasToQuit = false;
	ui->buffer_size = 1025;
	ui->buffer = safe_malloc(ui->buffer_size + 1);
	ui->session = create_sess();
	ui->w_chat = create_window(ui, &update_w_chat);
	ui->w_chan = create_window(ui, &update_w_chan);
	ui->w_info = create_window(ui, &update_w_info);
	ui->w_logs = create_window(ui, &update_w_logs);
	return (ui);
}