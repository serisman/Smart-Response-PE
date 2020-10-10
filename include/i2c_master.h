// Name: i2c_master.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __i2c_master_h_included__
#define __i2c_master_h_included__

#if !defined(I2C_FREQ_KHZ)
  #define I2C_FREQ_KHZ			100
#endif

void i2c_master_start();
void i2c_master_stop();

void i2c_master_write_bit(uint8_t bit);
uint8_t i2c_master_read_bit();

uint8_t i2c_master_write_byte(uint8_t byte);
uint8_t i2c_master_read_byte(uint8_t nack);

#endif /* __i2c_master_h_included__ */
