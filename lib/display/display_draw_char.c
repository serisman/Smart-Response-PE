// Name: display/display_draw_char.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"
#include "font_5x7.h"

uint8_t display_cursor_x = 0;
uint8_t display_cursor_y = 0;

void display_draw_char(char chr) {
  if (chr >= ' ' && chr <= '~') { // ASCII printable only
      //display_draw_bitmap(font_5x7_clear, display_cursor_x, display_cursor_y, CHAR_WIDTH, CHAR_HEIGHT, COLOR_WHITE); // clear behind char
      display_draw_bitmap(&font_5x7[(chr-' ')*5], display_cursor_x, display_cursor_y, CHAR_WIDTH-1, CHAR_HEIGHT);	// draw char
      display_cursor_x += CHAR_WIDTH;
  } else if (chr == '\r') {
    display_cursor_x = 0;
  } else if (chr == '\n') {
    display_cursor_y += CHAR_HEIGHT;
  } else if (chr == '\t') {
    display_cursor_x += CHAR_WIDTH*2;
  }
}
