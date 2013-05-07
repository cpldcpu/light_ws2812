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
struct CRGB led[3];

int main(void)
{
	CLKPR=_BV(CLKPCE);
	CLKPR=0;			// set clock prescaler to 1 (attiny 25/45/85/24/44/84)
	
	DDRB|=_BV(PB4);

	while(1)
    {
		uint8_t i;
		
		led[0].r=32;led[0].g=32;led[0].b=32;
		led[1].r=32;led[1].g=0;led[1].b=0;
		led[2].r=0;led[2].g=32;led[2].b=0;

		ws2812_sendarray(&led[0],3*3);
		_delay_ms(500);
		
		led[0].r=32;led[0].g=0;led[0].b=0;
		led[1].r=0;led[1].g=32;led[1].b=0;
		led[2].r=0;led[2].g=0;led[2].b=32;
	
		ws2812_sendarray(&led[0],3*3);
		_delay_ms(500);
	
    }
}