#ifndef RIMOT_RF_TASK
#define RIMOT_RF_TASK
#include <stdint.h>

#include "rimot_device.h"
#include "task_def.h"

void rf_task(struct rimot_device *dev, struct task *task);


#endif