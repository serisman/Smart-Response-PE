// Name: keyboard.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-17
// License: MIT

#include "../hardware.h"
#include "util.h"
#include "uart.h"
#include "keyboard.h"

//#define PIN_KB_PWR_COL			P0_0
//#define PIN_KB_PWR_ROW			P1_7

#define PIN_KB_COL_TOP			P1_5
#define PIN_KB_COL_1				P2_0
#define PIN_KB_COL_2				P0_1
#define PIN_KB_COL_3				P1_6

#define PIN_KB_ROW_1				P1_0
#define PIN_KB_ROW_2				P1_1
#define PIN_KB_ROW_3				P1_2
#define PIN_KB_ROW_4				P1_3
#define PIN_KB_ROW_5				P1_4

uint8_t _keyboard_scan_rows();

void keyboard_scan(uint8_t *keymap) {
  uart_wait_for_tx_idle();
  uart_disable();

	//_clearBits(P1DIR,_BV6(7,4,3,2,1,0)); // Set keyboard rows as inputs
	_clearBits(P1DIR,_BV5(4,3,2,1,0)); // Set keyboard rows as inputs

	_setBit(P1DIR,5);
	PIN_KB_COL_TOP = 0;
	keymap[0] = _keyboard_scan_rows();
	PIN_KB_COL_TOP = 1;
	_clearBit(P1DIR,5);

	// Read the on/off button
//	_setBit(P0DIR,0);
//	PIN_KB_PWR_COL = 0;
//	if (!PIN_KB_PWR_ROW)
//		keymap[0] |= _BV(7);
//	PIN_KB_PWR_COL = 1;
//	_clearBit(P0DIR,0);

	_setBit(P2DIR,0);
	PIN_KB_COL_1 = 0;
	keymap[1] = _keyboard_scan_rows();
	PIN_KB_COL_1 = 1;
	_clearBit(P2DIR,0);

	_setBit(P0DIR,1);
	PIN_KB_COL_2 = 0;
	keymap[2] = _keyboard_scan_rows();
	PIN_KB_COL_2 = 1;
	_clearBit(P0DIR,1);

	_setBit(P1DIR,6);
	PIN_KB_COL_3 = 0;
	keymap[3] = _keyboard_scan_rows();
	PIN_KB_COL_3 = 1;
	_clearBit(P1DIR,6);

	uart_enable();
}

// private methods --------------------------------------------------------

uint8_t _keyboard_scan_rows() {
	uint8_t keymap = 0;
	if (!PIN_KB_ROW_1)
		keymap |= _BV(0);
	if (!PIN_KB_ROW_2)
		keymap |= _BV(1);
	if (!PIN_KB_ROW_3)
		keymap |= _BV(2);
	if (!PIN_KB_ROW_4)
		keymap |= _BV(3);
	if (!PIN_KB_ROW_5)
		keymap |= _BV(4);
	return keymap;
}
