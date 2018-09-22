// Name: util.h
// Project: Smart-Response-PE/include
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __util_h_included__
#define __util_h_included__

#include <stdint.h>

#define HIGH                          1
#define LOW                           0

#define ARG1(a,...)										a
#define ARG2(a,b,...)									b

// ----------------------------------------------------------------------

#define BV(bit)											  (uint8_t)(1<<(bit))

#define BV1(b1)											  (BV(b1))
#define BV2(b1,b2)										(BV(b1)|BV(b2))
#define BV3(b1,b2,b3)							  	(BV(b1)|BV(b2)|BV(b3))
#define BV4(b1,b2,b3,b4)							(BV(b1)|BV(b2)|BV(b3)|BV(b4))
#define BV5(b1,b2,b3,b4,b5)					  (BV(b1)|BV(b2)|BV(b3)|BV(b4)|BV(b5))
#define BV6(b1,b2,b3,b4,b5,b6)				(BV(b1)|BV(b2)|BV(b3)|BV(b4)|BV(b5)|BV(b6))
#define BV7(b1,b2,b3,b4,b5,b6,b7)		  (BV(b1)|BV(b2)|BV(b3)|BV(b4)|BV(b5)|BV(b6)|BV(b7))
#define BV8(b1,b2,b3,b4,b5,b6,b7,b8)	(BV(b1)|BV(b2)|BV(b3)|BV(b4)|BV(b5)|BV(b6)|BV(b7)|BV(b8))

#define setBit(byte,bit)							byte |= BV(bit)
#define clearBit(byte,bit)						byte &= ~(BV(bit))
#define setBits(byte,mask)						byte |= mask
#define clearBits(byte,mask)					byte &= ~(mask)

#define isBitSet(byte,bit)						byte & BV(bit)
#define isBitClear(byte,bit)					!(byte & BV(bit))
#define areBitsSet(byte,mask)			  	byte & mask
#define areBitsClear(byte,mask)		  	!(byte & mask)

// ----------------------------------------------------------------------

#define PORT_EX(port,pin)             port
#define PORT_DIR_EX(port,pin)         port ## DIR
#define PORT_SEL_EX(port,pin)         port ## SEL
#define PIN_EX(port,pin)              port ## _ ## pin

#define setPinOutput_EX(port,pin)			setBit(PORT_DIR_EX(port,pin),pin)
#define setPinInput_EX(port,pin)			clearBit(PORT_DIR_EX(port,pin),pin)

#define setPin_EX(port,pin)	  		  	PIN_EX(port,pin) = HIGH
#define clearPin_EX(port,pin)		    	PIN_EX(port,pin) = LOW
#define writePin_EX(port,pin,value) 	PIN_EX(port,pin) = value

#define isPinHigh_EX(port,pin)        PIN_EX(port,pin)
#define isPinLow_EX(port,pin)         !(PIN_EX(port,pin))

// ----------------------------------------------------------------------

#define PORT(pinspec)                	PORT_EX(pinspec)
#define PORT_DIR(pinspec)            	PORT_DIR_EX(pinspec)
#define PORT_SEL(pinspec)            	PORT_SEL_EX(pinspec)
#define PIN(pinspec)                 	PIN_EX(pinspec)

#define setPinOutput(pinspec)         setBit(PORT_DIR_EX(pinspec),ARG2(pinspec))
#define setPinInput(pinspec)          clearBit(PORT_DIR_EX(pinspec),ARG2(pinspec))

#define setPin(pinspec)	  		  	    PIN_EX(pinspec) = HIGH
#define clearPin(pinspec)		     	    PIN_EX(pinspec) = LOW
#define writePin(pinspec,value)       PIN_EX(pinspec) = value

#define isPinHigh(pinspec)            PIN_EX(pinspec)
#define isPinLow(pinspec)             !(PIN_EX(pinspec))

// ----------------------------------------------------------------------

extern const uint8_t __code util_bit_to_mask[];

uint8_t util_mask_to_bit(uint8_t mask);

#endif /* __util_h_included__ */
