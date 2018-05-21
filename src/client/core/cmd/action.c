/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static const char *refs[] = {
	"SERVER", "NICK", "LIST", "JOIN",
	"PART", "USERS", "NAMES", "MSG",
	"ACCEPT_FILE", NULL,
};

static bool (*fcts[])(sess_t *, char *) = {
	&cmd_server, &cmd_nick, &cmd_list,
	&cmd_join, &cmd_part, &cmd_users,
	&cmd_names, &cmd_msg, &cmd_accept_file,
};

static int cmd_to_fctn(char *line)
{
	char *cmd;
	size_t endcmd = 0;
	int res = -1;

	for (; line[endcmd] && line[endcmd] != ' '; ++endcmd);
	cmd = strndup(line, endcmd);
	for (size_t i = 0 ; cmd[i] ; ++i)
		cmd[i] = (char) toupper(cmd[i]);
	for (int i = 0 ; refs[i] ; ++i)
		if (strcmp(refs[i], cmd) == 0)
			res = i;
	return (res);
}

bool do_cmd(ui_t *ui)
{
	bool res = false;
	int fctn = 0;

	if (ui->buffer[0] != '/')
		res = cmd_broadcast(ui, ui->buffer);
	else if ((fctn = cmd_to_fctn(ui->buffer + 1)) >= 0)
		res = fcts[fctn](
			ui->session, ui->buffer + strlen(refs[fctn]) + 2);
	ui->w_info->update(ui->w_info);
	ui->w_logs->update(ui->w_logs);
	return (res);
}
