#ifndef RIMOT_TASK_LOOP
#define RIMOT_TASK_LOOP
#include <stdint.h>

/* the various task indices in the task loop */
typedef enum
{
    task_index_system,
    task_index_serial,
    task_index_analytics,
    task_index_motion,
    task_index_humidity,
    task_index_rf,
    task_index_digital_input,
    task_index_relay,
    task_index_battery,
    task_index_temperature,
}   task_index_t;

/* a task can be in several states */
typedef enum
{
    TASK_STATE_init,
    TASK_STATE_blocked,
    TASK_STATE_ready,
    TASK_STATE_suspended,
}   TASK_STATE_t;

#endif