/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static void update_w_info_server(win_t *this)
{
	if (this->ui->session->serv->connected) {
		wattron(this->ncurses_win, A_BOLD);
		mvwprintw(this->ncurses_win, 5, 2, "Server");
		wattroff(this->ncurses_win, A_BOLD);
		wattron(this->ncurses_win, A_ITALIC);		
		mvwprintw(this->ncurses_win, 5, 15, "%s:%d",
			this->ui->session->serv->host,
			this->ui->session->serv->port);
		wattroff(this->ncurses_win, A_ITALIC);			
	}
}

static void update_w_info_nick(win_t *this)
{
	if (this->ui->session->nickname) {
		wattron(this->ncurses_win, A_BOLD);
		mvwprintw(this->ncurses_win, 3, 2, "Nickname");
		wattroff(this->ncurses_win, A_BOLD);
		wattron(this->ncurses_win, A_ITALIC);
		mvwprintw(this->ncurses_win, 3, 15, "|%s|",
			this->ui->session->nickname);
		wattroff(this->ncurses_win, A_ITALIC);
	}
}

void update_w_info(win_t *this)
{
	mvwin(this->ncurses_win, 2 * LINES / 3, 2 * COLS / 3);
	wresize(this->ncurses_win,
		LINES / 3 - (LINES / 3 * 3 == LINES ? 5 : 4), COLS / 3);
	wclear(this->ncurses_win);
	box(this->ncurses_win, ACS_VLINE, ACS_HLINE);
	mvwprintw(this->ncurses_win, 0, 3, "       ");
	wattron(this->ncurses_win, A_BOLD | A_ITALIC | A_UNDERLINE);
	mvwprintw(this->ncurses_win, 0, 4, "Infos");
	wattroff(this->ncurses_win, A_BOLD | A_ITALIC | A_UNDERLINE);
	update_w_info_server(this);
	update_w_info_nick(this);
	wrefresh(this->ncurses_win);
}
