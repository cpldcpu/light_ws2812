/*
 * light_ws2812 example
 *
 * Created: 07.03.2014 12:49:30
 *  Author: Matthias Riegler
 */ 

#include <WS2812.h>

WS2812 LED(1); // 1 LED
	
void setup() {
	LED.setOutput(9); // Digital Pin 9
}

void loop() {
	LED.set_crgb_at(0, {0, 0, 255}); // Set RGB Blue at LED found at index 0
	LED.sync(); // Sends the value to the LED
	delay(500); // Wait 500 ms
	
	LED.set_crgb_at(0, {255, 0, 0}); // Set RGB Red at LED found at index 0
	LED.sync(); // Sends the value to the LED
	delay(500); // Wait 500 ms
}

