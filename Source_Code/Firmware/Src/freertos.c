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

#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
#include "task_defs.h"


#include "usbd_cdc_if.h"
#include "i2c.h"
#include "i2s.h"
#include "spi.h"
#include "usb_device.h"
#include "gpio.h"


#include "jsmn.h"

#define STACK_SIZE 256u
#define USBSERIAL_BUFFER_SIZE 1000

osThreadId defaultTaskHandle;
osThreadId serialTaskHandle;
osThreadId rfTaskHandle;
osThreadId digitalOutputHandle;
osThreadId digitalInputHandle;
osThreadId analogInputHandle;


osMessageQId usbSerialMsgQHandle;
osMessageQId defaultMsgQHandle;


osMessageQId dcOutMsgQHandle;
osMessageQId dcInMsgQHandle;


void SerialTask(void const *argument);
void RfSensorTask(void const *arguement);
void DefaultTask(void const *argument);
void DigInTask(void const *arguement);
void AnalogInTask(void const *arguement);
void DigOutTask(void const *arguement);


void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**< Task character buffer for transmitting to host >**/
uint8_t usbSerialTxBuffer[2][USBSERIAL_BUFFER_SIZE];

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    /* place for user code */
}


/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    osMessageQDef(usbSerialMsgQ, 8, USBSERIALMSGQ_t);
    usbSerialMsgQHandle = osMessageCreate(osMessageQ(usbSerialMsgQ), NULL);

    /* definition and creation of defaultMsgQ */
    osMessageQDef(defaultMsgQ, 4, DEFAULTMSGQ_t);
    defaultMsgQHandle = osMessageCreate(osMessageQ(defaultMsgQ), NULL);

    osThreadDef(defaultT, DefaultTask, osPriorityNormal, 0, STACK_SIZE);
    defaultTaskHandle = osThreadCreate(osThread(defaultT), NULL);

    osThreadDef(serialT, SerialTask, osPriorityHigh, 0, STACK_SIZE);
    serialTaskHandle = osThreadCreate(osThread(serialT), NULL);


#if 0 
    osThreadDef(rfT, RfSensorTask, osPriorityNormal, 0, STACK_SIZE);
    rfTaskHandle = osThreadCreate(osThread(rfT), NULL);

    osThreadDef(digitalInT, DigInTask, osPriorityNormal, 0, STACK_SIZE);
    digitalInputHandle = osThreadCreate(osThread(digitalInT), NULL);

    osThreadDef(digOutT, DigOutTask, osPriorityNormal, 0, STACK_SIZE);
    digitalOutputHandle = osThreadCreate(osThread(digOutT), NULL);

    osThreadDef(analogInT, AnalogInTask, osPriorityNormal, 0, STACK_SIZE);
    analogInputHandle = osThreadCreate(osThread(analogInT), NULL);
#endif
}

DEVICE_STATE_t device_state = DEVICE_STATE_idle;

/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
void DefaultTask(void const *argument)
{
    /* USER CODE BEGIN StartDefaultTask */
    static DEFAULTMSGQ_t Q;
    static DEFAULTMSGQ_t dfmsg;
    static USBSERIALMSGQ_t usmsg;
    static DCOUTMSGQ_t domsg;
    static DCINMSGQ_t dimsg;

    static uint32_t addr;
    static uint32_t data;

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

                /* start heartbeat messages */
                memset(&usmsg, 0, sizeof(usmsg));
                usmsg.msg.ctx = TASK_USBSERIAL_CTX_general;
                usmsg.msg.evt = TASK_USBSERIAL_GENERAL_EVT_start_notifs;
                xQueueSend(usbSerialMsgQHandle, (void *)&usmsg, 0);
            }
        }
    }
}


/**
 * @brief RTOS Task implementing the serial communications task
 *
 * @param argument
 */

static int jsonRetval;
static jsmn_parser jsonParser;
static jsmntok_t jsonTokens[20];
static uint8_t jsonStrBuf[256];
void SerialTask(void const *argument)
{
    static USBSERIALMSGQ_t Q;
    static DEFAULTMSGQ_t dfmsg;
    static DCINMSGQ_t dimsg;

    static uint8_t buf_idx = 0;

    memset(jsonStrBuf, 0, sizeof(jsonStrBuf));

    MX_USB_DEVICE_Init();
    for (;;)
    {
        /*
        uint8_t msg[] = "USB INITIALIZED!\n";
        CDC_Transmit_FS(msg, (uint16_t)sizeof(msg));
        */
        if (xQueueReceive(usbSerialMsgQHandle, (void *)(&Q),
                          (TickType_t)portMAX_DELAY) == pdTRUE)
        {
            HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);

            if ((TASK_USBSERIAL_CTX_t)Q.msg.ctx == TASK_USBSERIAL_CTX_general)
            {
                if ((TASK_USBSERIAL_GENERAL_EVT_t)Q.msg.evt ==
                    TASK_USBSERIAL_GENERAL_EVT_com_open)
                {
                    HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
                    osDelay(100); /* This has to be here */
                    HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
                }
                if ((TASK_USBSERIAL_GENERAL_EVT_t)Q.msg.evt ==
                    TASK_USBSERIAL_GENERAL_EVT_start_notifs)
                {
                    /* start periodic messages
                    osTimerStart(sysTickMessageTimerId,
                                 heartbeat_reporting_interval * 1000);
                    */
                }
            }

            if ((TASK_USBSERIAL_CTX_t)Q.msg.ctx == TASK_USBSERIAL_CTX_receive)
            {

                if ((TASK_USBSERIAL_RECIEVE_EVT_t)Q.msg.evt ==
                    TASK_USBSERIAL_RECIEVE_EVT_message_received)
                {
                    HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
                    /*

                    if (CDC_getCommandString(jsonStrBuf, sizeof(jsonStrBuf)) ==
                        0)
                    {
                        jsmn_init(&jsonParser);
                        jsonRetval =
                            jsmn_parse(&jsonParser, (const char *)jsonStrBuf,
                                       sizeof(jsonStrBuf), jsonTokens, 20);
                        if (jsonRetval > 0 &&
                            jsonTokens[0].type ==
                                JSMN_OBJECT &&
                            jsonTokens[1].type == JSMN_STRING)
                        {

                            sprintf((char *)usbSerialTxBuffer[buf_idx],
                                    "Echoing back your message: \"%s\"\r\n",
                                    jsonStrBuf);
                            CDC_Transmit_FS(jsonStrBuf, sizeof(jsonStrBuf));
                        }
                    }
                    */
                }
            }
        }
    }
}


/**
 * @brief RTOS Task for the serial
 *
 * @param arguement
 */
void RfSensorTask(void const *arguement)
{
    for (;;)
    {
        osDelay(1);
    }
}


/**
 * @brief
 *
 * @param arguement
 */
void DigInTask(void const *arguement)
{


    for (;;)
    {
        osDelay(1);
    }
}


/**
 * @brief
 *
 * @param arguement
 */
void AnalogInTask(void const *arguement)
{


    for (;;)
    {
        osDelay(1);
    }
}


/**
 * @brief
 *
 * @param arguement
 */
void DigOutTask(void const *arguement)
{

    for (;;)
    {
        osDelay(1);
    }
}
