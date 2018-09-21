// Name: display.h
// Project: Smart-Response-PE/include
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __display_h_included__
#define __display_h_included__

#include <stdint.h>
#include "uc1701.h"

#define COLOR_BLACK					0
#define COLOR_WHITE					1

#define NUM_SCREEN_ROWS			(SCREEN_HEIGHT/8)

#define CHAR_WIDTH					6
#define CHAR_HEIGHT					8

extern uint8_t __xdata _screen[NUM_SCREEN_ROWS * SCREEN_WIDTH];
extern uint8_t display_each_frame_millis;
extern uint32_t _prev_frame_ms;

extern uint8_t display_cursor_x;
extern uint8_t display_cursor_y;

inline void display_init();
inline void display_paint();
uint8_t __xdata *display_get_screen_ptr(uint8_t x, uint8_t y);
void display_draw_pixel(uint8_t x, uint8_t y, uint8_t color);
void display_draw_bitmap(int8_t x, int8_t y, uint8_t *bitmap, uint8_t width, uint8_t height, uint8_t color);

void display_set_frame_rate(uint8_t rate);
uint8_t display_next_frame();

void display_set_cursor(uint8_t x, uint8_t y);
void display_draw_char(char c);
void display_print(char *str);

#endif /* __display_h_included__ */
