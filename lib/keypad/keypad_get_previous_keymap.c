// Name: keypad/keypad_get_previous_keymap.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "keypad.h"

uint8_t keypad_get_previous_keymap(uint8_t col) {
  if (col == 3)	return keypad_previous_keymap_3;
  if (col == 2)	return keypad_previous_keymap_2;
  if (col == 1)	return keypad_previous_keymap_1;
  return keypad_previous_keymap_0;
}
