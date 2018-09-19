// Name: uart.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-14
// License: MIT

#include "../hardware.h"
#include "util.h"
#include "uart.h"

void uart_init() {

	_setBit(PERCFG,PERCFG_U1CFG);	// Enable USART1 Alternate 2 I/O location - P1_4:7
	uart_enable();

	U1UCR = _BV2(UxUCR_FLUSH,UxUCR_STOP);	// (defaults) 8N1, no flow control, high stop bit (and FLUSH any activity)

	// Default to 115200 baud
	uart_set_baud(_isBitClear(CLKCON,CLKCON_CLKSPD) ? 11 : 12, 216); // 11 for 32 MHz, 12 for 16 MHz

	_setBit(U1CSR,UxCSR_MODE); 		// Switch to UART mode
}

void uart_set_baud(uint8_t BAUD_E, uint8_t BAUD_M) {
	_clearBits(U1GCR,_BV5(4,3,2,1,0));
	U1GCR |= (BAUD_E & 0x1F);	// BAUD_E[4:0] (exponent)
	U1BAUD = BAUD_M;					// BAUD_M (mantissa)
}

void uart_enable() {
	_setBits(P1,_BV2(7,6));				// Port 1 - set (7)RxD & (6)TxD high
	_setBit(P1DIR,6);							// Port 1 - set (6)TxD as output
	_clearBit(P1DIR,7);						// Port 1 - set (7)RxD as input
	_setBits(P1SEL,_BV2(7,6));		// Enable Peripheral function for (7)RxD & (6)TxD
}

void uart_disable() {
	_clearBits(P1SEL,_BV2(7,6));	// Disable Peripheral function for (7)RxD & (6)TxD
}

inline void uart_wait_for_tx_idle() {
	while (_isBitSet(U1CSR,UxCSR_ACTIVE));	// Wait until any previously written byte has been transmitted
}

void uart_put_c(char c) {
	uart_wait_for_tx_idle();
	U1DBUF = c;
}

void uart_printf(char * str) {
	while (*str != 0) {
		uart_wait_for_tx_idle();
		U1DBUF = *str;
		str++;
	}
}
