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
#include "apa102_config.h"

/* User Interface
 * 
 * Input:
 *         ledarray:           An array of RGB  data describing the LED colors
 *         number_of_leds:     The number of LEDs to write
 *
 * The functions will perform the following actions:
 *         - Set the data-out pin as output
 *         - Send out the LED data 
 */

void apa102_setleds    (struct cRGB *ledarray, uint16_t number_of_leds);

/*
 * Internal defines
 */
#define CONCAT(a, b)            a ## b
#define CONCAT_EXP(a, b)   CONCAT(a, b)

#define apa102_PORTREG  CONCAT_EXP(PORT,apa102_port)
#define apa102_DDRREG   CONCAT_EXP(DDR,apa102_port)

#endif /* LIGHT_APA102_H_ */
