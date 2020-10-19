/**
 * @file freertos.c
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief FreeRTOS task definition source file
 *        for low power sensor card firmware
 * @version 0.1
 * @date 2020-10-06
 * @copyright Copyright (c) 2020 [TO BE ENTERED]
 * @note
 * @todo     LOTS OF STUFF TO DO
 */
#include <stdint.h>
#include <limits.h>

/* CMSIS_RTOS_V2 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "cmsis_os.h"

/* HAL + USB Layer */
#include "stm32f4xx.h"
#include "gpio.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

/* Application */
#include "main.h"
#include "task_defs.h"
#include "jsmn.h"

/* Thread functions */
#include "usbSerialTask.h"
#include "defaultTask.h"
#include "digitalInputTask.h"
#include "digitalOutputTask.h"
#include "analogInputTask.h"
#include "rfSensorTask.h"
#include "mothSensorTask.h"


/* Thread control blocks */
osStaticThreadDef_t defaultTaskControlBlock;
osStaticThreadDef_t usbSerialTaskControlBlock;
osStaticThreadDef_t digitalInputTaskControlBlock;
osStaticThreadDef_t digitalOutputTaskControlBlock;
osStaticThreadDef_t analogInputTaskControlBlock;
osStaticThreadDef_t rfSensorTaskControlBlock;
osStaticThreadDef_t mothSensorTaskControlBlock;

/* Timer Defs */
osStaticTimerDef_t LED_HB_TimerControlBlock;

/* Message Queue Control Blocks */
osStaticMessageQDef_t usbSerialMsgQHandleControlBlock;
osStaticMessageQDef_t defaultMsgQHandleControlBlock;
osStaticMessageQDef_t digitalInputMsgQHandleControlBlock;
osStaticMessageQDef_t digitalOutputMsgQHandleControlBlock;
osStaticMessageQDef_t analogInputMsgQHandleControlBlock;
osStaticMessageQDef_t rfSensorMsgQHandleControlBlock;
osStaticMessageQDef_t mothSensorMsgQHandleControlBlock;

/* Message Queue GUIDs */
osMessageQueueId_t usbSerialMsgQHandle;
osMessageQueueId_t defaultMsgQHandle;
osMessageQueueId_t digitalInputMsgQHandle;
osMessageQueueId_t digitalOutputMsgQHandle;
osMessageQueueId_t analogInputMsgQHandle;
osMessageQueueId_t rfSensorMsgQHandle;
osMessageQueueId_t mothSensorMsgQHandle;

/* TASK STACKS */
uint32_t defaultTaskBuffer[THREAD_STACK_SIZE];
uint32_t usbSerialTaskBuffer[THREAD_STACK_SIZE];
uint32_t digitalInputTaskBuffer[THREAD_STACK_SIZE];
uint32_t digitalOutputTaskBuffer[THREAD_STACK_SIZE];
uint32_t analogInputTaskBuffer[THREAD_STACK_SIZE];
uint32_t rfSensorTaskBuffer[THREAD_STACK_SIZE];
uint32_t mothSensorTaskBuffer[THREAD_STACK_SIZE];

/* Message Queues */
uint8_t defaultMsgQHandleBuffer[MSGQ_DEPTH * sizeof(DEFAULTMSGQ_t)];
uint8_t usbSerialMsgQHandleBuffer[MSGQ_DEPTH * sizeof(USBSERIALMSGQ_t)];
uint8_t digitalInputMsgQHandleBuffer[MSGQ_DEPTH * sizeof(DIGITALINMSGQ_t)];
uint8_t digitalOutputMsgQHandleBuffer[MSGQ_DEPTH * sizeof(DIGITALOUTMSGQ_t)];
uint8_t analogInputMsgQHandleBuffer[MSGQ_DEPTH * sizeof(ANALOGINMSGQ_t)];
uint8_t rfSensorMsgQHandleBuffer[MSGQ_DEPTH * sizeof(RFSENSORMSGQ_t)];
uint8_t mothSensorMsgQHandleBuffer[MSGQ_DEPTH * sizeof(MOTHSENSORMSGQ_t)];

/* Thread IDs */
osThreadId_t defaultTaskHandle;
osThreadId_t usbSerialTaskHandle;
osThreadId_t digitalInputTaskHandle;
osThreadId_t digitalOutputTaskHandle;
osThreadId_t analogInputTaskHandle;
osThreadId_t rfSensorTaskHandle;
osThreadId_t mothSensorTaskHandle;


