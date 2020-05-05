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


typedef struct usbProtocolDriverStruct usbProtocolDriver;


#endif /* USE_HAL_DRIVER */

#endif /* MCU_APP */
#ifdef __cplusplus
}
#endif /* C linkage*/
#endif /* RIMOT_MCU_USB_OTG_CONFIG */
