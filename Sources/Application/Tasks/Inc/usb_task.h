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

    USB_CTX_cdc,     
    USB_CTX_dfu,     
    USB_CTX_ins,     
    USB_CTX_outs,    
    USB_CTX_bats,    
    USB_CTX_hum,     
    USB_CTX_temp,    
    USB_CTX_motion,  
    USB_CTX_sys,     
    USB_CTX_rf,     
    USB_CTX_stats,
    USB_CTX_timing,
}   USB_CTX_t;



void serial_task(struct rimot_device *dev, struct task *task);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_USB_TASK */