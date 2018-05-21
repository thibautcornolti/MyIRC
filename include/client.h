/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#pragma once

#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <ncurses.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "common.h"

struct ui_s;

/*
** Utils
*/

typedef struct {
	size_t x;
	size_t y;
} pos_t;

/*
** Core
*/

typedef struct commander_s {
	size_t (*size)(struct commander_s *);
	bool (*push)(struct commander_s *, char *, ...);
	char *(*pop)(struct commander_s *);
	void (*free)(struct commander_s *);

	char *cmds[513];
} commander_t;

commander_t *create_commander();
size_t size_commander(commander_t *);
bool push_commander(commander_t *, char *, ...);
char *pop_commander(commander_t *);
void free_commander(commander_t *);

typedef struct log_s {
	char *msg;
	time_t timestamp;
} log_t;

typedef struct logger_s {
	void (*add)(struct logger_s *, log_t);
	void (*log)(struct logger_s *, char *);
	void (*free)(struct logger_s *);

	log_t *logs;
	size_t size;
} logger_t;

logger_t *create_logger();
void add_logger(logger_t *, log_t);
void log_logger(logger_t *, char *);
void free_logger(logger_t *);

typedef struct serv_s {
	void (*free)(struct serv_s *);

	char *host;
	int port;
	int fd;
	bool connected;
	struct sockaddr_in s_in;

	commander_t *commander;

	char *buffer;
	char buffer_last;
	int buffer_last_nb;
	size_t buffer_idx;
	size_t buffer_size;
} serv_t;

serv_t *create_serv();
void free_serv(serv_t *);

bool do_srv(struct ui_s *);

typedef struct chan_s {
	logger_t *logger;
	char *name;
	bool update;
	struct chan_s *next;
} chan_t;

typedef struct sess_s {
	int (*addChan)(struct sess_s *, char *);
	int (*rmChan)(struct sess_s *, char *);
	void (*printChan)(struct sess_s *, char *, char *);
	void (*printfChan)(struct sess_s *, char *, char *, ...);
	void (*free)(struct sess_s *);
	void (*_freeChan)(struct sess_s *);

	serv_t *serv;
	chan_t *chan;
	chan_t *cur_chan;
	poll_t *pl;
	char *nickname;
} sess_t;

sess_t *create_sess();
int add_chan(sess_t *, char *);
int rm_chan(sess_t *, char *);
void printf_chan(struct sess_s *this, char *name, char *model, ...);
void print_chan(struct sess_s *this, char *name, char *log);
void free_chan(struct sess_s *this);
void free_sess(sess_t *);

bool do_cmd(struct ui_s *);

bool cmd_server(struct sess_s *, char *);
bool cmd_nick(struct sess_s *, char *);
bool cmd_list(struct sess_s *, char *);
bool cmd_join(struct sess_s *, char *);
bool cmd_part(struct sess_s *, char *);
bool cmd_users(struct sess_s *, char *);
bool cmd_names(struct sess_s *, char *);
bool cmd_msg(struct sess_s *, char *);
bool cmd_accept_file(struct sess_s *, char *);
bool cmd_broadcast(struct ui_s *, char *);

/*
** User Interface
*/

#define get_master_ui() set_master_ui(NULL)

typedef struct win_s {
	void (*init)(struct win_s *);
	void (*free)(struct win_s *);
	void (*update)(struct win_s *);

	WINDOW *ncurses_win;

	struct ui_s *ui;
} win_t;

typedef struct ui_s {
	void (*init)(struct ui_s *);
	void (*free)(struct ui_s *);
	void (*update)(struct ui_s *);
	bool (*getEvent)(struct ui_s *);
	void (*processEvent)(struct ui_s *);
	void (*initWindows)(struct ui_s *);
	void (*freeWindows)(struct ui_s *);
	bool (*getServerEvent)(struct ui_s *);
	void (*processServerEvent)(struct ui_s *);
	void (*sendServerEvent)(struct ui_s *);

	win_t *w_chat;
	win_t *w_chan;
	win_t *w_info;
	win_t *w_logs;

	size_t framecap;
	bool hasToQuit;
	sess_t *session;

	char *buffer;
	char buffer_last;
	size_t buffer_idx;
	size_t buffer_size;
} ui_t;

ui_t *create_ui();
void init_ui(ui_t *);
void free_ui(ui_t *);
void update_ui(ui_t *);
bool get_event_ui(ui_t *);
void process_event_ui(ui_t *);
void init_windows(ui_t *);
void free_windows(ui_t *);
bool get_event_serv(ui_t *);
void process_event_serv(ui_t *);
void send_event_serv(ui_t *);

win_t *create_window(ui_t *, void (*)(win_t *));
void init_window(win_t *);
void free_window(win_t *);

void update_w_chat(win_t *);
void update_w_chan(win_t *);
void update_w_info(win_t *);
void update_w_logs(win_t *);

ui_t *set_master_ui(ui_t *);

typedef struct {
	char *name;
	void (*fnt)(ui_t *, char **);
} list_cmd_action_t;

typedef union {
	uint32_t val;
	char digit[4];
} ip_t;

char *get_nickname(char *domaine);
void resp_no_action(ui_t *ui, char **resp);
void resp_privmsg(ui_t *this, char **resp);
void resp_join(ui_t *ui, char **resp);
void resp_names(ui_t *ui, char **resp);
void resp_part(ui_t *this, char **resp);
void resp_list(ui_t *this, char **list);
void resp_end_list(ui_t *this, char **list);

char *pretty_size(char *size_c);
