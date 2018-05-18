/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

win_t *create_window(ui_t *ui, void (*update_w_fct)(win_t *))
{
	win_t *win;

	win = safe_malloc(sizeof(win_t));
	win->init = &init_window;
	win->free = &free_window;
	win->update = update_w_fct;
	win->ui = ui;
	return (win);
}

void init_window(win_t *this)
{
	this->ncurses_win = newwin(1, 1, 0, 0);
}

void free_window(win_t *this)
{
	delwin(this->ncurses_win);
	free(this);
}
