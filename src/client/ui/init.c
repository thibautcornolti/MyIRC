/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

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
	init_pair(1, COLOR_RED, COLOR_BLACK);
	this->session->printChan(
		this->session, "master", "Welcome to my IRC client!");
}

void free_ui(ui_t *this)
{
	this->freeWindows(this);
	endwin();
	this->session->free(this->session);
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

void free_windows(ui_t *this)
{
	this->w_chat->free(this->w_chat);
	this->w_chan->free(this->w_chan);
	this->w_info->free(this->w_info);
	this->w_logs->free(this->w_logs);
}
