// Name: display/display_every_x_frames.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"

bool display_every_x_frames(uint8_t frames) {
	return display_frame_count % frames == 0;
}
