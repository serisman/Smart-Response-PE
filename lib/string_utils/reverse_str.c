// Name: string_utils/reverse_str.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "string_utils.h"

void reverse_str(char *str_buf, uint8_t len) {
	uint8_t tmp;
	uint8_t *ptr1 = str_buf;
	uint8_t *ptr2 = str_buf + len;

	*ptr2 = 0;
	ptr2--;
	len /= (uint8_t)2;
	while (len > 0) {
		tmp = *ptr1;
		*ptr1 = *ptr2;
		*ptr2 = tmp;
		ptr1++;
		ptr2--;
		len--;
	}
}
