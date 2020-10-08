
#include <stdio.h> /* vsnprintf and snprintf */
#include <stdint.h>
#include <limits.h>
#include <string.h> /* memset */

#include "main.h"
#include "task_defs.h"
#include "usbd_cdc_if.h"
#include "cmsis_compiler.h"


#define APP_RX_USER_CMD_DATA_SIZE 128

uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];
uint8_t UserRxCommandStringBuffer[APP_RX_USER_CMD_DATA_SIZE];
uint8_t *UserRxBufferInPtr;  /**< Data insertion USB Rx buffer pointer     */
uint8_t *UserRxBufferOutPtr; /**< Data removal USB RX buffer pointer       */

USBD_CDC_LineCodingTypeDef linecoding = {
    115200, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* nb. of bits 8*/
};

extern USBD_HandleTypeDef hUsbDeviceFS;

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t *pbuf, uint32_t *Len);
static int8_t CDC_TransmitCplt_FS(uint8_t *pbuf, uint32_t *Len, uint8_t epnum);


/* clang-format off */
USBD_CDC_ItfTypeDef USBD_Interface_fops_FS = 
{
    CDC_Init_FS, 
    CDC_DeInit_FS,
    CDC_Control_FS, 
    CDC_Receive_FS,
    CDC_TransmitCplt_FS,
};
/* clang-format on */

/**
 * @brief  Initializes the CDC media low layer over the FS USB IP
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_Init_FS(void)
{
    /* Set Application Buffers */
    USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);
    return (USBD_OK);
}

/**
 * @brief  DeInitializes the CDC media low layer
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_DeInit_FS(void)
{
    /* USER CODE BEGIN 4 */
    return (USBD_OK);
    /* USER CODE END 4 */
}

/**
 * @brief  Manage the CDC class requests
 * @param  cmd: Command code
 * @param  pbuf: Buffer containing command data (request parameters)
 * @param  length: Number of data to be sent (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else
 * USBD_FAIL
 */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length)
{
    /* USER CODE BEGIN 5 */

    USBSERIALMSGQ_t usmsg;
    switch (cmd)
    {
        case CDC_SEND_ENCAPSULATED_COMMAND:

            break;

        case CDC_GET_ENCAPSULATED_RESPONSE:

            break;

        case CDC_SET_COMM_FEATURE:

            break;

        case CDC_GET_COMM_FEATURE:

            break;

        case CDC_CLEAR_COMM_FEATURE:

            break;
        case CDC_SET_LINE_CODING:
            linecoding.bitrate = (uint32_t)(pbuf[0] | (pbuf[1] << 8) |
                                            (pbuf[2] << 16) | (pbuf[3] << 24));
            linecoding.format = pbuf[4];
            linecoding.paritytype = pbuf[5];
            linecoding.datatype = pbuf[6];
            break;
        case CDC_GET_LINE_CODING:
            pbuf[0] = (uint8_t)(linecoding.bitrate);
            pbuf[1] = (uint8_t)(linecoding.bitrate >> 8);
            pbuf[2] = (uint8_t)(linecoding.bitrate >> 16);
            pbuf[3] = (uint8_t)(linecoding.bitrate >> 24);
            pbuf[4] = linecoding.format;
            pbuf[5] = linecoding.paritytype;
            pbuf[6] = linecoding.datatype;
            break;

        case CDC_SET_CONTROL_LINE_STATE:
            memset(&usmsg, 0, sizeof(usmsg));
            usmsg.msg.ctx = TASK_USBSERIAL_CTX_general;
            usmsg.msg.evt = TASK_USBSERIAL_GENERAL_EVT_com_open;
            xQueueSendFromISR(usbSerialMsgQHandle, (void *)&(usmsg), 0);
            break;
        case CDC_SEND_BREAK:

            break;

        default:
            break;
    }

    return (USBD_OK);
}

/**
 * @brief  Data received over USB OUT endpoint are sent over CDC interface
 *         through this function.
 *
 *         @note
 *         This function will issue a NAK packet on any OUT packet received on
 *         USB endpoint until exiting this function. If you exit this function
 *         before transfer is complete on CDC interface (ie. using DMA
 * controller) it will result in receiving more data while previous ones are
 * still not sent.
 *
 * @param  Buf: Buffer of data to be received
 * @param  Len: Number of data received (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else
 * USBD_FAIL
 *
 * @note CALLED FROM ISR
 */
