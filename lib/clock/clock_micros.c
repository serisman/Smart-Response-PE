// Name: clock/clock_micros.c
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#include "clock.h"

#ifdef CLOCK_MICROS

// NOTE: resolution is 4uS (overflows in approx 70 minutes?)
uint32_t clock_micros() {
	uint32_t micros;

	ATOMIC_BEGIN;
		micros = _clock_ticks;
		micros += T4CNT;

		if (T4OVFIF) {
			micros += TICKS_PER_MS;
		}
		micros *= uS_PER_TICK;
	ATOMIC_END;

	return micros;
}

#endif
