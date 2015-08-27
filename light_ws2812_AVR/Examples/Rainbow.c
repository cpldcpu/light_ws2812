/*
* Light_WS2812 library example - RGB_blinky
*
* cycles one LED through red, green, blue
*
* This example is configured for a ATtiny85 with PLL clock fuse set and
* the WS2812 string connected to PB4.
*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"

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

    uint8_t i;
    uint8_t maxpix=30;
    uint8_t dirRed=1;
   // uint8_t dirGreen=1;
    uint8_t dirBlue=0;
    uint8_t stepBlueDown = 15;
    uint8_t stepBlueUp = 4;
    
    for(i=maxpix; i>0; i--)
    {    
        led[i].r=0;led[i].g=00;led[i].b=0;

    }
led[1].r=100;led[0].g=00;led[0].b=100;

  while(1)
  {
  


  
    for(i=maxpix-1; i>0; i--)
    {    
        led[i+1]=led[i];
        ws2812_setleds(led,(i+1));

    }
    i=0;
    
   
    
    if(dirRed==1 && led[1].r<255)       
        led[1].r++;                 
    else if(dirRed==1 && led[1].r==255) 
        dirRed=0;
  
    if(dirRed==0 && led[1].r>0)       
        led[1].r--;                 
    else if(dirRed==0 && led[1].r==0) 
        dirRed=1;  
    
    
    
    if(dirBlue==1 && led[1].b<255-stepBlueUp)       
        led[1].b+=stepBlueUp;                 
  
    if(dirBlue==0 && led[1].b>stepBlueDown)    
        led[1].b-=stepBlueDown;                 
 
              
    if(led[1].b>=(255-stepBlueUp))
    {
      dirBlue=0; 
      if(led[1].b>255)
            led[1].b=255; 
     }
        
    if(led[1].b<=stepBlueDown)
    {
      dirBlue=1; 
      if(led[1].b<0)
            led[1].b=0;
     }   

        
        
    _delay_ms(300);
     



  }
}
