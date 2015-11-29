/*
 * light_ws2812 example
 * Fade LEDs in R, G, B order; demonstrate functions for changing color order.
 *
 * Created: September 6, 2014
 * Author: Windell Oskay (www.evilmadscientist.com)
 */

#include <WS2812.h>

#define outputPin 7  // Digital output pin (default: 7)
#define LEDCount 9   // Number of LEDs to drive (default: 9)


WS2812 LED(LEDCount); 
cRGB value;

byte intensity;
byte sign;

void setup() {
	  LED.setOutput(outputPin); // Digital Pin 7

	/* You may uncomment one of the following three lines to switch 
	to a different data transmission sequence for your addressable LEDs.
	(These functions can be used at any point in your program as needed.)   */

	LED.setColorOrderRGB();  // Uncomment for RGB color order
	//LED.setColorOrderBRG();  // Uncomment for BRG color order
	//LED.setColorOrderGRB();  // Uncomment for GRB color order (Default; will be used if none other is defined.)

	intensity = 0;
	sign = 1;
}

void loop() {
	int i = 0;
	if (sign) {
		intensity++;
		if (intensity == 255) 
			sign = 0; 
	}
	else {
		intensity--;
		if (intensity == 0)
			sign = 1;
	}

	while (i < LEDCount){
		if ((i % 3) == 0) {  // First LED, and every third after that
			value.b = 0; 
			value.g = 0; 
			value.r = intensity; // RGB Value -> Red Only
			LED.set_crgb_at(i, value); // Set value at LED found at index 0
		}
		else if ((i % 3) == 1) { // Second LED, and every third after that
			value.b = 0; 
			value.g = intensity; 
			value.r = 0; // RGB Value -> Green Only
			LED.set_crgb_at(i, value); // Set value at LED found at index 0
		}
		else  { // Third LED, and every third after that
			value.b = intensity; 
			value.g = 0; 
			value.r = 0; // RGB Value -> Blue Only
			LED.set_crgb_at(i, value); // Set value at LED found at index 0
		}
		i++;
	}

	LED.sync(); // Sends the data to the LEDs
	delay(10); // Wait (ms)
}
