// Name: uc1701.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __uc1701_h_included__
#define __uc1701_h_included__

#include <stdint.h>

#define SCREEN_WIDTH				128
#define SCREEN_HEIGHT				48

void uc1701_init();
void uc1701_clear();
void uc1701_paint(uint8_t __xdata *screen);

#endif /* __uc1701_h_included__ */
