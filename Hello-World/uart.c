// Name: uart.c
// Project: Smart-Response-PE/Hello-World
// Author: Stephen Erisman
// Creation Date: 2018-09-14
// License: MIT

#include "hardware.h"
#include "uart.h"

void uart_init() {
	uint8_t BAUD_E;

	PERCFG |= (1 << 1);		// U1CFG=1 // Enable USART1 Alternate 2 I/O location - P1_4:7

	P1SEL |= 0xC0;				// Enable Peripheral function for TX and RX
	P1 &= ~0x20;					// Set RTS Low
	P1DIR |= 0x60;				// Set RTS and TX as Outputs
	P1DIR &= ~0x90;				// Set CTS and RX as Inputs

	U1UCR = 0x82;					// (defaults) 8N1, no flow control, high stop bit (and FLUSH any activity)
	UTX1IF = 0;

	// Default to 115200 baud
	if (!(CLKCON & 0x01))
		BAUD_E = 11;				// 32 MHz
	else
		BAUD_E = 12;				// 16 MHz
	uart_set_baud(BAUD_E, 216);

	U1CSR |= (1<<7); 			// MODE=1 // Switch to UART mode
}

void uart_set_baud(uint8_t BAUD_E, uint8_t BAUD_M) {
	U1GCR &= 0xE0;
	U1GCR |= (BAUD_E & 0x1F);	// BAUD_E[4:0] (exponent)
	U1BAUD = BAUD_M;					// BAUD_M (mantissa)
}

int putchar(int c) {
	put_c(c);
	return c;
}

void put_c(char c) {
	UTX1IF = 0;
	U1DBUF = c;
	while (!(UTX1IF));		// Wait until the byte has been transmitted
	UTX1IF = 0;
}

void put_str(char * str) {
	uint8_t i = 0;
	while (str[i] != 0) {
		put_c(str[i++]);
	}
}

char buf[10];

void put_u(uint8_t ul) {
	uint8_t pos = 0;
	do {
		buf[pos++] = '0' + (ul % 10);
		ul /= 10;
	} while (ul != 0);
	while (pos-- > 0) {
		put_c(buf[pos]);
	}
}

void put_ul(uint32_t ul) {
	uint8_t pos = 0;
	do {
		buf[pos++] = '0' + (ul % 10);
		ul /= 10;
	} while (ul != 0);
	while (pos-- > 0) {
		put_c(buf[pos]);
	}
}

void put_ulb(uint32_t ul, uint8_t length) {
	while (length--) {
		if (ul & (1UL << length)) {
			put_c('1');
		} else {
			put_c('0');
		}
	}
}
