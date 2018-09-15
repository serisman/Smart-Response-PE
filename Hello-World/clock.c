// Name: clock.c
// Project: Smart-Response-PE/Hello-World
// Author: Stephen Erisman
// Creation Date: 2018-09-14
// License: MIT

#include "hardware.h"

#define uS_PER_TICK			4
#define TICKS_PER_MS		(1000 / uS_PER_TICK)

volatile uint32_t _millis = 0;
volatile uint32_t _ticks = 0;

void clock_init() {
	// Configure 8-bit Timer 4
	//  [7:5] Set Prescaler to /64 ... each tick = 4 uS (with a 16MHz clock)
	//  [4] Start timer
	//  [3] Enable Overflow interrupt
	//  [2] Clear counter
	//  [1:0] Modulo, repeatedly count from 0x00 to T4CC0 (TICKS_PER_MS)
	T4CTL = 0xDE;
	T4CC0 = TICKS_PER_MS;
	T4IE = 1;	// Timer 4 Interrupt Enable
}

// NOTE: resolution is 4uS (overflows in approx 70 minutes?)
uint32_t clock_micros() {
	uint32_t micros;

	ATOMIC_BEGIN;
		micros = _ticks;
		micros += T4CNT;

		if (T4OVFIF) {
			micros += TICKS_PER_MS;
		}
		micros *= uS_PER_TICK;
	ATOMIC_END;

	return micros;
}

uint32_t clock_millis() {
	uint32_t millis;

	ATOMIC_BEGIN;
		millis = _millis;
	ATOMIC_END;

	return millis;	
}

void clock_delay_ms(uint32_t ms) {
	uint32_t start, now;

	start = clock_millis();
	do {
		now = clock_millis();
	} while ((now-start) < ms);
}

// private methods --------------------------------------------------------

INTERRUPT(clock_isr, T4_VECTOR) {
	if (T4OVFIF) {		// Did a timer overflow occur?
		_ticks += TICKS_PER_MS;
		_millis++;

		T4OVFIF = 0;		// Clear timer overflow interrupt flag
	}
}
