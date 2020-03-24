#ifndef RIMOT_TASK_STATE
#define RIMOT_TASK_STATE
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */
#define NUM_TASKS 11

/* a task can be in several states */
enum task_state
{   
    /*
     * Task waiting for resource currently held by another task
     */ 
    TASK_STATE_blocked,

    /* Task has the resources it needs and is ready to execute */
    TASK_STATE_ready,

    /* Task is waiting to wake up after a set interval */
    TASK_STATE_asleep,
};  

/* task indices for round-robin */
typedef enum
{
    task_idx_system,
    task_idx_usb,
    task_idx_analytics,
    task_idx_motion,
    task_idx_humidity,
    task_idx_rf,
    task_idx_digital_input,
    task_idx_relay,
    task_idx_battery,
    task_idx_temperature,
    task_idx_timing,
}   task_idx_t;


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_TASK_STATE */