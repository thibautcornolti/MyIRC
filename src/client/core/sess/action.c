/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

bool do_srv(ui_t *ui)
{
	ui->session->logger->log(ui->session->logger, ui->session->serv->buffer);
	return (true);
}
