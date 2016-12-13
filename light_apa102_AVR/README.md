light_apa102 v1.1
============

Light weight library to control APA102 and SK9822 based LEDS and LED Strings on 8-Bit AVR microcontrollers. This is a companion library to the light_weight_ws2812 library and uses an identical interface. 

To convert your code from the light\_ws2812 lib to the light\_apa102 lib simply do a search and replace of "ws2812" with "apa102".  

Description
===========

This is a small Ansi-C library to control APA102 based RGB LEDs and strings. This library uses a software based SPI implementation for maximum compatibility. If you want maximum performance, you should build your own hardware-SPI based version.

- Compatible to all AVR MCUs since it does not rely on special periphery.
- Arbitrary CPU clock

Please see the following article for more background on controlling the APA102: [Understanding the APA102](https://cpldcpu.wordpress.com/2014/11/30/understanding-the-apa102-superled/)

See here for a write-up on the changes to improve compatibility to the SK9822: [SK9822](https://cpldcpu.com/2016/12/13/sk9822-a-clone-of-the-apa102/)

Usage C - Interface
===================

- Add "light\_apa102.c", "light\_apa102.h" and "apa102_config.h" to your project. 
- Update "apa102\_config.h" according to your I/O pin.
- Call "apa102\_setleds" with a pointer to the LED array and the number LEDs.

Examples are provided in the [Examples](https://github.com/cpldcpu/light_ws2812/tree/master/light_apa102_AVR/Examples) folder. You can build them with the supplied makefile.

Release History
================

- v1.0b 2014/11/30 
	- Initial release
- v1.1 2016/11/27 
	- Added reset frame to fix SK9822 update issue. Changed reset frame to 0x000000.
	- Added **apa102_setleds_brightness** function which allows to set global brightness as well.

Tested Combinations AVR
================

| Device             | 4 MHz  | 8 MHz  | 9.6 MHz | 12 MHz | 16 MHz | 20 Mhz |
| -------------       |:-------:| :-----: | :------: | :----:| :---:| :---:|
| ATtiny 85 (Standard Core )|        |        |         |       |  X   |    |

Please find updates on https://github.com/cpldcpu/light_ws2812

bug reports etc: cpldcpu@gmail.com

