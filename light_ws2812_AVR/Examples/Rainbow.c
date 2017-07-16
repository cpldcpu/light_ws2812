/*
 *
 * This example is configured for a Atmega32 at 16MHz
 */ 

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"

#define MAXPIX 30
#define COLORLENGTH (MAXPIX/2)
#define FADE (256/COLORLENGTH)

struct cRGB colors[8];
struct cRGB led[MAXPIX];

int main(void)
{
	
	uint8_t j = 1;
	uint8_t k = 1;

	DDRB|=_BV(ws2812_pin);
		
    uint8_t i;
    for(i=MAXPIX; i>0; i--)
    {    
        led[i-1].r=0;led[i-1].g=0;led[i-1].b=0;
    }
		
    //Rainbowcolors
    colors[0].r=150; colors[0].g=150; colors[0].b=150;
    colors[1].r=255; colors[1].g=000; colors[1].b=000;//red
    colors[2].r=255; colors[2].g=100; colors[2].b=000;//orange
    colors[3].r=100; colors[3].g=255; colors[3].b=000;//yellow
    colors[4].r=000; colors[4].g=255; colors[4].b=000;//green
    colors[5].r=000; colors[5].g=100; colors[5].b=255;//light blue (türkis)
    colors[6].r=000; colors[6].g=000; colors[6].b=255;//blue
    colors[7].r=100; colors[7].g=000; colors[7].b=255;//violet
    
	while(1)
    {
        //shift all vallues by one led
        uint8_t i=0;           
        for(i=MAXPIX; i>1; i--) 
            led[i-1]=led[i-2];
        //change colour when colourlength is reached   
        if(k>COLORLENGTH)
        {
            j++;
            if(j>7)
            {
              j=0;
            }

            k=0;
        }
        k++;
        //loop colouers
        
        //fade red
        if(led[0].r<(colors[j].r-FADE))
            led[0].r+=FADE;
            
        if(led[0].r>(colors[j].r+FADE))
            led[0].r-=FADE;

        if(led[0].g<(colors[j].g-FADE))
            led[0].g+=FADE;
            
        if(led[0].g>(colors[j].g+FADE))
            led[0].g-=FADE;

        if(led[0].b<(colors[j].b-FADE))
            led[0].b+=FADE;
            
        if(led[0].b>(colors[j].b+FADE))
            led[0].b-=FADE;

		 _delay_ms(10);
		 ws2812_sendarray((uint8_t *)led,MAXPIX*3);
    }
}
