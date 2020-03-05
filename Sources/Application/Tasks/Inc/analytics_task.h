#ifndef RIMOT_ANALYTICS_TASK
#define RIMOT_ANALYTICS_TASK
#include <stdint.h>
#include "rimot_device.h"
#include "tasks.h"

void analytics_task(struct rimot_device *dev, enum task_state *state);

#endif