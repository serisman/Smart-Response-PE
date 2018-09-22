// Name: display/display_set_cursor.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"

void display_set_cursor(uint8_t x, uint8_t y) {
	display_cursor_x = x;
	display_cursor_y = y;
}
