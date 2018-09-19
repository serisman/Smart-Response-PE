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
volatile uint32_t _ticks = 0;

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
