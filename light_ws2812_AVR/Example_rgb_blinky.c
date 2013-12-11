/*
 * Light_WS2812 library example - RGB_blinky
 *
 * cycles one LED through red, green, blue
 *
 * This example is configured for a ATtiny85 with PLL clock fuse set and 
 * the WS2812 string connected to PB4. 
 */ 

#define F_CPU 16000000

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"

struct CRGB { uint8_t g; uint8_t r; uint8_t b; };
struct CRGB led[1];

int main(void)
{
	uint8_t mask;
	
	#ifdef __AVR_ATtiny10__
		CCP=0xD8;		// configuration change protection, write signature
		CLKPSR=1;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
		mask=_BV(PB2);
	#else
		CLKPR=_BV(CLKPCE);
		CLKPR=0;			// set clock prescaler to 1 (attiny 25/45/85/24/44/84/13/13A)		
		mask=_BV(PB0);
	#endif
		DDRB|=mask;
	
	while(1)
    {
		led[0].r=255;led[0].g=00;led[0].b=0;		// Write red to array
		ws2812_sendarray((uint8_t *)&led[0],3);		// Send array to WS2812 LED. The output pin is low after send.
		_delay_ms(500);								// Issue reset and wait for 500ms.
		
		led[0].r=0;led[0].g=255;led[0].b=0;			// green
		ws2812_sendarray((uint8_t *)&led[0],3);
		_delay_ms(500);

		led[0].r=0;led[0].g=00;led[0].b=255;		// blue
		ws2812_sendarray((uint8_t *)&led[0],3);
		_delay_ms(500);	
    }
}