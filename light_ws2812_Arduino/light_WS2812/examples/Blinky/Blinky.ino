/*
 * light_ws2812 example
 *
 * Created: 07.03.2014 12:49:30
 *  Author: Matthias Riegler
 */ 

#include <WS2812.h>

WS2812 LED(1); // 1 LED
	
cRGB value;

void setup() {
	LED.setOutput(9); // Digital Pin 9
}

void loop() {
	value.b = 255; value.g = 0; value.r = 0; // RGB Value -> Blue
	LED.set_crgb_at(0, value); // Set value at LED found at index 0
	LED.sync(); // Sends the value to the LED
	delay(500); // Wait 500 ms
	
	value.b = 0; value.g = 0; value.r = 255; // RGB Value -> Red
	LED.set_crgb_at(0, value); // Set value at LED found at index 0
	LED.sync(); // Sends the value to the LED
	delay(500); // Wait 500 ms
}

