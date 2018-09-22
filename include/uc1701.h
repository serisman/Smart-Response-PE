// Name: uc1701.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __uc1701_h_included__
#define __uc1701_h_included__

#include <stdint.h>
#include <stdbool.h>

#define SCREEN_WIDTH				128
#define SCREEN_HEIGHT				48

// Special 'Icons'
//	 page: 8
//		col: 128
//			bit-0: rf sig 0
//	page: 6
//		col: 128
//			bit-0: rf sig 1
//			bit-1: low battery
//			bit-2: right digit bottom
//			bit-3: left digit bottom
//			bit-4: 1 digit
//			bit-5: pound
//		col: 129
//			bit-0: rf sig 2
//			bit-1: question mark
//			bit-2: right digit lower right
//			bit-3: right digit lower left
//			bit-4: left digit lower right
//			bit-5: left digit lower left
//		col: 130
//			bit-0: rf sig 3
//			bit-1: network
//			bit-2: right digit middle
//			bit-3: right digit upper left
//			bit-4: left digit middle
//			bit-5: left digit upper left
//		col: 131
//			bit-0: rf sig 4
//			bit-1: person
//			bit-2: right digit upper right
//			bit-3: right digit top
//			bit-4: left digit upper right
//			bit-5: left digit top

void uc1701_init();
void uc1701_clear();
void uc1701_invert(bool invert);
void uc1701_paint(uint8_t __xdata *screen, bool clear);

#endif /* __uc1701_h_included__ */
