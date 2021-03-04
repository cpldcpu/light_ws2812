/*
* light weight APA102 lib - v0.1
*
* Controls APA102 RGB-LEDs
* Author: Tim (cpldcpu@gmail.com)
*
* Nov 30th, 2014 Initial Version
*
* License: GNU GPL v2 (see License.txt)
*/

#include "light_apa102.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define nop() asm volatile(" nop \n\t")

/*
  Software based SPI implementation. f_clk is approximately f_cpu/16.
  This is not optimized for maximum speed, but to output proper waveforms in case of
  bad cabling. If you want more speed, you should adapt this code to use
  hardware SPI.
*/

static inline void SPI_init(void) {
  apa102_DDRREG  |=  _BV(apa102_data);
  apa102_DDRREG  |=  _BV(apa102_clk);
  apa102_PORTREG &= ~_BV(apa102_clk);  // initial state of clk is low
}

// Assumed state before call: SCK- Low, MOSI- High
void SPI_write(uint8_t c) {
  uint8_t i;
  for (i=0; i<8 ;i++)
  {
    if (!(c&0x80)) {
      apa102_PORTREG &= ~_BV(apa102_data); // set data low
    } else {
      apa102_PORTREG |=  _BV(apa102_data); // set data high
    }     
  
  apa102_PORTREG |= (1<< apa102_clk); // SCK hi , data sampled here

  c<<=1;
  
  nop();  // Stretch clock
  nop();
  
  apa102_PORTREG &= ~_BV(apa102_clk); // clk low
  }
// State after call: SCK Low, Dat high
}

void inline apa102_setleds(struct cRGB *ledarray, uint16_t leds)
{
  apa102_setleds_brightness(ledarray,leds,31);
}
 
void inline apa102_setleds_brightness(struct cRGB *ledarray, uint16_t leds,uint8_t brightness)
{
  uint16_t i;
  uint8_t *rawarray=(uint8_t*)ledarray;
  SPI_init();
  
  SPI_write(0x00);  // Start Frame 
  SPI_write(0x00);
  SPI_write(0x00);
  SPI_write(0x00);
 
  for (i=0; i<(leds+leds+leds); i+=3)
  {
    SPI_write(0xe0+brightness);  // Maximum global brightness
    SPI_write(rawarray[i+0]);
    SPI_write(rawarray[i+1]);
    SPI_write(rawarray[i+2]);
  }

  // Reset frame - Only needed for SK9822, has no effect on APA102
  SPI_write(0x00);  
  SPI_write(0x00);
  SPI_write(0x00);
  SPI_write(0x00);
  
  // End frame: 8+8*(leds >> 4) clock cycles    
  for (i=0; i<leds; i+=16)
  {
    SPI_write(0x00);  // 8 more clock cycles
  }
}
