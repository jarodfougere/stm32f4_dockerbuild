#ifndef RIMOT_TASK_LOOP
#define RIMOT_TASK_LOOP
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */
#include <stdint.h>

#include "task_def.h"

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
#define NUM_TASKS 10

/**
 * @brief Put a task to sleep for a given number of ticks.
 * This is non-blocking. Task state automatically returns to ready
 * After the number of sleep ticks has expired.
 * 
 * @param task The task to sleep
 * @param ticks Number of ticks to sleep for.
 */
void task_sleep(struct task *task, uint32_t ticks);


/**
 * @brief Change a task's state to ready.
 * If the task was sleeping, its sleep tick is also cleared.
 * @param task the task to wakeup
 */
void task_wakeup(struct task *task);


/**
 * @brief Assign a callback function to a task.
 * 
 * @param task 
 * @param evt_cb 
 * @return int 
 */
int assign_task_evt_cb(struct task *task, void (*evt_cb)(void*));




#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* RIMOT_TASK_LOOP */