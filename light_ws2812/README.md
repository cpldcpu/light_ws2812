light_ws2812
============

Light wight library to control WS2811/WS2812 based LEDS and LED Strings for 8-Bit AVR microcontrollers.



Description
===========

This is a small Ansi-C library to control WS2811/WS2812 based RGB Leds and strings. Only the 800kHz
high-speed mode is supported. This library uses a bit-banging approach with cycle optimized assembler
innerloops. Some advantages of this approach compared to existing solutions are:

- Compatible to all AVR MCUs since it does not rely on special periphery.
- Low hardware footprint: Does not rely on any timer or the USI
- Low software footprint: Size optimized assembler without unrolled loops (<50 bytes in most cases)
- No configuration needed
- Supports reduced core AVR such as Attiny 4/5/9/10
- Arduino or C++ not required

A disadvantage of this approach is that the code has to be hand optimized for each cpu clock. However,
a number of different routines are provided with support cpu clocks from 8Mhz to 16Mhz (standard AVR)
or 4MHz to 8Mhz (reduced core).

Usage
=====

- Add "light_ws2812.c" and "light_ws2812.h" to your project
- Change ws2812_port and ws2812_pin in the include file according to the I/O pin you are using.
- Uncomment the #define appropiate for your CPU core and clock settings. If your exact clock is
  not supported, try a higher or lower clock setting. The WS2811 controller chip is tolerant to
  some timing inaccuracy.
- Please use at least optimizations settings -O1 to compile.

A simple example is provided as "test_rgb_blinky.c"

Release History
================

v0.3 2013/05/06 - Initial release

Please find updates on https://github.com/cpldcpu/light_ws2812

bug reports etc: cpldcpu@gmail.com







