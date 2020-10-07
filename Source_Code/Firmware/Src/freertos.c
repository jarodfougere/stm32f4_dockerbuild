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
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


#include "usbd_cdc_if.h"
#include "i2c.h"
#include "i2s.h"
#include "spi.h"
#include "usb_device.h"
#include "gpio.h"

#include "usb_device.h"

#define OS_STACK_SIZE_BYTES 128u

osThreadId defaultTaskHandle;
osThreadId serialTaskHandle;
osThreadId rfTaskHandle;

void StartSerialTask(void const *argument);
void StartRfSensorTask(void const *arguement);
void StartDefaultTask(void const *argument);


void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
    osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0,
                OS_STACK_SIZE_BYTES);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

    osThreadDef(serialTask, StartSerialTask, osPriorityAboveNormal, 0,
                OS_STACK_SIZE_BYTES);
    serialTaskHandle = osThreadCreate(osThread(serialTask), NULL);


    osThreadDef(rfTask, StartRfSensorTask, osPriorityAboveNormal, 0,
                OS_STACK_SIZE_BYTES);
    rfTaskHandle = osThreadCreate(osThread(rfTask), NULL);
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
void StartSerialTask(void const *argument)
{
    MX_USB_DEVICE_Init();
    for (;;)
    {
        osDelay(1);
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
