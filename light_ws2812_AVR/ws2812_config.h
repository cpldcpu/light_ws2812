/*
 * light_ws2812_config.h
 *
 * Created: 18.01.2014 09:58:15
 *
 * User Configuration file for the light_ws2812_lib
 *
 */ 


#ifndef WS2812_CONFIG_H_
#define WS2812_CONFIG_H_

///////////////////////////////////////////////////////////////////////
// Define I/O pin
///////////////////////////////////////////////////////////////////////


#ifndef ws2812_port 
#define ws2812_port B // Data port
#endif

#ifndef ws2812_pin
#define ws2812_pin 1 // Data out pin
#endif

#endif /* WS2812_CONFIG_H_ */