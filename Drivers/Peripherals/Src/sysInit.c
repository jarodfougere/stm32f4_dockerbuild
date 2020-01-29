#include "processor_select.h"

void SystemInit(void)
{
#if defined(STM32F303K8) /* NUCLEO */

    /* set CP10 and CP11 Full Access */
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  

#elif defined(STM32L072VZT6) /* GPIO V3 MCU */
    /*!< Set MSION bit */
    RCC->CR |= (uint32_t)0x00000100U;

    /*!< Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], MCOSEL[2:0] and MCOPRE[2:0] bits */
    RCC->CFGR &= (uint32_t)0x88FF400CU;

    /*!< Reset HSION, HSIDIVEN, HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFF6U;

    /*!< Reset HSI48ON  bit */
    RCC->CRRCR &= (uint32_t)0xFFFFFFFEU;

    /*!< Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFFU;

    /*!< Reset PLLSRC, PLLMUL[3:0] and PLLDIV[1:0] bits */
    RCC->CFGR &= (uint32_t)0xFF02FFFFU;

    /*!< Disable all interrupts */
    RCC->CIER = 0x00000000U;
#endif

    /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
    /* Vector Table Relocation in Internal SRAM */
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; 
#else
    /* Vector Table Relocation in Internal FLASH */
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; 
#endif
}