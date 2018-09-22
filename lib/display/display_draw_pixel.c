// Name: display/display_draw_pixel.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "util.h"
#include "display.h"

// It is faster and produces less code to look this up rather than calculate it in runtime!
uint8_t __code _bitmasks[] = { BV(0), BV(1), BV(2), BV(3), BV(4), BV(5), BV(6), BV(7) };

void display_draw_pixel(uint8_t x, uint8_t y, uint8_t color) {
	uint8_t __xdata *screen_ptr = display_get_screen_ptr(x,y);
	uint8_t pixel = *screen_ptr;
	uint8_t bitMask = _bitmasks[y % 8];
	if (color)
		pixel &= ~bitMask;
	else
		pixel |= bitMask;
	*screen_ptr = pixel;
}
