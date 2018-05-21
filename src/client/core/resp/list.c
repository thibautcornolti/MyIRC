/*
** EPITECH PROJECT, 2018
** Project
** File description:
** list.c
*/

#include "client.h"

void resp_end_list(ui_t *this, char **list)
{
	(void)list;
	this->session->printChan(
		this->session, "master", "End of channel list");
}

void resp_list(ui_t *this, char **list)
{
	if (len_array((void **)list) < 5)
		return;
	this->session->printfChan(
		this->session, "master", "%s (%s user(s))", list[3], list[4]);
}