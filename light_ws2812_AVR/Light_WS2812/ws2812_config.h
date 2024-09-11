/*
 * light_ws2812_config.h
 *
 * v2.4 - Nov 27, 2016
 *
 * User Configuration file for the light_ws2812_lib
 *
 */ 


#ifndef WS2812_CONFIG_H_
#define WS2812_CONFIG_H_

///////////////////////////////////////////////////////////////////////
// Define Reset time in µs. 
//
// This is the time the library spends waiting after writing the data.
//
// WS2813 needs 300 µs reset time
// WS2812 and clones only need 50 µs
//
///////////////////////////////////////////////////////////////////////

#define ws2812_resettime  300 

///////////////////////////////////////////////////////////////////////
// Define I/O pin
///////////////////////////////////////////////////////////////////////


#define ws2812_port B     // Data port 
#define ws2812_pin  0     // Data out pin

///////////////////////////////////////////////////////////////////////
// Define interrupt behaviour
//
// Set to 1 if you want the library to handle interrupt toggling
// (i.e. turning off interrupts when sending data and reverting back after).
// Set to 0 if you need to allow interrupts (can introduce flickering!).
//
///////////////////////////////////////////////////////////////////////

#define ws2812_interrupt_handling 1

#endif /* WS2812_CONFIG_H_ */