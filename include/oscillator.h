// Name: oscillator.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __oscillator_h_included__
#define __oscillator_h_included__

#include "util.h"
#include "delay.h"

inline void oscillator_32mhz() {
	clearBit(SLEEP,SLEEP_OSC_PD); 							// Enable both 16 MHz RC and 32 MHz crystal oscillators
	while (isBitClear(SLEEP,SLEEP_XOSC_STB));	  // Wait for XOSC to power up and be stable
	delay_us_16mhz(64);

	clearBit(CLKCON,CLKCON_OSC);								// Select 32 MHz crystal oscillator
	while (isBitSet(CLKCON,CLKCON_OSC));				// Wait for system clock to switch to 32 MHz crystal oscillator
	setBit(SLEEP,SLEEP_OSC_PD);								  // Disable 16 MHz RC oscillator

	clearBits(CLKCON,BV3(CLKCON_TICKSPD_2,CLKCON_TICKSPD_1,CLKCON_TICKSPD_0));  // Set timer ticks to 32 MHz
}

#endif /* __oscillator_h_included__ */
