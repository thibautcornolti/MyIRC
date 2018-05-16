/*
** EPITECH PROJECT, 2018
** Project
** File description:
** part.c
*/

#include <server.h>
#include "server.h"

void part_cmd(server_t *server, client_t *cli, cmd_t *cmd)
{
	(void) server;
	if (cmd->ac == 0) {
		msg_sendf(&cli->to_send, ":%s 461 %s PART :%s\r\n",
		"localhost", cli->nickname, "Not enough parameters");
		return;
	}
	if (!channel_contain(cli->channel, cmd->args[0])) {
		msg_sendf(&cli->to_send, ":%s 403 %s %s :%s\r\n", "localhost",
		cli->nickname, cmd->args[0], "You're not on that channel");
		return;
	}
	broadcast_channel(server->clients, cmd->args[0],
	":%s!~%s@localhost PART %s :%s\r\n", cli->nickname, cli->nickname,
	cmd->args[0], (cmd->ac >= 2) ? cmd->args[1] : "");
	channel_rm(&cli->channel, cmd->args[0]);
//	:irc.knoepflin.tk 403 test #lol :No such channel
//	:irc.knoepflin.tk 442 test #lol :You're not on that channel
//	:<nickname>!~<>username@localhost PART #<av[0]> :<av[1]>
}
//BROADCAST    :test2!~d@163.5.141.157 PART #lol :<msg>
//BROADCASR    :Arthur!~arthur@163.5.141.157 PART #lol :salut