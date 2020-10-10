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

typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
typedef StaticTimer_t osStaticTimerDef_t;

/* Thread defs */
osStaticThreadDef_t defaultTaskControlBlock;
osStaticThreadDef_t usbSerialTaskControlBlock;

/* Timer Defs */
osStaticTimerDef_t LED_HB_TimerControlBlock;

/* Message Queues */
osStaticMessageQDef_t usbSerialMsgQHandleControlBlock;
osStaticMessageQDef_t defaultMsgQHandleControlBlock;

osMessageQueueId_t usbSerialMsgQHandle;
osMessageQueueId_t defaultMsgQHandle;

uint32_t usbSerialTaskBuffer[128];
uint32_t defaultTaskBuffer[128];
uint8_t defaultMsgQHandleBuffer[16 * sizeof(DEFAULTMSGQ_t)];
uint8_t usbSerialMsgQHandleBuffer[16 * sizeof(USBSERIALMSGQ_t)];


osThreadId_t defaultTaskHandle;
osThreadId_t usbSerialTaskHandle;
osTimerId_t LED_HB_TimerHandle;

const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .stack_mem = &defaultTaskBuffer[0],
    .stack_size = sizeof(defaultTaskBuffer),
    .cb_mem = &defaultTaskControlBlock,
    .cb_size = sizeof(defaultTaskControlBlock),
    .priority = (osPriority_t)osPriorityNormal,
};

const osThreadAttr_t usbSerialTask_attributes = {
    .name = "usbSerialTask",
    .stack_mem = &usbSerialTaskBuffer[0],
    .stack_size = sizeof(usbSerialTaskBuffer),
    .cb_mem = &usbSerialTaskControlBlock,
    .cb_size = sizeof(usbSerialTaskControlBlock),
    .priority = (osPriority_t)osPriorityHigh,
};

const osTimerAttr_t LED_HB_Timer_attributes = {
    .name = "LED_HB_Timer",
    .cb_mem = &LED_HB_TimerControlBlock,
    .cb_size = sizeof(LED_HB_TimerControlBlock),
};

/* Definitions for defaultMsgQHandle */
const osMessageQueueAttr_t defaultMsgQHandle_attributes = {
    .name = "defaultMsgQHandle",
    .cb_mem = &defaultMsgQHandleControlBlock,
    .cb_size = sizeof(defaultMsgQHandleControlBlock),
    .mq_mem = &defaultMsgQHandleBuffer,
    .mq_size = sizeof(defaultMsgQHandleBuffer)};


/* Definitions for usbSerialMsgQHandle */
const osMessageQueueAttr_t usbSerialMsgQHandle_attributes = {
    .name = "usbSerialMsgQHandle",
    .cb_mem = &usbSerialMsgQHandleControlBlock,
    .cb_size = sizeof(usbSerialMsgQHandleControlBlock),
    .mq_mem = &usbSerialMsgQHandleBuffer,
    .mq_size = sizeof(usbSerialMsgQHandleBuffer)};


DEVICE_STATE_t device_state = DEVICE_STATE_idle;
uint8_t outpostID[8] = "00000000";

void StartDefaultTask(void *argument);
void StartUsbSerialTask(void *argument);
void LED_HB_TimerBlink(void *argument);


void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**< Task character buffer for transmitting to host >**/
#define USBSERIAL_BUFFER_SIZE 1000
uint8_t usbTxBuf[2][USBSERIAL_BUFFER_SIZE];

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    LED_HB_TimerHandle = osTimerNew(LED_HB_TimerBlink, osTimerPeriodic, NULL,
                                    &LED_HB_Timer_attributes);

    defaultMsgQHandle = osMessageQueueNew(4, sizeof(DEFAULTMSGQ_t),
                                          &defaultMsgQHandle_attributes);

    usbSerialMsgQHandle = osMessageQueueNew(4, sizeof(USBSERIALMSGQ_t),
                                            &usbSerialMsgQHandle_attributes);

    defaultTaskHandle =
        osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

    usbSerialTaskHandle =
        osThreadNew(StartUsbSerialTask, NULL, &usbSerialTask_attributes);
}


