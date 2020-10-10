// Name: display/display_draw_pixel.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "util.h"
#include "display.h"

void display_draw_pixel(uint8_t x, uint8_t y) {
  uint8_t __xdata *screen_ptr = display_get_screen_ptr(x,y);
  uint8_t pixel = *screen_ptr;
  uint8_t bitMask = util_bit_to_mask[y % 8];
  if (display_color)
    pixel &= ~bitMask;
  else
    pixel |= bitMask;
  *screen_ptr = pixel;
}
