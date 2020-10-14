/**
 * @file usbSerialTask.c
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief This source module implements the logic for the usb serial task
 * @version 0.1
 * @date 2020-10-11
 *
 * @copyright Copyright (c) 2020
 */

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#include "main.h"
#include "cmsis_os.h"
#include "usbd_cdc_if.h"
#include "usb_device.h"
#include "usbd_desc.h"
#include "stm32f4xx.h"
#include "task_defs.h"
#include "json_utils.h"
#include "systemConfig.h"

#define USBSERIAL_BUFFER_SIZE 1000u
#define MAX_JSON_STRLEN 256
#define MAX_JSON_TOKEN_COUNT 35

#define USB_TX_ERROR INT32_MIN


uint8_t usbTxBuf[2][USBSERIAL_BUFFER_SIZE];

static jsmn_parser   jsonParser;
static jsmntok_t     jsonTokens[MAX_JSON_TOKEN_COUNT];
static uint8_t       jsonStr[MAX_JSON_STRLEN];
static uint_least8_t jsonRetval;


/**
 * @brief printf wrapper for outgoing USB serial communications
 *
 * @param fmt
 * @param ...
 * @return int32_t the number of outgoing bytes sent. If there was an error
 * loading the transmit buffer, a value < 0 is returned
 *
 * @note THIS CAN SMASH THE STACK DUE TO VA_ARGS, JUST LIKE PRINTF. BE CAREFUL
 */
static int32_t printf_CDC(const char *restrict fmt, ...);


/**
 * @brief (Attempts to) Parse a string as a json and execute its payload
 *         base on contents
 *
 * @param str the char array
 * @param len length of the char array
 * @return int 0 on successful parse and execution, !0 otherwise
 */
static int obeyJson(uint8_t *str, uint_least16_t len);


void usbSerialTask(const USBSERIALMSGQ_t *Q)
{
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
                    HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);

                    if (CDC_getCommandString(jsonStr, sizeof(jsonStr)) == 0)
                    {
                        if (obeyJson(jsonStr, strlen(jsonStr)))
                        {
                            CDC_sendJSON("error", "json_format");
                        }
                    }
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


