#ifndef RIMOT_BATTERY_TASK
#define RIMOT_BATTERY_TASK
#include <stdint.h>

#include "analog_measurements.h"
#include "rimot_device.h"
#include "tasks.h"

void battery_task(struct rimot_device *dev, enum task_state *state);

#endif