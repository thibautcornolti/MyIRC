/*
** EPITECH PROJECT, 2018
** Project
** File description:
** parse_cmd.c
*/

#include <server.h>
#include "server.h"

void free_cmd(cmd_t *cmd)
{
	free_array((void **) (cmd->args - 1));
	free(cmd);
}

cmd_t *parse_cmd(char *str)
{
	cmd_t *ret = malloc(sizeof(cmd_t));
	char **split = split_cmd(str);

	if (!ret || !split) {
		free(ret);
		free_array((void **) split);
		return (NULL);
	}
	str_toupper(split[0]);
	ret->cmd = split[0];
	ret->ac = len_array((void **) split) - 1;
	ret->args = split + 1;
	return (ret);
}