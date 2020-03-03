#if defined(MCU_APP)
#include "drivers.h"


#if defined(USE_HAL_DRIVER)
I2C_HandleTypeDef hi2c1;    /* I2c interface provisioned */
#if !defined(NDEBUG)
UART_HandleTypeDef my_uart; /* uart is used for debug */
#endif /* DEBUG BUILD */
#endif /* USING STM32 HAL */
#endif /* MCU APP */

#include "serial_data.h"


static void UART_Init(UART_HandleTypeDef *uart, USART_TypeDef* instance);

/* USER CONFIGURES THE PARAMETERS FOR THE USART */
static void UART_Init(UART_HandleTypeDef *uart, USART_TypeDef* instance)
{   
    if(NULL != uart && NULL != instance)
    {
        uart->Instance = instance;
        uart->Init.BaudRate = 9600;
        uart->Init.WordLength = UART_WORDLENGTH_8B;
        uart->Init.StopBits = UART_STOPBITS_1;
        uart->Init.Parity = UART_PARITY_NONE;
        uart->Init.Mode = UART_MODE_TX_RX;
        uart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
        uart->Init.OverSampling = UART_OVERSAMPLING_16;
        ASSERT(HAL_OK == HAL_UART_Init(uart)); 
    }
}


void init_comms_interface(void)
{
    #if defined(MCU_APP)
    MX_USB_DEVICE_Init();
    #if !defined(NDEBUG)
    /* IN DEBUG MODE ALSO SEND DATA VIA USART */
    UART_Init(&my_uart, USART2); 
    #endif
    #else
        /* OSkernel will init the stdout/stdin interfaces */
    #endif
}



void transmit_serial(const char* restrict format, ...)
{   
    va_list args;
    va_start(args, format);
    const char msg_delim[] = "\r\n";

    /* this is used to differentiate between UART and USB messages when the application is in a hosted environment */
    const char msg_prelim[] = "[SERIAL] : "; 

    char data_buf[500]; /* data holder */

    /* load message prefix into buffer */
    strncpy(data_buf, msg_prelim, sizeof(msg_prelim) -1);

    /* load actual payload into rest of buffer */
    /* add 1 because we dont copy nullchar from msg prelim */
    vsnprintf(data_buf + (sizeof(msg_prelim) - 1), sizeof(data_buf) - (sizeof(msg_prelim) + 1 + strlen(msg_delim)), format, args); 
#if defined(MCU_APP)

    /* put serial rx delimiter on the end of message if it doesnt exist */
    if(NULL == strstr(data_buf, msg_delim))
    {
        strcat(data_buf, msg_delim);
    }

    /* WARNING: THIS IS A BLOCKING TRANSMISSION WITH A TIMEOUT */
    HAL_UART_Transmit(&my_uart, (uint8_t*)data_buf, (uint16_t)strlen(data_buf), 300); 
#else
    printf(data_buf);
#endif
}


void transmit_usb(const char* restrict format, ...)
{
    va_list args;
    va_start(args, format);
#if defined(MCU_APP)
    const char msg_delim[] = "\r\n";
    char data_buf[500];
    vsnprintf(data_buf, sizeof(data_buf) - strlen(msg_delim), format, args);

    /* put serial rx delimiter on the end of message if it doesnt exist */
    if(NULL == strstr(data_buf, msg_delim))
    {
        strcat(data_buf, msg_delim);
    }
    #if !defined(NDEBUG)
    CDC_Transmit_FS((uint8_t*)data_buf, (uint16_t)strlen(data_buf)); 
    #endif /* !defined(NDEBUG) */
#else
    vprintf(format, args); /* just directly print to the terminal */
#endif
}


/*
static void MX_I2C1_Init(void)
{
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    LL_ASSERT(HAL_I2C_Init(&hi2c1) == HAL_OK)
}
*/


