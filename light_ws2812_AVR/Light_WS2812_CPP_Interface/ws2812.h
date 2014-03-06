/*
 * C++ Interface for light weight WS2812 lib 
 *
 *  Created: 06.03.2014 20:34:01
 *  Author: Matthias Riegler (abcbyxvzf@gmail.com)
 *
 * License: GNU GPL v2 (see License.txt)
 */ 
 
#ifndef WS2812_H_
#define WS2812_H_
#include "light_ws2812.h"

#define WS2812_ERROR 1
#define WS2812_SUCCESS 0

#ifndef __COUNT_WS2812
#define __COUNT_WS2812 255
#endif

class ws2812 {
public:
	/* Should be understandable */
	ws2812(uint16_t num_leds);
	
	/* Inits just one LED */
	ws2812();
	
	~ws2812();

	/* Update complete LED string */
	void sync();
	
	/* If you want to dynamicly increase or decrease the LEDs you wan't to adress */
	void dynamic_update_count(uint16_t num_leds);
	
	/* Set value to LED and update - this function doesn't save the value in the array, use the one below*/
	uint8_t set_led_value_and_update(uint16_t index, uint8_t R, uint8_t G, uint8_t B);
	
	/* Sets value to Array. Color will be set by the next sync() */
	uint8_t set_led_value(uint16_t index, uint8_t R, uint8_t G, uint8_t B);
	
	/* Not recommendet to use, but if you want to scale up brightness or sth like this it's usefull */
	cRGB get_led_value(uint16_t index);
	
private:
	void init();
	
	uint16_t led_count;
	struct cRGB leds[__COUNT_WS2812];	
	
} ;



#endif /* WS2812_H_ */