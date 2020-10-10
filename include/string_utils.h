// Name: string_utils.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __string_utils_h_included__
#define __string_utils_h_included__

#include <stdint.h>

void reverse_str(char __xdata *str_buf, uint8_t len);
void clear_str(char __xdata *str_buf, uint8_t len);
void str_to_str(char *str, char __xdata *str_buf);

void u8_to_str(char __xdata * str_buf, uint8_t u);
void u8_to_bin_str(char __xdata * str_buf, uint8_t u, uint8_t digits);

void u32_to_str(char __xdata * str_buf, uint32_t ul);

#endif /* __string_utils_h_included__ */
