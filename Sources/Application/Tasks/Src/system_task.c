/**
 * @file system_task.c
 * @author Carl Mattatall
 * @brief  This file handles the system task such as the non-volatile
 *  configuration, initializing system interfaces, controlling power modes, 
 * and so on... 
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */
#include "system_task.h"


/**
 * @brief This task is responsible for the top-level system task management.
 * Examples of the task's responsibility are: 
 *  -    
 *  -    
 *  -    
 *  -    
 * 
 * @param dev 
 * @param state 
 */
void system_task(struct rimot_device *dev, struct task *task)
{   
    switch(task->state)
    {
        case TASK_STATE_init:
            middleware_init_core(); /* init the middleware layer */
            
            /* transition to ready after initialization */
            task->state = TASK_STATE_ready; 
            break;
        case TASK_STATE_ready:

            break;
        case TASK_STATE_asleep:
            task_sleep(task, 0);
            break;
        case TASK_STATE_blocked:
            /* check if blocking resource has become available */
            break;
    }
}
