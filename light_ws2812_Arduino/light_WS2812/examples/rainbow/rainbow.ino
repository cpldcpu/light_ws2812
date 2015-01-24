// use the cRGB struct hsv method
#define USE_HSV

#include <WS2812.h>

#define LEDCount 10
#define outputPin 7

WS2812 LED(LEDCount); 
cRGB value;

int h = 0;   //stores 0 to 614
byte steps = 15; //number of hues we skip in a 360 range per update

byte sat = 255;
byte val = 127;

long sleep = 100; //delays between update
  
void setup() {
  LED.setOutput(outputPin);
}

void loop() {
  Cycle();
  
  for(int i = 0; i < LEDCount; i++)
  {
      LED.set_crgb_at(i, value);
  }
  // Sends the data to the LEDs
  LED.sync();
  
  delay(sleep);
}

void Cycle()
{
  value.SetHSV(h, sat, val);
  
  h += steps;  
  if(h > 360)
  {
      h %= 360;
  }
}
