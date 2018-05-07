/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "server.h"

static int core(int serv)
{
	return (0);
}

int main(int ac, char **av)
{
	uint16_t port;
	int serv;

	if (ac != 2 || !is_positive_integer(av[1], 65535)) {
		dprintf(2, "USAGE: %s PORT\n", av[0]);
		return (EXIT_FAILURE);
	}
	port = (uint16_t) atoi(av[1]);
	serv = create_server(port);
	if (serv == -1)
		return (EXIT_FAILURE);
	core(serv);
	return (EXIT_SUCCESS);
}