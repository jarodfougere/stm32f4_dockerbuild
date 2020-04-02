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
    struct adc_common_regs  *adc1_common;
    struct adc_regs         *adc1;
    struct dma_regs         *dma1;
    struct dma_regs         *dma2;
    struct crc_regs         *crc;
    struct exti_regs        *exti;
    struct flash_regs       *flash;
    struct gpio_port        *gpioA;
    struct gpio_port        *gpioB;
    struct gpio_port        *gpioC;
    struct gpio_port        *gpioD;
    struct gpio_port        *gpioE;
    struct gpio_port        *gpioH;
    struct iwdg_regs        *iwdg;
    struct i2c_regs         *i2c1;
    struct i2c_regs         *i2c2;
    struct i2c_regs         *i2c3;
    struct mcu_debug_regs   *mcudbg;
    struct pwr_ctl_regs     *pwr;
    struct rcc_regs         *rcc;
    struct rtc_regs         *rtc;
    struct sdio_regs        *sdio;
    struct spi_regs         *spi1;
    struct spi_regs         *spi2;
    struct spi_regs         *spi3;
    struct spi_regs         *spi4;
    struct spi_regs         *spi5;
    struct syscfg_regs      *syscfg;
    struct timer_regs       *tim1;
    struct timer_regs       *tim2;
    struct timer_regs       *tim3;
    struct timer_regs       *tim4;
    struct timer_regs       *tim5;
    struct timer_regs       *tim9;
    struct timer_regs       *tim10;
    struct timer_regs       *tim11;
    struct usart_regs       *usart1;
    struct usart_regs       *usart2;
    struct usart_regs       *usart6;
    struct usb_otg          *usb;
    struct wwdg_regs        *wwdg;
};


#define NEW_PERIPH_MAP(name)        \
struct periph_map name =            \
{                                   \
    .adc1_common = _ADC1_COMMON,    \
    .adc1   = _ADC1,                \
    .dma1   = _DMA1,                \
    .dma2   = _DMA2,                \
    .crc    = _CRC,                 \
    .exti   = _EXTI,                \
    .flash  = _FLASH,               \
    .gpioA  = _GPIOA,               \
    .gpioB  = _GPIOB,               \
    .gpioC  = _GPIOC,               \
    .gpioD  = _GPIOD,               \
    .gpioE  = _GPIOE,               \
    .gpioH  = _GPIOH,               \
    .iwdg   = _IWDG,                \
    .i2c1   = _I2C1,                \
    .i2c2   = _I2C2,                \
    .i2c3   = _I2C3,                \
    .mcudbg = _MCUDBG,              \
    .pwr    = _PWR,                 \
    .rcc    = _RCC,                 \
    .rtc    = _RTC,                 \
    .sdio   = _SDIO,                \
    .spi1   = _SPI1,                \
    .spi2   = _SPI2,                \
    .spi3   = _SPI3,                \
    .spi4   = _SPI4,                \
    .spi5   = _SPI5,                \
    .syscfg = _SYSCFG,              \
    .tim1   = _TIM1,                \
    .tim2   = _TIM2,                \
    .tim3   = _TIM3,                \
    .tim4   = _TIM4,                \
    .tim5   = _TIM5,                \
    .tim9   = _TIM9,                \
    .tim10  = _TIM10,               \
    .tim11  = _TIM11,               \
    .usart1 = _USART1,              \
    .usart2 = _USART2,              \
    .usart6 = _USART6,              \
    .usb    = _USB,                 \
    .wwdg   = _WWDG                 \
}

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_STM32F411XE_PERIPHERALS */