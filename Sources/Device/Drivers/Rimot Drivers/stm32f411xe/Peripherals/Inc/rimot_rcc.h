#ifndef RIMOT_MCU_
#define RIMOT_MCU_
#ifdef __cplusplus
extern "C" {
#endif /* C linkage  */


void rccLowLevelInit(void);

typedef enum
{
    RCC_CLOCKSTATE_enabled,
    RCC_CLOCKSTATE_disabled,
}   RCC_CLOCKSTATE_t;


typedef enum
{
    RCC_APB1_CLOCK_TYPE_timer5,
    RCC_APB1_CLOCK_TYPE_wwdg,
    RCC_APB1_CLOCK_TYPE_spi2,
    RCC_APB1_CLOCK_TYPE_usart2,
    RCC_APB1_CLOCK_TYPE_i2c1,
    RCC_APB1_CLOCK_TYPE_i2c2,
    RCC_APB1_CLOCK_TYPE_voltageReg
}   RCC_APB1_CLOCK_TYPE_t;



void rccEnableAPB1Clk(RCC_APB1_CLOCK_TYPE_t clockType, RCC_CLOCKSTATE_t state);


#ifdef __cplusplus
}
#endif /* C linkage  */
#endif /* RIMOT_MCU_  */