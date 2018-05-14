/*
** EPITECH PROJECT, 2018
** Project
** File description:
** str_tolower.c
*/

#include <stddef.h>
#include <ctype.h>

void str_tolower(char *str)
{
	size_t idx = 0;

	while (str && str[idx]) {
		str[idx] = (char) tolower(str[idx]);
		idx++;
	}
}