// Name: clock/clock_delay_ms.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "clock.h"

// Good for up to 255 ms.
void clock_delay_ms(uint8_t ms) {
  _clock_delay_ms = ms;
  do {
    setBit(PCON, PCON_IDLE); // Set CPU to idle.  CPU will be re-activated by the timer (or any other) interrupt
  } while (_clock_delay_ms);
}
