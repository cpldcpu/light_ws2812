/*
 * light weight WS2812 lib
 *
 * Created: 07.04.2013 15:57:49 - v0.1
 *			21.04.2013 15:57:49 - v0.2 - Added 12 Mhz code, cleanup
 *			07.05.2013          - v0.4 - size optimization, disable irq
 *
 *  Author: Tim (cpldcpu@gmail.com) 
 */ 

#include "light_ws2812.h"
#include <avr/interrupt.h>

#if defined ws2812_noirq
	#define ws2812_sei
	#define ws2812_cli
#else
	#define ws2812_sei	sei();
	#define ws2812_cli	cli();
#endif

/*
	This routine writes an array of bytes with RGB values to the Dataout pin
	using the fast 800kHz clockless WS2811/2812 protocol.
	
	The description of the protocol in the datasheet is somewhat confusing and
	it appears that some timing values have been rounded. 
	
	The order of the color-data is GRB 8:8:8. Serial data transmission begins 
	with the most significant bit in each byte.
	
	The total length of each bit is 1.25탎 (20 cycles @ 16Mhz)
	* At 0탎 the dataline is pulled high.
	* To send a zero the dataline is pulled low after 0.375탎 (6 cycles).
	* To send a one the dataline is pulled low after 0.625탎 (10 cycles).
	
	After the entire bitstream has been written, the dataout pin has to remain low
	for at least 50탎 (reset condition).
	
	Due to the loop overhead there is a slight timing error: The loop will execute
	in 21 cycles for the last bit write. This does not cause any issues though,
	as only the timing between the rising and the falling edge seems to be critical.
	Some quick experiments have shown that the bitstream has to be delayed by 
	more than 3탎 until it cannot be continued (3탎=48 cyles).
	
	Note: Code should be compiled with optimizations switched on or the timing
	will be off. -O1 is minimum.

	timing is slightly different on xmega and reduced avr due to single cycle sbi/cbi
*/

#if defined ws2812_16MHz

void ws2812_sendarray(uint8_t *data,uint16_t datlen)
{
	uint8_t curbyte,ctr;	
	
	ws2812_sei
	
	while (datlen--) {
		curbyte=*data++;	
						
		asm volatile(
			"		ldi	%0,8		\n\t"		// 0
			"loop%=:sbi	%2,	%3		\n\t"		// 2
			"		lsl	%1			\n\t"		// 3
			"		dec	%0			\n\t"		// 4

			"		nop				\n\t"		// 5
		
			"		brcs .+2		\n\t"		// 6l / 7h
			"		cbi	%2,	%3		\n\t"		// 8l / -

			"		rjmp .+2		\n\t"		// 10l / 9h
									  					
			"		brcc .+2		\n\t"		// 12l / 10h
			"		cbi	%2,	%3		\n\t"		// -   / 12h    
			"		breq end%=		\n\t"		// 13 nt. 14 taken

			"		rjmp .+2		\n\t"		// 15
			"		rjmp .+2		\n\t"		// 17

			"		nop				\n\t"		// 18
			"		rjmp loop%=		\n\t"		// 20				
			"end%=:					\n\t"		
		:	"=&d" (ctr)
		:	"r" (curbyte), "I" (ws2812_port), "I" (ws2812_pin)
		);
		
		// loop overhead including byte load is 6+1 cycles		
	}
	
	ws2812_cli
}

/*
	Timing optimized for 12Mhz AVR (excl. XMEGA and reduced instruction set)

	The total length of each bit is 1.25탎 (15 cycles @ 12Mhz)
	* At 0탎 the dataline is pulled high.  (cycle 4+0)
	* To send a zero the dataline is pulled low after 0.333탎 (4+4=8 cycles).
	* To send a one the dataline is pulled low after 0.666탎 (4+8=12 cycles).

	Total loop timing is correct, but the timing for the falling edge can
	not be accurately reached as the correct 0.375탎 (4.5 cyc.) and 0.675탎 (7.5 cyc)
	timings fall in between cycles.
	
	Final timing: 
	* 15 cycles for bits 7-1
	* 19 cycles for bit 0		
*/


#elif defined ws2812_12MHz

void ws2812_sendarray(uint8_t *data,uint16_t datlen)
{
	uint8_t curbyte,ctr;

	ws2812_sei
	
	while (datlen--) {
		curbyte=*data++;
		
		asm volatile(
		"		ldi	%0,8		\n\t"		// 0
		"loop%=:lsl	%1			\n\t"		// 1
		"		dec	%0			\n\t"		// 2
		"		sbi	%2,	%3		\n\t"		// 4
		"		nop				\n\t"		// 5
	
		"		brcs .+2		\n\t"		// 6l  / 7h
		"		cbi	%2,	%3		\n\t"		// 8l  / -

		"		rjmp .+2		\n\t"		// 10l / 9h
											
		"		brcc .+2		\n\t"		// 12l / 10h
		"		cbi	%2,	%3		\n\t"		// -   / 12h 

		"		nop				\n\t"		// 13
		
		"		brne loop%=		\n\t"		// 15 loop /14 nt
		:	"=&d" (ctr)
		:	"r" (curbyte), "I" (ws2812_port), "I" (ws2812_pin)
		);
		
		// loop overhead including byte load is 6+1 cycles
	}
	ws2812_cli
}

