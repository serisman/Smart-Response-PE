// Name: string_utils/u8_to_bin_str.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "string_utils.h"

void u8_to_bin_str(uint8_t u, uint8_t digits, char *str_buf) {
	uint8_t pos = 0;
	while (digits--) {
		str_buf[pos++] = (u & (1 << digits)) ? '1' : '0';
	}
	str_buf[pos] = 0;
}
