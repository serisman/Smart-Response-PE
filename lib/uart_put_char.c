// Name: uart_put_char.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "uart.h"

void uart_put_char(char c) {
	uart_wait_for_tx_idle();
	UxDBUF = c;
}
