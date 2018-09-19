// Name: num-to-string.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-18
// License: MIT

#include <stdint.h>

#include "num-to-string.h"

char tmp_buf[10];

void _reverse_buf(char * str_buf, uint8_t pos);

void u_to_str(uint8_t u, char * str_buf) {
	uint8_t pos = 0;
	do {
		tmp_buf[pos++] = '0' + (u % 10);
		u /= 10;
	} while (u != 0);
	_reverse_buf(str_buf, pos);
}

void u_to_bin_str(uint8_t u, uint8_t digits, char * str_buf) {
	uint8_t pos = 0;
	while (digits--) {
		str_buf[pos++] = (u & (1 << digits)) ? '1' : '0';
	}
	str_buf[pos] = 0;
}

void ul_to_str(uint32_t ul, char * str_buf) {
	uint8_t pos = 0;
	do {
		tmp_buf[pos++] = '0' + (ul % 10);
		ul /= 10;
	} while (ul != 0);
	_reverse_buf(str_buf, pos);
}

// private methods --------------------------------------------------------

void _reverse_buf(char * str_buf, uint8_t pos) {
	uint8_t pos2 = 0;
	str_buf[pos] = 0;
	while (pos-- > 0) {
		str_buf[pos2++] = tmp_buf[pos];
	}
}
