// Name: keypad/keypad_any_pressed.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "keypad.h"

bool keypad_any_pressed() {
  return keypad_keymap_0 || keypad_keymap_1 || keypad_keymap_2 || keypad_keymap_3;
}
