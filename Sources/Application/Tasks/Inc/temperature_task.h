#ifndef RIMOT_TEMPERATURE_TASK
#define RIMOT_TEMPERATURE_TASK
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#include <stdint.h>

#include "rimot_device.h"
#include "task.h"

typedef enum
{
    TEMP_CTX_none = TASK_CTX_NONE,
}   TEMP_CTX_t;

void temperature_task(virtualDev *dev, task_t *task);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_TEMPERATURE_TASK */
