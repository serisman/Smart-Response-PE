// Name: display/display_set_frame_rate.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"

void display_set_frame_rate(uint8_t rate) {
	display_each_frame_millis = 1000 / rate;
}
