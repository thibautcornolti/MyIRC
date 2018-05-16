/*
** EPITECH PROJECT, 2018
** Project
** File description:
** data_sendf.c
*/

#include <stdarg.h>
#include "server.h"

static int place_arg(va_list list, char **str, size_t *i)
{
	switch ((*str)[(*i) + 1]) {
		case 'c':
			return place_char(list, str, i);
		case 'd':
			return place_int(list, str, i);
		case 'u':
			return place_unsigned_int(list, str, i);
		case 's':
			return place_str(list, str, i);
		default:
			break;
	}
	return (0);
}

static char *sendf(const char *model, va_list list)
{
	size_t i = 0;
	char *str = strdup(model);

	if (!str)
		return (NULL);
	while (str && str[i]) {
		if (str[i] == '%' && !place_arg(list, &str, &i))
			return (NULL);
		i++;
	}
	return (str);
}

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