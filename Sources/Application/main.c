/**
 * @file main.c
 * @author Carl Mattatall
 * @brief  The application mainline starts here.
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
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "main.h"
#include "tasks.h"



/* see tasks.c */
extern void (*taskLoop[])(struct rimot_device *, enum task_state *);

int main(void)
{
    struct rimot_device dev = RIMOT_DEV_DFLT_INITIALIZER;
    uint32_t task_idx; /* index of the current timesliced task */
    
    /* all tasks begin in their initialization state */
    enum task_state task_states[NUM_TASKS] =
    {
        TASK_STATE_init,
        TASK_STATE_init,
        TASK_STATE_init,
        TASK_STATE_init,
        TASK_STATE_init,
        TASK_STATE_init,
        TASK_STATE_init,
        TASK_STATE_init,
        TASK_STATE_init,
        TASK_STATE_init,
    };

    /* TASK LOOP */
    for (task_idx = 0;; task_idx = ((task_idx + 1) % NUM_TASKS))
    {
        switch (dev.state)
        {
            case DEVICE_STATE_boot:
                /* if we are servicing a bootloader request */
                if (0 == checkBootloaderRequest()) 
                {
                    //TODO: JUMP TO BOOTLOADER
                }
                else
                {
                    dev.state = DEVICE_STATE_active;
                }
            
            /* FALLTHROUGH FROM INIT TO DEVICE STATE ACTIVE */
            case DEVICE_STATE_active:
                taskLoop[task_idx](&dev, &task_states[task_idx]);
                break;
            case DEVICE_STATE_idle:
                /* do nothing */
                break;
            case DEVICE_STATE_fault:
                /* todo: handle device-level fault */
                break;
        }
    }
}
