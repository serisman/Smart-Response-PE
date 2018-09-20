// Name: clock.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-14
// License: MIT

#include "../hardware.h"
#include "util.h"
#include "clock.h"

#define uS_PER_TICK			4
#define TICKS_PER_MS		(1000 / uS_PER_TICK)

volatile uint32_t _millis = 0;
volatile uint8_t _delay_ms = 0;

#ifdef CLOCK_MICROS
volatile uint32_t _ticks = 0;
#endif

// MHz	TICKSPD		Prescaler	DIV
// 32		0					/128			7
// 16		1					/64				6
// 8		2					/32				5
// 4		3					/16				4
// 2		4					/8				3
// 1		5					/4				2
// .5		6					/2				1
// .25	7					/1				0

void clock_init() {
	uint8_t TICKSPD = (CLKCON >> CLKCON_TICKSPD_0) & 0x3;	// Look up global timer tick speed
	// Configure 8-bit Timer 4
	//  [7:5] DIV: Set Prescaler to generate a tick every 4 uS
	//  [4] START: Start timer
	//  [3] OVFIM: Enable Overflow interrupt
	//  [2] CLR: Clear counter
	//  [1:0] MODE: Modulo, repeatedly count from 0x00 to T4CC0 (TICKS_PER_MS)
	T4CTL = ((7-TICKSPD) << TxCTL_DIV_0) | _BV4(4,3,2,1);
	T4CC0 = TICKS_PER_MS;
	T4IE = 1;	// Timer 4 Interrupt Enable
}

uint32_t clock_millis() {
	uint32_t millis;

	ATOMIC_BEGIN;
		millis = _millis;
	ATOMIC_END;

	return millis;	
}

// Good for up to 255 ms.
void clock_delay_ms(uint8_t ms) {
	_delay_ms = ms;
	do {
		_setBit(PCON, PCON_IDLE); // Set CPU to idle.  CPU will be re-activated by the timer (or any other) interrupt
	} while (_delay_ms);
}

// Good for up to 65,535 ms. (anything longer should really use a different approach)
void clock_long_delay_ms(uint16_t ms) {
	uint16_t ctr = ms;
	while (ms > 255) {
		clock_delay_ms(255);
		ms -= 255;
	};
	clock_delay_ms(ms);
}

#ifdef CLOCK_MICROS
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
#endif

// private methods --------------------------------------------------------

INTERRUPT(clock_isr, T4_VECTOR) {
	if (T4OVFIF) {		// Did a timer overflow occur?
		_millis++;

		if (_delay_ms) _delay_ms--;

#ifdef CLOCK_MICROS
		_ticks += TICKS_PER_MS;
#endif

		T4OVFIF = 0;		// Clear timer overflow interrupt flag
	}
}
