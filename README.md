light_ws2812 V2.5
============

Light weight library to control WS2812 based LEDS and LED Strings on 8-Bit AVR and ARM microcontrollers. The new version 2 of this library supports a simplified interface and arbitrary CPU clock. V2.1 finally adds Arduino support.

[See the library in action on a LPC810](http://www.youtube.com/watch?v=Uwxt7SuSV7Y)

**New** 
- [companion library for APA102 and SK9822 LEDs](https://github.com/cpldcpu/light_ws2812/tree/master/light_apa102_AVR)
- Added support for SK6812RGBW LED strings. See examples.
 
**Supported Devices**
- WS2811 800kHz mode, WS2812S, WS2812B, WS2812C
- WS2813: Connect BIN of the first LED to ground. 
- SK6812, SK6812RGBW
- PD9853
- APA106, APA104
- Other WS2812 clones: Untested
- APA102, APA102C, SK9822: Use dedicated library
 
Description
===========

This is a small Ansi-C library to control WS2811/WS2812 based RGB Leds and strings. Only the 800kHz
high-speed mode is supported. This library uses a bit-banging approach with cycle optimized assembler
innerloops. Some advantages of this approach compared to other solutions are:

- Compatible to all AVR MCUs since it does not rely on special periphery.
- The code timing is automatically adjusted to the CPU clock at compile time.
- A CPU clock speed of 8 MHz and up is recommended.
- Much smaller program code: Size optimized assembler without unrolled loops (<50 bytes in most cases)
- Supports standard AVR, reduced core AVR (Attiny 4/5/9/10/20/40) and XMEGA (untested) without special case handling.
- Experimental Cortex-M0 ARM support.

The timing values used in the library were adjusted to work on all devices. Look [here](http://cpldcpu.wordpress.com/2014/01/14/light_ws2812-library-v2-0-part-i-understanding-the-ws2812/) and [here](http://cpldcpu.wordpress.com/2014/01/19/light_ws2812-library-v2-0/) for details.

Usage C - Interface
===================

- Add "light_ws2812.c", "light_ws2812.h" and "ws2812_config.h" to your project. 
- Optionally update `ws2812_config.h` according to your I/O pin, and include it before
  including `light_ws2812.h`. Otherwise, the defaults in `light_ws2812.h` will
  be used.
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
- In case of ATtiny85/45/25, library works with [ATtiny "Classic" Core](https://github.com/SpenceKonde/ATTinyCore). Tested with Arduino IDE 1.6.7 and ATtiny Classic 1.0.6 and 8MHz internal oscillator, B.O.D disabled. 

Usage C++ - Interface
=====================
- Add "light_ws2812.cpp", "WS2812.cpp" and "WS2812.h" from the Arduino folder to your project.
- Refer to the header WS2812.h to determine how to use the class.
- Ports and LED-Count are handled dynamically, so you can add as many LED-Strips as you got free outpupt ports! 

Usage `platformio`
==================

For `arduino` and pure C implementations, the library supports `platformio`.
By default, `light_ws2812_Arduino` will be used. If `arduino` is not used,
i.e. the code is written pure C without `arduino`, define one of `build_flags`
in `platformio.ini`.

| Flag               | Library            |
|--------------------|--------------------|
| `LIGHT_WS2812_AVR` | `light_ws2812_AVR` |
| `LIGHT_APA102_AVR` | `light_apa102_AVR` |

Here is an example `platformio.ini` for `attiny85` and `nanoatmega328` without
`arduino`.

```ini
[common]
platform = atmelavr
build_flags = -DLIGHT_APA102_AVR
lib_deps = https://github.com/cpldcpu/light_ws2812.git
upload_port = /dev/cuaU0

[env:attiny85]
board = attiny85
platform = ${common.platform}
lib_deps = ${common.lib_deps}
build_flags = ${common.build_flags}

# with ArduinoISP programmer
upload_port = ${common.upload_port}
upload_speed = 19200
upload_protocol = stk500v1
upload_flags =
    -P$UPLOAD_PORT

[env:nanoatmega328]
board = nanoatmega328
platform = ${common.platform}
lib_deps = ${common.lib_deps}
build_flags = ${common.build_flags}
upload_port = ${common.upload_port}
```

All examples under [examples](examples) directory are built by `platformio`.

Troubleshooting 
================
Please note that incorrect timing is rarely the source of problems. If you want to save some time, go through the items below before altering the library.

#### None or only a part of the string is lighting up ####

 * Did you pass the correct array size in the function call?
 * Is the pin configuration correct?
 * Is anything else connected to the output pin you are using? Some development boards have LEDs connected to various pins.
 * Did you choose the correct CPU frequency setting? Did you initialize the clock correctly?

#### The LEDs are flickering and are not showing the intended color ####

 * This is often a problem with insufficient current sourcing capability.
 * Are you using a bypass capacitor for each LEDs as indicated in the datasheet? Not using a bypass capacitor will lead to erroneous behaviour. 
 * You may have to add an additional electrolytic capacitor at the input of your LED strip if you use long power supply lines.
 * Is your power supply able to supply the required current-level? If set to white at maximum brightness, each LED will draw 60mA. A single USB-Port is barely able to supply 10 LEDs.
 * The LEDs only display white: This can happen if the actual clock frequency of your MCU is lower than that given in F_CPU to the code.

Release History
================

- v2.0b 2014/01/19
	- Initial release of V2 lib with new interface and architecture.
- v2.1 2014/03/08
	- Added Arduino and C++ support courtesy of Matthias Riegler (@xvzf) 		
- v2.2 2014/11/30
	- Improved Ardunio version with variable color order, courtesy of Windell Oskay (@oskay)
	- Fixed a bug where the other bits of the port were trashed in Arduino version.
- v2.3 2015/11/29
	- Added support for SK6812RGBW LEDs. Please see example folder for usage.
- v2.4 2016/11/27
	- Increased waittime to support WS2813 LEDs
- v2.4x 2021 
	- Many smaller updates and fixed, please check commit history
- v2.5 2023/11/18
    - Changed AVR library to use direct memory access instead of "OUT". This should fix issues on newer AVR devices. As a side effect, 
	4 MHz operation is no longer supported.
	- Updated Arduino library archive
	- Fixed an issue where the config include was not used


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
| ATmega 32u4 (Standard Core)|        |        |         |   X    |  X   |  X  |


Tested Combinations Arduino
================

| Device             | 4 MHz  | 8 MHz  | 9.6 MHz | 12 MHz | 16 MHz | 20 Mhz |
| -------------       |:-------:| :-----: | :------: | :----:| :---:| :---:|
| Arduino Uno |       |   X   |         |       |  X   |    |
| Arduino Mega 2560 |        |        |        |       |    X    |    |
| Arduino Nano |        |        |        |       |    X    |    |


Tested Combinations ARM
================
|         Device         | 12 MHz | 16 MHz | 20 MHz | 30 MHz | 32 MHz |
|:----------------------:|:------:|:------:|:------:|:------:|--------|
|   LPC810 (Cortex M0+)  |    X   |        |    X   |    X   |        |
| STL32L052 (Cortex M0+) |        |    X   |        |        |        |
|   KW36Z (Cortex M0+)   |        |        |        |        | X      |   

Please find updates on https://github.com/cpldcpu/light_ws281
