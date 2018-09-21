// Name: uart.h
// Project: Smart-Response-PE/include
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __uart_h_included__
#define __uart_h_included__

#include <stdint.h>
#include "cc2430.h"

// TODO... support easier re-configuration?
#define UART_NUM          1
#define UART_USE_ALT2     1

#if UART_NUM == 0
	#define PERCFG_UxCFG    PERCFG_U0CFG
	#define UxUCR           U0UCR
	#define UxCSR           U0CSR
	#define UxGCR           U0GCR
	#define UxBAUD          U0BAUD
	#define UxDBUF          U0DBUF

	#if UART_USE_ALT2 == 1
		#define PxSEL           P1SEL
		#define TX_PIN          P1,5
		#define RX_PIN				  P1,4
		#define UART_PIN_MASK   BV2(5,4)
	#else
		#define PxSEL           P0SEL
		#define TX_PIN          P0,3
		#define RX_PIN				  P0,2
		#define UART_PIN_MASK   BV2(3,2)
	#endif
#else
	#define PERCFG_UxCFG    PERCFG_U1CFG
	#define UxUCR           U1UCR
	#define UxCSR           U1CSR
	#define UxGCR           U1GCR
	#define UxBAUD          U1BAUD
	#define UxDBUF          U1DBUF

	#if UART_USE_ALT2 == 1
		#define PxSEL           P1SEL
		#define TX_PIN          P1,6
		#define RX_PIN				  P1,7
		#define UART_PIN_MASK   BV2(7,6)
	#else
		#define PxSEL           P0SEL
		#define TX_PIN          P0,4
		#define RX_PIN				  P0,5
		#define UART_PIN_MASK   BV2(5,4)
	#endif
#endif

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

void uart_init();
void uart_set_baud(uint8_t BAUD_E, uint8_t BAUD_M);
void uart_enable();
void uart_disable();
inline void uart_wait_for_tx_idle();

void uart_put_char(char c);
void uart_print(char *str);
void uart_println(char *str);

#endif /* __uart_h_included__ */
