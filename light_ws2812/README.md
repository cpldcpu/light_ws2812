light_ws2812
============

Light weight library to control WS2811/WS2812 based LEDS and LED Strings for 8-Bit AVR microcontrollers.


Description
===========

This is a small Ansi-C library to control WS2811/WS2812 based RGB Leds and strings. Only the 800kHz
high-speed mode is supported. This library uses a bit-banging approach with cycle optimized assembler
innerloops. Some advantages of this approach compared to existing solutions are:

- Compatible to all AVR MCUs since it does not rely on special periphery.
- Low hardware footprint: Does not rely on any timer or the USI
- Much smaller program code: Size optimized assembler without unrolled loops (<50 bytes in most cases)
- No initialization required
- Carefully optimized to use instructions which are available on all AVR cores and have the same instruction timing across all devices.
- Supports standard AVR, reduced core AVR (Attiny 4/5/9/10/20/40) and XMEGA (untested) without special case handling.
- Arduino or C++ not required
- Clock speeds down to 4Mhz supported.

A disadvantage of this approach is that the code has to be hand optimized for each CPU clockspeed. 
However, a number of different routines are provided which support CPU clocks from 4Mhz to 16Mhz.

Usage
=====

- Add "light_ws2812.c" and "light_ws2812.h" to your project.
- Make sure optimizations are enabled in the compiler.
- Change ws2812_port and ws2812_pin in the include file according to the I/O pin you are using.
- Uncomment the #define appropiate for your clock settings. If your exact clock is not supported, 
  try a higher or lower clock setting. The WS2811 controller chip is tolerant to some timing inaccuracy.
- Set the data output register for the output pin you are using.
- Call "ws2812_sendarray" with a pointer to your LED data and the number of bytes to transmit.
  Each LED receives 3 bytes in Green-Red-Blue order. Therefore the total number of bytes should
  be three times the number of LEDs in the chain.
- Alternatively you can use ws2813_sendarray_mask, which allows to specify one or more output pins
  on the same port.
- Wait for at least 50 us before the next LED update to reset the chain.

A simple example is provided in "test_rgb_blinky.c"

Release History
================

- v0.3 2013/05/06 
	- Initial release. Thanks to "Matthias H." for testing with a longer led chain.
- v0.4 2013/05/07 
	- General clean up 
	- Some code size optimizations. Thanks to "Fallobst" for suggestions 
	- Disabled interrupts in the critical sections.
- v0.5 2013/05/20
	- Fixed timing bug from size optimization
- v0.6 2013/05/27
	- Major update: Changed all port accesses from SBI/CBI to OUT. This removes 
	a timing inconsistency between reduced core AVR and standard AVR, avoiding separate
	implementations for different cores. A disadvantage is increase register usage.
	- Added the "ws2812_sendarray_mask" function which allows to pass a bitmask for the
	 selected port. This allows controlling up to 8 independent LED strips.
	- Removed functions for interrupt handling. Avoiding interference with interrupts
	is now up to the user. 
	- 4 MHz clock speed is now also supported for standard core AVRs.
- v0.7 2013/05/28
	- Optimized timing and size of 8 and 12 Mhz routines. All routines are within 
	  datasheet specs now, expect of 9.6 Mhz which is marginally off but works under
	  all test conditions	


 Tested Combinations
 ================

| Device             | 4 MHz  | 8 MHz  | 9.6 MHz | 12 MHz | 16 MHz |
| -------------       |:-------:| :-----: | :------: | :----:| :---:|
| ATtiny 85 (Standard Core )| X      |  X     |         |       |  X   | 
| ATtiny 13 (Standard Core)|        |        |    X    |       |     | 
| ATmega 8 (Standard Core)|        |        |         |   X    |     | 
| ATtiny 10 (Reduced Core)| X      |  X     |         |       |     | 

Please find updates on https://github.com/cpldcpu/light_ws2812

bug reports etc: cpldcpu@gmail.com







