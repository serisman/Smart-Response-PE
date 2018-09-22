// Name: keypad.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "cc2430.h"
#include "util.h"
#include "keypad.h"

//#define PIN_KB_PWR_COL			P0,0
//#define PIN_KB_PWR_ROW			P1,7

#define PIN_KB_COL_TOP			P1,5
#define PIN_KB_COL_1				P2,0
#define PIN_KB_COL_2				P0,1
#define PIN_KB_COL_3				P1,6

#define PIN_KB_ROW_1				P1,0
#define PIN_KB_ROW_2				P1,1
#define PIN_KB_ROW_3				P1,2
#define PIN_KB_ROW_4				P1,3
#define PIN_KB_ROW_5				P1,4

#define _keyboard_scan_col(keys_x,PIN_KB_COL_x)	\
	setPinOutput_EX(PIN_KB_COL_x); \
	clearPin_EX(PIN_KB_COL_x); \
	keys_x = _keypad_scan_rows(); \
	setPin_EX(PIN_KB_COL_x); \
	setPinInput_EX(PIN_KB_COL_x);

uint8_t _keypad_scan_rows();

void keypad_scan(uint8_t __xdata *keymap) {
	uint8_t keys_0,keys_1,keys_2,keys_3;

	//_clearBits(P1DIR,BV6(7,4,3,2,1,0)); // Set keypad rows as inputs
	clearBits(P1DIR,BV5(4,3,2,1,0)); // Set keypad rows as inputs

	_keyboard_scan_col(keys_0, PIN_KB_COL_TOP);
	_keyboard_scan_col(keys_1, PIN_KB_COL_1);
	_keyboard_scan_col(keys_2, PIN_KB_COL_2);
	_keyboard_scan_col(keys_3, PIN_KB_COL_3);

	// Read the on/off button
//	setPinOutput(PIN_KB_PWR_COL);
//	clearPin(PIN_KB_PWR_COL);
//	if (isPinLow(PIN_KB_PWR_ROW))
//		keys_0 |= BV(7);
//	setPin(PIN_KB_PWR_COL);
//	setPinInput(PIN_KB_PWR_COL);

	*keymap = keys_0;	keymap++;
	*keymap = keys_1;	keymap++;
	*keymap = keys_2;	keymap++;
	*keymap = keys_3;
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
