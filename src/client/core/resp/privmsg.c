/*
** EPITECH PROJECT, 2018
** Project
** File description:
** privmsg.c
*/

#include "client.h"

static void recv_file(ui_t *this, char *msg, char *nick)
{
	char **msg_split = split_cmd(msg);
	char *size;

	if (!msg_split)
		return;
	if (len_array((void **)msg_split) != 6) {
		free_array((void **)msg_split);
		return;
	}
	size = pretty_size(msg_split[5]);
	if (size)
		this->session->printfChan(this->session, nick,
		"%s: Send a file \"%s\" "
		"(size: ~%s)",
		nick, msg_split[2], size);
	init_get_file(this, msg_split, nick);
	free(size);
	free_array((void **)msg_split);
}

static void treat_msg_channel(ui_t *this, char **resp, char *nick)
{
	char *tmp;

	int i = 0;
	dprintf(2, "MSG INCOMMING\n"); // TODO rm debug
	while (resp[3][i]) {
		dprintf(2, "CHAR %c %d\n", resp[3][i], resp[3][i]);
		i++;
	}
	if (resp[3][0] == 1 && resp[2][0] != '#') {
		recv_file(this, resp[3], nick);
		return;
	}
	tmp = safe_malloc(sizeof(char) * (strlen(nick) + strlen(resp[3]) + 3));
	memcpy(tmp, nick, strlen(nick));
	memcpy(tmp + strlen(nick), ": ", 2);
	memcpy(tmp + strlen(nick) + 2, resp[3], strlen(resp[3]));
	tmp[strlen(nick) + 2 + strlen(resp[3])] = '\0';
	this->session->printChan(
		this->session, (resp[2][0] == '#') ? resp[2] : nick, tmp);
	free(tmp);
}

void resp_privmsg(ui_t *this, char **resp)
{
	char *nick;

	if (len_array((void **)resp) < 4)
		return;
	nick = get_nickname(resp[0]);
	if (nick)
		treat_msg_channel(this, resp, nick);
	free(nick);
}