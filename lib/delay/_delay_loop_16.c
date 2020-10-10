#include "delay.h"

// 15 cycles per loop, 21 cycles overhead
void _delay_loop_16(uint16_t ctr) {
//  while (--ctr);
  ctr;
__asm
// mov  dptr, #0x????     ; [3]
// lcall __delay_loop_16  ; [6]
  mov   r6, dpl           ; [4]
  mov   r7, dph           ; [4]
_delay_loop_16_lp:
  clr   c                     ; [1]

  mov   a, r6                 ; [1]
  subb  a, #1                 ; [2]
  mov   r6, a                 ; [2]

  mov   a, r7                 ; [1]
  subb  a, #0                 ; [2]
  mov   r7, a                 ; [2]

  orl	  a, r6                 ; [1]
  jnz	  _delay_loop_16_lp     ; [3]
// ret	                  ; [4]
__endasm;
}
