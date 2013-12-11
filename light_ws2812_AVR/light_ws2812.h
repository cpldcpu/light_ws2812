/*
 * light weight WS2812 lib
 *
 * Created: 07.04.2013 15:58:05 - v0.1
 *			06.05.2013          - v0.3 - clean up
 *			27.05.2013			- v0.6 - clean up, removed RC variants, added mask
 *          08.08.2013          - v0.9 - 20 Mhz version added
 *			11.12.3013			- v1.0 - added irq disable
 *  Author: Tim (cpldcpu@gmail.com) 
 */ 

#ifndef LIGHT_WS2812_H_
#define LIGHT_WS2812_H_

#include <avr/io.h>
#include <avr/interrupt.h>
// Call with address to led color array (order is Green-Red-Blue)
// Numer of bytes to be transmitted is leds*3

void ws2812_sendarray(uint8_t *ledarray,uint16_t length);
void ws2812_sendarray_mask(uint8_t *ledarray,uint16_t length, uint8_t mask);

#define irq_disable  uint8_t sreg_prev=SREG;cli();
#define irq_restore  SREG=sreg_prev;

///////////////////////////////////////////////////////////////////////
// User defined area: Define I/O pin
///////////////////////////////////////////////////////////////////////

#define ws2812_port PORTB						// Data port register
#define ws2812_pin 0							// Number of the data out pin

///////////////////////////////////////////////////////////////////////
// User defined area: Define CPU clock speed
// Uncomment one and only one #define matching your application
///////////////////////////////////////////////////////////////////////

// #define ws2812_4MHz
// #define ws2812_8MHz		
// #define ws2812_9p6MHz
// #define ws2812_12MHz  
 #define ws2812_16MHz
// #define ws2812_20MHz     

///////////////////////////////////////////////////////////////////////
// End user defined area
///////////////////////////////////////////////////////////////////////

#endif /* LIGHT_WS2812_H_ */
