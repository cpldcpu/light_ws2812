/*
 * C++ Interface for light weight WS2812 lib 
 *
 *  Created: 06.03.2014 20:34:01
 *  Author: Matthias Riegler (abcbyxvzf@gmail.com)
 *
 * License: GNU GPL v2 (see License.txt)
 */ 

#include "ws2812.h"


ws2812::ws2812(uint16_t num_leds) {
	led_count = num_leds;
	init();
}

void ws2812::init() {
	for(uint16_t i = 0; i < led_count; i++) {
		leds[i].b = 0; leds[i].g = 0; leds[i].r = 0;
	}
}

void ws2812::dynamic_update_count(uint16_t num_leds) {
	delete leds;
	led_count = num_leds;
	init();
}

void ws2812::sync() {
	ws2812_setleds(leds, led_count);
}

uint8_t ws2812::set_led_value_and_update(uint16_t index, uint8_t R, uint8_t G, uint8_t B) {
	
	uint8_t status = set_led_value(index, R, G, B);
	sync();	
	return status;
}


uint8_t ws2812::set_led_value(uint16_t index, uint8_t R, uint8_t G, uint8_t B) {
	if( (index < led_count) && (index <= __COUNT_WS2812) ) {
		leds[index].b = B;
		leds[index].g = G;
		leds[index].r = R;
		return WS2812_SUCCESS;
	} 
	return WS2812_ERROR;
}

cRGB ws2812::get_led_value(uint16_t index) {
	
	cRGB value;
	if( (index < led_count) && (index <= __COUNT_WS2812) ) {
		value.b = leds[index].b;
		value.g = leds[index].g;
		value.r = leds[index].r;
		return value;
	}
	value.b = 0; value.g = 0; value.r = 0;
	return value;
}


ws2812::~ws2812() {
	delete leds;	
}