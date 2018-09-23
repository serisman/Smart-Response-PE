// Name: main.c
// Project: Smart-Response-PE/examples/hello-world-receiver
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-14
// License: MIT

#include "cc2430.h"
#include "clock.h"
#include "uart.h"
#include "string_utils.h"

#define RED_LED				  P0,0
#define GREEN_LED			  P0,1
#define TX_LED				  P0,6
#define RX_LED				  P0,7

char __xdata str_buf[10];

inline void setup() {
  setPinOutput(RED_LED);    clearPin(RED_LED);
  setPinOutput(GREEN_LED);  clearPin(GREEN_LED);
  setPinOutput(TX_LED);     clearPin(TX_LED);
  setPinOutput(RX_LED);     clearPin(RX_LED);

  uart_init();
  uart_println("Hello World!");
}

inline void loop() {
  uint32_t millis = clock_millis();
  u32_to_str(millis, str_buf);
  uart_print("millis: "); uart_println(str_buf);

  setPin(RED_LED);
  clearPin(GREEN_LED);
  setPin(TX_LED);
  clearPin(RX_LED);
  clock_delay_ms(250);

  clearPin(TX_LED);
  setPin(RX_LED);
  clock_delay_ms(250);

  clearPin(RED_LED);
  setPin(GREEN_LED);
  setPin(TX_LED);
  clearPin(RX_LED);
  clock_delay_ms(250);

  clearPin(TX_LED);
  setPin(RX_LED);
  clock_delay_ms(250);
}

void main() {
  oscillator_32mhz();
  clock_init();
  ENABLE_INTERRUPTS;
  setup();

  while(1) {
    loop();
  }
}
