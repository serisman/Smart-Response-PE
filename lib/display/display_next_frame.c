// Name: display/display_next_frame.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"
#include "clock.h"

uint8_t display_each_frame_millis = 1000 / 30;
uint32_t display_prev_frame_ms = 0;
uint8_t display_frame_count = 0;

bool display_next_frame() {
	uint32_t millis = clock_millis();
	uint8_t elapsed_ms = millis - display_prev_frame_ms;

	if (elapsed_ms >= display_each_frame_millis) {
		display_prev_frame_ms = millis;
		display_frame_count++;
		return true;
	}

	clock_delay_ms(1);
	return false;
}
