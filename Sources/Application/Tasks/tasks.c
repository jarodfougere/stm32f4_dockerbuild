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

#include "middleware_core.h"
#include "tasks.h"

void (*taskLoop[NUM_TASKS])(struct rimot_device*, struct task*) = 
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


void task_sleep(struct task *task, uint32_t ticks)
{   
    if(task->state != TASK_STATE_asleep)
    {   
        /* transition from !asleep -> asleep */
        task->state = TASK_STATE_asleep; 

        /* set the tick value for task to wakeup */
        task->wakeup_tick = get_tick() + ticks; 
    }
    else if(task->wakeup_tick == get_tick()) /* check for wakeup condition */
    {   
        /* return to ready state upon countdown expiry */
        task->state = TASK_STATE_ready;
    }
}