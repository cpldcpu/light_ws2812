/*
 * light weight APA102 lib include
 *
 * Initial version  - Nov 30th, 2014
 * Author: Tim (cpldcpu@gmail.com) 
 *
 * Please do not change this file! All configuration is handled in "apa102_config.h"
 *
 * License: GNU GPL v2 (see License.txt)
 */ 

#ifndef LIGHT_APA102_H_
#define LIGHT_APA102_H_

#include <avr/io.h>
#include <avr/interrupt.h>

///////////////////////////////////////////////////////////////////////
// Define I/O pins
// Clk and Data have to be connected to the same port
///////////////////////////////////////////////////////////////////////

#if !defined(apa102_port)
#define apa102_port B     // Data and clk port
#endif
#if !defined(apa102_data)
#define apa102_data 0    // Data out pin
#endif
#if !defined(apa102_clk)
#define apa102_clk  2    // Clk out pin
#endif

///////////////////////////////////////////////////////////////////////
// Define color byte order
//
// Define APA102_BYTE_ORDER_GBR if byte order is not standard BGR.
///////////////////////////////////////////////////////////////////////

#if defined(APA102_BYTE_ORDER_GBR)
struct cRGB { uint8_t g; uint8_t b; uint8_t r; };   // GBR
#else
struct cRGB { uint8_t b; uint8_t g; uint8_t r; };   // BGR (APA102 Standard)
#endif

/* User Interface
 * 
 * Input:
 *         ledarray:           An array of RGB  data describing the LED colors
 *         number_of_leds:     The number of LEDs to write
 *		   brightness:		   Set global brightness value (0-31)
 *
 * The functions will perform the following actions:
 *         - Set the data-out pin as output
 *         - Send out the LED data 
 */

void apa102_setleds   	  		  (struct cRGB *ledarray, uint16_t number_of_leds);
void apa102_setleds_brightness    (struct cRGB *ledarray, uint16_t number_of_leds,uint8_t brightness);

/*
 * Internal defines
 */
#if !defined(CONCAT)
#define CONCAT(a, b)            a ## b
#endif

#if !defined(CONCAT_EXP)
#define CONCAT_EXP(a, b)   CONCAT(a, b)
#endif

#define apa102_PORTREG  CONCAT_EXP(PORT,apa102_port)
#define apa102_DDRREG   CONCAT_EXP(DDR,apa102_port)

#endif /* LIGHT_APA102_H_ */