/*
	Timing optimized for 8Mhz AVR (excl. XMEGA and reduced instruction set)

	The total length of each bit is 1.25탎 (10 cycles @ 8Mhz)
	* At 0탎 the dataline is pulled high.  (cycle 4+0)
	* To send a zero the dataline is pulled low after 0.375탎 (4+3=7 cycles).
	* To send a one the dataline is pulled low after 0.625탎 (4+5=9 cycles).

	10 cycles can not be reached without loop unrolling, or by using byte
	writes to the ports. However since the critical timing between the rising and 
	falling edge is correct, it seems to be acceptable to slightly increase 
	bit timing
	
	Final timing: 
	* 11 cycles for bits 7-1
	* 17 cycles for bit 0		
*/

#elif defined ws2812_8MHz

void ws2812_sendarray(uint8_t *data,uint16_t datlen)
{
	uint8_t curbyte,ctr;

	ws2812_sei
	
	while (datlen--) {
		curbyte=*data++;
		
		asm volatile(
		"		ldi	%0,8		\n\t"		// 0
		"loop%=:lsl	%1			\n\t"		// 1
		"		dec	%0			\n\t"		// 2
		"		sbi	%2,	%3		\n\t"		// 4
	
		"		brcs .+2		\n\t"		// 5l / 6h
		"		cbi	%2,	%3		\n\t"		// 7l / -
											// 7l / 6h
		"		brcc .+2		\n\t"		// 9l / 7h
		"		cbi	%2,	%3		\n\t"		// -  / 9h
		"		brne loop%=		\n\t"		// 11 loop /10 nt
		:	"=&d" (ctr)
		:	"r" (curbyte), "I" (ws2812_port), "I" (ws2812_pin)
		);
		
		// loop overhead including byte load is 6+1 cycles
	}
	ws2812_cli
}

/*
Timing optimized for 9.6Mhz AVR (excl. XMEGA and reduced instruction set)

The total length of each bit is 1.25탎 (12 cycles @ 9.6Mhz)
* At 0탎 the dataline is pulled high.  (cycle 4)
* To send a zero the dataline is pulled low after 0.375탎 (4+4=8 cycles).
* To send a one the dataline is pulled low after 0.625탎 (4+6=10 cycles).

12 cycles can not be reached for bit 0 write. However since the timing 
between the rising and falling edge is correct, it seems to be acceptable 
to slightly increase bit timing

Final timing:
* 12 cycles for bits 7-1
* 18 cycles for bit 0
*/

#elif defined ws2812_9p6MHz

void ws2812_sendarray(uint8_t *data,uint16_t datlen)
{
	uint8_t curbyte,ctr;
	ws2812_sei
	
	while (datlen--) {
		curbyte=*data++;
		asm volatile(
		"		ldi	%0,8		\n\t"		// 0
		"loop%=:lsl	%1			\n\t"		// 1
		"		dec	%0			\n\t"		// 2
		"		sbi	%2,	%3		\n\t"		// 4
		"		nop				\n\t"		// 5
		
		"		brcs .+2		\n\t"		// 6l / 7h
		"		cbi	%2,	%3		\n\t"		// 8l / -
											// 8l / 7h
		"		brcc .+2		\n\t"		// 10l / 8h
		"		cbi	%2,	%3		\n\t"		// -   / 10h
		"		brne loop%=		\n\t"		// 12 loop / 11 nt
		:	"=&d" (ctr)
		:	"r" (curbyte), "I" (ws2812_port), "I" (ws2812_pin)		
		);
		
		// loop overhead including byte load is 6+1 cycles
	}
	ws2812_cli
}


/*
	Timing optimized for 8Mhz tinyAVR with reduced core.
	(ATtiny 4/5/9/10/20/40)
	
	The main difference is a reduced instruction timing for cbi and sbi

	The total length of each bit is 1.25탎 (10 cycles @ 8Mhz)
	* At 0탎 the dataline is pulled high.  (cycle 3+0=3)
	* To send a zero the dataline is pulled low after 0.375탎 (3+3=6 cycles).
	* To send a one the dataline is pulled low after 0.625탎 (3+5=8 cycles).

	10 cycles can not be reached for the last bit. However, since the critical 
	timing between the rising and falling  edge is correct, it seems to be 
	acceptable to slightly increase bit timing.
	
	Final timing: 
	* 10 cycles for bits 7-1
	* 15 cycles for bit 0		
*/


#elif defined ws2812_8MHz_RC

