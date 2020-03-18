#ifndef RIMOT_MOTION_TASK
#define RIMOT_MOTION_TASK
#include <stdint.h>

#include "rimot_device.h"
#include "task_def.h"



void motion_task(struct rimot_device *dev, struct task *task);


#endif