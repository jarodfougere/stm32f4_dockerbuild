#ifndef RIMOT_HUMIDITY_TASK
#define RIMOT_HUMIDITY_TASK
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#include <stdint.h>

#include "rimot_device.h"
#include "task.h"


typedef enum
{
    HUM_CTX_none = TASK_CTX_NONE,
}   HUM_CTX_t;


void humidity_task(virtualDev *dev, task_t *task);



#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_HUMIDITY_TASK */
