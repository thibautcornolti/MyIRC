/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static void update_w_logs_show(win_t *this)
{
	struct tm *tm;
	int start;

	start = ((int)this->ui->session->logger->size > LINES - 9) ?
		this->ui->session->logger->size - (LINES - 8) :
		0;
	for (size_t i = start; i < this->ui->session->logger->size; ++i) {
		if (!(tm = localtime(
			      &this->ui->session->logger->logs[i].timestamp)))
			continue;
		wattron(this->ncurses_win, A_ITALIC);
		mvwprintw(this->ncurses_win, i + 2 - start, 2,
			"%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
		wattroff(this->ncurses_win, A_ITALIC);
		wattron(this->ncurses_win, A_BOLD);
		mvwprintw(this->ncurses_win, i + 2 - start, 11, "|");
		wattroff(this->ncurses_win, A_BOLD);
		mvwprintw(this->ncurses_win, i + 2 - start, 14, "%s",
			this->ui->session->logger->logs[i].msg);
	}
}

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
	update_w_logs_show(this);
	wrefresh(this->ncurses_win);
}
