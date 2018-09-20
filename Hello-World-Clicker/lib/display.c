// Name: display.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-18
// License: MIT

#include "../hardware.h"
#include "util.h"
#include "uc1701.h"
#include "display.h"
#include "font_5x7.h"

uint8_t __xdata _screen[NUM_SCREEN_ROWS * SCREEN_WIDTH];

uint8_t __xdata *_get_screen_ptr(uint8_t x, uint8_t y) { return &_screen[(y/8*SCREEN_WIDTH) + x]; }

// It is faster and produces less code to look this up rather than calculate it in runtime!
uint8_t __code _bitmasks[] = { _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7) };

uint8_t _each_frame_millis = 1000 / 30;
uint32_t _prev_frame_ms = 0;

uint8_t _cursor_x = 0;
uint8_t _cursor_y = 0;

void display_paint() {
	uc1701_paint(_screen);
}

void display_draw_pixel(uint8_t x, uint8_t y, uint8_t color) {
	uint8_t __xdata *screen_ptr = _get_screen_ptr(x,y);
	uint8_t pixel = *screen_ptr;
	uint8_t bitMask = _bitmasks[y % 8];
	if (color)
		pixel &= ~bitMask;
	else
		pixel |= bitMask;
	*screen_ptr = pixel;
}

void display_draw_bitmap(int8_t x, int8_t y, uint8_t *bitmap, uint8_t width, uint8_t height, uint8_t color) {
  int8_t yOffset, row, end_row;
  uint8_t bitmap_pixel, pixel_mask, screen_pixel;
  uint8_t __xdata *screen_ptr;
  uint8_t __xdata *screen_ptr2 = _screen;

  // no need to draw at all if we're offscreen
  if (x+width < 0 /*|| x > SCREEN_WIDTH-1*/ || y+height < 0 || y > SCREEN_HEIGHT-1)
    return;

 	row = y / 8;
  if (y < 0) {
  	yOffset = 8 - ((0-y) % 8);
    row--;
  } else {
  	yOffset = y % 8;
  }
  end_row = row + (height/8);
  if (height % 8 != 0) end_row++;
  if (end_row > NUM_SCREEN_ROWS)
  	end_row = NUM_SCREEN_ROWS;
  for (; row < end_row; row++) {
    screen_ptr = _get_screen_ptr(x>=0 ? x : 0, row*8);
		if (yOffset && row<NUM_SCREEN_ROWS-1 && row >= -1) {
			screen_ptr2 = _get_screen_ptr(x>=0 ? x : 0, (row+1)*8);
    }
		for (uint8_t iCol = 0; iCol<width; iCol++) {
			bitmap_pixel = *bitmap;
			bitmap++;
			if (iCol + x > (SCREEN_WIDTH-1)) continue;
			if (iCol + x >= 0) {
				if (row >= 0) {
					pixel_mask = bitmap_pixel << yOffset;
					screen_pixel = *screen_ptr;
					if (color == COLOR_BLACK)				screen_pixel |= pixel_mask;
					else if (color == COLOR_WHITE)	screen_pixel &= ~pixel_mask;
					else														screen_pixel ^= pixel_mask;
					*screen_ptr = screen_pixel;
					screen_ptr++;
				}
				if (yOffset && row<NUM_SCREEN_ROWS-1 && row >= -1) {
					pixel_mask = bitmap_pixel >> (8-yOffset);
					screen_pixel = *screen_ptr2;
					if (color == COLOR_BLACK)				screen_pixel |= pixel_mask;
					else if (color == COLOR_WHITE)	screen_pixel &= ~pixel_mask;
					else														screen_pixel ^= pixel_mask;
					*screen_ptr2 = screen_pixel;
					screen_ptr2++;
				}
			}
		}
	}
}

void display_set_frame_rate(uint8_t rate) {
  _each_frame_millis = 1000 / rate;
}

uint8_t display_next_frame() {
	uint32_t millis = clock_millis();
	uint8_t elapsed_ms = millis - _prev_frame_ms;

	if (elapsed_ms >= _each_frame_millis) {
		_prev_frame_ms = millis;
		return 1;
	}

	clock_delay_ms(1);
	return 0;
}

void display_set_cursor(uint8_t x, uint8_t y) {
	_cursor_x = x;
	_cursor_y = y;
}

void display_draw_char(char chr) {
	if (chr == '\r') {
		_cursor_x = 0;
	} else if (chr == '\t') {
		_cursor_x += CHAR_WIDTH*2;
	} else if (chr == '\n') {
		_cursor_y += CHAR_HEIGHT;
	} else if (chr >= ' ' && chr <= '~') { // ASCII printable only
		display_draw_bitmap(_cursor_x, _cursor_y, &font_5x7[(chr-' ')*5], CHAR_WIDTH-1, CHAR_HEIGHT, COLOR_BLACK);
		_cursor_x += CHAR_WIDTH;
	}
}

void display_printf(char *str) {
	while (*str != 0) {
		display_draw_char(*str);
		str++;
	}
}
