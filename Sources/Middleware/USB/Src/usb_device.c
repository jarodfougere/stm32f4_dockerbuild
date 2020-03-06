/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usb_device.c
  * @version        : v1.0_Cube
  * @brief          : This file implements the USB Device
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
#if defined(MCU_APP)
#include "drivers.h"
#else
#include <stdio.h>
#endif /* MCU_APP */

#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "usbd_desc.h"
#include "usb_device.h"

USBD_HandleTypeDef hUsbDeviceFS;

#ifdef MCU_APP
/**
 * @brief This function handles configuration errors for the USB Peripheral on
 *  the MCU
 * 
 */
static void usb_device_error_handler(void)
{
    while (1)
    {
        /* hang forever */
    }
}
#endif /* MCU APP */


#ifdef MCU_APP
/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
static void MX_USB_DEVICE_Init(void)
{
    /* Init Device Library, add supported class and start the library. */
    if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
    {
        usb_device_error_handler();
    }

    if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
    {
        usb_device_error_handler();
    }

    if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK)
    {
        usb_device_error_handler();
    }

    if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
    {
        usb_device_error_handler();
    }
}
#endif /* MCU APP */


void usb_init(void)
{
#if defined(MCU_APP)
    MX_USB_DEVICE_Init();
#else
    printf( "EXECUTED usb_init\n."
            "The USB peripheral is initialized in CDC Mode\n");
#endif /* MCU_APP */
}



