#ifndef RIMOT_USB_TASK
#define RIMOT_USB_TASK
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include "rimot_device.h"
#include "task.h"

typedef enum
{   
    /* IF THIS GETS EXECUTED THERE IS MOST LIKELY A SOFTWARE BUG */
    USB_CTX_none = TASK_CTX_NONE, 
    USB_CTX_receive,
    USB_CTX_transmit,
}   USB_CTX_t;



void usb_task(virtualDev *dev, task_t *task);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_USB_TASK */
