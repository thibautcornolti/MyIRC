/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include <client.h>
#include "client.h"

list_cmd_action_t cmd[] = {
	{"PRIVMSG", &resp_privmsg},
	{"JOIN", &resp_join},
	{"353", &resp_list},
	{"366", &resp_no_action},
	{NULL, NULL}
};

bool do_srv(ui_t *ui)
{
	char *msg = ui->session->serv->buffer;
	char **resp = split_cmd(msg + (msg[0] == ':'));
	size_t i = 0;

	if (!resp)
		return (false); //TODO Ask tibo about the return false consequence
	if (len_array((void **) resp) < 3)
		return (false);
	str_toupper(resp[1]);
	while (cmd[i].name) {
		if (!strcmp(cmd[i].name, resp[1])) {
			cmd[i].fnt(ui, resp);
			return (true);
		}
		i += 1;
	}
	dprintf(2, "DO_SRV: %s\n", msg);
	i = 0;
	while (resp[i]) {
		dprintf(2, "[%lu] = %s\n", i, resp[i]);
		i += 1;
	}
	push_log_in_chan(ui, "master", resp[len_array((void **) resp) - 1]);
	return (true);
}
