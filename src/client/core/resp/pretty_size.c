/*
** EPITECH PROJECT, 2018
** Project
** File description:
** pretty_size.c
*/

#include "client.h"

static size_t len_number(unsigned long nb)
{
	size_t ret = 1;

	while (nb > 9) {
		ret += 1;
		nb /= 10;
	}
	return (ret);
}

static void place_uint_in_str(char *str, unsigned long nb, size_t len)
{
	size_t i = 1;

	if (nb == 0)
		str[0] = '0';
	while (nb > 0) {
		str[len - i] = (char) (nb % 10 + '0');
		nb /= 10;
		i += 1;
	}
}

static char *ret_size(unsigned long val, char *unit)
{
	size_t len = len_number(val);
	char *ret = safe_malloc(sizeof(char) * (len + strlen(unit) + 2));

	memset(ret, 0, sizeof(char) * (len + strlen(unit) + 2));
	memset(ret, ' ', sizeof(char) * (len + strlen(unit) + 1));
	place_uint_in_str(ret, val, len);
	memcpy(ret + len + 1, unit, strlen(unit));
	return (ret);
}

char *pretty_size(char *size_c)
{
	unsigned long size = (unsigned long) strtol(size_c, NULL, 10);
	char *unit[] = {"o", "ko", "mo", "go", NULL};
	unsigned long cond[] = {size, size / 1024, size / 1048576,
				size / 1073741824, 0};
	int i = 0;

	while (cond[i + 1] > 0)
		i += 1;
	return (ret_size(cond[i], unit[i]));
}