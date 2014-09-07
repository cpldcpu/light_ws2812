/*
* light weight WS2812 lib V2.1 - Arduino support
*
* Controls WS2811/WS2812/WS2812B RGB-LEDs
* Author: Matthias Riegler
*
* Mar 07 2014: Added Arduino and C++ Library
*
* September 6, 2014      Added option to switch between most popular color orders
*                          (RGB, GRB, and BRG) --  Windell H. Oskay
*
* License: GNU GPL v2 (see License.txt)
*/

#ifndef WS2812_H_
#define WS2812_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#ifndef F_CPU
#define  F_CPU 16000000UL
#endif
#include <util/delay.h>
#include <stdint.h>

#ifdef ARDUINO
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif
#endif

struct cRGB { uint8_t g; uint8_t r; uint8_t b; };

class WS2812 {
public: 
	WS2812(uint16_t num_led);
	~WS2812();
	
	#ifndef ARDUINO
	void setOutput(const volatile uint8_t* port, volatile uint8_t* reg, uint8_t pin);
	#else
	void setOutput(uint8_t pin);
	#endif
	
	cRGB get_crgb_at(uint16_t index);
	uint8_t set_crgb_at(uint16_t index, cRGB px_value);
	void sync();
	void setColorOrderRGB();
	void setColorOrderGRB();
	void setColorOrderBRG();
	

private:
	uint16_t count_led;
	uint8_t *pixels;
	uint8_t offsetRed;
	uint8_t offsetGreen;
	uint8_t offsetBlue;

	void ws2812_sendarray_mask(uint8_t *array,uint16_t length, uint8_t pinmask,uint8_t *port, uint8_t *portreg);

	const volatile uint8_t *ws2812_port;
	volatile uint8_t *ws2812_port_reg;
	uint8_t pinMask; 
};



#endif /* WS2812_H_ */