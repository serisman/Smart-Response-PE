// Name: i2c_master.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT
// Source: Based off of pseudo-code from: http://en.wikipedia.org/wiki/I%C2%B2C
// https://www.i2c-bus.org/

#include "hal.h"
#include "util.h"
#include "delay.h"
#include "i2c_master.h"

#define PIN_I2C_SCL         P0,6
#define PIN_I2C_SDA         P0,7

bool started = 0;

void i2c_master_half_delay() {
  _delay_us(1000.0 / (float)I2C_FREQ_KHZ / 2.0);
}

void i2c_master_start() {
  if (started) {
    setPinInput(PIN_I2C_SDA);
    i2c_master_half_delay();

    setPinInput(PIN_I2C_SCL);
    while (isPinLow(PIN_I2C_SCL)) {
      ; // add timeout?
    }
    i2c_master_half_delay();
  }

  setPinInput(PIN_I2C_SDA);
//	if (isPinLow(PIN_I2C_SDA)) {
//		; // Arbitration lost!
//	}

  setPinOutput(PIN_I2C_SDA);
  clearPin(PIN_I2C_SDA);
  i2c_master_half_delay();

  setPinOutput(PIN_I2C_SCL);
  clearPin(PIN_I2C_SCL);

  started = true;
}

void i2c_master_stop() {
  setPinOutput(PIN_I2C_SDA);
  clearPin(PIN_I2C_SDA);
  i2c_master_half_delay();

  setPinInput(PIN_I2C_SCL);
  while (isPinLow(PIN_I2C_SCL)) {
    ; // add timeout?
  }
  i2c_master_half_delay();

  setPinInput(PIN_I2C_SDA);
  i2c_master_half_delay();
//	if (isPinLow(PIN_I2C_SDA)) {
//		; // Arbitration lost!
//	}

  started = false;
}

void i2c_master_write_bit(uint8_t bit) {
  if (bit) {
    setPinInput(PIN_I2C_SDA);
  } else {
    setPinOutput(PIN_I2C_SDA);
    clearPin(PIN_I2C_SDA);
  }
  i2c_master_half_delay();

  setPinInput(PIN_I2C_SCL);
  while (isPinLow(PIN_I2C_SCL)) {
    ; // add timeout?
  }
  i2c_master_half_delay();

//	if (bit && isPinLow(PIN_I2C_SDA)) {
//		; // Arbitration lost!
//	}

  setPinOutput(PIN_I2C_SCL);
  clearPin(PIN_I2C_SCL);
}

uint8_t i2c_master_read_bit() {
  uint8_t bit;

  setPinInput(PIN_I2C_SDA);
  i2c_master_half_delay();

  setPinInput(PIN_I2C_SCL);
  while (isPinLow(PIN_I2C_SCL)) {
    ; // add timeout?
  }
  i2c_master_half_delay();
  bit = (isPinHigh(PIN_I2C_SDA));

  setPinOutput(PIN_I2C_SCL);
  clearPin(PIN_I2C_SCL);

  return bit;
}

uint8_t i2c_master_write_byte(uint8_t byte) {
  uint8_t nack;

  for (uint8_t i=8; i>0; i--) {
    i2c_master_write_bit(isBitSet(byte,7));
    byte <<= 1;
  }
  nack = i2c_master_read_bit();

  return nack;
}

uint8_t i2c_master_read_byte(uint8_t nack) {
  uint8_t byte = 0;

  for (uint8_t i=8; i>0; i--) {
    byte <<= 1;
    byte |= i2c_master_read_bit();
  }
  i2c_master_write_bit(nack);

  return byte;
}
