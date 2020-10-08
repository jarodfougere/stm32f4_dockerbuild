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

#define STACK_SIZE 128u
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


void StartSerialTask(void const *argument);
void StartRfSensorTask(void const *arguement);
void StartDefaultTask(void const *argument);
void StartDigitalInputTask(void const *arguement);
void StartAnalogInputTask(void const *arguement);
void StartDigitalOutputTask(void const *arguement);


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
    osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, STACK_SIZE);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

    osThreadDef(serialTask, StartSerialTask, osPriorityAboveNormal, 0,
                STACK_SIZE);
    serialTaskHandle = osThreadCreate(osThread(serialTask), NULL);

    osThreadDef(rfTask, StartRfSensorTask, osPriorityAboveNormal, 0,
                STACK_SIZE);
    rfTaskHandle = osThreadCreate(osThread(rfTask), NULL);

    osThreadDef(digitalInputTask, StartDigitalInputTask, osPriorityNormal, 0,
                STACK_SIZE);
    digitalInputHandle = osThreadCreate(osThread(digitalInputTask), NULL);

    osThreadDef(digitalOutputTask, StartDigitalOutputTask, osPriorityNormal, 0,
                STACK_SIZE);
    digitalOutputHandle = osThreadCreate(osThread(digitalOutputTask), NULL);

    osThreadDef(analogInputTask, StartAnalogInputTask, osPriorityNormal, 0,
                STACK_SIZE);
    analogInputHandle = osThreadCreate(osThread(analogInputTask), NULL);
}


/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
void StartDefaultTask(void const *argument)
{
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_I2S2_Init();
    MX_I2S3_Init();
    MX_SPI1_Init();
    for (;;)
    {
        osDelay(1);
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
void StartSerialTask(void const *argument)
{
    static USBSERIALMSGQ_t Q;
    static DEFAULTMSGQ_t dfmsg;
    static DCINMSGQ_t dimsg;

    static uint8_t buf_idx = 0;



    for (;;)
    {

#if 0
        if (xQueueReceive(usbSerialMsgQHandle, (void *)(&Q),
                          (TickType_t)portMAX_DELAY) == pdTRUE)
        {
            if (CDC_getCommandString(jsonStrBuf, sizeof(jsonStrBuf)) == 0)
            {
                jsmn_init(&jsonParser);
                jsonRetval = jsmn_parse(&jsonParser, (const char *)jsonStrBuf,
                                        sizeof(jsonStrBuf), jsonTokens, 20);
                if (jsonRetval > 0 &&
                    jsonTokens[0].type ==
                        JSMN_OBJECT && /* these checks or keyval pair */
                    jsonTokens[1].type == JSMN_STRING)
                {

                    sprintf((char *)usbSerialTxBuffer[buf_idx],
                            "Echoing back your message: \"%s\"\r\n",
                            jsonStrBuf);
                    CDC_Transmit_FS(jsonStrBuf, sizeof(jsonStrBuf));
                }
            }
        }
#endif
    }
}


/**
 * @brief RTOS Task for the serial
 *
 * @param arguement
 */
void StartRfSensorTask(void const *arguement)
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
void StartDigitalInputTask(void const *arguement)
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
void StartAnalogInputTask(void const *arguement)
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
void StartDigitalOutputTask(void const *arguement)
{

    for (;;)
    {
        osDelay(1);
    }
}
