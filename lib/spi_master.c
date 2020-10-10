// Name: spi_master.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2020-10-10
// License: MIT

#include "hal.h"
#include "util.h"

#define PIN_SPI_SCK					P0,4
#define PIN_SPI_MOSI				P0,5

void spi_init() {
  setPinOutput(PIN_SPI_SCK);
  setPinOutput(PIN_SPI_MOSI);

  clearPin(PIN_SPI_SCK);
  clearPin(PIN_SPI_MOSI);
}

void spi_write(uint8_t data) {
//  uint8_t i = 8;
//	do {
//		writePin(PIN_SPI_MOSI, isBitSet(data,7));
//		data <<= 1;
//		// NOTE: No additional delays needed.
//		// Even at 32 MHz, each cpu cycle takes 31.25 ns., and clr/setb take 4 cycles each,
//    // meaning we are already well above the min of 50 ns. low/high clk pulse width.
//		setPin(PIN_SPI_SCK);
//		clearPin(PIN_SPI_SCK);
//	} while (--i);
  data;
__asm
  mov   a, dpl
  mov   r7, #0x08
00001$:
  rlc   a
  mov   _P0_5, c
  setb  _P0_4
  clr   _P0_4
  djnz  r7, 00001$
__endasm;
}

void spi_write_xdata_buf(uint8_t __xdata *xdata, uint8_t length, bool clear) {
//	do {
//    spi_write(*xdata);
//		if (clear)
//			*xdata = 0;
//		xdata++;
//	} while (--length);
  xdata;
  length;
  clear;
__asm
  mov   r7, _spi_write_xdata_buf_PARM_2
00001$:
	movx  a, @dptr

  mov r6, #0x08
00002$:
	rlc   a
	mov   _P0_5, c
	setb  _P0_4
	clr   _P0_4
	djnz  r6, 00002$

	mov   a, _spi_write_xdata_buf_PARM_3
	jz    00003$
	clr   a
	movx  @dptr, a

00003$:
  inc   dptr
  djnz  r7, 00001$
__endasm;
}
