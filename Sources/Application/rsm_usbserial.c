#define CURRENT_KEY_EQUAL(x) (strncmp((char const *)parser.buf + parser.tkns[tknIdex].start, x, strlen(x)) == 0)

void doUsbSerialTask(usbSerialTaskQ_t *TaskMessages, osMsgQHandles_t *messageQHandles)
{
    static uint32_t txBuf_index; /* transmission buffer can hold multiple payload strings. This is the index of the current Tx string */
    static jsonParser_t parser;  /* the JSON parser instance */
    uint16_t tknIdex = 0;

  
  if (xQueueReceive(messageQHandles->usbSerialMsgQHandle, (void *)(&TaskMessages->currentTask), (TickType_t)portMAX_DELAY) == pdTRUE)
  {
    if ((TASK_USBSERIAL_CTX_t)TaskMessages->currentTask.msg.context == TASK_USBSERIAL_CTX_receive)
    {
      if ((TASK_USBSERIAL_RECIEVE_EVT_t)TaskMessages->currentTask.msg.event == TASK_USBSERIAL_RECIEVE_EVT_message_received)
      {
        /* load command string and process */
        if (CDC_getCommandString(parser.buf, sizeof(parser.buf)) == 0)
        {

          /* parse command string */
          jsmn_init(&parser.tokenizer);

          //todo: revisit if 20 is the max number of tokens we'd expect. Probably not since tokens include all object start, end, keys, and values
          parser.initStatus = jsmn_parse(&parser.tokenizer, (const char *)parser.buf, sizeof(parser.buf), parser.tkns, MAX_PARSER_JSMNTOK_CNT);

          /* handle json command */
          if (parser.initStatus > 0 && parser.tkns[tknIdex].type == JSMN_OBJECT && parser.tkns[++tknIdex].type == JSMN_STRING)
          {
            if (CURRENT_KEY_EQUAL("GPIO_DEVICE_INFO"))
            {
              // Send a message to USB to output gpio payload
                TaskQueues->usbTask_dfmsg.callbackmsg.QId = messageQHandles->usbSerialMsgQHandle;
                TaskQueues->usbTask_dfmsg.callbackmsg.context = TASK_USBSERIAL_CTX_transmit;
                TaskQueues->usbTask_dfmsg.callbackmsg.event = TASK_USBSERIAL_TRANSMIT_EVT_send_dcin;
                xQueueSend(messageQHandles->defaultMsgQHandle, (void *)&TaskQueues->usbTask_dfmsg, 0);

            }
          }
        }
      }
    }
    if ((TASK_USBSERIAL_CTX_t)TaskQueues->usbTask_Q.msg.context == TASK_USBSERIAL_CTX_transmit)
    {
        switch ((TASK_USBSERIAL_TRANSMIT_EVT_t)TaskMessages->currentTask.msg.event)
        {
        case TASK_USBSERIAL_TRANSMIT_EVT_send_pinInfo:
            sendGPIOpayload_testHW(TaskMessages, &txBuf_index);
            //sendMotionPayload();
            //sendTempHumidityPayload();
            break;    
        }
    }

static void sendGPIOpayload_testHW(usbSerialTaskQ_t *TaskMessages, uint32_t *bufidx)
{
    uint32_t slen = 0;
    uint32_t numPinJsonsInArray = 0; //need this flag to prevent trailing comma in JSON
    uint32_t i = 0;
    uint32_t digital_input, adc_channel, adc_data;

    memset(usbTxBuf[*bufidx], 0, sizeof(usbTxBuf[*bufidx]));

    slen += sprintf((char *)usbTxBuf[*bufidx],"{\"GPIO_PIN_INFO\":\"PinInfo\":[");

    //add digital input interface info to payload (active pins)
    for (i = 0; i < MAX_DIGITAL_INPUTS; i++)
    {
        if (numPinJsonsInArray != 0) //if this isn't the first pin JSON in the pin array, prepend with comma
        {
            slen += sprintf((char *)usbTxBuf[*bufidx] + slen, ",");
        }
        switch(i)
        {
            case 0: digital_input = HAL_GPIO_ReadPin(DI0_GPIO_Port, DI0_Pin); break;
            case 1: digital_input = HAL_GPIO_ReadPin(DI1_GPIO_Port, DI1_Pin); break;
            case 2: digital_input = HAL_GPIO_ReadPin(DI2_GPIO_Port, DI2_Pin); break;
            case 3: digital_input = HAL_GPIO_ReadPin(DI3_GPIO_Port, DI3_Pin); break;
            case 4: digital_input = HAL_GPIO_ReadPin(DI4_GPIO_Port, DI4_Pin); break;
            case 5: digital_input = HAL_GPIO_ReadPin(DI5_GPIO_Port, DI5_Pin); break;
            case 6: digital_input = HAL_GPIO_ReadPin(DI6_GPIO_Port, DI6_Pin); break;
            case 7: digital_input = HAL_GPIO_ReadPin(DI7_GPIO_Port, DI7_Pin); break;
            default: digital_input = 2; break;
        }
        slen += sprintf((char *)usbTxBuf[*bufidx] + slen,
                    "{"
                    "\"di_pin\":\"%d\","
                    "\"level\":\"%d\"}",
                    i+1,
                    digital_input);

        numPinJsonsInArray++;
    }

    for (i = 0; i < MAX_ANALOG_INPUTS; i++)
    {
        if (numPinJsonsInArray != 0) //if this isn't the first pin JSON in the pin array, prepend with comma
        {
            slen += sprintf((char *)usbTxBuf[*bufidx] + slen, ",");
        }
        switch(i)
        {
            case 0: adc_channel = 6; break;
            case 1: adc_channel = 7; break;
            case 2: adc_channel = 8; break;
            case 3: adc_channel = 9; break;
            default: adc_channel = 6; break;
        }
        convertAnalogInput(adc_channel,&adc_data);

        slen += sprintf((char *)usbTxBuf[*bufidx] + slen,
                      "{"
                      "\"id\":\"%d\","
                      "\"voltage\":\"%u\"}",
                      i+1,
                      adc_data);
        numPinJsonsInArray++;
    }
  }

  //terminate parent JSON
  slen += sprintf((char *)usbTxBuf[*bufidx] + slen, "]}\r\n");

  while (CDC_Transmit_FS(usbTxBuf[*bufidx], slen) == USBD_BUSY)
  {
    osDelay(10);
  }
  *bufidx += 1;
}

static void sendMotionPayload_testHW(uint32_t *bufidx)
{
    uint32_t slen = 0;
    uint32_t motion_input;

    memset(usbTxBuf[*bufidx], 0, sizeof(usbTxBuf[*bufidx]));

    if(HAL_GPIO_ReadPin(MOTION_GPIO_Port, MOTION_Pin) == 0)
        slen += sprintf((char *)usbTxBuf[*bufidx],"{\"MOTION\": \"false\", \"status\": \"Active\"}");
    else
        slen += sprintf((char *)usbTxBuf[*bufidx],"{\"MOTION\": \"true\", \"status\": \"Active\"}");

  //terminate parent JSON
  slen += sprintf((char *)usbTxBuf[*bufidx] + slen, "\r\n");

  while (CDC_Transmit_FS(usbTxBuf[*bufidx], slen) == USBD_BUSY)
  {
    osDelay(10);
  }
  *bufidx += 1;
}


