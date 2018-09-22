// Name: display/display_fill_rect.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"

void display_fill_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color) {
	uint8_t yEnd = y + height;

	if (yEnd > SCREEN_HEIGHT)
		yEnd = SCREEN_HEIGHT;

	// TODO... optimize this...
  for (int y2 = y; y2 < yEnd; y2++) {
    display_draw_fast_hline(x,y2,width,color);
  }
}
