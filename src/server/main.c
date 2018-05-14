/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <zconf.h>
#include <server.h>
#include "server.h"

static void core(int serv)
{
	server_t s;
	int inf = 1;

	s.clients = NULL;
	s.poll = NULL;
	poll_add(&s.poll, serv, POLLIN);
	while (inf) {
		poll_wait(s.poll, -1);
		if (poll_canread(s.poll, serv))
			accept_client(serv, &s.clients, &s.poll);
		read_all_cli(&s);
		write_all_cli(&s);
		update_write_poll(s.clients, s.poll);
	}
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