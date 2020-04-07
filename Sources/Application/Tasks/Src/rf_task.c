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
#include "task.h"




void rf_task(virtualDev *dev, task_t *task)
{   
    switch(taskGetState(task))
    {
        case TASK_STATE_init:
        {
            rfIF_init();
            taskSetState(task, TASK_STATE_enumerating);
        }
        break;
        case TASK_STATE_enumerating:
        {
            if(DEVICE_STATE_active == devGetState(dev))
            {
                taskSetState(task, TASK_STATE_ready);
            }
        }
        break;
        case TASK_STATE_ready:
        {
        }
        break;
        case TASK_STATE_err:
        {

        }
        break;
        case TASK_STATE_blocked:
        {

        }
        break;
    }
}
