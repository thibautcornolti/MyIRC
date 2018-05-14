/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"
#include "common.h"

void update_w_chan(win_t *this)
{
	mvwin(this->ncurses_win, 0, 2 * COLS / 3);
	wresize(this->ncurses_win, 2 * LINES / 3, COLS / 3);
	wclear(this->ncurses_win);
	box(this->ncurses_win, ACS_VLINE, ACS_HLINE);
	mvwprintw(this->ncurses_win, 0, 3, "          ");
	wattron(this->ncurses_win, A_BOLD | A_ITALIC | A_UNDERLINE);
	mvwprintw(this->ncurses_win, 0, 4, "Channels");
	wattroff(this->ncurses_win, A_BOLD | A_ITALIC | A_UNDERLINE);
	mvwprintw(this->ncurses_win, 3, 5, "#lesgomuscu");
	mvwprintw(this->ncurses_win, 5, 5, "#epirando");
	wrefresh(this->ncurses_win);
}
