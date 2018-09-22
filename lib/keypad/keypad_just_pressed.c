// Name: keypad/keypad_just_pressed.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "keypad.h"

bool keypad_just_pressed(uint8_t col, uint8_t mask) {
	uint8_t keymap, previous_keymap;

	keymap = keypad_get_keymap(col);
	if ((keymap & mask) == 0)		// Return false if button is not currently pressed.
		return false;

	previous_keymap = keypad_get_previous_keymap(col);
	return (previous_keymap & mask) == 0;	// Return true if button previously was not pressed.
}
