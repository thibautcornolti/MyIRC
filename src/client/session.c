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
	sess->nickname = strdup(getlogin());
	return (sess);
}