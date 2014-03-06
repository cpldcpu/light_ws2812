/*
* Light_WS2812 library example - RGB_blinky_CPP
*
* cycles one LED through red, green, blue
*
* This example is configured for a ATtiny85 with PLL clock fuse set and
* the WS2812 string connected to PB4.
*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define __COUNT_WS2812 1

#include "ws2812.h"

int main(void)
{

  #ifdef __AVR_ATtiny10__
  CCP=0xD8;		// configuration change protection, write signature
  CLKPSR=0;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
  #else
  CLKPR=_BV(CLKPCE);
  CLKPR=0;			// set clock prescaler to 1 (attiny 25/45/85/24/44/84/13/13A)
  #endif

  ws2812 led(1);
  
  while(1)
  {
  
	led.set_led_value(0,255,0,0);			// red
    _delay_ms(500);                         // wait for 500ms.
	led.set_led_value(0,0,255,0);			// green
    _delay_ms(500);

    led.set_led_value(0,0,0,255);			// blue
    _delay_ms(500);
  }
}
