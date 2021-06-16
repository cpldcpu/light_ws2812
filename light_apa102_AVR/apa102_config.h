/*
 * light_apa102_config.h
 *
 * Created: 30.11.2014
 *
 * User Configuration file for the light_apa102_lib
 *
 */ 


#ifndef APA102_CONFIG_H_
#define APA102_CONFIG_H_

///////////////////////////////////////////////////////////////////////
// Define I/O pins
// Clk and Data have to be connected to the same port
///////////////////////////////////////////////////////////////////////

#define apa102_port B     // Data and clk port 
#define apa102_data 0    // Data out pin
#define apa102_clk  2    // Clk out pin

struct cRGB { uint8_t r; uint8_t g; uint8_t b; };

///////////////////////////////////////////////////////////////////////
// Define APA102_BYTE_ORDER_GBR if byte order is not standard BGR.
///////////////////////////////////////////////////////////////////////

#endif /* APA102_CONFIG_H_ */
