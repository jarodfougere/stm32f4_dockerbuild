#ifndef RIMOT_COMMAND_PARSE
#define RIMOT_COMMAND_PARSE
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include "rimot_device.h"
#include "tasks.h"




void serial_task(struct rimot_device *dev, enum task_state *state);
#endif