/*
** EPITECH PROJECT, 2018
** Project
** File description:
** list.c
*/

#include "client.h"

void resp_end_list(ui_t *this, char **list)
{
	(void) list;
	push_log_in_chan(this, "master", "End of channel list");
}

void resp_list(ui_t *this, char **list)
{
	if (len_array((void **) list) < 5)
		return;
	push_log_chanf(this, "master", "%s (%s user(s))", list[3], list[4]);
}