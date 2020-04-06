#ifndef RIMOT_TASK_DEF
#define RIMOT_TASK_DEF
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */
#include <stdint.h>
#include "task_state.h"
#include "rimot_device.h"


/* Considering implementing something similar to:
http://www.qnx.com/developers/docs/6.5.0/index.jsp?topic=%2Fcom.qnx.doc.dinkum_en_c99%2Fsignal.html

For tasks to signal resource requests / releases to each other
int raise(int sig);
void (*signal(int sig, void (*func)(int)))(int);
*/

#define NO_TASK_EVT 0
#define TASK_CTX_NONE 0

typedef enum
{   
    TASK_EVT_none = NO_TASK_EVT,
    TASK_EVT_init,                  /* Initialize LL deps   */
    TASK_EVT_rx,                    /* Receive event        */
    TASK_EVT_tx,                    /* Transmit event       */
    TASK_EVT_err,                   /* Handle a fault       */
}   TASK_EVT_t;


struct task_exec
{
    TASK_EVT_t evt;     /* event                                        */
    int ctx;            /* context for the event (on a per-task basis ) */
};



struct task
{
    volatile enum task_state state;
    struct task_exec exec;
    uint32_t wakeup_tick;

    /** Some compilers will complain that the function pointer is not visible
     *  outside the structure because we haven't actually assigned it to a
     *  function yet. I know htere's a GNUC __attribute__(()) to tell the 
     *  compiler to omit the warning but I'm too lazy to look it up.
     * 
     *  In any case, ignore the warning.
     */

    /* the task's handle function */
    void (*handler)(struct rimot_device*, struct task*); 
};


#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* RIMOT_TASK_DEF */