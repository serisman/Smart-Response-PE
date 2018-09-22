// Name: delay.h
// Project: Smart-Response-PE/include
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __delay_h_included__
#define __delay_h_included__

#include <stdint.h>

// For when the system clock is 16 MHz (only good for up to 255 usec)
inline void delay_us_16mhz(uint8_t usec) {
	while (usec--) {
		__asm
		xch a,r4
		xch a,r4
		__endasm;
	}
}

/*
	mov	r7,usec			2,4
loop:								16 cycles
	mov	ar6,r7			2,3
	dec	r7					1,2
	mov	a,r6				1,1
	jz	done				1,3
	xch a,r4				1,2
	xch a,r4				1,2
	sjmp	loop			2,3
done:
	11 bytes total
*/

// For when the system clock is 32 MHz (only good for up to 127 usec)
inline void delay_us_32mhz(uint8_t usec) {
	delay_us_16mhz(usec*2);
}

// For when the system clock is 32 MHz (good for up to ~65 msec)
inline void long_delay_us_32mhz(uint16_t usec) {
	while (usec--) {
		__asm
		xch a,r4
		xch a,r4
		xch a,r4
		xch a,r4
		nop
		nop
		__endasm;
	}
}

/*
	mov	r6,LO_BYTE(usec)			2,4
	mov	r7,HI_BYTE(usec)			2,4
loop:													32 cycles
	mov	ar4,r6								2,3
	mov	ar5,r7								2,3
	dec	r6										1,2
	cjne	r6,#0xff,00148$			3,4
	dec	r7										1,2
00148$:
	mov	a,r4									1,1
	orl	a,r5									1,1
	jz	done									1,3
	xch a,r4									1,2
	xch a,r4									1,2
	xch a,r4									1,2
	xch a,r4									1,2
	nop												1,1
	nop												1,1
	sjmp	loop								2,3
done:
	24 bytes total
*/

#endif /* __delay_h_included__ */
