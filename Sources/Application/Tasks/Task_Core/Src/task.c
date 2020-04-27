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
 * @copyright Copyright (c) 2020 Rimot.io Incorporated. All rights reserved.
 * 
 * This software is licensed under the Berkley Software Distribution (BSD) 
 * 3-Clause license. Redistribution and use in source and binary forms, 
 * with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE. 
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
    task->handler(dev, task);
}






