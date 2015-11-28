/*
* Light_WS2812 library example - RGBW_blinky
*
* cycles one LED through red, green, blue, white
*
* This example does only work with the SK6812RGBW LEDs
*
* Please make sure to set your configuration in "WS2812_config.h" first
*
*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"

struct cRGBW led[1];

int main(void)
{
  #ifdef __AVR_ATtiny10__
  CCP=0xD8;		// configuration change protection, write signature
  CLKPSR=0;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
  #endif

  while(1)
  {
    led[0].r=128;led[0].g=00;led[0].b=0;led[0].w=0;    // Write red to array
    ws2812_setleds_rgbw(led,1);
    _delay_ms(500);                                   // wait for 500ms.

    led[0].r=0;led[0].g=128;led[0].b=0;led[0].w=0;    // green
    ws2812_setleds_rgbw(led,1);
    _delay_ms(500);                                   

    led[0].r=0;led[0].g=0;led[0].b=128;led[0].w=0;    // blue
    ws2812_setleds_rgbw(led,1);
    _delay_ms(500);                                   

    led[0].r=0;led[0].g=0;led[0].b=0;led[0].w=128;    // white
    ws2812_setleds_rgbw(led,1);
    _delay_ms(500);                                   

  }
}
