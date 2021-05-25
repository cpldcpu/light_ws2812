/*
 * light weight WS2812 lib - ARM Cortex M0/M0+ version
 *
 * Created: 07.07.2013
 *  Author: Tim (cpldcpu@gmail.com)
 */

#ifndef LIGHT_WS2812_H_
#define LIGHT_WS2812_H_

#ifdef __cplusplus
 extern "C" {
#endif

///////////////////////////////////////////////////////////////////////
// User defined area: CPU specific CMSIS include
///////////////////////////////////////////////////////////////////////

#if defined(LIGHT_WS2812_UC_LPC8XX)
  #include "LPC8XX.h"
  #define LIGHT_WS2812_LPC
#elif defined(LIGHT_WS2812_UC_STM32L0XX)
  #include "stm32l0xx_hal.h"
  #define LIGHT_WS2812_STM32
#elif defined(LIGHT_WS2812_UC_FSL)
  #include "fsl_port.h"
  #include "fsl_gpio.h"
  #define LIGHT_WS2812_FSL
#elif defined(LIGHT_WS2812_UC_XMC4500)
  #include "xmc_gpio.h"
  #include <stdint.h>
  #define LIGHT_WS2812_GPIO_PIN 2
  #define LIGHT_WS2812_XMC4500
#elif defined(LIGHT_WS2812_UC_XMC1100)
  #include "xmc_gpio.h"
  #include <stdint.h>
  #define LIGHT_WS2812_GPIO_PIN 2
  #define LIGHT_WS2812_XMC1100
#else
#error "Error: Please define WS2812_UC_XXXXX"
#endif

///////////////////////////////////////////////////////////////////////
// User defined area: Define I/O pin
///////////////////////////////////////////////////////////////////////

// Data port and pin definition for your CPU. Depending on the way
// port access is implemented in your Cortex CPU, the set and clr
// mask and addresses may be the same.
#ifdef LIGHT_WS2812_LPC
  // This example is for the NXP LPC81X
  #define ws2812_port_set ((uint32_t*)&LIGHT_WS2812_GPIO_PORT->SET0)	// Address of the data port register to set the pin
  #define ws2812_port_clr ((uint32_t*)&LIGHT_WS2812_GPIO_PORT->CLR0)	// Address of the data port register to clear the pin

  #define ws2812_mask_set  (1 << LIGHT_WS2812_GPIO_PIN)		// Bitmask to set the data out pin
  #define ws2812_mask_clr  (1 << LIGHT_WS2812_GPIO_PIN)		// Bitmask to clear the data out pin
#endif
#ifdef LIGHT_WS2812_STM32
  // This example is for STM32 family
  #define ws2812_port_set ((uint32_t*)&LIGHT_WS2812_GPIO_PORT->BSRR)  // Address of the data port register to set the pin
  #define ws2812_port_clr ((uint32_t*)&LIGHT_WS2812_GPIO_PORT->BRR) // Address of the data port register to clear the pin

  #define ws2812_mask_set  LIGHT_WS2812_GPIO_PIN   // Bitmask to set the data out pin
  #define ws2812_mask_clr  LIGHT_WS2812_GPIO_PIN   // Bitmask to clear the data out pin
#endif
#ifdef LIGHT_WS2812_FSL
  // This example is for Freescale family
  #define ws2812_port_set ((uint32_t*)&LIGHT_WS2812_GPIO_PORT->PSOR)  // Address of the data port register to set the pin
  #define ws2812_port_clr ((uint32_t*)&LIGHT_WS2812_GPIO_PORT->PCOR) // Address of the data port register to clear the pin

  #define ws2812_mask_set  (1 << LIGHT_WS2812_GPIO_PIN)		// Bitmask to set the data out pin
  #define ws2812_mask_clr  (1 << LIGHT_WS2812_GPIO_PIN)		// Bitmask to clear the data out pin
#endif
#ifdef LIGHT_WS2812_XMC4500
  // This example is for XMC family
  #define ws2812_port_set  ( (uint32_t*)(&((XMC_GPIO_PORT_t *)PORT1_BASE)->OUT) ) // Address of the data port register to set the pin
  #define ws2812_port_clr  ws2812_port_set                                        // Address of the data port register to clear the pin

  #define ws2812_mask_set  (1 << LIGHT_WS2812_GPIO_PIN)  // Bitmask to set the data out pin
  #define ws2812_mask_clr  (0 << LIGHT_WS2812_GPIO_PIN)  // Bitmask to clear the data out pin
#endif
#ifdef LIGHT_WS2812_XMC1100
  // This example is for XMC family
  #define ws2812_port_set  ( (uint32_t*)(&((XMC_GPIO_PORT_t *)PORT1_BASE)->OUT) ) // Address of the data port register to set the pin
  #define ws2812_port_clr  ws2812_port_set                                        // Address of the data port register to clear the pin

  #define ws2812_mask_set  (1 << LIGHT_WS2812_GPIO_PIN)  // Bitmask to set the data out pin
  #define ws2812_mask_clr  (0 << LIGHT_WS2812_GPIO_PIN)  // Bitmask to clear the data out pin
#endif
///////////////////////////////////////////////////////////////////////
// CPU clock speed
//
// The current implementation of the sendarray routine uses cycle accurate
// active waiting. The routine is automatically adjusted according to
// the clockspeed defined below. Only values between 8 Mhz and 60 Mhz
// are allowable.
//
// Important: The timing calculation assumes that there are no waitstates
// for code memory access. If there are waitstates you may have to reduce
// the value below until you get acceptable timing. It is highly recommended
// to use this library only on devices without flash waitstates and
// predictable code execution timing.
///////////////////////////////////////////////////////////////////////

#ifndef F_CPU
	#error "Error: F_CPU (CPU clock speed) is not defined"
#endif

#if (F_CPU<8000000)
	#error "Minimum clockspeed for ARM ws2812 library is 8 Mhz!"
#endif

#if (F_CPU>60000000)
	#error "Maximum clockspeed for ARM ws2812 library is 60 Mhz!"
#endif


///////////////////////////////////////////////////////////////////////
// Main function call
//
// Call with address to led color array (order is Green-Red-Blue)
// Numer of bytes to be transmitted is leds*3
///////////////////////////////////////////////////////////////////////

void ws2812_sendarray(uint8_t *ledarray,int length);

#ifdef __cplusplus
}
#endif

#endif /* LIGHT_WS2812_H_ */
