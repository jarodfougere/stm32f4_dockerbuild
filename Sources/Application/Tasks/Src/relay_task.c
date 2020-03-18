/**
 * @file relay_task.c
 * @author Carl Mattatall
 * @brief  This module handles the control of the relays using the
 *  relay_interface middleware module.
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */
#include "relay_task.h"
#include "task_core.h"




void relay_task(struct rimot_device *dev, struct task *task)
{
    switch(task->state)
    {
        case TASK_STATE_init:


            /* transition to ready after initialization */
            task->state = TASK_STATE_ready; 
            break;
        case TASK_STATE_ready:

            break;
        case TASK_STATE_asleep:
            task_sleep(task, 0);
            break;
        case TASK_STATE_blocked:

            break;
    }
}
