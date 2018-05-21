/*
** EPITECH PROJECT, 2018
** Project
** File description:
** place_int.c
*/

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t size_int(int nb)
{
	size_t ret = 1;

	if (nb < 0) {
		ret += 1;
		nb *= -1;
	}
	while (nb > 9) {
		ret += 1;
		nb /= 10;
	}
	return (ret);
}

static void place_int_in_str(char *str, int nb, size_t len)
{
	size_t i = 1;

	if (nb < 0) {
		str[0] = '-';
		nb *= -1;
	}
	if (nb == 0) {
		str[0] = '0';
	}
	while (nb > 0) {
		str[len - i] = (char) (nb % 10 + '0');
		nb /= 10;
		i += 1;
	}
}

int place_int(va_list list, char **str, size_t *i)
{
	int arg = va_arg(list, int);
	size_t len = size_int(arg);

	*str = realloc(*str, sizeof(char *) + (strlen(*str) + len));
	if (!*str)
		return (0);
	memmove(*str + *i + len, *str + *i + 2, strlen(*str) -
							(*i + 1));
	place_int_in_str(*str + *i, arg, len);
	*i += len - 1;
	return (*str != NULL);
}