static int obeyJson(uint8_t *str, uint_least16_t len)
{
    int status = 0;
    if (str == NULL)
    {
        status = -1;
    }
    else
    {
        jsmn_init(&jsonParser);
        jsonRetval =
            jsmn_parse(&jsonParser, (const char *)jsonStr, sizeof(jsonStr),
                       jsonTokens, MAX_JSON_TOKEN_COUNT);
        if (jsonRetval > 0 && isValidJson(jsonTokens, MAX_JSON_TOKEN_COUNT))
        {
            if (jutil_tokcmp("system", jsonStr, &jsonTokens[1]))
            {
                if (jutil_tokcmp("reset_main", jsonStr, &jsonTokens[2]))
                {
                    systemReset();
                }
                else if (jutil_tokcmp("reset_boot", jsonStr, &jsonTokens[2]))
                {
                    jumpToBootloader();
                }
                else if (jutil_tokcmp("info", jsonStr, &jsonTokens[2]))
                {
                    /* clang-format off */
                    printf_CDC("{\"info\":{"
                               "\"device_name\" : \"%s\","
                               "\"device_id\":\"%08x%08x%08x\","
                               "\"hw_version\":\"%2d.%-2d\","
                               "\"fw_version\":\"%s\""
                               "}}\r\n",
                               DEVICE_NAME_STRING, 
                               *(uint32_t *)(DEVICE_ID1),
                               *(uint32_t *)(DEVICE_ID2),
                               *(uint32_t *)(DEVICE_ID3), 
                               HWVERSION_MINOR,
                               FWID_RELEASE);
                    /* clang-format on */
                }
                else
                {
                    /** @todo some sort of error flag? */
                }
            }
            else if (jutil_tokcmp("read", jsonStr, &jsonTokens[1]))
            {
                if (jutil_tokcmp("hwVersion", jsonStr, &jsonTokens[2]))
                {
                    printf_CDC("{ \"hwVersion\" : \"%2d.%-2d\" } ",
                               HWVERSION_MAJOR, HWVERSION_MINOR);
                }
                else if (jutil_tokcmp("fwVersion", jsonStr, &jsonTokens[2]))
                {
                    printf_CDC("{\"fwVersion\" : \"%s\"}",
                               (char *)FWID_RELEASE);
                }
                else if (jutil_tokcmp("hb_interval", jsonStr, &jsonTokens[2]))
                {
                    printf_CDC("{ \"hb_interval\" : \"%5d\"}",
                               heartbeat_reporting_interval);
                }
                else if (jutil_tokcmp("pin_info_interval", jsonStr,
                                      &jsonTokens[2]))
                {
                    printf_CDC("{ \"pin_info_interval\" : \"%5d\"}",
                               dcin_periodic_timer_interval);
                }
                else
                {
                    /** @todo ERROR: INVALID READ COMMAND */
                }
            }
            else if (jutil_tokcmp("config", jsonStr, &jsonTokens[1]))
            {
                if (jutil_tokcmp("write", jsonStr, &jsonTokens[2]))
                {
                    if (jutil_tokcmp("hb_interval", jsonStr, &jsonTokens[3]))
                    {
                        


                        #if 0
if ((jsonTokens[4].type == JSMN_STRING) ||
                            (jsonTokens[4].end - jsonTokens[4].start <=
                             (4 * 2)))

#if 0 

                                            if ((jsonTokens[4].type ==
                                             JSMN_STRING) ||
                                            (jsonTokens[4].end -
                                                 jsonTokens[4].start <=
                                             (4 * 2)))
                                        {
                                            /* convert user value to float */
                                            uint16_t val = atoi(
                                                (char *)(jsonStr +
                                                         jsonTokens[4].start));

                                            if (val >= 30)
                                            {
                                                /* store new value */
                                                heartbeat_reporting_interval =
                                                    val;
                                            }
                                            else
                                            {
                                                CDC_sendJSON(
                                                    "error",
                                                    "value_out_of_range");
                                            }
                                        }
                                        else
                                        {
                                            CDC_sendJSON("error",
                                                         "value_too_large");
                                        }

                        #endif 
                    }
                    else if (jutil_tokcmp("pin_info_interval", jsonStr,
                                          &jsonTokens[3]))
                    {
                    }
                    else
                    {
                        /** @todo ERROR. INVALIDE CONFIG : WRITE COMMAND */
                    }
                }
            }
            else if (jutil_tokcmp("outpostID", jsonStr, &jsonTokens[1]))
            {
            }
            else if (jutil_tokcmp("GPIO_DEVICE_INFO", jsonStr, &jsonTokens[1]))
            {
            }
            else if (jutil_tokcmp("GPIO_PIN_CONFIG", jsonStr, &jsonTokens[1]))
            {
            }
            else if (jutil_tokcmp("GPIO_PIN_UPDATE", jsonStr, &jsonTokens[1]))
            {
            }


#if 0
            else if (strncmp((char const *)jsonStr + jsonTokens[1].start,
                             "config", sizeof("config") - 1) == 0)
            {
                if (strncmp((char const *)jsonStr + jsonTokens[2].start,
                            "write", sizeof("write") - 1) == 0)
                {
                    if (strncmp((char const *)jsonStr + jsonTokens[3].start,
                                "hb_interval", sizeof("hb_interval") - 1) == 0)
                    {
                        
#endif
                    }
                    else if (strncmp((char const *)jsonStr +
                                         jsonTokens[3].start,
                                     "pin_info_interval",
                                     sizeof("pin_info_interval") - 1) == 0)
                    {

#if 0 

                                            if ((jsonTokens[4].type ==
                                             JSMN_STRING) ||
                                            (jsonTokens[4].end -
                                                 jsonTokens[4].start <=
                                             (4 * 2)))
                                        {
                                            /* convert user value to float */
                                            uint16_t val = atoi(
                                                (char *)(jsonStr +
                                                         jsonTokens[4].start));

                                            if (val >= 30)
                                            {
                                                /* store new value */
                                                dcin_periodic_timer_interval =
                                                    val;
                                            }
                                            else
                                            {
                                                CDC_sendJSON(
                                                    "error",
                                                    "value_out_of_range");
                                            }
                                        }
                                        else
                                        {
                                            CDC_sendJSON("error",
                                                         "value_too_large");
                                        }
#endif
                    }
                }
            }
            else if (strncmp((char const *)jsonStr + jsonTokens[1].start,
                             "outpostID", sizeof("outpostID") - 1) == 0)
            {
            }
            else if (strncmp((char const *)jsonStr + jsonTokens[1].start,
                             "GPIO_DEVICE_INFO",
                             sizeof("GPIO_DEVICE_INFO") - 1) == 0)
            {
            }
            else if (strncmp((char const *)jsonStr + jsonTokens[1].start,
                             "GPIO_PIN_CONFIG",
                             sizeof("GPIO_PIN_CONFIG") - 1) == 0)
            {
            }
            else if (strncmp((char const *)jsonStr + jsonTokens[1].start,
                             "GPIO_PIN_UPDATE",
                             sizeof("GPIO_PIN_UPDATE") - 1) == 0)
            {
            }
#endif
            else
            {
                status = 1;
            }
        }
        return status;
    }
}


