#include "analytics_task.h"
#include "battery_task.h"
#include "digital_input_task.h"
#include "motion_task.h"
#include "relay_task.h"
#include "rf_task.h"
#include "serial_task.h"
#include "system_task.h"
#include "temperature_task.h"
#include "humidity_task.h"

void (*taskLoop[])(struct rimot_device*) = 
{
    &system_task,
    &serial_task,
};

const int32_t num_tasks = sizeof(taskLoop)/sizeof(taskLoop[0]);


/* 

 &rf_task,
    &battery_task,
    digital_input_task,
    relay_task,
    temperature_task,
    motion_task,
    humidity_task,

    */

