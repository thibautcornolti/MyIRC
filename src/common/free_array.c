/*
** EPITECH PROJECT, 2018
** Project
** File description:
** free_array.c
*/

#include <glob.h>
#include <stdlib.h>

void free_array(void **arr)
{
	size_t i = 0;

	while (arr[i]) {
		free(arr[i]);
		i += 1;
	}
	free(arr);
}