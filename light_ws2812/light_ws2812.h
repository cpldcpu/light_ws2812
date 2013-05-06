/*
 * light weight WS2812 lib
 *
 * Created: 07.04.2013 15:58:05 - v0.1
 *			06.05.2013          - v0.3 - clean up
 *  Author: Tim (cpldcpu@gmail.com) 
 */ 

#include <avr/io.h>

#ifndef LIGHT_WS2812_H_
#define LIGHT_WS2812_H_

// Call with address to led color array (order is Green-Red-Blue)
// Numer of bytes to be transmitted is leds*3

void ws2812_sendarray_8Mhz(uint8_t *ledarray,uint16_t length);

///////////////////////////////////////////////////////////////////////
// User defined area: Define I/O pin
///////////////////////////////////////////////////////////////////////

#define ws2812_port _SFR_IO_ADDR(PORTB)		// Data port register
#define ws2812_pin 1						// Number of the data out pin


///////////////////////////////////////////////////////////////////////
// User defined area: Define CPU Core and clock speed
// Uncomment one and only one define matching your application
///////////////////////////////////////////////////////////////////////

/* Standard AVR Core - should work on most devices */

// #define ws2812_8MHz		
// #define ws2812_9p6MHz
// #define ws2812_12MHz
 #define ws2812_16MHz

/* Reduced AVR core - works on Attiny 4/5/9/10 */

// #define ws2812_4MHz_RC
// #define ws2812_8MHz_RC

//////////////////////////////////////////////////////////////////////
// End user defined area
//////////////////////////////////////////////////////////////////////

#endif /* LIGHT_WS2812_H_ */