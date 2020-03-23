/**
 * @file main.c
 * @author Carl Mattatall
 * @brief  The low-power-sensorcard firmware application mainline starts here.
 * 
 * @note
 * Application architecture is an equal timeslice round-robin superloop.
 *  
 * We cycle through each of the tasks.
 * Each task is responsible for executing based on the device state and its
 * task state (idle, active, blocked, suspended)
 *
 * In general, system and serial tasks should occupy the majority of 
 * runtime, with other tasks yielding to those 2 tasks as they are the
 * primary modifiers of the device state (config in nvmem and runtime
 * variable values)
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

    /* index of the scheduled task in the event loop */
    uint32_t task_idx; 

    /* tasks that the event loop will service */
    struct task tasks[NUM_TASKS] = 
    {   
        [task_idx_system] = 
        {
            TASK_STATE_init,
            .wakeup_tick = 0,
            .handler = &system_task,
        },

        [task_idx_serial] = 
        {
            TASK_STATE_init,
            .wakeup_tick = 0,
            .handler = &serial_task,
        },

        [task_idx_analytics] = 
        {
            TASK_STATE_init,
            .wakeup_tick = 0,
            .handler = &analytics_task,
        },

        [task_idx_motion] = 
        {
            TASK_STATE_init,
            .wakeup_tick = 0,
            .handler = &motion_task,
        },

        [task_idx_humidity] = 
        {
            TASK_STATE_init,
            .wakeup_tick = 0,
            .handler = &humidity_task,
        },

        [task_idx_rf] = 
        {
            TASK_STATE_init,
            .wakeup_tick = 0,
            .handler = &rf_task,
        },

        [task_idx_digital_input] = 
        {
            TASK_STATE_init,
            .wakeup_tick = 0,
            .handler = &digital_input_task,
        },

        [task_idx_relay] = 
        {
            TASK_STATE_init,
            .wakeup_tick = 0,
            .handler = &relay_task,
        },

        [task_idx_battery] = 
        {
            TASK_STATE_init,
            .wakeup_tick = 0,
            .handler = &battery_task,
        },

        [task_idx_temperature] = 
        {
            TASK_STATE_init,
            .wakeup_tick = 0,
            .handler = &temperature_task,
        },
    };

    for (task_idx = 0; /* forever */; task_idx = ((task_idx + 1) % NUM_TASKS))
    {
        tasks[task_idx].handler(&dev, &tasks[task_idx]); 
    }
}
