// Name: keypad/keypad_just_released.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "keypad.h"

bool keypad_just_released(uint8_t col, uint8_t mask) {
  uint8_t keymap, previous_keymap;

  keymap = keypad_get_keymap(col);
  if ((keymap & mask) == mask)		// Return false if button is currently pressed.
    return false;

  previous_keymap = keypad_get_previous_keymap(col);
  return (previous_keymap & mask) == mask;	// Return true if button previously was pressed.
}
