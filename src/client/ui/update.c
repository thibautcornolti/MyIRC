/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"
#include "common.h"

void update_ui(ui_t *this)
{
	usleep(this->framecap);
	clear();
	refresh();
	this->w_chat->update(this->w_chat);
	this->w_chan->update(this->w_chan);
	this->w_info->update(this->w_info);
	this->w_logs->update(this->w_logs);
}
