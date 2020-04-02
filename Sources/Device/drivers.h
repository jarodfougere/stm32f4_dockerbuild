/**
 * @file drivers.h
 * @author your name (you@domain.com)
 * @brief Bundled drivers header to be included by middleware module
 * @version 0.1
 * @date 2020-02-27
 * 
 * @copyright Copyright Rimot.io Incorporated (c) 2020
 * @author Carl Mattatall
 */


#ifndef RIMOT_DRIVERS
#define RIMOT_DRIVERS

#if defined(MCU_APP)
#if defined(USE_HAL_DRIVER)
#include "stm32f4xx.h" /* CMSIS definitions */ 

#include "stm32f4xx_hal.h" /* stm32 hal apis */
#else
#error  drivers.h does not provide alternative driver inclusion when \
        USE_HAL_DRIVER is undefined. Please update the driver module or \
        revise drivers.h
#endif

/* This bundles USB Core + CDC + DFU drivers */
#include "stm32_usb_driver_lib.h"

#endif /* MCU_APP */
/* the stm32 usb library also depends on their HAL apis */

#endif /* RIMOT_DRIVERS */