/*
** EPITECH PROJECT, 2018
** Project
** File description:
** send_file.c
*/

#include <client.h>
#include <sys/stat.h>
#include "client.h"

static char *convert_cmd(char *cmd)
{
	char *ret;

	if (!cmd)
		return (NULL);
	ret = safe_malloc(sizeof(char) * (strlen(cmd) + 3));
	ret[0] = 1;
	memcpy(ret + 1, cmd, strlen(cmd));
	ret[strlen(cmd) + 1] = 1;
	ret[strlen(cmd) + 2] = '\0';
	free(cmd);
	return (ret);
}

static void add_sock_in_serv(sess_t *sess, int fd, int sock, char *filename)
{
	sess->send_serv = realloc(sess->send_serv, sizeof(send_file_t) *
	(sess->nb_send_serv + 1));
	sess->send_serv[sess->nb_send_serv].serv = sock;
	sess->send_serv[sess->nb_send_serv].client = 0;
	sess->send_serv[sess->nb_send_serv].file = strdup(filename);
	sess->send_serv[sess->nb_send_serv].fd_file = fd;
	sess->nb_send_serv += 1;
	poll_add(&sess->pl, sock, POLLIN);
}

bool send_file(sess_t *sess, int fd, char *nick, char *filename) //TODO Coding Style
{
	ip_t ip;
	struct stat s;
	char *to_send;
	uint16_t port;
	int sock;

	if (fstat(fd, &s) == -1)
		return (false);
	sess->printfChan(sess, "master", "Send \"%s\" to %s", filename, nick);
	sock = create_random_serv(&port);
	ip = convert_ip(sock);
	if (ip.val == 0 || sock == -1)
		return (false);
	to_send = convert_cmd(asendf("DCC SEND %s %u %d %u", filename,
		ip.val, port, s.st_size));
	sess->serv->commander->push(sess->serv->commander,
			"PRIVMSG %s :%s", nick, to_send);
	add_sock_in_serv(sess, fd, sock, filename);
	free(to_send);
	return (true);
}