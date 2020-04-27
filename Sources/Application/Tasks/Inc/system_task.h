#ifndef RIMOT_SYSTEM_TASK
#define RIMOT_SYSTEM_TASK
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#include <stdint.h>

#include "rimot_device.h"
#include "system_interface.h"
#include "middleware_core.h"
#include "task.h"


typedef enum
{
    SYSTEM_CTX_none = TASK_CTX_NONE,
}   SYSTEM_CTX_t;



void system_task(virtualDev *dev, task_t *task);
#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_SYSTEM_TASK */
