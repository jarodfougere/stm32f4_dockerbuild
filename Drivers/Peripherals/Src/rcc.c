#include <stdint.h>
#include <string.h>

#include "processor_select.h"
#include "rcc.h"


void rcc_init(void)
{   
    memset(RCC, 0, sizeof(RCC_TypeDef));

    /* reset MasterClockOut bits */
    RCC->CFGR &= ~(RCC_CFGR_MCO_Msk);

    /* select sysclock as master clock out */
    RCC->CFGR |= RCC_CFGR_MCO_SYSCLK; 

    /* enable HighSpeedInternal oscillator */
    RCC->CR |= RCC_CR_HSION;

    /* wait for hardware to stabilize the oscillator */
    while((RCC_CR_HSIRDY) != (RCC->CR & RCC_CR_HSIRDY))
    {
        /* CARL + JAROD TODO: ADD TIMEOUT SAFETY CONDITION (THIS WILL BE HARD BECAUSE WTF TO DO WHEN NO CLOCKS) */
    }

    //REMOVE EVERYTHING BELOW HERE ONCE WE GET THE SYSTEM CLOCK CONFIGURED CORRECTLY

    /* clear MCO prescaler */
    RCC->CFGR &= ~(RCC_CFGR_MCOPRE);

    /* divide master clock by 16 */
    RCC->CFGR |= RCC_CFGR_MCOPRE_DIV16; 


    GPIOA->MODER    &= ~(GPIO_MODER_MODER8);
    GPIOA->MODER    |= GPIO_MODER_MODER8_1;
    RCC->AHBENR     |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER    &= ~(GPIO_MODER_MODER8);
    
    /* 
    TODO: CHIPSET COMPAT. 
    CMSIS DOESNT SEEM TO HAVE A DEFINITION REGARDING THE ALTFUNC VALUE */
    GPIOA->AFR[1]   |= 0 << 0;

    //0xFUL 0x0000000f
}