// Name: display/display_print.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"

void display_print(char *str) {
	while (*str) {
		display_draw_char(*str++);
	}
}
