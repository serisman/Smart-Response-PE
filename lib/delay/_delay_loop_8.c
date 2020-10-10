#include "delay.h"

// 3 cycles per loop, 17 cycles overhead
void _delay_loop_8(uint8_t ctr) {
//  while (--ctr);
  ctr;
__asm
// mov  dpl, #0x??        ; [3]
// lcall __delay_loop_8   ; [6]
  mov r7, dpl             ; [4]
_delay_loop_8_lp:
  djnz  r7, _delay_loop_8_lp  ; [3]
// ret	                  ; [4]
__endasm;
}
