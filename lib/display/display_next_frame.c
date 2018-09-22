// Name: display/display_next_frame.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"
#include "clock.h"

bool display_next_frame() {
	uint32_t millis = clock_millis();
	uint8_t elapsed_ms = millis - _prev_frame_ms;

	if (elapsed_ms >= display_each_frame_millis) {
		_prev_frame_ms = millis;
		return true;
	}

	clock_delay_ms(1);
	return false;
}
