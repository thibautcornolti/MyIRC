/*
** EPITECH PROJECT, 2018
** Project
** File description:
** swap_endian.c
*/

#include <stdint.h>

uint32_t swap_endian(uint32_t num)
{
	uint32_t swapped;
	swapped = ((num >> 24) & 0xff) | // move byte 3 to byte 0
		  ((num << 8) & 0xff0000) | // move byte 1 to byte 2
		  ((num >> 8) & 0xff00) | // move byte 2 to byte 1
		  ((num << 24) & 0xff000000);
	return (swapped);
}