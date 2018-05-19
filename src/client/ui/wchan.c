/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

static void set_spec(win_t *this, chan_t *chan)
{
	if (this->ui->session->cur_chan == chan) {
		wattron(this->ncurses_win, A_BOLD | A_UNDERLINE);
		chan->update = false;
	}
	if (chan->update)
		wattron(this->ncurses_win, COLOR_PAIR(1));
}

static void unset_spec(win_t *this, chan_t *chan)
{
	if (this->ui->session->cur_chan == chan)
		wattroff(this->ncurses_win, A_BOLD | A_UNDERLINE);
	if (chan->update)
		wattroff(this->ncurses_win, COLOR_PAIR(1));
}

static void display_chan(win_t *this)
{
	int i = 0;
	chan_t *chan = this->ui->session->chan;

	while (chan) {
		set_spec(this, chan);
		mvwprintw(this->ncurses_win, 1 + i, (!strcmp(chan->name,
		"master")) ? 3 : 5, chan->name);
		unset_spec(this, chan);
		chan = chan->next;
		i += 1;
	}
}

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
	display_chan(this);
	wrefresh(this->ncurses_win);
}