void ws2812_sendarray(uint8_t *data,uint16_t datlen)
{
	uint8_t curbyte,ctr;
	
	if (!datlen) return;

	ws2812_sei
	
		asm volatile(
		"olop%=:ld  %1,Z+		\n\t"			
		"		ldi	%0,8		\n\t"		// 0
		
		"ilop%=:rjmp .+2		\n\t"		// 2
		"		sbi	%2,	%3		\n\t"		// 3
		"		lsl	%1			\n\t"		// 4
		
		"		brcs .+2		\n\t"		// 5l / 6h
		"		cbi	%2,	%3		\n\t"		// 6l / -
											// 6l / 6h
		"		dec	%0			\n\t"		// 7l / 7h
										
		"		cbi	%2,	%3		\n\t"		// 8h  / 8h
		"		brne ilop%=		\n\t"		// 10 loop /9 nt
	
		"		dec %5			\n\t"		
		"		brne olop%=		\n\t"		
		
		:	"=&d" (ctr), "=&d" (curbyte)
		:	 "I" (ws2812_port), "I" (ws2812_pin), "z" (data), "r" (datlen)
		);
	ws2812_cli		
}

/*
	Timing optimized for 4Mhz tinyAVR with reduced core.
	(ATtiny 4/5/9/10/20/40)
	
	2013/04/08 - cpldcpu@gmail.com
	
	The main difference is a reduced instruction timing for cbi and sbi 
	with 1 cycle instead of 2.
		
	The total length of each bit is 1.25탎 (5 cycles @ 4Mhz)
	* At 0탎 the dataline is pulled high.  (cycle 0+1)
	* To send a zero the dataline is pulled low after 0.5탎 (spec: 0.375탎)  (2+1=3 cycles).
	* To send a one the dataline is pulled low after 0.75탎  (spec: 0.625탎) (3+1=4 cycles).

	The timing of this implementation is slightly off, however it seems to 
	work empirically. Not recommended for actual use.
		
	Final timing: 
	* 5 cycles for bits 7-1
	* 6 cycles for bit 0		
*/


#elif defined ws2812_4MHz_RC

void ws2812_sendarray_4Mhz_rc(uint8_t *data,uint16_t datlen)
{
	uint8_t curbyte,ctr;
	
	if (!datlen) return;
	
	ws2812_sei
	
		asm volatile(
		"		ld  %0,Y		\n\t"			
		
		"olop%=:sbi	%2,	%3		\n\t"		// 1		
		"		sbrs %0,7		\n\t"		// 2
		"		cbi	%2,	%3		\n\t"		// 3										
		"		cbi	%2,	%3		\n\t"		// 4
		"		subi r28,-1		\n\t"		// 5
		
		"		sbi	%2,	%3		\n\t"		// 1
		"		sbrs %0,6		\n\t"		// 2
		"		cbi	%2,	%3		\n\t"		// 3
		"		cbi	%2,	%3		\n\t"		// 4
		"		sbci r29,-1		\n\t"		// 5

		"		sbi	%2,	%3		\n\t"		// 1
		"		sbrs %0,5		\n\t"		// 2
		"		cbi	%2,	%3		\n\t"		// 3
		"		cbi	%2,	%3		\n\t"		// 4
		"		mov %1,%0		\n\t"		// 5

		"		sbi	%2,	%3		\n\t"		// 1
		"		sbrs %1,4		\n\t"		// 2
		"		cbi	%2,	%3		\n\t"		// 3
		"		cbi	%2,	%3		\n\t"		// 4
		"		nop				\n\t"		// 5

		"		sbi	%2,	%3		\n\t"		// 1
		"		sbrs %1,3		\n\t"		// 2
		"		cbi	%2,	%3		\n\t"		// 3
		"		cbi	%2,	%3		\n\t"		// 4
		"		nop				\n\t"		// 5

		"		sbi	%2,	%3		\n\t"		// 1
		"		sbrs %1,2		\n\t"		// 2
		"		cbi	%2,	%3		\n\t"		// 3
		"		cbi	%2,	%3		\n\t"		// 4
		"		ld  %0,Y		\n\t"		// 5

		"		sbi	%2,	%3		\n\t"		// 1
		"		sbrs %1,1		\n\t"		// 2
		"		cbi	%2,	%3		\n\t"		// 3
		"		cbi	%2,	%3		\n\t"		// 4
		"		dec %5			\n\t"		// 5

		"		sbi	%2,	%3		\n\t"		// 1
		"		sbrs %1,0		\n\t"		// 2
		"		cbi	%2,	%3		\n\t"		// 3
		"		cbi	%2,	%3		\n\t"		// 4

		"		brne olop%=		\n\t"		// 6
		
		:	"=&d" (ctr), "=&d" (curbyte)
		:	 "I" (ws2812_port), "I" (ws2812_pin), "y" (data), "r" (datlen)
		);		

	ws2812_cli
}

#else
	#error "Invalid processor selection for ws2812 library!"
#endif