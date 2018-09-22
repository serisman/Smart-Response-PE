// Name: display/display_draw_fast_hline.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "util.h"
#include "display.h"

void display_draw_fast_hline(uint8_t x, uint8_t y, uint8_t width, uint8_t color) {
  uint8_t xEnd; // last x point + 1
	uint8_t pixel_mask, screen_pixel;
	uint8_t __xdata *screen_ptr;

  // Do y bounds checks
  if (/*y < 0 ||*/ y >= SCREEN_HEIGHT)
    return;

  xEnd = x + width;

  // Check if the entire line is not on the display
  if (/*xEnd <= 0 ||*/ x >= SCREEN_WIDTH)
    return;

  // Don't start before the left edge
//  if (x < 0)
//    x = 0;

  // Don't end past the right edge
  if (xEnd > SCREEN_WIDTH)
    xEnd = SCREEN_WIDTH;

  // calculate actual width (even if unchanged)
  width = xEnd - x;

	screen_ptr = display_get_screen_ptr(x, y);
	pixel_mask = util_bit_to_mask[y & 7];
	if (color != COLOR_BLACK)
		pixel_mask = ~pixel_mask;
	while (width--) {
		screen_pixel = *screen_ptr;
		if (color == COLOR_BLACK)
			screen_pixel |= pixel_mask;
		else
			screen_pixel &= pixel_mask;
		*screen_ptr++ = screen_pixel;
	}
}
