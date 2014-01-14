/*
* light weight WS2812 lib V2.0a
*
* Created Jan 11th, 2014  v2.0a Initial Version
* Author: Tim (cpldcpu@gmail.com)
*/

#include "light_ws2812.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void inline ws2812_sendarray_mask(uint8_t *, uint16_t , uint8_t);

void ws2812_sendarray(uint8_t *data,uint16_t datlen)
{
  ws2812_sendarray_mask(data,datlen,_BV(ws2812_pin));
}


/*
This routine writes an array of bytes with RGB values to the Dataout pin
using the fast 800kHz clockless WS2811/2812 protocol.

The description of the protocol in the datasheet is somewhat confusing and
it appears that some timing values have been rounded.

The order of the color-data is GRB 8:8:8. Serial data transmission begins
with the most significant bit in each byte.

The total length of each bit is 1.25µs (20 cycles @ 16Mhz)
* At 0µs the dataline is pulled high.
* To send a zero the dataline is pulled low after 0.375µs (6 cycles).
* To send a one the dataline is pulled low after 0.625µs (10 cycles).

After the entire bitstream has been written, the dataout pin has to remain low
for at least 50µS (reset condition).

Due to the loop overhead there is a slight timing error: The loop will execute
in 21 cycles for the last bit write. This does not cause any issues though,
as only the timing between the rising and the falling edge seems to be critical.
Some quick experiments have shown that the bitstream has to be delayed by
more than 3µs until it cannot be continued (3µs=48 cyles).

*/

#if F_CPU>=8000000
#elif F_CPU>=4000000
#warning "The WS2812 timing for 4 MHz CPU clock is critical, see documentation."
#warning "If you experience problems you should consider using at least 8 MHz CPU clock."
#else
#error "Sorry, clock speeds below 4MHz are not supported. Did you set the define F_CPU correctly?"
#endif

// Fixed instructions in loop take 8 cycles on all architectures
#define w_fixedcycles 8   

// Insert NOPs so the total loop execution time is 1.25µs or more
#define w_totaldelay	(((F_CPU/1000)*1250)/1000000)-w_fixedcycles

#if w_totaldelay>0
  #define w_nops w_totaldelay
#else
  #define w_nops  0
#endif

#define w_nop1  "	nop		    \n\t"
#define w_nop2  "	rjmp .+0	\n\t"
#define w_nop4  w_nop2 w_nop2
#define w_nop8  w_nop4 w_nop4
#define w_nop16 w_nop8 w_nop8

void inline ws2812_sendarray_mask(uint8_t *data,uint16_t datlen,uint8_t maskhi)
{
  uint8_t curbyte,ctr,masklo;
  uint8_t sreg_prev=SREG;
  
  cli();
  
  masklo	=~maskhi&ws2812_port;
  maskhi |=        ws2812_port;

  while (datlen--) {
    curbyte=*data++;
    
    asm volatile(
    "       ldi   %0,8  \n\t"
    "loop%=:            \n\t"
    "       out   %2,%3 \n\t"    //  '1' [01] '0' [01]
    "       sbrs  %1,7  \n\t"    //  '1' [03] '0' [02]
    "       out   %2,%4 \n\t"    //  '1' [--] '0' [03]
    "       lsl   %1    \n\t"    //  '1' [04] '0' [04]
    "       dec   %0    \n\t"    //  '1' [05] '0' [05]
#if (w_nops&1)
  w_nop1
#endif
#if (w_nops&2)
  w_nop2
#endif
#if (w_nops&4)
  w_nop4
#endif
#if (w_nops&8)
  w_nop8
#endif
#if (w_nops&16)
  w_nop16 
#endif
    "       out   %2,%4 \n\t"    //  '1' [+1] '0' [+1]
    "       brne  loop%=\n\t"    //  '1' [+3] '0' [+3]
    :	"=&d" (ctr)
    :	"r" (curbyte), "I" (_SFR_IO_ADDR(ws2812_port)), "r" (maskhi), "r" (masklo)
    );
  }
  
  SREG=sreg_prev;
}
