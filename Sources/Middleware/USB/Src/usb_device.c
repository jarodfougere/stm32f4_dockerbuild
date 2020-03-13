/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usb_device.c
  * @version        : v1.0_Cube
  * @brief          : This file implements the USB Device base drivers
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


/**
 * @file usb_device.c
 * @author Carl Mattatall
 * @brief  This file provides additional functionality to the middleware layer
 * used by the STM32 USB Device Library.
 * @version 0.1
 * @date 2020-03-12
 * 
 * @attention
 *  Although modified, this file is licensed under the Ultimate Liberty License 
 *  SLA0044 as indicated above
 */
#if defined(MCU_APP)
#include "drivers.h" /* expose driver layer */
#else
#include <stdio.h>
#endif /* MCU_APP */

#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "usbd_desc.h"
#include "usb_device.h"

USBD_HandleTypeDef hUsbDeviceFS;

#ifdef MCU_APP
#ifdef USE_HAL_DRIVER
/**
 * @brief This function handles USBD_StatusTypeDef retvals for API calls to the
 *  Stm32 usb device peripheral driver library
 * 
 * @param status 
 */
void usb_status_handler(USBD_StatusTypeDef status)
{  
    switch(status)
    {
        case USBD_OK:
            /* do nothing */
            break;
        case USBD_BUSY:
            while(1)
            {
                /* hang forever */
            }
            break;
        case USBD_FAIL:
            while(1)
            {
                /* hang forever */
            }
            break;
        default:
        #ifndef NDEBUG
            while(1)
            {
                /* WTF IS HAPPENING?? */
            }
        #endif /* NOT DEFINED NDEBUG */
            break;
    }

}
#endif /* USE HAL DRIVER */
#endif /* MCU APP */


#ifdef MCU_APP
#ifdef USE_HAL_DRIVER
/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
static void MX_USB_DEVICE_Init(void)
{
    /* Init Device Library, add supported class and start the library. */
    usb_status_handler(USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS));
    usb_status_handler(USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS));
    usb_status_handler(USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC));

    /* cast because cdc reg is uint8_t */
    usb_status_handler((USBD_StatusTypeDef)USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS)); 
    
    usb_status_handler(USBD_Start(&hUsbDeviceFS));
}
#endif /* USE HAL DRIVER */
#endif /* MCU APP */


/**
 * @brief initializes the usb interface for the application module.
 */
void usb_init(void)
{
#if defined(MCU_APP)
    #if defined(USE_HAL_DRIVER)
    MX_USB_DEVICE_Init();
    #else
    #warning usb_init() does not provide an alternative initialization \
    method for USB peripheral drivers.
    #endif /* USE HAL DRIVER */
#else
    printf( "EXECUTED usb_init\n."
            "The USB peripheral is initialized in CDC Mode\n");
#endif /* MCU_APP */
}



