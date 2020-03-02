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
#include "debug.h"

#if defined(MCU_APP)
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "usb_device.h"


#endif /* MCU_APP */

#endif /* RIMOT_DRIVERS */