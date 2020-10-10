// Name: string_utils/reverse_str.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "string_utils.h"

void reverse_str(char __xdata *str_buf, uint8_t len) {
  char tmp;
  char __xdata *left = str_buf;
  char __xdata *right = str_buf + len;

  *right-- = 0;
  len /= (uint8_t)2;
  while (len--) {
    tmp = *left;
    *left++ = *right;
    *right-- = tmp;
  }
}
