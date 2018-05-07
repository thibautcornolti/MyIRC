/*
** EPITECH PROJECT, 2018
** Project
** File description:
** is_positive_integer.c
*/

#include <stddef.h>
#include <stdlib.h>

int is_positive_integer(const char *str, int max)
{
	size_t i = 0;
	int val;

	while (str && str[i]) {
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i += 1;
	}
	val = atoi(str);
	if (val > max)
		return (0);
	return (1);
}