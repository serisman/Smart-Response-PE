// Name: display/display.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"

uint8_t __xdata screen[NUM_SCREEN_ROWS * SCREEN_WIDTH];

inline void display_init() {
	uc1701_init();
}

inline void display_invert(bool invert) {
	uc1701_invert(invert);
}

inline void display_paint() {
	uc1701_paint(screen, true);
}
