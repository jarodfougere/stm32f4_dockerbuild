/**
 * @file analytics_task.c
 * @author Carl Mattatall
 * @brief  This task module performas analytics and data normalization/
 * processing on data gathered by the other tasks.
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Inc
 * 
 */
#include "analytics_task.h"



void analytics_task(struct rimot_device *dev, enum task_state *state)
{   
    switch(*state)
    {
        case TASK_STATE_init:


            /* transition to ready after initialization */
            *state = TASK_STATE_ready; 
            break;
        case TASK_STATE_ready:

            break;
        case TASK_STATE_asleep:

        break;
        case TASK_STATE_blocked:

            break;
    }
}