static int32_t printf_CDC(const char *restrict fmt, ...)
{
    static uint8_t buf_idx;
    int            bytes_sent = 0;
    if (fmt != NULL)
    {
        memset(usbTxBuf[buf_idx], 0, sizeof(usbTxBuf[buf_idx]));
        va_list args;
        va_start(args, fmt);

        uint_least16_t       bytes_loaded;
        const uint_least16_t max_bytes =
            sizeof(usbTxBuf[buf_idx]) -
            (sizeof(USB_DELIMIT_STRING) + sizeof('\0')); /* room for delims */

        bytes_loaded = vsnprintf(usbTxBuf[buf_idx], max_bytes, fmt, args);
        va_end(args); /* end va_list as soon as we can, to save stack */
                      /* This is NOT a micro-optimization, each RTOS thread
                       * has limited stack size (~ SRAM_SIZE/(2*numthreads)) */

        if (bytes_loaded > max_bytes) /* check for truncated output */
        {
            memset(usbTxBuf[buf_idx], 0, sizeof(usbTxBuf[buf_idx]));
            bytes_loaded = snprintf(
                usbTxBuf[buf_idx], max_bytes,
                "couldn't load outgoing message format string \"%s\"", fmt);
        }

        /* Attach delimiter, even if in some cases it's redundant */
        char *res;
        res = strcat((char *)&usbTxBuf[bytes_loaded], USB_DELIMIT_STRING);
        if (res != NULL)
        {
            bytes_loaded += strlen(USB_DELIMIT_STRING);
        }
        else
        {
            bytes_sent = USB_TX_ERROR;
        }

        /* Transmit the buffer */
        if (USBD_OK == CDC_Transmit_FS(usbTxBuf[buf_idx], bytes_loaded))
        {
            bytes_sent = bytes_loaded;
        }
        else
        {
            /**
             * @note The STM32F4 USB CDC class library API sadly discards all
             * info regarding packet ACKS. Best we can do is indicate error to
             * caller, we don't know how many packets the host received.
             */
            bytes_sent = USB_TX_ERROR;

            /*
             * In practice, it's very unlikely (perhaps even impossible) to
             * transfer packets so fast from an embedded USB peripheral
             * that the host session FIFO gets overwhelmed.
             */
        }
        if (++buf_idx > 1)
        {
            buf_idx = 0;
        }
    }
    else
    {
        bytes_sent = USB_TX_ERROR;
    }
    return bytes_sent;
}
