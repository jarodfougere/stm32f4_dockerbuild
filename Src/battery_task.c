#include "battery_task.h"


void battery_task(void* param, task_t* thisTask)
{
  switch(thisTask->state)
  {
    case TASK_STATE_ready:
      /* do nothing, task is ready but scheduler has not scheduled it */
    break;
    case TASK_STATE_running:


    break;
    case TASK_STATE_idle:

    break;
    case TASK_STATE_busy:

    break;
    case TASK_STATE_blocked:

    break;
    case TASK_STATE_error:

    break;
    default:
      // this should never occur
    break;
  }
}
