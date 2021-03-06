/*
** EPITECH PROJECT, 2018
** Project
** File description:
** common.h
*/

#pragma once

#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct poll_s {
	int fd;
	short evt;
	short revt;
	struct poll_s *next;
} poll_t;

int is_positive_integer(const char *str, int max);

int poll_add(poll_t **p, int fd, short evt);
int poll_rm(poll_t **p, int fd);
int poll_update(poll_t *p, int fd, short evt);

int poll_wait(poll_t *p, int timeout);

int poll_canread(poll_t *p, int fd);
int poll_canwrite(poll_t *p, int fd);
int poll_isclose(poll_t *p, int fd);

void *safe_malloc(size_t);
void *safe_realloc(void *, size_t, size_t);

char **split_str(char *str, char *delim);

char **split_cmd(char *str);

void free_array(void **arr);

size_t len_array(void **arr);

void str_toupper(char *str);

char *sendf(const char *model, va_list list);

char *asendf(char *model, ...);