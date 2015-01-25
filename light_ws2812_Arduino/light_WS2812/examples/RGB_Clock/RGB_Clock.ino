/*
** Example RGB clock by Duncan Waterreus ( FreezyExp )
 **
 ** Summary:
 **
 ** This example shows you how to manage multiple strings efficiently (still using a delay instead of a sleep function)
 ** It also shows you how to set sub-pixels without needing to update the other two colours.
 **
 **
 ** Details:
 **
 ** This example will use one RGB component for seconds, one for minutes, one for hours.
 ** AM PM switches the colours around a bit.
 **
 ** If the hand is in between two numbers, it will split the 255 value between those numbers.
 **
 ** Gratuitous use of bit-logic makes this a pretty nice example
 **
 ** Why read from the pixel buffer (RGB), if you already know the exact value you want a subpixel to have? (R=12, B=?, G=?)
 ** You could read out the pixel first, then change the one field you want to update then set and sync.
 ** But... the library already has a subpixel buffer available, so writing into that directly is more efficient.
 ** Keeping track of the chains that actually update, requires much less syncs
 **
 ** Setup:
 ** Connect a jumper from Analog pin 0 to Digital Pin 2 (interrupt 0).
 ** Connect 6 chains of 2 x WS2812 to pins 3 through 8
 **
 ** TODO:
 ** - Add configuration for minutes and hours, based on user input.
 **
 ** Alternatives:
 ** - You could also rewrite the code to use a single 12 leds chain, or perhaps three 60 led chains.
 **
 **  Comment "define DEMO" to switch to realtime clock.
 */

//uncomment to let the clock run in realtime
//#define DEMO

int clockInt = 0;            // digital pin 2 is now interrupt 0
int masterClock = 0;         // counts rising edge clock signals

int maskUpdate = 0;

boolean tick = 0;

#include <WS2812.h>

#define LEDCount 2

#define BUTTON_PIN A7

//5 minute slice IDS: 
WS2812 LED1(LEDCount); // 0 1 
WS2812 LED2(LEDCount); // 2 3
WS2812 LED3(LEDCount); // 4 5
WS2812 LED4(LEDCount); // 6 7
WS2812 LED5(LEDCount); // 8 9
WS2812 LED6(LEDCount); // 10 11

int longPress = 0;

//keep this between 1 and 255
#define BRIGHTNESS 16

long Brightness(byte x)
{  
  return (long)x * (long)BRIGHTNESS / 255L; 
}

class TimePie
{
public:

  TimePie(int Max)
  {
    _max = Max -1;
    Reset();
  }

  void Reset()
  {
    value = 0;
    slice = 0;
    next_slice = 1;
    partial = 1;
  }

  int value;
  int slice;
  int next_slice;
  int partial; //0 to 5 

  int _max;

  boolean Next()
  {
    value++;

    // 5 steps in between the 12 numbers
    // at 1 led is max
    // it dims as it moves further
    // at 5 it is off    

    slice = value / 5;
    partial = (value % 5) + 1;

    next_slice = slice + 1;
    if (next_slice > 11) //only 12 steps
      next_slice = 0;

    if (value >= _max)
    {
      value = 0;
      return true;
    }
    return false;
  }
};

TimePie seconds(60);
TimePie minutes(60);
TimePie hours(60); //update 5 times an hour

boolean AM_PM = false;

void setup()
{
  //Clock PWM setup
  attachInterrupt(clockInt, clockCounter, RISING);
  //  clockInt is our interrupt, clockCounter function is called when
  //  invoked on a RISING clock edge
  analogReference(DEFAULT);
  analogWrite(2, 127);   // this starts our PWM 'clock' with a 50% duty cycle

  // RGB LED Chains setup
  LED1.setOutput(3);
  LED2.setOutput(4);
  LED3.setOutput(5);
  LED4.setOutput(6);
  LED5.setOutput(7);
  LED6.setOutput(8);

  ResetLEDS();

  //set up button
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH); // connect internal pull-up

  Serial.begin(9600);
}

void ResetLEDS()
{
  //WS2812 library needs initialization otherwise all the leds will sync to uninitialized data
  cRGB cBlack = {
    0, 0, 0     };

  LED1.set_crgb_at(0, (cRGB) {
    BRIGHTNESS, BRIGHTNESS, BRIGHTNESS
  }
  ); //clock starts at 12
  LED1.set_crgb_at(1, cBlack);

  LED2.set_crgb_at(0, cBlack);
  LED2.set_crgb_at(1, cBlack);

  LED3.set_crgb_at(0, cBlack);
  LED3.set_crgb_at(1, cBlack);

  LED4.set_crgb_at(0, cBlack);
  LED4.set_crgb_at(1, cBlack);

  LED5.set_crgb_at(0, cBlack);
  LED5.set_crgb_at(1, cBlack);

  LED5.set_crgb_at(0, cBlack);
  LED5.set_crgb_at(1, cBlack);

  LED6.set_crgb_at(0, cBlack);
  LED6.set_crgb_at(1, cBlack);

  //force all leds to update next loop
  maskUpdate = 63;
}

