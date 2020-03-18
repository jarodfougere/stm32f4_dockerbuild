#ifndef RIMOT_TASK_DEF
#define RIMOT_TASK_DEF
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */
#include <stdint.h>
#include "task_state.h"
#define MAX_NUM_TASK_EVT_HANDLERS 5



struct task
{
    enum task_state state;
    uint32_t wakeup_tick;
    void (*handler)(struct rimot_device*, struct task*);
    void (*event_handlers[MAX_NUM_TASK_EVT_HANDLERS])(void*);
    int num_event_handlers;
};


#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* RIMOT_TASK_DEF */