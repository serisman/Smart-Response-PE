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

void print_keymap() {
  uint8_t i, keymap[4];

	keyboard_scan(keymap);

	if (keymap[0] != prev_keymap[0] || keymap[1] != prev_keymap[1] || keymap[2] != prev_keymap[2] || keymap[3] != prev_keymap[3]) {
		uart_printf("keyscan: ");
		display_set_cursor(5,2);
		for (i=0; i<4; i++) {
			prev_keymap[i] = keymap[i];
			u_to_bin_str(keymap[i], 5, str_buf);
			uart_printf(str_buf); uart_printf(" ");
			display_printf(str_buf); display_printf((i == 1) ? "\r\n " : " ");
		}
		uart_printf("\r\n");
	}
}

inline void loop() {
	uint32_t millis = clock_millis();
	ul_to_str(millis, str_buf);

	if (millis-prev_millis >= 1000) {
		uart_printf("millis: "); uart_printf(str_buf); uart_printf("\r\n");
		prev_millis += 1000;
	}

	display_set_cursor(4,1);
	display_printf(str_buf); display_printf(" ms.");

	print_keymap();

	clock_delay_ms(100);
}

inline void setup() {
	uart_printf("Hello World!\r\n");

	uc1701_draw_bitmap((SCREEN_WIDTH-35-60)/2, 0, bmp_smart_logo, 60, 2);
	uc1701_draw_bitmap(SCREEN_WIDTH-35, 0, bmp_wolf, 35, 6);

	display_set_cursor(3,1);
	display_printf("Hello World!");
}

void main() {
	hardware_init();
	setup();

	while(1) {
		loop();
	}
}
