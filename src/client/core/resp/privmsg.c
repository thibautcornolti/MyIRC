/*
** EPITECH PROJECT, 2018
** Project
** File description:
** privmsg.c
*/

#include "client.h"

static void treat_msg_channel(ui_t *this, char **resp, char *nick)
{
	char *tmp;

	tmp = safe_malloc(sizeof(char) * (strlen(nick) + strlen
	(resp[3]) + 3));
	memcpy(tmp, nick, strlen(nick));
	memcpy(tmp + strlen(nick), ": ", 2);
	memcpy(tmp + strlen(nick) + 2, resp[3], strlen(resp[3]));
	tmp[strlen(nick) + 2 + strlen(resp[3])] = '\0';
	push_log_in_chan(this, (resp[2][0] == '#') ? resp[2] : nick, tmp);
	free(tmp);
}

void resp_privmsg(ui_t *this, char **resp)
{
	char *nick;

	if (len_array((void **) resp) < 4)
		return;
	nick = get_nickname(resp[0]);
	if (nick)
		treat_msg_channel(this, resp, nick);
	free(nick);
}