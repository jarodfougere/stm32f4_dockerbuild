#include <stdint.h>

#include "usb_status_handler.h"

#ifdef MCU_APP
#ifdef USE_HAL_DRIVER
/**
 * @brief This function handles USBD_StatusTypeDef retvals for API calls to the
 *  Stm32 usb device peripheral driver library
 * 
 * @param status the status of the usb peripheral
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
        #endif /* DEBUG BUILD */
            break;
    }
}
#endif /* USE HAL DRIVER */
#endif /* MCU APP */