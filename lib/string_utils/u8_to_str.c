// Name: string_utils/u8_to_str.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "string_utils.h"

void u8_to_str(char __xdata *str_buf, uint8_t u) {
  uint8_t pos = 0;
  do {
    str_buf[pos++] = '0' + (u % 10);
    u /= 10;
  } while (u != 0);
  reverse_str(str_buf, pos);
}
