/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** myirc
*/

#include "client.h"
#include "common.h"

bool get_event_ui(ui_t *this)
{
	char c = 0;

	if (read(0, &c, 1) > 0) {
		if (c >= 32 && c <= 126) {
			this->buffer[this->buffer_idx % this->buffer_size] = c;
			this->buffer_idx++;
		}
	}
	this->buffer_last = c;
	return (errno == EAGAIN);
}

void process_event_ui(ui_t *this)
{
	char c = this->buffer_last;

	printf("%d\n", c);
	if (c == 127) {
		if (this->buffer_idx > 0)
			this->buffer_idx--;
		this->buffer[this->buffer_idx % this->buffer_size] = 0;
	} else if (c == 13 || c == 10) {
		this->buffer_idx = 0;
		memset(this->buffer, 0, this->buffer_size);
	}
}
