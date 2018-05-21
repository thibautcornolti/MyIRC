/*
** EPITECH PROJECT, 2018
** Project
** File description:
** place_str.c
*/

#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int place_str(va_list list, char **str, size_t *i)
{
	char *arg = va_arg(list, char *);

	*str = realloc(*str, sizeof(char *) + (strlen(*str) + strlen(arg)));
	if (!*str)
		return (0);
	memmove(*str + *i + strlen(arg), *str + *i + 2, strlen(*str) -
	(*i + 1));
	memmove(*str + *i, arg, strlen(arg));
	*i += strlen(arg) - 1;
	return (str != NULL);
}