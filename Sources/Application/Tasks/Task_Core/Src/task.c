/**
 * @file task.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This file hides implementation details while exposing functionality
 * for the "rimot_task" structure. The task structure is used to implement
 * a round-robin scheduled event loop that is abstract enough that with
 * some future work it could be scheduled using RMA if real-time performance
 * is desired.
 * @version 0.1
 * @date 2020-04-07
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include <stdlib.h>

#include "task.h"
#include "rimot_LL_debug.h"

struct rimot_task
{
    volatile TASK_STATE_t state;
    struct 
    {
        int ctx;
        TASK_EVT_t evt;
    }   exec;
    unsigned long long    wakeup_tick;
    taskHandler handler;
};

task_t* taskInit(taskHandler handler)
{   
    task_t* task = (task_t*)malloc(sizeof(task_t));
#ifndef NDEBUG
    LL_ASSERT(NULL != task); /* Check for malloc failure */
#endif  /* DEBUG BUILD */
    task->state = TASK_STATE_init;
    task->exec.ctx = TASK_CTX_NONE;
    task->exec.evt = TASK_EVT_run;
    task->handler = handler;
    task->wakeup_tick = 0;
    return task;
}


TASK_STATE_t taskGetState(const task_t *task)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != task);
#endif  /* DEBUG BUILD */
    return task->state;
}


int taskGetContext(const task_t *task)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != task);
#endif  /* DEBUG BUILD */
    return task->exec.ctx;
}


int taskGetEvent(const task_t *task)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != task);
#endif  /* DEBUG BUILD */
    return task->exec.evt;
}


unsigned long long taskGetWakeupTick(const task_t *task)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != task);
#endif  /* DEBUG BUILD */
    return task->wakeup_tick;
}


void taskSetState(task_t *task, TASK_STATE_t state)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != task);
#endif  /* DEBUG BUILD */
    task->state = state;
}


void taskSetContext(task_t *task, int ctx)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != task);
#endif  /* DEBUG BUILD */
    task->exec.ctx = ctx;
}


void taskSetEvent(task_t *task, int evt)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != task);
#endif  /* DEBUG BUILD */
    task->exec.evt = (TASK_EVT_t)evt;
}


void taskSetWakeupTick(task_t *task, unsigned long long tick)
{
#ifndef NDEBUG
    LL_ASSERT(NULL != task);
#endif  /* DEBUG BUILD */
    task->wakeup_tick = tick;
}


void taskCallHandler(task_t *task, virtualDev *dev)
{   
#ifndef NDEBUG
    LL_ASSERT(NULL != task);
    LL_ASSERT(NULL != dev);
#endif  /* DEBUG BUILD */
    task->handler(dev, task); /* Task's self is passed in as param */
}






