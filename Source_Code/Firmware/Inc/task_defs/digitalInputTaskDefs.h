#ifndef __DIGITALINPUTTASKDEFS_H__
#define __DIGITALINPUTTASKDEFS_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */


/** Dry Contact Input Task **/
typedef enum
{
    TASK_STATE_DCIN_idle,
    TASK_STATE_DCIN_polling,
} TASK_STATE_DCIN_t;


typedef enum
{
    TASK_DCIN_CONTEXT_initialize,
    TASK_DCIN_CONTEXT_poll,
} TASK_DCIN_CONTEXT_t;


typedef enum
{
    TASK_DCIN_INITIALIZE_EVENT_update,
} TASK_DCIN_INITIALIZE_EVENT_t;


typedef enum
{
    TASK_DCIN_POLL_EVENT_start,
    TASK_DCIN_POLL_EVENT_update,
    TASK_DCIN_POLL_EVENT_periodic_message,
    TASK_DCIN_POLL_EVENT_stop,
} TASK_DCIN_POLL_EVENT_t;

#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __DIGITALINPUTTASKDEFS_H__ */
