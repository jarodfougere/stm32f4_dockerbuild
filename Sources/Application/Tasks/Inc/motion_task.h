#ifndef RIMOT_MOTION_TASK
#define RIMOT_MOTION_TASK
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#include <stdint.h>

#include "rimot_device.h"
#include "task.h"

typedef enum 
{
    MOTION_CTX_none = TASK_CTX_NONE,
}   MOTION_CTX_t;


void motion_task(struct rimot_device *dev, struct task *task);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MOTION_TASK */