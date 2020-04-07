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
#include "task.h"

#include "gpio_interface.h"


void battery_task(virtualDev *dev, task_t *task)
{   
    switch(taskGetState(task))
    {
        case TASK_STATE_init:
        {
            gpioIF_initBattery();
        }
        break;
        case TASK_STATE_ready:
        {
            gpioIF_measureBattery();
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
