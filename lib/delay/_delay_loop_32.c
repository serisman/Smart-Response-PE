#include "delay.h"

// 27 cycles per loop, 35 cycles overhead
void _delay_loop_32(uint32_t ctr) {
//	while (--ctr);
  ctr;
__asm
// mov  dptr, #0x????     ; [3]
// mov  b, #0x??          ; [3]
// mov  a, #0x??          ; [3]
// lcall __delay_loop_32  ; [6]
  mov   r4, dpl           ; [4]
  mov   r5, dph           ; [4]
  mov	  r6, b             ; [4]
  mov	  r7, a             ; [4]
_delay_loop_32_lp:
  clr   c                     ; [1]

  mov   a, r4                 ; [1]
  subb  a, #1                 ; [2]
  mov   r4, a                 ; [2]

  mov   a, r5                 ; [1]
  subb  a, #0                 ; [2]
  mov   r5, a                 ; [2]

  mov   a, r6                 ; [1]
  subb  a, #0                 ; [2]
  mov   r6, a                 ; [2]

  mov   a, r7                 ; [1]
  subb  a, #0                 ; [2]
  mov   r7, a                 ; [2]

  orl	  a, r6                 ; [1]
  orl	  a, r5                 ; [1]
  orl	  a, r4                 ; [1]
  jnz	  _delay_loop_32_lp     ; [3]
// ret	                  ; [4]
__endasm;
}
