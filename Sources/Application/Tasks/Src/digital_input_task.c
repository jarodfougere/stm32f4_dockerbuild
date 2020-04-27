/**
 * @file digital_input_task.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief  This module manages the digital input functionality using the 
 * digital input interface module. 

 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated. All rights reserved.
 * 
 * This software is licensed under the Berkley Software Distribution (BSD) 
 * 3-Clause license. Redistribution and use in source and binary forms, 
 * with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE. 
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

