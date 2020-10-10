// Name: display.h
// Project: Smart-Response-PE/include
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __display_h_included__
#define __display_h_included__

#include <stdint.h>
#include <stdbool.h>
#include "uc1701.h"

#define COLOR_BLACK					0
#define COLOR_WHITE					1

#define NUM_SCREEN_ROWS			(SCREEN_HEIGHT/8)

#define CHAR_WIDTH					6
#define CHAR_HEIGHT					8

extern uint8_t __xdata screen[NUM_SCREEN_ROWS * SCREEN_WIDTH];
extern uint8_t display_color;

extern uint8_t display_each_frame_millis;
extern uint32_t display_prev_frame_ms;
extern uint8_t display_frame_count;

extern uint8_t display_cursor_x;
extern uint8_t display_cursor_y;

inline void display_init()              { uc1701_init(); }
inline void display_invert(bool invert) { uc1701_invert(invert); }
inline void display_paint(bool clear)   { uc1701_paint(screen, clear); }
uint8_t __xdata *display_get_screen_ptr(uint8_t x, uint8_t y);

inline void display_set_color(uint8_t color);
void display_draw_pixel(uint8_t x, uint8_t y);
void display_draw_bitmap(const uint8_t __code *bitmap, int8_t x, int8_t y, uint8_t width, uint8_t height);
void display_draw_circle(uint8_t x0, uint8_t y0, uint8_t r);
void display_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void display_draw_fast_vline(uint8_t x, uint8_t y, uint8_t height);
void display_draw_fast_hline(uint8_t x, uint8_t y, uint8_t width);
void display_draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void display_fill_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height);

void display_set_frame_rate(uint8_t rate);
bool display_every_x_frames(uint8_t frames);
bool display_next_frame();

inline void display_set_cursor(uint8_t x, uint8_t y);
void display_draw_char(char c);
void display_print(char *str);

#endif /* __display_h_included__ */
