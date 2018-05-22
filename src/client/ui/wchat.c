/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static void show_buffer(win_t *this)
{
	char *buffer = safe_malloc(COLS);

	mvwprintw(this->ncurses_win, 2, 2, "> ", buffer);
	for (size_t i = 0; i < 2; ++i) {
		memcpy(buffer, this->ui->buffer + i * (COLS - 6), COLS - 6);
		mvwprintw(this->ncurses_win, 2 + i, 4, "%s", buffer);
	}
	if (this->ui->buffer_idx <= COLS - 7)
		mvwprintw(this->ncurses_win, 2, 4 + this->ui->buffer_idx, "|");
	else if (this->ui->buffer_idx < COLS * 2 - 12)
		mvwprintw(this->ncurses_win, 3,
			this->ui->buffer_idx % (COLS - 6) + 4, "|");
	free(buffer);
}

void update_w_chat(win_t *this)
{
	if (LINES < 6 || COLS < 6)
		return;
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
