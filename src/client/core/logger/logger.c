/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

void add_logger(logger_t *this, log_t log)
{
	this->logs = safe_realloc(this->logs, (this->size) * sizeof(log_t),
		(this->size + 1) * sizeof(log_t));
	this->logs[this->size] = log;
	this->size++;
}

void log_logger(logger_t *this, char *msg)
{
	log_t log = {0};

	log.msg = strdup(msg);
	log.timestamp = time(NULL);
	this->add(this, log);
}
