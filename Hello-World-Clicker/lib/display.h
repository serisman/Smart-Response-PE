// Name: display.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-18
// License: MIT

#ifndef __display_h_included__
#define __display_h_included__

#define COLOR_BLACK					0
#define COLOR_WHITE					1

#define NUM_SCREEN_ROWS			(SCREEN_HEIGHT/8)

#define CHAR_WIDTH					6
#define CHAR_HEIGHT					8

void display_paint();
void display_draw_pixel(uint8_t x, uint8_t y, uint8_t color);
void display_draw_bitmap(int8_t x, int8_t y, uint8_t *bitmap, uint8_t width, uint8_t height, uint8_t color);

void display_set_frame_rate(uint8_t rate);
uint8_t display_next_frame();

void display_set_cursor(uint8_t x, uint8_t y);
void display_draw_char(char c);
void display_printf(char *str);

#endif /* __display_h_included__ */
