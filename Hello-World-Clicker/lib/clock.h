// Name: clock.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-14
// License: MIT

#ifndef __clock_h_included__
#define __clock_h_included__

void clock_init();

uint32_t clock_millis();
void clock_delay_ms(uint8_t ms);
void clock_long_delay_ms(uint16_t ms);

#ifdef CLOCK_MICROS
uint32_t clock_micros();
#endif

INTERRUPT(clock_isr, T4_VECTOR);

#endif /* __clock_h_included__ */
