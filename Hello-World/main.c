// Name: main.c
// Project: Smart-Response-PE/Hello-World
// Author: Stephen Erisman
// Creation Date: 2018-09-14
// License: MIT

#include "hardware.h"
#include "clock.h"

inline void loop() {
	PIN_RED_LED = 1;
	PIN_GREEN_LED = 0;
	PIN_TX_LED = 1;
	PIN_RX_LED = 0;
	clock_delay_ms(250);

	PIN_TX_LED = 0;
	PIN_RX_LED = 1;
	clock_delay_ms(250);

	PIN_RED_LED = 0;
	PIN_GREEN_LED = 1;
	PIN_TX_LED = 1;
	PIN_RX_LED = 0;
	clock_delay_ms(250);

	PIN_TX_LED = 0;
	PIN_RX_LED = 1;
	clock_delay_ms(250);
}

inline void setup() {
	clock_init();

	P0DIR = 0xFF;	// Port 0 - set as outputs
	P0 = 0x00; 		// Port 0 - set all low
}

void main() {
	setup();

	ENABLE_INTERRUPTS;
	for(;;) {
		loop();
	}
}
