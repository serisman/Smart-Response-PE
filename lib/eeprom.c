// Name: eeprom.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "util.h"
#include "i2c_master.h"
#include "eeprom.h"

#define EEPROM_I2C_ADDRESS    BV2(7,5)

#define BANK(addr)            ((addr >> 8) & BV2(1,0))

void eeprom_write_byte(uint16_t addr, uint8_t value) {
  uint8_t firstByte, nack;

  // EEPROM control code in [7:4] + 2 MSB addr bits in [2,1] + write indicator (0) in [0]
  firstByte = EEPROM_I2C_ADDRESS | (BANK(addr) << 1);

  // Write the byte
	i2c_master_start();
	i2c_master_write_byte(firstByte);
	i2c_master_write_byte(addr & 0xFF);
	i2c_master_write_byte(value);
	i2c_master_stop();

  // Wait for the write to finish
  do {
    i2c_master_start();
	  nack = i2c_master_write_byte(firstByte);
  } while (nack);
}

uint8_t eeprom_read_byte(uint16_t addr) {
  uint8_t firstByte, value;

  // EEPROM control code in [7:4] + 2 MSB addr bits in [2,1] + write indicator (0) in [0]
  firstByte = EEPROM_I2C_ADDRESS | (BANK(addr) << 1);

	i2c_master_start();
	i2c_master_write_byte(firstByte);
	i2c_master_write_byte(addr & 0xFF);
	// terminate the write... still sets the address!

	i2c_master_start();
	i2c_master_write_byte(firstByte | BV(0)); // change [0] to read indicator (1)
  value = i2c_master_read_byte(1);
  i2c_master_stop();

  return value;
}
