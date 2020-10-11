#ifndef __DEFAULTTASKDEFS_H__
#define __DEFAULTTASKDEFS_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */

/** Default Task **/
typedef enum
{
    TASK_DEFAULT_EVENT_boot,
    TASK_DEFAULT_EVENT_clear_config,
    TASK_DEFAULT_EVENT_active_state,
    TASK_DEFAULT_EVENT_store_config,
} TASK_DEFAULT_EVENT_t;

#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __DEFAULTTASKDEFS_H__ */
