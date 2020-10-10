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
#include "stm32f4xx.h"
#include "gpio.h"
#include "usb_device.h"
#include "main.h"
#include "cmsis_os.h"


#include "jsmn.h"
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticTimer_t osStaticTimerDef_t;

osThreadId_t defaultTaskHandle;

uint32_t defaultTaskBuffer[128];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .stack_mem = &defaultTaskBuffer[0],
    .stack_size = sizeof(defaultTaskBuffer),
    .cb_mem = &defaultTaskControlBlock,
    .cb_size = sizeof(defaultTaskControlBlock),
    .priority = (osPriority_t)osPriorityNormal,
};

osThreadId_t usbSerialTaskHandle;
uint32_t usbSerialTaskBuffer[128];
osStaticThreadDef_t usbSerialTaskControlBlock;
const osThreadAttr_t usbSerialTask_attributes = {
    .name = "usbSerialTask",
    .stack_mem = &usbSerialTaskBuffer[0],
    .stack_size = sizeof(usbSerialTaskBuffer),
    .cb_mem = &usbSerialTaskControlBlock,
    .cb_size = sizeof(usbSerialTaskControlBlock),
    .priority = (osPriority_t)osPriorityHigh,
};

osTimerId_t LED_HB_TimerHandle;
osStaticTimerDef_t LED_HB_TimerControlBlock;
const osTimerAttr_t LED_HB_Timer_attributes = {
    .name = "LED_HB_Timer",
    .cb_mem = &LED_HB_TimerControlBlock,
    .cb_size = sizeof(LED_HB_TimerControlBlock),
};

void StartDefaultTask(void *argument);
void StartUsbSerialTask(void *argument);
void LED_HB_TimerBlink(void *argument);


void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**< Task character buffer for transmitting to host >**/
#define USBSERIAL_BUFFER_SIZE 1000
uint8_t usbSerialTxBuffer[2][USBSERIAL_BUFFER_SIZE];

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    LED_HB_TimerHandle = osTimerNew(LED_HB_TimerBlink, osTimerPeriodic, NULL,
                                    &LED_HB_Timer_attributes);

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
    MX_USB_DEVICE_Init();
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
void StartUsbSerialTask(void *argument)
{
    for (;;)
    {
        osDelay(1);
    }
}

void LED_HB_TimerBlink(void *argument)
{
    HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
}
