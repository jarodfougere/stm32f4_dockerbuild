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

/*
const char *json[] =
{
    "{\"GPIO_PIN_UPDATE\": true}",
    "{\"GPIO_DEVICE_INFO\" : 1}",
    "{\"system\":\"info\"}",
    "{\"write\":{\"mode\" : 1}}",
    "{\"GPIO_PIN_CONFIG\":{\"id\" : 1, \"type\" : 2, \"active\":1, \"label\" : 5, \"debounce\": 100}}",
    "{\"system\":\"reset_boot\"}",
    "{\"system\":\"reset_main\"}",
    "{\"write\": {\"pin_info_interval\" : 5}}",
    "{\"write\": {\"hb_interval\" : 5}}",
    NULL
};
*/

/* see tasks.c */
extern void (*taskLoop[])(struct rimot_device*, enum task_state*);

int main(void)
{
    struct rimot_device dev = RIMOT_DEV_DFLT_INITIALIZER;

    enum task_state task_states[NUM_TASKS];
    uint32_t task_idx;
    
    for(task_idx = 0; task_idx < NUM_TASKS; task_idx++)
    {
        task_states[task_idx] = TASK_STATE_init;
    }

    for(task_idx = 0; ; task_idx = ((task_idx + 1) % NUM_TASKS))
    {
        taskLoop[task_idx](&dev, &task_states[task_idx]);
    }
}
