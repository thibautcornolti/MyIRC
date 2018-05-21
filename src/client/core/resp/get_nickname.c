/*
** EPITECH PROJECT, 2018
** Project
** File description:
** get_nickname.c
*/

#include <stddef.h>
#include <string.h>

char *get_nickname(char *domaine)
{
	size_t idx = 0;

	while (domaine[idx] && strncmp(domaine + idx, "!~", 2) != 0)
		idx += 1;
	return strndup(domaine, idx);
}