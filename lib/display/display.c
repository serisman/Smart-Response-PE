// Name: display/display.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"

uint8_t __xdata screen[NUM_SCREEN_ROWS * SCREEN_WIDTH];

uint8_t display_each_frame_millis = 1000 / 30;
uint32_t display_prev_frame_ms = 0;

uint8_t display_cursor_x = 0;
uint8_t display_cursor_y = 0;

inline void display_init() {
	uc1701_init();
}

inline void display_paint() {
	uc1701_paint(screen);
}