/* Timer declarations */
osTimerId_t SysTickHeartbeatTimerHandle;

uint32_t runtick;

/* Static methods */
static void StartDefaultTask(void *argument);
static void StartUsbSerialTask(void *argument);
static void StartDigitalInputTask(void *argument);
static void StartDigitalOutputTask(void *argument);
static void StartAnalogInputTask(void *argument);
static void StartRadioFrequencyTask(void *argument);
static void StartMothSensorTask(void *argument);


/* Static Task attributes (entire application should not use heap) */
const osThreadAttr_t defaultTask_attributes = {
    .name       = "defaultTask",
    .stack_mem  = defaultTaskBuffer,
    .stack_size = sizeof(defaultTaskBuffer),
    .cb_mem     = &defaultTaskControlBlock,
    .cb_size    = sizeof(defaultTaskControlBlock),
    .priority   = (osPriority_t)osPriorityNormal,
};

const osThreadAttr_t usbSerialTask_attributes = {
    .name       = "usbSerialTask",
    .stack_mem  = usbSerialTaskBuffer,
    .stack_size = sizeof(usbSerialTaskBuffer),
    .cb_mem     = &usbSerialTaskControlBlock,
    .cb_size    = sizeof(usbSerialTaskControlBlock),
    .priority   = (osPriority_t)osPriorityHigh,
};


const osThreadAttr_t digitalInputTask_attributes = {
    .name       = "digitalInputTask",
    .stack_mem  = digitalInputTaskBuffer,
    .stack_size = sizeof(digitalInputTaskBuffer),
    .cb_mem     = &digitalInputTaskControlBlock,
    .cb_size    = sizeof(digitalInputTaskControlBlock),
    .priority   = (osPriority_t)osPriorityNormal,
};

const osThreadAttr_t digitalOutputTask_attributes = {
    .name       = "digitalOutputTask",
    .stack_mem  = digitalOutputTaskBuffer,
    .stack_size = sizeof(digitalOutputTaskBuffer),
    .cb_mem     = &digitalOutputTaskControlBlock,
    .cb_size    = sizeof(digitalOutputTaskControlBlock),
    .priority   = (osPriority_t)osPriorityNormal,
};


const osThreadAttr_t analogInputTask_attributes = {
    .name       = "analogInputTask",
    .stack_mem  = analogInputTaskBuffer,
    .stack_size = sizeof(analogInputTaskBuffer),
    .cb_mem     = &analogInputTaskControlBlock,
    .cb_size    = sizeof(analogInputTaskControlBlock),
    .priority   = (osPriority_t)osPriorityNormal,
};


const osThreadAttr_t rfSensorTask_attributes = {
    .name       = "rfSensorTask",
    .stack_mem  = rfSensorTaskBuffer,
    .stack_size = sizeof(rfSensorTaskBuffer),
    .cb_mem     = &rfSensorTaskControlBlock,
    .stack_size = sizeof(rfSensorTaskControlBlock),
    .priority   = (osPriority_t)osPriorityNormal,
};


const osThreadAttr_t mothSensorTask_attributes = {
    .name       = "mothSensorTask",
    .stack_mem  = mothSensorTaskBuffer,
    .stack_size = sizeof(mothSensorTaskBuffer),
    .cb_mem     = &mothSensorTaskControlBlock,
    .cb_size    = sizeof(mothSensorTaskControlBlock),
    .priority   = (osPriority_t)osPriorityNormal,
};


/* SOFTWARE TIMER TASK CONTROL BLOCKS */

const osTimerAttr_t LED_HB_Timer_attributes = {
    .name    = "LED_HB_Timer",
    .cb_mem  = &LED_HB_TimerControlBlock,
    .cb_size = sizeof(LED_HB_TimerControlBlock),
};


/* MESSAGE QUEUE CONTROL BLOCKS */

const osMessageQueueAttr_t defaultMsgQHandle_attributes = {
    .name    = "defaultMsgQHandle",
    .cb_mem  = &defaultMsgQHandleControlBlock,
    .cb_size = sizeof(defaultMsgQHandleControlBlock),
    .mq_mem  = &defaultMsgQHandleBuffer,
    .mq_size = sizeof(defaultMsgQHandleBuffer)};

