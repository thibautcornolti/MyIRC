/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** sock_io.c
*/

#include <stdlib.h>
#include <zconf.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

static char *sock_io_split(char *line)
{
	char **tmp = split_str(line, "\n");
	char *ret;

	if (!tmp) {
		free(line);
		return (NULL);
	}
	if (tmp[0] && strlen(tmp[0]) != 0)
		ret = strdup(tmp[0]);
	else
		ret = strdup("");
	free_array((void **) tmp);
	free(line);
	return (ret);

}

char *read_sock(client_t *cli)
{
	char *ret = malloc(sizeof(char) * (512 + 1));
	size_t i = 0;
	ssize_t size = 512;

	if (!ret)
		return (0);
	memset(ret, 0, 512 + 1);
	while (size != 0 && strstr(ret, "\n") == NULL) {
		size = read(cli->fd, ret + i, 512 - i);
		i = (i + size) % 512;
	}
	if (size == 0) {
		free(ret);
		return (NULL);
	}
	ret[512] = 0;
	return (sock_io_split(ret));
}

int read_cmd(client_t *cli)
{
	char tmp;

	if (!cli->buf)
		cli->buf = malloc(sizeof(char) * (512 + 1));
	if (!cli->buf)
		return (0);
	if (read(cli->fd, &tmp, 1) == 0)
		return (0);
	cli->buf[cli->idx_buf] = tmp;
	cli->buf[cli->idx_buf + 1] = '\0';
	cli->buf[512] = '\0';
	cli->idx_buf += 1;
	if (cli->idx_buf >= 511)
		cli->idx_buf = 0;
	if (strstr(cli->buf, "\r\n")) {
		cli->buf[strlen(cli->buf) - 2] = '\0';
		cli->idx_buf = 0;
		return (2);
	}
	return (1);
}

int send_sock(client_t *cli, char *msg)
{
	ssize_t ret = write(cli->fd, msg, strlen(msg));

	if (ret == -1) {
		perror("write");
		return (0);
	}
	return (1);
}