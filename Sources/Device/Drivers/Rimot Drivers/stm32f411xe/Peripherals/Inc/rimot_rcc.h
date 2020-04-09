#ifndef RIMOT_MCU_
#define RIMOT_MCU_
#ifdef __cplusplus
extern "C" {
#endif /* C linkage  */

void rccLowLevelInit(void);


typedef enum
{
    RCC_PERIPH_CLOCK_adc,
    RCC_PERIPH_CLOCK_gpioa,
    RCC_PERIPH_CLOCK_gpiob,
    RCC_PERIPH_CLOCK_gpioc,
    RCC_PERIPH_CLOCK_gpiod,
    RCC_PERIPH_CLOCK_gpioe,
    RCC_PERIPH_CLOCK_gpioh,
    RCC_PERIPH_CLOCK_dma1,
    RCC_PERIPH_CLOCK_dma2,
    RCC_PERIPH_CLOCK_crc,
    RCC_PERIPH_CLOCK_usb,
    RCC_PERIPH_CLOCK_pwr,
    RCC_PERIPH_CLOCK_i2c3,
    RCC_PERIPH_CLOCK_i2c2,
    RCC_PERIPH_CLOCK_i2c1,
    RCC_PERIPH_CLOCK_usart1,
    RCC_PERIPH_CLOCK_usart2,
    RCC_PERIPH_CLOCK_usart6,
    RCC_PERIPH_CLOCK_spi5,
    RCC_PERIPH_CLOCK_spi4,
    RCC_PERIPH_CLOCK_spi3,
    RCC_PERIPH_CLOCK_spi2,
    RCC_PERIPH_CLOCK_spi1,
    RCC_PERIPH_CLOCK_wwdg,
    RCC_PERIPH_CLOCK_tim5,
    RCC_PERIPH_CLOCK_tim4,
    RCC_PERIPH_CLOCK_tim3,
    RCC_PERIPH_CLOCK_tim2,
    RCC_PERIPH_CLOCK_tim1,
    RCC_PERIPH_CLOCK_tim11,
    RCC_PERIPH_CLOCK_tim10,
    RCC_PERIPH_CLOCK_tim9,
    RCC_PERIPH_CLOCK_syscfg,
    RCC_PERIPH_CLOCK_sdio,
}   RCC_PERIPH_CLOCK_t;



void rccEnablePeriphClock(RCC_PERIPH_CLOCK_t clock);
void rccDisablePeriphClock(RCC_PERIPH_CLOCK_t clock);

uint32_t rccGetSysClockVal(void);




#ifdef __cplusplus
}
#endif /* C linkage  */
#endif /* RIMOT_MCU_  */