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
    task_index_system,
    task_index_serial,
    task_index_analytics,
    task_index_motion,
    task_index_humidity,
    task_index_rf,
    task_index_digital_input,
    task_index_relay,
    task_index_battery,
    task_index_temperature,
}   task_index_t;


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_TASK_STATE */