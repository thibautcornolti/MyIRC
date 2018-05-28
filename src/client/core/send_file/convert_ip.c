/*
** EPITECH PROJECT, 2018
** Project
** File description:
** convert_ip.c
*/

#include <client.h>
#include "client.h"

ip_t convert_ip(int sock)
{
	ip_t ip = {0};
	char *ip_str = get_ip_from_sock(sock);
	char **ip_split;

	if (!ip_str)
		return (ip);
	dprintf(2, "IP : %s\n", ip_str);
	ip_split = split_str(ip_str, ".");
	if (!ip_split || len_array((void **) ip_split) != 4) {
		free(ip_str);
		free(ip_split);
		return (ip);
	}
	for (int i = 0; i < 4; i++)
		ip.digit[3 - i] = (unsigned char) atoi(ip_split[i]);
	return (ip);
}