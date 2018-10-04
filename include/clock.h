// Name: clock.h
// Project: Smart-Response-PE/include
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __clock_h_included__
#define __clock_h_included__

#include <stdint.h>
#include "hal.h"

extern volatile uint32_t _clock_ticks;
extern volatile uint32_t _clock_millis;
extern volatile uint8_t _clock_delay_ms;

void clock_init();

uint32_t clock_millis();
void clock_delay_ms(uint8_t ms);
void clock_long_delay_ms(uint16_t ms);

uint32_t clock_micros();

INTERRUPT(clock_isr, T4_VECTOR);

#endif /* __clock_h_included__ */
