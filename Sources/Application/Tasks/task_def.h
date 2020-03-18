#ifndef RIMOT_TASK_DEF
#define RIMOT_TASK_DEF
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */
#include <stdint.h>

#define MAX_NUM_TASK_EVT_HANDLERS 5

/* a task can be in several states */
enum task_state
{
    TASK_STATE_init,
    TASK_STATE_blocked,
    TASK_STATE_ready,
    TASK_STATE_asleep,
};   

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