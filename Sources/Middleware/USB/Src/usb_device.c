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

#include "drivers.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "usbd_desc.h"
#include "usb_device.h"

USBD_HandleTypeDef hUsbDeviceFS;


static void usb_device_error_handler(void);


static void usb_device_error_handler(void)
{
    while(1)
    {
        /* hang forever */
    }
}


/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
void MX_USB_DEVICE_Init(void)
{
    
    /* Init Device Library, add supported class and start the library. */
    if(USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
    {
        usb_device_error_handler();
    }

    if(USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
    {
        usb_device_error_handler();
    }

    if(USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK)
    {
        usb_device_error_handler();
    }

    if(USBD_Start(&hUsbDeviceFS) != USBD_OK)
    {
        usb_device_error_handler();
    }
}