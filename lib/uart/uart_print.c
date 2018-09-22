// Name: uart/uart_print.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "uart.h"

void uart_print(char *str) {
	while (*str) {
		uart_wait_for_tx_idle();
		UxDBUF = *str++;
	}
}
