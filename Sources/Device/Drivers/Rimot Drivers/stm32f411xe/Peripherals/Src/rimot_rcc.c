/**
 * @file rimot_rcc.c
 * @author Carl Mattatall
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


void rccEnableVoltageRegulatorInternalClock(void)
{
    _RCC->AHB1ENR |= APB1ENR_PWREN;

    /* 
     * We do this to make a non-optimizable delay. 
     * Also so we can confirm the regulator clock actually worked 
     */
    volatile uint32_t temp = _RCC->AHB1ENR & APB1ENR_PWREN;
    LL_ASSERT( temp);
}


void rccEnableAPB1Clk(RCC_APB1_CLOCK_TYPE_t clockType, RCC_CLOCKSTATE_t state)
{
    switch(clockType)
    {
        case RCC_APB1_CLOCK_TYPE_timer5:
        {   
            _RCC->APB1ENR = (state == RCC_CLOCKSTATE_enabled) ? 
                            _RCC->APB1ENR | (APB1ENR_TIM5EN) :
                            _RCC->APB1ENR & ~(APB1ENR_TIM5EN);
        }
        break;
        case RCC_APB1_CLOCK_TYPE_wwdg:
        {   
            _RCC->APB1ENR = (state == RCC_CLOCKSTATE_enabled) ? 
                            _RCC->APB1ENR  | (APB1ENR_WWDGEN) : 
                            _RCC->APB1ENR  & ~(APB1ENR_WWDGEN);
        }
        break;
        case RCC_APB1_CLOCK_TYPE_spi2:
        {   
            _RCC->APB1ENR = (state == RCC_CLOCKSTATE_enabled) ? 
                            _RCC->APB1ENR  | (APB1ENR_SPI2EN) : 
                            _RCC->APB1ENR  & ~(APB1ENR_SPI2EN);
        }
        break;
        case RCC_APB1_CLOCK_TYPE_usart2:
        {
            _RCC->APB1ENR = (state == RCC_CLOCKSTATE_enabled) ? 
                            _RCC->APB1ENR  | (APB1ENR_USART2EN) : 
                            _RCC->APB1ENR  & ~(APB1ENR_USART2EN);
        }
        break;
        case RCC_APB1_CLOCK_TYPE_i2c1:
        {
            _RCC->APB1ENR = (state == RCC_CLOCKSTATE_enabled) ? 
                            _RCC->APB1ENR  | (APB1ENR_I2C1EN) : 
                            _RCC->APB1ENR  & ~(APB1ENR_I2C1EN);
        }
        break;
        case RCC_APB1_CLOCK_TYPE_i2c2:
        {
            _RCC->APB1ENR = (state == RCC_CLOCKSTATE_enabled) ? 
                            _RCC->APB1ENR  | (APB1ENR_I2C2EN) : 
                            _RCC->APB1ENR  & ~(APB1ENR_I2C2EN);
        }
        break;
        case RCC_APB1_CLOCK_TYPE_voltageReg:
        {
            _RCC->APB1ENR = (state == RCC_CLOCKSTATE_enabled) ? 
                            _RCC->APB1ENR  | (APB1ENR_PWREN) : 
                            _RCC->APB1ENR  & ~(APB1ENR_PWREN);
        }
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
}
