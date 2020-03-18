/**
 * @file tasks.c
 * @author Carl Mattatall
 * @brief  This module provides various core functions shared by task modules.
 * @version 0.1
 * @date 2020-03-18
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include "middleware_core.h"
#include "task_core.h"

void task_sleep(struct task *task, uint32_t ticks)
{   
    if(task->state != TASK_STATE_asleep)
    {   
        /* transition from !asleep -> asleep */
        task->state = TASK_STATE_asleep; 

        /* set the tick value for task to wakeup */
        task->wakeup_tick = get_tick() + ticks; 
    }
    else if(task->wakeup_tick == get_tick()) /* check for wakeup condition */
    {   
        /* return to ready state upon countdown expiry */
        task->state = TASK_STATE_ready;
    }
}


void task_wakeup(struct task *task)
{   
    switch(task->state)
    {
        case TASK_STATE_asleep:
            task->wakeup_tick = get_tick();
        case TASK_STATE_blocked:
        case TASK_STATE_init:
        case TASK_STATE_ready:
            task->state = TASK_STATE_ready;
            break;
    }
}