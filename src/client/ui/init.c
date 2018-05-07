/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"
#include "common.h"

ui_t *create_ui()
{
	ui_t *ui;

	ui = safe_malloc(sizeof(ui_t));
	ui->init = &init_ui;
	ui->stop = &stop_ui;
	ui->update = &update_ui;
	ui->getEvent = &get_event_ui;
	ui->processEvent = &process_event_ui;
	ui->initWindows = &init_windows;
	ui->stopWindows = &stop_windows;
	ui->framecap = 10000;
	ui->buffer_size = 1025;
	ui->buffer = safe_malloc(ui->buffer_size + 1);
	ui->w_chat = create_window(ui, &update_w_cli);
	return (ui);
}

void init_ui(ui_t *this)
{
	int flags;

	initscr();
	noecho();
	curs_set(FALSE);
	start_color();
	flags = fcntl(0, F_GETFL, 0);
	fcntl(0, F_SETFL, flags | O_NONBLOCK);
	this->initWindows(this);
}

void stop_ui(ui_t *this)
{
	endwin();
	free(this->buffer);
	free(this);
}

void init_windows(ui_t *this)
{
	this->w_chat->init(this->w_chat);
}

void stop_windows(ui_t *this)
{
	this->w_chat->stop(this->w_chat);
}
