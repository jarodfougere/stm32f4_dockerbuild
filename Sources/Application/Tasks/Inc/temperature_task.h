#ifndef RIMOT_TEMPERATURE_TASK
#define RIMOT_TEMPERATURE_TASK
#include <stdint.h>

#include "rimot_device.h"
#include "tasks.h"


void temperature_task(struct rimot_device *dev, struct task *task);


#endif