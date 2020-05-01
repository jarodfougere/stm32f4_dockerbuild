#ifndef RIMOT_MCU_USB_OTG_CONFIG
#define RIMOT_MCU_USB_OTG_CONFIG
#ifdef __cplusplus
extern "C"
{
#endif /* C linkage*/
#if defined(MCU_APP)

#include <stdlib.h> /* Size_t */
#include <stdint.h>
#include "rimot_register_padding.h"
#include "rimot_LL_debug.h"

    /* COMMENT THIS OUT TO USE A CUSTOM DRIVER */
    /**
 * @fn usbInjectDelayFunc
 * @brief Registera function pointer that generates a blocking delay 
 * with the USB driver layer
 * 
 * @param delayFunc the function ptr to register.
 */
    void usbInjectDelayFunc(void (*delayFunc)(uint32_t));

    /**
 * @fn USBD_Delay
 * @brief Execute a blocking delay with the USB driver's registered delay
 * function
 * 
 * @param ms the blocking period in milliseconds 
 */
    void USBD_Delay(uint32_t ms);

    typedef __packed struct __usb_reg_overlay USB_t;

#endif /* MCU_APP */
#ifdef __cplusplus
}
#endif /* C linkage*/
#endif /* RIMOT_MCU_USB_OTG_CONFIG */
