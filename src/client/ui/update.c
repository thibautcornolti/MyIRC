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
}
