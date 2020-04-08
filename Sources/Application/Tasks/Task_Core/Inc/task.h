#ifndef RIMOT_TASK_DEF
#define RIMOT_TASK_DEF
#ifdef __cplusplus
extern "C" {
#endif /* c linkage */
#include <stdint.h>
#include "rimot_device.h"

#define NUM_TASKS 10

/* a task can be in several states */
typedef enum
{   
    /*
     * Task waiting for resource currently held by another task
     */ 
    TASK_STATE_blocked,

    /* Task has the resources it needs and is ready to execute */
    TASK_STATE_ready,

    /* First time the task is running */
    TASK_STATE_init,

    TASK_STATE_enumerating,

    TASK_STATE_err, /* Error has occurred */

} TASK_STATE_t;


typedef enum
{
    TASK_IDX_system,
    TASK_IDX_usb,
    TASK_IDX_analytics,
    TASK_IDX_motion,
    TASK_IDX_humidity,
    TASK_IDX_rf,
    TASK_IDX_digital_input,
    TASK_IDX_relay,
    TASK_IDX_battery,
    TASK_IDX_temperature,
}   TASK_IDX_t;

#define NO_TASK_EVT   (0)
#define TASK_CTX_NONE (0)

typedef enum
{   
    TASK_EVT_none = NO_TASK_EVT,
    TASK_EVT_run,
    TASK_EVT_init,
    TASK_EVT_reset,
    TASK_EVT_timer,                
    TASK_EVT_err,                   
}   TASK_EVT_t;

/* Anonymous declarations */
typedef struct rimot_task task_t;
typedef void (*taskHandler)(virtualDev*, task_t*);

task_t* taskInit(taskHandler handler);
TASK_STATE_t taskGetState(const task_t *task);
int taskGetContext(const task_t *task);
int taskGetEvent(const task_t *task);
unsigned long long taskGetWakeupTick(const task_t *task);
void taskSetState(task_t *task, TASK_STATE_t state);
void taskSetContext(task_t *task, int ctx);
void taskSetEvent(task_t *task, int evt);
void taskSetWakeupTick(task_t *task, unsigned long long tick);
void taskCallHandler(task_t *task, virtualDev* dev);

#ifdef __cplusplus
}
#endif /* c linkage */
#endif /* RIMOT_TASK_DEF */
