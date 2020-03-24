#ifndef RIMOT_TASK_LOOP
#define RIMOT_TASK_LOOP
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */
#include <stdint.h>

#include "task.h"

/* the various task indices in the task loop */


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
 * @brief Block a task and clear its execution info
 * 
 * @param task the task to block
 */
void task_block_self(struct task *task);


#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* RIMOT_TASK_LOOP */