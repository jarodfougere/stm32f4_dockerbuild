#ifndef RIMOT_BATTERY_TASK
#define RIMOT_BATTERY_TASK
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#include <stdint.h>

#include "rimot_device.h"
#include "task.h"

typedef enum
{
    BAT_CTX_none = TASK_CTX_NONE,
    BAT_CTX_sample,
}   BAT_CTX_t;

void battery_task(virtualDev *dev, task_t *task);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_BATTERY_TASK */