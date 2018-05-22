/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static bool cmd_server_connect(serv_t *serv, char *ip, char *port)
{
	struct addrinfo *result = NULL;
	int ret = 1;

	if (getaddrinfo(ip, port, NULL, &result) == 0) {
		while (result && ret) {
			ret = connect(
				serv->fd, result->ai_addr, result->ai_addrlen);
			result = result->ai_next;
		}
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

static void cmd_server_prepare(sess_t *sess, char *host, char *port)
{
	errno = 0;
	if (sess->serv->connected) {
		sess->printChan(sess, "master", "Disconnected!");
		sess->cleanChans(sess);
		close(sess->serv->fd);
	}
	sess->serv->connected = false;
	sess->serv->host = strdup(host);
	sess->serv->port = atoi(port);
}

static void cmd_server_process_post_cmd(sess_t *sess, bool prepare)
{
	static bool was_connected;
	serv_t *serv = sess->serv;

	if (prepare)
		was_connected = serv->connected;
	else if (was_connected && serv->connected) {
		serv->commander->push(serv->commander,
			"USER %s 127.0.0.1 server %s", getlogin(), getlogin());
		serv->commander->push(
			serv->commander, "NICK %s", sess->nickname);
	}
}

bool cmd_server(sess_t *sess, char *line)
{
	bool res = true;
	char *host = get_host(line);
	char *port = get_port(line);

	cmd_server_process_post_cmd(sess, true);
	cmd_server_prepare(sess, host, port);
	if (!cmd_server_init(sess->serv) ||
		!cmd_server_connect(sess->serv, host, port)) {
		if (errno)
			sess->printChan(sess, "master", strerror(errno));
		res = false;
	}
	else {
		sess->serv->connected = true;
		sess->printChan(sess, "master", "Connected!");
		poll_add(&sess->pl, sess->serv->fd, POLLIN | POLLOUT);
	}
	cmd_server_process_post_cmd(sess, false);
	free(host);
	return (res);
}
