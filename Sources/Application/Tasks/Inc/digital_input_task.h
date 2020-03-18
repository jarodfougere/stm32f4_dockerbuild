#ifndef RIMOT_DIGITAL_INPUT_TASK
#define RIMOT_DIGITAL_INPUT_TASK
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "rimot_device.h"
#include "task.h"

void digital_input_task(struct rimot_device *dev, struct task *task);




#endif