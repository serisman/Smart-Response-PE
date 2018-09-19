// Name: display.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-18
// License: MIT

#include "../hardware.h"
#include "uc1701.h"
#include "display.h"
#include "font_5x7.h"

uint8_t _cursor_row = 1;
uint8_t _cursor_col = 1;

void display_set_cursor(uint8_t row, uint8_t col) {
	if (row >= 1 && row <= NUM_ROWS)
		_cursor_row = row;
	if (col >= 1 && col <= NUM_ROWS)
		_cursor_col = col;
}

void display_draw_char(char chr) {
	if (chr == '\r') {
		_cursor_col = 1;
	} else if (chr == '\t') {
		//if (_cursor_col < NUM_COLS-1)
			_cursor_col += 2;
	} else if (chr == '\n') {
		//if (_cursor_row < NUM_ROWS)
			_cursor_row++;
	} else if (chr >= ' ' && chr <= '~') { // ASCII printable only
		uc1701_draw_bitmap((_cursor_col-1) * CHAR_WIDTH + 1, _cursor_row-1, &font_5x7[(chr-' ')*5], 5, 1);
		//_uc1701_transfer(0x00);
		_cursor_col++;
//		if (_cursor_col >= NUM_COLS && _cursor_row < NUM_ROWS) {
//			_cursor_row++;
//			_cursor_col = 1;
//		}
	}
}

void display_printf(char * str) {
	while (*str != 0) {
		display_draw_char(*str);
		str++;
	}
}
