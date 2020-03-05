#ifndef RIMOT_RF_TASK
#define RIMOT_RF_TASK
#include <stdint.h>

#include "analog_measurements.h"
#include "rimot_device.h"
#include "tasks.h"

void rf_task(struct rimot_device *dev, enum task_state *state);


#endif