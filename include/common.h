/*
** EPITECH PROJECT, 2018
** Project
** File description:
** common.h
*/

#ifndef PROJECT_COMMON_H
	#define PROJECT_COMMON_H

typedef struct poll_s
{
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

#endif /* !PROJECT_COMMON_H */
