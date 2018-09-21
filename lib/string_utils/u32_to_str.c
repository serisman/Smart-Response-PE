// Name: string_utils/u32_to_str.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "string_utils.h"

void u32_to_str(uint32_t ul, char __xdata *str_buf) {
	uint8_t pos = 0;
	do {
		str_buf[pos++] = '0' + (ul % 10);
		ul /= 10;
	} while (ul != 0);
	reverse_str(str_buf, pos);
}
