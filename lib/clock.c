// Name: clock.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "util.h"
#include "clock.h"

#define uS_PER_TICK			4
#define TICKS_PER_MS		(1000 / uS_PER_TICK)

volatile uint32_t _clock_millis = 0;
volatile uint8_t _clock_delay_ms = 0;

#ifdef CLOCK_MICROS
volatile uint32_t _clock_ticks = 0;
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
	T4CTL = ((7-TICKSPD) << TxCTL_DIV_0) | BV4(4,3,2,1);
	T4CC0 = TICKS_PER_MS;
	T4IE = 1;	// Timer 4 Interrupt Enable
}

INTERRUPT(clock_isr, T4_VECTOR) {
	if (T4OVFIF) {		// Did a timer overflow occur?
		_clock_millis++;

		if (_clock_delay_ms) _clock_delay_ms--;

#ifdef CLOCK_MICROS
		_clock_ticks += TICKS_PER_MS;
#endif

		T4OVFIF = 0;		// Clear timer overflow interrupt flag
	}
}
