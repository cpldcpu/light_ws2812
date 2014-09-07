light_ws2812 V2.1
============

Light weight library to control WS2811/WS2812/WS2812B based LEDS and LED Strings on 8-Bit AVR and ARM microcontrollers. The new version 2 of this library supports a simplified interface and arbitrary CPU clock. V2.1 finally adds Arduino support.

[See the library in action on a LPC810](http://www.youtube.com/watch?v=Uwxt7SuSV7Y)

Description
===========

This is a small Ansi-C library to control WS2811/WS2812 based RGB Leds and strings. Only the 800kHz
high-speed mode is supported. This library uses a bit-banging approach with cycle optimized assembler
innerloops. Some advantages of this approach compared to other solutions are:

- Compatible to all AVR MCUs since it does not rely on special periphery.
- The code timing is automatically adjusted for CPU clock speeds from 4 Mhz up to the maximum on AVR.
- Much smaller program code: Size optimized assembler without unrolled loops (<50 bytes in most cases)
- Supports standard AVR, reduced core AVR (Attiny 4/5/9/10/20/40) and XMEGA (untested) without special case handling.
- Arduino or C++ not required
- New: Experimental Cortex-M0 ARM core.

The timing values used in the library were adjusted to work on all devices. Look [here](http://cpldcpu.wordpress.com/2014/01/14/light_ws2812-library-v2-0-part-i-understanding-the-ws2812/) and [here](http://cpldcpu.wordpress.com/2014/01/19/light_ws2812-library-v2-0/) for details.

Usage C - Interface
===================

- Add "light_ws2812.c", "light_ws2812.h" and "ws2812_config.h" to your project. 
- Update "ws2812_config.h" according to your I/O pin.
- Make sure F\_CPU is correctly defined in your makefile or the project. (For AtmelStudio: Project->Properties->Toolchain->AVR/GNU C Compiler->Symbols. Add symbol F_CPU=xxxxx)
- Call "ws2812\_setleds" with a pointer to the LED array and the number LEDs.
- Alternatively you can use "ws2812\_setleds\_pin" to control up to 8 LED strips on the same Port.

Examples are provided in the [Examples](https://github.com/cpldcpu/light_ws2812/tree/master/light_ws2812_AVR/Examples) folder. You can build them with the supplied makefile.


Usage Arduino
=============

- If you have Arduino 1.0.5 or newer, simply import the zipfile from light\_ws2812\_arduino with sketch->import library.
- Please refer to [these](http://arduino.cc/en/Guide/Libraries) instruction for older versions.
- To see how you can use it, have a look at the examples.
- Make sure the Pin you use to address the LEDs really exists! If not, the sketch won't compile or doesn't run correctly on your Arduino.


Usage C++ - Interface
=====================
- Add "light_ws2812.cpp", "WS2812.cpp" and "WS2812.h" from the Arduino folder to your project.
- Refer to the header WS2812.h to determine how to use the class.
- Ports and LED-Count are handled dynamically, so you can add as many LED-Strips as you got free outpupt ports! 


Troubleshooting 
================
Please note that incorrect timing is rarely the source of problems. If you want to save some time, go through the items below before altering the library.

None or only a part of the string is lighting up.

 * Did you pass the correct array size in the function call?
 * Is the pin configuration correct?
 * Is anything else connected to the output pin you are using? Some development boards have LEDs connected to various pins.
 * Did you choose the correct CPU frequency setting? Did you initialize the clock correctly?

The LEDs are flickering and not showing the intended colour.

 * This is usually a problem with insufficient current sourcing capability.
 * Are you using a bypass capacitor for each LEDs as indicated in the datasheet? Not using a bypass capacitor will lead to erroneous behaviour. 
 * You may have to add an additional electrolytic capacitor at the input of your LED strip if you use long power supply lines.
 * Is your power supply able to supply the required current-level? If set to white at maximum brightness, each LED will draw 60mA. A single USB-Port is barely able to supply 10 LEDs.

Release History
================

- v2.0b 2014/01/19
	- Initial release of V2 lib with new interface and architecture.
- v2.1 2014/03/08
	- Added Arduino and C++ support courtesy of Matthias Riegler (@xvzf) 		

You can find the old V1 here: https://github.com/cpldcpu/light_ws2812/tree/v1.0

Tested Combinations AVR
================

| Device             | 4 MHz  | 8 MHz  | 9.6 MHz | 12 MHz | 16 MHz | 20 Mhz |
| -------------       |:-------:| :-----: | :------: | :----:| :---:| :---:|
| ATtiny 85 (Standard Core )| X      |  X     |         |       |  X   |    |
| ATtiny 13 (Standard Core)|        |        |    X    |       |     |    |
| ATmega 8 (Standard Core)|        |        |         |   X    |  X  |    |
| ATtiny 10 (Reduced Core)| X      |  X     |         |       |     |    |
| ATmega 168 (Standard Core)|        |        |         |       |  X  |  X  |
| ATmega 32u4 (Standard Core)|        |        |         |   X    |     |  X  |


Tested Combinations Arduino
================

| Device             | 4 MHz  | 8 MHz  | 9.6 MHz | 12 MHz | 16 MHz | 20 Mhz |
| -------------       |:-------:| :-----: | :------: | :----:| :---:| :---:|
| Arduino Uno |       |       |         |       |  X   |    |
| Arduino Mega 2560 |        |        |        |       |    X    |    |


Tested Combinations ARM
================
| Device             | 12 MHz  | 20 MHz  | 30 MHz | 
| -------------       |:-------:| :-----: | :------: |
| LPC810 (Cortex M0+)| X      |  X     |    x     |    

Please find updates on https://github.com/cpldcpu/light_ws2812

bug reports etc: cpldcpu@gmail.com

