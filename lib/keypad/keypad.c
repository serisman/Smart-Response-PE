// Name: keypad/keypad.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "hal.h"
#include "util.h"
#include "keypad.h"

#define PIN_KB_PWR_COL			P0,0
#define PIN_KB_PWR_ROW			P1,7

#define PIN_KB_COL_TOP			P1,5
#define PIN_KB_COL_1				P2,0
#define PIN_KB_COL_2				P0,1
#define PIN_KB_COL_3				P1,6

#define PIN_KB_ROW_1				P1,0
#define PIN_KB_ROW_2				P1,1
#define PIN_KB_ROW_3				P1,2
#define PIN_KB_ROW_4				P1,3
#define PIN_KB_ROW_5				P1,4

uint8_t keypad_keymap_0;
uint8_t keypad_keymap_1;
uint8_t keypad_keymap_2;
uint8_t keypad_keymap_3;

#define _keyboard_scan_col(col,PIN_KB_COL_x)	\
  setPinOutput_EX(PIN_KB_COL_x); \
  clearPin_EX(PIN_KB_COL_x); \
  keys = _keypad_scan_rows(); \
  setPin_EX(PIN_KB_COL_x); \
  setPinInput_EX(PIN_KB_COL_x); \
  keypad_keymap_ ## col = keys;

uint8_t _keypad_scan_rows();

void keypad_scan() {
  uint8_t keys;

  clearBits(P1DIR,BV6(7,4,3,2,1,0)); // Set keypad rows as inputs

  _keyboard_scan_col(0,PIN_KB_COL_TOP);
  _keyboard_scan_col(1,PIN_KB_COL_1);
  _keyboard_scan_col(2,PIN_KB_COL_2);
  _keyboard_scan_col(3,PIN_KB_COL_3);

// Read the PWR button
  keys = 0;
  setPinOutput(PIN_KB_PWR_COL);
  clearPin(PIN_KB_PWR_COL);
  if (isPinLow(PIN_KB_PWR_ROW))
    keys |= BV(7);
  setPin(PIN_KB_PWR_COL);
  setPinInput(PIN_KB_PWR_COL);
  keypad_keymap_0 |= keys;
}

// private methods --------------------------------------------------------

uint8_t _keypad_scan_rows() {
  uint8_t keymap = 0;
  if (isPinLow(PIN_KB_ROW_1))
    keymap |= BV(0);
  if (isPinLow(PIN_KB_ROW_2))
    keymap |= BV(1);
  if (isPinLow(PIN_KB_ROW_3))
    keymap |= BV(2);
  if (isPinLow(PIN_KB_ROW_4))
    keymap |= BV(3);
  if (isPinLow(PIN_KB_ROW_5))
    keymap |= BV(4);
  return keymap;
}
