//  MCU IO Pin COntrol
// The following structure controls the mode and state for each pin of a port.
typedef struct
{
  __IO uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  __IO uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IO uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IO uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  __IO uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  __IO uint32_t BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
  __IO uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IO uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} GPIO_TypeDef;

typedef struct
{
  uint32_t Pin;    /*Specifies the GPIO pins to be configured. */
  uint32_t Mode;   /*Specifies the operating mode for the selected pins. */
  uint32_t Pull;   /*Specifies the Pull-up or Pull-Down activation for the selected pins. */
  uint32_t Speed;     /*!< Specifies the speed for the selected pins. */
  uint32_t Alternate;  /*!< Peripheral to be connected to the selected pins. */
}GPIO_InitTypeDef;

// In RF Sensor repository, pin configuration is handled (mostly) in gpio.c and adc.c.
// Unused pins are configured in gpio.c. In RF Sensor they are put into an 'Analog mode' (??)
// Initialization is done by writing defined values into a structure type GPIO_InitTypeDef.
// The function HAL_GPIO_Init() is called to configure the appropriate port pointer. This function
// updates parameters in port GPIO_TypeDef STRUCT.
GPIO_InitStruct.Pin = GPIO_PIN_2;
GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init(<port GPIO_TypeDef pointer>, <address of structure with configuration>);
HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

// Example of reading a pin (no HAL function to do a multibit read of a port)
HAL_GPIO_ReadPin(<port GPIO_TypeDef pointer>, <32bit mask indicating bit to be read>)
HAL_GPIO_ReadPin(GPIOA, DIGITAL_INPUT_0_PIN)
// Example for writing common value to two pins (no HAL function to write multibit value to a port)
HAL_GPIO_WritePin(<port GPIO_TypeDef pointer>, <32bit mask indicating bits to be written>, <value>);
HAL_GPIO_WritePin(GPIOB, LED_0_EN_Pin|LED_1_EN_Pin, GPIO_PIN_RESET);

  
typedef enum  // from gpio.h
{
  INVALID_TRIGGER_LEVEL = 0xff,
  FALLING = 0x00,
  RISING = 0x01,
} triggerType_t;

typedef struct  // from gpio.h
{
  uint16_t debounce;     //debounce time in multiples of 100ms.
  triggerType_t triglvl; //trigger level (rising or falling edge)
} inputInterface_t;

typedef struct  // from gpio.h
{
  GPIO_TypeDef *port;
  uint16_t bit;
} mcuGPIO_t;

typedef enum  // from gpio.h
{
  INVALID_PIN_TYPE = 0xff,
  DIGITAL_INPUT = 0x00,
  LATCHING_RELAY = 0x01,
  ANALOG_INPUT = 0x02,
} pinType_t;

typedef enum  // from gpio.h
{
  INVALID_ACTIVE_STATE = 0xff,
  INACTIVE = 0x00,
  ACTIVE = 0x01,
} activeType_t;

typedef struct  // from gpio.h
{
  pinType_t type;       //the type of "pin" (input, output, analog input, etc...)
  activeType_t active;  //whether or not the pin is registered on site page
  uint16_t id;          //the "pin" number on the decal
  uint16_t label;       //Normalized "type" of the device being controlled/monitored.
  uint8_t priority;     //device priority as assigned on site page. ADDED AS FUTUREPROOFING
  uint32_t dummy;       //used for word alignment.
} pinConfig_t;

typedef struct  // from gpio.h
{
  pinConfig_t cfg;            //fields common for all deviceGPIO types
  mcuGPIO_t mcupin;           //the input pin on the mcu
//  RGled_t led;              //not used on LPS
  inputInterface_t interface; //interface specific values
  uint32_t dummy; //need to pack the structs and realign with dummy word since eeprom page size is only 1 word
} digitalInput_t;

typedef struct  // from gpio.h
{
  char outpostID[OUTPOST_ID_STRLEN + 1]; //+1 FOR \0
  digitalInput_t digitalIns[MAX_DIGITAL_INPUTS];
//  relayOutput_t relays[MAX_RELAY_OUTPUTS];
//  analogInput_t analogIns[MAX_ANALOG_INPUTS];
} systemConfig_t;        

