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
	poll_add(&sess->pl, 0, POLLIN);
	sess->serv = create_serv();
	sess->logger = create_logger();	
	sess->nickname = strdup(getlogin());
	return (sess);
}

serv_t *create_serv()
{
	serv_t *serv;

	serv = safe_malloc(sizeof(serv_t));
	serv->buffer_size = 10240;
	serv->buffer = safe_malloc(serv->buffer_size + 1);
	return (serv);
}