/*
Clock from PWM to interrupt based on code found here:
 http://www.instructables.com/id/Make-an-accurate-Arduino-clock-using-only-one-wire/
 Simple internal clock demo: by Joseph Unik aka Relic1974
 Uses analog PWM output of 490Hz with a 50% duty cycle to
 keep very accurate time ;).
 */
void clockCounter()      // called by interrupt
{
  masterClock++;        // with each clock rise add 1 to masterclock count

  if (masterClock >=
#ifdef DEMO // we want it fast
    1
#else // 490Hz reached ~1 second 
    489
#endif
    )
  {
    tick++;          // after one 490Hz cycle add 1 second ;)
    masterClock = 0;     // Reset after 1 second is reached
  }
  return;
}

void loop()
{
  boolean button_pressed = !digitalRead(BUTTON_PIN);
  if (button_pressed)
  {
    tick++;
    longPress++;
  }
  else
  {
    longPress = 0;
  }

  if (tick > 0)
  {
    tick = 0;
    HandleTime(button_pressed);

    Serial.print(hours.slice);
    Serial.print(":");
    Serial.print(minutes.value);
    Serial.print(":");
    Serial.println(seconds.value);

#ifndef DEMO	
    if (button_pressed)
#endif	
      delay(50); //too fast otherwise, which chrashes the chains/arduino
  }
}

void HandleTime(boolean button_pressed)
{
  int tmp;

  //skips seconds update if button is pressed, neat!
  if (button_pressed || seconds.Next())
  {
    if (longPress == 1)
    {
      //first reset the two active slices to 0
      maskUpdate |= SetSubpixel(seconds.next_slice, 2, 0);
      maskUpdate |= SetSubpixel(seconds.slice, 2, 0);

      //reset to the seconds to '12' == 0 seconds
      seconds.Reset();
    }

    if (minutes.Next())
    {
      //60 minutes passed
    }
    //update minutes display
    tmp = (minutes.partial * 51);
    maskUpdate |= SetSubpixel(minutes.slice, 1, Brightness(~tmp));
    maskUpdate |= SetSubpixel(minutes.next_slice, 1, Brightness(tmp));

    // hour hand should move 1 every 12 minutes (60 / 5 = 12)
    if ((minutes.value % 12) == 0)
    {
      if (hours.Next())
      {
        // 12 hours passed
        // AM_PM = !AM_PM;
      }

      // 255 brightness / 5 steps = 51 per step
      // ~ flips all bits, alternatively you can use 255-tmp
      // Brightness re maps the value to a smaller range, in case you want your clock to be a bit less bright

        //update hours display
      tmp = (hours.partial * 51);
      maskUpdate |= SetSubpixel(hours.slice, 0, Brightness(~tmp));
      maskUpdate |= SetSubpixel(hours.next_slice, 0, Brightness(tmp));
    }
  }

  //disable seconds while editing time
  if (!button_pressed)
  {
    //update seconds display
    tmp = (seconds.partial * 51);
    maskUpdate |= SetSubpixel(seconds.slice, 2, Brightness(~tmp));
    maskUpdate |= SetSubpixel(seconds.next_slice, 2, Brightness(tmp));
  }

  //use bitmask to determine which pixels we need to update
  //with an unsigned int you can use up to 32-bits, one for each string, you can easily find the correct bitmask using: 
  // 1 << bitfield
  // or 2 to the power of the bitfiled ( 2^bit )

  if ((maskUpdate & 1) > 0)
    LED1.sync();
  if ((maskUpdate & 2) > 0)
    LED2.sync();
  if ((maskUpdate & 4) > 0)
    LED3.sync();
  if ((maskUpdate & 8) > 0)
    LED4.sync();
  if ((maskUpdate & 16) > 0)
    LED5.sync();
  if ((maskUpdate & 32) > 0)
    LED6.sync();

  //everything is up to date now
  maskUpdate = 0;
}

int SetSubpixel(int id, byte subpixel, byte value)
{
  if (AM_PM)
  {
    //use other style
    switch (subpixel)
    {
    case 0:
      subpixel = 0; //hours
    case 1:
      subpixel = 1; //minutes
    case 2:
      subpixel = 2; //seconds
    }
  }

  //lets ask for a pointer to the correct LED to update
  WS2812 *p;
  int sid = 0;//id on the string

  switch (id)
  {
  default: //additional loop around protection for free :D
  case 0:
    p = &LED1;
    break;
  case 1:
    p = &LED1;
    sid = 1;
    break;
  case 2:
    p = &LED2;
    break;
  case 3:
    p = &LED2;
    sid = 1;
    break;
  case 4:
    p = &LED3;
    break;
  case 5:
    p = &LED3;
    sid = 1;
    break;
  case 6:
    p = &LED4;
    break;
  case 7:
    p = &LED4;
    sid = 1;
    break;
  case 8:
    p = &LED5;
    break;
  case 9:
    p = &LED5;
    sid = 1;
    break;
  case 10:
    p = &LED6;
    break;
  case 11:
    p = &LED6;
    sid = 1;
    break;
    break;
  }
  //using a pointer so we dont need to copy paste this six times
  p->set_subpixel_at(sid, subpixel, value);

  //get 1 << (id / 2)
  return 1 << (id >> 1);
}

