// Name: uart/uart.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "util.h"
#include "uart.h"

void uart_init() {

#if UART_USE_ALT2 == 1
  setBit(PERCFG,PERCFG_UxCFG);	        // Enable UART Alternate 2 I/O location
#endif

  uart_enable();

  UxUCR = BV2(UxUCR_FLUSH,UxUCR_STOP);	// 8n1, no flow control, high stop bit, and FLUSH any activity

  // Default to 115200 baud
  uart_set_baud(oscillator_is_32mhz() ? 11 : 12, 216); // 11 for 32 MHz, 12 for 16 MHz (TODO... add support for other clock speeds for CC253x series?)

  setBit(UxCSR,UxCSR_MODE); 		        // Switch to UART mode
}

void uart_set_baud(uint8_t BAUD_E, uint8_t BAUD_M) {
  clearBits(UxGCR,BV5(4,3,2,1,0));
  UxGCR |= (BAUD_E & 0x1F);	            // BAUD_E[4:0] (exponent)
  UxBAUD = BAUD_M;					            // BAUD_M (mantissa)
}

void uart_enable() {
  setPin(TX_PIN);                       // Set RxD high
  setPin(RX_PIN);                       // Set TxD high
  setPinOutput(TX_PIN);                 // Set TxD as output
  setPinInput(RX_PIN);                  // Set TxD as input

  setBits(PxSEL,UART_PIN_MASK);		      // Enable Peripheral functions
}

void uart_disable() {
  uart_wait_for_tx_idle();
  clearBits(PxSEL,UART_PIN_MASK);	      // Disable Peripheral functions
}

inline void uart_wait_for_tx_idle() {
  while (isBitSet(UxCSR,UxCSR_ACTIVE));	// Wait until any previously written byte has been transmitted
}
