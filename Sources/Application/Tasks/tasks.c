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

#include "tasks.h"

void (*taskLoop[NUM_TASKS])(struct rimot_device*, enum task_state*) = 
{
    [task_index_system] = &system_task,
    [task_index_serial] = &serial_task,
    [task_index_analytics] = &analytics_task,
    [task_index_battery] = &battery_task,
    [task_index_digital_input] = &digital_input_task,
    [task_index_humidity] = &humidity_task,
    [task_index_motion] = &motion_task,
    [task_index_relay] = &relay_task,
    [task_index_rf] = &rf_task,
    [task_index_temperature] = &temperature_task,
};

