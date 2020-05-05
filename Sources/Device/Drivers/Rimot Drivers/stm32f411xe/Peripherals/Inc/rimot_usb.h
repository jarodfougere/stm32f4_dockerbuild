#ifndef RIMOT_MCU_USB_OTG_CONFIG
#define RIMOT_MCU_USB_OTG_CONFIG
#ifdef __cplusplus
extern "C" {
#endif /* C linkage*/
#if defined(MCU_APP)

#include <stdint.h>
#include <stdlib.h> /* Size_t */

#if !defined(USE_HAL_DRIVER)

#include "rimot_register_field_sizes.h"

/**
 * @fn usbDriver_setDelayFunc
 * @brief register a function pointer that generates a blocking delay
 * with the USB driver layer
 *
 * @param delayFunc the function ptr to register.
 */
void usbDriver_setDelayFunc(void (*delayFunc)(uint32_t));

/**
 * @fn USBD_Delay
 * @brief Execute a blocking delay with the USB driver's registered delay
 * function
 *
 * @param ms the blocking period in milliseconds
 */
void USBD_Delay(uint32_t ms);

/* Anonymous declarations */
typedef struct usbProtocolDriverStruct usbProtocolDriver;
typedef void *                         usbClassDriverPtr;

/**
 * @brief Constructs an instance of usbProtocolDriver
 * at runtime (runtime is used to allow for anon declaration)
 * @param usbClassDriverPtr the class implementation handle
 * @return usbProtocolDriver the low-level USB 2.0 driver handle
 */
usbProtocolDriver *usbProtocolDriverInit(usbClassDriverPtr class);

/**
 * @brief Execute the sequence to configure the USB peripheral as a USB device
 * enumerated with a registered session on a host USBdevice node tree.
 * @param driver the low-level driver that implements USB 2.0 protocl
 * @return uint32_t retval. 0 for success.
 */
uint32_t usbDeviceInit(usbProtocolDriver *driver);

#endif /* USE_HAL_DRIVER */

#endif /* MCU_APP */
#ifdef __cplusplus
}
#endif /* C linkage*/
#endif /* RIMOT_MCU_USB_OTG_CONFIG */
