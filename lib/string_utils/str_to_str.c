// Name: string_utils/str_to_str.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "string_utils.h"

void str_to_str(char *str, char __xdata *str_buf) {
  while (*str) {
    *str_buf++ = *str++;
  }
  *str_buf = 0;
}
