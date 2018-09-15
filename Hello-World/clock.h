// Name: clock.h
// Project: Smart-Response-PE/Hello-World
// Author: Stephen Erisman
// Creation Date: 2018-09-14
// License: MIT

#ifndef __clock_h_included__
#define __clock_h_included__

void clock_init();
uint32_t clock_micros();
uint32_t clock_millis();
void clock_delay_ms(uint32_t ms);

INTERRUPT(clock_isr, T4_VECTOR);

#endif /* __clock_h_included__ */
