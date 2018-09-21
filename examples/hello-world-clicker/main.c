// Name: main.c
// Project: Smart-Response-PE/examples/hello-world-clicker
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "cc2430.h"
#include "clock.h"
#include "uart.h"
#include "display.h"
#include "keypad.h"
#include "string_utils.h"

#include "bitmaps.h"

char __xdata str_buf[10];

uint32_t prev_millis = 0;
uint8_t __xdata prev_keymap[4] = {0,0,0,0};

int8_t scroll_x = 0;
int8_t scroll_x_dir = 1;

int8_t scroll_y = 0;
int8_t scroll_y_dir = 1;

inline void setup() {
	uart_init();
	uart_println("Hello World!");

	display_init();
	display_set_frame_rate(30);
}

inline void loop() {
	uint8_t __xdata keymap[4];
	uint32_t millis;

	millis = clock_millis();
	u32_to_str(millis, str_buf);
	if (millis-prev_millis >= 1000) {
		uart_print("millis: "); uart_println(str_buf);
		prev_millis += 1000;
	}

	keypad_scan(keymap);
	if (keymap[0] != prev_keymap[0] || keymap[1] != prev_keymap[1] || keymap[2] != prev_keymap[2] || keymap[3] != prev_keymap[3]) {
		uart_print("keymap: ");
		for (uint8_t i=0; i<4; i++) {
			prev_keymap[i] = keymap[i];
			u8_to_bin_str(keymap[i], 5, str_buf);
			uart_print(str_buf); uart_print(" ");
		}
		uart_println("");
	}

	if (!display_next_frame())
		return;

	display_draw_bitmap(scroll_x, 0, bmp_smart_logo, 60, 16, COLOR_BLACK);
	scroll_x += scroll_x_dir;
	if (scroll_x + (uint8_t)60 > SCREEN_WIDTH-35 || scroll_x + (uint8_t)(60/2) < 0) {
		scroll_x_dir = (uint8_t)0- scroll_x_dir;
	}

	display_draw_bitmap(SCREEN_WIDTH-35, scroll_y, bmp_wolf, 35, 48, COLOR_BLACK);
	scroll_y += scroll_y_dir;
	if (scroll_y + (uint8_t)(48/2) > SCREEN_HEIGHT || scroll_y + (uint8_t)(48/2) < 0) {
		scroll_y_dir = (uint8_t)0- scroll_y_dir;
	}

	display_set_cursor(3,17);
	display_print("Hello World!");

	display_set_cursor(3,25);
	u32_to_str(millis, str_buf);
	display_print(str_buf); display_print(" ms.");

	display_set_cursor(12,33);
	for (uint8_t i=0; i<4; i++) {
		u8_to_bin_str(keymap[i], 5, str_buf);
		display_print(str_buf); display_print((i == 1) ? "\r\n\t" : " ");
	}

	display_paint();
}

void main() {
	oscillator_32mhz();
	clock_init();
	ENABLE_INTERRUPTS;
	setup();

	while(1) {
		loop();
	}
}