// This structure is updated in 'doDcInTask' which is called periodically by RTOS.
// 'doDcInTask' initializes the structure when first called, then goes into timed polling mode
// 'doDcInTask' does the actual MCU PIN read      
// 'doDcInTask' sends an RTOS message for GPIO_PIN_INFO to be sent (below) if there is a change on a DI  
const systemConfig_t systemconfig;        


            if (CURRENT_KEY_EQUAL("GPIO_DEVICE_INFO"))
            {
                //Don't bother sending this for now. Only needed when connecting to LPO
                /*memset(usbSerialTxBuffer[txBuf_index], 0, sizeof(usbSerialTxBuffer[txBuf_index]));
                sprintf((char *)usbSerialTxBuffer[txBuf_index], "{\"GPIO_DEVICE_INFO\":\"active\","
                                                              "\"device_id\":\"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\","
                                                              "\"inputs\":\"%d\","
                                                              "\"outputs\":\"%d\""
                                                              "\"batteryMonitoring\":\"%d\""
                                                              "}\r\n",
                      *(((uint8_t *)(UID_BASE)) + 0x00), *(((uint8_t *)(UID_BASE)) + 0x01), *(((uint8_t *)(UID_BASE)) + 0x02), *(((uint8_t *)(UID_BASE)) + 0x03),
                      *(((uint8_t *)(UID_BASE)) + 0x04), *(((uint8_t *)(UID_BASE)) + 0x05), *(((uint8_t *)(UID_BASE)) + 0x06), *(((uint8_t *)(UID_BASE)) + 0x07),
                      *(((uint8_t *)(UID_BASE)) + 0x14), *(((uint8_t *)(UID_BASE)) + 0x15), *(((uint8_t *)(UID_BASE)) + 0x16), *(((uint8_t *)(UID_BASE)) + 0x17),
                      MAX_DIGITAL_INPUTS,
                      MAX_RELAY_OUTPUTS,
                      MAX_ANALOG_INPUTS
              );
              CDC_Transmit_FS(usbSerialTxBuffer[txBuf_index], strlen((char const *)usbSerialTxBuffer[txBuf_index]));
              if (++txBuf_index > 1)
              {
                txBuf_index = 0;
              }*/

              // Send a message to USB print Digital input payload
                TaskQueues->usbTask_dfmsg.callbackmsg.QId = messageQHandles->usbSerialMsgQHandle;
                TaskQueues->usbTask_dfmsg.callbackmsg.context = TASK_USBSERIAL_CTX_transmit;
                TaskQueues->usbTask_dfmsg.callbackmsg.event = TASK_USBSERIAL_TRANSMIT_EVT_send_dcin;
                xQueueSend(messageQHandles->defaultMsgQHandle, (void *)&TaskQueues->usbTask_dfmsg, 0);

            }





    if ((TASK_USBSERIAL_CTX_t)TaskQueues->usbTask_Q.msg.context == TASK_USBSERIAL_CTX_transmit)
    {
      if ((TASK_USBSERIAL_TRANSMIT_EVT_t)TaskQueues->usbTask_Q.msg.event == TASK_USBSERIAL_TRANSMIT_EVT_send_dcin)
      {      
        uint8_t gpio_state = TaskQueues->usbTask_Q.subtask.id;
        memset(usbSerialTxBuffer[txBuf_index], 0, sizeof(usbSerialTxBuffer[txBuf_index]));
        uint16_t slen = 0;
        slen += sprintf((char *)usbSerialTxBuffer[txBuf_index], "{\"GPIO_PIN_INFO\":[");
//                                    "{\"GPIO_PIN_INFO\":\"active\","
//                                    "\"device_id\":\"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\","
//                                    "\"PinInfo\":[",
//                        *(((uint8_t *)(UID_BASE)) + 0x00), *(((uint8_t *)(UID_BASE)) + 0x01), *(((uint8_t *)(UID_BASE)) + 0x02), *(((uint8_t *)(UID_BASE)) + 0x03),
//                        *(((uint8_t *)(UID_BASE)) + 0x04), *(((uint8_t *)(UID_BASE)) + 0x05), *(((uint8_t *)(UID_BASE)) + 0x06), *(((uint8_t *)(UID_BASE)) + 0x07),
//                        *(((uint8_t *)(UID_BASE)) + 0x14), *(((uint8_t *)(UID_BASE)) + 0x15), *(((uint8_t *)(UID_BASE)) + 0x16), *(((uint8_t *)(UID_BASE)) + 0x17));

        /* add all active GPIO to message payload */

        build_digital_input_payload();
        build_analog_input_payload();
        build_motion_payload();
        build_temp_humidity_payload();

        /* terminate packet string with delimiter so outpost "on data" event triggers*/
        slen += sprintf((char *)usbSerialTxBuffer[txBuf_index] + slen, "]}\r\n");

        /* transmit payload */
        while (CDC_Transmit_FS(usbSerialTxBuffer[txBuf_index], slen) == USBD_BUSY)
        {
            osDelay(10);
        }
        if (++txBuf_index > 1)
        {
            txBuf_index = 0;
        }
      }
    }

/* ================================================================
void build_digital_input_payload(*buffer)
================================================================= */
void build_digital_input_payload(*buffer)
(
    /* add all active GPIO to message payload */
    int i = 0;
    int first_flag = 0;
    do
    {
        if (systemconfig.digitalIns[i].cfg.active == ACTIVE)
        {
            if (first_flag == 0)
            {
              first_flag = 1;
            }
            else
            {
              slen += sprintf((char *)usbSerialTxBuffer[txBuf_index] + slen, ",");
            }

            /* This is original from GPIO, however key/values and data seem mismathed */
            /*slen += sprintf((char *)usbSerialTxBuffer[txBuf_index] + slen,
                            "{"
                            "\"id\":\"%d\","
                            "\"type\":\"%d\","
                            "\"trigger\":\"%d\","
                            "\"debounce\":\"%d\","
                            "\"label\":\"%d\","
                            "\"active\":\"%d\","
                            "\"status\":\"%d\"}",
                            systemconfig.digitalIns[i].cfg.id,
                            systemconfig.digitalIns[i].cfg.type,
                            systemconfig.digitalIns[i].cfg.label,
                            systemconfig.digitalIns[i].cfg.active,
                            systemconfig.digitalIns[i].interface.triglvl,
                            systemconfig.digitalIns[i].interface.debounce,
                            (gpio_state >> i) & 0x01); */
            // Use this version for hardware testing
            digital_input = 0;

        case(i)
        {
            0: digital_input = HAL_GPIO_ReadPin(GPIOA, 0x1);
            1: digital_input = HAL_GPIO_ReadPin(GPIOA, 0x2);
            2: digital_input = HAL_GPIO_ReadPin(GPIOA, 0x4);
            //etc...
        }
        slen += sprintf((char *)usbSerialTxBuffer[txBuf_index] + slen,
                    "{"
                    "\"di_pin\":\"%d\","
                    "\"level\":\"%d\"}",
                    i+1,
                    digital_input
        );
    } while (++i < MAX_DIGITAL_INPUTS);

}
