// Name: keypad/keypad_pressed.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "keypad.h"

bool keypad_pressed(uint8_t col, uint8_t mask) {
	uint8_t keymap = keypad_get_keymap(col);
	return (keymap & mask) == mask;
}
