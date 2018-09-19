// Name: util.h
// Project: Smart-Response-PE/lib
// Author: Stephen Erisman
// Creation Date: 2018-09-17
// License: MIT

#ifndef __util_h_included__
#define __util_h_included__

#define _BV(bit)											(1<<(bit))

#define _BV1(b1)											(_BV(b1))
#define _BV2(b1,b2)										(_BV(b1)|_BV(b2))
#define _BV3(b1,b2,b3)								(_BV(b1)|_BV(b2)|_BV(b3))
#define _BV4(b1,b2,b3,b4)							(_BV(b1)|_BV(b2)|_BV(b3)|_BV(b4))
#define _BV5(b1,b2,b3,b4,b5)					(_BV(b1)|_BV(b2)|_BV(b3)|_BV(b4)|_BV(b5))
#define _BV6(b1,b2,b3,b4,b5,b6)				(_BV(b1)|_BV(b2)|_BV(b3)|_BV(b4)|_BV(b5)|_BV(b6))
#define _BV7(b1,b2,b3,b4,b5,b6,b7)		(_BV(b1)|_BV(b2)|_BV(b3)|_BV(b4)|_BV(b5)|_BV(b6)|_BV(b7))
#define _BV8(b1,b2,b3,b4,b5,b6,b7,b8)	(_BV(b1)|_BV(b2)|_BV(b3)|_BV(b4)|_BV(b5)|_BV(b6)|_BV(b7)|_BV(b8))

#define _setBit(byte,bit)							byte |= _BV(bit)
#define _clearBit(byte,bit)						byte &= ~(_BV(bit))
#define _setBits(byte,mask)						byte |= mask
#define _clearBits(byte,mask)					byte &= ~(mask)

#define _isBitSet(byte,bit)						byte & _BV(bit)
#define _isBitClear(byte,bit)					!(byte & _BV(bit))
#define _areBitsSet(byte,mask)				byte & mask
#define _areBitsClear(byte,mask)			!(byte & mask)

#endif /* __util_h_included__ */
