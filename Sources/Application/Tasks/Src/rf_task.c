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



void rf_task(struct rimot_device *dev, enum task_state *state)
{   
    switch(*state)
    {
        case TASK_STATE_init:

            /* transition to ready after initialization */
            *state = TASK_STATE_ready; 
            break;
        case TASK_STATE_ready:

            break;
        case TASK_STATE_asleep:

        break;
        case TASK_STATE_blocked:

            break;
    }
}
