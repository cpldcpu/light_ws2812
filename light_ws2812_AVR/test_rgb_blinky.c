/*
 * test_rgb_blinky
 *
 * Created: 17.04.2013 10:01:20
 *  Author: Tim
 */ 

#define F_CPU 16000000

#include <avr/delay.h>
#include <avr/io.h>
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
		mask=_BV(PB4);
	#endif
		DDRB|=mask;
	
	
	while(1)
    {
		uint8_t i;
		
		led[0].r=32;led[0].g=32;led[0].b=32;

		ws2812_sendarray(&led[0],3);
		_delay_ms(500);
		
		led[0].r=32;led[0].g=0;led[0].b=0;
	
		ws2812_sendarray(&led[0],3);
		_delay_ms(500);
	
    }
}