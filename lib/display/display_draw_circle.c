// Name: display/display_draw_circle.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"

void display_draw_circle(uint8_t x0, uint8_t y0, uint8_t r) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  display_draw_pixel(x0, y0+r);
  display_draw_pixel(x0, y0-r);
  display_draw_pixel(x0+r, y0);
  display_draw_pixel(x0-r, y0);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }

    x++;
    ddF_x += 2;
    f += ddF_x;

    display_draw_pixel(x0 + x, y0 + y);
    display_draw_pixel(x0 - x, y0 + y);
    display_draw_pixel(x0 + x, y0 - y);
    display_draw_pixel(x0 - x, y0 - y);
    display_draw_pixel(x0 + y, y0 + x);
    display_draw_pixel(x0 - y, y0 + x);
    display_draw_pixel(x0 + y, y0 - x);
    display_draw_pixel(x0 - y, y0 - x);
  }
}
