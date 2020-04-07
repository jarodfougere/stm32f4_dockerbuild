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
#include "task.h"




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
void system_task(virtualDev *dev, task_t *task)
{   
    switch(taskGetState(task))
    {
        case TASK_STATE_ready:
        {
            switch(taskGetEvent(task))
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
                case TASK_EVT_run:
                {

                }
                break;
                case TASK_EVT_timer:
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

                }
            }
        }
        break;
        case TASK_STATE_blocked:
        {
            /* check if blocking resource has become available */
        }
        break;
    }
}
