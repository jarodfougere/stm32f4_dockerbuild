/**
 * @file rimot_rcc.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level driver for the 
 * reset and clock controller on the stm32f411re microcontroller
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include "rimot_bus_region_offsets.h"
#include "rimot_register_field_sizes.h"

#define RCC_BASE (AHB1PERIPH_BASE + 0x3800UL)

#include "rimot_rcc.h"
#include "rimot_rcc_register_masks.h"
#include "rimot_register_bit_ops.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"

#include "rimot_oscillator_hardware_config.h"

static const uint8_t AHBPrescTable[] = 
{
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    0, 
    1, 
    2, 
    3, 
    4, 
    6, 
    7, 
    8, 
    9
};


static const uint8_t APBPrescTable[8] = 
{
    0, 
    0, 
    0, 
    0, 
    1, 
    2, 
    3, 
    4
};

/* PAGE 102, REFERENCE MANUAL */
struct rcc_regs
{
    hw_reg CR;         /* Clock control register                   */
    hw_reg PLLCFGR;    /* PLL configuration register               */
    hw_reg CFGR;       /* Clock configuration register             */
    hw_reg CIR;        /* Clock interrupt register                 */
    hw_reg AHB1RSTR;   /* AHB1 peripheral reset register           */
    hw_reg AHB2RSTR;   /* AHB2 peripheral reset register           */
    hw_reg AHB3RSTR;   /* AHB3 peripheral reset register           */
    pad32 RESERVED0;   /* Reserved                                 */
    hw_reg APB1RSTR;   /* APB1 peripheral reset register           */
    hw_reg APB2RSTR;   /* APB2 peripheral reset register           */
    pad32 RESERVED1;   /* Reserved                                 */
    pad32 RESERVED2;   /* Reserved                                 */
    hw_reg AHB1ENR;    /* AHB1 peripheral clock register           */
    hw_reg AHB2ENR;    /* AHB2 peripheral clock register           */
    hw_reg AHB3ENR;    /* AHB3 peripheral clock register           */
    pad32 RESERVED3;   /* Reserved                                 */
    hw_reg APB1ENR;    /* APB1 peripheral clock enable register    */
    hw_reg APB2ENR;    /* APB2 peripheral clock enable register    */
    pad32 RESERVED4;   /* Reserved                                 */
    pad32 RESERVED5;   /* Reserved                                 */
    hw_reg AHB1LPENR;  /* AHB1 periph clock enable in LPM register */
    hw_reg AHB2LPENR;  /* AHB2 periph clock enable in LPM register */
    hw_reg AHB3LPENR;  /* AHB3 periph clock enable in LPM register */
    pad32 RESERVED6;   /* Reserved                                 */
    hw_reg APB1LPENR;  /* APB1 periph clk enable in LPM register   */
    hw_reg APB2LPENR;  /* APB2 periph clk enable in LPM register   */
    pad32 RESERVED7;   /* Reserved                                 */
    pad32 RESERVED8;   /* Reserved                                 */
    hw_reg BDCR;       /* Backup domain control register           */
    hw_reg CSR;        /* Clock control & status register          */
    pad32 RESERVED9;   /* Reserved                                 */ 
    pad32 RESERVED10;  /* Reserved                                 */
    hw_reg SSCGR;      /* Spread spectrum clock gen register       */
    hw_reg PLLI2SCFGR; /* PLLI2S configuration register            */
    pad32 RESERVED11;  /* Reserved                                 */
    hw_reg DCKCFGR;    /* Dedicated Clocks configuration register  */
}; 

/* Instance */
#define _RCC ((struct rcc_regs*) RCC_BASE)


#define RCC_PLLCFGR_RST_VALUE 0x24003010U
#define RCC_PLLI2SCFGR_RST_VALUE 0x20003010U

/* Max frequency of family in Hz*/
#define RCC_MAX_FREQUENCY 100000000U 

