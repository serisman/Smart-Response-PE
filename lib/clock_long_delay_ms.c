// Name: clock_long_delay_ms.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "clock.h"

// Good for up to 65,535 ms. (anything longer should really use a different approach)
void clock_long_delay_ms(uint16_t ms) {
	uint16_t ctr = ms;
	while (ms > 255) {
		clock_delay_ms(255);
		ms -= 255;
	};
	clock_delay_ms(ms);
}
