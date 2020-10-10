// Name: util/util_mask_to_bit.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "util.h"

uint8_t util_mask_to_bit(uint8_t mask) {
  uint8_t bit = 8;
  while (bit--) {
    if (isBitSet(mask,7))
      return bit;
    mask <<= 1;
  }
  return 0;		// TODO... what should we actually do if the mask is empty?
}
