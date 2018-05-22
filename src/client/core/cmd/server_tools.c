/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

char *get_host(char *line)
{
	size_t len = 0;

	for (; line[len] && line[len] != ':'; len++)
		;
	return (strndup(line, len));
}

char *get_port(char *line)
{
	size_t len = 0;
	char *res = "194";

	for (; line[len] && line[len] != ':'; len++)
		;
	if (line[len] == ':')
		res = line + len + 1;
	return (res);
}