/* Maximum frequency for system clock at power scale1, in Hz */
#define RCC_MAX_FREQUENCY_SCALE1 RCC_MAX_FREQUENCY 

/* Maximum frequency for system clock at power scale2, in Hz */
#define RCC_MAX_FREQUENCY_SCALE2 84000000U 

/* Maximum frequency for system clock at power scale3, in Hz */
#define RCC_MAX_FREQUENCY_SCALE3 64000000U 

 /* Frequency min for PLLVCO output, in Hz */
#define RCC_PLLVCO_OUTPUT_MIN 100000000U 

 /* Frequency min for PLLVCO input, in Hz */
#define RCC_PLLVCO_INPUT_MIN 950000U 

/* Frequency max for PLLVCO input, in Hz */
#define RCC_PLLVCO_INPUT_MAX 2100000U 

/* Frequency max for PLLVCO output, in Hz */
#define RCC_PLLVCO_OUTPUT_MAX 432000000U 

#define RCC_PLLN_MIN_VALUE 50U
#define RCC_PLLN_MAX_VALUE 432U

/* HCLK frequency to set FLASH latency 1 in power scale 1  */
#define FLASH_SCALE1_LATENCY1_FREQ   30000000U      

/* HCLK frequency to set FLASH latency 2 in power scale 1  */
#define FLASH_SCALE1_LATENCY2_FREQ   64000000U      

/* HCLK frequency to set FLASH latency 3 in power scale 1  */
#define FLASH_SCALE1_LATENCY3_FREQ   90000000U      

/* HCLK frequency to set FLASH latency 1 in power scale 2  */
#define FLASH_SCALE2_LATENCY1_FREQ   30000000U     

/* HCLK frequency to set FLASH latency 2 in power scale 2  */
#define FLASH_SCALE2_LATENCY2_FREQ   64000000U      


/* HCLK frequency to set FLASH latency 1 in power scale 3  */
#define FLASH_SCALE3_LATENCY1_FREQ   30000000U   

/* HCLK frequency to set FLASH latency 2 in power scale 3  */
#define FLASH_SCALE3_LATENCY2_FREQ   64000000U    


void rccLowLevelInit(void)
{   


    /* Disable High speed external input while we configure RCC */
    _RCC->CR &= ~CR_HSEON;

    /*
     * HSE XTAL used with feedback, 
     * no externally driven clock (eg: signal generator) 
     */
    _RCC->CR &= ~CR_HSEBYP; 


    /* Re-enable high speed external oscillator */
    _RCC->CR |= CR_HSEON;

    /* Re-enable high speed internal oscillator. This is a fallback in case of 
     * failure (though HSI is not fast enough to service USB peripheral, we can 
     * still dump debug info out of a UART for example)
     */
    _RCC->CR |= CR_HSION;
}


