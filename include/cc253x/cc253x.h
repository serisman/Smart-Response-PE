// Name: cc253x/cc253x.h
// Project: Smart-Response-PE/include
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-10-03
// License: MIT

#ifndef __cc253x_h_included__
#define __cc253x_h_included__

#define CC253x                  1

// https://github.com/contiki-os/contiki/tree/master/cpu/cc253x
#include "mcs51/cc2530.h"				// https://github.com/darconeous/sdcc/blob/master/device/include/mcs51/cc2530.h

#define ENABLE_INTERRUPTS 			EA=1;
#define DISABLE_INTERRUPTS 			EA=0;

//#define ATOMIC_BEGIN						// TODO: save IEN0?, then EA=0
//#define ATOMIC_END							// TODO: restore IEN0?
#define ATOMIC_BEGIN						DISABLE_INTERRUPTS
#define ATOMIC_END							ENABLE_INTERRUPTS

// SLEEPCMD (0xBE)
#define SLEEPCMD_OSC32K_CALDIS	7
#define SLEEPCMD_MODE_1					1
#define SLEEPCMD_MODE_0					0

// SLEEPSTA (0x9D)
#define SLEEPSTA_OSC32K_CALDIS	7
#define SLEEPSTA_RST_1					4
#define SLEEPSTA_RST_0					3
#define SLEEPSTA_CLK32K					0

// PCON (0x87)
#define PCON_IDLE								0

// CLKCONCMD (0xC6)
// CLKCONSTA (0x9E)
#define CLKCON_OSC32K				    7
#define CLKCON_OSC							6
#define CLKCON_TICKSPD_2				5
#define CLKCON_TICKSPD_1				4
#define CLKCON_TICKSPD_0				3
#define CLKCON_CLKSPD_2					2
#define CLKCON_CLKSPD_1					1
#define CLKCON_CLKSPD_0					0

// PERCFG (0xF1)
#define PERCFG_T1CFG						6
#define PERCFG_T3CFG						5
#define PERCFG_T4CFG						4
#define PERCFG_U1CFG						1
#define PERCFG_U0CFG						0

// T4CTL (0xEB)
#define TxCTL_DIV_2							7
#define TxCTL_DIV_1							6
#define TxCTL_DIV_0							5
#define TxCTL_START							4
#define TxCTL_OVFIM							3
#define TxCTL_CLR								2
#define TxCTL_MODE_1						1
#define TxCTL_MODE_0						0

// U0CSR (0x86), U1CSR (0xF8)
#define UxCSR_MODE							7
#define UxCSR_RE								6
#define UxCSR_SLAVE							5
#define UxCSR_FE								4
#define UxCSR_ERR								3
#define UxCSR_RX_BYTE						2
#define UxCSR_TX_BYTE						1
#define UxCSR_ACTIVE						0

// U0UCR (0xC4), U1UCR (0xFB)
#define UxUCR_FLUSH							7
#define UxUCR_FLOW							6
#define UxUCR_D9								5
#define UxUCR_BIT9							4
#define UxUCR_PARITY						3
#define UxUCR_SPB								2
#define UxUCR_STOP							1
#define UxUCR_START							0

// U0GCR (0xC5), U1GCR (0xFC)
#define UxUCR_CPOL							7
#define UxUCR_CPHA							6
#define UxUCR_ORDER							5
#define UxUCR_BAUD_E_4					4
#define UxUCR_BAUD_E_3					3
#define UxUCR_BAUD_E_2					2
#define UxUCR_BAUD_E_1					1
#define UxUCR_BAUD_E_0					0

#include "oscillator.h"

#endif /* __cc253x_h_included__ */
