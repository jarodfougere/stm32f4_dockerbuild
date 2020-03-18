#ifndef RIMOT_TASK_STATE
#define RIMOT_TASK_STATE
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/* a task can be in several states */
enum task_state
{
    TASK_STATE_init,
    TASK_STATE_blocked,
    TASK_STATE_ready,
    TASK_STATE_asleep,
};   

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_TASK_STATE */