static int8_t CDC_Receive_FS(uint8_t *Buf, uint32_t *Len)
{
    /* USER CODE BEGIN 6 */
    USBSERIALMSGQ_t usmsg;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
    USBD_CDC_ReceivePacket(&hUsbDeviceFS);

    HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

#if 0
    /* copy bytes into receive buffer and test for command terminator */
    uint32_t i = 0;
    do
    {
        /* copy byte into command buffer */
        *(UserRxBufferInPtr++) = Buf[i];

        /* check if this is a command terminator character */
        if (Buf[i] == '\r')
        {
            /* notify command handler */
            memset(&usmsg, 0, sizeof(usmsg));
            usmsg.msg.ctx = TASK_USBSERIAL_CTX_receive;
            usmsg.msg.evt = TASK_USBSERIAL_RECIEVE_EVT_message_received;
            xQueueSendFromISR(usbSerialMsgQHandle, (void *)&usmsg,
                              &xHigherPriorityTaskWoken);

            /* allow cmsis to include the compiler intrinsics portably */
            //__NOP();
        }

        /* buffer pointer management */
        if (UserRxBufferInPtr >=
            UserRxCommandStringBuffer + APP_RX_USER_CMD_DATA_SIZE)
        {
            UserRxBufferInPtr = UserRxCommandStringBuffer;
        }

    } while (++i < *Len);

#endif

    return (USBD_OK);
}


/**
 * @brief  CDC_Transmit_FS
 *         Data to send over USB IN endpoint are sent over CDC interface
 *         through this function.
 *         @note
 *
 *
 * @param  Buf: Buffer of data to be sent
 * @param  Len: Number of data to be sent (in bytes)
 * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
 */
uint8_t CDC_Transmit_FS(uint8_t *Buf, uint16_t Len)
{
    uint8_t result = USBD_OK;
    /* USER CODE BEGIN 7 */
    USBD_CDC_HandleTypeDef *hcdc =
        (USBD_CDC_HandleTypeDef *)hUsbDeviceFS.pClassData;
    if (hcdc->TxState != 0)
    {
        return USBD_BUSY;
    }
    USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
    result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
    /* USER CODE END 7 */
    return result;
}


/**
 * @brief  CDC_getCommandString
 *         Copies command string into provided buffer.
 *         @note
 *
 *
 * @param  Buf: Buffer to store command string
 * @param  Len: Buffer length
 * @retval Result of the operation: 1 on error, 0 otherwise
 */
uint8_t CDC_getCommandString(uint8_t *Buf, uint16_t Len)
{
    uint16_t i = 0;
    uint8_t flag = 0;

    /* check for API error */
    if (Len < 1)
    {
        return 1;
    }

    do
    {
        /* copy next byte */
        Buf[i] = *UserRxBufferOutPtr;

        /* end of command */
        if (*UserRxBufferOutPtr == '\r')
        {
            /* null terminate to make string and return */
            Buf[i + 1] = '\0';
            flag = 1;
        }

        /* pointer management */
        if (++UserRxBufferOutPtr >=
            UserRxCommandStringBuffer + APP_RX_USER_CMD_DATA_SIZE)
        {
            UserRxBufferOutPtr = UserRxCommandStringBuffer;
        }

        i++;

    } while ((i < Len) && (flag == 0));

    /* check if data fit in buffer, return 0 on error */
    if (flag == 0)
    {
        return 1;
    }

    /* success */
    return 0;
}


/**
 * @brief Sends single JSON formatted key/value on serial port
 *
 * @param key key text string
 * @param value value text string
 * @return uint8_t USBD_OK on success else USBD_FAIL or USBD_BUSY
 */
uint8_t CDC_sendJSON(char *key, char *value)
{
    uint8_t result = USBD_FAIL;
    char str[120] = {0};
    int slen;
    slen = sprintf(str, "{\"%s\":\"%s\"}\r\n", key, value);
    if (slen > 0)
    {
        result = CDC_Transmit_FS((uint8_t *)str, slen);
    }

    return result;
}


/**
 * @brief  CDC_TransmitCplt_FS
 *         Data transmited callback
 *
 * @param  Buf: Buffer of data to be received
 * @param  Len: Number of data received (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else
 * USBD_FAIL
 * @note CALLED FROM ISR
 */
static int8_t CDC_TransmitCplt_FS(uint8_t *Buf, uint32_t *Len, uint8_t epnum)
{
    uint8_t result = USBD_OK;
    UNUSED(Buf);
    UNUSED(Len);
    UNUSED(epnum);
    return result;
}