const osMessageQueueAttr_t usbSerialMsgQHandle_attributes = {
    .name    = "usbSerialMsgQHandle",
    .cb_mem  = &usbSerialMsgQHandleControlBlock,
    .cb_size = sizeof(usbSerialMsgQHandleControlBlock),
    .mq_mem  = &usbSerialMsgQHandleBuffer,
    .mq_size = sizeof(usbSerialMsgQHandleBuffer)};

const osMessageQueueAttr_t digitalInputMsgQHandle_attributes = {
    .name    = "digitalInputMsgQHandle",
    .cb_mem  = &digitalInputMsgQHandleControlBlock,
    .cb_size = sizeof(digitalInputMsgQHandleControlBlock),
    .mq_mem  = &digitalInputMsgQHandleBuffer,
    .mq_size = sizeof(digitalInputMsgQHandleBuffer),
};

const osMessageQueueAttr_t digitalOutputMsgQHandle_attributes = {
    .name    = "digitalOutputMsgQHandle",
    .cb_mem  = &digitalOutputMsgQHandleControlBlock,
    .cb_size = sizeof(digitalOutputMsgQHandleControlBlock),
    .mq_mem  = &digitalOutputMsgQHandleBuffer,
    .mq_size = sizeof(digitalOutputMsgQHandleBuffer),
};


const osMessageQueueAttr_t analogInputMsgQHandle_attributes = {
    .name    = "analogInputMsgQHandle",
    .cb_mem  = &analogInputMsgQHandleControlBlock,
    .cb_size = sizeof(analogInputMsgQHandleControlBlock),
    .mq_mem  = &analogInputMsgQHandleBuffer,
    .mq_size = sizeof(analogInputMsgQHandleBuffer),
};

const osMessageQueueAttr_t rfSensorMsgQHandle_attributes = {
    .name    = "rfSensorMsgQHandle",
    .cb_mem  = &rfSensorMsgQHandleControlBlock,
    .cb_size = sizeof(rfSensorMsgQHandleControlBlock),
    .mq_mem  = &rfSensorMsgQHandleBuffer,
    .mq_size = sizeof(rfSensorMsgQHandleBuffer)};


const osMessageQueueAttr_t mothSensorMsgQHandle_attributes = {
    .name    = "mothSensorMsgQHandle",
    .cb_mem  = &mothSensorMsgQHandleControlBlock,
    .cb_size = sizeof(mothSensorMsgQHandleControlBlock),
    .mq_mem  = &mothSensorMsgQHandleBuffer,
    .mq_size = sizeof(mothSensorMsgQHandleBuffer),
};

uint8_t outpostID[8] = "00000000";

void LED_HB_TimerBlink(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */


/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    /* CONFIGURE TIMERS */
    SysTickHeartbeatTimerHandle = osTimerNew(LED_HB_TimerBlink, osTimerPeriodic,
                                             NULL, &LED_HB_Timer_attributes);

    /* CONFIGURE MESSAGE QUEUES */
    defaultMsgQHandle = osMessageQueueNew(MSGQ_DEPTH, sizeof(DEFAULTMSGQ_t),
                                          &defaultMsgQHandle_attributes);

    usbSerialMsgQHandle = osMessageQueueNew(MSGQ_DEPTH, sizeof(USBSERIALMSGQ_t),
                                            &usbSerialMsgQHandle_attributes);

    digitalInputMsgQHandle =
        osMessageQueueNew(MSGQ_DEPTH, sizeof(DIGITALINMSGQ_t),
                          &digitalInputMsgQHandle_attributes);

    digitalOutputMsgQHandle =
        osMessageQueueNew(MSGQ_DEPTH, sizeof(DIGITALOUTMSGQ_t),
                          &digitalOutputMsgQHandle_attributes);

    analogInputMsgQHandle = osMessageQueueNew(
        MSGQ_DEPTH, sizeof(ANALOGINMSGQ_t), &analogInputMsgQHandle_attributes);

    rfSensorMsgQHandle = osMessageQueueNew(MSGQ_DEPTH, sizeof(RFSENSORMSGQ_t),
                                           &rfSensorMsgQHandle_attributes);

    mothSensorMsgQHandle = osMessageQueueNew(
        MSGQ_DEPTH, sizeof(MOTHSENSORMSGQ_t), &mothSensorMsgQHandle_attributes);

    /* CONFIGURE THREADS */
    defaultTaskHandle =
        osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

    usbSerialTaskHandle =
        osThreadNew(StartUsbSerialTask, NULL, &usbSerialTask_attributes);


    digitalInputTaskHandle =
        osThreadNew(StartDigitalInputTask, NULL, &digitalInputTask_attributes);


    digitalOutputTaskHandle = osThreadNew(StartDigitalOutputTask, NULL,
                                          &digitalOutputTask_attributes);

    analogInputTaskHandle =
        osThreadNew(StartAnalogInputTask, NULL, &analogInputTask_attributes);

    rfSensorTaskHandle =
        osThreadNew(StartRadioFrequencyTask, NULL, &rfSensorTask_attributes);
    mothSensorTaskHandle =
        osThreadNew(StartMothSensorTask, NULL, &mothSensorTask_attributes);
}


