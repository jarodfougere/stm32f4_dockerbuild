#ifndef RIMOT_TASK_DEF
#define RIMOT_TASK_DEF
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */
#include <stdint.h>
#include "task_state.h"
#define MAX_NUM_TASK_EVT_HANDLERS 5


/* Considering implementing something similar to:
http://www.qnx.com/developers/docs/6.5.0/index.jsp?topic=%2Fcom.qnx.doc.dinkum_en_c99%2Fsignal.html

For tasks to signal resource requests / releases to each other
int raise(int sig);
void (*signal(int sig, void (*func)(int)))(int);
*/

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