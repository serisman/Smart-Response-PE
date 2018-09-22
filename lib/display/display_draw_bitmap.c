// Name: display/display_draw_bitmap.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"

void display_draw_bitmap(int8_t x, int8_t y, uint8_t *bitmap, uint8_t width, uint8_t height, uint8_t color) {
	int8_t yOffset, row, end_row;
	uint8_t bitmap_pixel, pixel_mask, screen_pixel;
	uint8_t __xdata *screen_ptr;
	uint8_t __xdata *screen_ptr2 = screen_ptr;

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
		screen_ptr = display_get_screen_ptr(x>=0 ? x : 0, row*8);
		if (yOffset && row<NUM_SCREEN_ROWS-1 && row >= -1) {
			screen_ptr2 = display_get_screen_ptr(x>=0 ? x : 0, (row+1)*8);
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
