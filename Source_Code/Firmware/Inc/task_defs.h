#ifndef __TASK_DEFS_H__
#define __TASK_DEFS_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */

#include <stdint.h>
#include <limits.h>

#include "cmsis_os.h"


#define NUM_TASKS 8
#define MSGQ_DEPTH (NUM_TASKS)
#define THREAD_STACK_SIZE 256u

#define MSG_CONTENT_NONE -1

typedef StaticTask_t  osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
typedef StaticTimer_t osStaticTimerDef_t;

/* Thread control blocks */
extern osStaticThreadDef_t defaultTaskControlBlock;
extern osStaticThreadDef_t usbSerialTaskControlBlock;
extern osStaticThreadDef_t digitalInputTaskControlBlock;
extern osStaticThreadDef_t digitalOutputTaskControlBlock;
extern osStaticThreadDef_t analogInputTaskControlBlock;
extern osStaticThreadDef_t rfSensorTaskControlBlock;
extern osStaticThreadDef_t mothSensorTaskControlBlock;

/* Timer Defs */
extern osStaticTimerDef_t LED_HB_TimerControlBlock;

/* Message Queue Control Blocks */
extern osStaticMessageQDef_t usbSerialMsgQHandleControlBlock;
extern osStaticMessageQDef_t defaultMsgQHandleControlBlock;
extern osStaticMessageQDef_t digitalInputMsgQHandleControlBlock;
extern osStaticMessageQDef_t digitalOutputMsgQHandleControlBlock;
extern osStaticMessageQDef_t analogInputMsgQHandleControlBlock;
extern osStaticMessageQDef_t rfSensorMsgQHandleControlBlock;
extern osStaticMessageQDef_t mothSensorMsgQHandleControlBlock;

/* Message Queue GUIDs */
extern osMessageQueueId_t usbSerialMsgQHandle;
extern osMessageQueueId_t defaultMsgQHandle;
extern osMessageQueueId_t digitalInputMsgQHandle;
extern osMessageQueueId_t digitalOutputMsgQHandle;
extern osMessageQueueId_t analogInputMsgQHandle;
extern osMessageQueueId_t rfSensorMsgQHandle;
extern osMessageQueueId_t mothSensorMsgQHandle;


extern osTimerId_t SysTickHeartbeatTimerHandle;

/* Task Queue Message Types */
typedef enum
{
    TASK_CB_FLAG_success = 0x00,
    TASK_CB_FLAG_fail    = 0x01,
} TASK_CB_FLAG_t;

typedef struct
{
    uint8_t ctx;
    uint8_t evt;
} TASKMSGQ_t;

typedef struct QUEUE_DEFAULT_MSG_struct
{
    TASKMSGQ_t msg;
    void *     cb_args;
    void (*callback)(void *);
} QUEUE_DEFAULT_MSG;

typedef QUEUE_DEFAULT_MSG DEFAULTMSGQ_t;
typedef QUEUE_DEFAULT_MSG USBSERIALMSGQ_t;
typedef QUEUE_DEFAULT_MSG DIGITALINMSGQ_t;
typedef QUEUE_DEFAULT_MSG DIGITALOUTMSGQ_t;
typedef QUEUE_DEFAULT_MSG ANALOGINMSGQ_t;
typedef QUEUE_DEFAULT_MSG RFSENSORMSGQ_t;
typedef QUEUE_DEFAULT_MSG MOTHSENSORMSGQ_t;
typedef QUEUE_DEFAULT_MSG INDICATORMSGQ_t;

typedef enum
{
    DEVICE_STATE_idle,
    DEVICE_STATE_resetting_to_defaults,
    DEVICE_STATE_active,
} DEVICE_STATE_t;

/* Task Context and Event Definitions */
#include "defaultTaskDefs.h"
#include "usbSerialTaskDefs.h"
#include "digitalOutputTaskDefs.h"
#include "digitalInputTaskDefs.h"
#include "analogInputTaskDefs.h"
#include "rfSensorTaskDefs.h"
#include "mothSensorTaskDefs.h"


#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __TASK_DEFS_H__ */
