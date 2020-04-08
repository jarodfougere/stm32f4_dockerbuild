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
#include "gpio_interface.h"

#include "rimot_LL_debug.h"


void battery_task(virtualDev *dev, task_t *task)
{   
    switch(taskGetState(task))
    {
        case TASK_STATE_init:
        {
            gpioIF_initBattery();
            taskSetState(task, TASK_STATE_enumerating);
        }
        break;
        case TASK_STATE_enumerating:
        {
            switch (devGetState(dev))
            {
                case DEVICE_STATE_active:
                {
                    taskSetState(task, TASK_STATE_ready);
                    taskSetEvent(task, TASK_EVT_init);
                }
                break;
                case DEVICE_STATE_resetting:
                {
                    taskSetState(task, TASK_STATE_ready);
                    taskSetEvent(task, TASK_EVT_reset);
                }
                break;
                case DEVICE_STATE_boot:
                {
                    /* OUTPOST ID NOT RECEIVED BY USB TASK YET */
                }
                break;
                default:
                {
                    LL_ASSERT(0);
                }
                break;
            }
        }
        break;
        case TASK_STATE_ready:
        {   
            switch(taskGetEvent(task))
            {
                case TASK_EVT_init:
                {

                    taskSetEvent(task, TASK_EVT_run);
                }
                break;
                case TASK_EVT_reset:
                {

                    taskSetEvent(task, TASK_EVT_run);
                }
                break;
                case TASK_EVT_run:
                {
                    gpioIF_measureBattery();

                }
                break;
                case TASK_EVT_timer:
                {

                }
                break;
                case TASK_EVT_err:
                {

                }
                break;
                case TASK_EVT_none:
                default:
                {
                    LL_ASSERT(0);
                }
                break;
            }
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
