/*
** EPITECH PROJECT, 2018
** Project
** File description:
** free_data_msg.c
*/

#include "server.h"

void free_data_msg(data_send_t *data)
{
	data_send_t *tmp;

	while (data) {
		tmp = data->next;
		free(data->data);
		free(data);
		data = tmp;
	}
}