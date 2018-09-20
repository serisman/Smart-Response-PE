// Name: main.c
// Project: Smart-Response-PE/Hello-World-Clicker
// Author: Stephen Erisman
// Creation Date: 2018-09-17
// License: MIT

#include "hardware.h"
#include "lib/keyboard.h"
#include "lib/display.h"
#include "lib/num-to-string.h"

#include "bitmaps.h"

char str_buf[10];

uint32_t prev_millis = 0;
uint8_t prev_keymap[4] = {0,0,0,0};

int8_t scroll_x = 0;
int8_t scroll_x_dir = 1;

int8_t scroll_y = 0;
int8_t scroll_y_dir = 1;

inline void loop() {
	uint8_t keymap[4];
	uint32_t millis;

	millis = clock_millis();
	ul_to_str(millis, str_buf);
	if (millis-prev_millis >= 1000) {
		uart_printf("millis: "); uart_printf(str_buf); uart_printf("\r\n");
		prev_millis += 1000;
	}

	keyboard_scan(keymap);
	if (keymap[0] != prev_keymap[0] || keymap[1] != prev_keymap[1] || keymap[2] != prev_keymap[2] || keymap[3] != prev_keymap[3]) {
		uart_printf("keymap: ");
		for (uint8_t i=0; i<4; i++) {
			prev_keymap[i] = keymap[i];
			u_to_bin_str(keymap[i], 5, str_buf);
			uart_printf(str_buf); uart_printf(" ");
		}
		uart_printf("\r\n");
	}

	if (!display_next_frame())
		return;

	display_draw_bitmap(scroll_x, 0, bmp_smart_logo, 60, 16, COLOR_BLACK);
	scroll_x += scroll_x_dir;
	if (scroll_x + 60 > SCREEN_WIDTH-35 || scroll_x + 60/2 < 0) {
		scroll_x_dir = 0- scroll_x_dir;
	}

	display_draw_bitmap(SCREEN_WIDTH-35, scroll_y, bmp_wolf, 35, 48, COLOR_BLACK);
	scroll_y += scroll_y_dir;
	if (scroll_y + 48/2 > SCREEN_HEIGHT || scroll_y + 48/2 < 0) {
		scroll_y_dir = 0- scroll_y_dir;
	}

	display_set_cursor(3,17);
	display_printf("Hello World!");

	display_set_cursor(3,25);
	display_printf(str_buf); display_printf(" ms.");

	display_set_cursor(12,33);
	for (uint8_t i=0; i<4; i++) {
		u_to_bin_str(keymap[i], 5, str_buf);
		display_printf(str_buf); display_printf((i == 1) ? "\r\n\t" : " ");
	}

	display_paint();
}

inline void setup() {
	uart_printf("Hello World!\r\n");

	display_set_frame_rate(30);
}

void main() {
	hardware_init();
	setup();

	while(1) {
		loop();
	}
}
