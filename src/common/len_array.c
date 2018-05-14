/*
** EPITECH PROJECT, 2018
** Project
** File description:
** len_array.c
*/

#include "common.h"

size_t len_array(void **arr)
{
	size_t ret = 0;

	while (arr && arr[ret])
		ret++;
	return (ret);
}