/*
** EPITECH PROJECT, 2018
** Project
** File description:
** parse_get_file.c
*/

#include <client.h>
#include "client.h"

void init_get_file(ui_t *this, char **line, char *nick)
{
	ip_t ip;
	get_file_t *tmp;

	this->session->get_file = realloc(this->session->get_file,
	sizeof(get_file_t) * (this->session->nb_get_file + 1));
	if (!this->session->get_file)
		exit(84);
	tmp = &this->session->get_file[this->session->nb_get_file];
	memset(tmp, 0, sizeof(get_file_t));
	tmp->name = strdup(line[2]);
	tmp->port = (uint16_t) atol(line[4]);
	ip.val = (uint32_t) atol(line[3]);
	tmp->ip = asendf("%d.%d.%d.%d", ip.digit[3], ip.digit[2], ip.digit[1],
	ip.digit[0]);
	tmp->nick = strdup(nick);
	tmp->size_tot = (size_t) atoll(line[5]);
	this->session->nb_get_file += 1;
}