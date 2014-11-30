/*
* Light_APA102 library example - RGB_blinky
*
* cycles one LED through red, green, blue
*
* This example is configured for a ATtiny85 with PLL clock fuse set
*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_apa102.h"

struct cRGB led[1];

int main(void)
{

  #ifdef __AVR_ATtiny10__
  CCP=0xD8;		// configuration change protection, write signature
  CLKPSR=0;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
  #else
  CLKPR=_BV(CLKPCE);
  CLKPR=0;			// set clock prescaler to 1 (attiny 25/45/85/24/44/84/13/13A)
  #endif


  while(1)
  {
    led[0].r=255;led[0].g=00;led[0].b=0;    // Write red to array
    apa102_setleds(led,30);
    _delay_ms(500);                         // wait for 500ms.

    led[0].r=0;led[0].g=255;led[0].b=0;			// green
    apa102_setleds(led,1);
    _delay_ms(500);

    led[0].r=0;led[0].g=00;led[0].b=255;		// blue
    apa102_setleds(led,1);
    _delay_ms(500);
  }
}
