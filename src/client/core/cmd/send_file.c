/*
** EPITECH PROJECT, 2018
** Projectm
** File description:
** send_file.c
*/

#include "client.h"

static char *cmd_send_fname(char *or)
{
	int i = -1;
	int s = -1;

	while (or[++i]) {
		if (or[i] == '/' && or[i + 1])
			s = i;
	}
	return (or + s + 1);
}

bool cmd_send_file(sess_t *sess, char *line)
{
	int fd;
	char **cmd = split_cmd(line);
	bool ret = false;

	if (!cmd)
		return (false);
	if (len_array((void **)cmd) >= 2) {
		fd = open(cmd[1], O_RDONLY);
		if (fd == -1 ||
			!send_file(sess, fd, cmd[0], cmd_send_fname(cmd[1])))
			sess->printfChan(sess, "master",
				"Cannot send file \"%s\"", cmd[1]);
		else
			ret = true;
	}
	free_array((void **)cmd);
	return (ret);
}