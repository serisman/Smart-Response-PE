// Name: num-to-string.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-18
// License: MIT

#ifndef __num_to_string_h_included__
#define __num_to_string_h_included__

void u_to_str(uint8_t u, char * str_buf);
void u_to_bin_str(uint8_t u, uint8_t digits, char * str_buf);

void ul_to_str(uint32_t ul, char * str_buf);

#endif /* __num_to_string_h_included__ */
