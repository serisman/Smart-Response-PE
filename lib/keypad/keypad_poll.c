// Name: keypad/keypad_poll.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "keypad.h"

uint8_t __xdata keypad_previous_keymap_0;
uint8_t __xdata keypad_previous_keymap_1;
uint8_t __xdata keypad_previous_keymap_2;
uint8_t __xdata keypad_previous_keymap_3;

void keypad_poll() {
	keypad_previous_keymap_0 = keypad_keymap_0;
	keypad_previous_keymap_1 = keypad_keymap_1;
	keypad_previous_keymap_2 = keypad_keymap_2;
	keypad_previous_keymap_3 = keypad_keymap_3;

	keypad_scan();
}
