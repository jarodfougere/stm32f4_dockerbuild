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
#define NUM_TASKS 10

/* a task can be in several states */
enum task_state
{
    TASK_STATE_init,
    TASK_STATE_blocked,
    TASK_STATE_ready,
    TASK_STATE_asleep,
};   


struct task
{
    enum task_state state;
    uint32_t wakeup_tick;
};


/**
 * @brief Put a task to sleep for a given number of ticks.
 * This is non-blocking. Task state automatically returns to ready
 * After the number of sleep ticks has expired.
 * 
 * @param task The task to sleep
 * @param ticks Number of ticks to sleep for.
 */
void task_sleep(struct task *task, uint32_t ticks);


#endif