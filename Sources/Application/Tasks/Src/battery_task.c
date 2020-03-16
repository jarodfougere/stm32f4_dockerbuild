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



void battery_task(struct rimot_device *dev, enum task_state *state)
{
    switch(*state)
    {
        case TASK_STATE_init:
            adc_init();

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
