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
#if defined(MCU_APP)
    const char msg_delim[] = "\r\n";
    char data_buf[500];
    vsnprintf(data_buf, sizeof(data_buf) - strlen(msg_delim), format, args);

    /* put serial rx delimiter on the end of message */
    if(NULL == strstr(data_buf, msg_delim))
    {
        strcat(data_buf, msg_delim);
    }
    CDC_Transmit_FS((uint8_t*)data_buf, (uint16_t)strlen(data_buf));
    #if !defined(NDEBUG)
    /* WARNING: THIS IS A BLOCKING USART TX (I HAVE SET A 300ms TIMEOUT) */
    /* 300 is the time before transmit times out */
    HAL_UART_Transmit(&my_uart, (uint8_t*)data_buf, (uint16_t)strlen(data_buf), 300); 
    #endif /* !defined(NDEBUG) */
#else
    vprintf(format, args);
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


