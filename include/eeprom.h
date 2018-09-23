// Name: eeprom.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __eeprom_h_included__
#define __eeprom_h_included__

void eeprom_write_byte(uint16_t addr, uint8_t value);
uint8_t eeprom_read_byte(uint16_t addr);

#endif /* __eeprom_h_included__ */
