// Name: util.h
// Project: Smart-Response-PE/include
// Author: Stephen Erisman <github@serisman.com>
// Creation Date: 2018-09-21
// License: MIT

#ifndef __util_h_included__
#define __util_h_included__

#define BV(bit)											  (uint8_t)(1<<(bit))

#define BV1(b1)											  (uint8_t)(BV(b1))
#define BV2(b1,b2)										(uint8_t)(BV(b1)|BV(b2))
#define BV3(b1,b2,b3)							  	(uint8_t)(BV(b1)|BV(b2)|BV(b3))
#define BV4(b1,b2,b3,b4)							(uint8_t)(BV(b1)|BV(b2)|BV(b3)|BV(b4))
#define BV5(b1,b2,b3,b4,b5)					  (uint8_t)(BV(b1)|BV(b2)|BV(b3)|BV(b4)|BV(b5))
#define BV6(b1,b2,b3,b4,b5,b6)				(uint8_t)(BV(b1)|BV(b2)|BV(b3)|BV(b4)|BV(b5)|BV(b6))
#define BV7(b1,b2,b3,b4,b5,b6,b7)		  (uint8_t)(BV(b1)|BV(b2)|BV(b3)|BV(b4)|BV(b5)|BV(b6)|BV(b7))
#define BV8(b1,b2,b3,b4,b5,b6,b7,b8)	(uint8_t)(BV(b1)|BV(b2)|BV(b3)|BV(b4)|BV(b5)|BV(b6)|BV(b7)|BV(b8))

#define setBit(byte,bit)							byte |= BV(bit)
#define clearBit(byte,bit)						byte &= ~(BV(bit))
#define setBits(byte,mask)						byte |= mask
#define clearBits(byte,mask)					byte &= ~(mask)

#define isBitSet(byte,bit)						byte & BV(bit)
#define isBitClear(byte,bit)					!(byte & BV(bit))
#define areBitsSet(byte,mask)			  	byte & mask
#define areBitsClear(byte,mask)		  	!(byte & mask)

// ----------------------------------------------------------------------

#define HIGH                          1
#define LOW                           0

#define PORT(port,pin)                port
#define PORT_DIR(port,pin)            port ## DIR
#define PORT_SEL(port,pin)            port ## SEL
#define PIN(port,pin)                 port ## _ ## pin
#define PIN_NUM(port,pin)             pin

#define setPinOutput(pinspec)         setBit(PORT_DIR(pinspec),PIN_NUM(pinspec))
#define setPinInput(pinspec)          clearBit(PORT_DIR(pinspec),PIN_NUM(pinspec))

#define setPin(pinspec)	  		  	    PIN(pinspec) = HIGH
#define clearPin(pinspec)		     	    PIN(pinspec) = LOW
#define writePin(pinspec,value)       PIN(pinspec) = value

#define isPinHigh(pinspec)            PIN(pinspec)
#define isPinLow(pinspec)             !(PIN(pinspec))

#endif /* __util_h_included__ */
