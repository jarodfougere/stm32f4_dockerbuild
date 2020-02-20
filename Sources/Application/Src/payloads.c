#include <string.h>
#include <time.h> /* eventually we want to add timestamps to payloads */

#include "payloads.h"
#include "middleware.h"

void doDoSysCommand(const char* cmd_string)
{
    if(0 == strncmp(cmd_string, "info", sizeof("info") - 1))
    {

    }
    else if (0 == strncmp(cmd_string, "reset_boot", sizeof("reset_boot") - 1))
    {
    }
    else if (0 == strncmp(cmd_string, "reset_main", sizeof("reset_main") - 1))
    {
        
    }
    else if(0 == strncmp(cmd_string, "mode", sizeof("mode") - 1))
    {

    }
    else if (0 == strncmp(cmd_string, "hb_interval", sizeof("hb_interval") - 1))
    {
    }
    else if (0 == strncmp(cmd_string, "pin_info_interval", sizeof("pin_info_interval") - 1) 
    || 
    /* add data interval command now to provision for future */
    0 == strncmp(cmd_string, "data_interval", sizeof("data_interval") - 1)) 
    {
        
    }
    else if (0 == strncmp(cmd_string, "fwVersion", sizeof("fwVersion") - 1))
    {

    }
    else if (0 == strncmp(cmd_string, "hwVersion", sizeof("hwVersion") - 1))
    {
    }
}



