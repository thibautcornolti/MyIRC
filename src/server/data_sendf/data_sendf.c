/*
** EPITECH PROJECT, 2018
** Project
** File description:
** data_sendf.c
*/

#include <stdarg.h>
#include "server.h"

int msg_sendf(data_send_t **ds, const char *model, ...)
{
	va_list list;
	char *str;

	va_start(list, model);
	str = sendf(model, list);
	va_end(list);
	if (str)
		msg_send(ds, str);
	free(str);
	return (1);
}

void broadcast_channel(client_t *all_cli, char *chan_name, char *model, ...)
{
	va_list list;
	char *str;

	va_start(list, model);
	str = sendf(model, list);
	va_end(list);
	if (!str)
		return;
	while (all_cli) {
		if (channel_contain(all_cli->channel, chan_name))
			msg_send(&all_cli->to_send, str);
		all_cli = all_cli->next;
	}
	free(str);
}