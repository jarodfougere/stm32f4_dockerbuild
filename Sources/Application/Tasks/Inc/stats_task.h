#ifndef RIMOT_ANALYTICS_TASK
#define RIMOT_ANALYTICS_TASK
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>

#include "rimot_device.h"
#include "task.h"


typedef enum
{
    STATS_CTX_none = TASK_CTX_NONE,
}   STATS_CTX_t;



void analytics_task(virtualDev *dev, task_t *task);


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_ANALYTICS_TASK */
