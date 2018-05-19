/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool do_srv(ui_t *ui)
{
	push_log_in_chan(ui, "master", ui->session->serv->buffer);
	return (true);
}
