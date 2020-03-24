/**
 * @file relay_task.c
 * @author Carl Mattatall
 * @brief  This module handles the control of the relays using the
 *  relay_interface middleware module.
 * @version 0.1
 * @date 2020-03-05
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */
#include "relay_task.h"
#include "task_core.h"




void relay_task(struct rimot_device *dev, struct task *task)
{
    switch(task->state)
    {
        case TASK_STATE_ready:
        {
            switch(task->exec.evt)
            {
                case TASK_EVT_init:
                {

                }
                break;  
                case TASK_EVT_rx:
                {

                }
                break;
                case TASK_EVT_tx:
                {

                }
                break;
                case TASK_EVT_err:
                {

                }
                break;
                case TASK_EVT_none: /* FALLTHROUGH TO DEFAULT */
                default:
#if !defined(NDEBUG)
                {
                    while(1)
                    {
                        /* 
                         * 2 cases:
                         * 
                         *  - Programmer forgot to add an event to switch,
                         *    thus triggering the default case.
                         *
                         *  - Task is being signaled but its evt not being 
                         *    updated by the signalling task. 
                         * 
                         * Both scenarios mean a bug in software. Hang forever 
                         * in debug build.
                         */
                    }
                }
#else
                break;
#endif /* DEBUG BUILD */
            }

            /* After execution, block and clear exec event and context */
            task_block_self(task); 
        }
        break;
        case TASK_STATE_asleep:
        {
            task_sleep(task, 0);
        }
        break;
        case TASK_STATE_blocked:
        {
            
        }
        break;
    }
}
