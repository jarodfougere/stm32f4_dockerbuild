#ifndef RIMOT_STM32F411XE_PERIPHERALS
#define RIMOT_STM32F411XE_PERIPHERALS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include <stdint.h>

#include "rimot_adc_regs.h"
#include "rimot_dma_regs.h"
#include "rimot_crc_regs.h"
#include "rimot_exti_regs.h"
#include "rimot_flash_ctl_regs.h"
#include "rimot_gpio_regs.h"
#include "rimot_iwdg_regs.h"
#include "rimot_i2c_regs.h"
#include "rimot_mcu_dbg_regs.h"
#include "rimot_power_control_regs.h"
#include "rimot_rcc_regs.h"
#include "rimot_rtc_regs.h"
#include "rimot_sdio_regs.h"
#include "rimot_spi_regs.h"
#include "rimot_syscfg_regs.h"
#include "rimot_timer_regs.h"
#include "rimot_usart_regs.h"
#include "rimot_usb_otg_regs.h"
#include "rimot_wwdg_regs.h"




struct periph_map
{   
    struct adc_common_regs  *ADC1_COMMON;
    struct adc_regs         *ADC1;
    struct dma_regs         *DMA1;
    struct dma_regs         *DMA2;
    struct crc_regs         *CRC;
    struct exti_regs        *EXTI;
    struct flash_regs       *FLASH;
    struct gpio_port        *GPIOA;
    struct gpio_port        *GPIOB;
    struct gpio_port        *GPIOC;
    struct gpio_port        *GPIOD;
    struct gpio_port        *GPIOE;
    struct gpio_port        *GPIOH;
    struct iwdg_regs        *IWDG;
    struct i2c_regs         *I2C1;
    struct i2c_regs         *I2C2;
    struct i2c_regs         *I2C3;
    struct mcu_debug_regs   *MCUDBG;
    struct pwr_ctl_regs     *PWR;
    struct rcc_regs         *RCC;
    struct rtc_regs         *RTC;
    struct sdio_regs        *SDIO;
    struct spi_regs         *SPI1;
    struct spi_regs         *SPI2;
    struct spi_regs         *SPI3;
    struct spi_regs         *SPI4;
    struct spi_regs         *SPI5;
    struct syscfg_regs      *SYSCFG;
    struct timer_regs       *TIM1;
    struct timer_regs       *TIM2;
    struct timer_regs       *TIM3;
    struct timer_regs       *TIM4;
    struct timer_regs       *TIM5;
    struct timer_regs       *TIM9;
    struct timer_regs       *TIM10;
    struct timer_regs       *TIM11;
    struct usart_regs       *USART1;
    struct usart_regs       *USART2;
    struct usart_regs       *USART6;
    struct usb_otg_regs     *USB;
    struct wwdg_regs        *WWDG;
};

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_STM32F411XE_PERIPHERALS */