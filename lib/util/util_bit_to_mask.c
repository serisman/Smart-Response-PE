// Name: util/util_bit_to_mask.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "util.h"

// It is faster and produces less code to look this up rather than calculate it in runtime!
const uint8_t __code util_bit_to_mask[8] = { BV(0), BV(1), BV(2), BV(3), BV(4), BV(5), BV(6), BV(7) };
