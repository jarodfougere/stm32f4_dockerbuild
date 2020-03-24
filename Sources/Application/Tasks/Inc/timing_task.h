#ifndef RIMOT_TIMING_TASK
#define RIMOT_TIMING_TASK
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>

#include "rimot_device.h"
#include "task.h"


typedef enum
{   
    /* IF THIS GETS EXECUTED THERE IS MOST LIKELY A SOFTWARE BUG */
    TIM_CTX_none = TASK_CTX_NONE, 

    TIM_ctx_usb,
    TIM_CTX_ins,     
    TIM_CTX_outs,    
    TIM_CTX_bats,    
    TIM_CTX_hum,     
    TIM_CTX_temp,    
    TIM_CTX_motion,  
    TIM_CTX_sys,     
    TIM_CTX_rf,     
    TIM_CTX_stats,   
}   TIM_CTX_t;




void timing_task(struct rimot_device *dev, struct task *task);




#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_TIMING_TASK */