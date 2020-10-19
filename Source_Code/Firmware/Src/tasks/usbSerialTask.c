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
static jsmntok_t     jTkns[MAX_JSON_TOKEN_COUNT];
static uint8_t       jStr[MAX_JSON_STRLEN];
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
static int32_t serial_printf(const char *restrict fmt, ...);


/**
 * @brief API wrapper for transmitting a key value pair
 *
 * @param key char* json key
 * @param value char *value
 *
 * @note KEY AND VALUE MUST BE NUL-TERMINATED
 */
static void serial_sendJSON(const char *key, const char *value);


/**
 * @brief (Attempts to) Parse a string as a json and execute its payload
 *         base on contents
 *
 * @param str the char array
 * @param len length of the char array
 * @return int 0 on successful parse and execution, !0 otherwise
 */
static int serial_doReceive(uint8_t *str, uint_least16_t len);


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
                    if (CDC_getCommandString(jStr, sizeof(jStr)) == 0)
                    {
                        serial_printf("[USB RECIEVE] : %s\n", jStr);
                        if (serial_doReceive(jStr, strlen((char *)jStr)))
                        {
                            serial_sendJSON("error", "json_format");
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


static void serial_tx_send_heartbeat(void)
{
    /** @todo INCREMENT RUNTICK */

    /* clang-format off */
    serial_printf("{\"GPIO_SYSTICK\":{"
                  "\"model_name\":\"%s\","
                  "\"device_name\":\"%s\","
                  "\"device_id\":\"%08x%08x%08x\","
                  "\"uptime\":{\"value\":\"%ld\",\"units\":\"seconds\"}"
                  "}}\r\n",
                  DEVICE_NAME_STRING, 
                  getDeviceName(),
                  *(uint32_t *)(DEVICE_ID1), 
                  *(uint32_t *)(DEVICE_ID2),
                  *(uint32_t *)(DEVICE_ID3), 
                  runtick);
    /* clang-format on */
}


static int serial_doReceive(uint8_t *str, uint_least16_t len)
{
    int status = 0;
    if (str == NULL)
    {
        status = -1;
    }
    else
    {
        jsmn_init(&jsonParser);
        jsonRetval = jsmn_parse(&jsonParser, (const char *)jStr, sizeof(jStr),
                                jTkns, MAX_JSON_TOKEN_COUNT);


        return status;

        uint_fast8_t t = 1; /* token index */
        if (jsonRetval > 0 && isValidJson(jTkns, MAX_JSON_TOKEN_COUNT))
        {
            if (jutil_tokcmp("system", jStr, &jTkns[t]))
            {
                t++;
                if (jutil_tokcmp("reset_main", jStr, &jTkns[t]))
                {
                    systemReset();
                }
                else if (jutil_tokcmp("reset_boot", jStr, &jTkns[t]))
                {
                    jumpToBootloader();
                }
                else if (jutil_tokcmp("info", jStr, &jTkns[t]))
                {
                }
                else if (jutil_tokcmp("sleep", jStr, &jTkns[t]))
                {
                    /** @todo ENTER LOW POWER MODE */
                }
                else
                {
                    /** @todo some sort of error flag? */
                }
            }
            else if (jutil_tokcmp("read", jStr, &jTkns[t]))
            {
                t++;
                if (jutil_tokcmp("hwVersion", jStr, &jTkns[t]))
                {
                    serial_printf("{ \"hwVersion\" : \"%2d.%-2d\" } ",
                                  HWVERSION_MAJOR, HWVERSION_MINOR);
                }
                else if (jutil_tokcmp("fwVersion", jStr, &jTkns[t]))
                {
                    serial_sendJSON("fwVersion", FWID_RELEASE);
                }
                else if (jutil_tokcmp("hb_interval", jStr, &jTkns[t]))
                {
                }
                else if (jutil_tokcmp("pin_info_interval", jStr, &jTkns[t]))
                {
                }
                else
                {
                    /** @todo ERROR: INVALID READ COMMAND */
                }
            }
            else if (jutil_tokcmp("write", jStr, &jTkns[t]))
            {
                t++;
            }
            if (jutil_tokcmp("outpostID", jStr, &jTkns[t]))
            {
                t++;
                uint_least8_t id_len = jutil_toklen(&jTkns[t]);
                if (id_len == OUTPOST_ID_STRLEN)
                {
                    DEFAULTMSGQ_t dflt;
                    memset(&dflt, 0, sizeof(dflt));

                    /* if outpost ids are equal, load into ram from eeprom */

                    /* if unequal, overwrite config with defaults and store to
                     * eeprom */

                    dflt.msg.ctx = TASK_DEFAULT_CONTEXT_config;
                }
                else if (id_len > OUTPOST_ID_STRLEN)
                {
                    serial_sendJSON("outpost_idErr",
                                    "outpost_id_stringTooLong");
                }
                else
                {
                    serial_sendJSON("outpost_idErr",
                                    "outpost_id_stringTooShort");
                }
            }

            else if (jutil_tokcmp("GPIO_DEVICE_INFO", jStr, &jTkns[t]))
            {
                t++;
            }
            else if (jutil_tokcmp("GPIO_PIN_CONFIG", jStr, &jTkns[t]))
            {
                t++;
                if (jTkns[t].type == JSMN_OBJECT)
                {
                    /** @todo INTEGRATE LOGIC FROM GPIO CODE */
                }
                else
                {
                    serial_sendJSON(
                        "Error", "expected JSMN OBJECT after GPIO_PIN_CONFIG");
                }
            }
            else if (jutil_tokcmp("GPIO_PIN_UPDATE", jStr, &jTkns[t]))
            {
                t++;
                /** @todo INTEGRATE FUNCTIONALITY FROM GPIO CODE */

#if 0
                  /* write systemconfig heap to EEPROM */
                  memset(&dfmsg,0,sizeof(dfmsg));
                  dfmsg.msg.evt   = TASK_DEFAULT_EVT_store_config;
                  dfmsg.cbmsg.QId = usbSerialMsgQHandle;
                  dfmsg.cbmsg.ctx = TASK_USBSERIAL_CTX_transmit;
                  dfmsg.cbmsg.evt = TASK_USBSERIAL_TRANSMIT_EVT_send_done;
                  xQueueSend(defaultMsgQHandle,(void*)&dfmsg,0);
#endif
            }
            else if (jutil_tokcmp("GPIO_PIN_CMD", jStr, &jTkns[t]))
            {
                t++;
            }
            else
            {
                status = 1;
            }
        }
    }
    return status;
}


static int32_t serial_printf(const char *restrict fmt, ...)
{
    static uint8_t buf_idx;
    int            bytes_sent = 0;
    if (fmt != NULL)
    {
        memset(usbTxBuf[buf_idx], 0, sizeof(usbTxBuf[buf_idx]));
        va_list args;
        va_start(args, fmt);

        uint_least16_t bytes_loaded;

        /* max size leaves room for delims */
        const uint_least16_t max_bytes =
            sizeof(usbTxBuf[buf_idx]) -
            (sizeof(USB_DELIMIT_STRING) + sizeof((char)'\0'));
        /* and for crying out loud, please don't remove the cast to char */

        bytes_loaded =
            vsnprintf((char *)usbTxBuf[buf_idx], max_bytes, fmt, args);
        va_end(args); /* end va_list as soon as we can, to save
                         stack */
        /* This is NOT a micro-optimization, each RTOS thread
         * has limited stack size (~ SRAM_SIZE/(2*numthreads)) */

        if (bytes_loaded > max_bytes) /* check for truncated output */
        {
            memset(usbTxBuf[buf_idx], 0, sizeof(usbTxBuf[buf_idx]));
            bytes_loaded = snprintf((char *)usbTxBuf[buf_idx], max_bytes,
                                    "couldn't load outgoing "
                                    "message format string \"%s\"",
                                    fmt);
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
             * @note The STM32F4 USB CDC class library API sadly
             * discards all info regarding packet ACKS. Best we can
             * do is indicate error to caller, we don't know how
             * many packets the host received.
             */
            bytes_sent = USB_TX_ERROR;

            /*
             * In practice, it's very unlikely (perhaps even
             * impossible) to transfer packets so fast from an
             * embedded USB peripheral that the host session FIFO
             * gets overwhelmed.
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


static void serial_sendJSON(const char *key, const char *value)
{
    if (key != NULL && value != NULL)
    {
        /* sometimes compilers assume release as default */
#if defined(DEBUG) || !defined(NDEBUG)
        uint32_t bytes_sent = serial_printf("{\"%s\" : \"%s\"}", key, value);
        if (bytes_sent == USB_TX_ERROR)
        {
            serial_printf("error with %s in %s on line %s", __func__, __FILE__,
                          __LINE__);
        }
#else
        serial_printf("{\"%s\" : \"%s\"}", key, value);
#endif
    }
}


/*
 *
 * #ifdef DEBUG
 #define dmsg(fmt, args...) printf(fmt, ##args)
#else
 #define dmsg(fmt, args...)
#endif
 *
 *
 *
 *
 */