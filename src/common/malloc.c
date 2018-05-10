/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "common.h"

void *safe_malloc(size_t size)
{
	void *ret = malloc(size);

	if (ret == NULL) {
		perror("Error when allocating");
		exit(EXIT_FAILURE);
	}
	memset(ret, 0, size);
	return (ret);
}
