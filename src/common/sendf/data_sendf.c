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

char *sendf(const char *model, va_list list)
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