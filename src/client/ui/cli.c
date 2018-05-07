/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"
#include "common.h"

static void show_buffer(win_t *this)
{
	char *buffer = safe_malloc(COLS);

	for (size_t i = 0; i < 2; ++i) {
		memcpy(buffer, this->ui->buffer + i * (COLS - 4), COLS - 4);
		mvwprintw(this->ncurses_win, 2 + i, 2, "%s", buffer);
	}
	free(buffer);
}

void update_w_cli(win_t *this)
{
	mvwin(this->ncurses_win, LINES - 5, 0);
	wresize(this->ncurses_win, 5, COLS);
	wclear(this->ncurses_win);
	box(this->ncurses_win, ACS_VLINE, ACS_HLINE);
	mvwprintw(this->ncurses_win, 0, 3, " Command line ");
	show_buffer(this);
	wrefresh(this->ncurses_win);
}
