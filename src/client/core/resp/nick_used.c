/*
** EPITECH PROJECT, 2018
** Project
** File description:
** list.c
*/

#include "client.h"

void resp_nick_used(ui_t *this, char **list)
{
	int len_nick = strlen(this->session->nickname);
	char *new_nick = safe_realloc(
		this->session->nickname, len_nick + 1, len_nick + 2);

	(void) list;
	new_nick[len_nick] = '_';
	this->session->printfChan(this->session, "master",
		"Nick %s already used, trying %s", this->session->nickname,
		new_nick);
	this->session->serv->commander->push(
		this->session->serv->commander, "NICK %s", new_nick);
	free(this->session->nickname);
	this->session->nickname = new_nick;
}