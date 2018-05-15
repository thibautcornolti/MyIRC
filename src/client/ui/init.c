/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

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
	this->stopWindows(this);
	endwin();
	free(this->buffer);
	free(this);
}

void init_windows(ui_t *this)
{
	this->w_chat->init(this->w_chat);
	this->w_chan->init(this->w_chan);
	this->w_info->init(this->w_info);
	this->w_logs->init(this->w_logs);
}

void stop_windows(ui_t *this)
{
	this->w_chat->stop(this->w_chat);
	this->w_chan->stop(this->w_chan);
	this->w_info->stop(this->w_info);
	this->w_logs->stop(this->w_logs);
}
