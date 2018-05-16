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

void *safe_realloc(void *ptr, size_t old_size, size_t size)
{
	void *ret = safe_malloc(size);

	if (ptr && old_size > 0)
		memcpy(ret, ptr, old_size);
	return (ret);
}
