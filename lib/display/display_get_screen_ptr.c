// Name: display/display_get_screen_ptr.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"

uint8_t __xdata *display_get_screen_ptr(uint8_t x, uint8_t y) {
  return &screen[(y/8u*SCREEN_WIDTH) + x];
}