/* honestly, probably should have called this task the "system" task */
/** @todo refactor so the naming makes more sense */
void StartDefaultTask(void *argument)
{
    static DEFAULTMSGQ_t Q;

    /* Application entry point */
    DEFAULTMSGQ_t dfmsg;
    memset(&dfmsg, MSG_CONTENT_NONE, sizeof(dfmsg));
    dfmsg.msg.ctx  = TASK_DEFAULT_CONTEXT_default;
    dfmsg.msg.evt  = TASK_DEFAULT_EVENT_boot;
    dfmsg.callback = NULL;
    xQueueSend(defaultMsgQHandle, (void *)&dfmsg, 0);
    for (;;)
    {
        if (xQueueReceive(defaultMsgQHandle, (void *)(&Q),
                          (TickType_t)portMAX_DELAY) == pdTRUE)
        {
            defaultTask(&Q);
            if (Q.callback != NULL)
            {
                Q.callback(Q.cb_args);
            }
        }
    }
}


void StartUsbSerialTask(void *argument)
{
    static USBSERIALMSGQ_t Q;
    for (;;)
    {
        if (xQueueReceive(usbSerialMsgQHandle, &Q, portMAX_DELAY) == pdTRUE)
        {
            usbSerialTask(&Q);
            if (Q.callback != NULL)
            {
                Q.callback(Q.cb_args);
            }
        }
        memset(&Q, MSG_CONTENT_NONE, sizeof(Q));
    }
}


void StartDigitalInputTask(void *argument)
{
    static DIGITALINMSGQ_t Q;
    for (;;)
    {
        if (xQueueReceive(digitalInputMsgQHandle, &Q, portMAX_DELAY) == pdTRUE)
        {
            digitalInputTask(&Q);
            if (Q.callback != NULL)
            {
                Q.callback(Q.cb_args);
            }
        }
    }
}


void StartDigitalOutputTask(void *argument)
{
    static DIGITALOUTMSGQ_t Q;
    for (;;)
    {
        if (xQueueReceive(digitalOutputMsgQHandle, &Q, portMAX_DELAY) == pdTRUE)
        {
            digitalOutputTask(&Q);
            if (Q.callback != NULL)
            {
                Q.callback(Q.cb_args);
            }
        }
    }
}


void StartAnalogInputTask(void *argument)
{
    static ANALOGINMSGQ_t Q;
    for (;;)
    {
        if (xQueueReceive(analogInputMsgQHandle, &Q, portMAX_DELAY) == pdTRUE)
        {
            analogInputTask(&Q);
            if (Q.callback != NULL)
            {
                Q.callback(Q.cb_args);
            }
        }
    }
}


void StartRadioFrequencyTask(void *argument)
{
    static RFSENSORMSGQ_t Q;
    for (;;)
    {
        if (xQueueReceive(rfSensorMsgQHandle, &Q, portMAX_DELAY) == pdTRUE)
        {
            rfSensorTask(&Q);
            if (Q.callback != NULL)
            {
                Q.callback(Q.cb_args);
            }
        }
    }
}


void StartMothSensorTask(void *argument)
{
    static MOTHSENSORMSGQ_t Q;
    for (;;)
    {
        if (xQueueReceive(mothSensorMsgQHandle, &Q, portMAX_DELAY) == pdTRUE)
        {
            mothSensorTask(&Q);
            if (Q.callback != NULL)
            {
                Q.callback(Q.cb_args);
            }
        }
    }
}


void LED_HB_TimerBlink(void *argument)
{
    HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
}
