

#include "middleware_core.h"
#include "tasks.h"

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



int assign_task_evt_cb(struct task *task, void (*evt_cb)(void*))
{   
    int status = 0;
    if(NULL != evt_cb)
    {
        if(task->num_event_handlers < MAX_NUM_TASK_EVT_HANDLERS)
        {
            task->event_handlers[task->num_event_handlers++] = evt_cb;
        }
        else
        {
            status = 1;
        }
    }
    return status;
}

