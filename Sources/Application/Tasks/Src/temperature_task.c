/**
 * @file temperature_task.c
 * @author Carl Mattatall
 * @brief This module is responsible for gathering and processing temperature
 * measurements using the temperature_interface middleware module
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "temperature_task.h"

#ifndef NDEBUG
#include "usb_middleware.h"
#endif

void temperature_task(struct rimot_device *dev, enum task_state *state)
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