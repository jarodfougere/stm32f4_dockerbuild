/**
 * @file digital_input_task.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief  This module manages the digital input functionality using the 
 * digital input interface module. 

 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "digital_input_task.h"

#include "rimot_LL_debug.h"



void digital_input_task(virtualDev *dev, task_t *task)
{   
    switch(taskGetState(task))
    {
        case TASK_STATE_init:
        {   
            gpioIF_initInputs();
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
                    /*  
                     * Read from external eeprom.
                     * Load each digital input pin's active state.
                     * Load each digital input pin's debounce time.
                     * Load each digital input pin's trigger mode.
                     * Load each digital input pin's label.
                     * Load each digital input pin's priority.
                     */
                    taskSetEvent(task, TASK_EVT_run);
                }
                break;
                case TASK_EVT_reset:
                {
                    /* 
                     * Set all digital input pins inactive.
                     * Set all digital input pin debounces to default.
                     * Set all digital input pin trigger modes to default.
                     * Set all digital input pin labels to default.
                     * Set all digital input pin priorities to default.
                     * Write the each pin configuration to external eeprom.
                     */ 
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

