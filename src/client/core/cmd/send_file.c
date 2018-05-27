/*
** EPITECH PROJECT, 2018
** Projectm
** File description:
** send_file.c
*/

#include "client.h"

bool cmd_send_file(sess_t *sess, char *line)
{
	int fd;
	char **cmd = split_cmd(line);
	bool ret = false;

	if (!cmd)
		return (false);
	if (len_array((void **) cmd) >= 2) {
		fd = open(cmd[1], O_RDONLY);
		if (fd == -1 || !send_file(sess, fd, cmd[0], cmd[1]))
			sess->printfChan(sess, "master", "Cannot send file "
			"\"%s\"", cmd[1]);
		else
			ret = true;
	}
	free_array((void **) cmd);
	return (ret);
}