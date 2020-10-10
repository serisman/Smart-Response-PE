// Name: spi_master.h
// Project: Smart-Response-PE/include
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2020-10-10
// License: MIT

#ifndef __spi_master_h_included__
#define __spi_master_h_included__

#include <stdint.h>

void spi_init();

void spi_write(uint8_t data);
void spi_write_xdata_buf(uint8_t __xdata *data, uint8_t length, bool clear);

#endif /* __spi_master_h_included__ */
