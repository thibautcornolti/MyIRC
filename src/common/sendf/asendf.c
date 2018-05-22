/*
** EPITECH PROJECT, 2018
** Project
** File description:
** asendf.c
*/

#include <stdio.h>
#include <zconf.h>
#include "common.h"

char *asendf(char *model, ...)
{
	char *ret;
	va_list list;

	va_start(list, model);
	ret = sendf(model, list);
	va_end(list);
	return (ret);
}