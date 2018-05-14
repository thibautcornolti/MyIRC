/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"
#include "common.h"

void update_w_logs(win_t *this)
{
	mvwin(this->ncurses_win, 0, 0);
	wresize(this->ncurses_win, LINES - 5, 2 * COLS / 3);
	wclear(this->ncurses_win);
	box(this->ncurses_win, ACS_VLINE, ACS_HLINE);
	mvwprintw(this->ncurses_win, 0, 3, "      ");
	wattron(this->ncurses_win, A_BOLD | A_ITALIC | A_UNDERLINE);
	mvwprintw(this->ncurses_win, 0, 4, "Logs");
	wattroff(this->ncurses_win, A_BOLD | A_ITALIC | A_UNDERLINE);
	wrefresh(this->ncurses_win);
}
