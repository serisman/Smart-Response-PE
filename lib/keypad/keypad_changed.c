// Name: keypad/keypad_changed.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "keypad.h"

bool keypad_changed() {
  // It's a bit ugly, but this approach seems to generate the most efficient assembly code
  if (keypad_keymap_0 != keypad_previous_keymap_0)	goto _true;
  if (keypad_keymap_1 != keypad_previous_keymap_1)	goto _true;
  if (keypad_keymap_2 != keypad_previous_keymap_2)	goto _true;
  if (keypad_keymap_3 != keypad_previous_keymap_3)	goto _true;
  return false;

_true:
  return true;
}
