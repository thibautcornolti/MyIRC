/*
** EPITECH PROJECT, 2018
** Project
** File description:
** data_sendf.c
*/

#include <stdarg.h>
#include "server.h"

static int place_arg(va_list *list, char **str, size_t *i)
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

int msg_sendf(data_send_t **ds, const char *model, ...)
{
	size_t i = 0;
	va_list list;
	char *str = strdup(model);

	if (!str)
		return (0);
	va_start(list, model);
	while (str && str[i]) {
		if (str[i] == '%')
			place_arg(&list, &str, &i);
		i++;
	}
	va_end(list);
	msg_send(ds, str);
	free(str);
	return (1);
}