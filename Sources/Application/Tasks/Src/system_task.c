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
#include "task_core.h"




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
        case TASK_STATE_ready:
        {
             switch(task->exec.evt)
            {
                case TASK_EVT_init:
                {
                    middleware_init_core(); /* Init the middleware layer */

                    /*  
                     * Wait for PLL and RCC to stablize clocks.
                     * 
                     * If you remove this, USB handler will occur before the 
                     * 48MHz PLL is stable and OTG hardfault will occur.  
                     */   
                    delay_ms(10);     
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
                {
#if !defined(NDEBUG)
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
#else           
                    break;
#endif /* DEBUG BUILD */
                }
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
            /* check if blocking resource has become available */
        }
        break;
    }
}
