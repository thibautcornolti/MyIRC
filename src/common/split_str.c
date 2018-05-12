/*
** EPITECH PROJECT, 2018
** Project
** File description:
** split_str.c
*/

#include <glob.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int is_delim(const char *str, const char *delim)
{
	if (strncmp(str, delim, strlen(delim)) == 0)
		return (1);
	return (0);
}

static size_t nb_split(const char *str, const char *delim)
{
	size_t i = 0;
	size_t ret = 1;

	while (str[i] && is_delim(str + i, delim))
		i += strlen(delim);
	while (str[i]) {
		if (is_delim(str + i, delim)) {
			i += strlen(delim);
			while (str[i] && is_delim(str + i, delim))
				i += strlen(delim);
			if (str[i])
				ret += 1;
		}
		i += 1;
	}
	return (ret);
}

static size_t start_token(const char *str, const char *delim, size_t idx)
{
	size_t i = 0;
	size_t ret = 0;

	while (str[i] && is_delim(str + i, delim))
		i += strlen(delim);
	while (str[i] && ret < idx) {
		if (is_delim(str + i, delim)) {
			i += strlen(delim);
			while (str[i] && is_delim(str + i, delim))
				i += strlen(delim);
			if (str[i])
				ret += 1;
		}
		if (ret < idx)
			i += 1;
	}
	return (i);
}

static size_t len_token(const char *str, const char *delim, size_t idx)
{
	size_t i = start_token(str, delim, idx);
	size_t start = i;

	while (str[i] && strncmp(str + i, delim, strlen(delim)) != 0)
		i += 1;
	return i - start;
}

char **split_str(char *str, char *delim)
{
	size_t size = nb_split(str, delim);
	char **ret = malloc(sizeof(char *) * (size + 1));

	if (!ret)
		return (NULL);
	memset(ret, 0, sizeof(char *) * (size + 1));
	size_t i = 0;
	while (i < size) {
		ret[i] = malloc(sizeof(char) * (len_token(str, delim, i) + 1));
		if (!ret[i])
			return (NULL);
		memset(ret[i], 0, len_token(str, delim, i) + 1);
		strncpy(ret[i], str + start_token(str, delim, i),
		len_token(str, delim, i));
		i += 1;
	}
	return (ret);
}