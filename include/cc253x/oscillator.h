// Name: cc253x/oscillator.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-10-03
// License: MIT

#ifndef __oscillator_h_included__
#define __oscillator_h_included__

#include "util.h"

inline void oscillator_32mhz() {
  clearBit(CLKCONCMD,CLKCON_OSC);						    // Select 32 MHz crystal oscillator
  while (isBitSet(CLKCONSTA,CLKCON_OSC));		    // Wait for system clock to switch to 32 MHz crystal oscillator

  clearBits(CLKCONCMD,BV3(CLKCON_CLKSPD_2,CLKCON_CLKSPD_1,CLKCON_CLKSPD_0));  // Set clock frequency to 32 MHz
  while (CLKCONSTA != CLKCONCMD);

  clearBits(CLKCONCMD,BV3(CLKCON_TICKSPD_2,CLKCON_TICKSPD_1,CLKCON_TICKSPD_0));  // Set timer ticks to 32 MHz
  while (CLKCONSTA != CLKCONCMD);
}

inline uint8_t oscillator_get_timer_tick_speed() {
  return (CLKCONSTA >> CLKCON_TICKSPD_0) & 0x7;
}

inline bool oscillator_is_32mhz() {
  return (CLKCONSTA & 0x7) == 0;
}

#endif /* __oscillator_h_included__ */
