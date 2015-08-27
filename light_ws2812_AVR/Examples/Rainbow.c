/*
* Light_WS2812 library example - Rainbowfade
*
*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"

struct cRGB led[30];
struct cRGB colors[30];
int main(void)
{

  #ifdef __AVR_ATtiny10__
  CCP=0xD8;		// configuration change protection, write signature
  CLKPSR=0;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
  #else
  CLKPR=_BV(CLKPCE);
  CLKPR=0;			// set clock prescaler to 1 (attiny 25/45/85/24/44/84/13/13A)
  #endif

    uint8_t j=1;
    uint8_t k=1;
    uint8_t maxpix=30;
    //uint8_t stepwidth = 5;


    
    uint8_t i=0;
    for(i=maxpix; i>0; i--)
    {    
        led[i].r=0;led[i].g=0;led[i].b=0;
    }

    //Rainbowcolors
    colors[0].r=000; colors[0].g=000; colors[0].b=000;
    colors[1].r=255; colors[1].g=000; colors[1].b=000;//red
    colors[2].r=255; colors[2].g=100; colors[2].b=000;//orange
    colors[3].r=100; colors[3].g=255; colors[3].b=000;//yellow
    colors[4].r=000; colors[4].g=255; colors[4].b=000;//green
    colors[5].r=000; colors[5].g=100; colors[5].b=255;//light blue (türkis)
    colors[6].r=000; colors[6].g=000; colors[6].b=255;//blue
    colors[7].r=100; colors[7].g=000; colors[7].b=255;//violet

  while(1)
  {
    uint8_t i=0;
    
    for(i=maxpix-1; i>0; i--)
    {    
        led[i+1]=led[i];
        ws2812_setleds(led,(i+1));

    }
    if(k>100)
    {
        j++;
        k=0;
    }
    k++;
    if(j>7)
        j=0;
    
    
    if(led[1].r<colors[j].r)
        led[1].r++;
        
    if(led[1].r>colors[j].r)
        led[1].r--;
    
    if(led[1].g<colors[j].g)
        led[1].g++;
        
    if(led[1].g>colors[j].g)
        led[1].g--;

    if(led[1].b<colors[j].b)
        led[1].b++;
        
    if(led[1].b>colors[j].b)
        led[1].b--;
     
    _delay_ms(100);


  }
}
