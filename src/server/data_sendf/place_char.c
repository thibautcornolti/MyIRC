/*
** EPITECH PROJECT, 2018
** Project
** File description:
** place_char.c
*/

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int place_char(va_list *list, char **str, const size_t *i)
{
	size_t len = strlen(*str);
	(*str)[*i] = (char) va_arg(*list, int);
	memmove((*str) + (*i) + 1, *str + (*i) + 2, strlen(*str) - ((*i) + 2));
	(*str)[len - 1] = '\0';
	*str = realloc(*str, sizeof(char *) * (strlen(*str)));
	return (str != NULL);
}