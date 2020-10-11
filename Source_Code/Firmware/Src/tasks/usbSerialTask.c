/**
 * @file usbSerialTask.c
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief This source module implements the logic for the usb serial task
 * @version 0.1
 * @date 2020-10-11
 *
 * @copyright Copyright (c) 2020
 *
 * @note
 * @todo json parsing
 */

#include <stdint.h>
#include <limits.h>

#include "main.h"
#include "cmsis_os.h"
#include "usbd_cdc_if.h"
#include "usb_device.h"
#include "stm32f4xx.h"
#include "task_defs.h"
#include "jsmn.h"

/**< Task character buffer for transmitting to host >**/
#define USBSERIAL_BUFFER_SIZE 1000
uint8_t usbTxBuf[2][USBSERIAL_BUFFER_SIZE];

static jsmn_parser jsonParser;
static jsmntok_t jsonTokens[20];
static int jsonRetval;
static uint8_t jsonStrBuf[256];


void usbSerialTask(const USBSERIALMSGQ_t *Q)
{
    static uint8_t buf_idx;
    switch ((TASK_USBSERIAL_CONTEXT_t)Q->msg.ctx)
    {
        case TASK_USBSERIAL_CONTEXT_general:
        {
            switch ((TASK_USBSERIAL_GENERAL_EVENT_t)Q->msg.evt)
            {
                case TASK_USBSERIAL_GENERAL_EVENT_com_open:
                {
                    osDelay(100);
                }
                break;
                case TASK_USBSERIAL_GENERAL_EVENT_start_notifs:
                {
                    osTimerStart(SysTickHeartbeatTimerHandle, 250);
                }
                break;
            }
        }
        break;
        case TASK_USBSERIAL_CONTEXT_receive:
        {
            switch ((TASK_USBSERIAL_RECIEVE_EVENT_t)Q->msg.evt)
            {
                case TASK_USBSERIAL_RECIEVE_EVENT_message_received:
                {
                    /* BLUE LED IS A VISUAL INDICATOR OF USB RECEPTION
                     */
                    HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);

                    if (CDC_getCommandString(jsonStrBuf, sizeof(jsonStrBuf)) ==
                        0)
                    {
                        memset(usbTxBuf[buf_idx], 0, sizeof(usbTxBuf[buf_idx]));


                        sprintf((char *)usbTxBuf[buf_idx], "[USB_RX] : %s ",
                                jsonStrBuf);

                        CDC_Transmit_FS(usbTxBuf[buf_idx],
                                        sizeof(usbTxBuf[buf_idx]));
                    }

                    osDelay(100);

                    HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
                }
                break;
            }
        }
        break;
        case TASK_USBSERIAL_CONTEXT_transmit:
        {
            switch ((TASK_USBSERIAL_TRANSMIT_EVENT_t)Q->msg.evt)
            {
                case TASK_USBSERIAL_TRANSMIT_EVENT_send_dcin:
                {
                    /** @todo */
                }
                break;
                case TASK_USBSERIAL_TRANSMIT_EVENT_send_done:
                {
                }
                case TASK_USBSERIAL_TRANSMIT_EVENT_send_heartbeat:
                {
                }
                break;
            }
        }
        break;
    }
}
