// Name: main.c
// Project: Smart-Response-PE/Hello-World
// Author: Stephen Erisman
// Creation Date: 2018-09-14
// License: MIT

#include <stdio.h>

#include "hardware.h"
#include "clock.h"
#include "uart.h"

inline void loop() {
	uint32_t millis = clock_millis();
	printf("millis: ");	put_ul(millis);	printf("\r\n");

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
	// TODO... set clock to 32 MHz on boot?
	clock_init();

	P0 = 0xC0; 			// Port 0 - set all low (except TxD/RxD)
	P0DIR = 0x5F;		// Port 0 - set as outputs (except RxD/CTS)

	uart_init();
	clock_delay_ms(10);	// let the baud rate timer settle in?
	printf("Hello World!\r\n");
}

void main() {
	ENABLE_INTERRUPTS;
	setup();

	for(;;) {
		loop();
	}
}
