#ifndef RIMOT_SERIAL_DATA
#define RIMOT_SERIAL_DATA
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>


/**
 * @brief This function transmits data via the uart2 peripheral when in MCU mode and to the terminal when hosting the application
 * 
 * @param format 
 * @param ... 
 */
void transmit_serial(const char* restrict format, ...);

/**
 * @brief This function transmits data via the usb peripheral when in MCU mode and to the terminal when hosting the application
 * 
 * @param format 
 * @param ... 
 */
void transmit_usb(const char* restrict format, ...);



/**
 * @brief This function initializes the data comminication peripherals and 
 * Their corresponding interfaces.
 */
void init_comms_interface(void);
#endif
