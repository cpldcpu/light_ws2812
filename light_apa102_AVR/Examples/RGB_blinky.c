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
    apa102_setleds({255, 0, 0},30);         // Write red to array
    _delay_ms(500);                         // wait for 500ms.

    apa102_setleds({0, 255, 0},30);         // green
    _delay_ms(500);

    apa102_setleds({0, 0, 255},30);         // blue
    _delay_ms(500);
  }
}
