#ifndef RIMOT_RELAY_TASK
#define RIMOT_RELAY_TASK
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#include <stdint.h>

#include "rimot_device.h"
#include "task.h"

typedef enum
{
    RELAY_CTX_none = TASK_CTX_NONE,
}   RELAY_CTX_t;


void relay_task(virtualDev *dev, task_t *task);
#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_RELAY_TASK */