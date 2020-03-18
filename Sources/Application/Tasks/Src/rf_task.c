/**
 * @file rf_task.c
 * @author Carl Mattatall
 * @brief  This module handles acquisition and processing of RF power / SWR
 * measurements using the analog_measurements middleware module
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "rf_task.h"
#include "analog_measurements.h"
#include "tasks.h"



void rf_task(struct rimot_device *dev, struct task *task)
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
