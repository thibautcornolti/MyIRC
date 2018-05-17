/*
** EPITECH PROJECT, 2018
** Project
** File description:
** get_user_by_chan.c
*/

#include "server.h"

static int get_internal(client_t *all_cli, char **ret, client_t *client, char
*chan_name)
{
	size_t len;

	while (all_cli) {
		if (all_cli->log_state == 0x11 && all_cli != client &&
		channel_contain(all_cli->channel, chan_name)) {
			len = strlen(*ret);
			*ret = realloc(*ret, sizeof(char) * (len +
			strlen(all_cli->nickname) + 2));
			if (!(*ret))
				return (1);
			(*ret)[len] = ' ';
			memcpy(*ret + len + 1, all_cli->nickname,
			       strlen(all_cli->nickname));
			(*ret)[len + strlen(all_cli->nickname) + 1] = '\0';
		}
		all_cli = all_cli->next;
	}
	return (0);
}

char *get_user_by_chan(client_t *all_cli, client_t *client, char *chan_name)
{
	char *ret = malloc(sizeof(char) * (strlen(client->nickname) + 2));

	if (!ret)
		return (NULL);
	ret[0] = '@';
	memcpy(ret + 1, client->nickname, strlen(client->nickname));
	ret[strlen(client->nickname) + 1] = '\0';
	if (get_internal(all_cli, &ret, client, chan_name))
		return (NULL);
	return (ret);
}