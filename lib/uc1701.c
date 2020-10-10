// Name: uc1701.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "hal.h"
#include "util.h"
#include "delay.h"
#include "spi_master.h"
#include "uc1701.h"

#define PIN_LCD_RST					P0,2
#define PIN_LCD_DC					P0,3

inline void _uc1701_set_cmd_mode() { clearPin(PIN_LCD_DC); }
inline void _uc1701_set_data_mode() {	setPin(PIN_LCD_DC); }

void _uc1701_cmd(uint8_t cmd);
void _uc1701_switch_page(uint8_t page);

/*
http://www.hpinfotech.ro/UC1701.pdf

UC1701 Commands (seems to match the ST7565 as well)

0x00-0x0F					Set Column Address LSB: CA[3:0], range is 0-131
0x10-0x1F					Set Column Address MSB: CA[7:4], range is 0-131
0x28-0x2F					Set Power Control: PC[2:0], PC[2]=Boost, PC[1]=Voltage Regular, PC[0]=Voltage Follower
0x40-0x7F					Set Scroll Line: SL[5:0], range is 0-63 (does not affect icons)
0xB0-0xBF					Set Page Address: PA[3:0], range is 0-8 (page 8 is for icons)
0x20-0x27					Set Resistor Ratio (contrast): PC[5:3], range is 0-7 (default is 4)
0x81 + 0x00-0x3F	Set Electronic Volume (contrast): PM[5:0], range is 0-63 (default is 32)
0xA4,0xA5					Set All-Pixel-On: DC[1]
0xA6,0xA7					Set Inverse Display: DC[0]
0xAE,0xAF					Set Display Enable, DC[2]
0xA0,0xA1					Set SEG Direction, MX
0xC0,0xC8					Set COM Direction: MY
0xE2							System Reset
0xE3							NOP
0xA2,0xA3					Set LCD Bias Ratio: BR
0xE0,0xEE					Set/Reset Cursor Update Mode: AC3,CA/CR
0xAC,0xAD + 0xXX	Set Static Indicator (NOP)
0xF8 + 0x00-0x03	Set Booster Ratio (NOP)
0xFA + byte				Set Adv. Program Control 0: byte[4]=1, TC=byte[7], WA[1:0] = byte[1:0]
*/

uint8_t __code _uc1701_init[] = {
  0xE2,								// System Reset
  0xA0 | BV(0),		  	// Set SEG Direction: Mirror X
  0xC0 | BV(3),			  // Set COM Direction: Mirror Y
  0xA2, 							// Set LCD Bias Ratio: 1/9
  0x28 | BV3(2,1,0),	// Set Power Control: Boost ON, Voltage Regular On, Voltage Follower On
  //0x85,							// Not sure why, but real Smart Response PE units send this (according to logic analyzer).
  0x20 | 5,						// Set Resistor Ratio (contrast) (0-7): 5
  0x81, 34,						// Set Electronic Volume (contrast) (0-63): 34
  0xA6,								// Set Inverse Display: OFF
  0x40 | 48,					// Set Scroll Line: 48
  0xA4,								// Set All-Pixel-On: OFF
  0xAE | BV(0)				// Set Display Enable: ON
};

void uc1701_init() {
  spi_init();

  // Set RST, DC as outputs
  setPinOutput(PIN_LCD_RST);
  setPinOutput(PIN_LCD_DC);

  // Reset the LCD
  clearPin(PIN_LCD_RST);
  delay_us_32mhz(1);
  setPin(PIN_LCD_RST);
  delay_us_32mhz(5);

  // Initialize the LCD
  _uc1701_set_cmd_mode();
  for (uint8_t i=0; i<sizeof(_uc1701_init); i++) {
    spi_write(_uc1701_init[i]);
  }
  _uc1701_set_data_mode();

  uc1701_clear();
}

void uc1701_clear() {
  for (uint8_t page=0; page<=8; page++) {
    _uc1701_switch_page(page);
    for (uint8_t column=132; column>0; column--) {
      spi_write(0x00);
    }
  }
}

void uc1701_paint(uint8_t __xdata *screen, bool clear) {
	for (uint8_t page = 0; page < (SCREEN_HEIGHT/8u); page++) {
		_uc1701_switch_page(page);
		spi_write_xdata_buf(screen, SCREEN_WIDTH, clear);
		screen += SCREEN_WIDTH;
	}
}

void uc1701_invert(bool invert) {
  _uc1701_cmd(0xA6 | invert);       // Set Inverse Display: OFF/ON
}

// private methods --------------------------------------------------------

void _uc1701_cmd(uint8_t cmd) {
  _uc1701_set_cmd_mode();
  spi_write(cmd);
  _uc1701_set_data_mode();
}

void _uc1701_switch_page(uint8_t page) {
  _uc1701_set_cmd_mode();
  spi_write(0xB0 | page);						// Set Page Address
  spi_write(0x10 | (0x00 >> 4));    // Set Column Address MSB (column 0)
  spi_write(0x00 & 0x0F);           // Set Column Address LSB (column 0)
  _uc1701_set_data_mode();
}
