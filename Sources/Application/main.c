/**
 * @file main.c
 * @author Carl Mattatall
 * @brief  The application mainline starts here.
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */


#include "main.h"
#include "tasks.h"

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
        NULL};

extern void (*taskLoop[])(struct rimot_device *);
extern const int32_t num_tasks;

int main(void)
{
    //TODO:  check if we have returned here from bootloader

    struct rimot_device dev = RIMOT_DEV_DFLT_INITIALIZER;

    /* 
    Application architecture is an equal timeslice round-robin superloop.
    
    We cycle through each of the tasks.
    Each task is responsible for executing based on the device state and its
    internal task state (idle, active, blocked, suspended)

    In general, system and serial tasks should occupy the majority of runtime,
    with other tasks yielding to those 2 tasks as they are the primary modifiers
    of the device state (config in nvmem and runtime variable values)
    */
    while (1)
    {
        int32_t task_idx = 0;
        taskLoop[task_idx++ % num_tasks](&dev);
    }
}
