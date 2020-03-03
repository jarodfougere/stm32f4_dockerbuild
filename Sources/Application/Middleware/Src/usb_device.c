#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceFS;

/**
  * @brief Init STM32 USB device Library, 
  * add supported class and pass device descriptor fields.
  * @retval None
  */
void MX_USB_DEVICE_Init(void)
{

    /* Init Device Library, add supported class and start the library. */
    if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
    {
        FORCE_ASSERT
    }
    if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
    {
        FORCE_ASSERT
    }
    if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK)
    {
        FORCE_ASSERT
    }
    if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
    {
        FORCE_ASSERT
    }
}
