/*
** EPITECH PROJECT, 2018
** Project
** File description:
** str_toupper.c
*/

#include <stddef.h>
#include <ctype.h>

void str_toupper(char *str)
{
	size_t idx = 0;

	while (str && str[idx]) {
		str[idx] = (char) toupper(str[idx]);
		idx++;
	}
}