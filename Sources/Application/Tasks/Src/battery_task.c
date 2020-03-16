/**
 * @file battery_task.c
 * @author Carl Mattatall
 * @brief  This module gathers battery voltage or RF data using the analog
 *  measurements interface module
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "battery_task.h"
#include "analog_measurements.h"



void battery_task(  struct rimot_device *dev, struct task *task)
{   
    switch(task->state)
    {
        case TASK_STATE_init:
            adc_init();

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
