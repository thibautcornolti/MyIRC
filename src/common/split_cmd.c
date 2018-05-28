/*
** EPITECH PROJECT, 2018
** Project
** File description:
** split_str_colon.cpp
*/

#include <glob.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int is_delim(const char *str)
{
	return (str[0] == ' ');
}

static size_t nb_split(const char *str, const char *delim)
{
	size_t i = 0;
	size_t ret = 1;

	while (str[i] && is_delim(str + i))
		i += strlen(delim);
	while (str[i]) {
		if (is_delim(str + i)) {
			i += strlen(delim);
			while (str[i] && is_delim(str + i))
				i += strlen(delim);
			if (str[i])
				ret += 1;
		}
		if (str[i] == ':')
			return (ret);
		i += 1;
	}
	return (ret);
}

static size_t start_token(const char *str, size_t idx)
{
	size_t i = 0;
	size_t ret = 0;

	while (str[i] && is_delim(str + i))
		i += 1;
	while (str[i] && ret < idx) {
		if (is_delim(str + i)) {
			i += 1;
			while (str[i] && is_delim(str + i))
				i += 1;
			if (str[i])
				ret += 1;
		}
		if (str[i] == ':')
			return (i + 1);
		if (ret < idx)
			i += 1;
	}
	return (i);
}

static size_t len_token(const char *str, size_t idx)
{
	size_t i = start_token(str, idx);
	size_t start = i;

	if (i == 0 || (i > 0 && str[i - 1] != ':'))
		while (str[i] && strncmp(str + i, " ", 1) != 0)
			i += 1;
	else
		while (str[i])
			i += 1;
	return (i - start);
}

char **split_cmd(char *str)
{
	size_t size = nb_split(str, " ");
	char **ret = malloc(sizeof(char *) * (size + 1));
	size_t i = 0;

	if (!ret)
		return (NULL);
	memset(ret, 0, sizeof(char *) * (size + 1));
	while (i < size) {
		ret[i] = malloc(sizeof(char) * (len_token(str, i) + 1));
		if (!ret[i])
			return (NULL);
		memset(ret[i], 0, len_token(str, i) + 1);
		strncpy(ret[i], str + start_token(str, i), len_token(str, i));
		i += 1;
	}
	return (ret);
}