// Name: uart.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-14
// License: MIT

#ifndef __uart_h_included__
#define __uart_h_included__

// Baudrate = (((256 + BAUD_M) * POW(2,BAUD_E)) / POW(2,28)) * (Hz * 1000000)
//
// BAUD_E = LOG(((Baudrate / (Hz * 1000000)) * POW(2,28)) / (256 + BAUD_M)) / LOG(2)
// BAUD_M = (((baudrate / (Hz * 1000000)) * POW(2,28)) / POW(2,BAUD_E))) - 256


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
void uart_enable();
void uart_disable();
void uart_wait_for_tx_idle();

void uart_put_c(char c);
void uart_printf(char * str);

#endif /* __uart_h_included__ */
