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
int client_rm(client_t **cli, client_t *to_rm);

void read_all_cli(client_t **cli, poll_t **p);

void write_all_cli(client_t *cli, poll_t *p);

void update_write_poll(client_t *cli, poll_t *p);

int data_send_add(data_send_t **ds, char *data);
void data_send_clear(data_send_t **ds);

char *read_sock(client_t *cli);
int send_sock(client_t *cli, char *msg);

#endif /* !PROJECT_SERVER_H */
