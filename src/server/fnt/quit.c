/*
** EPITECH PROJECT, 2018
** Project
** File description:
** quit.c
*/

#include "server.h"

static void send_quit_msg(client_t *all_cli, client_t *cli, channel_t *chan,
cmd_t *cmd)
{
	while (all_cli) {
		if (all_cli != cli && channel_contain(all_cli->channel,
		chan->name))
			msg_sendf(&all_cli->to_send, ":%s!~%s@localhost QUIT "
			":\"%s\"\r\n", cli->nickname, cli->username,
			(cmd->ac >= 1) ? cmd->args[0] : "");
		all_cli = all_cli->next;
	}
}

void quit_cmd(server_t *server, client_t *cli, cmd_t *cmd)
{
	channel_t *chan = cli->channel;

	while (chan) {
		send_quit_msg(server->clients, cli, chan, cmd);
		chan = chan->next;
	}
	free_channel(cli->channel);
	cli->channel = NULL;
	close_empty_chan(server);
	if (cli->log_state == 0x11)
		msg_sendf(&cli->to_send, "ERROR :%s: %s[~%s@localhost] (\"%s\""
	")\r\n", "Closing Link", cli->nickname, cli->username, (cmd->ac >= 1) ?
	cmd->args[0] : "");
	else
		msg_sendf(&cli->to_send, "ERROR :%s: [%s@localhost] (\"%s\")\r"
	"\n", "Closing Link", "unknown", (cmd->ac >= 1) ? cmd->args[0] : "");
	cli->quit = 1;
}