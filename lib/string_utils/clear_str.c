// Name: string_utils/clear_str.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "string_utils.h"

void clear_str(char __xdata *str_buf, uint8_t len) {
	while (len--) {
		*str_buf++ = 0;
	}
}