/*
** EPITECH PROJECT, 2018
** Project
** File description:
** handle_transfer.c
*/

#include "client.h"

void handle_transfer(ui_t *this)
{
	handle_send_serv(this);
	handle_get_file(this);
}