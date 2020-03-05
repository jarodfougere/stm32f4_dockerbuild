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
    switch (dev->state)
    {
    case DEVICE_STATE_init:
        switch (*state)
        {
        case TASK_STATE_init:
            /* any required initialization happens here */
            *state = TASK_STATE_ready;
            break;
        case TASK_STATE_blocked:
        case TASK_STATE_ready:
        case TASK_STATE_suspended:
            /* do nothing */
            break;
        default:
#ifndef NDEBUG
            /* this means something corrupted the task state (or developer forgot to add a case to the switch statement -> but compiling with -Wall should catch this second scenario) */
            while (1)
            {
                /* hang forever */
            }
#endif
            break;
        }
        break;
    case DEVICE_STATE_active:
        switch (*state)
        {
        case TASK_STATE_init:

            break;
        case TASK_STATE_blocked:

            break;
        case TASK_STATE_ready:

            break;
        case TASK_STATE_suspended:
            break;
        default:
#ifndef NDEBUG
            /* this means something corrupted the task state (or developer forgot to add a case to the switch statement -> but compiling with -Wall should catch this second scenario) */
            while (1)
            {
                /* hang forever */
            }
#endif
            break;
        }
        break;
    case DEVICE_STATE_idle:
        switch (*state)
        {
        case TASK_STATE_init:

            break;
        case TASK_STATE_blocked:

            break;
        case TASK_STATE_ready:

            break;
        case TASK_STATE_suspended:

            break;
        default:
#ifndef NDEBUG
            /* this means something corrupted the task state (or developer forgot to add a case to the switch statement -> but compiling with -Wall should catch this second scenario) */
            while (1)
            {
                /* hang forever */
            }
#endif
            break;
        }
        break;
    case DEVICE_STATE_boot:
        switch (*state)
        {
        case TASK_STATE_init:

            break;
        case TASK_STATE_blocked:

            break;
        case TASK_STATE_ready:

            break;
        case TASK_STATE_suspended:

            break;
        default:
#ifndef NDEBUG
            /* this means something corrupted the task state (or developer forgot to add a case to the switch statement -> but compiling with -Wall should catch this second scenario) */
            while (1)
            {
                /* hang forever */
            }
#endif
            break;
        }
        break;
    case DEVICE_STATE_fault:
        /* fallthrough */
    default:
        /* 
        this should ideally never happen. it means the task that was previously called created an error and did not correctly handle it 
        before exiting
        */
#ifndef NDEBUG
        while (1)
        {
            /* hang forever */
        }
#endif
        break;
    }
}