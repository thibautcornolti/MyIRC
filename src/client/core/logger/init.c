/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"

logger_t *create_logger(void)
{
	logger_t *logger;

	logger = safe_malloc(sizeof(logger_t));
	logger->add = &add_logger;
	logger->log = &log_logger;
	logger->free = &free_logger;
	return (logger);
}

log_t *create_log(void)
{
	log_t *log;

	log = safe_malloc(sizeof(log_t));
	return (log);
}

void free_logger(logger_t *this)
{
	free(this);
}
