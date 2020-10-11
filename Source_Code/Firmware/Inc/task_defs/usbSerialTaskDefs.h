#ifndef __USBSERIALTASKDEFS_H__
#define __USBSERIALTASKDEFS_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */

typedef enum
{
    TASK_USBSERIAL_CONTEXT_general,
    TASK_USBSERIAL_CONTEXT_transmit,
    TASK_USBSERIAL_CONTEXT_receive,
} TASK_USBSERIAL_CONTEXT_t;

typedef enum
{
    TASK_USBSERIAL_GENERAL_EVENT_com_open,
    TASK_USBSERIAL_GENERAL_EVENT_start_notifs,
} TASK_USBSERIAL_GENERAL_EVENT_t;

typedef enum
{
    TASK_USBSERIAL_TRANSMIT_EVENT_send_heartbeat,
    TASK_USBSERIAL_TRANSMIT_EVENT_send_dcin,
    TASK_USBSERIAL_TRANSMIT_EVENT_send_done,
} TASK_USBSERIAL_TRANSMIT_EVENT_t;

typedef enum
{
    TASK_USBSERIAL_RECIEVE_EVENT_message_received,
} TASK_USBSERIAL_RECIEVE_EVENT_t;

#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __USBSERIALTASKDEFS_H__ */
