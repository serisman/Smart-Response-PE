// Name: hardware.h
// Project: Smart-Response-PE/Hello-World
// Author: Stephen Erisman
// Creation Date: 2018-09-14
// License: MIT

#ifndef __hardware_h_included__
#define __hardware_h_included__

#include <stdint.h>

#include "mcs51/cc2430.h" // https://github.com/darconeous/sdcc/blob/master/device/include/mcs51/cc2430.h

#define ENABLE_INTERRUPTS 				EA=1;
#define DISABLE_INTERRUPTS 				EA=0;

#define ATOMIC_BEGIN							// TODO: save IEN0?, then EA=0
#define ATOMIC_END								// TODO: restore IEN0?

// -------------------------------------

#define PIN_RED_LED				P0_0
#define PIN_GREEN_LED			P0_1
#define PIN_TX_LED				P0_6
#define PIN_RX_LED				P0_7

#endif /* __hardware_h_included__ */
