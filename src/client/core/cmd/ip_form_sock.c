/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** ip.c
*/

#include <ifaddrs.h>
#include <zconf.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

static int get_ip_internal(struct ifaddrs *head, char **ret, struct
sockaddr_in *addr, struct ifaddrs *inter)
{
	struct sockaddr_in *iface;

	if (head->ifa_addr && head->ifa_addr->sa_family == AF_INET) {
		iface = (struct sockaddr_in *) head->ifa_addr;
		if (iface->sin_addr.s_addr == addr->sin_addr.s_addr) {
			*ret = inet_ntoa(iface->sin_addr);
			freeifaddrs(inter);
			return (1);
		}
	}
	return (0);
}

char *get_ip_from_sock(int sock)
{
	struct ifaddrs *inter;
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	char *ret;

	if (getifaddrs(&inter) == -1)
		return (NULL);
	if (getsockname(sock, (struct sockaddr *)&addr, &len) == -1)
		return (NULL);
	for (struct ifaddrs *head = inter; head; head = head->ifa_next) {
		if (get_ip_internal(head, &ret, &addr, inter))
			return (ret);
	}
	return (NULL);
}