/*
static void transmitSysTick(uint32_t *buf_i)
{
  memset(usbTxBuf[*buf_i], 0, sizeof(usbTxBuf[*buf_i]));
  runtick += systemconfig.sysTickInterval;
  sprintf((char *)usbTxBuf[*buf_i],
          "{\"GPIO_SYSTICK\":{"
          "\"model_name\":\"%s\","
          "\"device_name\":\"%s\","
          "\"device_id\":\"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\","
          "\"uptime\":{\"value\":\"%ld\",\"units\":\"seconds\"}"
          "}}\r\n",
          "Rimot GPIO Monitor",
          "Unnamed",
          *(((uint8_t *)(UID_BASE)) + 0x00), *(((uint8_t *)(UID_BASE)) + 0x01),
          *(((uint8_t *)(UID_BASE)) + 0x02), *(((uint8_t *)(UID_BASE)) + 0x03),
          *(((uint8_t *)(UID_BASE)) + 0x04), *(((uint8_t *)(UID_BASE)) + 0x05),
          *(((uint8_t *)(UID_BASE)) + 0x06), *(((uint8_t *)(UID_BASE)) + 0x07),
          *(((uint8_t *)(UID_BASE)) + 0x14), *(((uint8_t *)(UID_BASE)) + 0x15),
          *(((uint8_t *)(UID_BASE)) + 0x16), *(((uint8_t *)(UID_BASE)) + 0x17),
          runtick);
  CDC_Transmit_FS(usbTxBuf[*buf_i], strlen((char const *)usbTxBuf[*buf_i]));
  *buf_i += 1;
}





static void transmitPinInfo(usbSerialTaskQ_t *TaskMessages, uint32_t *bufidx)
{
  uint_fast32_t slen = 0;
  uint_fast32_t numPinJsonsInArray = 0; //need this flag to prevent trailing comma in JSON
  memset(usbTxBuf[*bufidx], 0, sizeof(usbTxBuf[*bufidx]));
  slen += sprintf((char *)usbTxBuf[*bufidx],
                  "{\"GPIO_PIN_INFO\":\"active\","
                  "\"device_id\":\"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\","
                  "\"PinInfo\":[",
                  *(((uint8_t *)(UID_BASE)) + 0x00), *(((uint8_t *)(UID_BASE)) + 0x01),
                  *(((uint8_t *)(UID_BASE)) + 0x02), *(((uint8_t *)(UID_BASE)) + 0x03),
                  *(((uint8_t *)(UID_BASE)) + 0x04), *(((uint8_t *)(UID_BASE)) + 0x05),
                  *(((uint8_t *)(UID_BASE)) + 0x06), *(((uint8_t *)(UID_BASE)) + 0x07),
                  *(((uint8_t *)(UID_BASE)) + 0x14), *(((uint8_t *)(UID_BASE)) + 0x15),
                  *(((uint8_t *)(UID_BASE)) + 0x16), *(((uint8_t *)(UID_BASE)) + 0x17));
  int32_t i = 0;

  //add digital input interface info to payload (active pins)
  for (i = 0; i < MAX_DIGITAL_INPUTS; i++)
  {
    if (systemconfig.digitalIns[i].cfg.active == ACTIVE)
    {
      if (numPinJsonsInArray != 0) //if this isn't the first pin JSON in the pin array, prepend with comma
      {
        slen += sprintf((char *)usbTxBuf[*bufidx] + slen, ",");
      }
      slen += sprintf((char *)usbTxBuf[*bufidx] + slen,
                      "{"
                      "\"id\":\"%d\","
                      "\"type\":\"%d\","
                      "\"trigger\":\"%d\","
                      "\"debounce\":\"%d\","
                      "\"label\":\"%d\","
                      "\"active\":\"%d\","
                      "\"status\":\"%u\"}",
                      systemconfig.digitalIns[i].cfg.id,
                      systemconfig.digitalIns[i].cfg.type,
                      systemconfig.digitalIns[i].interface.triglvl,
                      systemconfig.digitalIns[i].interface.debounce,
                      systemconfig.digitalIns[i].cfg.label,
                      systemconfig.digitalIns[i].cfg.active,
                      (pinInfoPayload.digitalInputStates >> i) & 0x01);
      numPinJsonsInArray++;
    }
  }

  //add relay interface info to payload (active pins)
  for (i = 0; i < MAX_RELAY_OUTPUTS; i++)
  {
    if (systemconfig.relays[i].cfg.active == ACTIVE)
    {
      if (numPinJsonsInArray != 0) //if this isn't the first pin JSON in the pin array, prepend with comma
      {
        slen += sprintf((char *)usbTxBuf[*bufidx] + slen, ",");
      }
      slen += sprintf((char *)usbTxBuf[*bufidx] + slen,
                      "{"
                      "\"id\":\"%d\","
                      "\"type\":\"%d\","
                      "\"state\":\"%d\"," //default relay position as configured
                      "\"debounce\":\"%d\","
                      "\"label\":\"%d\","
                      "\"active\":\"%d\","
                      "\"status\":\"%d\"}", //current relay position
                      systemconfig.relays[i].cfg.id,
                      systemconfig.relays[i].cfg.type,
                      systemconfig.relays[i].interface.defaultState,
                      systemconfig.relays[i].interface.holdTime,
                      systemconfig.relays[i].cfg.label,
                      systemconfig.relays[i].cfg.active,
                      systemconfig.relays[i].interface.currentState);
      numPinJsonsInArray++;
    }
  }

#if defined(BOARD_V3)
  //add battery monitoring interface info to payload (active pins)
  for (i = 0; i < MAX_ANALOG_INPUTS; i++)
  {
    if (systemconfig.analogIns[i].cfg.active == ACTIVE)
    {
      if (numPinJsonsInArray != 0) //if this isn't the first pin JSON in the pin array, prepend with comma
      {
        slen += sprintf((char *)usbTxBuf[*bufidx] + slen, ",");
      }
      slen += sprintf((char *)usbTxBuf[*bufidx] + slen,
                      "{"
                      "\"id\":\"%d\","
                      "\"type\":\"%d\","
                      "\"label\":\"%d\","
                      "\"active\":\"%d\","
                      "\"debounce\":\"%d\","
                      "\"battType\":\"%u\","
                      "\"redHigh\":\"%u\","
                      "\"redLow\":\"%u\","
                      "\"yellowHigh\":\"%u\","
                      "\"yellowLow\":\"%u\","
                      "\"voltage\":\"%u\"}",
                      systemconfig.analogIns[i].cfg.id,
                      systemconfig.analogIns[i].cfg.type,
                      systemconfig.analogIns[i].cfg.label,
                      systemconfig.analogIns[i].cfg.active,
                      systemconfig.analogIns[i].interface.samplePeriod,
                      systemconfig.analogIns[i].interface.battType,
                      systemconfig.analogIns[i].interface.redHigh,
                      systemconfig.analogIns[i].interface.redLow,
                      systemconfig.analogIns[i].interface.yellowHigh,
                      systemconfig.analogIns[i].interface.yellowLow,
                      pinInfoPayload.batteryMV[i]);
      numPinJsonsInArray++;
    }
  }
#endif

  //terminate parent JSON
  slen += sprintf((char *)usbTxBuf[*bufidx] + slen, "]}\r\n");

  while (CDC_Transmit_FS(usbTxBuf[*bufidx], slen) == USBD_BUSY)
  {
    osDelay(10);
  }
  *bufidx += 1;
}




memset(usbTxBuf[txBuf_index], 0, sizeof(usbTxBuf[txBuf_index]));
                  sprintf((char *)usbTxBuf[txBuf_index],
                          "{\"info\":{"
                          "\"model_name\":\"%s\","
                          "\"device_id\":\"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\","
                          "\"hw_version\":\"%2d.%-2d\","
                          "\"fw_version\":\"%s\""
                          "}}\r\n",
                          "GPIO",
                          *(((uint8_t *)(UID_BASE)) + 0x00), *(((uint8_t *)(UID_BASE)) + 0x01), *(((uint8_t *)(UID_BASE)) + 0x02), *(((uint8_t *)(UID_BASE)) + 0x03),
                          *(((uint8_t *)(UID_BASE)) + 0x04), *(((uint8_t *)(UID_BASE)) + 0x05), *(((uint8_t *)(UID_BASE)) + 0x06), *(((uint8_t *)(UID_BASE)) + 0x07),
                          *(((uint8_t *)(UID_BASE)) + 0x14), *(((uint8_t *)(UID_BASE)) + 0x15), *(((uint8_t *)(UID_BASE)) + 0x16), *(((uint8_t *)(UID_BASE)) + 0x17),
                          HWVERSION_MAJOR,
                          HWVERSION_MINOR,
                          FWID_RELEASE);



                          sprintf((char *)usbTxBuf[txBuf_index],
                      "{\"GPIO_DEVICE_INFO\":\"active\","
                      "\"device_id\":\"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\","
                      "\"inputs\":\"%d\","
                      "\"outputs\":\"%d\","
#if defined(BOARD_V3)
                      "\"batteryMonitoring\":\"%d\""
#endif
                      "}\r\n",


*/