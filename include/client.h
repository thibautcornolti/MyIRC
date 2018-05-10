/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#pragma once

#include <errno.h>
#include <fcntl.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define get_master_ui() set_master_ui(NULL)

typedef struct {
	size_t x;
	size_t y;
} pos_t;

struct ui_s;

typedef struct win_s {
	void (*init)(struct win_s *);
	void (*stop)(struct win_s *);
	void (*update)(struct win_s *);

	WINDOW *ncurses_win;

	struct ui_s *ui;
} win_t;

typedef struct ui_s {
	void (*init)(struct ui_s *);
	void (*stop)(struct ui_s *);
	void (*update)(struct ui_s *);
	bool (*getEvent)(struct ui_s *);
	void (*processEvent)(struct ui_s *);
	void (*initWindows)(struct ui_s *);
	void (*stopWindows)(struct ui_s *);

	win_t *w_chat;

	size_t framecap;

	char *buffer;
	char buffer_last;
	size_t buffer_idx;
	size_t buffer_size;
} ui_t;

ui_t *create_ui();
void init_ui(ui_t *);
void stop_ui(ui_t *);
void update_ui(ui_t *);
bool get_event_ui(ui_t *);
void process_event_ui(ui_t *);
void init_windows(ui_t *);
void stop_windows(ui_t *);

win_t *create_window(ui_t *, void (*)(win_t *));
void init_window(win_t *);
void stop_window(win_t *);

void update_w_cli(win_t *);

ui_t *set_master_ui(ui_t *);
