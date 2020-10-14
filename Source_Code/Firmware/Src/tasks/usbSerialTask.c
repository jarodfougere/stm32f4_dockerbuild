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


/**
 * @brief send the keepalive json
 */
static void serial_tx_send_heartbeat(void);

/**
 * @brief send the digital input json
 */
static void serial_tx_send_dcin(void);


/**
 * @brief send gpio pin update done json */
static void serial_tx_sendDone(void);


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

                    serial_printf("TESTING PRINTF %s", "this_is_a_string");

                    /*
                    CDC_Transmit_FS((uint8_t *)"RECEIVED STUFF\r\n",
                                    sizeof("RECEIVED STUFF\r\n"));

                    */
#if 0
                    HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);

                    if (CDC_getCommandString(jsonStr, sizeof(jsonStr)) == 0)
                    {
                        if (serial_doReceive(jsonStr, strlen((char *)jsonStr)))
                        {
                            serial_sendJSON("error", "json_format");
                        }
                    }

#endif
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
                    serial_tx_send_dcin();
                }
                break;
                case TASK_USBSERIAL_TRANSMIT_EVENT_send_done:
                {
                    serial_tx_sendDone();
                }
                case TASK_USBSERIAL_TRANSMIT_EVENT_send_heartbeat:
                {
                    serial_tx_send_heartbeat();
                }
                break;
            }
        }
        break;
    }
}


static void serial_tx_send_dcin(void)
{
    /** @todo INTEGRATE FUNCTIONALITY FROM GPIO CODE */
#if 0
    uint8_t gpio_state = Q.sbtask.id;
    memset(usbSerialTxBuffer[buf_idx], 0, sizeof(usbSerialTxBuffer[buf_idx]));
    uint16_t slen = 0;
    slen += sprintf(
        (char *)usbSerialTxBuffer[buf_idx],
        "{\"GPIO_PIN_INFO\":\"active\","
        "\"device_id\":\"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\","
        "\"PinInfo\":[",
        *(((uint8_t *)(UID_BASE)) + 0), *(((uint8_t *)(UID_BASE)) + 1),
        *(((uint8_t *)(UID_BASE)) + 2), *(((uint8_t *)(UID_BASE)) + 3),
        *(((uint8_t *)(UID_BASE)) + 4), *(((uint8_t *)(UID_BASE)) + 5),
        *(((uint8_t *)(UID_BASE)) + 6), *(((uint8_t *)(UID_BASE)) + 7),
        *(((uint8_t *)(UID_BASE)) + 8), *(((uint8_t *)(UID_BASE)) + 9),
        *(((uint8_t *)(UID_BASE)) + 10), *(((uint8_t *)(UID_BASE)) + 11));
    /* add all active GPIO to message */
    int i          = 0;
    int first_flag = 0;
    do
    {
        if (systemconfig.config.gpio_config[i].active)
        {
            if (first_flag == 0)
            {
                first_flag = 1;
            }
            else
            {
                slen += sprintf((char *)usbSerialTxBuffer[buf_idx] + slen, ",");
            }

            slen += sprintf((char *)usbSerialTxBuffer[buf_idx] + slen,
                            "{"
                            "\"id\":\"%d\","
                            "\"type\":\"%d\","
                            "\"trigger\":\"%d\","
                            "\"debounce\":\"%d\","
                            "\"label\":\"%d\","
                            "\"active\":\"%d\","
                            "\"status\":\"%d\"}",
                            systemconfig.config.gpio_config[i].id,
                            systemconfig.config.gpio_config[i].type,
                            systemconfig.config.gpio_config[i].trigger,
                            systemconfig.config.gpio_config[i].debounce,
                            systemconfig.config.gpio_config[i].label,
                            systemconfig.config.gpio_config[i].active,
                            (gpio_state >> i) & 0x01);
        }
    } while (++i < MAXGPIOINNUM);

    /* terminate packet string */
    slen += sprintf((char *)usbSerialTxBuffer[buf_idx] + slen, "]}\r\n");

    /* send string */
    while (CDC_Transmit_FS(usbSerialTxBuffer[buf_idx], slen) == USBD_BUSY)
    {
        osDelay(10);
    }
    if (++buf_idx > 1)
        buf_idx = 0;
#endif
}


static void serial_tx_sendDone(void)
{
    serial_sendJSON("GPIO_PIN_UPDATE", "Done");

    /** @todo INTEGRATE FUNCTIONALITY FROM GPIO CODEBASE */

#if 0
    /* inform the digital input task state to return polling */
    memset((void *)&dimsg, 0, sizeof(dimsg));
    dimsg.msg.ctx = TASK_DCIN_CTX_poll;
    dimsg.msg.evt = TASK_DCIN_POLL_EVT_periodic_message;
    xQueueSend(dcInMsgQHandle, (void *)&dimsg, 0);
#endif
}