void rccEnablePeriphClock(RCC_PERIPH_CLOCK_t clock)
{
    switch(clock)
    {
        case RCC_PERIPH_CLOCK_adc:
        {
            _RCC->APB2ENR |= (APB2ENR_ADC1EN);
        }
        break;
        case RCC_PERIPH_CLOCK_gpioa:
        {
            _RCC->AHB1ENR |= (AHB1ENR_GPIOAEN);
        }
        break;
        case RCC_PERIPH_CLOCK_gpiob:
        {
            _RCC->AHB1ENR |= (AHB1ENR_GPIOBEN);
        }
        break;
        case RCC_PERIPH_CLOCK_gpioc:
        {
            _RCC->AHB1ENR |= (AHB1ENR_GPIOCEN);
        }
        break;
        case RCC_PERIPH_CLOCK_gpiod:
        {
            _RCC->AHB1ENR |= (AHB1ENR_GPIODEN);
        }
        break;
        case RCC_PERIPH_CLOCK_gpioe:
        {
            _RCC->AHB1ENR |= (AHB1ENR_GPIOEEN);
        }
        break;
        case RCC_PERIPH_CLOCK_gpioh:
        {
            _RCC->AHB1ENR |= (AHB1ENR_GPIOHEN);
        }
        break;
        case RCC_PERIPH_CLOCK_dma1:
        {
            _RCC->AHB1ENR |= (AHB1ENR_DMA1EN);
        }
        break;
        case RCC_PERIPH_CLOCK_dma2:
        {
            _RCC->AHB1ENR |= (AHB1ENR_DMA2EN);
        }
        break;
        case RCC_PERIPH_CLOCK_crc:
        {
            _RCC->AHB1ENR |= (AHB1ENR_CRCEN);
        }
        break;
        case RCC_PERIPH_CLOCK_usb:
        {
            _RCC->AHB2ENR |= (AHB2ENR_OTGFSEN);
        }
        break;
        case RCC_PERIPH_CLOCK_pwr:
        {
            _RCC->APB1ENR |= (APB1ENR_PWREN);
        }
        break;
        case RCC_PERIPH_CLOCK_i2c3:
        {
            _RCC->APB1ENR |= (APB1ENR_I2C3EN);
        }
        break;
        case RCC_PERIPH_CLOCK_i2c2:
        {
            _RCC->APB1ENR |= (APB1ENR_I2C2EN);
        }
        break;
        case RCC_PERIPH_CLOCK_i2c1:
        {
            _RCC->APB1ENR |= (APB1ENR_I2C1EN);
        }
        break;
        case RCC_PERIPH_CLOCK_usart1:
        {
            _RCC->APB2ENR |= (APB2ENR_USART1EN);
        }
        break;
        case RCC_PERIPH_CLOCK_usart2:
        {
            _RCC->APB1ENR |= (APB1ENR_USART2EN);

        }
        break;
        case RCC_PERIPH_CLOCK_usart6:
        {
            _RCC->APB2ENR |= (APB2ENR_USART6EN);
        }
        break;
        case RCC_PERIPH_CLOCK_spi5:
        {
            _RCC->APB2ENR |= (APB2ENR_SPI5EN);
        }
        break;
        case RCC_PERIPH_CLOCK_spi4:
        {
            _RCC->APB2ENR |= (APB2ENR_SPI4EN);
        }
        break;
        case RCC_PERIPH_CLOCK_spi3:
        {
            _RCC->APB1ENR |= (APB1ENR_SPI3EN);
        }
        break;
        case RCC_PERIPH_CLOCK_spi2:
        {
            _RCC->APB1ENR |= (APB1ENR_SPI2EN);
        }
        break;
        case RCC_PERIPH_CLOCK_spi1:
        {
            _RCC->APB2ENR |= (APB2ENR_SPI1EN);
        }
        break;
        case RCC_PERIPH_CLOCK_wwdg:
        {
            _RCC->APB1ENR |= (APB1ENR_WWDGEN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim5:
        {
            _RCC->APB1ENR |= (APB1ENR_TIM5EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim4:
        {
            _RCC->APB1ENR |= (APB1ENR_TIM4EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim3:
        {
            _RCC->APB1ENR |= (APB1ENR_TIM3EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim2:
        {
            _RCC->APB1ENR |= (APB1ENR_TIM2EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim1:
        {
            _RCC->APB2ENR |= (APB2ENR_TIM1EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim11:
        {
            _RCC->APB2ENR |= (APB2ENR_TIM11EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim10:
        {
            _RCC->APB2ENR |= (APB2ENR_TIM10EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim9:
        {
            _RCC->APB2ENR |= (APB2ENR_TIM9EN);
        }
        break;
        case RCC_PERIPH_CLOCK_syscfg:
        {
            _RCC->APB2ENR |= (APB2ENR_SYSCFGEN);
        }
        break;
        case RCC_PERIPH_CLOCK_sdio:
        {
            _RCC->APB2ENR |= (APB2ENR_SDIOEN);
        }
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}




void rccDisablePeriphClock(RCC_PERIPH_CLOCK_t clock)
{
    switch(clock)
    {
        case RCC_PERIPH_CLOCK_adc:
        {
            _RCC->APB2ENR &= ~(APB2ENR_ADC1EN);
        }
        break;
        case RCC_PERIPH_CLOCK_gpioa:
        {
            _RCC->AHB1ENR &= ~(AHB1ENR_GPIOAEN);
        }
        break;
        case RCC_PERIPH_CLOCK_gpiob:
        {
            _RCC->AHB1ENR &= ~(AHB1ENR_GPIOBEN);
        }
        break;
        case RCC_PERIPH_CLOCK_gpioc:
        {
            _RCC->AHB1ENR &= ~(AHB1ENR_GPIOCEN);
        }
        break;
        case RCC_PERIPH_CLOCK_gpiod:
        {
            _RCC->AHB1ENR &= ~(AHB1ENR_GPIODEN);
        }
        break;
        case RCC_PERIPH_CLOCK_gpioe:
        {
            _RCC->AHB1ENR &= ~(AHB1ENR_GPIOEEN);
        }
        break;
        case RCC_PERIPH_CLOCK_gpioh:
        {
            _RCC->AHB1ENR &= ~(AHB1ENR_GPIOHEN);
        }
        break;
        case RCC_PERIPH_CLOCK_dma1:
        {
            _RCC->AHB1ENR &= ~(AHB1ENR_DMA1EN);
        }
        break;
        case RCC_PERIPH_CLOCK_dma2:
        {
            _RCC->AHB1ENR &= ~(AHB1ENR_DMA2EN);
        }
        break;
        case RCC_PERIPH_CLOCK_crc:
        {
            _RCC->AHB1ENR &= ~(AHB1ENR_CRCEN);
        }
        break;
        case RCC_PERIPH_CLOCK_usb:
        {
            _RCC->AHB2ENR &= ~(AHB2ENR_OTGFSEN);
        }
        break;
        case RCC_PERIPH_CLOCK_pwr:
        {
            _RCC->APB1ENR &= ~(APB1ENR_PWREN);
        }
        break;
        case RCC_PERIPH_CLOCK_i2c3:
        {
            _RCC->APB1ENR &= ~(APB1ENR_I2C3EN);
        }
        break;
        case RCC_PERIPH_CLOCK_i2c2:
        {
            _RCC->APB1ENR &= ~(APB1ENR_I2C2EN);
        }
        break;
        case RCC_PERIPH_CLOCK_i2c1:
        {
            _RCC->APB1ENR &= ~(APB1ENR_I2C1EN);
        }
        break;
        case RCC_PERIPH_CLOCK_usart1:
        {
            _RCC->APB2ENR &= ~(APB2ENR_USART1EN);
        }
        break;
        case RCC_PERIPH_CLOCK_usart2:
        {
            _RCC->APB1ENR &= ~(APB1ENR_USART2EN);

        }
        break;
        case RCC_PERIPH_CLOCK_usart6:
        {
            _RCC->APB2ENR &= ~(APB2ENR_USART6EN);
        }
        break;
        case RCC_PERIPH_CLOCK_spi5:
        {
            _RCC->APB2ENR &= ~(APB2ENR_SPI5EN);
        }
        break;
        case RCC_PERIPH_CLOCK_spi4:
        {
            _RCC->APB2ENR &= ~(APB2ENR_SPI4EN);
        }
        break;
        case RCC_PERIPH_CLOCK_spi3:
        {
            _RCC->APB1ENR &= ~(APB1ENR_SPI3EN);
        }
        break;
        case RCC_PERIPH_CLOCK_spi2:
        {
            _RCC->APB1ENR &= ~(APB1ENR_SPI2EN);
        }
        break;
        case RCC_PERIPH_CLOCK_spi1:
        {
            _RCC->APB2ENR &= ~(APB2ENR_SPI1EN);
        }
        break;
        case RCC_PERIPH_CLOCK_wwdg:
        {
            _RCC->APB1ENR &= ~(APB1ENR_WWDGEN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim5:
        {
            _RCC->APB1ENR &= ~(APB1ENR_TIM5EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim4:
        {
            _RCC->APB1ENR &= ~(APB1ENR_TIM4EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim3:
        {
            _RCC->APB1ENR &= ~(APB1ENR_TIM3EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim2:
        {
            _RCC->APB1ENR &= ~(APB1ENR_TIM2EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim1:
        {
            _RCC->APB2ENR &= ~(APB2ENR_TIM1EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim11:
        {
            _RCC->APB2ENR &= ~(APB2ENR_TIM11EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim10:
        {
            _RCC->APB2ENR &= ~(APB2ENR_TIM10EN);
        }
        break;
        case RCC_PERIPH_CLOCK_tim9:
        {
            _RCC->APB2ENR &= ~(APB2ENR_TIM9EN);
        }
        break;
        case RCC_PERIPH_CLOCK_syscfg:
        {
            _RCC->APB2ENR &= ~(APB2ENR_SYSCFGEN);
        }
        break;
        case RCC_PERIPH_CLOCK_sdio:
        {
            _RCC->APB2ENR &= ~(APB2ENR_SDIOEN);
        }
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}

uint32_t rccGetSysClockVal(void)
{
    uint32_t pllvco = 0; 
    uint32_t pllp = 2;
    uint32_t pllsource = 0;
    uint32_t pllm = 2;
    uint32_t sysClockVal;

    switch (_RCC->CFGR & CFGR_SWS)
    {
        case CFGR_SWS_HSI:  /* HSI used as system clock source */
        {
            sysClockVal = HSI_RC_OSC_FREQ;
        }
        break;
        case CFGR_SWS_HSE:  /* HSE used as system clock source */
        {
            sysClockVal = HIGH_SPEED_EXTERNAL_XTAL_FREQ;
        }
        break;
        case CFGR_SWS_PLL:  /* PLL used as system clock source */
        {
            /* 
             * EITHER:
             * 
             * PLL_VCO = (HIGH_SPEED_EXTERNAL_XTAL_FREQ) / PLL_M) * PLL_N
             * 
             * OR
             * 
             * PLL_VCO = (HSI_RC_OSC_FREQ) / PLL_M) * PLL_N
             *  
             * therefoer:
             * SYSCLK = PLL_VCO / PLL_P
             */    

            pllsource = (_RCC->PLLCFGR & PLLCFGR_PLLSRC) >> PLLCFGR_PLLSRC_POS;
            pllm = _RCC->PLLCFGR & PLLCFGR_PLLM;
        
            if (pllsource != 0)
            {
                /* HSE used as PLL clock source */
                pllvco = (HIGH_SPEED_EXTERNAL_XTAL_FREQ / pllm) * 
                        ((_RCC->PLLCFGR & PLLCFGR_PLLN) >> PLLCFGR_PLLN_POS);
            }
            else
            {
                /* HSI used as PLL clock source */
                pllvco = (HSI_RC_OSC_FREQ / pllm) * 
                        ((_RCC->PLLCFGR & PLLCFGR_PLLN) >> PLLCFGR_PLLN_POS);
            }

            pllp = 
            (((_RCC->PLLCFGR & PLLCFGR_PLLP) >> PLLCFGR_PLLP_POS) + 1 ) * 2;

            sysClockVal = pllvco/pllp;
        }
        break;
        default:
        {
            sysClockVal = HSI_RC_OSC_FREQ;
        }
        break;
    }

    /* Get HCLK prescaler and compute HCLK Freq */
    sysClockVal = sysClockVal >> 
                    AHBPrescTable[((_RCC->CFGR & CFGR_HPRE) >> CFGR_HPRE_POS)];

    return sysClockVal;
}




void RCC_IRQHandler(void)
{

}