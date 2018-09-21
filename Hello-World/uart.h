// Name: uart.h
// Project: Smart-Response-PE/Hello-World
// Author: Stephen Erisman
// Creation Date: 2018-09-14
// License: MIT

#ifndef __uart_h_included__
#define __uart_h_included__

// Baudrate = (((256 + BAUD_M) * POW(2,BAUD_E)) / POW(2,28) * F_CPU

// Examples 			@ 16 MHz					@ 32 MHz
//  Baudrate		BAUD_E	BAUD_M		BAUD_E	BAUD_M
// 		9600				9				59				8				59
// 		14400				9				216				8				216
// 		19200				10			59				9				59
// 		28800				10			216				9				216
// 		38400				11			59				10			59
// 		57600				11			216				10			216
// 		76800				12			59				11			59
// 		115200			12			216				11			216

void uart_init();		// defaults to 115200 baud
void uart_set_baud(uint8_t BAUD_E, uint8_t BAUD_M);

int putchar(int c);	// enables printf support

void put_c(char c);
void put_str(char * str);
void put_u(uint8_t ul);
void put_ul(uint32_t ul);

#endif /* __uart_h_included__ */
