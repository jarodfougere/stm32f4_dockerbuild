#ifndef RIMOT_HUMIDITY_TASK
#define RIMOT_HUMIDITY_TASK
#include <stdint.h>

#include "rimot_device.h"
#include "tasks.h"


void humidity_task(struct rimot_device *dev, enum task_state *state);




#endif