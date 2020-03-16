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
#include "usb_status_handler.h"

USBD_HandleTypeDef hUsbDeviceFS;


#ifdef MCU_APP
#ifdef USE_HAL_DRIVER
/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
void MX_USB_DEVICE_Init(void)
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






