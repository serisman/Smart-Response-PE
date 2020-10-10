// Name: display/display_draw_rect.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"

void display_draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
  display_draw_fast_hline(x,y,width);
  display_draw_fast_hline(x,y+height-1,width);
  display_draw_fast_vline(x,y,height);
  display_draw_fast_vline(x+width-1,y,height);
}