static void serial_tx_send_heartbeat(void)
{
    runtick += heartbeat_reporting_interval;

    /* clang-format off */
    serial_printf("{\"LPO_SYSTICK\":{"
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
                    serial_printf("{\"info\":{"
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
                    serial_printf("{ \"hwVersion\" : \"%2d.%-2d\" } ",
                                  HWVERSION_MAJOR, HWVERSION_MINOR);
                }
                else if (jutil_tokcmp("fwVersion", jsonStr, &jsonTokens[2]))
                {
                    serial_sendJSON("fwVersion", FWID_RELEASE);
                }
                else if (jutil_tokcmp("hb_interval", jsonStr, &jsonTokens[2]))
                {
                    serial_printf("{ \"hb_interval\" : \"%5d\"}",
                                  heartbeat_reporting_interval);
                }
                else if (jutil_tokcmp("pin_info_interval", jsonStr,
                                      &jsonTokens[2]))
                {
                    serial_printf("{ \"pin_info_interval\" : \"%5d\"}",
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
                        if (jsonTokens[4].type == JSMN_STRING ||
                            jsonTokens[4].end - jsonTokens[4].start <= (4 * 2))
                        {

                            /** @note atoi is not safe. refactor with strtoul or
                             * snprintf.
                             *
                             * in the original gpio code, it was used because
                             * it was an easy way to have the string -> int
                             * conversion automatically end when the json
                             * token was not nul-terminated
                             */
                            uint16_t new_val =
                                atoi((char *)(jsonStr + jsonTokens[4].start));

                            if (new_val >= MIN_HEARTBEAT_REPORTING_INTERVAL_S)
                            {
                                /* store new value */
                                heartbeat_reporting_interval = new_val;
                            }
                            else
                            {
                                serial_sendJSON("error", "value_out_of_range");
                            }
                        }
                        else
                        {
                            serial_sendJSON("error", "value_too_large");
                        }
                    }
                    else if (jutil_tokcmp("pin_info_interval", jsonStr,
                                          &jsonTokens[3]))
                    {
                        if (jsonTokens[4].type == JSMN_STRING ||
                            jsonTokens[4].end - jsonTokens[4].start <= (4 * 2))
                        {

                            /** @note atoi is not safe. refactor with strtoul or
                             * snprintf.
                             *
                             * in the original gpio code, it was used because
                             * it was an easy way to have the string -> int
                             * conversion automatically end when the json
                             * token was not nul-terminated
                             */
                            uint16_t new_val =
                                atoi((char *)(jsonStr + jsonTokens[4].start));

                            if (new_val >= MIN_DCIN_PERIODIC_TIMER_INTERVAL_S)
                            {
                                /* store new value */
                                dcin_periodic_timer_interval = new_val;
                            }
                            else
                            {
                                serial_sendJSON("error", "value_out_of_range");
                            }
                        }
                        else
                        {
                            serial_sendJSON("error", "value_too_large");
                        }
                    }
                    else
                    {
                        /** @todo INVALID WRITE COMMAND */
                    }
                }
            }
            if (jutil_tokcmp("outpostID", jsonStr, &jsonTokens[1]))
            {
                if ((jsonTokens[2].type == JSMN_STRING) ||
                    (jsonTokens[2].end - jsonTokens[2].start == (6 * 2)))
                {
                    /* literally no clue why the code has 6 * 2 instead of 12 */
                    char id[(6 * 2)];
                    jutil_tokcpy(id, sizeof(id), jsonStr, &jsonTokens[2]);
                    serial_printf("RECEIVED OUTPOST ID : %s", id);

                    /** @todo INTEGRATE FUNCTIONALITY FROM GPIO CODEBASE. I HAVE
                     * ADDED AN ECHO MESSAGE THINGY FOR NOW */
#if 0
                    /* compare ID with stored value */
                    if (strncmp((char const *)jsonStrBuf + jsonTokens[2].start,
                                (char const *)systemconfig.config.outpostID,
                                6) == 0)
                    {
                        memset(&dfmsg, 0, sizeof(dfmsg));
                        dfmsg.msg.evt = TASK_DEFAULT_EVT_active_state;
                        xQueueSend(defaultMsgQHandle, (void *)&dfmsg, 0);
                    }
                    else
                    {
                        strncpy((char *)outpostID,
                                (char *)(jsonStrBuf + jsonTokens[2].start), 6);
                        memset(&dfmsg, 0, sizeof(dfmsg));
                        dfmsg.msg.evt = TASK_DEFAULT_EVT_clear_config;
                        xQueueSend(defaultMsgQHandle, (void *)&dfmsg, 0);
                    }
#endif
                }
                else
                {
                    serial_sendJSON("error", "ID string wrong size");
                }
            }

            else if (jutil_tokcmp("LPO_DEVICE_INFO", jsonStr, &jsonTokens[1]))
            {
                serial_printf("{\"LPO_DEVICE_INFO\" : \"active\","
                              "\"device_id\":\"%08x%08x%08x\","
                              "\"inputs\":\"%d\""
                              "\"outputs\":\"%d\""
                              "\"analogs\":\"%d\""
                              "\"rf_sensors\":\"%d\""
                              "\"moth_sensors\":\"%d\"}",
                              *(uint32_t *)(DEVICE_ID1),
                              *(uint32_t *)(DEVICE_ID2),
                              *(uint32_t *)(DEVICE_ID3), MAX_DIGITAL_INS,
                              MAX_DIGITAL_OUTS, MAX_ANALOG_INS, MAX_RF_SENSORS,
                              MAX_MOTH_SENSORS);
            }
            else if (jutil_tokcmp("LPO_PIN_CONFIG", jsonStr, &jsonTokens[1]))
            {
                if (jsonTokens[2].type == JSMN_OBJECT)
                {
                    /** @todo INTEGRATE LOGIC FROM GPIO CODE */
#if 0
                /* load pin configuration heap with current settings */
                  int       i           = 3;
                  uint8_t   id          = 0xFF; // set to 0xFF to indicate valid id not found
                  uint16_t  tmp;
                  uint8_t   num_fields  = 0;
                  do
                  {
                    /* check for valid token */
                    if (strncmp((char const *)jsonStrBuf+jsonTokens[i].start,"id",2)==0)
                    {
                      /* load id */
                      i++;
                      id = atoi((char*)(jsonStrBuf+jsonTokens[i].start));
                      if ((id<1)||(id>MAXGPIONUM))
                      {
                        CDC_sendJSON("GPIO_PIN_CONFIG","pin_id_outofrange");
                        break;
                      }
                      else
                      {
                        num_fields++;
                        i++;
                        id--;
                        systemconfig_heap.config.gpio_config[id].id = id+1;
                      }
                    }
                    else if (strncmp((char const *)jsonStrBuf+jsonTokens[i].start,"type",4)==0)
                    {
                      i++;
                      if (id<MAXGPIONUM)
                      {
                        tmp = atoi((char*)(jsonStrBuf+jsonTokens[i].start));
                        if (tmp<2)
                        {
                          num_fields++;
                          i++;
                          systemconfig_heap.config.gpio_config[id].type  = (uint8_t)tmp;
                        }
                        else
                        {
                          CDC_sendJSON("GPIO_PIN_CONFIG","pin_type_outofrange");
                          break;
                        }
                      }
                    }
                    else if (strncmp((char const *)jsonStrBuf+jsonTokens[i].start,"trigger",7)==0)
                    {
                      i++;
                      if (id<MAXGPIONUM)
                      {
                        tmp = atoi((char*)(jsonStrBuf+jsonTokens[i].start));
                        if (tmp<2)
                        {
                          num_fields++;
                          i++;
                          systemconfig_heap.config.gpio_config[id].trigger = (uint8_t)tmp;
                        }
                        else
                        {
                          CDC_sendJSON("GPIO_PIN_CONFIG","pin_trigger_outofrange");
                          break;
                        }
                      }
                    }
                    else if (strncmp((char const *)jsonStrBuf+jsonTokens[i].start,"debounce",8)==0)
                    {
                      i++;
                      if (id<MAXGPIONUM)
                      {
                        tmp = atoi((char*)(jsonStrBuf+jsonTokens[i].start));
//                        if (tmp>=0)
//                        {
                          num_fields++;
                          i++;
                          systemconfig_heap.config.gpio_config[id].debounce = (uint16_t)tmp;
//                        }
//                        else
//                        {
//                          CDC_sendJSON("GPIO_PIN_CONFIG","pin_debounce_outofrange");
//                          break;
//                        }
                      }
                    }
                    else if (strncmp((char const *)jsonStrBuf+jsonTokens[i].start,"label",5)==0)
                    {
                      i++;
                      if (id<MAXGPIONUM)
                      {
                        tmp = atoi((char*)(jsonStrBuf+jsonTokens[i].start));
                        num_fields++;
                        i++;
                        systemconfig_heap.config.gpio_config[id].label = (uint8_t)tmp;
                      }
                    }
                    else if (strncmp((char const *)jsonStrBuf+jsonTokens[i].start,"active",6)==0)
                    {
                      i++;
                      if (id<MAXGPIONUM)
                      {
                        tmp = atoi((char*)(jsonStrBuf+jsonTokens[i].start));
                        if (tmp<2)
                        {
                          num_fields++;
                          i++;
                          systemconfig_heap.config.gpio_config[id].active = (uint8_t)tmp;
                        }
                        else
                        {
                          CDC_sendJSON("GPIO_PIN_CONFIG","pin_active_outofrange");
                          break;
                        }
                      }
                    }
                    else
                    {
                      /* unrecognized type */
                      CDC_sendJSON("error","unrecognized_pin_config_type");:
                      break;
                    }

                  } while(jsonTokens[i].type!=JSMN_PRIMITIVE);

                  /* send success message */
                  if (num_fields==6)
                  {
                    CDC_sendJSON("GPIO_PIN_CONFIG","ok");
                  }

#endif
                }
            }
            else if (jutil_tokcmp("LPO_PIN_UPDATE", jsonStr, &jsonTokens[1]))
            {

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
