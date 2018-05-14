/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"
#include "common.h"

sess_t *create_sess()
{
	sess_t *sess;

	sess = safe_malloc(sizeof(sess_t));
	sess->nickname = strdup("iencli");
	return (sess);
}