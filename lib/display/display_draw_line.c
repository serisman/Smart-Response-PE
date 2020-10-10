// Name: display/display_draw_line.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "display.h"

// TODO... optimize this

int abs(int j) {
	return (j < 0) ? -j : j;
}

#define SWAP(x,y) do {	\
		tmp = x;	\
		x = y;	\
		y = tmp;	\
	} while(0)

void display_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
	int16_t tmp, dx, dy, err;
  int8_t ystep;

  // bresenham's algorithm - thx wikpedia
  bool steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    SWAP(x0, y0);
    SWAP(x1, y1);
  }

  if (x0 > x1) {
    SWAP(x0, x1);
    SWAP(y0, y1);
  }

  dx = x1 - x0;
  dy = abs(y1 - y0);

  err = dx / 2;

  if (y0 < y1)
    ystep = 1;
  else
    ystep = -1;

  for (; x0 <= x1; x0++) {
    if (steep)
      display_draw_pixel(y0, x0);
    else
      display_draw_pixel(x0, y0);

    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}
