#ifndef RIMOT_USB_STATUS_HANDLER
#define RIMOT_USB_STATUS_HANDLER

#include "usbd_def.h"

#ifdef __cplusplus
extern "C" {
#endif /* c linkage */

void usb_status_handler(USBD_StatusTypeDef status);

#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* USB_STATUS_HANDLER */