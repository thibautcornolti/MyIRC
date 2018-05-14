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

typedef struct
{
	char *cmd;
	char **args;
	size_t ac;
} cmd_t;

typedef struct
{
	client_t *clients;
	poll_t *poll;
} server_t;

typedef struct
{
	char *name;
	void (*fnt)(server_t *, client_t *, cmd_t *);
} cmd_list_t;


int create_server(uint16_t port);

int accept_client(int sock_serv, client_t **cli, poll_t **p);

size_t nb_client(client_t *cli);
int client_add(client_t **cli, client_t *to_add);
int client_rm(client_t **cli, client_t *to_rm);

void read_all_cli(server_t *s);

void write_all_cli(server_t *server);

void update_write_poll(client_t *cli, poll_t *p);

int msg_send(data_send_t **ds, char *data);
void msg_send_clear(data_send_t **ds);

char *read_sock(client_t *cli);
int send_sock(client_t *cli, char *msg);

void free_cmd(cmd_t *cmd);
cmd_t *parse_cmd(char *str);

int exec_cmd(server_t *serv, client_t *cli, cmd_t *cmd);

int msg_sendf(data_send_t **ds, const char *model, ...);
int place_char(va_list *list, char **str, const size_t *i);
int place_str(va_list *list, char **str, size_t *i);
int place_int(va_list *list, char **str, size_t *i);
int place_unsigned_int(va_list *list, char **str, size_t *i);

/*
** FNT
*/

void nick_cmd(server_t *server, client_t *cli, cmd_t *cmd);
void user_cmd(server_t *server, client_t *cli, cmd_t *cmd);

#endif /* !PROJECT_SERVER_H */
