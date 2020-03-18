#ifndef RIMOT_BOOTLOADER_TASK
#define RIMOT_BOOTLOADER_TASK
#include <stdint.h>

#include "rimot_device.h"
#include "system_config.h"
#include "middleware_core.h"
#include "task_def.h"



void system_task(struct rimot_device *dev, struct task *task);

#endif