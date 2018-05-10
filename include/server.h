/*
** EPITECH PROJECT, 2018
** Project
** File description:
** server.h
*/

#ifndef PROJECT_SERVER_H
	#define PROJECT_SERVER_H

	#include <stdint.h>
	#include "common.h"

typedef struct data_send_s
{
	char *data;
	struct data_send_s *next;
} data_send_t;

typedef struct client_s
{
	int log_state;
	int fd;
	char *nickname;
	data_send_t *to_send;
	struct client_s *next;
} client_t;

int create_server(uint16_t port);

int accept_client(int sock_serv, client_t **cli, poll_t **p);

size_t nb_client(client_t *cli);
int client_add(client_t **cli, client_t *to_add);

void read_all_cli(client_t **cli, poll_t **p);

#endif /* !PROJECT_SERVER_H */
