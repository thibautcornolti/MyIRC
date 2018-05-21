/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"
#include <client.h>

list_cmd_action_t cmd[] = {{"PRIVMSG", &resp_privmsg}, {"JOIN", &resp_join},
	{"PART", &resp_part}, {"353", &resp_names}, {"366", &resp_no_action},
	{"322", &resp_list}, {"323", &resp_end_list}, {NULL, NULL}};

bool do_srv(ui_t *ui)
{
	char *msg = ui->session->serv->buffer;
	char **resp = split_cmd(msg + (msg[0] == ':'));
	size_t i = 0;

	if (!resp)
		return (false);
	dprintf(2, "DO_SRV: %s\n", msg); // TODO rm debug
	while (resp[i]) {
		dprintf(2, "[%lu] = %s\n", i, resp[i]);
		i += 1;
	}
	if (len_array((void **)resp) < 3)
		return (false);
	str_toupper(resp[1]);
	i = 0;
	while (cmd[i].name) {
		if (!strcmp(cmd[i].name, resp[1])) {
			cmd[i].fnt(ui, resp);
			return (true);
		}
		i += 1;
	}
	ui->session->printChan(
		ui->session, "master", resp[len_array((void **)resp) - 1]);
	return (true);
}
