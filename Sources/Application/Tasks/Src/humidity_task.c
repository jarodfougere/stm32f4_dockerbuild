/**
 * @file humidity_task.c
 * @author Carl Mattatall
 * @brief This module handles the gathering and processing of humidity data
 * using the humidity interface middleware module
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "humidity_task.h"
#include "task_core.h"




void humidity_task(struct rimot_device *dev, struct task *task)
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
