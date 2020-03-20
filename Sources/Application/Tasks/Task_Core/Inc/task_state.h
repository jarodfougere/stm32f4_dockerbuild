#ifndef RIMOT_TASK_STATE
#define RIMOT_TASK_STATE
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#define NUM_TASKS 10

/* a task can be in several states */
enum task_state
{
    TASK_STATE_init,
    TASK_STATE_blocked,
    TASK_STATE_ready,
    TASK_STATE_asleep,
};  

typedef enum
{
    task_idx_system,
    task_idx_serial,
    task_idx_analytics,
    task_idx_motion,
    task_idx_humidity,
    task_idx_rf,
    task_idx_digital_input,
    task_idx_relay,
    task_idx_battery,
    task_idx_temperature,
}   task_idx_t;


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_TASK_STATE */