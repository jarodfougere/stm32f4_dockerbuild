#ifndef RIMOT_RF_TASK
#define RIMOT_RF_TASK
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#include <stdint.h>

#include "rimot_device.h"
#include "task.h"

typedef enum
{
    RF_CTX_none = TASK_CTX_NONE,
}   RX_CTX_t;

void rf_task(virtualDev *dev, task_t *task);

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_RF_TASK */
