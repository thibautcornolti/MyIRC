/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static bool cmd_server_connect(serv_t *serv, char *ip, int port)
{
	struct hostent *server = gethostbyname(ip);
	int ret = 1;

	if (server) {
		serv->s_in.sin_family = AF_INET;
		memcpy(server->h_addr, &serv->s_in.sin_addr.s_addr,
			server->h_length);
		serv->s_in.sin_port = htons(port);
		ret = connect(serv->fd, (struct sockaddr *)&serv->s_in,
			sizeof(serv->s_in));
	}
	return (ret == 0);
}

static bool cmd_server_init(serv_t *serv)
{
	bool res = true;

	serv->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (serv->fd == -1)
		res = false;
	else if (setsockopt(serv->fd, SOL_SOCKET, SO_REUSEADDR, &(int){1},
			 sizeof(int)) < 0)
		res = false;
	return (res);
}

static char *get_host(char *line)
{
	size_t len = 0;

	for (; line[len] && line[len] != ':'; len++)
		;
	return (strndup(line, len));
}

static int get_port(char *line)
{
	size_t len = 0;
	int res = 194;

	for (; line[len] && line[len] != ':'; len++)
		;
	if (line[len] == ':')
		res = atoi(line + len + 1);
	return (res);
}

bool cmd_server(sess_t *sess, char *line)
{
	bool res = true;
	char *host = get_host(line);
	int port = get_port(line);

	memset(&sess->serv, 0, sizeof(serv_t));
	sess->serv.host = strdup(host);
	sess->serv.port = port;
	if (!cmd_server_init(&sess->serv))
		res = false;
	else if (!cmd_server_connect(&sess->serv, host, port))
		res = false;
	else
		sess->serv.connected = true;
	free(host);
	return (res);
}