/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
void StartDefaultTask(void *argument)
{

    static DEFAULTMSGQ_t Q;
    static DEFAULTMSGQ_t dfmsg;
    static USBSERIALMSGQ_t usmsg;

    memset(&dfmsg, 0, sizeof(dfmsg));
    dfmsg.msg.evt = TASK_DEFAULT_EVT_boot;
    xQueueSend(defaultMsgQHandle, (void *)&dfmsg, 0);

    for (;;)
    {
        if (xQueueReceive(defaultMsgQHandle, (void *)(&Q),
                          (TickType_t)portMAX_DELAY) == pdTRUE)
        {
            /* GENERAL */
            if ((TASK_DEFAULT_EVT_t)Q.msg.evt == TASK_DEFAULT_EVT_boot)
            {
                /* wait for outpost ID packet before activating GPIO */
                device_state = DEVICE_STATE_idle;


                /** @note THIS DOESNT GO HERE. ITS BEING PLACED HERE FOR
                 * HEARTBEAT DURING DEVELOPMENT */
                memset(&usmsg, 0, sizeof(usmsg));
                usmsg.msg.ctx = TASK_USBSERIAL_CTX_general;
                usmsg.msg.evt = TASK_USBSERIAL_GENERAL_EVT_start_notifs;
                xQueueSend(usbSerialMsgQHandle, (void *)&usmsg, 0);
            }
        }
    }
}


// static jsmn_parser jsonParser;
// static jsmntok_t jsonTokens[20];
// static int jsonRetval;
static uint8_t jsonStrBuf[256];
/**
 * @brief RTOS Task implementing the serial communications task
 *
 * @param argument
 */
void StartUsbSerialTask(void *argument)
{
    static USBSERIALMSGQ_t Q;

    /* More than one message can be queued for outgoing */
    static uint8_t buf_idx = 0;

    // static DEFAULTMSGQ_t dfmsg;
    memset(jsonStrBuf, 0, sizeof(jsonStrBuf));

    for (;;)
    {
        BaseType_t has_msg;
        has_msg = xQueueReceive(usbSerialMsgQHandle, (void *)(&Q),
                                (TickType_t)portMAX_DELAY);
        if (has_msg)
        {
            switch ((TASK_USBSERIAL_CTX_t)Q.msg.ctx)
            {
                case TASK_USBSERIAL_CTX_general:
                {
                    switch ((TASK_USBSERIAL_GENERAL_EVT_t)Q.msg.evt)
                    {
                        case TASK_USBSERIAL_GENERAL_EVT_com_open:
                        {
                            osDelay(100);
                        }
                        break;
                        case TASK_USBSERIAL_GENERAL_EVT_start_notifs:
                        {
                            osTimerStart(LED_HB_TimerHandle, 250);
                        }
                        break;
                    }
                }
                break;
                case TASK_USBSERIAL_CTX_receive:
                {
                    switch ((TASK_USBSERIAL_RECIEVE_EVT_t)Q.msg.evt)
                    {
                        case TASK_USBSERIAL_RECIEVE_EVT_message_received:
                        {
                            /* BLUE LED IS A VISUAL INDICATOR OF USB RECEPTION
                             */
                            HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin,
                                              GPIO_PIN_SET);


                            if (CDC_getCommandString(jsonStrBuf,
                                                     sizeof(jsonStrBuf)) == 0)
                            {
                                memset(usbTxBuf[buf_idx], 0,
                                       sizeof(usbTxBuf[buf_idx]));


                                sprintf((char *)usbTxBuf[buf_idx],
                                        "[USB_RX] : %s ", jsonStrBuf);

                                CDC_Transmit_FS(usbTxBuf[buf_idx],
                                                sizeof(usbTxBuf[buf_idx]));
                            }

                            osDelay(100);

                            HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin,
                                              GPIO_PIN_RESET);
                        }
                        break;
                    }
                }
                break;
                case TASK_USBSERIAL_CTX_transmit:
                {
                    switch ((TASK_USBSERIAL_TRANSMIT_EVT_t)Q.msg.evt)
                    {
                        case TASK_USBSERIAL_TRANSMIT_EVT_send_dcin:
                        {
                            /** @todo */
                        }
                        break;
                        case TASK_USBSERIAL_TRANSMIT_EVT_send_done:
                        {
                        }
                        case TASK_USBSERIAL_TRANSMIT_EVT_send_heartbeat:
                        {
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
}

void LED_HB_TimerBlink(void *argument)
{
    HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
}
