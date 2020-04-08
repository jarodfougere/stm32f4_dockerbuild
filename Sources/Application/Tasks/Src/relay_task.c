/**
 * @file relay_task.c
 * @author Carl Mattatall
 * @brief  This module handles the control of the relays using the
 *  relay_interface middleware module.
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "relay_task.h"


#include "rimot_LL_debug.h"




void relay_task(virtualDev *dev, task_t *task)
{
    switch(taskGetState(task))
    {
        case TASK_STATE_init:
        {
            gpioIF_initRelays();
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
            /* 
             *      - set relay state pins to default position
             *      - latch relays via pulse pins
             *      - set all relay pins inactive
             *      - store the system configuration to external eeprom
             */

            /*      
             *      - load system configuration for relays from external eeprom
             *      - set state pins to the position indicated by system config
             *      - latch relays
             */


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
        default:
        {
            LL_ASSERT(0); /* Hang in debug mode. Possible omission error */
        }   
        break;
    }
}
