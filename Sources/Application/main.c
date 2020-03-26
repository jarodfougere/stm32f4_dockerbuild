/**
 * @file main.c
 * @author Carl Mattatall
 * @brief  The low-power-sensorcard firmware application mainline starts here.
 * If a different scheduling algorithm is used, this source module is where we
 * would write it.
 * 
 * @note
 * High-level architecture is a round-robin event loop.
 * 
 * In the future, if real-time performance is required, a scheduler can be
 * integrated (such as freeRTOS or chibiOS) or implemented to call each task's
 * handler as part of an RMA scheduling algorithm using systick as a timeslice
 * rather than simply executing in a round-robin.
 * 
 * Each task is responsible for executing based on the device state and its
 * task state (ready, blocked, suspended)
 * Tasks can signal each other to request or release peripheral resources as 
 * many peripheral drivers have been configured to operate in a non-blocking 
 * fashion with interrupts signaling peripheral process completion.
 * 
 * 90 % of request and release for resources will be for the SPI peripheral and
 * the ADC since SPI is shared by temp, humidity, and eeprom, with ADC 
 * being shared by battery monitoring, RF detection, and the analog output of 
 * the sparkfun motion detection module.
 * 
 * @version 0.3
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "main.h"
#include "task_core.h"

#if defined(__GNUC__)
#if !defined(MCU_APP)
__stdcall
#endif /* HOST APPLCIATION CHECK */
#endif /* GNUC */
int main(void)
{   
    /* virtual device structure */
    struct rimot_device dev = RIMOT_DEV_DFLT_INITIALIZER;

    /* tasks that the event loop will service */
    struct task tasks[NUM_TASKS] = 
    {   
        [task_idx_system] = 
        {   
            .exec = 
            {
                .evt = TASK_EVT_init,   /* Right away, system task inits */
                .ctx = TASK_CTX_NONE,   /* No signal */
            },
            .state = TASK_STATE_ready,
            .wakeup_tick = 0,
            .handler = &system_task,
        },

        [task_idx_usb] = 
        {   
            .exec = 
            {
                .evt = TASK_EVT_init,   /* Right away, usb task inits */
                .ctx = TASK_CTX_NONE,   /* No signal */
            },
            .state = TASK_STATE_ready,
            .wakeup_tick = 0,
            .handler = &usb_task,
        },

        [task_idx_timing] = 
        {
            .exec = 
            {
                .evt = TASK_EVT_init,   /* Right away, timing task inits */
                .ctx = TASK_CTX_NONE,   /* No signal */
            },
            .state = TASK_STATE_ready,
            .wakeup_tick = 0,
            .handler = &timing_task,
        },

        /*********************************************************************/
        /* UNTIL WE REGISTER OR LOAD OUTPOST ID, ALL OTHER TASKS ARE BLOCKED */
        /*********************************************************************/

        [task_idx_analytics] = 
        {   
            .exec = 
            {
                .evt = TASK_EVT_init,   /* When task unblocks it will init */
                .ctx = TASK_CTX_NONE,   /* No signal */ 
            },
            .state = TASK_STATE_blocked,
            .wakeup_tick = 0,
            .handler = &analytics_task,
        },

        [task_idx_motion] = 
        {   
            .exec = 
            {
                .evt = TASK_EVT_init,   /* When task unblocks it will init */
                .ctx = TASK_CTX_NONE,   /* No signal */
            },
            .state = TASK_STATE_blocked,
            .wakeup_tick = 0,
            .handler = &motion_task,
        },

        [task_idx_humidity] = 
        {   
            .exec = 
            {
                .evt = TASK_EVT_init,   /* When task unblocks it will init */
                .ctx = TASK_CTX_NONE,   /* No signal */
            },
            .state = TASK_STATE_blocked,
            .wakeup_tick = 0,
            .handler = &humidity_task,
        },

        [task_idx_rf] = 
        {   
            .exec = 
            {
                .evt = TASK_EVT_init,   /* When task unblocks it will init */
                .ctx = TASK_CTX_NONE,   /* No signal */
            },
            .state = TASK_STATE_blocked,
            .wakeup_tick = 0,
            .handler = &rf_task,
        },

        [task_idx_digital_input] = 
        {   
            .exec = 
            {
                .evt = TASK_EVT_init,   /* When task unblocks it will init */
                .ctx = TASK_CTX_NONE,   /* No signal */
            },
            .state = TASK_STATE_blocked,
            .wakeup_tick = 0,
            .handler = &digital_input_task,
        },

        [task_idx_relay] = 
        {   
            .exec = 
            {
                .evt = TASK_EVT_init,   /* When task unblocks it will init */
                .ctx = TASK_CTX_NONE,   /* No signal */
            },
            .state = TASK_STATE_blocked, 
            .wakeup_tick = 0,
            .handler = &relay_task,
        },

        [task_idx_battery] = 
        {   
            .exec = 
            {
                .evt = TASK_EVT_init,   /* When task unblocks it will init */
                .ctx = TASK_CTX_NONE,   /* No signal */
            },
            .state = TASK_STATE_blocked,
            .wakeup_tick = 0,
            .handler = &battery_task,
        },

        [task_idx_temperature] = 
        {   
            .exec = 
            {
                .evt = TASK_EVT_init,   /* When task unblocks it will init */
                .ctx = TASK_CTX_NONE,   /* No signal */
            },
            .state = TASK_STATE_blocked,
            .wakeup_tick = 0,
            .handler = &temperature_task,
        },
    };

    while (1)
    {
        switch(dev.state)
        {
            case DEVICE_STATE_boot:
            {   
                /* until outpostID registered, only 3 task run */
                tasks[task_idx_system].handler(&dev, &tasks[task_idx_system]);
                tasks[task_idx_usb].handler(&dev, &tasks[task_idx_usb]);
                tasks[task_idx_timing].handler(&dev, &tasks[task_idx_timing]);
            }
            break;
            case DEVICE_STATE_active:
            {   
                /* Once fully booted, all the tasks run in an event loop */
                unsigned int task_idx;
                for (task_idx = 0; ; task_idx = ((task_idx + 1) % NUM_TASKS))
                {   
                    tasks[task_idx].handler(&dev, &tasks[task_idx]); 
                }
            }
            break;
            case DEVICE_STATE_fault:
            {
                /* Handle the fault */
            }
            break;
        }
    }
}
