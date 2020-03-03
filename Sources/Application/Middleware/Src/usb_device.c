#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceFS;

extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

/**
  * @brief Init STM32 USB device Library, 
  * add supported class and pass device descriptor fields.
  * @retval None
  */
void MX_USB_DEVICE_Init(void)
{   
    /* for some reason USB causes hardfault without this. 
    https://community.st.com/s/question/0D50X00009XkfCR/
    stm32f429-usb-msc-enumeration-fails-in-fs-mode-connected-at-fs-pins */
    
    /* Go to USB_LL_Init in usbd_conf.c to chase the source trail yourself. It really doesn't make sense why the HW is hardfaulting. */
    hpcd_USB_OTG_FS.Init.dma_enable = 0; 
    
    /* Init Device Library, add supported class and start the library. */
    ASSERT(USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) == USBD_OK);

    ASSERT(USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) == USBD_OK);

    ASSERT(USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) == USBD_OK);

    ASSERT(USBD_Start(&hUsbDeviceFS) == USBD_OK);
}
