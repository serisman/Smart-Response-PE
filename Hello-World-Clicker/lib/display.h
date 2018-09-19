// Name: display.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-18
// License: MIT

#ifndef __display_h_included__
#define __display_h_included__

#define NUM_ROWS				(SCREEN_HEIGHT/8)
#define NUM_COLS				(SCREEN_WIDTH/6)
#define CHAR_WIDTH			6

void display_set_cursor(uint8_t row, uint8_t col);
void display_draw_char(char c);
void display_printf(char * str);

#endif /* __display_h_included__ */
