// Name: uart/uart_println.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "uart.h"

void uart_println(char *str) {
	uart_print(str);
	uart_print("\r\n");
}
