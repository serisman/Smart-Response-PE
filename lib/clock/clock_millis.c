// Name: clock/clock_millis.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "util.h"
#include "clock.h"

uint32_t clock_millis() {
	uint32_t millis;

	ATOMIC_BEGIN;
		millis = _clock_millis;
	ATOMIC_END;

	return millis;
}
