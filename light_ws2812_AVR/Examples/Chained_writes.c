/*
 * ATTENTION: This example uses the old v1.0 interface.
 *
 * Light_WS2812 library example - Chained Writes
 *
 * This example shows how to use multiple calls without issuing a reset 
 * in between, allowing to send the same buffer to the string
 * multiple times. This technique can be useful to conserve memory
 * or to calculate LED colors on-the-fly.
 *
 * Please make sure to set your configuration in "WS2812_config.h" first
 *
 */ 

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"

struct cRGB led[2];

int main(void)
{

	uint8_t pos=0;
	uint8_t direction=1;	
	uint8_t i;
	
	#ifdef __AVR_ATtiny10__
		CCP=0xD8;		// configuration change protection, write signature
		CLKPSR=0;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
	#endif
  	
	led[0].r=16;led[0].g=00;led[0].b=00;		// LED 0 is red
	led[1].r=16;led[1].g=16;led[1].b=16;		// LED 1 is White
	
	while(1)
    {
	
		for (i=0; i<pos; i++) 
			ws2812_sendarray((uint8_t *)&led[0],3);			// Repeatedly send "red" to the led string. 
															// No more than 1-2µs should pass between calls
															// to avoid issuing a reset condition.			
		for (i=0; i<(16-pos); i++) 
			ws2812_sendarray((uint8_t *)&led[1],3);			// white
			
		_delay_ms(50);										// Issue reset and wait for 50 ms.
		
		pos+=direction;		
		if ((pos==16)||(pos==0)) direction=-direction;
    }
}