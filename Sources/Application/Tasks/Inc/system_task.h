#ifndef RIMOT_BOOTLOADER_TASK
#define RIMOT_BOOTLOADER_TASK
#include <stdint.h>

#include "rimot_device.h"
#include "tasks.h"


void system_task(struct rimot_device *dev);

#endif