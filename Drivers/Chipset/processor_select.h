#ifndef PROCESSOR_SELECT
#define PROCESSOR_SELECT

#if defined(STM32F303K8)    /* NUCLEO */
    #include "stm32f303x8.h"
#elif defined(STM32L072VZT6)    /* GPIO V3 MCU */
    #include "stm32l072xx.h"
#endif






#endif