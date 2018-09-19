// Name: oscillator.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-17
// License: MIT

#ifndef __oscillator_h_included__
#define __oscillator_h_included__

#include "lib/util.h"
#include "lib/delay.h"

inline void oscillator_init32() {
	_clearBit(SLEEP,SLEEP_OSC_PD); 							// Enable both 16 MHz RC and 32 MHz crystal oscillators
	while (_isBitClear(SLEEP,SLEEP_XOSC_STB));	// Wait for XOSC to power up and be stable
	_delay16_short_us(64);

	_clearBit(CLKCON,CLKCON_OSC);								// Select 32 MHz crystal oscillator
	while (_isBitSet(CLKCON,CLKCON_OSC));				// Wait for system clock to switch to 32 MHz crystal oscillator
	_setBit(SLEEP,SLEEP_OSC_PD);								// Disable 16 MHz RC oscillator

	_clearBits(CLKCON,_BV3(CLKCON_TICKSPD_2,CLKCON_TICKSPD_1,CLKCON_TICKSPD_0));			// Set timer ticks to 32 MHz
}

#endif /* __oscillator_h_included__ */
