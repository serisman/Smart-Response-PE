// Name: hardware.h
// Project: Smart-Response-PE/Hello-World-Clicker
// Author: Stephen Erisman
// Creation Date: 2018-09-17
// License: MIT

#ifndef __hardware_h_included__
#define __hardware_h_included__

#include <stdint.h>

#include "lib/cc2430.h"
//#include "lib/util.h"
//#include "lib/delay.h"
#include "lib/oscillator.h"
#include "lib/clock.h"
#include "lib/uart.h"
#include "lib/uc1701.h"

#define ENABLE_INTERRUPTS 				EA=1
#define DISABLE_INTERRUPTS 				EA=0

//#define ATOMIC_BEGIN							// TODO: save IEN0?, then EA=0
//#define ATOMIC_END								// TODO: restore IEN0?
#define ATOMIC_BEGIN							DISABLE_INTERRUPTS
#define ATOMIC_END								ENABLE_INTERRUPTS

// -------------------------------------


// -------------------------------------

inline void hardware_init() {
	oscillator_init32();

	clock_init();
	uart_init();
	uc1701_init();

	ENABLE_INTERRUPTS;
}

#endif /* __hardware_h_included__ */
