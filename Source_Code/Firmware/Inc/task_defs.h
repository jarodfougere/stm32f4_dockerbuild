#ifndef __TASK_DEFS__H_
#define __TASK_DEFS__H

#include <stdint.h>
#include <limits.h>

#include "cmsis_os.h"

/* Task Thread Ids */
extern osThreadId defaultTaskHandle;
extern osThreadId usbSerialTaskHandle;
extern osThreadId indicatorTaskHandle;
extern osThreadId dcOutTaskHandle;
extern osThreadId dcInTaskHandle;

/* Task Message Ids */
extern osMessageQId usbSerialMsgQHandle;
extern osMessageQId defaultMsgQHandle;
extern osMessageQId indicatorMsgQHandle;
extern osMessageQId dcOutMsgQHandle;
extern osMessageQId dcInMsgQHandle;

/* Task Queue Message Types */
typedef enum
{
    TASK_CB_FLAG_success = 0x00,
    TASK_CB_FLAG_fail = 0x01,
} TASK_CB_FLAG_t;


typedef struct
{
    uint8_t id;
} TASKMSGQ_SUBTASK_t;


typedef struct
{
    uint8_t ctx;
    uint8_t evt;
    TASKMSGQ_SUBTASK_t sbtask;
} TASKMSGQ_t;


typedef struct
{
    osMessageQId QId;
    uint8_t ctx;
    uint8_t evt;
    TASKMSGQ_SUBTASK_t sbtask;
    TASK_CB_FLAG_t flag;
} TASKMSGQ_CBEVT_t;


typedef struct
{
    TASKMSGQ_t msg;
    TASKMSGQ_CBEVT_t cbmsg;
    TASKMSGQ_SUBTASK_t sbtask;
} QUEUE_DEFAULT_MSG;


typedef QUEUE_DEFAULT_MSG DEFAULTMSGQ_t;
typedef QUEUE_DEFAULT_MSG USBSERIALMSGQ_t;
typedef QUEUE_DEFAULT_MSG INDICATORMSGQ_t;
typedef QUEUE_DEFAULT_MSG DCOUTMSGQ_t;
typedef QUEUE_DEFAULT_MSG DCINMSGQ_t;

/* Task Context and Event Definitions */
/** Default Task **/
typedef enum
{
    TASK_DEFAULT_EVT_boot,
    TASK_DEFAULT_EVT_clear_config,
    TASK_DEFAULT_EVT_active_state,
    TASK_DEFAULT_EVT_store_config,
} TASK_DEFAULT_EVT_t;


typedef enum
{
    DEVICE_STATE_idle,
    DEVICE_STATE_resetting_to_defaults,
    DEVICE_STATE_active,
} DEVICE_STATE_t;


/** USB Serial Task **/
typedef enum
{
    TASK_USBSERIAL_CTX_general,
    TASK_USBSERIAL_CTX_transmit,
    TASK_USBSERIAL_CTX_receive,
} TASK_USBSERIAL_CTX_t;


typedef enum
{
    TASK_USBSERIAL_GENERAL_EVT_com_open,
    TASK_USBSERIAL_GENERAL_EVT_start_notifs,
} TASK_USBSERIAL_GENERAL_EVT_t;


typedef enum
{
    TASK_USBSERIAL_TRANSMIT_EVT_send_heartbeat,
    TASK_USBSERIAL_TRANSMIT_EVT_send_dcin,
    TASK_USBSERIAL_TRANSMIT_EVT_send_done,
} TASK_USBSERIAL_TRANSMIT_EVT_t;


typedef enum
{
    TASK_USBSERIAL_RECIEVE_EVT_message_received,
} TASK_USBSERIAL_RECIEVE_EVT_t;


/** Indicator Task **/
// TBD ---
/** Dry Contact Output Task **/
typedef enum
{
    TASK_DCOUT_CTX_update,
} TASK_DCOUT_CTX_t;

/** Dry Contact Input Task **/
typedef enum
{
    TASK_STATE_DCIN_idle,
    TASK_STATE_DCIN_polling,
} TASK_STATE_DCIN_t;


typedef enum
{
    TASK_DCIN_CTX_initialize,
    TASK_DCIN_CTX_poll,
} TASK_DCIN_CTX_t;


typedef enum
{
    TASK_DCIN_INITIALIZE_EVT_update,
} TASK_DCIN_INITIALIZE_EVT_t;


typedef enum
{
    TASK_DCIN_POLL_EVT_start,
    TASK_DCIN_POLL_EVT_update,
    TASK_DCIN_POLL_EVT_periodic_message,
    TASK_DCIN_POLL_EVT_stop,
} TASK_DCIN_POLL_EVT_t;
#endif