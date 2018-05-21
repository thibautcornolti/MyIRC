/*
** EPITECH PROJECT, 2018
** Project
** File description:
** list.c
*/

#include "client.h"

void resp_names(ui_t *ui, char **resp)
{
	char *tmp;

	if (len_array((void **) resp) < 6)
		return;
	tmp = safe_malloc(sizeof(char) * (strlen("Users: ") +
	strlen(resp[5]) + 1));
	memcpy(tmp, "Users: ", strlen("Users: "));
	memcpy(tmp + strlen("Users: "), resp[5], strlen(resp[5]));
	push_log_in_chan(ui, resp[4], tmp);
	free(tmp);
}