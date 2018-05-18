/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

sess_t *create_sess()
{
	sess_t *sess;

	sess = safe_malloc(sizeof(sess_t));
	sess->free = &free_sess;
	poll_add(&sess->pl, 0, POLLIN);
	sess->serv = create_serv();
	sess->logger = create_logger();	
	sess->nickname = strdup(getlogin());
	return (sess);
}

void free_sess(sess_t *this)
{
	this->serv->free(this->serv);
	this->logger->free(this->logger);
	free(this->nickname);
	free(this);
}

serv_t *create_serv()
{
	serv_t *serv;

	serv = safe_malloc(sizeof(serv_t));
	serv->free = &free_serv;
	serv->buffer_size = 10240;
	serv->buffer = safe_malloc(serv->buffer_size + 1);
	serv->commander = create_commander();
	return (serv);
}

void free_serv(serv_t *this)
{
	this->commander->free(this->commander);
	free(this->buffer);
	free(this);
}