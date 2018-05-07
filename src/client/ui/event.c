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

	while (read(0, &c, 1) > 0) {
		if (c >= 32 && c <= 126) {
			this->buffer[this->buffer_idx++ % this->buffer_size] =
				c;
		}
		else if (c == 127) {
			if (this->buffer_idx > 0)
				this->buffer_idx--;
			this->buffer[this->buffer_idx % this->buffer_size] = 0;
		}
		c = 0;
	}
	return (errno == EAGAIN);
}