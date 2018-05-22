/*
** EPITECH PROJECT, 2018
** Project
** File description:
** convert_ip.c
*/

#include <client.h>
#include "client.h"

ip_t convert_ip(int sock) //TODO Get ip
{
	ip_t ip = {0};
//	char *ip_str = get_ip_from_sock(serv);
//	char **ip_split;
//
//	if (!ip_str)
//		return (ip);
//	dprintf(2, "IP : %s\n", ip_str);
//	ip_split = split_str(ip_str, ".");
//	if (!ip_split || len_array((void **) ip_split) != 4) {
//		free(ip_str);
//		free(ip_split);
//		return (ip);
//	}
//	for (int i = 0; i < 4; i++)
//		ip.digit[3 - i] = (char) atoi(ip_split[i]);
	(void) sock;
	ip.digit[3] = 127;
	ip.digit[2] = 0;
	ip.digit[1] = 0;
	ip.digit[0] = 1;
	return (ip);
}