#ifndef RIMOT_MOTION_TASK
#define RIMOT_MOTION_TASK
#include <stdint.h>

#include "rimot_device.h"
#include "tasks.h"



void motion_task(struct rimot_device *dev, enum task_state *state);


#endif