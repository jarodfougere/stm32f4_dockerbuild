/**
 * @file motion_task.c
 * @author Carl Mattatall
 * @brief This module handles the gathering of motion activity data using
 * the motion_interface middleware module
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */
#include "motion_task.h"

#ifndef NDEBUG
#include "usb_middleware.h"
#endif

void motion_task(struct rimot_device *dev, enum task_state *state)
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