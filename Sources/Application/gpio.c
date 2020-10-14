#include "gpio.h"
#include <stdint.h>

//  MCU IO Pin COntrol
// The following structure controls the mode and state for each pin of a port.
/*
typedef struct
{
    __IO uint32_t MODER;   /*!< GPIO port mode register, Address offset: 0x00 */
    __IO uint32_t OTYPER;  /*!< GPIO port output type register, Address offset: 0x04 */
    __IO uint32_t OSPEEDR; /*!< GPIO port output speed register, Address offset: 0x08 */
    __IO uint32_t PUPDR;   /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C */
    __IO uint32_t IDR; /*!< GPIO port input data register, Address offset: 0x10 */
    __IO uint32_t ODR; /*!< GPIO port output data register, Address offset: 0x14 */
    __IO uint32_t BSRR; /*!< GPIO port bit set/reset register, Address offset: 0x18 */
    __IO uint32_t LCKR; /*!< GPIO port configuration lock register, Address offset: 0x1C */
    __IO uint32_t AFR[2]; /*!< GPIO alternate function registers, Address offset: 0x20-0x24 */
}
GPIO_TypeDef;
*/
/*
typedef struct
{
   uint32_t Pin;    /*Specifies the GPIO pins to be configured. */
   uint32_t Mode;   /*Specifies the operating mode for the selected pins. */ 
   uint32_t Pull;   /*Specifies the Pull-up or Pull-Down activation for the selected pins. */ 
   uint32_t Speed;     /*!< Specifies the speed for the selected pins. */ 
   uint32_t Alternate; /*!< Peripheral to be connected to the selected pins. */
} GPIO_InitTypeDef;
*/
// In RF Sensor repository, pin configuration is handled (mostly) in gpio.c
// and adc.c. Unused pins are configured in gpio.c. In RF Sensor they are
// put into an 'Analog mode' (??) Initialization is done by writing defined
// values into a structure type GPIO_InitTypeDef. The function
// HAL_GPIO_Init() is called to configure the appropriate port pointer. This
// function updates parameters in port GPIO_TypeDef STRUCT.
// GPIO_InitStruct.Pin = GPIO_PIN_2;
// GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
// GPIO_InitStruct.Pull = GPIO_NOPULL;
// HAL_GPIO_Init(<port GPIO_TypeDef pointer>, <address of structure with
// configuration>); HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

// Example of reading a pin (no HAL function to do a multibit read of a
// port) HAL_GPIO_ReadPin(<port GPIO_TypeDef pointer>, <32bit mask
// indicating bit to be read>) HAL_GPIO_ReadPin(GPIOA, DIGITAL_INPUT_0_PIN)
// Example for writing common value to two pins (no HAL function to write
// multibit value to a port) HAL_GPIO_WritePin(<port GPIO_TypeDef pointer>,
// <32bit mask indicating bits to be written>, <value>);
// HAL_GPIO_WritePin(GPIOB, LED_0_EN_Pin|LED_1_EN_Pin, GPIO_PIN_RESET);

void MX_GPIO_Init(void)
{
    /* GPIO Ports Clock Enable  - WHAT IS THIS FOR????? */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    // Write default state on digital outputs - Do this before configuring the
    // pins as output
    HAL_GPIO_WritePin(DO0_GPIO_Port, DO0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DO1_GPIO_Port, DO1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DO2_GPIO_Port, DO2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DO3_GPIO_Port, DO3_Pin, GPIO_PIN_RESET);

    /* INIT GPIOB (OUTPUT PINS) */
    GPIO_InitStruct.Pin   = DO0_Pin | DO1_Pin | DO2_Pin | DO3_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* INIT GPIOB (INPUT PINS)*/
    GPIO_InitStruct.Pin  = MOTION_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* INIT GPIOC (INPUT PINS)*/
    GPIO_InitStruct.Pin = DI0_Pin | DI1_Pin | DI2_Pin | DI3_Pin | DI4_Pin |
                          DI5_Pin | DI6_Pin | DI7_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}