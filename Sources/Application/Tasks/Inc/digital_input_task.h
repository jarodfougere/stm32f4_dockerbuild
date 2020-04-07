#ifndef RIMOT_DIGITAL_INPUT_TASK
#define RIMOT_DIGITAL_INPUT_TASK
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#include <stdint.h>

#include "rimot_device.h"
#include "task.h"

typedef enum
{
    INPUT_CTX_none = TASK_CTX_NONE,
}   INPUT_CTX_t;

void digital_input_task(virtualDev *dev, task_t *task);



#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_DIGITAL_INPUT_TASK */