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

	mvwprintw(this->ncurses_win, 2, 2, "> ", buffer);
	for (size_t i = 0; i < 2; ++i) {
		memcpy(buffer, this->ui->buffer + i * (COLS - 6), COLS - 6);
		mvwprintw(this->ncurses_win, 2 + i, 4, "%s", buffer);
	}
	free(buffer);
}

void update_w_chat(win_t *this)
{
	mvwin(this->ncurses_win, LINES - 5, 0);
	wresize(this->ncurses_win, 5, COLS);
	wclear(this->ncurses_win);
	box(this->ncurses_win, ACS_VLINE, ACS_HLINE);
	mvwprintw(this->ncurses_win, 0, 3, "              ");
	wattron(this->ncurses_win, A_BOLD | A_ITALIC | A_UNDERLINE);
	mvwprintw(this->ncurses_win, 0, 4, "Command line");
	wattroff(this->ncurses_win, A_BOLD | A_ITALIC | A_UNDERLINE);
	show_buffer(this);
	wrefresh(this->ncurses_win);
}
