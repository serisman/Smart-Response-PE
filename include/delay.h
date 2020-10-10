// Name: delay.h
// Project: Smart-Response-PE/include
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __delay_h_included__
#define __delay_h_included__

#if !defined(F_CPU)
  #error "F_CPU is not defined!"
#endif

#include <stdint.h>

void _delay_loop_8(uint8_t ctr);
void _delay_loop_16(uint16_t ctr);
void _delay_loop_32(uint32_t ctr);

#if !defined(MAX)
  #define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#define NS_TO_CYCLES_16(ns)     (((ns)*16000000UL)/1000000000UL)
#define US_TO_CYCLES_16(us)     (NS_TO_CYCLES_16(us*1000ULL))

#define NS_TO_CYCLES(ns)        (((ns)*F_CPU)/1000000000UL)
#define US_TO_CYCLES(us)        (NS_TO_CYCLES(us*1000ULL))
#define MS_TO_CYCLES(ms)        (NS_TO_CYCLES(ms*1000000ULL))

#define LOOP_CTR(cycles,ovh,lp) (MAX(0,(cycles-ovh-lp)/lp)+1)
#define LOOP_CTR_8(cycles)      LOOP_CTR(cycles,17,3)
#define LOOP_CTR_16(cycles)     LOOP_CTR(cycles,21,15)
#define LOOP_CTR_32(cycles)     LOOP_CTR(cycles,35,27)

#define _delay_loop(cycles)     \
  (LOOP_CTR_8(cycles) < 256ULL) ? \
  _delay_loop_8((uint8_t)LOOP_CTR_8(cycles)) : \
  (LOOP_CTR_16(cycles) < 65536ULL) ? \
  _delay_loop_16((uint16_t)LOOP_CTR_16(cycles)) : \
  _delay_loop_32((uint32_t)LOOP_CTR_32(cycles))

#define _delay_us_16mhz(us)     _delay_loop(US_TO_CYCLES_16(us))

#define _delay_us(us)           _delay_loop(US_TO_CYCLES(us))
#define _delay_ms(ms)           _delay_loop(MS_TO_CYCLES(ms))

#endif /* __delay_h_included__ */
