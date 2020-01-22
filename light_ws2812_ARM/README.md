light_ws2812_ARM - beta
============

Light weight library to control WS2811/WS2812 based LEDS and LED Strings on ARM Cortex microcontrollers.
This library uses a bitbanging approach with active CPU waiting. This approach allows good compatibility
to all ARM based devices in addition to a low software and hardware footprint. It does, however, rely on cycle
exact code execution timing. Therefore this library will fail if you have waitstates during code memory
access. If you want to use a highly clocked cortex core with multiple memory waitstates, I would recommend
to use a hardware based WS2812 controller approach. 

**This is still experimental and has only been tested on Cortex-M0**

[See the library in action on a LPC810](http://www.youtube.com/watch?v=Uwxt7SuSV7Y)

Usage
=====

- Add "light_ws2812_cortex.c" and "light_ws2812_cortex.h" to your project.
- Make sure optimizations are enabled in the compiler.
- Change i/o pin settings according to the I/O pin you are using:
  - Define `LIGHT_WS2812_GPIO_PIN=XXX`
  - Define `LIGHT_WS2812_GPIO_PORT=XXX`
- Add the correct CMSIS include for your CPU:
  - Define `LIGHT_WS2812_UC_LPC8XX`, `LIGHT_WS2812_UC_STM32L0XX` or add your CPU in "light_ws2812_cortex.h"
- Set `F_CPU` to your CPU core clock.
- Set code memory wait states to zero. **Important:** The library will not work if there are one or more code memory waitstate cycles. This may limit your code clock to 30 Mhz or lower on most Cortex-M0 controllers.
- Call "ws2812_sendarray" with a pointer to your LED data and the number of bytes to transmit.
  Each LED receives 3 bytes in Green-Red-Blue order. Therefore the total number of bytes should
  be three times the number of LEDs in the chain.
- Wait for at least 50 us before the next LED update to reset the chain.


Release History
================

- v0.9 2013/07/29
	- Added first version of ARM Cortex library

Tested Combinations ARM
================
|         Device         | 12 MHz | 16 MHz | 20 MHz | 30 MHz | 32 MHz |
|:----------------------:|:------:|:------:|:------:|:------:|--------|
|   LPC810 (Cortex M0+)  |    X   |        |    X   |    X   |        |
| STL32L052 (Cortex M0+) |        |    X   |        |        |        |
|   KW36Z (Cortex M0+)   |        |        |        |        | X      |

Please find updates on https://github.com/cpldcpu/light_ws2812

bug reports etc: cpldcpu@gmail.com
